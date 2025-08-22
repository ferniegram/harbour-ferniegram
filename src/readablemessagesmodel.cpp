#include "readablemessagesmodel.h"

#define DEBUG_MODULE ReadableMessagesModel
#include "debuglog.h"

ReadableMessagesModel::ReadableMessagesModel(TDLibWrapper *tdLibWrapper) : MessagesModel(tdLibWrapper) {

}
int ReadableMessagesModel::getLastReadMessageIndex() {
    int listInboxPosition = messageIndexMap.value(lastReadInboxMessageId(), -1);
    if (listInboxPosition > messages.size() - 1) listInboxPosition = -1;
    return listInboxPosition;
}

int ReadableMessagesModel::calculateLastReadSentMessageIndex() {
    LOG("calculateLastReadSentMessageIndex");
    qlonglong id = lastReadOutboxMessageId();
    LOG("lastReadSentMessageId" << id);
    LOG("size messageIndexMap" << messageIndexMap.size());
    LOG("contains ID?" << messageIndexMap.contains(id));
    int listOutboxPosition;
    if (messageIndexMap.contains(id))
        listOutboxPosition = messageIndexMap.value(id, -1);
    else {
        LOG("Last read sent message is not loaded, falling back to last loaded sent message");
        listOutboxPosition = findLastSentMessageIndex();
    }
    LOG("Last read sent message" << id << "is at position" << listOutboxPosition);
    return listOutboxPosition;
}

int ReadableMessagesModel::calculateScrollPosition() {
    if (loadingFullEnd) return this->messages.size() - 1;

    int scrollPosition = this->messageIndexMap.value(this->highlightedMessageId, -1);
    if (scrollPosition == -1) {
        LOG("calculateLastScrollMessageIndex");

        int listInboxPosition = lastReadInboxMessageId();
        int listOwnPosition = findLastSentMessageIndex();

        if (listInboxPosition > messages.size() - 1) listInboxPosition = -1;
        if (listOwnPosition > messages.size() - 1) listOwnPosition = -1;

        LOG("Last read received message is at position" << listInboxPosition << "; last read sent message is at position" << listOwnPosition);

        scrollPosition = qMax(listInboxPosition, listOwnPosition);
    }

    LOG("Calculating new scroll position, current:" << scrollPosition << ", list size:" << this->messages.size());
    return qMin(scrollPosition + 1, this->messages.size() - 1);
}

bool ReadableMessagesModel::isMostRecentMessageLoaded() {
    // Need to check if we can actually add messages (only possible if the previously latest messages are loaded)
    // some other things also depend on this now

    const qlonglong messageId = lastMessageId();
    const bool result = this->messageIndexMap.contains(messageId);
    LOG("Checking if most recent message is loaded" << messageId << result << messageIndexMap);
    return result;
}
