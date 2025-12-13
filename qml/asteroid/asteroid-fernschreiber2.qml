import QtQuick 2.9
import org.asteroid.controls 1.0
import App.Logic 1.0
import "pages"

Application {
    id: app

    centerColor: '#082ba0'
    outerColor: '#1c97df'

    LayerStack {
        id: stack
        firstPage: Comopnent {
            OverviewPage {}
        }
    }

    AppNotification {
        id: appNotification
    }

    MainShared {}

    /*Label {
        id: hello
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        text: "Hello World!"
    }
    Label {
        anchors.top: hello.bottom
        width: parent.width
        wrapMode: Text.Wrap
        text: qsTr("TDLib version %1 (commit hash %2)").arg(tdLibWrapper.options.version).arg(tdLibWrapper.options.commit_hash)
    }*/
}
