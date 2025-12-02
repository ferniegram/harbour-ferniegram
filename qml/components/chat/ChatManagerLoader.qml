import QtQuick 2.0
import App.Logic 1.0

QtObject {
    id: root

    property var chatManager
    property bool doDestroy
    property var parent
    property bool doInit: true

    property Component chatManagerComponent: Component {
        ChatManager {
            tdlib: tdLibWrapper
        }
    }

    signal ready

    function init() {
        if (typeof chatManager === 'undefined') {
            doDestroy = true

            var incubator = chatManagerComponent.incubateObject(parent)
            incubator.onStatusChanged = function(status) {
                // Hopefully avoid memory leaks with this:
                if (!root) incubator.object.destroy()

                if (status === Component.Ready) {
                    root.chatManager = incubator.object
                    ready()
                }
            }
        } else {
            doDestroy = false
            ready()
        }
    }

    Component.onCompleted: if (doInit) init()

    Component.onDestruction:
        if (doDestroy && chatManager)
            chatManager.destroy()
}
