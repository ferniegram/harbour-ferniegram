#include "platformapp.h"
#include "sailfishapp.h"

namespace {
    const QString FOLDER_ICON_PATH_PREFIX("images/folders/icon-m-folder-");
    const QString SVG_EXTENSION_SUFFIX(".svg");
    const QString THEME_ICON_PREFIX("image://theme/icon-m-");
}

QUrl PlatformApp::pathTo(const QString &filename) {
    return SailfishApp::pathTo(filename);
}

QUrl PlatformApp::pathToAppIcon() {
    return SailfishApp::pathTo("images/ferniegram-notification.png");
}

QUrl PlatformApp::pathToChatFolderIcon(ChatFoldersModel::Icon icon) {
    auto pathToIcon = [](const QString &name) {
        return PlatformApp::pathTo(FOLDER_ICON_PATH_PREFIX + name + SVG_EXTENSION_SUFFIX);
    };

    switch (icon) {
    case ChatFoldersModel::Icon::IconAll:
        return THEME_ICON_PREFIX + "chat"; // FIXME: should this be outline-chat?
    case ChatFoldersModel::Icon::IconHome:
        return THEME_ICON_PREFIX + "home";
    case ChatFoldersModel::Icon::IconFavorite:
        return THEME_ICON_PREFIX + "favorite";
    case ChatFoldersModel::Icon::IconCustom:
        return THEME_ICON_PREFIX + "folder";
    case ChatFoldersModel::Icon::IconGame:
        return THEME_ICON_PREFIX + "game-controller";
    case ChatFoldersModel::Icon::IconLike:
        return THEME_ICON_PREFIX + "like"; // FIXME: should this be outline-like?
    case ChatFoldersModel::Icon::IconNote:
        return THEME_ICON_PREFIX + "media-songs";
    case ChatFoldersModel::Icon::IconWork:
        return THEME_ICON_PREFIX + "company";


    // possibly FIXME for these:
    case ChatFoldersModel::Icon::IconLight:
        return THEME_ICON_PREFIX + "flashlight";
    case ChatFoldersModel::Icon::IconGroups:
        return THEME_ICON_PREFIX + "people";
    case ChatFoldersModel::Icon::IconMask:
        return THEME_ICON_PREFIX + "incognito";

    //case ChatFoldersModel::Icon::IconAirplane: // LOOOOOOL
    //    return THEME_ICON_PREFIX + "airplane-mode";


    case ChatFoldersModel::Icon::IconBook:
        return pathToIcon("book");
    case ChatFoldersModel::Icon::IconLove:
        return pathToIcon("love");
    case ChatFoldersModel::Icon::IconBots:
        return pathToIcon("bots");
    case ChatFoldersModel::Icon::IconCat:
        return pathToIcon("cat");
    case ChatFoldersModel::Icon::IconChannels:
        return pathToIcon("channels");
    case ChatFoldersModel::Icon::IconCrown:
        return pathToIcon("crown");
    case ChatFoldersModel::Icon::IconFlower:
        return pathToIcon("flower");
    case ChatFoldersModel::Icon::IconAirplane:
        return pathToIcon("airplane");
    case ChatFoldersModel::Icon::IconMoney:
        return pathToIcon("money");
    case ChatFoldersModel::Icon::IconPalette:
        return pathToIcon("palette");
    case ChatFoldersModel::Icon::IconParty:
        return pathToIcon("party");
    case ChatFoldersModel::Icon::IconPrivate:
        return pathToIcon("private");
    case ChatFoldersModel::Icon::IconSetup:
        return pathToIcon("setup");
    case ChatFoldersModel::Icon::IconSport:
        return pathToIcon("sport");
    case ChatFoldersModel::Icon::IconStudy:
        return pathToIcon("study");
    case ChatFoldersModel::Icon::IconTrade:
        return pathToIcon("trade");
    case ChatFoldersModel::Icon::IconTravel:
        return pathToIcon("travel");
    case ChatFoldersModel::Icon::IconUnmuted:
        return pathToIcon("unmuted");
    case ChatFoldersModel::Icon::IconUnread:
        return pathToIcon("unread");
    }

    return QString();
}
