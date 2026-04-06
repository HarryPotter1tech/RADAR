#include "../data/CameraData/CameraData.hpp"
#include "../data/GameData/Robomaster.hpp"
#include "../data/MapData/MapData.hpp"
#include "yaml-cpp/yaml.h"
#include <Eigen/Geometry>
#include <iostream>
#include <string>
#include <vector>

namespace YamlConfigs {
bool YamlLoad(
    std::shared_ptr<Data::CameraData::CameraConfigParameters> camera_config_parameters,
    std::shared_ptr<Data::MapData::MapConfigParameters> map_config_parameters,
    std::shared_ptr<Data::CameraData::CameraInsideParameters> camera_inside_parameters,
    std::shared_ptr<Data::CameraSpace::CameraPhysicalPose> camera_physical_pose,
    std::shared_ptr<Data::GameData::GameSide> game_side,
    std::shared_ptr<Data::GameData::GameState> game_state,
    std::shared_ptr<Data::GameData::GameVersion> game_version);
}
