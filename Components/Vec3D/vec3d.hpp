#ifndef VEC3D_HPP
#define VEC3D_HPP

class Vec3D
{
public:
    Vec3D(double xVal, double yVal, double zVal);
    Vec3D();
    ~Vec3D() = default;

    double getX() const;
    double getY() const;
    double getZ() const;

    Vec3D operator+(const Vec3D &other) const;
    Vec3D operator-(const Vec3D &other) const;
    Vec3D operator*(double scalar) const;
    Vec3D operator/(double scalar) const;
    bool operator==(const Vec3D &other) const;
    bool operator!=(const Vec3D &other) const;

private:
    double x, y, z;
};
#endif // VEC3D_HPP