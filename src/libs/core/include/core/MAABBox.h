#ifndef MASON_CORE_BOUNDING_BOX_H
#define MASON_CORE_BOUNDING_BOX_H

#include <string>

#include "MVector.h"
#include "win-export/WinExport.h"

namespace mason {

struct MASON_CORE_API MAABBox {
    Vector3f min = Vector3f();
    Vector3f max = Vector3f();

    MAABBox() = default;
    MAABBox(const Vector3f &min, const Vector3f &max);

    Vector3f center();

    bool contains(const Vector3f &point) const;

    bool contains(const MAABBox &other) const;

    bool intersects(const MAABBox &other) const;

    std::string str() const;
};

}

#endif
