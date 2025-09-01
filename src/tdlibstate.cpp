#include "tdlibstate.h"

#define DEBUG_MODULE TDLibState
#include "debuglog.h"

TDLibState::TDLibState(QObject *parent) : QObject(parent) {

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
