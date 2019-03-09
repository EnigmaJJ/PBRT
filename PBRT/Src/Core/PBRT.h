#pragma once

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

#ifdef PBRT_FLOAT_AS_DOUBLE
    typedef double Float;
#else
    typedef float Float;
#endif // PBRT_FLOAT_AS_DOUBLE
}
