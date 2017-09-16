/* Copyright (C) 2017 jonesnf@miamioh.edu
 * File:   Chart.h
 * Author: nate
 *
 * Created on September 13, 2017, 6:25 PM
 */

#ifndef CHART_H
#define CHART_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "Point.h"

using str = std::string;

class Chart {
    friend std::ostream& operator<<(std::ostream& os, const Chart& c);
    friend std::istream& operator>>(std::istream& is, Chart& c);
public:
    Chart();
    Chart(const Chart& orig);
    Chart(const str& filename);
    virtual ~Chart();
    Chart& operator=(const Chart& src);
    bool contains(const Point& p) const;
    Chart operator+(const Chart& other) const;
    Chart operator-(const Chart& other) const;
    Chart operator-(const Point& scale) const;
    Chart operator>>(int value) const;
    Chart operator<<(int value) const;
    void analyze(std::ostream& os, const int scale) const;
private:
    std::vector<Point> pointList;
};

#endif /* CHART_H */

