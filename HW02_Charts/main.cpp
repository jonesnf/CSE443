// Copyright (C) 2017 raodm@miamiOH.edu

#include "ChartMaker.h"
#include "Chart.h"
#include "Point.h"

// A simple main method to run ChartMaker
int main() {
    //  ChartMaker cm;
    //  return cm.run();
    Chart c("small_points1.txt");
    Chart c2;
    std::cout << "Chart1: " << c;
    std::ifstream myFile("small_points2.txt");
    myFile >> c2;
    std::cout << "Chart2: " << c2;
    // c2 = c;
    // std::cout << "copy chart: " << c;
    // Point p(-1, 1);
    // std::cout << "Contains p?: " << c2.contains(p) << std::endl;
    Chart c3;
    c3 = c + c2;
    std::cout << "added charts: " << c3;
    return 0;
}
