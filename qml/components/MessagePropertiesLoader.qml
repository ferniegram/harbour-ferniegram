import QtQuick 2.0

QtObject {
    id: loader
    property var chatId
    property var messageId

    property var properties: ({stub: true})

    property bool _messagePropertiesLoading
    property var __c1: Connections {
        target: tdLibWrapper
        onMessagePropertiesReceived: if (loader.messageId === messageId) {
                                         loader.properties = messageProperties
                                         loader._messagePropertiesLoading = false
                                     }
    }

    function load() {
        if (_messagePropertiesLoading || !properties.stub) return
        tdLibWrapper.getMessageProperties(loader.chatId, loader.messageId)
        _messagePropertiesLoading = true
    }
    function reset() {
        properties = {stub: true}
    }
}
