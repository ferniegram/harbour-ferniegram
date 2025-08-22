#ifndef READABLEMESSAGESMODEL_H
#define READABLEMESSAGESMODEL_H

#include "messagesmodel.h"

class ReadableMessagesModel : public MessagesModel {
    Q_OBJECT
    Q_PROPERTY(int lastReadSentMessageIndex READ calculateLastReadSentMessageIndex NOTIFY lastReadSentMessageUpdated)
    Q_PROPERTY(bool historyEndLoaded READ isMostRecentMessageLoaded NOTIFY historyEndLoadedChanged)

public:
    ReadableMessagesModel(TDLibWrapper *tdLibWrapper);

    Q_INVOKABLE bool isMostRecentMessageLoaded();

signals:
    void lastReadSentMessageUpdated();
    void historyEndLoadedChanged();

protected:
    int getLastReadMessageIndex();
    int calculateLastReadSentMessageIndex();
    int calculateScrollPosition();

    virtual qlonglong lastReadInboxMessageId() = 0;
    virtual qlonglong lastReadOutboxMessageId() = 0;
    virtual qlonglong lastMessageId() = 0;
};

#endif // READABLEMESSAGESMODEL_H
