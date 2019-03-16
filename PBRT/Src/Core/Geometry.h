#pragma once

#include "PBRT.h"
#include "Medium.h"
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

        template <typename T>
        explicit Vector3(const Normal3<T> &n)
            : x(n.x), y(n.y), z(n.z)
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

        Point2(const Point2<T> &p)
        {
            DCHECK(!p.HasNaNs());
            x = p.x;
            y = p.y;
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

        Point3(const Point3<T> &p)
        {
            DCHECK(!p.HasNaNs());
            x = p.x;
            y = p.y;
            z = p.z;
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

    template <typename T>
    class Normal3
    {
    public:
        Normal3(void)
        {
            x = y = z = 0;
        }

        Normal3(T x, T y, T z)
            : x(x), y(y), z(z)
        {
            DCHECK(!HasNaNs());
        }

        template <typename T>
        explicit Normal3(const Vector3<T> &v)
            : x(v.x), y(v.y), z(v.z)
        {
            DCHECK(!HasNaNs());
        }

        Normal3<T> operator-(void) const
        {
            return Normal3<T>(-x, -y, -z);
        }

        bool HasNaNs(void) const
        {
            return isNaN(x) || isNaN(y) || isNaN(z);
        }

        T x, y, z;
    };

    class Ray
    {
    public:
        Ray()
            : tMax(Infinity), time(0.0f), medium(nullptr)
        {}

        Ray(const Point3f &origin
          , const Vector3f &dir
          , Float tMax = Infinity
          , Float time = 0.0f
          , const Medium *medium = nullptr)
            : origin(origin), dir(dir), tMax(tMax), time(time), medium(medium)
        {}

        Point3f operator()(Float t) const
        {
            return (origin + (dir * t));
        }

        Point3f origin;
        Vector3f dir;
        mutable Float tMax;
        Float time;
        const Medium *medium;
    };

    class RayDifferential : public Ray
    {
    public:
        RayDifferential()
        {
            hasDifferentials = false;
        }

        RayDifferential(const Point3f &origin
                      , const Vector3f &dir
                      , Float tMax = Infinity
                      , Float time = 0.0f
                      , const Medium *medium = nullptr)
            : Ray(origin, dir, tMax, time, medium)
        {
            hasDifferentials = false;
        }

        RayDifferential(const Ray &ray)
            : Ray(ray)
        {
            hasDifferentials = false;
        }

        void ScaleDifferentials(Float s)
        {
            rxOrigin = origin + ((rxOrigin - origin) * s);
            ryOrigin = origin + ((ryOrigin - origin) * s);
            rxDir = rxDir + ((rxDir - dir) * s);
            ryDir = ryDir + ((ryDir - dir) * s);
        }

        bool hasDifferentials;
        Point3f rxOrigin, ryOrigin;
        Vector3f rxDir, ryDir;
    };

    template <typename T>
    class Bounds2
    {
    public:
        Bounds2()
        {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            minPoint = Point2<T>(maxNum, maxNum);
            maxPoint = Point2<T>(minNum, minNum);
        }

        Bounds2(const Point2<T> &p)
            : minPoint(p), maxPoint(p)
        {}

        Bounds2(const Point2<T> &p1, const Point2<T> &p2)
            : minPoint(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y))
            , maxPoint(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y))
        {}

        Point2<T> &operator[](int i);
        const Point2<T> &operator[](int i) const;

        Point2<T> Corner(int corner) const
        {
            return Point2<T>((*this)[corner & 1].x, (*this)[(corner & 2) ? 1 : 0].y);
        }

        Vector2<T> Diagonal() const
        {
            return (maxPoint - minPoint);
        }

        int MaximumExtent() const
        {
            Vector2<T> diagonal = Diagonal();
            return ((diagonal.x > diagonal.y) ? 0 : 1);
        }

        Point2<T> Lerp(const Point2f &t) const
        {
            return Point2f(::Lerp(t.x, minPoint.x, maxPoint.x), ::Lerp(t.y, minPoint.y, maxPoint.y));
        }

        Point2<T> minPoint, maxPoint;
    };

    template <typename T>
    class Bounds3
    {
    public:
        Bounds3()
        {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            minPoint = Point3<T>(maxNum, maxNum, maxNum);
            maxPoint = Point3<T>(minNum, minNum, minNum);
        }

        Bounds3(const Point3<T> &p)
            : minPoint(p), maxPoint(p)
        {}

        Bounds3(const Point3<T> &p1, const Point3<T> &p2)
            : minPoint(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y), std::fmin(p1.z, p2.z))
            , maxPoint(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y), std::fmax(p1.z, p2.z))
        {}

        Point3<T> &operator[](int i);
        const Point3<T> &operator[](int i) const;

        Point3<T> Corner(int corner) const
        {
            return Point3<T>((*this)[corner & 1].x
                           , (*this)[(corner & 2) ? 1 : 0].y
                           , (*this)[(corner & 4) ? 1 : 0].z);
        }

        Vector3<T> Diagonal() const
        {
            return (maxPoint - minPoint);
        }

        T SurfaceArea() const
        {
            Vector3<T> diagonal = Diagonal();
            return (2 * ((diagonal.x * diagonal.y) + (diagonal.y * diagonal.z) + (diagonal.x * diagonal.z)));
        }

        T Volume() const
        {
            Vector3<T> diagonal = Diagonal();
            return (diagonal.x * diagonal.y * diagonal.z);
        }

        int MaximumExtent() const
        {
            Vector3<T> diagonal = Diagonal();
            if ((diagonal.x > diagonal.y) && (diagonal.x > diagonal.z))
            {
                return 0;
            }
            else if (diagonal.y > diagonal.z)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }

        Point3<T> Lerp(const Point3f &t) const
        {
            return Point3f(::Lerp(t.x, minPoint.x, maxPoint.x)
                         , ::Lerp(t.y, minPoint.y, maxPoint.y)
                         , ::Lerp(t.z, minPoint.z, maxPoint.z));
        }

        Point3<T> minPoint, maxPoint;
    };

    typedef Bounds2<Float> Bounds2f;
    typedef Bounds2<int>   Bounds2i;
    typedef Bounds3<Float> Bounds3f;
    typedef Bounds3<int>   Bounds3i;

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

    // --------------------------------------------------------------------
    // Normal3 functions
    template <typename T>
    Float Dot(const Normal3<T> &n, const Vector3<T> &v)
    {
        return (n.x * v.x + n.y * v.y + n.z * v.z);
    }

    template <typename T>
    Float Dot(const Vector3<T> &v, const Normal3<T> &n)
    {
        return (v.x * n.x + v.y * n.y + v.z * n.z);
    }

    template <typename T>
    Float Dot(const Normal3<T> &n1, const Normal3<T> &n2)
    {
        return (n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
    }

    template <typename T>
    Float AbsDot(const Normal3<T> &n, const Vector3<T> &v)
    {
        return std::abs(n.x * v.x + n.y * v.y + n.z * v.z);
    }

    template <typename T>
    Float AbsDot(const Vector3<T> &v, const Normal3<T> &n)
    {
        return std::abs(v.x * n.x + v.y * n.y + v.z * n.z);
    }

    template <typename T>
    Float AbsDot(const Normal3<T> &n1, const Normal3<T> &n2)
    {
        return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
    }

    template <typename T>
    inline Normal3<T> FaceForward(const Normal3<T> &n, const Vector3<T> &v)
    {
        return (Dot(n, v) < 0.0f) ? -n : n;
    }

    template <typename T>
    inline Normal3<T> FaceForward(const Normal3<T> &n1, const Normal3<T> &n2)
    {
        return (Dot(n1, n2) < 0.0f) ? -n1 : n1;
    }

    template <typename T>
    inline Vector3<T> FaceForward(const Vector3<T> &v, const Normal3<T> &n)
    {
        return (Dot(v, n) < 0.0f) ? -v : v;
    }

    template <typename T>
    inline Vector3<T> FaceForward(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return (Dot(v1, v2) < 0.0f) ? -v1 : v1;
    }

    // --------------------------------------------------------------------
    // Bound2 functions
    template <typename T>
    inline Point2<T> &Bounds2<T>::operator[](int i)
    {
        DCHECK((0 == i) || (1 == i));
        return (0 == i) ? minPoint : maxPoint;
    }

    template <typename T>
    inline const Point2<T> &Bounds2<T>::operator[](int i) const
    {
        DCHECK((0 == i) || (1 == i));
        return (0 == i) ? minPoint : maxPoint;
    }

    template <typename T>
    Bounds2<T> Union(const Bounds2<T> &b, const Point2<T> &p)
    {
        return Bounds2<T>(Point2<T>(std::fmin(b.minPoint.x, p.x)
                                  , std::fmin(b.minPoint.y, p.y))
                        , Point2<T>(std::fmax(b.maxPoint.x, p.x)
                                  , std::fmax(b.maxPoint.y, p.y)));
    }

    template <typename T>
    Bounds2<T> Union(const Bounds2<T> &b1, const Bounds2<T> &b2)
    {
        return Bounds2<T>(Point2<T>(std::fmin(b1.minPoint.x, b2.minPoint.x)
                                  , std::fmin(b1.minPoint.y, b2.minPoint.y))
                        , Point2<T>(std::fmax(b1.maxPoint.x, b2.maxPoint.x)
                                  , std::fmax(b1.maxPoint.y, b2.maxPoint.y)));
    }

    template <typename T>
    Bounds2<T> Intersect(const Bounds2<T> &b1, const Bounds2<T> &b2)
    {
        return Bounds2<T>(Point2<T>(std::fmax(b1.minPoint.x, b2.minPoint.x)
                                  , std::fmax(b1.minPoint.y, b2.minPoint.y))
                        , Point2<T>(std::fmin(b1.maxPoint.x, b2.maxPoint.x)
                                  , std::fmin(b1.maxPoint.y, b2.maxPoint.y)));
    }

    template <typename T>
    bool Overlaps(const Bounds2<T> &b1, const Bounds2<T> &b2)
    {
        bool x = (b1.maxPoint.x >= b2.minPoint.x) && (b1.minPoint.x <= b2.maxPoint.x);
        bool y = (b1.maxPoint.y >= b2.minPoint.y) && (b1.minPoint.y <= b2.maxPoint.y);
        return (x && y);
    }

    template <typename T>
    bool Inside(const Point2<T> &p, const Bounds2<T> &b)
    {
        return (p.x >= b.minPoint.x) && (p.x <= b.maxPoint.x)
            && (p.y >= b.minPoint.y) && (p.y <= b.maxPoint.y);
    }

    template <typename T>
    bool InsideExclusive(const Point2<T> &p, const Bounds2<T> &b)
    {
        return (p.x >= b.minPoint.x) && (p.x < b.maxPoint.x)
            && (p.y >= b.minPoint.y) && (p.y < b.maxPoint.y);
    }

    template <typename T, typename U>
    inline Bounds2<T> Expand(const Bounds2<T> &b, U delta)
    {
        return Bounds2<T>(b.minPoint - Vector2<U>(delta, delta)
                        , b.maxPoint + Vector2<U>(delta, delta));
    }

    // --------------------------------------------------------------------
    // Bound3 functions
    template <typename T>
    inline Point3<T> &Bounds3<T>::operator[](int i)
    {
        DCHECK((0 == i) || (1 == i));
        return (0 == i) ? minPoint : maxPoint;
    }

    template <typename T>
    inline const Point3<T> &Bounds3<T>::operator[](int i) const
    {
        DCHECK((0 == i) || (1 == i));
        return (0 == i) ? minPoint : maxPoint;
    }

    template <typename T>
    Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p)
    {
        return Bounds3<T>(Point3<T>(std::fmin(b.minPoint.x, p.x)
                                  , std::fmin(b.minPoint.y, p.y)
                                  , std::fmin(b.minPoint.z, p.z))
                        , Point3<T>(std::fmax(b.maxPoint.x, p.x)
                                  , std::fmax(b.maxPoint.y, p.y)
                                  , std::fmax(b.maxPoint.z, p.z)));
    }

    template <typename T>
    Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T> &b2)
    {
        return Bounds3<T>(Point3<T>(std::fmin(b1.minPoint.x, b2.minPoint.x)
                                  , std::fmin(b1.minPoint.y, b2.minPoint.y)
                                  , std::fmin(b1.minPoint.z, b2.minPoint.z))
                        , Point3<T>(std::fmax(b1.maxPoint.x, b2.maxPoint.x)
                                  , std::fmax(b1.maxPoint.y, b2.maxPoint.y)
                                  , std::fmax(b1.maxPoint.z, b2.maxPoint.z)));
    }

    template <typename T>
    Bounds3<T> Intersect(const Bounds3<T> &b1, const Bounds3<T> &b2)
    {
        return Bounds3<T>(Point3<T>(std::fmax(b1.minPoint.x, b2.minPoint.x)
                                  , std::fmax(b1.minPoint.y, b2.minPoint.y)
                                  , std::fmax(b1.minPoint.z, b2.minPoint.z))
                        , Point3<T>(std::fmin(b1.maxPoint.x, b2.maxPoint.x)
                                  , std::fmin(b1.maxPoint.y, b2.maxPoint.y)
                                  , std::fmin(b1.maxPoint.z, b2.maxPoint.z)));
    }

    template <typename T>
    bool Overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2)
    {
        bool x = (b1.maxPoint.x >= b2.minPoint.x) && (b1.minPoint.x <= b2.maxPoint.x);
        bool y = (b1.maxPoint.y >= b2.minPoint.y) && (b1.minPoint.y <= b2.maxPoint.y);
        bool z = (b1.maxPoint.z >= b2.minPoint.z) && (b1.minPoint.z <= b2.maxPoint.z);
        return (x && y && z);
    }

    template <typename T>
    bool Inside(const Point3<T> &p, const Bounds3<T> &b)
    {
        return (p.x >= b.minPoint.x) && (p.x <= b.maxPoint.x)
            && (p.y >= b.minPoint.y) && (p.y <= b.maxPoint.y)
            && (p.z >= b.minPoint.z) && (p.z <= b.maxPoint.z);
    }

    template <typename T>
    bool InsideExclusive(const Point3<T> &p, const Bounds3<T> &b)
    {
        return (p.x >= b.minPoint.x) && (p.x < b.maxPoint.x)
            && (p.y >= b.minPoint.y) && (p.y < b.maxPoint.y)
            && (p.z >= b.minPoint.z) && (p.z < b.maxPoint.z);
    }

    template <typename T, typename U>
    inline Bounds3<T> Expand(const Bounds3<T> &b, U delta)
    {
        return Bounds3<T>(b.minPoint - Vector3<U>(delta, delta, delta)
                        , b.maxPoint + Vector3<U>(delta, delta, delta));
    }
}
