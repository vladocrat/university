#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QObject>
#include <QList>
#include "userdata.h"

class UsersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    UsersModel();

    enum UserDataRoles {
        RoleRole,
        LoginRole,
        EmailRole
    };
    Q_ENUM(UserDataRoles);

    void addUser(const UserData&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QList<UserData> list() const {return m_users;}
    void clear();

    static void registerType()
    {
        qmlRegisterUncreatableType<UsersModel>("UsersModel", 1, 0, "UsersModel",
                                               "Cant create instance of UsersModel");
    }

private slots:
    void updateUsers(const UserData& ud);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<UserData> m_users;
};


