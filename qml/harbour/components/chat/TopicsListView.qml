import QtQuick 2.0
import Sailfish.Silica 1.0
import App.Logic 1.0
import ".."

import "../../js/twemoji.js" as Emoji
import "../../js/functions.js" as Functions

SilicaListView {
    model: chatManager.topicsModel

    BusyLabel {
        running: count == 0
    }

    delegate: PhotoTextsListItem {
        width: parent.width

        property bool showDraft: !!draft_message_text && draft_message_date > last_message_date
        property string previewText: showDraft ? draft_message_text : last_message_text

        primaryText.text: name
        prologSecondaryText.text: showDraft ? "<i>"+qsTr("Draft")+"</i>" : (last_message_sender_id ? (last_message_sender_id !== ownUserId ? Emoji.emojify(Functions.getUserName(tdLibWrapper.getUserInformation(last_message_sender_id)), Theme.fontSizeExtraSmall) : qsTr("You")) : "")
        secondaryText.text: previewText ? Emoji.emojify(utilities.fixReservedHtmlCharacters(previewText), Theme.fontSizeExtraSmall) : "<i>" + qsTr("No message in this topic.") + "</i>"
        minithumbnail: showDraft ? null : last_message_minithumbnail
        tertiaryText.text: showDraft ? Functions.getDateTimeElapsed(draft_message_date) : (last_message_date ? (last_message_date.length === 0 ? "" : Functions.getDateTimeElapsed(last_message_date) + Emoji.emojify(last_message_status, tertiaryText.font.pixelSize)) : "")

        unreadCount: unread_count
        unreadReactionCount: unread_reaction_count
        unreadMentionCount: unread_mention_count
        isPinned: is_pinned
        muted: notification_settings.mute_for > 0

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
                topicId: {'@type': 'messageTopicForum', 'forum_topic_id': forumTopicId}

                ForumTopicMessagesModel {
                    id: topicMessagesModel
                    tdlib: tdLibWrapper
                    forumTopicsModel: chatManager.topicsModel
                }
            }
        }
    }
}
