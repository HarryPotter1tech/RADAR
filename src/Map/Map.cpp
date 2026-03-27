#define TINYOBJLOADER_IMPLEMENTATION
#include "Map.hpp"
namespace Map
{
    Map::Map(std::shared_ptr<const MapData::MapConfigParameters> cfg)
        : Mapconfig_(std::move(cfg))
    {
    }

    bool Map::Mapload()
    {
        if (!Mapconfig_)
        {
            std::cerr << "Map configuration is not available." << std::endl;
            return false;
        }

        warn_.clear();
        err_.clear();
        const bool loaded = tinyobj::LoadObj(
            &attrib_,
            &shapes_,
            &materials_,
            &warn_,
            &err_,
            Mapconfig_->obj_map_file_path.c_str(),
            nullptr,
            true,
            false);

        if (!warn_.empty())
        {
            std::cerr << "OBJ load warning: " << warn_ << std::endl;
        }

        if (!loaded)
        {
            std::cerr << "Failed to load OBJ file: " << err_ << std::endl;
            return false;
        }

        std::cout << "Successfully loaded OBJ file: " << Mapconfig_->obj_map_file_path << std::endl;
        return true;
    }

    std::vector<Eigen::Vector3d> Map::Getvector() const
    {
        std::vector<Eigen::Vector3d> Vertices;
        Vertices.reserve(attrib_.vertices.size() / 3);
        for (size_t i = 0; i < attrib_.vertices.size(); i += 3)
        {
            double x = attrib_.vertices[i];
            double y = attrib_.vertices[i + 1];
            double z = attrib_.vertices[i + 2];
            Vertices.emplace_back(x, y, z);
            std::cout << std::fixed << std::setprecision(3) << "Vertex " << i / 3 << ": (" << x << ", " << y << ", " << z << ")" << std::endl;
        }
        return Vertices;
    }
}