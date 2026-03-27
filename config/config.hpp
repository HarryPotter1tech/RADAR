#include "yaml-cpp/yaml.h"
#include "../data/GameData/Robomaster.hpp"
#include "../data/CameraData/CameraData.hpp"
#include "../data/Mapdata/Mapdata.hpp"
#include <Eigen/Geometry> 
#include <string>
#include <vector>
#include <iostream>

namespace YamlConfigs
{
     bool YamlLoad(std::shared_ptr<CameraData::CameraConfigParameters> camera_config_parameters,
                   std::shared_ptr<MapData::MapConfigParameters> map_config_parameters,
                   std::shared_ptr<CameraData::CameraInsideParameters> camera_inside_parameters,
                   std::shared_ptr<CameraSpace::CameraPhysicalPose> camera_physical_pose,
                   std::shared_ptr<Game::GameSide> game_side,
                   std::shared_ptr<Game::GameState> game_state
                   ,std::shared_ptr<Game::version> game_version);
}
