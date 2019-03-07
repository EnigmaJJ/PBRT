#pragma once

#include "PBRT.h"
#include "glog/logging.h"

namespace PBRT
{
    template <typename T>
    inline bool isNaN(const T x)
    {
        return std::isnan(x);
    }

    template <typename T>
    class Vector2
    {
    public:
        Vector2(void)
        {
            x = y = 0;
        }

        Vector2(T x, T y)
            : x(x), y(y)
        {
            DCHECK(!HasNaNs());
        }

        bool HasNaNs(void) const
        {
            return isNaN(x) || isNaN(y);
        }

        Vector2<T> operator+(const Vector2<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Vector2<T>(x + v.x, y + v.y);
        }

        Vector2<T>& operator+=(const Vector2<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2<T> operator-(const Vector2<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Vector2<T>(x - v.x, y - v.y);
        }

        Vector2<T>& operator-=(const Vector2<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x -= v.x;
            y -= v.y;
            return *this;
        }

        template <typename U>
        Vector2<T> operator*(U s) const
        {
            DCHECK(!isNaN(s));
            return Vector2<T>(x * s, y * s);
        }

        template <typename U>
        Vector2<T>& operator*=(U s) const
        {
            DCHECK(!isNaN(s));
            x *= s;
            y *= s;
            return *this;
        }

        template <typename U>
        Vector2<T> operator/(U s) const
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            return Vector2<T>(x * inv, y * inv);
        }

        template <typename U>
        Vector2<T>& operator/(U s)
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            x *= inv;
            y *= inv;
            return *this;
        }

        Vector2<T> operator-()
        {
            return Vector2<T>(-x, -y);
        }

        T operator[](int i) const
        {
            DCHECK((i >= 0) && (i <= 1));

            if (0 == i) return x;
            return y;
        }

        T& operator[](int i)
        {
            DCHECK((i >= 0) && (i <= 1));

            if (0 == i) return x;
            return y;
        }

        Float LengthSquared() const
        {
            return (x * x + y * y);
        }

        Float Length() const
        {
            return std::sqrt(LengthSquared());
        }

        T x, y;
    };

    template <typename T>
    class Vector3
    {
    public:
        Vector3(void)
        {
            x = y = z = 0;
        }

        Vector3(T x, T y, T z)
            : x(x), y(y), z(z)
        {
            DCHECK(!HasNaNs());
        }

        bool HasNaNs(void) const
        {
            return isNaN(x) || isNaN(y) || isNaN(z);
        }

        Vector3 operator+(const Vector3<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Vector3<T>(x + v.x, y + v.y, z + v.z);
        }

        Vector3<T>& operator+=(const Vector3<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3<T> operator-(const Vector3<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Vector3<T>(x - v.x, y - v.y, z - v.z);
        }

        Vector3<T>& operator-=(const Vector3<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        template <typename U>
        Vector3<T> operator*(U s) const
        {
            return Vector3<T>(x * s, y * s, z * s);
        }

        template <typename U>
        Vector3<T>& operator*=(U s) const
        {
            DCHECK(!isNaN(s));
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        template <typename U>
        Vector3<T> operator/(U s) const
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            return Vector3<T>(x * inv, y * inv, z * inv);
        }

        template <typename U>
        Vector3<T>& operator/(U s)
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }

        Vector3<T> operator-()
        {
            return Vector3<T>(-x, -y, -z);
        }

        T operator[](int i) const
        {
            DCHECK((i >= 0) && (i <= 2));

            if (0 == i) return x;
            if (1 == i) return y;
            return z;
        }

        T &operator[](int i)
        {
            DCHECK((i >= 0) && (i <= 2));

            if (0 == i) return x;
            if (1 == i) return y;
            return z;
        }

        Float LengthSquared() const
        {
            return (x * x + y * y + z * z);
        }

        Float Length() const
        {
            return std::sqrt(LengthSquared());
        }

        T x, y, z;
    };

    typedef Vector2<Float> Vector2f;
    typedef Vector2<int>   Vector2i;
    typedef Vector3<Float> Vector3f;
    typedef Vector3<int>   Vector3i;

    // --------------------------------------------------------------------
    // Vector2 functions
    template <typename T, typename U>
    inline Vector2<T> operator*(U s, const Vector2<T> &v)
    {
        return v * s;
    }

    template <typename T>
    Vector2<T> Abs(const Vector2<T>& v)
    {
        return Vector2<T>(std::abs(v.x), std::abs(v.y));
    }

    template <typename T>
    inline T Dot(const Vector2<T> &v1, const Vector2<T> &v2)
    {
        return (v1.x * v2.x + v1.y * v2.y);
    }

    template <typename T>
    inline T AbsDot(const Vector2<T> &v1, const Vector2<T> &v2)
    {
        return std::abs(Dot(v1, v2));
    }

    template <typename T>
    inline Vector2<T> Normalize(const Vector2<T> &v)
    {
        return (v / v.Length());
    }

    // --------------------------------------------------------------------
    // Vector3 functions
    template <typename T, typename U>
    inline Vector3<T> operator*(U s, const Vector3<T> &v)
    {
        return v * s;
    }

    template <typename T>
    Vector3<T> Abs(const Vector3<T>& v)
    {
        return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
    }

    template <typename T>
    inline T Dot(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }

    template <typename T>
    inline T AbsDot(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return std::abs(Dot(v1, v2));
    }

    template <typename T>
    inline Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        // 避免单精度浮点情况下引起的误差错误
        double v1x = v1.x, v1y = v1.y, v1z = v1.z;
        double v2x = v2.x, v2y = v2.y, v2z = v2.z;

        return Vector3<T>(v1y * v2z - v1z * v2y,
                          v1z * v2x - v1x * v2z,
                          v1x * v2y - v1y * v2x);
    }

    template <typename T>
    inline Vector3<T> Normalize(const Vector3<T> &v)
    {
        return (v / v.Length());
    }

    template <typename T>
    T MinComponent(const Vector3<T> &v)
    {
        return std::fmin(v.x, std::fmin(v.y, v.z));
    }

    template <typename T>
    T MaxComponent(const Vector3<T> &v)
    {
        return std::fmax(v.x, std::fmax(v.y, v.z));
    }

    template <typename T>
    int MaxDimension(const Vector3<T> &v)
    {
        return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
    }
}
