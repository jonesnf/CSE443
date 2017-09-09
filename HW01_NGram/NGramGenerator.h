/* Copyright (C) 2017 jonesnf@miamioh.edu
 * File:   NGram_Generator.h
 * Author: nate
 *
 * Created on September 6, 2017, 5:30 PM
 */

#ifndef N_GRAM_GENERATOR_H
#define N_GRAM_GENERATOR_H

//---------------------------------------------------------------------------
//
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
//---------------------------------------------------------------------------

// Included various commonly used libraries.  You may not need all of
// them but they are here just for your convenience.
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <queue>
#include <stack>
#include <utility>
#include <fstream>
#include <algorithm>
#include <iterator>

// A hashmap for counting frequency of n-grams
using NGramMap = std::unordered_map<std::string, int>;
using WordQueue = std::queue<std::string>;
    
/** A relatively straightforward class to extract n-grams from a given
    corpus of text.
    
*/
class NGramGenerator {
public:
    /** The constructor for this class to create a n-gram generator to
        extract n-grams of given length.

        The constructor merely initializes instance variables with
        corresponding parameter values.
        
        \param[in] minGramLen The minimum length of the n-gram to be
        extracted.  This value is assumed to be greater than 0 and no
        special checks are made on validity of this parameter.

        \param[in] maxGramLen The maximum length of the n-gram to be
        extracted.  This value is assumed to be greater than
        minGramLen and no special checks are made on validating this
        parameter.
    */
    NGramGenerator(const size_t minGramLen = 1, const size_t maxGramLen = 6);

    /** The destructor.

        The destructor does not have any special operations to perform
        and is merely present to adhere to good coding practices.
     */
    ~NGramGenerator() {}

    /** Convenience method to extract n-grams from a given input
        stream.

        This method extracts n-grams of length 'n', where minGramLen
        <= n <= maxGramLen.  This method computes the occurrence
        frequencies of n-grams and stores them internally for further
        processing.

        \param[in] is The input stream from where words are to be
        extracted and converted to n-grams.

        \param[in] is The input stream from where words are to be
        extracted.
    */
    void extractFrom(std::istream& is);

    /** Print the most frequently occurring n-grams.

        This method prints the most frequently occurring n-grams in
        their occurrenceq order.  Specifically, this method prints the
        top 'k' high frequency n-grams only.  N-grams with the same
        occurrence frequency are printed in alphabetical order.

        \note The output from this method is meaningful only only
        after the extractFrom() method has successfully finished.
        
        \param[in] topK The top-k n-grams to be printed.  This value
        must be > 0.

        \param[out] os The output stream to which the n-grams are to
        be printed.
    */
    void printTopNGrams(size_t topK, std::ostream& os = std::cout);
    
    void updateMap(WordQueue& q);
    
protected:
    // Add any instance variables or methods as needed.

private:
    // Add any instance variables or methods as needed.
    // Change theses later, wack names
    size_t minGramLength, maxGramLength;
    std::string wordHolder = "";
    WordQueue wordq;
};

#endif /* NGRAM_GENERATOR_H */

