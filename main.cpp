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
#include "grouprepository.h"
#include "contracttyperepository.h"
#include "documentrepository.h"
#include "gapyearrepository.h"

///! models
#include "usersmodel.h"
#include "accessrightsmodel.h"
#include "groupmodel.h"
#include "contracttypemodel.h"
#include "documentmodel.h"
#include "gapyearmodel.h"

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
    groupRepository->registerType();
    contractTypeRepository->registerType();
    documentRepository->registerType();
    gapYearRepository->registerType();
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
    engine.rootContext()->setContextProperty("groupModel", groupRepository->model());
    engine.rootContext()->setContextProperty("contractTypeModel", contractTypeRepository->model());
    engine.rootContext()->setContextProperty("documentsModel", documentRepository->model());
    engine.rootContext()->setContextProperty("gapYearModel", gapYearRepository->model());

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
