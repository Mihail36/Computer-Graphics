import { deleteLastCombinationElement } from "./deleteLastElement.js";
import { dataElementals } from "./dataElementals.js";
import { generateResultCombinationElement } from "./generateResultCombinationElement.js";
import { addResultOfCombination } from "./ResultOfCombination.js";
import { startDragAndDrop } from "./dragAndDrop.js";

export function checkCombination(element) {
    const allCombinationElements = document.querySelectorAll('.combination-element');
    allCombinationElements.forEach(elemental => {

        if (elemental != element) {
            getCombinationResult(element, elemental)
        }
    })
}

function coordsOfCombination(element, elemental) {

    element.offsetBottom = element.offsetTop + element.offsetHeight / 2 - element.lastElementChild.offsetHeight;
    element.offsetRight = element.offsetLeft + element.offsetWidth / 2;
    elemental.offsetBottom = elemental.offsetTop + elemental.offsetHeight / 2 - elemental.lastElementChild.offsetHeight;
    elemental.offsetRight = elemental.offsetLeft + elemental.offsetWidth / 2;

    return !((element.offsetBottom < elemental.offsetTop) || (element.offsetTop > elemental.offsetBottom) ||
        (element.offsetRight < elemental.offsetLeft) || (element.offsetLeft > elemental.offsetRight))
};

function getCombinationResult(element, elemental) {

    const combinationBox = document.querySelector('.combination-box');

    if (coordsOfCombination(element, elemental)) {

        const combinationName = element.firstElementChild.name + '+' + elemental.firstElementChild.name;

        let combinationNotFound = true;
        let nameNewElement;

        dataElementals.forEach(elem => {
            elem.variantsCombinations.forEach(combination => {
                if (combination == combinationName) {
                    nameNewElement = elem.name;
                    combinationNotFound = false;
                }
            })
        })

        if (!combinationNotFound) {

            const coordX = (element.offsetLeft + elemental.offsetLeft) / 2;
            const coordY = (element.offsetTop + elemental.offsetTop) / 2;

            combinationBox.removeChild(element);
            combinationBox.removeChild(elemental);

            combinationBox.outerHTML = combinationBox.outerHTML;

            generateResultCombinationElement(nameNewElement);

            const reloadCombinationBox = document.querySelector('.combination-box');

            reloadCombinationBox.lastElementChild.style.top = coordY + 'px';
            reloadCombinationBox.lastElementChild.style.left = coordX + 'px';

            deleteLastCombinationElement();

            addResultOfCombination(combinationNotFound, nameNewElement);

        } else {

            combinationBox.removeChild(element);
            combinationBox.removeChild(elemental);

            combinationBox.outerHTML = combinationBox.outerHTML;

            startDragAndDrop();

            addResultOfCombination(combinationNotFound, nameNewElement);

            deleteLastCombinationElement();
        }
    }
}