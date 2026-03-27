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

    std::vector<float> Map::Getvector() const
    {
        std::vector<float> vertices;
        vertices.reserve(attrib_.vertices.size());
        for (float value : attrib_.vertices)
        {
            vertices.push_back(value);
        }
        return vertices;
    }
}