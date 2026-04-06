#pragma once
#include "../../data/MapData/MapData.hpp"
#include "../../include/tiny_obj_loader.h"
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Map {
class Map {
private:
    std::shared_ptr<const Data::MapData::MapConfigParameters> Mapconfig_;
    tinyobj::attrib_t attrib_;
    std::vector<tinyobj::shape_t> shapes_;
    std::vector<tinyobj::material_t> materials_;
    std::string warn_;
    std::string err_;

public:
    explicit Map(std::shared_ptr<const Data::MapData::MapConfigParameters> cfg)
        : Mapconfig_(cfg) {};
    ~Map() = default;
    bool Mapload();
    std::vector<Eigen::Vector3d> Getvector() const;
    std::vector<Eigen::Matrix3d> GetTriangle() const;
    std::string GetMapFilePath() const { return Mapconfig_->obj_map_file_path; }
    std::string GetMapName() const { return Mapconfig_->map_name; }
};
} // namespace Map