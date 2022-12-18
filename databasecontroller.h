#pragma once

#include "database.h"
#include "dbsettings.h"
#include <optional>

class DatabaseController final
{
public:
    static DatabaseController* instance()
    {
        static DatabaseController dc;
        return &dc;
    }

    [[nodiscard]] bool connect(const DB::Settings& s);
    [[nodiscard]] bool login(const std::string& login, const std::string& password);

    ///! userdata
    [[nodiscard]] QList<UserData> getAllUsers();
    [[nodiscard]] bool insert(const UserData& d, const QString& password);
    [[nodiscard]] bool deleteOne(const UserData& d);
    [[nodiscard]] bool update(const UserData& newData, const UserData& userToUpdate, const QString& password);

private:
    DatabaseController() = default;
    ~DatabaseController() = default;
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController(DatabaseController&&) = delete;
    DatabaseController operator=(const DatabaseController&) = delete;

    DB::Database m_db;
};

#define dbController DatabaseController::instance()
