/* 
 * File:   PNGHelper.cpp
 * Author: Nate Jones
 *
 * Created on November 5, 2017, 7:41 PM
 * Copyright (C) 2017 jonesnf@miamioh.edu
 */
#include <string>
#include "PNGHelper.h"

PNGHelper::PNGHelper() {
    // default case
    img.load("Flag_of_the_US.png");
    buff = img.getBuffer();
    match = 0; mismatch = 0; netmatch = 0; height = 0; width = 0;
    numPixs = 0;
    avg = {0, 0, 0, 0};
}

PNGHelper::PNGHelper(const PNGHelper& png_h) : img(png_h.img), buff(png_h.buff),
        match(png_h.match), mismatch(png_h.mismatch), netmatch(png_h.netmatch),
        height(png_h.height), width(png_h.width), numPixs(png_h.numPixs),
        perPixMatch(png_h.perPixMatch), avg(png_h.avg) {
}

PNGHelper::PNGHelper(const std::string& filename) {
    img.load(filename);
    buff = img.getBuffer();
    match = 0; mismatch = 0; netmatch = 0; perPixMatch = 75;  // default perPix
    height = img.getHeight(); width = img.getWidth();
    numPixs = 0;
    avg = {0, 0, 0, 0};
}

int PNGHelper::getNetMatch() { return netmatch = abs(match - mismatch); }


/**
 * Why does this only work with getNetMatch() ???? 
 * @param const PNGHelper& mask
 * @return boolean
 */
bool PNGHelper::isNetGood(const PNGHelper& mask) { 
    return this->getNetMatch() > (mask.width * mask.height * \
                                    (mask.perPixMatch / 100));
}
