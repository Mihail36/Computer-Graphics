export function getFinishMessage() {

    const body = document.querySelector('body');

    const messageResultBox = document.createElement('div');
    const messageText = document.createElement('h2');
    const messageButton = document.createElement('button');
    const backOfMessage = document.createElement('img');

    messageText.className = 'message-text';
    messageResultBox.className = 'message-box';

    backOfMessage.src = 'images/unguessed.svg';
    backOfMessage.className = 'back-of-message';

    messageText.textContent = 'Поздравляю, вы собрали все элементы!!!';
    messageButton.className = 'message-button_finish';

    messageButton.textContent = 'Заново?';

    messageResultBox.appendChild(messageText);
    messageResultBox.appendChild(messageButton);

    messageButton.addEventListener('click', () => {
        location.reload();
    })

    body.appendChild(backOfMessage);
    body.appendChild(messageResultBox);

}