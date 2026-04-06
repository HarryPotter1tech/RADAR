#pragma once
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "../Camera/Camera.hpp"
#include "../Map/Map.hpp"
#include "../../data/CameraData/CameraData.hpp"
#include "../../data/MapData/MapData.hpp"
#include "../../data/GameData/GameData.hpp"
namespace Location
{
    class LocationDriver
    {
    private:
        std::shared_ptr<Camera::CameraDriver> camera; // 使用智能指针管理CameraDriver实例
        CameraSpace::ArmorPose armorPose;

    public:
        LocationDriver(std::shared_ptr<Data::CameraData::CameraDriver> camera, std::shared_ptr<Data::MapData::MapDriver> map) : camera(camera), map(map) {}
        {
            std::cout << "LocationDriver initialized with Camera and Map." << std::endl;
        };
        ~LocationDriver();
        void locate();
    };
}