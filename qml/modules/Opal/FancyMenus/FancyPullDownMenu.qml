import QtQuick 2.0
import Sailfish.Silica 1.0
import 'private/Util.js' as Util

PullDownMenu {
    id: pulleyMenu
    property Item _highlightBar
    property bool listItem
    //property bool down: !_atInitialPosition
    //property var lastKnownXPos
    property int originalHighlightBarX

    Component.onCompleted: {
        _highlightBar = Util.findHighlightRectangle(pulleyMenu)
        originalHighlightBarX = _highlightBar.x
    }

    onPositionChanged: {
        //lastKnownXPos = mouse.x
        //console.log("Changed(TM)")
        // propagate x-position since jolla's contextmenu doesn't remember it.
        if (_highlightBar.highlightedItem && _highlightBar.highlightedItem.hasOwnProperty("xPos"))
            _highlightBar.highlightedItem.xPos = _contentColumn.mapFromItem(pulleyMenu, mouse.x, mouse.y).x
    }

    function resetHighlightbar() {
        if (!_highlightBar) return
        _highlightBar.x = originalHighlightBarX // 0
        _highlightBar.width = width
    }

    on_AtInitialPositionChanged: if(_atInitialPosition) resetHighlightbar()

    function _highlightMenuItem(parentItem, yPos) {
        //console.trace()
        var child = _quickSelectMenuItem(parentItem, yPos)
        if (child) {
            return
        }

        //console.log(lastKnownXPos,mouseX,mouseY)
        //console.log(_dragDistance)
        //var xPos = lastKnownXPos - _contentColumn.x
        var xPos = width / 2

        // Only try to highlight if we haven't dragged to the final position
        if (!flickable.dragging || !_atFinalPosition) {
            child = Util.childAt(parentItem, xPos, yPos)
        }
        while (child) {
            if (child && child.hasOwnProperty("__silica_menuitem") && child.enabled && child.visible) {
                menuItem = child
                //xPos = parentItem.mapToItem(child, xPos, yPos).x
                yPos = parentItem.mapToItem(child, xPos, yPos).y
                _highlightBar.highlight(menuItem, pulleyMenu, _dragDistance <= _contentEnd && !_atFinalPosition)
                break
            }
            parentItem = child
            //xPos = parentItem.mapToItem(child, xPos, yPos).x
            yPos = parentItem.mapToItem(child, xPos, yPos).y
            child = Util.childAt(parentItem, xPos, yPos)
        }
        if (!child) {
            menuItem = null
            _highlightBar.clearHighlight()
        }
    }
}
