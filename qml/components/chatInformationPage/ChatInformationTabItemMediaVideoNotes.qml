import QtQuick 2.0
import WerkWolf.Fernschreiber 1.0

ChatInformationTabItemMediaBase {
    model: chatManager.videoNoteMessagesModel
    viewModel: InvertedProxyModel {
        sourceModel: model
    }
}