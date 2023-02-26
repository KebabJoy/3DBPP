#include "pallet.hpp"

Pallet::Pallet(double weightCapacity, double length, double width, double height, double gravityCenterX, double gravityCenterY, double gravityCenterZ)
    : weightCapacity(weightCapacity), length(length), width(width), height(height), gravityCenterX(gravityCenterX), gravityCenterY(gravityCenterY), gravityCenterZ(gravityCenterZ) {}

double Pallet::getWeightCapacity() const {
    return weightCapacity;
}

double Pallet::getLength() const {
    return length;
}

double Pallet::getWidth() const {
    return width;
}

double Pallet::getHeight() const {
    return height;
}

double Pallet::getGravityCenterX() const {
    return gravityCenterX;
}

double Pallet::getGravityCenterY() const {
    return gravityCenterY;
}

double Pallet::getGravityCenterZ() const {
    return gravityCenterZ;
}

void Pallet::placeBox(Box& box, int x, int y, int z) {
    box.setX(x);
    box.setY(y);
    box.setZ(z);
    boxes.push_back(box);
    recalculateGravityCenter(box);
}

bool Pallet::canAddBox(const Box& box) const {
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

double Pallet::getTotalWeight() const {
    double totalWeight = 0.0;
    for (const auto& box : boxes) {
        totalWeight += box.getWeight();
    }
    return totalWeight;
}

double Pallet::getTotalGravityCenterX() const {
    double totalGCX = 0.0;
    for (const auto& box : boxes) {
        totalGCX += box.xcg() * box.getWeight();
    }
    return totalGCX / getTotalWeight();
}

double Pallet::getTotalGravityCenterY() const {
    double totalGCY = 0.0;
    for (const auto& box : boxes) {
        totalGCY += box.ycg() * box.getWeight();
    }
    return totalGCY / getTotalWeight();
}

double Pallet::getTotalGravityCenterZ() const {
    double totalGCZ = 0.0;
    for (const auto& box : boxes) {
        totalGCZ += box.zcg() * box.getWeight();
    }
    return totalGCZ / getTotalWeight();
}
  
const std::vector<Box>& Pallet::getBoxes() const {
    return boxes;
}

void Pallet::recalculateGravityCenter(const Box& box) {
    double newWeight = getTotalWeight() + box.getWeight();
    double newGCX = (getTotalGravityCenterX() * getTotalWeight() + box.xcg() * box.getWeight()) / newWeight;
    double newGCY = (getTotalGravityCenterY() * getTotalWeight() + box.ycg() * box.getWeight()) / newWeight;
    double newGCZ = (getTotalGravityCenterZ() * getTotalWeight() + box.zcg() * box.getWeight()) / newWeight;

    gravityCenterX = newGCX;
    gravityCenterY = newGCY;
    gravityCenterZ = newGCZ;
}

bool Pallet::isBoxPlaceable(const Box& box, int x, int y, int z) const {
    // check if the box is within the pallet boundaries
    if (x + box.getWidth() > this->width || y + box.getLength() > this->length) {
        return false;
    }

    // check if there is any intersection with existing boxes
    for (const auto& placedBox : this->boxes) {
        if (x < placedBox.getX() + placedBox.getWidth() && x + box.getWidth() > placedBox.getX() &&
            y < placedBox.getY() + placedBox.getLength() && y + box.getLength() > placedBox.getY() &&
            z < placedBox.getZ() + placedBox.getHeight() && z + box.getHeight() > placedBox.getZ()) {
            return false;
        }
    }

    return true;
}

double Pallet::getCenterX() const {
    return width / 2.0;
}

double Pallet::getCenterY() const {
    return length / 2.0;
}