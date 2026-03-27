#pragma once
#include <iostream>
#include <Eigen/Dense>

namespace CameraData
{
    struct CameraConfigParameters
    {
        int deviceID;   // 摄像头设备ID
        int width;      // 图像宽度
        int height;     // 图像高度
        int brightness; // 亮度
        int contrast;   // 对比度
        int saturation; // 饱和度
        int hue;        // 色调
        int exposure;   // 曝光
    };
    struct CameraInsideParameters // 摄像头内部参数
    {
        double focal_length;  // 焦距
        double sensor_width;  // 传感器宽度
        double sensor_height; // 传感器高度
    };
}
namespace CameraSpace
{
    struct CameraPhysicalPose // 摄像头物理位姿
    {
        Eigen::Vector3d position;       // 摄像头位置
        Eigen::Quaterniond orientation; // 摄像头朝向
    };
    struct ArmorPose
    {
      Eigen::Vector3d position; // 装甲板位置(x,y,0)  
    };
}
