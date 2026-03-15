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
import QtQuick 2.6
import Sailfish.Silica 1.0
import App.Logic 1.0

Item {
    id: profilePictureList

    property bool hidden: false
    visible: !hidden && bigProfilePictureList.count > 0

    property bool isUser
    property var chatId
    property bool active: true
    readonly property int currentPictureIndex: bigProfilePictureList.currentIndex
    property real thumbnailRadius

    opacity: active ? 1.0 : 0.0
    Behavior on opacity { FadeAnimation {} }

    PagedView {
        id: bigProfilePictureList
        anchors.fill: parent
        clip: true
        interactive: parent.active
        model: modelLoader.item

        Loader {
            id: modelLoader
            sourceComponent: isUser ? userModelComponent : chatModelComponent

            Component {
                id: chatModelComponent
                MediaMessagesModel {
                    tdlib: tdLibWrapper
                    filter: TDLibAPI.SearchMessagesFilterChatPhoto
                    Component.onCompleted: init(profilePictureList.chatId) // TODO: initialize from the currently set profile picture message id
                }
            }

            Component {
                id: userModelComponent
                UserProfilePicturesModel {
                    tdlib: tdLibWrapper
                    userId: profilePictureList.chatId
                }
            }
        }

        delegate: ProfileThumbnail {
            width: PagedView.contentWidth
            height: PagedView.contentHeight
            photoData: isUser ? big_photo : utilities.findBiggestPhotoSize(modelData.sizes).photo
            replacementStringHint: ''
            radius: thumbnailRadius

            MouseArea {
                anchors.fill: parent
                onClicked:
                    pageStack.push(Qt.resolvedUrl("../pages/ImagePage.qml"), {photoData: modelData})
            }
        }
    }

    Text {
        visible: bigProfilePictureList.count > 1
        width: parent.width - Theme.paddingSmall
        anchors {
            bottomMargin: Theme.paddingSmall
            bottom: parent.bottom
        }
        horizontalAlignment: Text.AlignHCenter
        property var baseString: new Array(bigProfilePictureList.count+1).join(" ○ ")
        text: (baseString.substring(0,bigProfilePictureList.currentIndex*3) + " ● " + baseString.substring((bigProfilePictureList.currentIndex+1)*3)).trim()
        font.pixelSize: Theme.fontSizeTiny
        color: Theme.primaryColor
        style: Text.Raised
        styleColor: Theme.highlightDimmerColor
    }

}
