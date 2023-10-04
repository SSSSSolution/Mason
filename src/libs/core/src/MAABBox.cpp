#include "core/MAABBox.h"

namespace mason {

MAABBox::MAABBox(const Vector3f &min, const Vector3f &max) : min(min), max(max) {}

Vector3f MAABBox::center() {
    return Vector3f((min.x + max.x) / 2.0f,
                    (min.y + max.y) / 2.0f,
                    (min.z + max.z) / 2.0f);
}

bool MAABBox::contains(const Vector3f &point) const {
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y &&
           point.z >= min.z && point.z <= max.z;
}

bool MAABBox::contains(const MAABBox &other) const {
    return contains(other.min) && contains(other.max);
}

bool MAABBox::intersects(const MAABBox &other) const {
    return (min.x <= other.max.x && max.x >= other.min.x) &&
           (min.y <= other.max.y && max.y >= other.min.y) &&
           (min.z <= other.max.z && max.z >= other.min.z);
}

std::string MAABBox::str() const {
    return "MAABBox(min: " + min.str() + ", max: " + max.str() + ")";
}

}
