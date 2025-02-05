//Сделать так, чтобы не промаргивало(Done)
//Избавиться от глобальных переменных, разделить логику и визуализацию игры
//Чтобы уже появлющиеся слова не показывались

let countTries = 0;
let correctLettersCount = 0;
let lastHangmanCount = 0;
let secretWord;
let gameStatus = "None";

//получение рандомного числа
function getRandomNumber(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}

//получение слова и подсказки
function getWordAndTip() {
    let saveWordsAndTips = [];
    saveWordsAndTips = wordsAndTips;
    const {word, tip} = saveWordsAndTips[getRandomNumber(0, saveWordsAndTips.length)]
    const actionBox = document.querySelector('.action-box');
    const displayBox = document.querySelector('.display-box');

    const insertWord = document.createElement('div');
    insertWord.className = 'word';
    insertWord.id = 'word';
    for (item in word) {
        const letter = document.createElement("li");
        letter.className = "letter";
        insertWord.appendChild(letter);
    }

    secretWord = word;
    
    const insertTip = document.createElement('div');
    insertTip.id = 'tip';
    const tipInDoc = document.createElement("h2");
    tipInDoc.textContent = "Подсказка: " + tip;
    insertTip.appendChild(tipInDoc);

    console.log(insertWord);
    displayBox.appendChild(insertWord);
    actionBox.appendChild(insertTip);
    return saveWordsAndTips;
}

//отрисовка стартовой игровой доски
function startGame() {

    const body = document.querySelector('body');
    const gameBorder = document.createElement('div');
    const displayBox = document.createElement('div');
    const hangman = document.createElement('img');
    const actionBox = document.createElement('div');
    gameBorder.className = 'game-border';
    displayBox.className = 'display-box';
    displayBox.id = 'display-box';
    hangman.id = 'hangman';
    hangman.src = 'images/hangman_0.svg';
    actionBox.className = 'action-box';
    gameBorder.appendChild(displayBox);
    gameBorder.appendChild(actionBox);
    body.appendChild(gameBorder);
    let saveWordsAndTips = getWordAndTip();
    
    console.log(saveWordsAndTips);
    saveWordsAndTips.splice(0, 1);
    console.log(saveWordsAndTips);

    displayBox.appendChild(hangman);

    const keyboard = document.createElement('div');
    keyboard.className = 'keyboard';
    keyboard.id = 'keyboard';
    const alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
    for (let i = 0; i < alphabet.length; i++) {
        const button = document.createElement('button');
        button.textContent = alphabet[i];
        button.className = "alphabet";
        keyboard.appendChild(button);
    }

    const lives = document.createElement('div');
    lives.className = 'lives';
    const textLives = document.createElement('h2');
    textLives.textContent = 'Жизни:';
    const hearts = document.createElement('div');
    hearts.className = 'hearts';
    hearts.id = 'hearts';
    const heartsCount = 7;
    for (let i = 0; i < heartsCount; i++) {
        const heart = document.createElement('img');
        heart.src = "images/heart.svg";
        heart.className = "heart";
        hearts.appendChild(heart);
    }
    lives.appendChild(textLives);
    lives.appendChild(hearts);

    actionBox.appendChild(keyboard);
    actionBox.appendChild(lives);
    gameBorder.appendChild(displayBox);
    gameBorder.appendChild(actionBox);
    body.appendChild(gameBorder);

    const clickButton = document.querySelectorAll('.alphabet');

    clickButton.forEach(clickButtonItem => {
        clickButtonItem.addEventListener('click', insertLetter, {
            once: true
        })
    }); 
}

//вся логика работы с буквами и отрисовкой виселицы.
function insertLetter()
{
    
    const hearts = document.getElementById('hearts');
    let correctLetter = false;
    const uniqueLettersCount = new Set(secretWord).size;
    console.log(lives, correctLettersCount, countTries, uniqueLettersCount);
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
        lastHangmanCount++;
        lastHangman.src = 'images/hangman_' + lastHangmanCount + '.svg';
        console.log(hearts.lastElementChild);
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
        buttonResult.className = 'buttonResult';
        result.className = 'resultContent';
        result.appendChild(failureText);
        result.appendChild(secretWordText);
        result.appendChild(failureImg);
        result.appendChild(buttonResult);
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

//перезагрузка игры
function refreshGame () {
    const body = document.querySelector('body');
    body.innerHTML = '';
    const lives = hearts.childElementCount;
    countTries = 0;
    correctLettersCount = 0;
    lastHangmanCount = 0;
    secretWord;
    gameStatus = "None";
    startGame(lives);
}

startGame();


