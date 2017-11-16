/* 
 * File:   PNGHelper.cpp
 * Author: Nate Jones
 *
 * Created on November 5, 2017, 7:41 PM
 * Copyright (C) 2017 jonesnf@miamioh.edu
 */
#include <string>
#include <utility>
#include <algorithm>
#include "PNGHelper.h"

using topLeft = std::pair<int, int>;

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

/**
 *  Returns net matches, which is equal to = matches - mismatches
 * @return netmatch
 */
int PNGHelper::getNetMatch() { return netmatch = abs(match - mismatch); }

/**
 * Reset the values computed in net match
 */
void PNGHelper::resetNetMatch() { netmatch = 0; match = 0; mismatch = 0; }


/**
 * Why does this only work with getNetMatch() ???? 
 * @param const PNGHelper& mask
 * @return boolean
 */
bool PNGHelper::isNetGood(const PNGHelper& mask) { 
    // std::cout << "isNetGood NetMatch: " << this->getNetMatch() << std::endl;
    /* std::cout << mask.width * mask.height * (mask.perPixMatch / 100) 
              << std::endl;*/
    return this->getNetMatch() > (mask.width * mask.height * \
                                    (mask.perPixMatch / 100));
}

/**
 * Check if index already exists based on previous match
 *  - Uses lambda to check if given index is in range of any previously added 
 *    matches
 * @param tl
 * @return true if indices were not already found, else return false
 */
bool PNGHelper::alrdyFnd(const int row, const int col, const PNGHelper& mask) {
    topLeft tl(row, col);
    auto result = std::find_if(matches.begin(), matches.end(), [tl, mask] \
        (const topLeft& tmp) { 
        return (tl.first >= tmp.first && tl.first <= tmp.first + mask.height)
           && (tl.second >= tmp.second && tl.second <= tmp.second + mask.width);
        });
    return result != std::end(matches);
}

bool customSort(topLeft& ta, topLeft& tb) { 
        if (ta.first == tb.first)
            return ta.second < tb.second;
        else 
            return ta.first < tb.first;
};

/**
 * Sort Matches based on row, then on column
 */
void PNGHelper::sortMatches() {
    std::sort(matches.begin(), matches.end(), customSort);
}
