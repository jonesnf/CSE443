// Copyright (C) 2016 raodm@miamiOH.edu

#include <algorithm>
#include <vector>
#include "MatrixOps.h"

// Initializes a matrix of a given size. 
Matrix initMatrix(const size_t rows, const size_t cols) {
    Matrix mat(rows, std::vector<Val>(cols));
    for (size_t row = 0; (row < rows); row++) {
        for (size_t col = 0; (col < cols); col++) {
            mat[row][col] = row + col;
        }
    }
    return mat;
}
    
Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    const size_t cols  = matrix2[0].size();
    Matrix matrix3(matrix1.size(), std::vector<Val>(cols));
    for (size_t row = 0; (row < matrix1.size()); row++) {
        for (size_t col = 0; (col < cols); col++) {
            Val sum = 0;
            const size_t rows2 = matrix2.size();
            for (size_t i = 0; (i < rows2); i++)  {
                sum += (matrix1[row][i] * matrix2[i][col]);
            }
            matrix3[row][col] = sum;
        }
    }
    return matrix3;
}

Val sumDiag(const Matrix& mat) {
    Val sum = 0;
    size_t minDim = std::min(mat.size(), mat[0].size());
    for (size_t i = 0; (i < minDim); i++) {
        sum += mat[i][i];
    }
    return sum;
}

