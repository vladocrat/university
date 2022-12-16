#pragma once

#include <string>
#include <unordered_map>
#include <QString>

enum class Role : uint8_t
{
    Admin = 0,
    MRO,
    Accountant
};

struct RoleHash
{
    std::size_t operator()(Role r) const
    {
        return static_cast<std::size_t>(r);
    }
};

const std::unordered_map<const Role, QString, RoleHash> mapRoleToString
{
    {Role::Admin, QString("Admin")},
    {Role::MRO, QString("MRO")},
    {Role::Accountant, QString("Accountant")}
};

static QString roleToString(Role r)
{
    return mapRoleToString.find(r)->second;
}

struct UserData
{
    QString roleStr() const
    {
        return roleToString(role);
    }

    Role role = Role::Admin;
    std::string login = "none";
    std::string email;
};

#define AdminString roleToString(Role::Admin)
#define MROString roleToString(Role::MRO)
#define AccountantString roleToString(Role::Accountant)
