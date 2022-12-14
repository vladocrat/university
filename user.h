#pragma once

#include <memory>
#include <QObject>
#include <QQmlEngine>

#include "userdata.h"

class User : public QObject
{
    Q_OBJECT
public:
    static User* instance()
    {
        static User user;
        return &user;
    }

    Q_PROPERTY(Role role READ role NOTIFY roleChanged)

    Role role() const   {return m_data.role;}
    UserData* data()    {return &m_data;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<User>("User", 1, 0, "User", User::instance());
    }

signals:
    void roleChanged();

private:
    User() = default;
    ~User() = default;
    User(const User&) = delete;
    User(User&&) = delete;
    User operator=(const User&) = delete;

    UserData m_data;
};

#define user User::instance()
