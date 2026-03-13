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
        std::shared_ptr<const CameraData::CameraConfigParameters> config; // 使用智能指针管理配置数据
        cv::VideoCapture cap;
        std::string videoPath;

    public:
        explicit CameraDriver(std::shared_ptr<const CameraData::CameraConfigParameters> config) : config(config)
        {
            std::cout << "CameraDriver initialized with config: " << std::endl;
        };
        CameraDriver(std::shared_ptr<const CameraData::CameraConfigParameters> config, const std::string &videoPath) : config(config), videoPath(videoPath)
        {
            std::cout << "CameraDriver initialized with config and video path: " << videoPath << std::endl;
        };
        ~CameraDriver();
        void setConfig();
        auto getVideoCapture();
        int getCameraWidth();
        int getCameraHeight();
    };
}