#include "passporttypemodel.h"


void PassportTypeModel::addType(const PassportTypeString &pt)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_types << pt;
    endInsertRows();
}

int PassportTypeModel::rowCount(const QModelIndex &parent) const
{
    return m_types.count();
}

QVariant PassportTypeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_types.count()) {
        return QVariant();
    }

    auto roleData = m_types[index.row()];
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

void PassportTypeModel::clear()
{
    beginResetModel();
    m_types.clear();
    endResetModel();
}

QHash<int, QByteArray> PassportTypeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";

    return roles;
}
