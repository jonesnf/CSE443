
/* 
 * File:   main.cpp
 * Author: nate
 * Copyright (C) 2017 jonesnf@miamioh.edu
 * Created on October 22, 2017, 9:04 PM
 */

#include <omp.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using Vec = std::vector<int>;

bool isPrime(size_t num_1) {
    if (num_1 <= 1)
        return false;
    else if (num_1 <= 3)
        return true;  
    else if (num_1 % 2 == 0 || num_1 % 3 == 0)
        return false;
    bool prime = true;
    size_t end = std::sqrt(num_1) + 1;
#pragma omp parallel for shared(prime)
    for (size_t i = 5; i <= end; i+=6) {
        if (!prime) continue;  // essentially a break
        if (num_1 % i == 0 || num_1 % (i+2) == 0)
            prime = false;
    }
    return prime;
}

bool isPrimeFact(size_t num_1) {
    if (num_1 <= 3)
        return false;
    if (num_1 == 4)
        return true;
    bool fact = false;
    size_t end = std::sqrt(num_1) + 1;
#pragma omp parallel for shared(fact) schedule(static, 1)
    for (size_t i = 2; i <= end; i++) {
        if (fact) continue;
        if (isPrime(i) && num_1 % i == 0) {
            for (size_t j = 3; (i*j) <= num_1; j+=2) {
                if (i*j == num_1 && isPrime(j)) 
                    fact = true; 
            }
        }
    }
    return fact;
}

bool isPalindrome(size_t num_1) {
    size_t digits = 0; size_t numTemp = num_1; size_t Idx = 10;
    while (numTemp > 0) { numTemp /= 10; digits++;}
    if (digits == 1) return false;
    std::vector<size_t> tmpVec(digits);
    for (size_t i = 0; i < digits; i++) {tmpVec[i] = num_1 % Idx; num_1 /= 10;}
    --digits;
    bool found = false;
#pragma omp parallel for shared(found)
    for (size_t j = omp_get_thread_num(); j < digits; j++) {
        if (tmpVec[j] != tmpVec[digits - omp_get_thread_num()] || found) 
            continue; 
        if (j == digits || j == digits - 1) found = true; 
        digits-= omp_get_thread_num();
    }
    return found;
}

bool isPropFactorial(size_t num_1) {
    bool found = false;
    // size_t inc = 1, tmp2 = 1, tmp = 1, j = 1;
    size_t sum = 1;
#pragma omp parallel for shared(found) reduction(*:sum)
        for (size_t i = 1; i <= num_1; i++) {
            if (sum == num_1)
                found = true;
            if (found || sum > num_1) continue;
            sum *= i;
        }
    return found;
}

/*
 * Since this is a data parallel program, multiple threads will 
 * be assigned to one task
 */
int main(int argc, char** argv) {
    size_t num1, num2;
    num1 = std::stoi(argv[1]);
    num2 = std::stoi(argv[2]);
    if (argc < 3 || (num2 < num1)) {
        std::cerr << "Please enter valid arguments" << std::endl;
        return 1;
    }
    while (num1 <= num2) {
      std::cout << num1 << ": " << (isPrime(num1) ? "is prime" : "not prime") 
        << ", " << (isPrimeFact(num1) ? "is factorable" : "not factorable") 
        << ", " << (isPropFactorial(num1) ? "is factorial" : "not factorial")
        << ", " << (isPalindrome(num1) ? "is palindrome" : "not palindrome")
        << std::endl;
        num1++;
    }
    return 0;
}
