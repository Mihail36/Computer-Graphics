import { addCombinationElement } from "./addCombinationElement.js";
import { deleteLastCombinationElement } from "./deleteLastElement.js";

export function game() {

    const elementalsFromDisplay = document.querySelectorAll('.icon-element');

    elementalsFromDisplay.forEach(elemental => {
        elemental.addEventListener('click', addCombinationElement);
    })

    deleteLastCombinationElement();
}