/* 
 * File:   PNGHelper.h
 * Author: Nate Jones
 *
 * Created on November 5, 2017, 7:41 PM
 * Copyright (C) 2017 jonesnf@miamioh.edu
 */

#ifndef PNGHELPER_H
#define PNGHELPER_H

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "PNG.h"

using topLeft = std::pair<int, int>;

class PNGHelper {
public: 
    PNGHelper();
    PNGHelper(PNG& img);
    PNGHelper(const std::string& filename);
    PNGHelper(const PNGHelper& png_h);
    virtual ~PNGHelper(){};
    int getNetMatch();
    bool isNetGood(const PNGHelper& mask);
    bool alrdyFnd(const int, const int, const PNGHelper&);
    void sortMatches();
    void resetNetMatch();
    PNG img;
    std::vector<unsigned char> buff; 
    int match, mismatch, netmatch, height, width, numPixs;
    double perPixMatch;
    std::vector<int> avg;
    std::vector<topLeft> matches;
private: 
};


#endif /* PNGHELPER_H */

