#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <vector>
#include <algorithm>

/**
 * @returns true if the a and b share any letters, false otherwise
 */
bool hasOverlap(const std::u32string &a, const std::u32string &b);


/**
 * @returns     average of given values
 */ 
double average(const std::vector<int>& input);


/**
 * replace every capital letter with the corresponding lowercase letter
 */
std::u32string toLowerCase(std::u32string input);

#endif