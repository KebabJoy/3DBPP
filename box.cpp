#pragma once

class Box {
public:
    Box(double weight, double width, double length, double height, double xcg, double ycg, double zcg)
    : weight_(weight), width_(width), length_(length), height_(height), xcg_(xcg), ycg_(ycg), zcg_(zcg) {}

    double getWeight() const { return weight_; }
    double getWidth() const { return width_; }
    double getLength() const { return length_; }
    double getHeight() const { return height_; }
    double xcg() const { return xcg_; }
    double ycg() const { return ycg_; }
    double zcg() const { return zcg_; }

private:
    double weight_;
    double width_;
    double length_;
    double height_;
    double xcg_;
    double ycg_;
    double zcg_;
};
