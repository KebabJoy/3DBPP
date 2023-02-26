#include <iostream>
#include "include/packer.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    Pallet pallet(1000.0, 120.0, 80.0, 0.0, 60.0, 40.0, 0.0);
    
     vector<Box> boxes = {
         {100, 80, 60, 40, 40, 30, 20},
         {150, 60, 40, 30, 30, 20, 15},
         {80, 40, 30, 20, 20, 15, 10},
         {120, 50, 50, 50, 25, 25, 25},
         {200, 80, 60, 40, 40, 30, 20},
         {100, 60, 40, 30, 30, 20, 15},
         {80, 30, 30, 30, 15, 15, 15},
         {150, 40, 40, 40, 20, 20, 20},
         {120, 50, 50, 50, 25, 25, 25},
         {80, 30, 30, 30, 15, 15, 15}
     };

    Packer p(pallet, boxes);
    p.packBoxes();
    for(auto x : p.getBoxes()){
        cout << x.getWeight() << '\n';
    }
    return 0;
}
