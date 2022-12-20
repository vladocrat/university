#include "accessrightsmodel.h"

void AccessRightsModel::addRole(const RoleString& rs)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_roles << rs;
    endInsertRows();

}

int AccessRightsModel::rowCount(const QModelIndex &parent) const
{
    return m_roles.count();
}

QVariant AccessRightsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_roles.count()) {
        return QVariant();
    }

    auto roleData = m_roles[index.row()];
    switch (role)
    {
    case NameRole:
    {
        return roleData.name;
    }
    default:
        return QVariant();
    }
}

void AccessRightsModel::clear()
{
    beginResetModel();
    m_roles.clear();
    endResetModel();
}

QHash<int, QByteArray> AccessRightsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";

    return roles;
}
