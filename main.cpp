#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
    double w; // weight
    double x, y, z; // dimensions
    double xc, yc, zc; // center of gravity
};

struct Pallet {
    double w; // weight capacity
    double x, y; // dimensions
    double xc, yc, zc; // center of gravity
    vector<Box> boxes;
};

class Heuristic {
public:
    Heuristic(Pallet& pallet, vector<Box>& boxes) : pallet(pallet), boxes(boxes) {}
    void solve() {
        sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) { return a.w > b.w; }); // sort boxes by weight in descending order
        for (int i = 0; i < boxes.size(); ++i) {
            bool placed = false;
            for (int j = 0; j < pallet.boxes.size(); ++j) {
                Box& box = pallet.boxes[j];
                if (box.w + boxes[i].w <= pallet.w) { // check weight constraint
                    double dx = max(boxes[i].x/2, box.x/2) + boxes[i].xc + box.xc;
                    double dy = max(boxes[i].y/2, box.y/2) + boxes[i].yc + box.yc;
                    double dz = max(boxes[i].z/2, box.z/2) + boxes[i].zc + box.zc;
                    if (dx <= pallet.x && dy <= pallet.y) { // check space constraint
                        box.w += boxes[i].w;
                        box.xc = (boxes[i].xc * boxes[i].w + box.xc * box.w) / (boxes[i].w + box.w); // update center of gravity
                        box.yc = (boxes[i].yc * boxes[i].w + box.yc * box.w) / (boxes[i].w + box.w);
                        box.zc = (boxes[i].zc * boxes[i].w + box.zc * box.w) / (boxes[i].w + box.w);
                        placed = true;
                        break;
                    }
                }
            }
            if (!placed) { // create new box on the pallet
                pallet.boxes.push_back({boxes[i].w, boxes[i].x, boxes[i].y, boxes[i].z, boxes[i].xc, boxes[i].yc, boxes[i].zc});
            }
        }
    }
private:
    Pallet& pallet;
    vector<Box>& boxes;
};


int main() {
    Pallet pallet;
    pallet.w = 1000;
    pallet.x = 120;
    pallet.y = 80;
    pallet.xc = pallet.x / 2;
    pallet.yc = pallet.y / 2;
    pallet.zc = 0;

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

    Heuristic heuristic(pallet, boxes);
    heuristic.solve();

    for (const Box& box : pallet.boxes) {
        cout << "Box weight: " << box.w << endl;
        cout << "Box dimensions (x, y, z): " << box.x << ", " << box.y << ", " << box.z << endl;
        cout << "Box center of gravity (x, y, z): " << box.xc << ", " << box.yc << ", " << box.zc << endl;
    }

    return 0;
}
