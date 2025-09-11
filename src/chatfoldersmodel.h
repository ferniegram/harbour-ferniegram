#ifndef CHATFOLDERSMODEL_H
#define CHATFOLDERSMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "tdlibwrapper.h"
#include "utilities.h"
#include "folderchatlistmodel.h"

class ChatFoldersModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Icon {
        IconAll,
        IconUnread,
        IconUnmuted,
        IconBots,
        IconChannels,
        IconGroups,
        IconPrivate,
        IconCustom,
        IconSetup,
        IconCat,
        IconCrown,
        IconFavorite,
        IconFlower,
        IconGame,
        IconHome,
        IconLove,
        IconMask,
        IconParty,
        IconSport,
        IconStudy,
        IconTrade,
        IconTravel,
        IconWork,
        IconAirplane,
        IconBook,
        IconLight,
        IconLike,
        IconMoney,
        IconNote,
        IconPalette
    };

    enum Role {
        RoleDisplay = Qt::DisplayRole,
        RoleId,
        RoleName,
        RoleIcon,
        RoleColorId,
        RoleIsShareable,
        RoleHasMyInviteLinks,
        RoleModel,
    };

    enum FolderType {
        FolderMain,
        FolderFolder,
        FolderArchive // this is for later
    };

    explicit ChatFoldersModel(TDLibWrapper *tdLibWrapper, AppSettings *appSettings, Utilities *utilities, QObject *parent = nullptr);
    ~ChatFoldersModel() override;

    ChatListModel* getMainChatListModel();
    ChatListModel* getArchiveChatListModel();

    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &index = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private slots:
    void handleChatAddedToFolderList(int folderId, ChatData *chatData, qlonglong order, bool isPinned);
    void handleChatFoldersUpdated(const QVariantList &newChatFolders, int mainChatListPosition, bool tagsEnabled);

private:
    struct ChatFolderData {
        ChatFolderData(const QVariantMap &data);
        ChatFolderData(FolderType type = FolderMain);

        QString name() const;

        FolderType type;
        Icon icon;
        QVariantMap data;
    };

    TDLibWrapper *tdLibWrapper;
    AppSettings *appSettings;
    Utilities *utilities;

    ChatListModel *mainChatListModel;
    ChatListModel *archiveChatListModel;

    QList<ChatFolderData*> chatFolders;
    QHash<int, FolderChatListModel*> chatModels;
};

#endif // CHATFOLDERSMODEL_H
