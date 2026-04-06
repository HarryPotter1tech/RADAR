#pragma once
#include "../../data/CameraData/CameraData.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

namespace Camera {
class CameraDriver {
private:
    std::shared_ptr<const Data::CameraData::CameraConfigParameters>
        config; // 使用智能指针管理配置数据
    cv::VideoCapture cap;
    std::string videoPath;

public:
    explicit CameraDriver(std::shared_ptr<const Data::CameraData::CameraConfigParameters> config)
        : config(config) {
        std::cout << "CameraDriver initialized with config: " << std::endl;
    };
    CameraDriver(
        std::shared_ptr<const Data::CameraData::CameraConfigParameters> config,
        const std::string& videoPath)
        : config(config)
        , videoPath(videoPath) {
        std::cout << "CameraDriver initialized with config and video path: " << videoPath
                  << std::endl;
    };
    ~CameraDriver();
    void setConfig();
    auto getVideoCapture();
    int getCameraWidth();
    int getCameraHeight();
};
} // namespace Camera