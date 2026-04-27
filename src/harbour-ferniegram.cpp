#include <sailfishapp.h>
#include <QQuickView>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QSysInfo>
#include <QSettings>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

// The default filter can be overridden by QT_LOGGING_RULES envinronment variable, e.g.
// QT_LOGGING_RULES="libfernie.*=true;ferniegram.*=true" harbour-ferniegram
#if defined (QT_DEBUG) || defined(DEBUG)
#  define DEFAULT_LOG_FILTER "libfernie.*=true\nferniegram.*=true"
#else
#  define DEFAULT_LOG_FILTER "libfernie.*=false\nferniegram.*=false"
#endif

#define JS_DEBUG_ROOT_MODULE "ferniegram.JS"
#include "ferniemain.h"

#include "voicenoterecorder.h"

int main(int argc, char *argv[]) {
    QLoggingCategory::setFilterRules(DEFAULT_LOG_FILTER);

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QSharedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext *context = view->rootContext();

    const QString dbusPath = "/io/ferniegram/ferniegram";
    const QString dbusServiceName = "io.ferniegram.ferniegram";

    QScopedPointer<FernieMain::AppContext> appContext(FernieMain::registerTypes(argc, argv, view, "Ferniegram", dbusPath, dbusServiceName));

    FernieMain::registerDBusService(view, dbusPath, dbusServiceName);
    // FIXME: there's a short period of time when the application closes (waiting for tdlib to close),
    // but the dbus service isn't unregistered yet, in which clicking the application doesn't open it.
    // Seems like SailfishOS uses X-Maemo-Method not only for opening URLs, but for opening the app itself too

    FernieMain::registerDebugLogJS(appContext.data());

    VoiceNoteRecorder *voiceNoteRecorder = new VoiceNoteRecorder(argc, argv, view.data());
    context->setContextProperty("voiceNoteRecorder", voiceNoteRecorder);
    qmlRegisterUncreatableType<VoiceNoteRecorder>(appContext->uri, 1, 0, "VoiceNoteRecorder", QString());

#ifdef NO_HARBOUR_COMPLIANCE
    context->setContextProperty("NO_HARBOUR_COMPLIANCE", true);
#else
    context->setContextProperty("NO_HARBOUR_COMPLIANCE", false);
#endif

    view->setSource(SailfishApp::pathToMainQml());
    view->show();
    return app->exec();
}
