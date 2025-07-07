import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.WebView 1.0

FullscreenContentPage {
    allowedOrientations: Orientation.All

    property var linkPreviewType: ({})

    MouseArea {
        width: parent.width
        anchors.bottom: webView.top
        onClicked: closeButton.enabled = !closeButton.enabled
    }

    WebView {
        id: webView
        anchors.centerIn: parent
        url: linkPreviewType.url

        width: parent.width > parent.height ? (parent.height / (linkPreviewType.height / linkPreviewType.width)) : parent.width
        height: parent.width <= parent.height ? (parent.width / (linkPreviewType.width / linkPreviewType.height)) : parent.height
    }

    MouseArea {
        width: parent.width
        anchors {
            top: webView.bottom
            bottom: parent.bottom
        }
        onClicked: closeButton.enabled = !closeButton.enabled
    }

    IconButton {
       id: closeButton
       icon.source: "image://theme/icon-m-cancel?" + (pressed
                    ? Theme.highlightColor
                    : Theme.lightPrimaryColor)
       onClicked: pageStack.pop()
       anchors {
           right: parent.right
           top: parent.top
           margins: Theme.horizontalPageMargin
       }
       opacity: enabled ? 1 : 0
       Behavior on opacity { FadeAnimator {} }
       onEnabledChanged: if (enabled) hideCloseButtonTimer.start()
                         else hideCloseButtonTimer.stop()
    }

    Timer {
        id: hideCloseButtonTimer
        running: true
        interval: 3000
        onTriggered: closeButton.enabled = false
    }
}
