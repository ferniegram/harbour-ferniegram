import QtQuick 2.0
import Sailfish.Silica 1.0
import "private"

Item {
    id: root
    property alias icon: icon
    property alias text: label.text
    property alias direction: row.layoutDirection

    property real size: 1
    width: parent.itemWidth * size
    height: Theme.itemSizeSmall

    property bool _useIconOnly: parent._checkIconOnly(size)
    property bool _useShort: parent._checkShort(size)
    property string shortText
    property string longText

    property bool _calculateWidth: true
    onVisibleChanged: if (parent.calculateItemWidth && _calculateWidth) parent.calculateItemWidth()

    property bool down
    property bool highlighted
    property bool _invertColors
    signal clicked

    property alias _menuItem: label
    property alias _content: row

    Row {
        id: row
        width: icon.width + label.width
        spacing: (icon.visible && label.visible) ? Theme.paddingMedium : 0
        anchors.centerIn: parent
        Icon {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            visible: !!source
            opacity: enabled ? 1.0 : Theme.opacityLow
        }
        FadeableHorizontalMenuItem {
            id: label
            width: !visible ? 0 : Math.min(implicitWidth, root.width - icon.width - parent.spacing)
            anchors.verticalCenter: parent.verticalCenter
            visible: !_useIconOnly && !!text
            text: _useShort ? shortText : longText
        }
    }
}
