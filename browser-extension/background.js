chrome.runtime.onInstalled.addListener(() => {
    //save initial values
    chrome.storage.local.set({
        hintWords: ["müden","pasch","wölbt","zuvor","käfig"]
    })

    chrome.storage.local.set({
        alphabet: "abcdefghijklmnopqrstuvwxyzäöü"
    })
})