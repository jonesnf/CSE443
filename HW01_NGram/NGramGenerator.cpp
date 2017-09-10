/* Copyright (C) 2017 jonesnf@miamioh.edu
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#ifndef N_GRAM_GENERATOR_CPP 
#define N_GRAM_GENERATOR_CPP 

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

#include "NGramGenerator.h"

NGramGenerator::NGramGenerator(const size_t minGramLen /*=1*/,
                               const size_t maxGramLen /*=6*/) {
    minGramLength = minGramLen;
    maxGramLength = maxGramLen;
}

//  Add checking for gram length later. For now, just do unigram
void NGramGenerator::extractFrom(std::istream& is) {
    char c;
    while ( !is.eof() ) {
        is >> std::noskipws >> c;
        if ( std::isalnum(c) ) {
            wordHolder += c;
        } else if ( wordHolder != "" ) {
            wordq.push_back(wordHolder);
            wordHolder = "";  // Reseting wordHolder
        }
        if ( wordq.size() == maxGramLength ) 
            processGrams(wordq);
    } 
    //  Make sure we clear rest of items from queue
    while ( !wordq.empty() )
        processGrams(wordq);
}

void NGramGenerator::processGrams(WordQueue& q) {
    size_t i; 
    for ( i = 0; i < q.size(); i++ )  {
        wordHolder += q[i] + " ";
        if ( i >= minGramLength - 1 ) {
            get = ngmap.find(wordHolder);
            if ( get == ngmap.end() ) {
                ngmap.insert({wordHolder, 1});
            } else {
                get->second++;
            }
        }
    }
    wordHolder = "";
    q.pop_front();
}

void NGramGenerator::printTopNGrams(size_t topK,
                                    std::ostream& os /*= std::cout*/) {
    for ( auto& m : ngmap ) {
        top_k.push(m);
    }
    size_t i = 0;
    while ( i < topK && !top_k.empty() ) {
        std::cout << std::regex_replace(top_k.top().first,
                     std::regex("[ ]+$"), "") << 
                     ": " << top_k.top().second << std::endl;
        top_k.pop();
        i++;
    }
}


#endif 
