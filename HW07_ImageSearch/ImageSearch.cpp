/* 
 * Copyright (C) 2017 jonesnf@miamioh.edu
 * File:   main.cpp
 * Author: Nate Jones
 *
 * Description:
 *      This file contains functions that are necessary to compute information
 * about the image itself, such as: number of black pixels, if a pixel is a 
 * background pixel, and adding a pixel color to average.  The PNGHelper class
 * contains functions for managing the aspects about the images, such as: image
 * information, net matches, matches/mismatches, and list managing for 
 * averages/matches.
 * 
 * Created on November 5, 2017, 7:41 PM
 */
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "PNG.h"
#include "Assert.h"
#include "PNGHelper.h"

// Used to store top left index of matched region.
using topLeft = std::pair<int, int>;

void drawBox(PNG& src, PNGHelper& mask, int row, int col) {
    //  Drawing horizontal lines (both sides)
    for (int i = 0; (i < mask.width); i++) {
        src.setRed(row, col + i);
        src.setRed(row + mask.height - 1, col + i);
    }
    //  Drawing vertical lines (both sides)
    for (int i = 0; (i < mask.height); i++) {
        src.setRed(row + i, col);
        src.setRed(row + i, col + mask.width - 1);
    }
}

void printMatches(PNGHelper& src, PNGHelper& mask) {
    for ( auto& a : src.matches ) {
        std::cout << "sub-image matched at: " << a.first << ", " << a.second
                  << ", " << a.first + mask.height 
                  << ", " << a.second + mask.width; 
        drawBox(src.img, mask, a.first, a.second);
    }
}

int getPixelIndex(int row, int col, int width) {
    int index = 0; 
    index = (4*width)*row + (4 * col);
    return index;
}

int isBlackPix(const PNGHelper& mask, int index) {
    int result = (static_cast<int>(mask.buff[index]) \
                + static_cast<int>(mask.buff[index+1]) \
                + static_cast<int>(mask.buff[index+2])) / 3;
    return result;
}


void showBckgrndPix(PNGHelper& img) {
    int index, blackPix = 0;
    for (int row = 0; row < img.height; row++) {
        for (int col = 0; col < img.width; col++) {
            index = getPixelIndex(row, col, img.width);
            if (isBlackPix(img, index) == 0)
                blackPix++;
        }
    }
    std::cout << "Num of black Pix: " << blackPix << std::endl;
}



bool isBckgrndPix(PNGHelper& mask, int row, int col) {
    int index = getPixelIndex(row, col, mask.width);
    if (isBlackPix(mask, index) == 0) 
        return true;
    return false;
}

void addPixel2Avg(PNGHelper& src, int index) {
    for (size_t i = 0; i < src.avg.size(); i++)
        src.avg[i] += src.buff[index+i];
}

// TODO(jonesnf): have to pass through tolerance, rn default is 32
bool isMatch(int index, PNGHelper& src) {
    for (size_t i = 0; i < src.avg.size()-1; i++) {
        if (static_cast<int>(src.buff[index+i]) < (src.avg[i] - 32) || \
            static_cast<int>(src.buff[index+i]) > (src.avg[i] + 32)   )
                return false;
    }
    return true;
}

int checkMatch(PNGHelper& src, PNGHelper& mask, int rend, int cend) {
    int index = 0, m_row = 0, m_col = 0;
    for (int row = 0; row < rend; row++) {
        for (int col = 0; col < cend; col++) {
            src.netmatch = 0;
            for (m_row = row; m_row < mask.height+row; m_row++) {
                for (m_col = col; m_col < mask.width+col; m_col++) {
                    index = getPixelIndex(m_row+row, m_col+col, src.width);
                    if (isBckgrndPix(mask, m_row - row, m_col - col)) {
                      (isMatch(index, src)) ? src.match++ : src.mismatch++; 
                    } else { 
                        (!isMatch(index, src)) ? src.match++ : src.mismatch++; }
                }                    
            }
            if (src.isNetGood(mask) && !src.alrdyFnd(m_row, m_col, mask)) { 
                topLeft tl(m_row - mask.height, m_col - mask.width);
                src.matches.push_back(tl); }
        }
    }
    return src.getNetMatch();
}


int calcAvgBg(PNGHelper& src, PNGHelper& mask) {
    int index = 0; int rowEnd = src.height - mask.height + 1;
    int colEnd = src.width - mask.width + 1;
    for (int row = 0; row < rowEnd; row++) {
        for (int col = 0; col < colEnd; col++) {
            for (int m_row = row; m_row < mask.height + row; m_row++) {
                for (int m_col = col; m_col < mask.width + col; m_col++) {
                    if (isBckgrndPix(mask, m_row - row, m_col - col)) {
                        src.numPixs++;
                        index = getPixelIndex(m_row+row, m_col+col, src.width);
                        addPixel2Avg(src, index);
                    }
                }                    
            }
        }
    }
    for (size_t i = 0; i < src.avg.size(); i++)
        src.avg[i] /= src.numPixs;
    return src.netmatch = checkMatch(src, mask, rowEnd, colEnd);
}

/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << "Start" << std::endl;
    PNGHelper srcHelp("star.png"); PNGHelper maskHelp("star_mask.png");
    showBckgrndPix(maskHelp);
    calcAvgBg(srcHelp, maskHelp);
    std::cout << "Netmatches: " << srcHelp.netmatch << std::endl;
    srcHelp.sortMatches();
    printMatches(srcHelp, maskHelp);
    srcHelp.img.write("myoutput.png");
    return 0;
}

