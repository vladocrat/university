#include "logincontroller.h"

#include "databasecontroller.h"

bool LoginController::login(const std::string &email, const std::string &password) const
{
    return dbController->login(email, password);
}

