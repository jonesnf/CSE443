#ifndef MAIN_CPP
#define MAIN_CPP

//---------------------------------------------------------------------------
//
// Copyright (c) jonesnf@miamiOH.edu
// CSE Department, Miami University, Oxford, OHIO.
// All rights reserved.
//
// Miami University makes no representations or warranties about the
// suitability of the software, either express or implied, including
// but not limited to the implied warranties of merchantability,
// fitness for a particular purpose, or non-infringement.  Miami
// University shall not be liable for any damages suffered by licensee
// as a result of using, result of using, modifying or distributing
// this software or its derivatives.
//
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.
//
// Authors: Dhananjai M. Rao    raodm@miamiOH.edu
//
//---------------------------------------------------------------------------

#include <string>
#include "NGramGenerator.h"

//---------------------------------------------------------------------------
//              DO   NOT   MODIFY  THIS  SOURCE  FILE
//---------------------------------------------------------------------------

bool parseCmdLineArgs(int argc, char *argv[], std::string& fileName,
                      int& minLen, int&maxLen, int& topK) {
    // Convenience to use ""s suffix to identify c++ strings
    using namespace std::string_literals;

    // Parse command-line arguments and update values for various
    // parameters appropriately.
    int param  = 1;  // next arg to parse
    while (param < argc) {
        if ("--min-len"s == argv[param]) {
            minLen = std::stoi(argv[++param]);  // parse out min n-gram size
        } else if ("--max-len"s == argv[param]) {
            maxLen = std::stoi(argv[++param]);  // parse out max n-gram size
        } else if ("--file"s == argv[param]) {
            fileName = argv[++param];  // parse out max n-gram size
        } else if ("--top-k"s == argv[param]) {
            topK = std::stoi(argv[++param]);
        } else {
            std::cerr << "Invalid parameter: " << argv[param] << std::endl;
            return 2;  // exit with non-zero error code
        }
        param++;  // On to the next command-line argument.
    }
    // We need a file name to be specified.
    return !fileName.empty();
}

int main(int argc, char *argv[]) {
    std::string fileName;                  // to be filled-in below
    int minLen = 2, maxLen = 6, topK = 3;  // default values for arguments
    // Ensure we have a file name specified.
    if (!parseCmdLineArgs(argc, argv, fileName, minLen, maxLen, topK)) {
        std::cerr << "Specify file to process via --file argument\n";
        return 3;  // exit with non-zero error code.
    }
    // Open file and ensure it is readable
    std::ifstream dataFile(fileName);
    if (!dataFile.good()) {
        std::cerr << "File is invalid.\n";
        return 4;  // exit with non-zero error code.
    }
    // Create n-gram generator using parameters 
    NGramGenerator ngram(minLen, maxLen);
    // Extract n-grams using contents in specified data file.
    ngram.extractFrom(dataFile);
    // Print the top-k n-grams.
    ngram.printTopNGrams(topK);
    // All done. Return 0 to indicate successful run.
    return 0;
}

#endif

