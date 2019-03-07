#pragma once

namespace PBRT
{
#ifdef PBRT_FLOAT_AS_DOUBLE
    typedef double Float;
#else
    typedef float Float;
#endif // PBRT_FLOAT_AS_DOUBLE
}
