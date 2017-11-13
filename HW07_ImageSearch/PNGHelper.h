/* 
 * File:   PNGHelper.h
 * Author: Nate Jones
 *
 * Created on November 5, 2017, 7:41 PM
 * Copyright (C) 2017 jonesnf@miamioh.edu
 */

#ifndef PNGHELPER_H
#define PNGHELPER_H

#include <string>
#include <vector>
#include "PNG.h"

class PNGHelper {
public: 
    PNGHelper();
    PNGHelper(PNG& img);
    PNGHelper(const std::string& filename);
    PNGHelper(const PNGHelper& png_h);
    virtual ~PNGHelper(){};
    PNG img;
    std::vector<unsigned char> buff; 
    int match, mismatch, netmatch, height, width, numPixs;
    std::vector<int> avg;
private: 
};


#endif /* PNGHELPER_H */

