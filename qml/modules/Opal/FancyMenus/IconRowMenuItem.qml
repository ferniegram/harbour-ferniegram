import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property bool down
    signal clicked
    property alias icon: icon

    property real size: 1
    width: parent.itemWidth * size
    height: Theme.itemSizeSmall//icon.height

    Icon {
        id: icon
        opacity: parent.enabled ? 1.0 : Theme.opacityLow
        anchors.centerIn: parent
    }

    onVisibleChanged: parent.calculateItemWidth()
}
