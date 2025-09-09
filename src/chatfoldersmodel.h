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

    explicit ChatFoldersModel(TDLibWrapper *tdLibWrapper, AppSettings *appSettings, Utilities *utilities, QObject *parent = nullptr);
    ~ChatFoldersModel() override;

    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &index = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    static Icon iconForName(const QString &name);

private slots:
    void handleChatAddedToFolderList(int folderId, ChatData *chatData, qlonglong order, bool isPinned);
    void handleChatFoldersUpdated(const QVariantList &newChatFolders, int mainChatListPosition, bool tagsEnabled);

private:
    TDLibWrapper *tdLibWrapper;
    AppSettings *appSettings;
    Utilities *utilities;
    QList<QVariantMap> chatFolders;
    QHash<int, FolderChatListModel*> chatModels;
};

#endif // CHATFOLDERSMODEL_H
