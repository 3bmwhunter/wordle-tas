document.getElementById("add-button").addEventListener("click", () => {
    const hintWordContainer = document.getElementById("hint-word-container");
    const inputElement = document.createElement("input");
    hintWordContainer.appendChild(inputElement);
})

document.getElementById("delete-button").addEventListener("click", () => {
    const hintWordContainer = document.getElementById("hint-word-container");
    Array.from(hintWordContainer.childNodes).slice(-1)[0].remove();
})

document.getElementById("save-button").addEventListener("click", () => {
    const alphabet = document.getElementById("alphabet-input").value;
    const hintWords = Array.from(document.getElementById("hint-word-container").childNodes, elem => elem.value)
        .filter(word => word !== undefined && word !== "")

    chrome.storage.local.set({
        alphabet
    })

    chrome.storage.local.set({
        hintWords
    })
})


chrome.storage.local.get(["alphabet"], result => {
    document.getElementById("alphabet-input").value = result.alphabet
})

chrome.storage.local.get(["hintWords"], result => {
    const hintWords = result.hintWords;
    const hintWordContainer = document.getElementById("hint-word-container");

    for(const word of hintWords) {
        const inputElement = document.createElement("input");
        inputElement.value = word;
        hintWordContainer.appendChild(inputElement);
    }
})

