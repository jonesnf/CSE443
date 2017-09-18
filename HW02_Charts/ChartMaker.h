/** A top-level class to perform operations on chart objects based on
	user input.

	NOTE: You may modify/add as many methods or instance variables
	as needed to design this class.
	
	Copyright (C) 2017 jonesnf@miamiOH.edu
*/

#ifndef CHART_MAKER_H
#define CHART_MAKER_H

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include "Chart.h"


using Menu = std::unordered_map<std::string, int>;
using MenuIt = std::unordered_map<std::string, int>::iterator;

class ChartMaker {
public:
    ChartMaker() {}
    ~ChartMaker() {}

    int run();
    void first3Cmds(int cmd, Chart& c);
    void sec3Cmds(int cmd, Chart& c);
    void third3Cmds(int cmd, Chart& c);
    void last3Cmds(int cmd, Chart& c); 

protected:
private:
    bool quit = false;
    std::string currCmd = "";
    std::string filePath = "";
    std::ifstream myFile; std::ofstream outFile;
    Chart tempChart;
    int tempX, tempY, maxSize, shiftPos;
    Menu cmds = {{"l", 1}, {"+", 2},
        {"-", 3}, {"*", 4}, {"/", 5}, {"?", 6},
        {"<", 7}, {">", 8}, {"s", 9}, {"p", 10},
        {"h", 11}, {"q", 12}};
    MenuIt getCmd;
};

#endif
