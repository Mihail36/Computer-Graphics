import { dataElementals } from "./dataElementals.js";
import { startDragAndDrop } from "./dragAndDrop.js";

function randomNumber(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}

function generateRandomPlace(element, parent) {

    const page = document.querySelector('body');

    const minX = page.getBoundingClientRect().width - parent.getBoundingClientRect().width;
    const minY = page.getBoundingClientRect().height - parent.getBoundingClientRect().height;

    const maxX = page.getBoundingClientRect().width - parent.getBoundingClientRect().width / 4;
    const maxY = parent.getBoundingClientRect().height - parent.getBoundingClientRect().height / 4;

    const coordinateX = randomNumber(minX, maxX);
    const coordinateY = randomNumber(minY, maxY);

    element.style.position = 'absolute';
    element.style.left = coordinateX + 'px';
    element.style.top = coordinateY + 'px';
}

export function addCombinationElement() {

    const combinationBox = document.querySelector('.combination-box');
    const combinationElement = this.parentNode.cloneNode(true);
    const oldCombinationElements = document.querySelectorAll('.combination-element');
    let newElementCount = 0;
    oldCombinationElements.forEach(oldElement => {
        if (oldElement.name == this.name) {
            newElementCount += 1;
        }
    })
    dataElementals.forEach(elemental => {
        if (this.name == elemental.name) {
            combinationElement.className = 'combination-element';
            combinationElement.name = this.name;
            combinationElement.id = this.name + '_' + newElementCount;
            generateRandomPlace(combinationElement, combinationBox);
            combinationElement.firstElementChild.style.cursor = 'pointer';
            combinationBox.appendChild(combinationElement);
        }
    })
    startDragAndDrop();
}