#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
namespace Data::UtilityData::AABB {
struct AABB {
    Eigen::Vector3d minPoint;
    Eigen::Vector3d maxPoint;
};
}
namespace Data::UtilityData::BVHNode {
struct BVHNode {
    Data::UtilityData::AABB::AABB aabb;
    int leftChild;
    int rightChild;
    int objectIndex;
};
} 
namespace Data::UtilityData::RayData {
struct Ray {
    Eigen::Vector3d origin;
    Eigen::Vector3d direction;
    double tMin;
    double tMax;
};
} 
