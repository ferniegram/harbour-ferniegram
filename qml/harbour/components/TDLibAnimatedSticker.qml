import QtQuick 2.6
import Sailfish.Silica 1.0
import QtMultimedia 5.6
import App.Logic 1.0
import "../js/twemoji.js" as Emoji

TDLibStickerBase {
    id: sticker

    stickerVisible: file.isDownloadingCompleted

    property alias stickerItem: animatedSticker
    property alias frameCount: animatedSticker.frameCount
    property alias currentFrame: animatedSticker.currentFrame
    property alias paused: animatedSticker.paused

    readonly property bool loaded: file.isDownloadingCompleted

    LottieItem {
        id: animatedSticker
        // Don't use anchors.fill here (breaks width & height values used below)
        width: parent.width
        height: parent.height

        source: file.path
        scaledSize {
            width: appSettings.downscaleAnimatedStickers ? Theme.itemSizeSmall : width
            height: appSettings.downscaleAnimatedStickers ? (Theme.itemSizeSmall * aspectRatio) : height
        }

        paused: !Qt.application.active
        loop: sticker.loop
        layer.enabled: sticker.highlighted
        layer.effect: PressEffect { source: animatedSticker }
    }
}
