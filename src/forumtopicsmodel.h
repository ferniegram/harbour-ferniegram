#ifndef FORUMTOPICSMODEL_H
#define FORUMTOPICSMODEL_H

#include <QAbstractListModel>

#include "tdlibwrapper.h"

class ForumTopicsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(qlonglong chatId MEMBER chatId NOTIFY chatIdChanged)

public:
    enum Role {
        RoleInfo,
        //RoleLastMessage,
        RoleOrder,
        RoleIsPinned,
        RoleUnreadCount,
        //RoleLastReadInboxMessageId,
        //RoleLastReadOutboxMessageId,
        RoleUnreadMentionCount,
        RoleUnreadReactionCount,
        RoleNotificationSettings,
        //RoleDraftMessage,
    };

    explicit ForumTopicsModel(TDLibWrapper *tdLibWrapper, QObject *parent = nullptr);

    virtual QHash<int,QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void init(qlonglong chatId);
    Q_INVOKABLE void reset();
    Q_INVOKABLE void loadMore();

signals:
    void chatIdChanged();

private slots:
    void handleForumTopicsReceived(qlonglong chatId, int totalCount, QVariantList newTopics, qint32 nextOffsetDate, qlonglong nextOffsetMessageId, qlonglong nextOffsetMessageThreadId);

private:
    struct ForumTopic {
        ForumTopic(const QVariantMap &forumTopic);

        QVariantMap data;

        qlonglong messageThreadId();
        /*QVariantMap info;
        QVariantMap lastMessage;
        qlonglong order;
        bool isPinned;
        int unreadCount;
        qlonglong lastReadInboxMessageId;
        qlonglong lastReadOutboxMessageId;
        int unreadMentionCount;
        int unreadReactionCount;
        QVariantMap notificationSettings;
        QVariantMap draftMessage;*/
    };

    TDLibWrapper *tdLibWrapper;

    QList<ForumTopic*> topics;
    QHash<qlonglong, int> topicIndexMap;

    qlonglong chatId;
    qint32 nextOffsetDate;
    qlonglong nextOffsetMessageId;
    qlonglong nextOffsetMessageThreadId;
};

#endif // FORUMTOPICSMODEL_H
