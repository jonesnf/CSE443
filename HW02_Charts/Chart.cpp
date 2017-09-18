/* Copyright (C) 2017 jonesnf@miamioh.edu
 * File:   Chart.cpp
 * Author: nate
 * 
 * Created on September 13, 2017, 6:25 PM
 */

#include "Chart.h"
#include <algorithm>
#include <vector>

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
    Chart newC = *this;
    std::copy_if(other.pointList.begin(), other.pointList.end(), 
            std::back_inserter(newC.pointList), 
            [this](const Point& p){return !(this->contains(p));});
    return newC;
}

Chart Chart::operator-(const Chart& other) const {
    Chart newC;
    std::copy_if(this->pointList.begin(), this->pointList.end(), 
            std::back_inserter(newC.pointList), 
            [&other](const Point& p){return !(other.contains(p));});
    return newC;
}

Chart Chart::operator*(const Point& scale) const {
    Chart newC;
    std::transform(this->pointList.begin(), this->pointList.end(),
            std::back_inserter(newC.pointList),
            [&scale](const Point& p){
            return Point(p.getX()*scale.getX(), p.getY()*scale.getY());});
    return newC;
}

Chart Chart::operator/(const Point& scale) const {
    Chart newC;
    std::transform(this->pointList.begin(), this->pointList.end(),
            std::back_inserter(newC.pointList),
            [&scale](const Point& p){
            return Point(p.getX()/scale.getX(), p.getY()/scale.getY());});
    return newC;
}

Chart Chart::operator>>(int value) const {
    Chart newC = *this;
    for (; value > 0 ; --value) newC.pointList.insert(newC.pointList.begin(),
                                                                   Point(0, 0));
    return newC;
}

Chart Chart::operator<<(int value) const {
    Chart newC = *this;
    for (; value > 0 ; --value) newC.pointList.erase(newC.pointList.begin());
    return newC;
}

//  Fix this at some point.  Way too inefficient
void Chart::analyze(std::ostream& os, const int scale) const {
    Chart temp;
    std::copy_if(this->pointList.begin(), this->pointList.end(),
                 std::back_inserter(temp.pointList), 
                 [&temp](const Point& p){return !(temp.contains(p));});
    
    std::vector<int> quadFreq(4, 0);
    std::vector<str> quad = {"I: ", "II: ", "III: ", "IV: "};
    for ( auto& m : temp.pointList ) {
        quadFreq[m.getQuadrant() - 1]++;
    }
    size_t i = 0;
    int j = 0;
    for (; i < quadFreq.size(); ++i) {
        std::cout << quad[i];
        for (; j < (quadFreq[i] * scale) / *std::max_element(quadFreq.begin(),
                quadFreq.end()); j++) {
            std::cout << "*";
        }
        j = 0;
        std::cout << std::endl;
    }
}
