#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../../data/Mapdata/Mapdata.hpp"
#include "../../include/OBJ_Loader.h"

namespace Map
{
    // Map 类：持有配置、OBJ 加载器和运行时网格数据
    class Map
    {
    private:
        std::shared_ptr<const MapData::MapConfigParameters> Mapconfig_; // 只读配置
        objl::Loader loader_;                                           // 私有 loader 实例

    public:
        // 接收只读配置（explicit 防止隐式转换）
        explicit Map(std::shared_ptr<const MapData::MapConfigParameters> cfg) {}
        ~Map() = default;
        std::vector<objl::Mesh> LoadMap();
    };
}