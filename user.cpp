#include "user.h"

#include <string>

struct User::Credentials
{
    Credentials() {}
    Credentials(const std::string& l, const std::string& e) :
    login(l), email(e) {}

    std::string login;
    std::string email;
};

User::User()
{
    impl = std::make_unique<Credentials>();
}
