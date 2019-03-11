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

    inline bool isNaN(const int x)
    {
        return false;
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
        Vector2<T>& operator/=(U s)
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
        Vector3<T>& operator/=(U s)
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

    template <typename T>
    class Point2
    {
    public:
        Point2(void)
        {
            x = y = 0;
        }

        Point2(T x, T y)
            : x(x), y(y)
        {
            DCHECK(!HasNaNs());
        }

        explicit Point2(const Point3<T> &p)
            : x(p.x), y(p.y)
        {
            DCHECK(!HasNaNs());
        }

        template <typename U>
        explicit Point2(const Point2<U> &p)
        {
            x = (T)p.x;
            y = (T)p.y;
            DCHECK(!HasNaNs());
        }

        template <typename U>
        explicit Point2(const Vector2<U> &v)
        {
            x = (T)v.x;
            y = (T)v.y;
            DCHECK(!HasNaNs());
        }

        template <typename U>
        explicit operator Vector2<U>() const
        {
            return Vector2<U>(x, y);
        }

        Point2<T> operator+(const Vector2<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Point2<T>(x + v.x, y + v.y);
        }

        Point2<T> &operator+=(const Vector2<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x += v.x;
            y += v.y;
            return *this;
        }

        Point2<T> operator+(const Point2<T> &p) const
        {
            DCHECK(!p.HasNaNs());
            return Point2<T>(x + p.x, y + p.y);
        }

        Point2<T> &operator+=(const Point2<T> &p)
        {
            DCHECK(!p.HasNaNs());
            x += p.x;
            y += p.y;
            return *this;
        }

        Point2<T> operator-(const Vector2<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Point2<T>(x - v.x, y - v.y);
        }

        Point2<T> &operator-=(const Vector2<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2<T> operator-(const Point2<T> &p) const
        {
            DCHECK(!p.HasNaNs());
            return Vector2<T>(x - p.x, y - p.y);
        }

        template <typename U>
        Point2<T> operator*(U s) const
        {
            DCHECK(!isNaN(s));
            return Point2<T>(x * s, y * s);
        }

        template <typename U>
        Point2<T>& operator*=(U s) const
        {
            DCHECK(!isNaN(s));
            x *= s;
            y *= s;
            return *this;
        }

        template <typename U>
        Point2<T> operator/(U s) const
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            return Point2<T>(x * inv, y * inv);
        }

        template <typename U>
        Point2<T>& operator/=(U s)
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            x *= inv;
            y *= inv;
            return *this;
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

        bool HasNaNs(void) const
        {
            return isNaN(x) || isNaN(y);
        }

        T x, y;
    };

    template <typename T>
    class Point3
    {
    public:
        Point3(void)
        {
            x = y = z = 0;
        }

        Point3(T x, T y, T z)
            : x(x), y(y), z(z)
        {
            DCHECK(!HasNaNs());
        }

        template <typename U>
        explicit Point3(const Point3<U> &p)
        {
            x = (T)p.x;
            y = (T)p.y;
            z = (T)p.z;
            DCHECK(!HasNaNs());
        }

        template <typename U>
        explicit Point3(const Vector3<U> &v)
        {
            x = (T)v.x;
            y = (T)v.y;
            z = (T)v.z;
            DCHECK(!HasNaNs());
        }

        template <typename U>
        explicit operator Vector3<U>() const
        {
            return Vector3<U>(x, y, z);
        }

        Point3<T> operator+(const Vector3<T> &v) const
        {
            return Point3<T>(x + v.x, y + v.y, z + v.z);
        }

        Point3<T> &operator+=(const Vector3<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Point3<T> operator+(const Point3<T> &p) const
        {
            DCHECK(!p.HasNaNs());
            return Point3<T>(x + p.x, y + p.y, z + p.z);
        }

        Point3<T> &operator+=(const Point3<T> &p)
        {
            DCHECK(!p.HasNaNs());
            x += p.x;
            y += p.y;
            z += p.z;
            return *this;
        }

        Point3<T> operator-(const Vector3<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Point3<T>(x - v.x, y - v.y, z - v.z);
        }

        Point3<T> &operator-=(const Vector3<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vector3<T> operator-(const Point3<T> &p) const
        {
            DCHECK(!p.HasNaNs());
            return Vector3<T>(x - p.x, y - p.y, z - p.y);
        }

        template <typename U>
        Point3<T> operator*(U s) const
        {
            DCHECK(!isNaN(s));
            return Point3<T>(x * s, y * s, z * s);
        }

        template <typename U>
        Point3<T>& operator*=(U s) const
        {
            DCHECK(!isNaN(s));
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        template <typename U>
        Point3<T> operator/(U s) const
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            return Point3<T>(x * inv, y * inv, z * inv);
        }

        template <typename U>
        Point3<T>& operator/=(U s)
        {
            CHECK_NE(0, s);
            Float inv = (Float)1 / s;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
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

        bool HasNaNs(void) const
        {
            return isNaN(x) || isNaN(y) || isNaN(z);
        }

        T x, y, z;
    };

    typedef Point2<Float> Point2f;
    typedef Point2<int>   Point2i;
    typedef Point3<Float> Point3f;
    typedef Point3<int>   Point3i;

    // --------------------------------------------------------------------
    // Vector2 functions
    template <typename T, typename U>
    inline Vector2<T> operator*(U s, const Vector2<T> &v)
    {
        DCHECK(!isNaN(s));
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

    template <typename T>
    Vector2<T> Min(const Vector2<T> &v1, const Vector2<T> &v2)
    {
        return Vector2<T>(std::fmin(v1.x, v2.x), std::fmin(v1.y, v2.y));
    }

    template <typename T>
    Vector2<T> Max(const Vector2<T> &v1, const Vector2<T> &v2)
    {
        return Vector2<T>(std::fmax(v1.x, v2.x), std::fmax(v1.y, v2.y));
    }

    // --------------------------------------------------------------------
    // Vector3 functions
    template <typename T, typename U>
    inline Vector3<T> operator*(U s, const Vector3<T> &v)
    {
        DCHECK(!isNaN(s));
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

        return Vector3<T>((T)(v1y * v2z - v1z * v2y),
                          (T)(v1z * v2x - v1x * v2z),
                          (T)(v1x * v2y - v1y * v2x));
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

    template <typename T>
    Vector3<T> Min(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return Vector3<T>(std::fmin(v1.x, v2.x), std::fmin(v1.y, v2.y), std::fmin(v1.z, v2.z));
    }

    template <typename T>
    Vector3<T> Max(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return Vector3<T>(std::fmax(v1.x, v2.x), std::fmax(v1.y, v2.y), std::fmax(v1.z, v2.z));
    }

    template <typename T>
    Vector3<T> Permute(const Vector3<T> &v, int xIndex, int yIndex, int zIndex)
    {
        return Vector3<T>(v[xIndex], v[yIndex], v[zIndex]);
    }

    // 通过单个向量构建坐标系
    // @remarks: v1应该是单位向量
    template <typename T>
    inline void CoordinateSystem(const Vector3<T> &v1, Vector3<T> *v2, Vector3<T> *v3)
    {
        // 把较小的分量置为0，可以防止出现(0, 0, 0)向量的情况
        if (std::abs(v1.x) > std::abs(v1.y))
        {
            *v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
        }
        else
        {
            *v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
        }

        *v3 = Cross(v1, *v2);
    }

    // --------------------------------------------------------------------
    // Point2 functions
    template <typename T, typename U>
    inline Point2<T> operator*(U s, const Point2<T> &p)
    {
        DCHECK(!isNaN(s));
        return p * s;
    }

    template <typename T>
    inline Float Distance(const Point2<T> &p1, const Point2<T> &p2)
    {
        return (p1 - p2).Length();
    }

    template <typename T>
    inline Float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2)
    {
        return (p1 - p2).LengthSquared();
    }

    template <typename T>
    Point2<T> Lerp(Float t, const Point2<T> &p1, const Point2<T> &p2)
    {
        return ((1 - t) * p1) + (t * p2);
    }

    template <typename T>
    Point2<T> Min(const Point2<T> &p1, const Point2<T> &p2)
    {
        return Point2<T>(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y));
    }

    template <typename T>
    Point2<T> Max(const Point2<T> &p1, const Point2<T> &p2)
    {
        return Point2<T>(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y));
    }

    template <typename T>
    Point2<T> Floor(const Point2<T> &p)
    {
        return Point2<T>(std::floor(p.x), std::floor(p.y));
    }

    template <typename T>
    Point2<T> Ceil(const Point2<T> &p)
    {
        return Point2<T>(std::ceil(p.x), std::ceil(p.y));
    }

    template <typename T>
    Point2<T> Abs(const Point2<T> &p)
    {
        return Point2<T>(std::abs(p.x), std::abs(p.y));
    }

    // --------------------------------------------------------------------
    // Point3 functions
    template <typename T, typename U>
    inline Point3<T> operator*(U s, const Point3<T> &p)
    {
        DCHECK(!isNaN(s));
        return p * s;
    }

    template <typename T>
    inline Float Distance(const Point3<T> &p1, const Point3<T> &p2)
    {
        return (p1 - p2).Length();
    }

    template <typename T>
    inline Float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2)
    {
        return (p1 - p2).LengthSquared();
    }

    template <typename T>
    Point3<T> Lerp(Float t, const Point3<T> &p1, const Point3<T> &p2)
    {
        return ((1 - t) * p1) + (t * p2);
    }

    template <typename T>
    Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2)
    {
        return Point3<T>(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y), std::fmin(p1.z, p2.z));
    }

    template <typename T>
    Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2)
    {
        return Point3<T>(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y), std::fmax(p1.z, p2.z));
    }

    template <typename T>
    Point3<T> Floor(const Point3<T> &p)
    {
        return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
    }

    template <typename T>
    Point3<T> Ceil(const Point3<T> &p)
    {
        return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
    }

    template <typename T>
    Point3<T> Abs(const Point3<T> &p)
    {
        return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
    }

    template <typename T>
    Point3<T> Permute(const Point3<T> &p, int xIndex, int yIndex, int zIndex)
    {
        return Point3<T>(p[xIndex], p[yIndex], p[zIndex]);
    }
}
