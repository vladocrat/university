#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "group.h"

class GroupModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum GroupRoles {
        NameRole
    };
    Q_ENUM(GroupRoles);

    void addGroup(const Group&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void clear();
    auto list() {return m_groups;}

    static void registerType()
    {
        qmlRegisterUncreatableType<GroupModel>("GroupModel", 1, 0, "GroupModel",
                                               "Cant create instance of GroupModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;


private:
    QList<Group> m_groups;
};

