#pragma once

#include <memory>

class User
{
public:
    enum Role {
        Admin,
        MRO,
        Accountant
    };

    User();
    ~User();

    Role role() const {return m_role;}

private:
    Role m_role;
    struct Credentials;
    std::unique_ptr<Credentials> impl;
};


