#include "tdlibstate.h"

#define DEBUG_MODULE TDLibState
#include "debuglog.h"

TDLibState::TDLibState(TDLibReceiver *tdLibReceiver, QObject *parent) : QObject(parent) {
    connect(tdLibReceiver, &TDLibReceiver::activeEmojiReactionsUpdated, this, &TDLibState::handleActiveEmojiReactionsUpdated);
    connect(tdLibReceiver, &TDLibReceiver::diceEmojisUpdated, this, &TDLibState::handleDiceEmojisUpdated);
}

void TDLibState::handleActiveEmojiReactionsUpdated(const QStringList& emojis) {
    if (activeEmojiReactions != emojis) {
        activeEmojiReactions = emojis;
        LOG(emojis.count() << "reaction(s) available");
        emit reactionsUpdated();
    }
}

void TDLibState::handleDiceEmojisUpdated(const QStringList &emojis) {
    if (diceEmojis != emojis) {
        LOG("Dice emojis updated" << emojis);
        diceEmojis = emojis;
    }
}

bool TDLibState::isDiceEmoji(const QString &text) {
    LOG("Checking if text is a dice emoji" << text);
    return diceEmojis.contains(QString(text).trimmed());
}
