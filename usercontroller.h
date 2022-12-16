#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QList>

#include "userdata.h"

class UserController : public QObject
{
    Q_OBJECT
public:
    static UserController* instance()
    {
        static UserController uc;
        return &uc;
    }

    QList<UserData> allUsers();

    static void registerType()
    {
        qmlRegisterSingletonInstance<UserController>
                ("UserController", 1, 0,"UserController",
                 UserController::instance());
    }

private:
    UserController() = default;
    ~UserController() = default;
    UserController(const UserController&) = delete;
    UserController(UserController&&) = delete;
    UserController operator=(const UserController&) = delete;
};

#define userController UserController::instance()
