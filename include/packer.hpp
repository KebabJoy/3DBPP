#ifndef PACKER_HPP
#define PACKER_HPP

#include "box.hpp"
#include "pallet.hpp"

#include <vector>

class Packer {
public:
  Packer(Pallet &pallet, std::vector<Box> boxes);

  bool packBoxes();
  
  const std::vector<Box>& getBoxes() const;
private:
  Pallet &pallet;
  std::vector<Box> boxes;

  bool packBoxInPallet(Box &box);
  double getSpotScore(const Box &box, int x, int y, int z) const;
};

#endif // PACKER_HPP
