#include "Map.hpp"
namespace Map
{
    std::vector<objl::Mesh> Map::LoadMap()
    {
        bool isMapLoaded = loader_.LoadFile(Mapconfig_->mapFilePath);
        if (isMapLoaded)
        {
            auto meshes = std::move(loader_.LoadedMeshes);
            std::cout << "地图加载成功！" << std::endl;
            std::cout << "加载的网格数量: " << meshes.size() << std::endl;
            for (size_t i = 0; i < meshes.size(); ++i)
            {
                std::cout << "网格 " << i + 1 << ": " << meshes[i].Vertices.size() << " 顶点, "
                          << meshes[i].Indices.size() / 3 << " 三角形" << std::endl;
            }
            return meshes;
        }
        else
        {
            std::cerr << "地图加载失败！请检查路径和文件格式。" << std::endl;
            return std::vector<objl::Mesh>();
        }
    }
}
