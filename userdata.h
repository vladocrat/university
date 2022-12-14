#pragma once

#include <string>

enum Role
{
    Admin,
    MRO,
    Accountant
};

struct UserData
{
    Role role;
    std::string login;
    std::string email;
};
