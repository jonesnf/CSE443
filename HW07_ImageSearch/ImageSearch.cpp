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
    int count = 0;
    // for all matches prev found, print and draw box
    for ( auto& a : src.matches ) {
        count++;
        std::cout << "sub-image matched at: " << a.first 
                  << ", " << a.second << ", " << a.first + mask.height 
                  << ", " << a.second + mask.width << std::endl; 
        drawBox(src.img, mask, a.first, a.second);
    }
    std::cout << "Num of matches: " << count << std::endl;
}


int getPixelIndex(int row, int col, int width) {
    int index = 0; 
    // calculate index of pixel based on row, col, and width of image
    index = (4*width)*row + (4 * col);
    return index;
}

bool isBlackPix(const PNGHelper& mask, int index) {
    // explicitly check if pixel is black
    int result = static_cast<int>(mask.buff[index])   == 0 &&
                 static_cast<int>(mask.buff[index+1]) == 0 &&
                 static_cast<int>(mask.buff[index+2]) == 0;
    return result;
}

// Simple method to determine how many black pixels are in mask
void showBckgrndPix(PNGHelper& img) {
    int index, blackPix = 0;
    for (int row = 0; row < img.height; row++) {
        for (int col = 0; col < img.width; col++) {
            index = getPixelIndex(row, col, img.width);
            if (isBlackPix(img, index))
                blackPix++;
        }
    }
    std::cout << "Num of black Pix: " << blackPix << std::endl;
}

// Determine if pixel in image is background pixel in corresponding masks
bool isBckgrndPix(PNGHelper& mask, int row, int col) {
    int index = getPixelIndex(row, col, mask.width);
    if (isBlackPix(mask, index)) 
        return true;
    return false;
}

void addPixel2Avg(PNGHelper& src, int index) {
    // add R G B A values to average for sub-image
    for (size_t i = 0; i < src.avg.size(); i++)
        src.avg[i] += src.buff[index+i];
}

bool isMatch(int index, PNGHelper& src) {
    // Determine if this pixel matches avg background w/ tolerance
    for (size_t i = 0; i < src.avg.size()-1; i++) {
        if (static_cast<int>(src.buff[index+i]) < (src.avg[i] - src.tol)
            || static_cast<int>(src.buff[index+i]) > (src.avg[i] + src.tol))
            return false;
    }
    return true;
}

bool checkMatch(PNGHelper& src, PNGHelper& mask, int row, int col) {
    int index = 0, m_row = 0, m_col = 0;
    // search through sub-image for matches
    for (m_row = row; m_row < mask.height+row; m_row++) {
        for (m_col = col; m_col < mask.width+col; m_col++) {
            index = getPixelIndex(m_row, m_col, src.width);
            if (isBckgrndPix(mask, m_row - row, m_col - col)) {
               (isMatch(index, src)) ? src.match++ : src.mismatch++; 
            } else { 
               (!isMatch(index, src)) ? src.match++ : src.mismatch++; 
            }
        }                    
    }
    // only add match if netmatch is sufficient and it's not already found
    if (src.isNetGood(mask) && !src.alrdyFnd(m_row, m_col, mask)) { 
        topLeft tl(m_row - mask.height, m_col - mask.width);
        src.matches.push_back(tl); return true;
    }
    return false;
}


void calcAvgBg(PNGHelper& src, PNGHelper& mask) {
    int index = 0; int rowEnd = src.height - mask.height + 1;
    int colEnd = src.width - mask.width + 1; bool mtchFnd = false;
    // search through image.  Increment col by width if match previously found
    for (int row = 0; row < rowEnd; row++) {
        for (int col = 0; col < colEnd; (mtchFnd) ? col += mask.width : col++) {
            for (int m_row = row; m_row < mask.height + row; m_row++) {
                for (int m_col = col; m_col < mask.width + col; m_col++) {
                    if (isBckgrndPix(mask, m_row - row, m_col - col)) {
                        src.numPixs++;
                        index = getPixelIndex(m_row, m_col, src.width);
                        addPixel2Avg(src, index);
                    }
                }                    
            } for (size_t i = 0; i < src.avg.size(); i++)
                    src.avg[i] /= src.numPixs;
            src.resetNetMatch(); src.numPixs = 0; 
            mtchFnd = checkMatch(src, mask, row, col);
        }
    }   
}

/*
 */
int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }
    PNGHelper srcHelp(argv[1]); 
    PNGHelper maskHelp(argv[2]);
    std::string output(argv[3]);
    // Ignoring argv[4], per the requirements
    if (argc > 5) srcHelp.perPixMatch = static_cast<double>(atoi(argv[5]));
    if (argc > 6) srcHelp.tol = static_cast<double>(atoi(argv[6]));
    showBckgrndPix(maskHelp);
    calcAvgBg(srcHelp, maskHelp);
    srcHelp.sortMatches();
    printMatches(srcHelp, maskHelp);
    srcHelp.img.write(output);
    return 0;
}

