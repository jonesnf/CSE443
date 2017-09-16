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
    
    Chart c4;
    c4 = c3 - c;
    std::cout << "sub charts: " << c4;
    
    // Point scale(2, 3);
    Chart c5;
    c5 = c4 >> 5;
    std::cout << "R-shifted chart: " << c5;
    
    Chart c6;
    c6 = c5 << 5;
    std::cout << "L-shifted chart: " << c6;
    
    return 0;
}
