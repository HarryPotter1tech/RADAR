#pragma once
#include "CameraData/CameraData.hpp"
#include <iostream>
#include <optional>
namespace Data::GameData {
struct GameState {
    std::string state; // "preparation", "in_progress", "ended"
};

struct GameSide {
    std::string enemy;
    std::string ally;
};
struct GameVersion {
    std::string version;
};

} // namespace Data::GameData
namespace Data::RobotParameters {
enum RobotType { hero, engineer, infantry_1, infantry_2, sentinel, drone, unknowntype };
enum RobotColor { red, blue, unknowncolor };
struct Robot {
    CameraSpace::ArmorPose armor;
    RobotType type;
    RobotColor color;
};

} // namespace Data::RobotParameters
