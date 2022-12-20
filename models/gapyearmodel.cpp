#include "gapyearmodel.h"


void GapYearModel::add(const GapYear& g)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_years << g;
    endInsertRows();
}

int GapYearModel::rowCount(const QModelIndex &parent) const
{
    return m_years.count();
}

QVariant GapYearModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_years.count()) {
        return QVariant();
    }

    auto roleData = m_years[index.row()];
    switch (role)
    {
    case DocumentRole:
    {
        return roleData.document.path;
    }
    case CreatorLoginRole:
    {
        return QString::fromStdString(roleData.creator->login);
    }
    case CreatorEmailRole:
    {
        return QString::fromStdString(roleData.creator->email);
    }
    case CreatorRoleRole:
    {
        return roleData.creator->roleStr();
    }
    case StartDateRole:
    {
        return roleData.start_date;
    }
    case EndDateRole:
    {
        return roleData.end_date;
    }
    default:
        return QVariant();
    }
}

void GapYearModel::clear()
{
    beginResetModel();
    m_years.clear();
    endResetModel();
}

QHash<int, QByteArray> GapYearModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DocumentRole] = "docPath";
    roles[CreatorLoginRole] = "creatorLogin";
    roles[CreatorEmailRole] = "creatorEmail";
    roles[CreatorRoleRole] = "creatorRole";
    roles[StartDateRole] = "startDate";
    roles[EndDateRole] = "endDate";

    return roles;
}
