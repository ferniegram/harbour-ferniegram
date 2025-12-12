#include "mainshared.h"

#include <asteroidapp.h>
#include <QQuickView>
//#include <QtQml>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QDir>

namespace SailfishyAsteroidApp {
    // Some things from sailfishapp which don't exist in asteroidapp (because we use some things asteroidapp doesn't generally recommend, like storing QML files in separate directory)

    QString dataDir() {
        return path.section('/', 0, -2) + "share/" + AsteroidApp::appName();
    }

    QUrl pathTo(const QString &filename) {
        return QUrl::fromLocalFile(QDir::cleanPath(dataDir() + '/' + filename));
    }

    QUrl pathToMainQml() {
        return pathTo("qml/" + AsteroidApp::appName() + ".qml")
    }

    void configureApp(QSharedPointer<QGuiApplication> app) {
        QString translations = pathTo("translations");
        if (QDir(translations).exists()) {
            QTranslator *translator = new QTranslator();
            translator->load(QLocale::system(), appName(), "-", translations, ".qm");
            app->installTranslator(translator);
        }
    }
}

int main(int argc, char *argv[]) {
    MainShared::setupLogging();

    QSharedPointer<QGuiApplication> app(AsteroidApp::application(argc, argv));
    QSharedPointer<QQuickView> view(AsteroidApp::createView()); // FIXME: should we actually use QScopedPointer here?

    SailfishyAsteroidApp::configureApp(app);

    //QQmlContext *context = view.data()->rootContext();

    app->setOrganizationName("io.github.roundedrectangle");
    app->setOrganizationDomain("io.github.roundedrectangle");
    app->setApplicationName("fernschreiber2");

    QScopedPointer<MainShared::AppContext> appContext(MainShared::registerTypes(argc, argv, view));

    LOG("HELLOOOO" << SailfishyAsteroidApp::pathToMainQml() << appContext);

    view->setSource(SailfishyAsteroidApp::pathToMainQml());
    view->show();
    return app->exec();
}
