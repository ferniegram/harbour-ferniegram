#ifndef READABLEMESSAGESMODEL_H
#define READABLEMESSAGESMODEL_H

#include "messagesmodel.h"

class ReadableMessagesModel : public MessagesModel {
public:
    ReadableMessagesModel(TDLibWrapper *tdLibWrapper);
};

#endif // READABLEMESSAGESMODEL_H
