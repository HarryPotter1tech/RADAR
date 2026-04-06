#include "AABB.hpp"
namespace Utility::AABB {
bool AABB::MIN_AABB_init() {
    aabbs.reserve(trangles_in.size());
    for (size_t i = 0; i < trangles_in.size(); i++) {
        Data::UtilityData::AABB::AABB aabb;
        aabb.minPoint = trangles_in[i].colwise().minCoeff();
        aabb.maxPoint = trangles_in[i].colwise().maxCoeff();
        aabbs.push_back(aabb);
        std::cout << "AABB " << i << " minPoint: " << aabb.minPoint.transpose()
                  << " maxPoint: " << aabb.maxPoint.transpose() << std::endl;
    }
    return true;
}
} // namespace Utility::AABB
