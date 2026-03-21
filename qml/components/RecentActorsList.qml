import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    width: childrenRect.width

    property real paddingDifference: Theme.paddingMedium
    property bool inverted
    property alias model: reactorsRepeater.model
    property alias count: reactorsRepeater.count
    property bool userIds // specifies if the model contains user ids instead of messageSender objects

    Repeater {
        id: reactorsRepeater
        ProfileThumbnail {
            id: reactorProfileThumbnail

            height: parent.height
            width: height
            x: paddingDifference * (inverted ? reactorsRepeater.count - index - 1 : index)

            photoData: isChat
                       ? tdLibWrapper.getChat(modelData.chat_id).photo.small
                       : reactorUserInfoLoader.info.profile_photo.small
            replacementStringHint: isChat
                                   ? tdLibWrapper.getChat(modelData.chat_id).title
                                   : utilities.getUserName(reactorUserInfoLoader.info)

            property bool isChat: !userIds && modelData['@type'] === 'messageSenderChat'

            TDLibUser {
                id: reactorUserInfoLoader
                userId: isChat ? 0 : (userIds ? modelData : modelData.user_id)
            }

            Connections {
                // FIXME: this can be improved (maybe use QQmlPropertyMaps for storing chat info?):
                target: isChat ? tdLibWrapper : null
                onChatTitleUpdated:
                    if (chatId === modelData.chat_id)
                        reactorProfileThumbnail.replacementStringHint = title
                onChatPhotoUpdated:
                    if (chatId === modelData.chat_id)
                        reactorProfileThumbnail.photoData = photo.small
            }
        }
    }
}
