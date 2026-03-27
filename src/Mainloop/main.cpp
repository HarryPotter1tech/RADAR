#include <iostream>
#include <memory>
#include "../../config/config.hpp"
#include "../../src/Camera/Camera.hpp"
#include "../../src/Map/Map.hpp"
int main()
{
    std::cout << "RADAR-H start\n";
    std::shared_ptr<CameraData::CameraConfigParameters> camera_config_parameters = std::make_shared<CameraData::CameraConfigParameters>();
    std::shared_ptr<MapData::MapConfigParameters> map_config_parameters = std::make_shared<MapData::MapConfigParameters>();
    std::shared_ptr<CameraData::CameraInsideParameters> camera_inside_parameters = std::make_shared<CameraData::CameraInsideParameters>();
    std::shared_ptr<CameraSpace::CameraPhysicalPose> camera_physical_pose = std::make_shared<CameraSpace::CameraPhysicalPose>();
    std::shared_ptr<Game::GameSide> game_side = std::make_shared<Game::GameSide>();
    std::shared_ptr<Game::GameState> game_state = std::make_shared<Game::GameState>();
    if(!YamlConfigs::YamlLoad(
           camera_config_parameters,
           map_config_parameters,
           camera_inside_parameters,
           camera_physical_pose,
           game_side,
           game_state))
    {
        std::cerr << "Failed to load YAML configuration." << std::endl;
        return -1;
    }
    std::shared_ptr<const CameraData::CameraConfigParameters> const_camera_config_parameters = camera_config_parameters;
    std::shared_ptr<const MapData::MapConfigParameters> const_map_config_parameters = map_config_parameters;
    std::shared_ptr<const CameraData::CameraInsideParameters> const_camera_inside_parameters = camera_inside_parameters;
    std::shared_ptr<const CameraSpace::CameraPhysicalPose> const_camera_physical_pose = camera_physical_pose;
    std::shared_ptr<const Game::GameSide> const_game_side = game_side;
    std::cout << "YAML configuration loaded successfully." << std::endl;
    std::shared_ptr<Camera::CameraDriver> camera_driver = std::make_shared<Camera::CameraDriver>(camera_config_parameters);
    std::shared_ptr<Map::MapLoader> map = std::make_shared<Map::MapLoader>(map_config_parameters);
    if(!map->Mapload())
    {
        std::cerr << "Failed to load map." << std::endl;
        return -1;
    }
    return 0;
}