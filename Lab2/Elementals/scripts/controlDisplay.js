import { dataElementals } from "./dataElementals.js";

export function previousElements() {

    const nextElementsButton = document.querySelector('.next-elements_button-off');

    nextElementsButton.className = 'next-elements_button';
    this.className = 'previous-elements_button-off';
    updateDisplay(0);
}

export function nextElements() {

    const previousElementsButton = document.querySelector('.previous-elements_button-off');

    previousElementsButton.className = 'previous-elements_button';
    this.className = 'next-elements_button-off';
    updateDisplay(dataElementals.length / 2);
}

function updateDisplay(displayElement) {

    const elements = document.querySelector('.elements-box');

    for (let i = 0; i < elements.childNodes.length; i++) {

        if (sessionStorage.getItem('already_' + dataElementals[i + displayElement].name) == 'true') {

            elements.childNodes[i].firstElementChild.src = dataElementals[i + displayElement].src;
            elements.childNodes[i].firstElementChild.name = dataElementals[i + displayElement].name;
            if (elements.childNodes[i].childNodes.length == 1) {
                const tegNameElement = document.createElement('h3');
                tegNameElement.className = 'name-element';
                tegNameElement.textContent = dataElementals[i + displayElement].tagName;
                elements.childNodes[i].appendChild(tegNameElement);
            } else {
                elements.childNodes[i].lastElementChild.textContent = dataElementals[i + displayElement].tagName;
            }
            elements.childNodes[i].className = 'element';

        } else {

            console.log('lal');
            elements.childNodes[i].firstElementChild.src = 'images/unguessed.svg';
            elements.childNodes[i].firstElementChild.name = 'unguessed';

            if (elements.childNodes[i].childNodes.length > 1) {
                elements.childNodes[i].removeChild(elements.childNodes[i].lastElementChild);
            }

            elements.childNodes[i].className = 'unguessed-element';
        }
    }
}