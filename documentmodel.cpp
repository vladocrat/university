#include "documentmodel.h"


void DocumentModel::addDocument(const Document& d)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_docs << d;
    endInsertRows();
}

int DocumentModel::rowCount(const QModelIndex &parent) const
{
    return m_docs.count();
}

QVariant DocumentModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_docs.count()) {
        return QVariant();
    }

    auto roleData = m_docs[index.row()];
    switch (role)
    {
    case PathRole:
    {
        return roleData.path;
    }
    default:
        return QVariant();
    }
}

void DocumentModel::clear()
{
    beginResetModel();
    m_docs.clear();
    endResetModel();
}

QHash<int, QByteArray> DocumentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PathRole] = "path";

    return roles;
}
