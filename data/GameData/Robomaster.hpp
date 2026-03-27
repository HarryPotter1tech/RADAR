#pragma once
#include <iostream>
#include "CameraData/CameraData.hpp"
namespace Game
{
    enum GameTime
    {
        preparation,
        play,
        end        
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
