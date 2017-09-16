/* Copyright (C) 2017 jonesnf@miamioh.edu
 * File:   Chart.cpp
 * Author: nate
 * 
 * Created on September 13, 2017, 6:25 PM
 */

#include "Chart.h"
#include <algorithm>

Chart::Chart() : pointList{} {    
}

Chart::Chart(const Chart& orig) : pointList(orig.pointList) {
}

//  For some reason I can't use string w/o include in .cpp?
Chart::Chart(const str& filename) { 
    std::ifstream myFile(filename);
    std::istream_iterator<Point> file(myFile);
    std::copy(file, std::istream_iterator<Point>(),
            std::back_inserter(pointList)); 
}

Chart::~Chart() {
}

std::ostream& operator<<(std::ostream& os, const Chart& c) {
    for ( auto p : c.pointList )
        os << p.getX() << " " << p.getY() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Chart& c) {
    std::istream_iterator<Point> file(is);
    c.pointList.clear();
    std::copy(file, std::istream_iterator<Point>(), 
            std::back_inserter(c.pointList)); 
    return is;
}

Chart& Chart::operator=(const Chart& src) {
    this->pointList = src.pointList;
    return *this;
}

bool Chart::contains(const Point& p) const {
    return ( std::find(pointList.begin(), pointList.end(), p) != 
            pointList.end()) ? true : false;
}

Chart Chart::operator+(const Chart& other) const {
    Chart newC;
    std::copy(this->pointList.begin(), this->pointList.end(),
            std::back_inserter(newC.pointList));
    std::copy_if(other.pointList.begin(), other.pointList.end(), 
            std::back_inserter(newC.pointList), 
            [this](const Point& p){return !(this->contains(p));});
    return newC;
}


