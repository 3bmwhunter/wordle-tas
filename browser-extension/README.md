# wordle-tas-browser-extension

This program is currently only compatible for the version of the game at [wordlegame.org](https://wordlegame.org/). 
It 
1. injects the required code into pages matching the domain above,
2. enters the defined starting words,
3. checks which letters were correct (green) and which letters are part of the word, but aren't in the right position,
4. uses the information gathered in 3. to guess the word
5. repeats from 2. until it has won 100 ganes.

The timing of the run will be printed to the browser console (press <kbd>F12</kbd> to open).

# Installation
1. provide a words.json file (you can use the analysis program to generate one)
2. go to [chrome://extensions/](chrome://extensions/)
3. enable dev mode (switch in upper right corner)
4. Load unpacked 
5. select the folder that contains this README
6. optional: change settings, see [Settings](#settings) 
7. go to [wordlegame.org](https://wordlegame.org/), the run will start instantly

# Settings
By clicking the logo in the extensions section of the toolbar you can adjust the settings.

## alphabet
Every possible input for a single letter in the game.

## hint words
The starting words to use.