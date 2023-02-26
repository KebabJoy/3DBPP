#pragma once

#include "Box.hpp"

Box::Box(double weight, double length, double width, double height, double gravityCenterX, double gravityCenterY, double gravityCenterZ)
: weight(weight), length(length), width(width), height(height), gravityCenterX(gravityCenterX), gravityCenterY(gravityCenterY), gravityCenterZ(gravityCenterZ) {}

double Box::getWeight() const {
    return weight;
}

double Box::getLength() const {
    return length;
}

double Box::getWidth() const {
    return width;
}

double Box::getHeight() const {
    return height;
}

double Box::xcg() const {
    return gravityCenterX;
}

double Box::ycg() const {
    return gravityCenterY;
}

double Box::zcg() const {
    return gravityCenterZ;
}

double Box::getX() const {
    return x;
}

double Box::getY() const {
    return y;
}

double Box::getZ() const {
    return z;
}

double Box::getVolume() const {
  return length * width * height;
}

void Box::setX(double x_) {
    this->x = x_;
}

void Box::setY(double y_) {
    this->y = y_;
}

void Box::setZ(double z_) {
    this->z = z_;
}