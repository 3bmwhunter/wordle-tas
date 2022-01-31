# wordle-analysis

A C++ program that attempts to find the best combination of starting words. The user can choose
 - the dictionary to use,
 - the number of words to find and
 - the length of an individual word.

The programm will
1. create a `word.json` file for the browser extension
2. filter all words that don't have the specified length
3. analyse the letter distribution of these words. the more occurances a letter has, the more favorable its "score" is
4. filter all words that share one or more letters. e.g. "hello" would be filtered, because it has two 'l's, "audio" wouldn't be filtered, because any letter occurs once at most.
5. find all possible permutations of words that don't share any letters. the same logic as in 3. applies.
6. rank all permutations 
    - every letter is assigned a score based on the distribution determined in 2. 
    - the sum of each word's score is the score of the permutation.
7. write the results to a file in JSON


# Build
## Prerequisites
- make
- g++ (with support for c++2a)

## Compile
```bash
make
```

# Run 
```bash
./wordle-analysis.out --dictionary /path/to/your/dictionary [--option-name value]
```

**Note** 
Make sure that the values in your dictionary are sperated by line breaks (only `\n`, not `\r\n`) and that the file is saved in UTF-8.

## Optional arguments

|option |argument  | example|
--- | --- | ---|
|`--word-length`|number|`./wordle-analysis.out --dictionary english.txt --word-length 6`|
|`--number-of-words`|number|`./wordle-analysis.out --dictionary english.txt --number-of-words 3`|