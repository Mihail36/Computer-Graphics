import { dataElementals } from "./dataElementals.js";
import { getFinishMessage } from "./getFinishMessage.js";

export function addResultOfCombination(combinationNotFound, combinationName) {

    if (combinationNotFound) {
        generateResults(combinationName, combinationNotFound);
    } else {
        if (isAldredyDone(combinationName)) {
            generateResults(combinationName, combinationNotFound);
        } else {
            generateResults(combinationName, combinationNotFound);
        }
    }

}

function isAldredyDone(combinationName) {

    let isAlready;

    if (sessionStorage.getItem('already_' + combinationName) == 'true') {
        isAlready = true;
    } else {
        isAlready = false;
    }

    return isAlready;
}

function generateResults(combinationName, combinationNotFound) {

    const allCombinationElements = document.querySelectorAll('.combination-element');
    const body = document.querySelector('body');
    const messageResultBox = document.createElement('div');
    const messageText = document.createElement('h2');
    let displayElement = document.createElement('div');
    const messageButton = document.createElement('button');
    const backOfMessage = document.createElement('img');


    messageText.className = 'message-text';
    messageResultBox.className = 'message-box';
    messageButton.textContent = 'Продолжить';

    backOfMessage.src = 'images/unguessed.svg';
    backOfMessage.className = 'back-of-message';

    allCombinationElements.forEach(element => {
        element.style.opacity = 0;
        element.style.position = 'relative';
        element.firstElementChild.style.cursor = 'default';
    })

    if (combinationNotFound) {

        const gifMessage = document.createElement('img');

        gifMessage.className = 'gif-message';
        gifMessage.src = 'gifs/wrong.gif';

        messageText.textContent = 'Такой комбинации не существует :(';
        messageButton.className = 'message-button_wrong-combination';

        messageResultBox.appendChild(messageText);
        messageResultBox.appendChild(gifMessage);
        messageResultBox.appendChild(messageButton);

    } else {

        messageButton.className = 'message-button';
        displayElement = getNewElement(combinationName);
        displayElement.className = 'display-element';

        if (isAldredyDone(combinationName)) {

            messageText.textContent = 'Такой элемент уже имеется :)';

        } else {

            messageText.textContent = 'Вы собрали новый элемент :)';
            messageButton.addEventListener('click', () => {
                updateDisplay(combinationName, displayElement);
            })

        }

        messageResultBox.appendChild(messageText);
        messageResultBox.appendChild(displayElement);
        messageResultBox.appendChild(messageButton);
    }


    messageButton.addEventListener('click', () => {
        if (checkFinish()) {
            body.innerHTML = '';
            getFinishMessage();
        } else {
            body.removeChild(body.lastElementChild);
            body.removeChild(body.lastElementChild);
            allCombinationElements.forEach(element => {
                element.style.opacity = 1;
                element.firstElementChild.style.cursor = 'pointer';
                element.style.position = 'absolute';
            })
        }
    })

    combinationSound();
    body.appendChild(backOfMessage);
    body.appendChild(messageResultBox);

}

function getNewElement(combinationName) {
    const newElement = document.createElement('div');
    dataElementals.forEach(elemental => {
        if (combinationName == elemental.name) {
            const iconElement = document.createElement('img');
            const nameElement = document.createElement('h3');

            iconElement.className = 'icon-element';
            iconElement.style.cursor = 'default';
            iconElement.src = elemental.src;

            nameElement.className = 'name-element';
            nameElement.textContent = elemental.tagName;

            newElement.appendChild(iconElement);
            newElement.appendChild(nameElement);

        }
    })
    return newElement;
}

function updateDisplay(combinationName) {

    const elements = document.querySelector('.elements-box');
    let displayElement;

    if (elements.childNodes[0].firstElementChild.name == 'water') {
        displayElement = 0;
    } else {
        displayElement = dataElementals.length / 2;
    }

    for (let i = 0; i < elements.childNodes.length; i++) {

        if (dataElementals[i + displayElement].name == combinationName) {

            elements.childNodes[i].firstElementChild.src = dataElementals[i + displayElement].src;
            elements.childNodes[i].firstElementChild.name = dataElementals[i + displayElement].name;
            const tegNameElement = document.createElement('h3');
            tegNameElement.className = 'name-element';
            tegNameElement.textContent = dataElementals[i + displayElement].tagName;
            elements.childNodes[i].appendChild(tegNameElement);
            elements.childNodes[i].className = 'element';
        }
        sessionStorage.setItem('already_' + combinationName, true);
    }
}

function checkFinish() {

    let countGuessedElements = 0;

    for (let i = 0; i < dataElementals.length; i++) {
        if (sessionStorage.getItem('already_' + dataElementals[i].name) == 'true') {
            countGuessedElements++;
        }
    }

    if (countGuessedElements == dataElementals.length) {
        return true;
    } else {
        return false;
    }
}

function combinationSound() {
    var audio = new Audio();
    audio.src = 'combination_sound.mp3';
    audio.autoplay = true;
}