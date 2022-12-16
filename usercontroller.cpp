#include "usercontroller.h"

#include "databasecontroller.h"

QList<UserData> UserController::allUsers()
{
    return dbController->getAllUsers();
}
