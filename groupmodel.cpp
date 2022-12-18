#include "groupmodel.h"

void GroupModel::addGroup(const Group& g)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_groups << g;
    endInsertRows();
}

int GroupModel::rowCount(const QModelIndex &parent) const
{
    return m_groups.count();
}

QVariant GroupModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_groups.count()) {
        return QVariant();
    }

    auto roleData = m_groups[index.row()];
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

void GroupModel::clear()
{
    beginResetModel();
    m_groups.clear();
    endResetModel();
}

QHash<int, QByteArray> GroupModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";

    return roles;
}
