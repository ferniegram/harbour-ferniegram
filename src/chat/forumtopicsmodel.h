#ifndef FORUMTOPICSMODEL_H
#define FORUMTOPICSMODEL_H

#include <QAbstractListModel>

#include "tdlib/tdlibwrapper.h"
#include "basemessagabledata.h"

class ForumTopicsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(qlonglong chatId MEMBER chatId NOTIFY chatIdChanged)

    friend class ForumTopicMessagesModel;

public:
    enum Role {
        RoleId,
        RoleName,
        RoleInfo,
        //RoleLastMessage,
        RoleIsPinned,
        RoleUnreadCount,
        RoleLastReadInboxMessageId,
        RoleLastReadOutboxMessageId,
        RoleUnreadMentionCount,
        RoleUnreadReactionCount,
        RoleNotificationSettings,
        //RoleDraftMessage,
    };

    explicit ForumTopicsModel(TDLibWrapper *tdLibWrapper, Utilities *utilities, qlonglong chatId, QObject *parent = nullptr);

    virtual QHash<int,QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void reset();
    Q_INVOKABLE void loadMore();

signals:
    void chatIdChanged();
    void forumTopicUpdated(int forumTopicId);

private slots:
    void handleForumTopicsReceived(qlonglong chatId, int totalCount, QVariantList newTopics, qint32 nextOffsetDate, qlonglong nextOffsetMessageId, qlonglong nextOffsetMessageThreadId);
    void handleForumTopicUpdated(qlonglong chatId, int forumTopicId, const QVariantMap &update);
    void handleForumTopicInfoUpdated(qlonglong chatId, int forumTopicId, const QVariantMap &info);

private:
    struct ForumTopic : public BaseMessagableData {
        ForumTopic(TDLibWrapper *tdLibWrapper, Utilities *utilities, const QVariantMap &forumTopic);

        qlonglong messageThreadId() const;
        bool isPinned() const;
        virtual qlonglong lastReadInboxMessageId() const override;
        virtual qlonglong lastReadOutboxMessageId() const override;

        virtual const QVariantMap lastMessage() const override;

        const QVariantMap notificationSettings() const;

        const QVector<int> updateIsPinned(bool value);
        const QVector<int> updateLastReadInboxMessageId(qlonglong value);
        const QVector<int> updateLastReadOutboxMessageId(qlonglong value);
        const QVector<int> updateLastMessage(const QVariantMap &value);
        const QVector<int> updateNotificationSettings(const QVariantMap &value);

        QVariantMap data;
        int id;
    };

private:
    ForumTopic *getTopic(int id);

private:
    TDLibWrapper *tdLibWrapper;
    Utilities *utilities;

    QList<ForumTopic*> topics;
    QHash<int, int> topicIndexMap;

    qlonglong chatId;
    qint32 nextOffsetDate;
    qlonglong nextOffsetMessageId;
    qlonglong nextOffsetMessageThreadId;
};

#endif // FORUMTOPICSMODEL_H
