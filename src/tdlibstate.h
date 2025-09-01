#ifndef TDLIBSTATE_H
#define TDLIBSTATE_H

#include <QObject>
#include "tdlibreceiver.h"

class TDLibState : public QObject {
    Q_OBJECT
public:
    explicit TDLibState(TDLibReceiver *tdLibReceiver, QObject *parent = nullptr);

    bool isDiceEmoji(const QString &text);

signals:
    void reactionsUpdated();

public slots:
    void handleActiveEmojiReactionsUpdated(const QStringList& emojis);
    void handleDiceEmojisUpdated(const QStringList &emojis);

public:
    QStringList activeEmojiReactions;
    QStringList diceEmojis;
};

#endif // TDLIBSTATE_H
