import QtQuick 2.0
import Sailfish.Silica 1.0
import App.Logic 1.0
import ".."

SilicaListView {
    model: chatManager.topicsModel

    delegate: PhotoTextsListItem {
        width: parent.width
        primaryText.text: name

        onClicked: pageStack.push(topicMessagesPage, {chatId: chatInformation.id, forumTopicId: forum_topic_id})
    }

    Component {
        id: topicMessagesPage
        Page {
            property alias chatId: topicMessagesModel.chatId
            property alias forumTopicId: topicMessagesModel.forumTopicId

            MessagesView {
                anchors.fill: parent
                messagesModel: topicMessagesModel

                ForumTopicMessagesModel {
                    id: topicMessagesModel
                    tdlib: tdLibWrapper
                    forumTopicsModel: chatManager.topicsModel
                }
            }
        }
    }
}
