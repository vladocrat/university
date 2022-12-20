#include "studentmodel.h"

void StudentModel::add(const Student& s)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_list << s;
    endInsertRows();
}

int StudentModel::rowCount(const QModelIndex &parent) const
{
    return m_list.count();
}

QVariant StudentModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.count()) {
        return QVariant();
    }

    auto roleData = m_list[index.row()];
    switch (role)
    {
    case NameRole:
    {
        return roleData.fullName;
    }
    case GroupRole:
    {
        return roleData.group.name;
    }
    default:
        return QVariant();
    }
}

void StudentModel::clear()
{
    beginResetModel();
    m_list.clear();
    endResetModel();
}

QHash<int, QByteArray> StudentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[GroupRole] = "group";

    return roles;
}
