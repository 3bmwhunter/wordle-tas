#ifndef WORDLE_ANALYSIS_H_
#define WORDLE_ANALYSIS_H_

#include <fstream>
#include <vector>
#include <map>
#include <codecvt>
#include <algorithm>
#include <locale>
#include <iostream>
#include <chrono>

#include "Utilities.h"

/**
 * attempts to find the best starting word combinations for the Wordle game. 
 * the user may specify
 *  - how many starting words they want
 *  - how long each word should be
 *  - the dictionary to use
 */
class WordleAnalysis {
    public:
        WordleAnalysis(const char* DICT_PATH, const unsigned int WORD_LENGTH = 5, const unsigned int TARGET_NUMBER_OF_WORDS = 5)
            : WORD_LENGTH(WORD_LENGTH), 
            TARGET_NUMBER_OF_WORDS(TARGET_NUMBER_OF_WORDS) {
                std::cout << "WORD_LENGTH = " << WORD_LENGTH << " TARGET_NUMBER = " << TARGET_NUMBER_OF_WORDS << std::endl;
                readDictionaryFile(DICT_PATH);
                writeWordsToJsonFile();
                filterWords();
                analyzeLetterDistribution();
                findPermutations();
                sortPermutations();
                writePermutationsToFile();
        }

    private:
        /**
         * all permutations
         */
        std::vector<std::vector<std::u32string>> results;

        /**
         * every WORD_LENGTH letter long word in the dictionary
         */
        std::vector<std::u32string> words;

        /**
         * every WORD_LENGTH letter long word in the dictionary, that has no duplicate letters
         */
        std::vector<std::u32string> wordsWithUniqueLetters;

        /**
         *  character -> probability of occuring in a WORD_LENGTH letter long word (in %) 
         */
        std::map<char32_t, double> probabilities;

        /**
         *  used to calculate average time in log
         */
        std::vector<int> timings;

        /**
         *  length of a single word
         */
        const unsigned int WORD_LENGTH;

        /**
         *  number of words in a permutation 
         */
        const unsigned int TARGET_NUMBER_OF_WORDS;

        /**
         *  reads the specified file into memory 
         */
        void readDictionaryFile(const char* DICT_PATH);

        /**
         * firstly filters out words that are not exactly WORD_LENGTH letters long.
         * secondly filter out words that share any letter, for example "hello" would be dropped since it has two 'l's
         */
        void filterWords();

        /**
         * maps every letter of the alphabet to it's number of occurances in all WORD_LENGTH letter long words 
         */
        void analyzeLetterDistribution();

        /**
         *  weighs a word based on the probability of each letter occuring in a WORD_LENGTH letter long word 
         */
        double getWordScore(std::u32string word);    

        /**
         *  weighs all words in permutation
         *  @returns sum of the individual word's score
         */
        double getCombinedWordScore(std::vector<std::u32string> permutation);

        /**
         * finds all permutations that
         *  - consist of TARGET_NUMBER_OF_WORDS many words
         *  - contain any letter at most once
         */
        void findPermutations();
        
        /**
         * finds all permutations of words in subset that
         *  - don't have any letters in common, i.e. every letter appears at most once in the entire permutation,
         *  - are exactly WORD_LENGTH words long.
         *
         * if all previously foundWords and the element in question don't have any letters in common,
         * it either
         *  - calls itself with the remaining words in subset (if the desired number of words hasn't been found yet) or
         *  - saves the sequence to results.
         * @param   subset      list of words to try
         * @param   foundWords  list of words that make up the (possible) result
         */
        void checkResult(const std::vector<std::u32string> &subset, std::vector<std::u32string> foundWords);

        /**
         *  sorts all found permutations based on the combined score of each of their words
         */
        void sortPermutations();

        /**
         * exports the sorted permutations as a JSON array
         */
        void writePermutationsToFile();

        /**
         * transform the given vector to a JSON array
         */
        std::string arrayToJsonString(std::vector<std::u32string> entry);

        /**
         * dump dictionary in json format (for usage in web extension)
         */
        void writeWordsToJsonFile();
};

#endif

