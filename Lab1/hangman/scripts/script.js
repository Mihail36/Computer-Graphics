let countTries = 0;
let correctLettersCount = 0;
let lastHangmanCount = 0;
let secretWord;
let gameStatus = "None";

function getRandomNumber(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}

function getWordAndTip() {
    const {word, tip} = wordsAndTips[getRandomNumber(0, wordsAndTips.length)];

    const insertWord = document.querySelector('.word');
    for (item in word) {
        const letter = document.createElement("li");
        letter.className = "letter";
        insertWord.appendChild(letter);
    }

    secretWord = word;
    
    const insertTip = document.getElementById('tip');
    const tipInDoc = document.createElement("h2");
    tipInDoc.textContent = "Подсказка: " + tip;
    insertTip.appendChild(tipInDoc);

}

function startGame() {
    
    getWordAndTip();
    
    const keyboard = document.querySelector('.keyboard');
    const alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
    for (let i = 0; i < alphabet.length; i++) {
        const button = document.createElement('button');
        button.textContent = alphabet[i];
        button.className = "alphabet";
        keyboard.appendChild(button);
    }

    const hearts = document.querySelector('.hearts');
    const lives = 7;
    for (let i = 0; i < lives; i++) {
        const heart = document.createElement('img');
        heart.src = "images/heart.svg";
        heart.className = "heart";
        hearts.appendChild(heart);
    }

    const clickButton = document.querySelectorAll('.alphabet');

    clickButton.forEach(clickButtonItem => {
        clickButtonItem.addEventListener('click', insertLetter, {
            once: true
        })
    }); 
}

function insertLetter()
{
    
    let correctLetter = false;
    const uniqueLettersCount = new Set(secretWord).size;
    for (item in secretWord) {

        if (this.innerHTML == secretWord[item]) {
            correctLetter = true;
            word.children[item].textContent = this.innerHTML;
            word.children[item].className = "letter guessed" ;
        }
    }

    const keyboard = document.getElementById('keyboard');
    keyboard.removeChild(this);

    if (!correctLetter) {
        const lastHangman = document.getElementById('hangman');
        const newHangman = document.createElement('img');
        const word = document.getElementById('word');
        displayBox.removeChild(lastHangman);
        lastHangmanCount++;
        newHangman.src = 'images/hangman_' + lastHangmanCount + '.svg';
        newHangman.id = 'hangman';
        displayBox.appendChild(newHangman);
        hearts.removeChild(hearts.lastElementChild);
        countTries++;
    }
    else {
        correctLettersCount++;
    }

    if ((countTries == lives) && !(correctLettersCount == uniqueLettersCount)) {
        gameStatus = "Failure";
    }
    if (!(countTries == lives) && (correctLettersCount == uniqueLettersCount)) {
        gameStatus = "Successful";
    }

    if (gameStatus == "Failure") {
        const gameBorder = document.querySelector(".game-border");
        gameBorder.innerHTML = '';
        const result = document.createElement('div');
        const failureText = document.createElement('h2');
        const secretWordText = document.createElement('h2');
        const failureImg = document.createElement('img');
        const buttonResult = document.createElement('button');
        failureText.textContent = 'К сожалению, поражение.. Попробуйте снова!';
        secretWordText.textContent = 'Загаданное слово: ' + secretWord;
        failureImg.src = 'gifs/defeat_' + getRandomNumber(1, 4) + '.gif';
        failureImg.className = 'gifs';
        buttonResult.textContent = "Заново";
        buttonResult.className = 'buttonResult'
        result.appendChild(failureText);
        result.appendChild(secretWordText);
        result.appendChild(failureImg);
        result.appendChild(buttonResult);
        result.className = 'resultContent';
        gameBorder.appendChild(result);

        const clickButton = document.querySelectorAll('.buttonResult');
        clickButton.forEach(clickButtonItem => {
        clickButtonItem.addEventListener('click', refreshGame, {
            once: true
        })
    });
    }
    else if (gameStatus == "Successful") {
        const gameBorder = document.querySelector(".game-border");
        gameBorder.innerHTML = '';
        const result = document.createElement('div');
        const congratulationText = document.createElement('h2');
        const secretWordText = document.createElement('h2');
        const failureImg = document.createElement('img');
        const buttonResult = document.createElement('button');
        congratulationText.textContent = 'Поздравляю, победа!!!';
        secretWordText.textContent = 'Загаданное слово: ' + secretWord;
        failureImg.src = 'gifs/victory_' + getRandomNumber(1, 4) + '.gif';
        failureImg.className = 'gifs';
        buttonResult.textContent = "Заново";
        buttonResult.className = 'buttonResult'
        result.appendChild(congratulationText);
        result.appendChild(secretWordText);
        result.appendChild(failureImg);
        result.appendChild(buttonResult);
        result.className = 'resultContent';
        gameBorder.appendChild(result);

        const clickButton = document.querySelectorAll('.buttonResult');
        clickButton.forEach(clickButtonItem => {
        clickButtonItem.addEventListener('click', refreshGame, {
            once: true
        })
    });
    }
}

function refreshGame () {
    location.reload();
}

startGame();

const hearts = document.getElementById('hearts');
const displayBox = document.getElementById('display-box');
const lives = hearts.childElementCount;

