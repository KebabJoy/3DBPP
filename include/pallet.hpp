#ifndef PALLET_HPP
#define PALLET_HPP

#include <vector>
#include "box.hpp"

class Pallet {
public:
    Pallet(double weightCapacity, double length, double width, double height, double gravityCenterX, double gravityCenterY, double gravityCenterZ);

    double getWeightCapacity() const;
    double getLength() const;
    double getWidth() const;
    double getHeight() const;
    double getGravityCenterX() const;
    double getGravityCenterY() const;
    double getGravityCenterZ() const;

    void placeBox(Box& box, int x, int y, int z);
    bool canAddBox(const Box& box) const;
    double getTotalWeight() const;
    double getTotalGravityCenterX() const;
    double getTotalGravityCenterY() const;
    double getTotalGravityCenterZ() const;
    const std::vector<Box>& getBoxes() const;
    bool isBoxPlaceable(const Box& box, int x, int y, int z) const;
    double getCenterX() const;
    double getCenterY() const;
private:
    double weightCapacity;
    double length;
    double width;
    double height;
    double gravityCenterX;
    double gravityCenterY;
    double gravityCenterZ;
    std::vector<Box> boxes;

    void recalculateGravityCenter(const Box& box);
};

#endif /* PALLET_HPP */
