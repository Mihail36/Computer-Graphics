import { checkCombination } from "./combinationOfElements.js";

export function startDragAndDrop() {

    const combinationElementals = document.querySelectorAll('.combination-element');

    combinationElementals.forEach(elemental => {
        dragAndDrop(elemental);
    })
}

function dragAndDrop(element) {

    const page = document.querySelector('body');

    function mouseDown() {
        element.parentNode.addEventListener('mousemove', mouseMove);
        element.firstElementChild.addEventListener('mouseup', mouseUp);
    }

    function mouseMove(event) {

        element.firstElementChild.style.cursor = 'default';

        let positionX = event.pageX - element.getBoundingClientRect().width / 2;
        let positionY = event.pageY - element.getBoundingClientRect().height / 2;


        const minX = page.getBoundingClientRect().width - element.parentNode.getBoundingClientRect().width;
        const minY = page.getBoundingClientRect().height - element.parentNode.getBoundingClientRect().height;

        const maxX = (page.getBoundingClientRect().width - element.getBoundingClientRect().width) * 0.98;
        const maxY = (page.getBoundingClientRect().height - element.getBoundingClientRect().height) * 1.05;

        if (event.pageX > maxX) {
            positionX = maxX - element.getBoundingClientRect().width;
            mouseUp();
        }
        if (event.pageY > maxY) {
            positionY = maxY - element.getBoundingClientRect().height;
            mouseUp();
        }

        if (event.pageX < minX) {
            positionX = minX;
            mouseUp();
        }

        if (event.pageY < minY) {
            positionY = minY;
            mouseUp();
        }

        element.style.left = positionX + 'px';
        element.style.top = positionY + 'px';
        checkCombination(element);
    }

    function mouseUp() {
        element.parentNode.removeEventListener('mousemove', mouseMove);
        element.firstElementChild.removeEventListener('mouseup', mouseUp);
        element.firstElementChild.style.cursor = 'pointer';
    }
    element.firstElementChild.onmousedown = mouseDown;
}