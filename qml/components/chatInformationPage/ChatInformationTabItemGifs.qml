import QtQuick 2.0
import WerkWolf.Fernschreiber 1.0

ChatInformationTabItemMediaBase {
    model: chatManager.animationsMessagesModel
    viewModel: InvertedProxyModel {
        sourceModel: model
    }
}