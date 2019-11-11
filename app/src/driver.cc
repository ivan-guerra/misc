#include <iostream>
#include <vector>
#include "3d_tree.h"

using namespace nnalgo;

int main(int argc, char** argv)
{
    std::vector<ThreeDPoint> points;
    points.emplace_back(1,0,0,0);
    points.emplace_back(2,0,0,1);
    points.emplace_back(3,0,1,1);
    points.emplace_back(4,1,0,0);
    points.emplace_back(5,1,0,1);
    points.emplace_back(6,1,1,0);
    points.emplace_back(7,1,1,1);

    ThreeDTree t(points);
    t.print_tree();

    return 0;
}
