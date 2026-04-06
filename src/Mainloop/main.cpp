#include "../../config/config.hpp"
#include "../../src/Camera/Camera.hpp"
#include "../../src/Map/Map.hpp"
#include "../../src/Utility/Ray/AABB.hpp"
#include <iostream>
#include <memory>
int main() {
    std::cout << "RADAR-H start\n";
    std::shared_ptr<Data::CameraData::CameraConfigParameters> camera_config_parameters =
        std::make_shared<Data::CameraData::CameraConfigParameters>();
    std::shared_ptr<Data::MapData::MapConfigParameters> map_config_parameters =
        std::make_shared<Data::MapData::MapConfigParameters>();
    std::shared_ptr<Data::CameraData::CameraInsideParameters> camera_inside_parameters =
        std::make_shared<Data::CameraData::CameraInsideParameters>();
    std::shared_ptr<Data::CameraSpace::CameraPhysicalPose> camera_physical_pose =
        std::make_shared<Data::CameraSpace::CameraPhysicalPose>();
    std::shared_ptr<Data::GameData::GameSide> game_side =
        std::make_shared<Data::GameData::GameSide>();
    std::shared_ptr<Data::GameData::GameState> game_state =
        std::make_shared<Data::GameData::GameState>();
    std::shared_ptr<Data::GameData::GameVersion> game_version =
        std::make_shared<Data::GameData::GameVersion>();
    if (!YamlConfigs::YamlLoad(
            camera_config_parameters, map_config_parameters, camera_inside_parameters,
            camera_physical_pose, game_side, game_state, game_version)) {
        std::cerr << "Failed to load YAML configuration." << std::endl;
        return -1;
    }
    std::shared_ptr<const Data::CameraData::CameraConfigParameters> const_camera_config_parameters =
        camera_config_parameters;
    std::shared_ptr<const Data::MapData::MapConfigParameters> const_map_config_parameters =
        map_config_parameters;
    std::shared_ptr<const Data::CameraData::CameraInsideParameters> const_camera_inside_parameters =
        camera_inside_parameters;
    std::shared_ptr<const Data::CameraSpace::CameraPhysicalPose> const_camera_physical_pose =
        camera_physical_pose;
    std::shared_ptr<const Data::GameData::GameSide> const_game_side = game_side;
    std::shared_ptr<const Data::GameData::GameVersion> const_game_version = game_version;
    std::cout << "YAML configuration loaded successfully." << std::endl;
    if (const_game_version->version == "test") {
        std::cout << "Running in test mode." << std::endl;
        // std::shared_ptr<Camera::CameraDriver> camera_driver =
        // std::make_shared<Camera::CameraDriver>(camera_config_parameters,
        // "../data/test_video/test_video.mp4");
    } else if (const_game_version->version == "release") {
        std::cout << "Running in release mode." << std::endl;
        std::shared_ptr<Camera::CameraDriver> camera_driver =
            std::make_shared<Camera::CameraDriver>(camera_config_parameters);
    }
    std::shared_ptr<Camera::CameraDriver> camera_driver =
        std::make_shared<Camera::CameraDriver>(camera_config_parameters);
    std::shared_ptr<Map::Map> map = std::make_shared<Map::Map>(map_config_parameters);
    if (!map->Mapload()) {
        std::cerr << "Failed to load map." << std::endl;
        return -1;
    }
    std::vector<Eigen::Vector3d> vertices = map->Getvector();
    std::vector<Eigen::Matrix3d> triangles = map->GetTriangle();
    std::shared_ptr<Utility::AABB::AABB> aabb = std::make_shared<Utility::AABB::AABB>(triangles);
    if (!aabb->MIN_AABB_init()) {
        std::cerr << "Failed to initialize AABB." << std::endl;
        return -1;
    }
    return 0;
}