import cv2
import numpy as np
import json
import sys

def load_calibration(json_path):
    """从 JSON 文件加载标定参数"""
    with open(json_path, 'r') as f:
        data = json.load(f)
    # 注意：JSON 中保存的是列表嵌套，需要转换为 numpy 数组
    K = np.array(data['camera_matrix'])
    D = np.array(data['dist_coeffs'])
    print(f"已加载标定参数: {json_path}")
    print("相机内参:\n", K)
    print("畸变系数:\n", D)
    return K, D

def pixel_to_ray_with_distortion(u, v, K, D):
    """考虑畸变的射线方向"""
    pts = np.array([[[u, v]]], dtype=np.float32)
    undistorted_norm = cv2.undistortPoints(pts, K, D, P=None)
    x_norm, y_norm = undistorted_norm[0, 0]
    ray = np.array([x_norm, y_norm, 1.0])
    ray = ray / np.linalg.norm(ray)
    return ray

def pixel_to_ray_without_distortion(u, v, K):
    """忽略畸变的射线方向"""
    fx, fy = K[0, 0], K[1, 1]
    cx, cy = K[0, 2], K[1, 2]
    x_norm = (u - cx) / fx
    y_norm = (v - cy) / fy
    ray = np.array([x_norm, y_norm, 1.0])
    ray = ray / np.linalg.norm(ray)
    return ray

def angle_between(v1, v2):
    """计算两个向量的夹角（度）"""
    cos = np.clip(np.dot(v1, v2), -1.0, 1.0)
    return np.degrees(np.arccos(cos))

if __name__ == "__main__":
    # 用法: python script.py your_calibration.json
    if len(sys.argv) > 1:
        json_file = sys.argv[1]
    else:
        json_file = "140nikon.json"   # 默认文件名
        print(f"未指定JSON文件，使用默认: {json_file}")

    try:
        K, D = load_calibration(json_file)
    except FileNotFoundError:
        print(f"错误: 文件 {json_file} 不存在")
        sys.exit(1)
    except Exception as e:
        print(f"加载失败: {e}")
        sys.exit(1)

    # 示例点击屏幕中心（可根据需要修改坐标）
    u, v = 400, 840
    ray_dist = pixel_to_ray_with_distortion(u, v, K, D)
    ray_raw = pixel_to_ray_without_distortion(u, v, K)
    angle = angle_between(ray_dist, ray_raw)

    print(f"\n像素坐标: ({u}, {v})")
    print("带畸变校正的射线方向:", ray_dist)
    print("无畸变校正的射线方向:", ray_raw)
    print(f"两种射线夹角: {angle:.6f} 度")