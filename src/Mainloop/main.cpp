#include <iostream>
#include <memory>
#include "../Map/Map.hpp"
#include "../../data/Mapdata/Mapdata.hpp"
int main()
{
    std::cout << "RADAR-H start\n";

    auto cfg_mut = std::make_shared<MapData::MapConfigParameters>();
    cfg_mut->mapFilePath = "/root/RADAR-H/data/Mapdata/map_obj/2026雷达站专用RMUC地图精简版.obj";
    cfg_mut->outputFilePath = "/root/RADAR-H/data/Mapdata/map_bin/2026RMUC_MAP.bin";

    std::shared_ptr<const MapData::MapConfigParameters> mapconfigs_ptr = cfg_mut;

    Map::Map loader(mapconfigs_ptr);
    std::vector<objl::Mesh> meshes = loader.LoadMap();
    return 0;
}