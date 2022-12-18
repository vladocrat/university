#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "user.h"
#include "DB_config.h"

///! controllers
#include "logincontroller.h"
#include "menucontroller.h"
#include "databasecontroller.h"
#include "filecontroller.h"

///! repositories
#include "userrepository.h"
#include "accessrightsrepository.h"

///! models
#include "usersmodel.h"
#include "accessrightsmodel.h"

#include <iostream>

static void registerTypes()
{
    User::instance()->registerType();

    ///! controllers
    loginController->registerType();
    menuController->registerType();

    ///! repositories
    userRepository->registerType();
    accessRightsRepository->registerType();
}

static void initDB()
{
    DB::Settings s;
    s.hostName = HOST_NAME;
    s.dbName = DB_NAME;
    s.username = USERNAME;
    s.password = PASSWORD;
    s.port = PORT;

    if (dbController->connect(s))
    {
        LOGL("connection established successfully");
    }
}

static void initLogger()
{
    fileController->init("log.txt");
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    initLogger();

    QGuiApplication app(argc, argv);

    registerTypes();

    QQmlApplicationEngine engine;

    initDB();

    ///! models
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("usersModel", userRepository->model());
    engine.rootContext()->setContextProperty("accessRightsModel", accessRightsRepository->model());

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
