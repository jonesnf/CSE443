/* 
 * File:   main.cpp
 * Author: nate
 *
 * Created on November 5, 2017, 7:41 PM
 * Copyright (C) 2017 jonesnf@miamioh.edu
 */
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "PNG.h"
#include "Assert.h"

using PixVec = std::vector<unsigned char>;
using AvgVec = std::vector<int>;

int getPixelIndex(int row, int col, int width) {
    int index = 0; 
    index = (4*width)*row + (4 * col);
    return index;
}

int isBlackPix(PixVec& buff, int index) {
    int result = (static_cast<int>(buff[index]) \
                + static_cast<int>(buff[index+1]) \
                + static_cast<int>(buff[index+2])) / 3;
    return result;
}


void showBckgrndPix(PNG& img) {
    int index, blackPix = 0;
    for (int row = 0; row < img.getHeight(); row++) {
        for (int col = 0; col < img.getWidth(); col++) {
            index = getPixelIndex(row, col, img.getWidth());
            if (isBlackPix(img.getBuffer(), index) == 0)
                blackPix++;
        }
    }
    std::cout << "Num of black Pix: " << blackPix << std::endl;
}



bool isBckgrndPix(PNG& img, PNG& mask, int row, int col) {
    int index = getPixelIndex(row, col, mask.getWidth());
    if (isBlackPix(mask.getBuffer(), index) == 0) 
        return true;
    return false;
}

void addPixel2Avg(AvgVec& avg, const PixVec& buff, int index) {
    for (size_t i = 0; i < avg.size(); i++)
        avg[i] += buff[index+i];
}

//TODO: have to pass through tolerance
bool isMatch(int index, PixVec& imgBuff, AvgVec& avg) {
    for (size_t i = 0; i < avg.size(); i++) {
        if (imgBuff[index+i] != avg[i])
                return false;
    }
    return true;
}

void checkMatch(PNG& mask, PNG& img, PixVec& imgBuff, AvgVec& avg, \
        int rend, int cend) {
    int index = 0; int match = 0; int mismatch = 0;
    for (int row = 0; row < rend; row++) {
        for (int col = 0; col < cend; col++) {
            for (int m_row = row; m_row < mask.getHeight() + row; m_row++) {
                for (int m_col = col; m_col < mask.getWidth() + col; m_col++) {
                    if (isBckgrndPix(img, mask, m_row - row, m_col - col)) {
                 index = getPixelIndex(m_row+row, m_col + col, img.getWidth());
                      (isMatch(index, imgBuff, avg)) ? match++ : mismatch++; 
                    } else { 
                      (!isMatch(index, imgBuff, avg)) ? match++ : mismatch++; }
                }                    
            }
        }
    }
    std::cout << "Matches: " << match << std::endl;
    std::cout << "Mismatches: " << mismatch << std::endl;
}


AvgVec calcAvgBg(PNG& img, PixVec& imgBuff, PNG& mask, PixVec& maskBuff) {
    std::vector<int> rgba_avg(4); int index = 0; int num = 0;
    int rowEnd = img.getHeight() - mask.getHeight() + 1;
    int colEnd = img.getWidth() - mask.getWidth() + 1;
    for (int row = 0; row < rowEnd; row++) {
        for (int col = 0; col < colEnd; col++) {
            for (int m_row = row; m_row < mask.getHeight() + row; m_row++) {
                for (int m_col = col; m_col < mask.getWidth() + col; m_col++) {
                    if (isBckgrndPix(img, mask, m_row - row, m_col - col)) {
                        num++;
                index = getPixelIndex(m_row+row, m_col + col, img.getWidth());
                        addPixel2Avg(rgba_avg, imgBuff, index);
                    }
                }                    
            }
        }
    }
    for (size_t i = 0; i < rgba_avg.size(); i++)
        rgba_avg[i] /= num;
    checkMatch(mask, img, imgBuff, rgba_avg, rowEnd, colEnd);
    return rgba_avg;
}

/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << "Start" << std::endl;
    PNG img; PNG mask; 
    std::vector<int> avg(4);
    mask.load("star_mask.png");
    img.load("star.png");
    PixVec& buffMask = mask.getBuffer();
    PixVec& buff = img.getBuffer();
    showBckgrndPix(mask);
    avg = calcAvgBg(img, buff, mask, buffMask);
    return 0;
}

