#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include "../../data/CameraData/CameraData.hpp"

namespace Camera
{
    class CameraDriver
    {
    private:
        CameraData::CameraConfigParameters config;
        cv::VideoCapture cap;
        std::string videoPath;

    public:
        CameraDriver(const CameraData::CameraConfigParameters &config); // 使用 const 引用
        CameraDriver(const CameraData::CameraConfigParameters &config, const std::string &videoPath);
        ~CameraDriver();
        void setConfig();
        cv::VideoCapture getVideoCapture();
        int getCameraWidth();
        int getCameraHeight();
    };
}