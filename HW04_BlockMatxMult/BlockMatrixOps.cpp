/* Copyright (C) 2017 jonesnf@miamioh.edu
 * File:   BlockMatrixOps.cpp
 *
 * Created on September 28, 2017, 7:52 PM
 */

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "MatrixOps.h"

Matrix load(const std::string& filePath) {
    std::ifstream myFile(filePath);
    int rows, cols, tempData, i = 0, j;
    myFile >> rows >> cols;
    Matrix mat(rows, std::vector<Val>(cols)); 
    for (; (!myFile.eof()) && i < rows; ++i) {
        for (j = 0; (!myFile.eof()) && j < cols; ++j) {
            myFile >> tempData;
            mat[i][j] = tempData;
        }
    }
    myFile.close();
    return mat;
}

void write(const std::string& filePath, const Matrix& mat) {
    std::ofstream myFile;
    myFile.open(filePath);
    myFile << mat.size() << " " << mat[0].size() << std::endl;
    for (size_t i = 0; i < mat.size(); ++i) {
        for (size_t j = 0; j < mat[0].size(); ++j) {
            myFile << mat[i][j] << " ";
        }
        myFile << std::endl;
    }
    myFile.close();
}

Matrix blockMultiply(const Matrix& matrix1, const Matrix& matrix2, 
                                            const size_t blockSize) {
    size_t size = matrix1.size(), colSize = matrix1[0].size();
    Matrix mat(size, std::vector<Val>(size));
    for (size_t i = 0; i < size; 
            i += (i + blockSize > size) ? (size % blockSize) - 1 : blockSize) {
     for (size_t j = 0; j < colSize; 
       j += (j + blockSize > colSize) ? (colSize % blockSize) - 1 : blockSize) {
       for (size_t ii = i; ii < std::min(i + blockSize, size); ++ii) {
         for (size_t jj = j; jj < std::min(j + blockSize, size); ++jj) {
            Val sum = 0;
           for (size_t kk = j; kk < std::min(j + blockSize, colSize); ++kk) {
                      sum += matrix1[ii][kk] * matrix2[kk][jj];
                     }
                    mat[ii][jj] += sum;
                }
            }
        }
    }
    return mat;
}
