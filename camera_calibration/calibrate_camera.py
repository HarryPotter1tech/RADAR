#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cv2
import numpy as np
import json
import os
import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk

class CameraCalibrator:
    def __init__(self, camera_id=4, img_dir='./calibration_images'):
        """
        camera_id: 摄像头设备索引，根据你的虚拟摄像头修改，例如 /dev/video4 对应 4
        img_dir:   保存采集图像的目录
        """
        self.camera_id = camera_id
        self.img_dir = img_dir
        if not os.path.exists(self.img_dir):
            os.makedirs(self.img_dir)

        # 棋盘格参数（根据你的标定板设置）
        self.CHECKERBOARD = (11, 8)   # 内角点数（宽12，高9）
        self.SQUARE_SIZE = 15         # 单个方格边长（毫米），实际打印尺寸

        # 存储点集
        self.objpoints = []   # 世界坐标系中的3D点
        self.imgpoints = []   # 图像中的2D点

        # 生成世界坐标系中的棋盘格点（Z=0平面）
        self.objp = np.zeros((self.CHECKERBOARD[0] * self.CHECKERBOARD[1], 3), np.float32)
        self.objp[:, :2] = np.mgrid[0:self.CHECKERBOARD[0], 0:self.CHECKERBOARD[1]].T.reshape(-1, 2)
        self.objp *= self.SQUARE_SIZE

        # 标定结果
        self.camera_matrix = None
        self.dist_coeffs = None

        # 创建Tkinter窗口
        self.root = tk.Tk()
        self.root.title("相机标定工具 - 实时采集")
        self.root.geometry("1920x1080")

        # 视频显示标签
        self.video_label = tk.Label(self.root)
        self.video_label.pack(pady=10)

        # 控制按钮区域
        control_frame = tk.Frame(self.root)
        control_frame.pack(pady=10)

        self.capture_btn = tk.Button(control_frame, text="采集图像", command=self.capture_frame,
                                     bg="green", fg="white", width=12)
        self.capture_btn.pack(side=tk.LEFT, padx=5)

        self.calibrate_btn = tk.Button(control_frame, text="开始标定", command=self.calibrate,
                                       bg="blue", fg="white", width=12)
        self.calibrate_btn.pack(side=tk.LEFT, padx=5)

        self.save_btn = tk.Button(control_frame, text="保存参数", command=self.save_params,
                                  bg="orange", fg="white", width=12)
        self.save_btn.pack(side=tk.LEFT, padx=5)

        self.load_btn = tk.Button(control_frame, text="加载参数", command=self.load_params,
                                  bg="purple", fg="white", width=12)
        self.load_btn.pack(side=tk.LEFT, padx=5)

        # 状态信息栏
        self.info_label = tk.Label(self.root, text="就绪", bd=1, relief=tk.SUNKEN, anchor=tk.W)
        self.info_label.pack(side=tk.BOTTOM, fill=tk.X)

        # 打开摄像头
        self.cap = cv2.VideoCapture(self.camera_id)
        if not self.cap.isOpened():
            messagebox.showerror("错误", f"无法打开摄像头 {self.camera_id}，请检查设备是否存在")
            self.root.quit()
            return

        # 启动视频更新循环
        self.update_frame()
        self.root.mainloop()

    def update_frame(self):
        """实时从摄像头读取画面并显示在 GUI 上"""
        ret, frame = self.cap.read()
        if ret:
            # 转换为 RGB 格式，供 PIL 使用
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(frame_rgb)
            # 缩放以适应窗口（保持宽高比）
            img.thumbnail((1920, 1080))
            imgtk = ImageTk.PhotoImage(image=img)
            self.video_label.imgtk = imgtk
            self.video_label.configure(image=imgtk)
        self.video_label.after(30, self.update_frame)  # 约33 FPS

    def capture_frame(self):
        """采集当前帧，检测棋盘格角点，若成功则保存图像并记录点集"""
        ret, frame = self.cap.read()
        if not ret:
            self.info_label.config(text="读取摄像头失败")
            return

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        ret_corners, corners = cv2.findChessboardCorners(gray, self.CHECKERBOARD, None)

        if ret_corners:
            # 亚像素细化
            criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
            corners2 = cv2.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria)

            # 存储点集
            self.objpoints.append(self.objp)
            self.imgpoints.append(corners2)

            # 在原图上绘制角点
            cv2.drawChessboardCorners(frame, self.CHECKERBOARD, corners2, ret_corners)

            # 保存带角点的图像
            img_name = os.path.join(self.img_dir, f'calib_{len(self.objpoints)}.jpg')
            cv2.imwrite(img_name, frame)
            self.info_label.config(text=f"已采集 {len(self.objpoints)} 张图像，保存至 {img_name}")
        else:
            self.info_label.config(text="未检测到完整棋盘格，请调整标定板角度/光照")

    def calibrate(self):
        """执行相机标定"""
        if len(self.objpoints) < 5:
            messagebox.showwarning("警告", "至少需要5张标定图像，当前仅采集了 {} 张".format(len(self.objpoints)))
            return

        # 获取图像尺寸（从最后一帧获取）
        ret, frame = self.cap.read()
        if not ret:
            messagebox.showerror("错误", "无法获取图像尺寸")
            return
        h, w = frame.shape[:2]

        # 调用 OpenCV 标定函数
        ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(
            self.objpoints, self.imgpoints, (w, h), None, None
        )

        if ret:
            self.camera_matrix = mtx.tolist()
            self.dist_coeffs = dist.tolist()
            # 计算重投影误差
            total_error = 0
            for i in range(len(self.objpoints)):
                imgpoints2, _ = cv2.projectPoints(self.objpoints[i], rvecs[i], tvecs[i], mtx, dist)
                error = cv2.norm(self.imgpoints[i], imgpoints2, cv2.NORM_L2) / len(imgpoints2)
                total_error += error
            mean_error = total_error / len(self.objpoints)
            self.info_label.config(text=f"标定完成！重投影误差: {mean_error:.3f} 像素")
            messagebox.showinfo("成功", f"标定完成，重投影误差: {mean_error:.3f} 像素")
        else:
            messagebox.showerror("错误", "标定失败！")

    def save_params(self):
        """将标定参数保存为 JSON 文件"""
        if self.camera_matrix is None:
            messagebox.showwarning("警告", "请先进行标定")
            return

        params = {
            'camera_matrix': self.camera_matrix,
            'dist_coeffs': self.dist_coeffs,
            'checkerboard_size': self.CHECKERBOARD,
            'square_size_mm': self.SQUARE_SIZE
        }

        filename = filedialog.asksaveasfilename(defaultextension=".json", filetypes=[("JSON files", "*.json")])
        if filename:
            with open(filename, 'w') as f:
                json.dump(params, f, indent=4)
            self.info_label.config(text=f"参数已保存至 {filename}")

    def load_params(self):
        """从 JSON 文件加载标定参数"""
        filename = filedialog.askopenfilename(filetypes=[("JSON files", "*.json")])
        if filename:
            with open(filename, 'r') as f:
                params = json.load(f)
            self.camera_matrix = params['camera_matrix']
            self.dist_coeffs = params['dist_coeffs']
            self.info_label.config(text=f"参数已从 {filename} 加载")
            messagebox.showinfo("成功", "参数加载完成")

    def __del__(self):
        if hasattr(self, 'cap') and self.cap.isOpened():
            self.cap.release()

if __name__ == "__main__":
    # 请根据你的虚拟摄像头设备修改 camera_id
    # 例如 /dev/video4 对应 camera_id = 4
    calibrator = CameraCalibrator(camera_id=4)