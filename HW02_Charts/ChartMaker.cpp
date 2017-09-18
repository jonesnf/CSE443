#ifndef CHART_MAKER_CPP
#define CHART_MAKER_CPP

// Copyright (C) 2017 raodm@miamiOH.edu

#include "ChartMaker.h"

int
ChartMaker::run() {
    Chart currChart;
    while (!quit) {
        std::cout << "Enter command (h for help): ";    
        std::cin >> currCmd;
        getCmd = cmds.find(currCmd);
        if ( getCmd->second >= 1 && getCmd->second <=3 )
            first3Cmds(getCmd->second, currChart);
        else if ( getCmd->second >= 4 && getCmd->second <=6 )
            sec3Cmds(getCmd->second, currChart);
        else if ( getCmd->second >= 7 && getCmd->second <=9 )
            third3Cmds(getCmd->second, currChart);
        else if ( getCmd->second >= 10 && getCmd->second <=12 )
            last3Cmds(getCmd->second, currChart);
        else
            std::cout << "Please enter valid cmd (h for help)" << std::endl;
    }
    
    return 0;
}


void ChartMaker::first3Cmds(int cmd, Chart& c) {
    switch (cmd) {
        case 1: 
            std::cout << "Enter path to file: ";  // Can move to run if needed
            std::cin >> filePath; myFile.open(filePath);
            myFile >> c; myFile.close();
            break;
        case 2:
            std::cout << "Enter path to file: ";
            std::cin >> filePath; myFile.open(filePath);
            myFile >> tempChart; c = c + tempChart; myFile.close();
            break;
        case 3:
            std::cout << "Enter path to file: ";
            std::cin >> filePath; myFile.open(filePath);
            myFile >> tempChart; c = c - tempChart; myFile.close();
            break;            
    }
}

void ChartMaker::sec3Cmds(int cmd, Chart& c) {
    switch (cmd) {
        case 4: 
            std::cout << "Enter values to scale x & y coordinates: ";
            std::cin >> tempX >> tempY; c = c * Point(tempX, tempY);
            break;
        case 5:
            std::cout << "Enter values to scale x & y coordinates: ";
            std::cin >> tempX >> tempY; c = c / Point(tempX, tempY);
            break;
        case 6:
            std::cout << "Enter max size for histogram: ";
            std::cin >> maxSize; c.analyze(std::cout, maxSize);
            break;            
    }
}

void ChartMaker::third3Cmds(int cmd, Chart& c) {
    switch (cmd) {
        case 7: 
            std::cout << "Enter positions to shift: ";
            std::cin >> shiftPos; c = c << shiftPos;
            break;
        case 8:
            std::cout << "Enter positions to shift: ";
            std::cin >> shiftPos; c = c >> shiftPos;
            break;
        case 9:
            std::cout << "Enter path to file: ";
            std::cin >> filePath; outFile.open(filePath);
            outFile << c << std::endl; outFile.close();
            break;            
    }
}

void ChartMaker::last3Cmds(int cmd, Chart& c) {
    switch (cmd) {
        case 10: 
            std::cout << c << std::endl;
            break;
        case 11:
            std::cout << "All commands are single characters.\nValid commands"
                      << " are:\n" 
                      << "l: Load data from file as current set of points\n"
                      << "+: Add data from another to to current points\n"
               << "-: Subtract data from another file from current poitns\n"
                      << "*: Scale current points by given pair of values\n"
                      << "/: Scale current points by given pair of values\n"
                      << "?: Print histogram current point distribution\n"
                      << "<: Shift points to left by a given value.\n"
                      << ">: Shift points to right by a given value.\n"
                      << "s: Save the current set of points to a given file\n"
                      << "p: Print current set of points on screen.\n"
                      << "h: Print this message\n"
                      << "q: Quit\n";
            break;
        case 12:
            quit = true;
            break;            
    }
}

#endif
