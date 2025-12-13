import QtQuick 2.0
import App.Logic 1.0
import "../js/functions.js" as Functions

QtObject {
    property Connections c1: Connections {
        target: tdLibWrapper
        onOpenFileExternally: Qt.openUrlExternally(filePath)
        onTgUrlFound: Functions.handleLink(tgUrl)
        onErrorReceived: Functions.handleErrorMessage(code, message, extra)
        onServiceNotificationReceived: appNotification.show(utilities.getMessageContentText(content, true))
    }

    Component.onCompleted: {
        Functions.setGlobals({
            tdLibWrapper: tdLibWrapper,
            appNotification: appNotification,
            utilities: utilities,
        })
    }
}
