export function deleteLastCombinationElement() {
    const buttonDelete = document.querySelector('.delete-element');
    const combinationBox = document.querySelector('.combination-box');
    buttonDelete.addEventListener('click', deleteElement => {
        if (combinationBox.childElementCount != 0) {
            combinationBox.removeChild(combinationBox.lastElementChild);
        }
    })
}