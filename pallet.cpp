#pragma once

#include <vector>
#include "box.cpp"

class Pallet {
public:
    Pallet(double weightCapacity, double length, double width, double height, double gravityCenterX, double gravityCenterY, double gravityCenterZ)
    : weightCapacity(weightCapacity), length(length), width(width), height(height), gravityCenterX(gravityCenterX), gravityCenterY(gravityCenterY), gravityCenterZ(gravityCenterZ) {}

    double getWeightCapacity() const { return weightCapacity; }
    double getLength() const { return length; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double xcg() const { return gravityCenterX; }
    double ycg() const { return gravityCenterY; }
    double zcg() const { return gravityCenterZ; }

    void addBox(const Box& box) {
        boxes.push_back(box);
        recalculateGravityCenter(box);
    }

    bool canAddBox(const Box& box) const {
        double newWeight = getTotalWeight() + box.getWeight();
        if (newWeight > weightCapacity) {
            return false;
        }

        double newGCX = (getTotalGravityCenterX() * getTotalWeight() + box.xcg() * box.getWeight()) / newWeight;
        double newGCY = (getTotalGravityCenterY() * getTotalWeight() + box.ycg() * box.getWeight()) / newWeight;
        double newGCZ = (getTotalGravityCenterZ() * getTotalWeight() + box.zcg() * box.getWeight()) / newWeight;

        double halfLength = box.getLength() / 2.0;
        double halfWidth = box.getWidth() / 2.0;
        double halfHeight = box.getHeight() / 2.0;

        if (newGCX - halfLength < -length / 2.0 || newGCX + halfLength > length / 2.0) {
            return false;
        }
        if (newGCY - halfWidth < -width / 2.0 || newGCY + halfWidth > width / 2.0) {
            return false;
        }
        if (newGCZ - halfHeight < -height / 2.0 || newGCZ + halfHeight > height / 2.0) {
            return false;
        }

        return true;
    }

    double getTotalWeight() const {
        double totalWeight = 0.0;
        for (const auto& box : boxes) {
            totalWeight += box.getWeight();
        }
        return totalWeight;
    }

    double getTotalGravityCenterX() const {
        double totalGCX = 0.0;
        for (const auto& box : boxes) {
            totalGCX += box.xcg() * box.getWeight();
        }
        return totalGCX / getTotalWeight();
    }

    double getTotalGravityCenterY() const {
        double totalGCY = 0.0;
        for (const auto& box : boxes) {
            totalGCY += box.ycg() * box.getWeight();
        }
        return totalGCY / getTotalWeight();
    }

    double getTotalGravityCenterZ() const {
        double totalGCZ = 0.0;
        for (const auto& box : boxes) {
            totalGCZ += box.zcg() * box.getWeight();
        }
        return totalGCZ / getTotalWeight();
    }

    const std::vector<Box>& getBoxes() const {
        return boxes;
    }

private:
    double weightCapacity; // weight capacity
    double length, width, height; // dimensions
    double gravityCenterX, gravityCenterY, gravityCenterZ; // center of gravity
    std::vector<Box> boxes;

    void recalculateGravityCenter(const Box& box) {
        double totalWeight = getTotalWeight();
        double totalGCX = getTotalGravityCenterX() * totalWeight;
        double totalGCY = getTotalGravityCenterY() * totalWeight;
        double totalGCZ = getTotalGravityCenterZ() * totalWeight;
        double boxGCX = box.xcg() * box.getWeight();
        double boxGCY = box.ycg() * box.getWeight();
        double boxGCZ = box.zcg() * box.getWeight();
        
        totalGCX += boxGCX;
        totalGCY += boxGCY;
        totalGCZ += boxGCZ;
        totalWeight += box.getWeight();

        gravityCenterX = totalGCX / totalWeight;
        gravityCenterY = totalGCY / totalWeight;
        gravityCenterZ = totalGCZ / totalWeight;
    }
};
