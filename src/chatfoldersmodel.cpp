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

ChatFoldersModel::Icon iconForName(const QString &name) {
    if (name == "All") return ChatFoldersModel::IconAll;
    if (name == "Unread") return ChatFoldersModel::IconUnread;
    if (name == "Unmuted") return ChatFoldersModel::IconUnmuted;
    if (name == "Bots") return ChatFoldersModel::IconBots;
    if (name == "Channels") return ChatFoldersModel::IconChannels;
    if (name == "Groups") return ChatFoldersModel::IconGroups;
    if (name == "Private") return ChatFoldersModel::IconPrivate;
    if (name == "Custom") return ChatFoldersModel::IconCustom;
    if (name == "Setup") return ChatFoldersModel::IconSetup;
    if (name == "Cat") return ChatFoldersModel::IconCat;
    if (name == "Crown") return ChatFoldersModel::IconCrown;
    if (name == "Favorite") return ChatFoldersModel::IconFavorite;
    if (name == "Flower") return ChatFoldersModel::IconFlower;
    if (name == "Game") return ChatFoldersModel::IconGame;
    if (name == "Home") return ChatFoldersModel::IconHome;
    if (name == "Love") return ChatFoldersModel::IconLove;
    if (name == "Mask") return ChatFoldersModel::IconMask;
    if (name == "Party") return ChatFoldersModel::IconParty;
    if (name == "Sport") return ChatFoldersModel::IconSport;
    if (name == "Study") return ChatFoldersModel::IconStudy;
    if (name == "Trade") return ChatFoldersModel::IconTrade;
    if (name == "Travel") return ChatFoldersModel::IconTravel;
    if (name == "Work") return ChatFoldersModel::IconWork;
    if (name == "Airplane") return ChatFoldersModel::IconAirplane;
    if (name == "Book") return ChatFoldersModel::IconBook;
    if (name == "Light") return ChatFoldersModel::IconLight;
    if (name == "Like") return ChatFoldersModel::IconLike;
    if (name == "Money") return ChatFoldersModel::IconMoney;
    if (name == "Note") return ChatFoldersModel::IconNote;
    if (name == "Palette") return ChatFoldersModel::IconPalette;

    return ChatFoldersModel::IconAll;
}

ChatFoldersModel::ChatFolderData::ChatFolderData(const QVariantMap &data) :
    type(FolderFolder),
    data(data)
{
    const QString iconName = this->data.take(ICON).toMap().value(NAME).toString();
    icon = iconForName(iconName);
}

ChatFoldersModel::ChatFolderData::ChatFolderData(FolderType type) :
    type(type),
    icon(IconAll),
    data()
{}

QString ChatFoldersModel::ChatFolderData::name() const {
    switch (type) {
    case FolderMain:
        return tr("All", "all chats tab");
    case FolderFolder:
        return Utilities::enhanceMessageText(data.value(NAME).toMap().value(TEXT).toMap(), true); // ignore entities because only animated emojis are supported and we don't support them yet
    case FolderArchive:
        return tr("Archive", "archived chats tab");
    }
}

ChatFoldersModel::ChatFoldersModel(TDLibWrapper *tdLibWrapper, AppSettings *appSettings, Utilities *utilities, QObject *parent) :
    QAbstractListModel(parent),
    tdLibWrapper(tdLibWrapper),
    appSettings(appSettings),
    utilities(utilities),
    mainChatListModel(new ChatListModel(tdLibWrapper, appSettings, utilities)),
    archiveChatListModel(new ChatListModel(tdLibWrapper, appSettings, utilities, true))
{
    connect(tdLibWrapper, &TDLibWrapper::chatAddedToFolderList, this, &ChatFoldersModel::handleChatAddedToFolderList);
    connect(tdLibWrapper, &TDLibWrapper::chatFoldersUpdated, this, &ChatFoldersModel::handleChatFoldersUpdated);
}

ChatFoldersModel::~ChatFoldersModel() {
    LOG("Destroying myself...");
    qDeleteAll(chatFolders);
    qDeleteAll(chatModels.values());
}


ChatListModel* ChatFoldersModel::getMainChatListModel() {
    return mainChatListModel;
}
ChatListModel* ChatFoldersModel::getArchiveChatListModel() {
    return archiveChatListModel;
}


QHash<int,QByteArray> ChatFoldersModel::roleNames() const {
    return QHash<int, QByteArray>{
        // Opal.Tabs-specific:
        {RoleName, "title"},

        {RoleDisplay, "display"},
        {RoleId, "id"},
        {RoleIcon, "icon_"},
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
        const ChatFolderData *data = chatFolders.at(row);
        switch ((ChatFoldersModel::Role)role) {
        case RoleDisplay: return data->data;
        case RoleId: return data->data.value(ID).toInt();
        case RoleName: return data->name(); // ignore entities because only animated emojis are supported and we don't support them yet
        case RoleIcon: return data->icon;
        case RoleColorId: return data->data.value(COLOR_ID).toInt();
        case RoleIsShareable: return data->data.value(IS_SHAREABLE).toBool();
        case RoleHasMyInviteLinks: return data->data.value(HAS_MY_INVITE_LINKS).toBool();
        case RoleModel:
            switch (data->type) {
            case FolderMain:
                return QVariant::fromValue(this->mainChatListModel);
            case FolderFolder: {
                const int id = data->data.value(ID).toInt();
                if (chatModels.contains(id))
                    return QVariant::fromValue(chatModels.value(id));
                break;
            }
            case FolderArchive:
                return QVariant::fromValue(this->archiveChatListModel);
            }
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
    qDeleteAll(chatFolders);
    chatFolders.clear();

    //QSet<int> newFolderIds;

    for (const QVariant &folderVariant : newChatFolders) {
        const QVariantMap folder = folderVariant.toMap();
        this->chatFolders.append(new ChatFolderData(folder));

        const int folderId = folder.value(ID).toInt();
        if (!this->chatModels.contains(folderId))
            this->chatModels.insert(folderId, new FolderChatListModel(tdLibWrapper, appSettings, utilities, folderId));

        //newFolderIds.insert(folder.value(ID).toInt());
    }

    this->chatFolders.insert(mainChatListPosition, new ChatFolderData());

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
