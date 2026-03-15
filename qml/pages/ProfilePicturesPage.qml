import QtQuick 2.0
import Sailfish.Silica 1.0
import App.Logic 1.0
import '../components'
import '../components/messageContent/mediaAlbumPage'

MediaAlbumPage {
    property alias userId: profilePicturesModel.userId

    model: UserProfilePicturesModel {
        id: profilePicturesModel
        tdlib: tdLibWrapper
    }

    delegate: PhotoComponent {
        width: PagedView.contentWidth
        height: PagedView.contentHeight

        photoData: null
        photoSize: big_photo
    }

    overlay.previewModel: profilePicturesModel
    overlay.previewComponent: Component {
        TDLibPhoto {
            fileInformation: small_photo.photo
            minithumbnail: photo_minithumbnail
            highlighted: singlePreviewMouseArea.containsPress

            MouseArea {
                id: singlePreviewMouseArea
                anchors.fill: parent
                onClicked: overlay.jumpedToIndex(index)
            }
        }
    }
}
