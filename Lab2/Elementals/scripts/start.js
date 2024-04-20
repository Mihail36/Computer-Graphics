import { dataElementals } from "./dataElementals.js";
import { nextElements, previousElements } from "./controlDisplay.js";

export function start() {

    document.ondragstart = function() {
        return false;
    };

    const displayBox = document.querySelector('.display-box');
    const textElements = document.createElement('h2');
    const controlElementsBox = document.createElement('div');
    const previousElementsButton = document.createElement('button');
    const elementBox = document.createElement('div');
    const nextElementsButton = document.createElement('button');

    textElements.className = 'text-elements';
    textElements.textContent = 'Открытые элементы';

    previousElementsButton.className = 'previous-elements_button-off';
    previousElementsButton.textContent = '<';

    previousElementsButton.addEventListener('click', previousElements);

    elementBox.className = 'elements-box';
    nextElementsButton.className = 'next-elements_button';
    nextElementsButton.textContent = '>';

    nextElementsButton.addEventListener('click', nextElements);

    dataElementals.forEach(function(item, index) {
        const element = document.createElement('div');
        const iconElement = document.createElement('img');

        if (item.variantsCombinations == '') {
            const nameElement = document.createElement('h3');

            iconElement.className = 'icon-element';
            iconElement.name = item.name;
            iconElement.src = item.src;
            nameElement.className = 'name-element';
            nameElement.textContent = item.tagName;
            element.className = 'element';

            element.appendChild(iconElement);
            element.appendChild(nameElement);
            elementBox.appendChild(element);
            sessionStorage.setItem('already_' + item.name, true);
        } else {
            if (index < dataElementals.length / 2) {

                iconElement.className = 'icon-element';
                iconElement.name = 'unguessed';
                iconElement.src = 'images/unguessed.svg';
                element.className = 'unguessed-element';

                element.appendChild(iconElement);
                elementBox.appendChild(element);

            }
            sessionStorage.setItem('already_' + item.name, false);
        }
    })

    controlElementsBox.className = 'control-elements-box'

    controlElementsBox.appendChild(previousElementsButton);
    controlElementsBox.appendChild(nextElementsButton);
    displayBox.appendChild(textElements);
    displayBox.appendChild(controlElementsBox);
    displayBox.appendChild(elementBox);
}