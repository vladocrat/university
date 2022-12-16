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

    enum RoomRoles {
        NameRole = Qt::UserRole + 1,
        StatusRole,
        PlayerCountRole,
        AccessStringRole,
        InitialBetRole,
        MaxPlayerCountRole,
    };
    Q_ENUM(RoomRoles);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

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
    QList<UserData> m_rooms;
};


