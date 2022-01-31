#include "WordleAnalysis.h"

#include <cstring>

int main(int argc, char** argv) {
    static constexpr char DICTIONARY_KEY[] = "--dictionary";
    static constexpr char WORD_LENGTH_KEY[] = "--word-length";
    static constexpr char NUMBER_OF_WORDS_KEY[] = "--number-of-words";

    char* dictionaryPath = nullptr;
    int wordLength = 5;
    int numberOfWords = 5;

    if(argc < 3) {
        std::cerr << "Usage: " 
                    << argv[0] << " " 
                    << DICTIONARY_KEY << " <path/to/dictionary> " 
                    << "[" << WORD_LENGTH_KEY <<  " <number>] " 
                    << "[" << NUMBER_OF_WORDS_KEY <<  " <number>]" << std::endl;
        return 1;
    }

    for(int i  = 1; i < argc; i++) {
        if(!strcmp(DICTIONARY_KEY, argv[i])) {
            if(i + 1 < argc) {
                dictionaryPath = argv[++i];
            } else {
                std::cerr << DICTIONARY_KEY << " option requires an argument." << std::endl;
                return 1;
            }
        } else if(!strcmp(WORD_LENGTH_KEY, argv[i])) {
            if(i + 1 < argc) {
                wordLength = std::stoi(argv[++i]);
            } else {
                std::cerr << WORD_LENGTH_KEY << " option requires an argument." << std::endl;
                return 1;
            }
        } else if(!strcmp(NUMBER_OF_WORDS_KEY, argv[i])) {
            if(i + 1 < argc) {
                numberOfWords = std::stoi(argv[++i]);
            } else {
                std::cerr << NUMBER_OF_WORDS_KEY << " option requires an argument." << std::endl;
                return 1;
            }
        }
    }

    std::cout << "calling with args " << dictionaryPath << " " << wordLength << " " << numberOfWords << std::endl;

    WordleAnalysis analysis(dictionaryPath, wordLength, numberOfWords);  

    return 0;
}
