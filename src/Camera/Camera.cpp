#include "Camera.hpp"
#include <iostream>

using namespace Camera;

CameraDriver::CameraDriver(const CameraData::CameraConfigParameters &config) : config(config)
{
    std::cout << "CameraDriver initialized with config: " << std::endl;
}

CameraDriver::CameraDriver(const CameraData::CameraConfigParameters &config, const std::string &videoPath)
    : config(config), videoPath(videoPath)
{
    std::cout << "CameraDriver initialized with config" << std::endl;
    std::cout << "train video come from: " << videoPath << std::endl;
}

CameraDriver::~CameraDriver()
{
    std::cout << "CameraDriver destroyed" << std::endl;
    cap.release();
}

void CameraDriver::setConfig()
{
    cap.set(cv::CAP_PROP_BRIGHTNESS, config.brightness); // 亮度
    cap.set(cv::CAP_PROP_CONTRAST, config.contrast);     // 对比度
    cap.set(cv::CAP_PROP_SATURATION, config.saturation); // 饱和度
    cap.set(cv::CAP_PROP_HUE, config.hue);               // 色调
    cap.set(cv::CAP_PROP_EXPOSURE, config.exposure);     // 曝光
    std::cout << "Camera configuration updated." << std::endl;
}

cv::VideoCapture CameraDriver::getVideoCapture()
{
    if (!videoPath.empty())
    {
        cap.open(videoPath);
    }
    else
    {
        cap = cv::VideoCapture(config.deviceID);
    }
    return cap;
}
int CameraDriver::getCameraWidth()
{
    return static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
}
int CameraDriver::getCameraHeight()
{
    return static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}