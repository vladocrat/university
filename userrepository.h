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
    Q_INVOKABLE bool insert(const QString& login, const QString& email, const QString& role, const QString& password);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const UserRepository &);
    Q_INVOKABLE int userCount();

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
