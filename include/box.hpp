#ifndef BOX_HPP
#define BOX_HPP

#include <algorithm>

class Box {
public:
    Box(double weight, double length, double width, double height, double gravityCenterX, double gravityCenterY, double gravityCenterZ);
    double getWeight() const;
    double getLength() const;
    double getWidth() const;
    double getHeight() const;
    double xcg() const;
    double ycg() const;
    double zcg() const;
    double getX() const;
    double getY() const;
    double getZ() const;
    double getVolume() const;

    void setX(double x_);
    void setY(double y_);
    void setZ(double z_);

    friend void swap(Box& lhs, Box& rhs);
private:
    double weight;
    double length;
    double width;
    double height;
    double gravityCenterX;
    double gravityCenterY;
    double gravityCenterZ;
    double x, y, z;
};

#endif // BOX_HPP
