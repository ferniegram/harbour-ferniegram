import QtQuick 2.6
import org.asteroid.controls 1.0
import App.Logic 1.0
import "../components"

Item {
    PageHeader {
        id: header
        text: tdLibWrapper.connectionState || qsTr("Ferniegram")
    }

    // TODO!

    /*PageDot {
        anchors {
            top: header.bottom
            anchors.topMargin: 3*Dims.iconButtonMargin
            horizontalCenter: parent.horizontalCenter
        }
        height: Dims.h(3)
        currentIndex: listView.currentIndex
        dotNumber:
    }

    ListView {
        id: listView
        anchors.fill: parent
        model:

        highlight: Item { width: app.width }
        clip: true
        snapMode: ListView.SnapToItem
        orientation: Qt.Horizontal

        delegate: Item {

        }
    }*/
}
