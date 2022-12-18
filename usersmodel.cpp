#include "usersmodel.h"

UsersModel::UsersModel()
{

}

void UsersModel::addUser(const UserData& ud)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_users << ud;
    endInsertRows();
}

///! TODO
int UsersModel::rowCount(const QModelIndex &parent) const
{
    return m_users.count();
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    Q_FUNC_INFO;

    if (index.row() < 0 || index.row() >= m_users.count()) {
            return QVariant();
        }

        auto userData = m_users[index.row()];
        switch (role){
        case RoleRole: {
            return userData.roleStr();
        }
        case LoginRole: {
            return QString::fromStdString(userData.login);
        }
        case EmailRole: {
            return QString::fromStdString(userData.email);
        }
        default:
            return QVariant();
        }
}

void UsersModel::clear()
{
    beginResetModel();
    m_users.clear();
    endResetModel();
}

void UsersModel::updateUsers(const UserData &ud)
{

}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[RoleRole] = "role";
        roles[LoginRole] = "login";
        roles[EmailRole] = "email";

    return roles;
}
