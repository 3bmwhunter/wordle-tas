let alphabet = "";

chrome.storage.local.get(["alphabet"], result => {
    alphabet = result.alphabet
});

let hintWords = [];
let wordLength = 5;

chrome.storage.local.get(["hintWords"], result => {
    hintWords = result.hintWords
    wordLength = hintWords[0].length
});

const url = chrome.runtime.getURL('/words.json');

let allWords = [];

let nWins = 0;
let nLosses = 0;

const solve = () => {
    const typeToGameKeyboard = (word) => {
        const buttonElements = Array.from(document.querySelectorAll(".Game-keyboard-button"));
        Array.from(word).forEach(letter => buttonElements.find(elem => elem.innerHTML === letter).click());
        buttonElements.find(elem => elem.innerHTML === "Enter").click();
    }
    hintWords.forEach(word => typeToGameKeyboard(word))
    
    const correct = Array.from(document.querySelectorAll(".Row-letter.letter-correct"));
    const elsewhere = Array.from(document.querySelectorAll(".Row-letter.letter-elsewhere"));
    const correctPositions = correct.map(elem => [
        elem.innerHTML, 
        Array.from(elem.parentNode.children)
            .findIndex(value => value.classList.contains('letter-correct')) 
    ]);
    
    const mustHaveLetters = elsewhere.map(elem => elem.innerHTML);

    const lettersLeft = [
        ...mustHaveLetters, 
        ...Array.from(alphabet)
            .filter(letter => !hintWords
                .reduce((accumulator, word) => accumulator += word)
                .includes(letter) 
        ), 
        ...correct.map(elem => elem.innerHTML)
    ];

     const candidates = allWords
        .filter(word => {
            for(const letter of mustHaveLetters) {
                if(!word.includes(letter)){
                    return false;
                }
            }

            return true;
        });

    const left = candidates.filter(word => {
            for(const letter of correctPositions) {
                if(word[letter[1]] !== letter[0]) {
                    return false;
                }
            }
            return true;
        });


    const final = left
        .filter(word => {
            for(const letter of word) {
                if(!lettersLeft.includes(letter)) {
                    return false;
                }
            }

            return true;
        });


     typeToGameKeyboard(final[0] || allWords[0]);

     setTimeout(() => {
        if(
            document.querySelectorAll(".modal_finish.poof.active>.top")[0]?.innerHTML === "You Win!"
        ) {
            nWins++;
        } else {
            nLosses++;
        }

        console.log(`${nWins} wins ${nLosses} losses`);

        if(nWins < 100) {
            document.querySelector(".restart_btn > button").click();
            solve()
        } else {
            console.timeEnd("wordle-tas");
        }
     }, 10);
}

    
    


fetch(url)
    .then(reponse => {
        reponse.json().then(words => {
            allWords = words.filter(word => word.length === wordLength);
            console.time("wordle-tas")
            solve();
        });
    });