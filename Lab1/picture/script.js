const pageWidth = 1920
const pageHeight = 1080

function dragAndDrop(element)
{
    let shiftX = 0
    let shiftY = 0

    function onMouseDown(event)
    {
        shiftX = event.clientX - element.getBoundingClientRect().left
        shiftY = event.clientY - element.getBoundingClientRect().top

        document.addEventListener('mousemove', onMouseMove)
        document.addEventListener('mouseup', onMouseUp)
    }

    function onMouseMove(event)
    {
        let positionX = event.pageX - shiftX
        let positionY = event.pageY - shiftY

        const minBorderX = 0
        const maxBorderX = pageWidth - element.getBoundingClientRect().width

        const minBorderY = 0
        const maxBorderY = pageHeight - element.getBoundingClientRect().height

        positionX = positionX < minBorderX ? minBorderX : positionX
        positionX = positionX > maxBorderX ? maxBorderX : positionX

        positionY = positionY < minBorderY ? minBorderY : positionY
        positionY = positionY > maxBorderY ? maxBorderY : positionY

        element.style.left = positionX + 'px'
        element.style.top = positionY + 'px'
    }

    function onMouseUp()
    {
        document.removeEventListener('mousemove', onMouseMove)
        document.removeEventListener('mouseup', onMouseUp)
    }

    element.style.position = 'absolute'
    element.onmousedown = onMouseDown
}

const image = document.getElementById('image')

dragAndDrop(image)