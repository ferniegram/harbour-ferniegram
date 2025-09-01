#ifndef TDLIBSTATE_H
#define TDLIBSTATE_H

#include <QObject>

class TDLibState : public QObject {
    Q_OBJECT
public:
    explicit TDLibState(QObject *parent = nullptr);

    bool isDiceEmoji(const QString &text);

public slots:
    void handleDiceEmojisUpdated(const QStringList &emojis);

private:
    QStringList diceEmojis;
};

#endif // TDLIBSTATE_H
