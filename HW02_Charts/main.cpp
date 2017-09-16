// Copyright (C) 2017 raodm@miamiOH.edu

#include "ChartMaker.h"
#include "Chart.h"

// A simple main method to run ChartMaker
int main() {
    //  ChartMaker cm;
    //  return cm.run();
    Chart c("small_points1.txt");
    std::cout << c;
    std::ifstream myFile("small_points2.txt");
    myFile >> c;
    std::cout << c;
    return 0;
}
