/*
    Copyright (C) 2020-21 Sebastian J. Wolf and other contributors

    This file is part of Fernschreiber.

    Fernschreiber is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fernschreiber is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fernschreiber. If not, see <http://www.gnu.org/licenses/>.
*/
import QtQuick 2.0
import Sailfish.Silica 1.0
import App.Logic 1.0
import "../"

// ignore appSettings.showStickersAsEmojis here (if really needed can be re-added later)
MessageContentBase {
    id: stickerMessage

    readonly property var diceSticker: rawMessage.content.final_state || rawMessage.content.initial_state || {}
    readonly property string emoji: rawMessage.content.emoji
    readonly property var stickerData: (diceSticker['@type'] === "diceStickersSlotMachine" ? diceSticker.lever : diceSticker.sticker) || {}
    readonly property bool isOwnSticker: typeof messageListItem !== 'undefined' ? messageListItem.isOwnMessage : overlayFlickable.isOwnMessage

    // do not play animation when viewing history
    property bool completed
    Component.onCompleted: {
        if (!generatedContentUnread && rawMessage.content.value > 0)
            completed = true
        console.log(rawMessage.id, completed, generatedContentUnread)
    }

    width: stickerData.width
    height: stickerData.height

    Loader {
        anchors.fill: sticker
        active: diceSticker['@type'] === "diceStickersSlotMachine"
        sourceComponent: Component {
            Item {
                anchors.fill: parent
                Repeater {
                    model: [diceSticker.background, diceSticker.left_reel, diceSticker.center_reel, diceSticker.right_reel]
                    TDLibAnimatedSticker {
                        anchors.fill: parent
                        loop: false
                        stickerData: modelData
                        //currentFrame: completed ? (frameCount - 1) : -1
                        //paused: !Qt.application.active || completed
                    }
                }
            }
        }
    }

    TDLibAnimatedSticker {
        id: sticker
        width: Math.min(implicitWidth, parent.width)
        height: width * aspectRatio
        // (centered in image mode, text-like in sticker mode)
        anchors {
            horizontalCenter: appSettings.showStickersAsImages ? parent.horizontalCenter : undefined
            right: !appSettings.showStickersAsImages && isOwnSticker ? parent.right : undefined
            verticalCenter: parent.verticalCenter
        }

        stickerData: stickerMessage.stickerData
        loop: !rawMessage.content.final_state

        paused: !Qt.application.active
        stickerItem.source: ''
        Component.onCompleted: {
            stickerItem.autoLoad = false
            stickerItem.source = Qt.binding(function() { return file.path })
            if (completed) {
                paused = true
                currentFrame = frameCount - 2
            } else
                stickerItem.begin()
        }
    }

    onClicked: {
        var canSend = hasSendPrivilege('can_send_other_messages')
        var chatId = chatInformation.id, emojiCopy = emoji // So if the message item is deleted, notification would still work
        appNotification.show(qsTr("Send a %1 emoji to any chat to try your luck.", "in-app notification text").arg(emoji),
                             canSend ? function() { tdLibWrapper.sendDiceMessage(chatId, emojiCopy) } : null,
                             canSend ? qsTr("Send", 'in-app notification button for "Send a %1 emoji to any chat to try your luck."') : null)
    }
}
