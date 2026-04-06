#pragma once
#include "../../data/CameraData/CameraData.hpp"
#include "../../data/GameData/GameData.hpp"
#include "../../data/MapData/MapData.hpp"
#include "../Camera/Camera.hpp"
#include "../Map/Map.hpp"
#include <Eigen/Dense>
#include <string>
#include <vector>
namespace Location {
class LocationDriver {
private:
    std::shared_ptr<Camera::CameraDriver> camera; // 使用智能指针管理CameraDriver实例
    CameraSpace::ArmorPose armorPose;

public:
    LocationDriver(
        std::shared_ptr<Data::CameraData::CameraDriver> camera,
        std::shared_ptr<Data::MapData::MapDriver> map)
        : camera(camera)
        , map(map) {
        std::cout << "LocationDriver initialized with Camera and Map." << std::endl;
    }
    ~LocationDriver();
    void locate();
};
} // namespace Location