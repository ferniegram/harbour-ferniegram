import QtQuick 2.9
import org.asteroid.controls 1.0
import App.Logic 1.0

Application {
    id: app

    centerColor: "#b04d1c"
    outerColor: "#421c0a"

    Label {
        id: hello
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        text: "Hello World!"
    }
    Label {
        anchors.top: hello.bottom
        text: qsTr("TDLib version %1 (commit hash %2)").arg(tdLibWrapper.options.version).arg(tdLibWrapper.options.commit_hash)
    }
}