#ifndef FORUMTOPIC_H
#define FORUMTOPIC_H

#include "tdlib/tdlibwrapper.h"
#include "basemessagabledata.h"

struct ForumTopic : public BaseMessagableData {
    enum Role {
        RoleId,
        RoleName,
        RoleIconColor,
        RoleIconCustomEmojiId,
        RoleCreationDate,
        RoleCreatorIsChat,
        RoleCreatorUserId,
        RoleCreatorChatId,
        RoleIsGeneral,
        RoleIsOutgoing,
        RoleIsClosed,
        RoleIsHidden,
        RoleIsNameImplicit,
        RoleLastMessageSenderId,
        RoleLastMessageDate,
        RoleLastMessageText,
        RoleLastMessageMinithumbnail,
        RoleLastMessageIsService,
        RoleLastMessageStatus,
        RoleIsPinned,
        RoleUnreadCount,
        RoleLastReadInboxMessageId,
        RoleLastReadOutboxMessageId,
        RoleUnreadMentionCount,
        RoleUnreadReactionCount,
        RoleNotificationSettings,
        RoleDraftMessageText,
        RoleDraftMessageDate,
    };

    ForumTopic(TDLibWrapper *tdLibWrapper, Utilities *utilities, const QVariantMap &forumTopic);

    QVariantMap info() const;

    bool isPinned() const;
    int unreadCount() const;
    int unreadMentionCount() const;
    int unreadReactionCount() const;
    virtual qlonglong lastReadInboxMessageId() const override;
    virtual qlonglong lastReadOutboxMessageId() const override;
    const QVariantMap notificationSettings() const;

    virtual const QVariantMap lastMessage() const override;
    virtual const QVariantMap draftMessage() const override;

    const QVector<int> updateIsPinned(bool value);
    const QVector<int> updateLastReadInboxMessageId(qlonglong value);
    const QVector<int> updateLastReadOutboxMessageId(qlonglong value);
    const QVector<int> updateLastMessage(const QVariantMap &message);
    const QVector<int> updateUnreadCount(int value);
    const QVector<int> updateUnreadMentionCount(int value);
    const QVector<int> updateUnreadReactionCount(int value);
    const QVector<int> updateNotificationSettings(const QVariantMap &value);
    const QVector<int> updateDraftMessage(const QVariantMap &value);

    const QVector<int> updateForumTopic(const QVariantMap &update);
    const QVector<int> updateForumTopicInfo(const QVariantMap &newInfo);

    QVariantMap data;
    int id;
};

#endif // FORUMTOPIC_H
