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
    [[nodiscard]] QList<UserData> getAllUsers();

private:
    DatabaseController() = default;
    ~DatabaseController() = default;
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController(DatabaseController&&) = delete;
    DatabaseController operator=(const DatabaseController&) = delete;

    DB::Database m_db;
};

#define dbController DatabaseController::instance()
