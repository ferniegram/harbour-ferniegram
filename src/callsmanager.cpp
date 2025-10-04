#include "callsmanager.h"

#include <tgcalls/Instance.h>
#include <tgcalls/InstanceImpl.h>
#include <tgcalls/v2/InstanceV2Impl.h>
#include <tgcalls/v2/InstanceV2ReferenceImpl.h>

namespace {
    const QString _TYPE("@type");
    const QString TYPE_CALL_PROTOCOL("callProtocol");
}

static bool compareVersions(const QString &a, const QString &b) {
    return a > b;
}

CallsManager::CallsManager(TDLibWrapper *tdLibWrapper, QObject *parent) : QObject(parent), tdLibWrapper(tdLibWrapper) {
    tgcalls::Register<tgcalls::InstanceImpl>();
    tgcalls::Register<tgcalls::InstanceV2Impl>();
    tgcalls::Register<tgcalls::InstanceV2ReferenceImpl>();
}

QVariantMap CallsManager::getProtocol() {
    QStringList versions;
    for (const std::string &version : tgcalls::Meta::Versions())
        versions << QString::fromStdString(version);
    std::sort(versions.begin(), versions.end(), compareVersions); // Server processes them newer to older

    QVariantMap protocol{
        {_TYPE, TYPE_CALL_PROTOCOL},
        {"udp_p2p", true},
        {"udp_reflector", true},
        {"min_layer", 92},
        {"max_layer", tgcalls::Meta::MaxLayer()},
        {"library_versions", versions}
    };
}
