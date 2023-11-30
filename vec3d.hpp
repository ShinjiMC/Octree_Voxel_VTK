#ifndef VEC3D_HPP
#define VEC3D_HPP

class Vec3D
{
public:
    Vec3D(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}
    Vec3D() : x(0), y(0), z(0){};
    ~Vec3D() = default;

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    Vec3D operator+(const Vec3D &other) const
    {
        return Vec3D(x + other.x, y + other.y, z + other.z);
    }
    Vec3D operator-(const Vec3D &other) const
    {
        return Vec3D(x - other.x, y - other.y, z - other.z);
    }
    Vec3D operator*(double scalar) const
    {
        return Vec3D(x * scalar, y * scalar, z * scalar);
    }

    Vec3D operator/(double scalar) const
    {
        if (scalar != 0)
            return Vec3D(x / scalar, y / scalar, z / scalar);
    }
    bool operator==(const Vec3D &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3D &other) const
    {
        return !(*this == other);
    }

private:
    double x, y, z;
};
#endif // VEC3D_HPP