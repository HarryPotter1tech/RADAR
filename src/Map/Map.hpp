#pragma once
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>
#include <Eigen/Dense>
#include "../../data/Mapdata/Mapdata.hpp"
#include "../../include/tiny_obj_loader.h"

namespace Map
{
    // Map 类：持有配置、OBJ 加载器和运行时网格数据
    class Map
    {
    private:
        std::shared_ptr<const MapData::MapConfigParameters> Mapconfig_; // 只读配置
        tinyobj::attrib_t attrib_;
        std::vector<tinyobj::shape_t> shapes_;
        std::vector<tinyobj::material_t> materials_;
        std::string warn_;
        std::string err_;

    public:
        // 接收只读配置（explicit 防止隐式转换）
        explicit Map(std::shared_ptr<const MapData::MapConfigParameters> cfg);
        ~Map() = default;
        bool Mapload();
        std::vector<Eigen::Vector3d> Getvector() const;
        std::string GetMapFilePath() const { return Mapconfig_->obj_map_file_path; }
        std::string GetMapName() const { return Mapconfig_->map_name; }
    };
}