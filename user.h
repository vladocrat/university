#pragma once

#include <memory>
#include <QObject>
#include <QQmlEngine>
#include <QString>

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

    Q_PROPERTY(QString role READ role NOTIFY roleChanged)

    QString role()  const {return m_data.roleStr();}
    QString login() const {return QString::fromStdString(m_data.login);}
    UserData* data()      {return &m_data;}

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
