#include "WordleAnalysis.h"

void WordleAnalysis::readDictionaryFile(const char* DICT_PATH) {
    std::basic_ifstream<char32_t> dictifs(DICT_PATH);
    std::u32string dictionaryFile;

    std::copy(
        std::istreambuf_iterator<char32_t>(dictifs),
        std::istreambuf_iterator<char32_t>(),
        std::back_inserter(dictionaryFile)
    );

    dictifs.close();
    
    dictionaryFile = toLowerCase(dictionaryFile);

    std::u32string segment;

    for(auto letter : dictionaryFile) {
        if(letter == '\n') {
            words.push_back(segment);
            segment.clear();
        } else {
            segment += letter;
        }
    }

    std::cout << "total words: " << words.size()  << std::endl; 
}

void WordleAnalysis::filterWords() {
    std::vector<std::u32string> nLetterWords;
    std::copy_if (words.begin(), words.end(), std::back_inserter(nLetterWords), [&](std::u32string in){
        return in.size() == WORD_LENGTH;
    });

    std::cout << WORD_LENGTH << " letter long words: " << nLetterWords.size()  << std::endl;
    
    words = nLetterWords;            

    std::vector<std::u32string> nLetterWordsWithUniqueCharacters;
    std::copy_if (nLetterWords.begin(), nLetterWords.end(), std::back_inserter(nLetterWordsWithUniqueCharacters), [&](std::u32string in){
        std::sort(in.begin(), in.end());
        return (std::unique(in.begin(), in.end()) == in.end());
    });

    std::cout << WORD_LENGTH << " letter long words with unique characters: " << nLetterWordsWithUniqueCharacters.size() << std::endl;

    wordsWithUniqueLetters = nLetterWordsWithUniqueCharacters;
}

void WordleAnalysis::analyzeLetterDistribution() {
    std::map<char32_t, int> letterCountMap;

    for(auto word : words) {
        for(auto letter : word) {
            auto elementIterator =  letterCountMap.find(letter);
            int oldCount = 0;
            if(elementIterator != letterCountMap.end()) {
                oldCount = elementIterator->second;
            }
            
            letterCountMap.insert({letter, ++oldCount });
        }
    }

    const int totalNumberOfletters = words.size() * WORD_LENGTH;

    for(auto entry : letterCountMap) {
        probabilities.insert({
            entry.first,
            (entry.second / double(totalNumberOfletters)) * 100.0
        });
    }
}

double WordleAnalysis::getWordScore(std::u32string word) {
    double total = 0.0;
    for(auto letter : word) {
        total += probabilities.find(letter)->second;
    }

    return total;
}

void WordleAnalysis::checkResult(
    const std::vector<std::u32string> &subset, 
    std::vector<std::u32string> foundWords
) { 
    std::u32string combined;       
    for(auto found : foundWords) {
        combined += found;
    }
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

    for(auto word : subset) {  
        if(!hasOverlap(combined, word)) {
            foundWords.push_back(word);

            if(foundWords.size() == TARGET_NUMBER_OF_WORDS)  {                
                results.push_back(foundWords);
            } else {   
                checkResult(
                    std::vector<std::u32string>(std::find(subset.begin(), subset.end(), word) + 1, subset.end()),
                    foundWords
                );
            }

            foundWords.pop_back();
        } 
    }
}

void WordleAnalysis::findPermutations() {
    auto start_time = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < wordsWithUniqueLetters.size(); i++) {
        auto firstWord = wordsWithUniqueLetters.at(i);

        std::vector<std::u32string> subset(
            wordsWithUniqueLetters.begin() + i,
            wordsWithUniqueLetters.end()
        );

        std::vector<std::u32string> foundWords {
            firstWord
        };

        checkResult(subset, foundWords);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        auto timeInMs = time / std::chrono::milliseconds(1);
        timings.push_back(timeInMs);


        std::cout << "[" << i + 1 << "/" << wordsWithUniqueLetters.size() << "] "
            << ((i + 1) / double(wordsWithUniqueLetters.size())) * 100 << "%"
            << "\t\tnResults: " << results.size()
            << "\tlast result: ";

        if(results.size() > 0) {
            std::cout << arrayToJsonString(results.at(results.size() - 1));
        }

        std::cout << "\t\tlastTick: " << timeInMs << " avg: " << average(timings) << std::endl;

        start_time = std::chrono::high_resolution_clock::now();
    }
}

void WordleAnalysis::sortPermutations() {
    std::sort(results.begin(), results.end(),
        [this](const std::vector<std::u32string>& a, const std::vector<std::u32string>& b) -> bool{             
            return getCombinedWordScore(a) < getCombinedWordScore(b); 
        }
    );
}

void WordleAnalysis::writePermutationsToFile() {
    std::cout << "writing results... ";

    std::ofstream myfile("analysis_results.json", std::ios::out);

    myfile << "[\n";

    for(unsigned int i = 0; i < results.size(); i++) {
        auto permutation = results[i];
        
        myfile << "\t" << arrayToJsonString(permutation);
        
        if(i != results.size() -1) {
            myfile << ",\n";
        }
    }

    myfile << "\n]\n";

    myfile.close();

    std::cout << "done!" << std::endl;
}

void WordleAnalysis::writeWordsToJsonFile() {
    std::cout << "dumping words to file... ";

    std::ofstream myfile("words.json", std::ios::out);

    myfile << arrayToJsonString(words);

    myfile.close();

    std::cout << "done!" << std::endl;
}


std::string WordleAnalysis::arrayToJsonString(std::vector<std::u32string> permutation) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

    std::string asString = "[";
    for(unsigned int j = 0; j < permutation.size(); j++) {
        asString += "\"" + converter.to_bytes( permutation[j] ) + "\"";
        if(j != permutation.size() - 1) {
            asString += ",";
        }
    }
    asString += "]";
    
    return asString;
}

double WordleAnalysis::getCombinedWordScore(std::vector<std::u32string> permutation) {
    double total = 0.0;

    for(auto word : permutation) {
        total += getWordScore(word);
    }

    return total;
}
