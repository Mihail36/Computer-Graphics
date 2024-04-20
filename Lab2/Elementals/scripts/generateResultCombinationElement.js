import { dataElementals } from "./dataElementals.js";
import { startDragAndDrop } from "./dragAndDrop.js";

export function generateResultCombinationElement(nameResult) {
    const combinationBox = document.querySelector('.combination-box');

    const combinationElement = document.createElement('div');
    const iconElement = document.createElement('img');
    const nameElement = document.createElement('h3');

    const oldCombinationElements = document.querySelectorAll('.combination-element');

    let newElementCount = 0;

    oldCombinationElements.forEach(oldElement => {
        if (oldElement.firstElementChild.name == nameResult) {
            newElementCount += 1;
        }
    })

    dataElementals.forEach(elemental => {
        if (nameResult == elemental.name) {

            iconElement.className = 'icon-element';
            iconElement.src = elemental.src;
            iconElement.style.cursor = 'pointer';
            iconElement.name = nameResult;
            nameElement.className = 'name-element';
            nameElement.textContent = elemental.tagName;


            combinationElement.className = 'combination-element';
            combinationElement.style.position = 'absolute';
            combinationElement.id = nameResult + '_' + newElementCount;

            combinationElement.appendChild(iconElement);
            combinationElement.appendChild(nameElement);
            combinationBox.appendChild(combinationElement);
        }
        startDragAndDrop();
    })
}