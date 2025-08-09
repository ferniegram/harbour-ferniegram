#ifndef CHATMODEL_H
#define CHATMODEL_H

#include "messagesmodel.h"

class ChatModel : public MessagesModel {
    Q_OBJECT
    Q_PROPERTY(QVariantMap smallPhoto READ smallPhoto NOTIFY smallPhotoChanged)
    Q_PROPERTY(QVariantMap chatActionsByUsers MEMBER chatActionsByUsers NOTIFY chatActionsChanged)
    Q_PROPERTY(QVariantMap chatActionsByChats MEMBER chatActionsByChats NOTIFY chatActionsChanged)

public:
    ChatModel(TDLibWrapper *tdLibWrapper);

    Q_INVOKABLE virtual void reset() override;
    Q_INVOKABLE void initialize(const QVariantMap &chatInformation, qlonglong fromMessageId = 0);

    QVariantMap smallPhoto() const;

signals:
    void smallPhotoChanged();
    void pinnedMessageChanged();
    void chatActionsChanged();
    void notificationSettingsUpdated();

private slots:
    void handleChatPhotoUpdated(qlonglong chatId, const QVariantMap &photo);
    void handleChatPinnedMessageUpdated(qlonglong chatId, qlonglong pinnedMessageId);
    void handleChatActionUpdated(qlonglong chatId, const QVariantMap &sender, const QVariantMap &chatAction, qlonglong messageThreadId);
    void handleChatNotificationSettingsUpdated(const QString &chatId, const QVariantMap &chatNotificationSettings);

private:
    QVariantMap chatActionsByUsers; // QMap<qlonglong, QString>
    QVariantMap chatActionsByChats; //QMap<qlonglong, QString>
};

#endif // CHATMODEL_H
