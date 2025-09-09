#include "chatfoldersmodel.h"

#define DEBUG_MODULE ChatFoldersModel
#include "debuglog.h"

namespace {
    const QString ID("id");
    const QString NAME("name");
    const QString ICON("icon");
    const QString COLOR_ID("color_id");
    const QString IS_SHAREABLE("is_shareable");
    const QString HAS_MY_INVITE_LINKS("has_my_invite_links");
    const QString TEXT("text");
}

ChatFoldersModel::ChatFoldersModel(TDLibWrapper *tdLibWrapper, AppSettings *appSettings, Utilities *utilities, QObject *parent) :
    QAbstractListModel(parent),
    tdLibWrapper(tdLibWrapper),
    appSettings(appSettings),
    utilities(utilities)
{
    connect(tdLibWrapper, &TDLibWrapper::chatAddedToFolderList, this, &ChatFoldersModel::handleChatAddedToFolderList);
    connect(tdLibWrapper, &TDLibWrapper::chatFoldersUpdated, this, &ChatFoldersModel::handleChatFoldersUpdated);
}

ChatFoldersModel::~ChatFoldersModel() {
    LOG("Destroying myself...");
    qDeleteAll(chatModels);
}

ChatFoldersModel::Icon ChatFoldersModel::iconForName(const QString &name) {
    if (name == "All") return IconAll;
    if (name == "Unread") return IconUnread;
    if (name == "Unmuted") return IconUnmuted;
    if (name == "Bots") return IconBots;
    if (name == "Channels") return IconChannels;
    if (name == "Groups") return IconGroups;
    if (name == "Private") return IconPrivate;
    if (name == "Custom") return IconCustom;
    if (name == "Setup") return IconSetup;
    if (name == "Cat") return IconCat;
    if (name == "Crown") return IconCrown;
    if (name == "Favorite") return IconFavorite;
    if (name == "Flower") return IconFlower;
    if (name == "Game") return IconGame;
    if (name == "Home") return IconHome;
    if (name == "Love") return IconLove;
    if (name == "Mask") return IconMask;
    if (name == "Party") return IconParty;
    if (name == "Sport") return IconSport;
    if (name == "Study") return IconStudy;
    if (name == "Trade") return IconTrade;
    if (name == "Travel") return IconTravel;
    if (name == "Work") return IconWork;
    if (name == "Airplane") return IconAirplane;
    if (name == "Book") return IconBook;
    if (name == "Light") return IconLight;
    if (name == "Like") return IconLike;
    if (name == "Money") return IconMoney;
    if (name == "Note") return IconNote;
    if (name == "Palette") return IconPalette;

    return IconAll;
}

QHash<int,QByteArray> ChatFoldersModel::roleNames() const {
    return QHash<int, QByteArray>{
        {RoleDisplay, "display"},
        {RoleId, "id"},
        {RoleName, "name"},
        {RoleIcon, "icon"},
        {RoleColorId, "color_id"},
        {RoleIsShareable, "is_shareable"},
        {RoleHasMyInviteLinks, "has_my_invite_links"},
        {RoleModel, "chat_list_model"}
    };
}

int ChatFoldersModel::rowCount(const QModelIndex &) const {
    return chatFolders.size();
}

QVariant ChatFoldersModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    if (row >= 0 && row < chatFolders.size()) {
        const QVariantMap data = chatFolders.at(row);
        switch ((ChatFoldersModel::Role)role) {
        case RoleDisplay: return data;
        case RoleId: return data.value(ID).toInt();
        case RoleName: return Utilities::enhanceMessageText(data.value(NAME).toMap().value(TEXT).toMap(), true); // ignore entities because only animated emojis are supported and we don't support them yet
        case RoleIcon: return iconForName(data.value(ICON).toMap().value(NAME).toString());
        case RoleColorId: return data.value(COLOR_ID).toInt();
        case RoleIsShareable: return data.value(IS_SHAREABLE).toBool();
        case RoleHasMyInviteLinks: return data.value(HAS_MY_INVITE_LINKS).toBool();
        case RoleModel:
            const int id = data.value(ID).toInt();
            if (chatModels.contains(id))
                return QVariant::fromValue(chatModels.value(id));
        }
    }
    return QVariant();
}

void ChatFoldersModel::handleChatAddedToFolderList(int folderId, ChatData *chatData, qlonglong order, bool isPinned) {
    if (!this->chatModels.contains(folderId)) {
        FolderChatListModel* chatModel = new FolderChatListModel(tdLibWrapper, appSettings, utilities, folderId);
        this->chatModels.insert(folderId, chatModel);
        chatModel->handleChatAddedToList(chatData, order, isPinned);
    }
}

void ChatFoldersModel::handleChatFoldersUpdated(const QVariantList &newChatFolders, int mainChatListPosition, bool tagsEnabled) {
    LOG("Chat folders list updated" << newChatFolders.count());

    beginResetModel();
    chatFolders.clear();

    //QSet<int> newFolderIds;

    for (const QVariant &folderVariant : newChatFolders) {
        const QVariantMap folder = folderVariant.toMap();
        chatFolders.append(folder);

        const int folderId = folder.value(ID).toInt();
        if (!this->chatModels.contains(folderId))
            this->chatModels.insert(folderId, new FolderChatListModel(tdLibWrapper, appSettings, utilities, folderId));

        //newFolderIds.insert(folder.value(ID).toInt());
    }

    /*QSet<int> folderIdsToRemove = chatModels.keys().toSet();
    folderIdsToRemove -= newFolderIds;
    for (int folderId : folderIdsToRemove)
        delete chatModels.take(folderId);

    QSet<int> folderIdsToAdd = newFolderIds;
    folderIdsToAdd -= chatModels.keys().toSet();
    for (int folderId : folderIdsToAdd) {
        chatModels.insert(folderId, new FolderChatListModel(tdLibWrapper, appSettings, utilities, folderId));
        tdLibWrapper->loadChatsForFolder(folderId);
    }*/

    endResetModel();
}
