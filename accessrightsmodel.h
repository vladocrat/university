#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QObject>

#include "userdata.h"

class AccessRightsModel final : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoleRoles {
        NameRole
    };
    Q_ENUM(RoleRoles);

    void addRole(const RoleString&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void clear();

    auto list() {return m_roles;}

    static void registerType()
    {
        qmlRegisterUncreatableType<AccessRightsModel>("UsersModel", 1, 0, "UsersModel",
                                               "Cant create instance of UsersModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<RoleString> m_roles;
};

