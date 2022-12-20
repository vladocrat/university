#include "dormitorymodel.h"


void DormitoryModel::add(const Dormitory& d)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_list << d;
    endInsertRows();
}

int DormitoryModel::rowCount(const QModelIndex &parent) const
{
    return m_list.count();
}

QVariant DormitoryModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.count()) {
        return QVariant();
    }

    auto roleData = m_list[index.row()];
    switch (role)
    {
    case AddressRole:
    {
        return roleData.address;
    }
    case RoomNumberRole:
    {
        return roleData.roomNumber;
    }
    case StatusRole:
    {
        return roleData.statusString();
    }
    case StudentFullNameRole:
    {
        return roleData.student->fullName;
    }
    case StudentGroupRole:
    {
        return roleData.student->group.name;
    }
    default:
        return QVariant();
    }
}

void DormitoryModel::clear()
{
    beginResetModel();
    m_list.clear();
    endResetModel();
}

QHash<int, QByteArray> DormitoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AddressRole] = "address";
    roles[RoomNumberRole] = "roomNumber";
    roles[StatusRole] = "status";
    roles[StudentFullNameRole] = "studentName";
    roles[StudentGroupRole] = "studentGroup";

    return roles;
}
