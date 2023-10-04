#ifndef MASON_CORE_MVECTOR_H
#define MASON_CORE_MVECTOR_H

#include <string>

#include "win-export/WinExport.h"

namespace mason {

struct MASON_CORE_API Vector2f {
    Vector2f() = default;
    Vector2f(float x, float y) : x(x), y(y) {}

    float x = 0.0f;
    float y = 0.0f;
};

struct MASON_CORE_API Vector3f {
    Vector3f() = default;
    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    std::string str() const {
        return "Vector3f(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

};

struct MASON_CORE_API Vector4f {
    Vector4f() = default;
    Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

}


#endif
