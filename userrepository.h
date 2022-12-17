#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QList>

#include "userdata.h"
#include "usersmodel.h"

class UserRepository final : public QObject
{
    Q_OBJECT
public:
    static UserRepository* instance()
    {
        static UserRepository uc;
        return &uc;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const UserData&, const QString& password);
    Q_INVOKABLE bool deleteOne(const UserRepository &);
    Q_INVOKABLE bool update(const UserRepository &);

    UsersModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<UserRepository>
                ("UserRepository", 1, 0,"UserRepository",
                 UserRepository::instance());
    }

private:
    UserRepository() = default;
    ~UserRepository() = default;
    UserRepository(const UserRepository&) = delete;
    UserRepository(UserRepository&&) = delete;
    UserRepository operator=(const UserRepository&) = delete;

    UsersModel m_model;
};

#define userRepository UserRepository::instance()
