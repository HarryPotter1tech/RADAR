#pragma once
#include "../../../data/UtilityData/Utility.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace Utility::AABB {
class AABB {
private:
    std::vector<Data::UtilityData::AABB::AABB> aabbs;
    std::vector<Eigen::Matrix3d> trangles_in;

public:
    AABB(const std::vector<Eigen::Matrix3d>& trangles_in)
        : trangles_in(trangles_in) {};
    ~AABB() = default;
    bool MIN_AABB_init();
    bool RAY_AABB_intersect();
    Eigen::Vector2d RAY_MASH_intersect();
};
} // namespace Utility::AABB