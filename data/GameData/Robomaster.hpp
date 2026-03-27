#pragma once
#include <iostream>
#include <optional>
#include "CameraData/CameraData.hpp"
namespace Game
{
    struct  GameState
    {
        std::string state; // "preparation", "in_progress", "ended"
    };
    
    struct GameSide
    {
        std::string enemy;
        std::string ally;
    };
}
namespace RobotParameters
{
    enum RobotType
    {
        hero,
        engineer,
        infantry_1,
        infantry_2,
        sentinel,
        drone,
        unknowntype
    };
    enum RobotColor
    {
        red,
        blue,
        unknowncolor
    };
    struct Robot
    {
        CameraSpace::ArmorPose armor;
        RobotType type;
        RobotColor color;
    };

} 
