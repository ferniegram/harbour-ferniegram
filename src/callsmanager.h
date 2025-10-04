#ifndef CALLSMANAGER_H
#define CALLSMANAGER_H

#include <QObject>

#include "tdlibwrapper.h"

class CallsManager : public QObject {
    Q_OBJECT
public:
    explicit CallsManager(TDLibWrapper *tdLibWrapper, QObject *parent = nullptr);

    Q_INVOKABLE static QVariantMap getProtocol();
private:
    TDLibWrapper *tdLibWrapper;
};

#endif // CALLSMANAGER_H
