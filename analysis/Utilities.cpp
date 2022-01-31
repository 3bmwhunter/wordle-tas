#include "Utilities.h"


bool hasOverlap(const std::u32string &a, const std::u32string &b) {
    for(auto aLetter : a) {
        for(auto bLetter : b) {
            if(aLetter == bLetter) {
                return true;
            }
        }
    }

    return false;
}

double average(const std::vector<int>& input) {
    double value = 0.0;
    for(auto in : input) {
        value += double(in);
    }

    return value / input.size();
}

std::u32string toLowerCase(std::u32string input) {    
    for(char32_t i = U'A'; i <= U'Z'; i++) {
        std::replace(
            input.begin(),
            input.end(),
            i,
            char32_t(i + 32)
        );  
    }
    
    std::replace(
        input.begin(),
        input.end(),
        U'Ä',
        U'ä'
    );  

    std::replace(
        input.begin(),
        input.end(),
        U'Ö',
        U'ö'
    );  
    
    std::replace(
        input.begin(),
        input.end(),
        U'Ü',
        U'ü'
    );  

    return input;
}