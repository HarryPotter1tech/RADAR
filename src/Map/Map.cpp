#define TINYOBJLOADER_IMPLEMENTATION
#include "Map.hpp"
namespace Map
{
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
    std::vector<Eigen::Matrix3d> Map::GetTriangle() const
    {
        // a shape contain a mash and mash contain a list of indices, indice
        // contain the vertex index, normal index and texture coordinate index
        // espcially, the list of indices contain triple elements, which represent
        // the three vertices of a triangle
        std::vector<Eigen::Matrix3d> Triangles;
        tinyobj::shape_t shape;
        size_t totalTriangles = 0;
        for (const auto &shape : shapes_)
            totalTriangles += shape.mesh.indices.size() / 3;
        Triangles.reserve(totalTriangles);
        for (size_t i = 0; i < shapes_.size(); i++)
        {
            for (size_t j = 0; j < shapes_[i].mesh.indices.size() / 3; j++)
            {
                Eigen::Vector3d x;
                Eigen::Vector3d y;
                Eigen::Vector3d z;
                int idx_v0 = shapes_[i].mesh.indices[3 * j + 0].vertex_index;
                int idx_v1 = shapes_[i].mesh.indices[3 * j + 1].vertex_index;
                int idx_v2 = shapes_[i].mesh.indices[3 * j + 2].vertex_index;
                x(0) = attrib_.vertices[3 * idx_v0 + 0];
                x(1) = attrib_.vertices[3 * idx_v0 + 1];
                x(2) = attrib_.vertices[3 * idx_v0 + 2];
                y(0) = attrib_.vertices[3 * idx_v1 + 0];
                y(1) = attrib_.vertices[3 * idx_v1 + 1];
                y(2) = attrib_.vertices[3 * idx_v1 + 2];
                z(0) = attrib_.vertices[3 * idx_v2 + 0];
                z(1) = attrib_.vertices[3 * idx_v2 + 1];
                z(2) = attrib_.vertices[3 * idx_v2 + 2];
                Eigen::Matrix3d triangle;
                triangle.row(0) = x.transpose();
                triangle.row(1) = y.transpose();
                triangle.row(2) = z.transpose();
                Triangles.push_back(triangle);
                std::cout << std::fixed << std::setprecision(3) << "Triangle " << j << ": " << std::endl;
                std::cout << "  (" << x(0) << ", " << x(1) << ", " << x(2) << ")" << std::endl;
                std::cout << "  (" << y(0) << ", " << y(1) << ", " << y(2) << ")" << std::endl;
                std::cout << "  (" << z(0) << ", " << z(1) << ", " << z(2) << ")" << std::endl;
            }
        }
        return Triangles;
    }
}