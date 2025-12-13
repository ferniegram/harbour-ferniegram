import QtQuick 2.0
import org.asteroid.controls 1.0
import "../js/debug.js" as Debug
import "../js/twemoji.js" as Emoji

StatusPage {
    property string defaultIcon: 'ios-information-circle-outline'

    function reset() {
        text = ''
        icon = defaultIcon
        clickedAction = null
        visible = false
    }

    property var clickedAction // using signals would be harder

    function show(message, onClicked, buttonText, asteroidMessage, asteroidIcon) {
        text = asteroidMessage || message
        clickedAction = onClicked
        icon = asteroidIcon || defaultIcon
        visible = true
        resetTimer.restart()
    }

    Timer {
        id: resetTimer
        interval: 3500
        onTriggered: reset()
    }

    onClicked: {
        if (clickedAction)
            clickedAction()
        reset()
    }
}