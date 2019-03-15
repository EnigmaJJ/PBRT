#pragma once

#include <limits>

namespace PBRT
{
    template <typename T>
    class Vector2;

    template <typename T>
    class Vector3;

    template <typename T>
    class Point2;

    template <typename T>
    class Point3;

    template <typename T>
    class Normal3;

#ifdef PBRT_FLOAT_AS_DOUBLE
    typedef double Float;
#else
    typedef float Float;
#endif // PBRT_FLOAT_AS_DOUBLE

// 全局常量
#ifdef _MSC_VER
    #define Infinity std::numeric_limits<Float>::infinity()
#else
    static PBRT_CONSTEXPR Float Infinity = std::numeric_limits<Float>::infinity();
#endif
}
