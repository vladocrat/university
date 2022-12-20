#include "contracttypemodel.h"

void ContractTypeModel::addType(const ContractType& ct)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_types << ct;
    endInsertRows();
}

int ContractTypeModel::rowCount(const QModelIndex &parent) const
{
    return m_types.count();
}

QVariant ContractTypeModel::data(const QModelIndex &index, int role) const
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

void ContractTypeModel::clear()
{
    beginResetModel();
    m_types.clear();
    endResetModel();
}

QHash<int, QByteArray> ContractTypeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";

    return roles;
}
