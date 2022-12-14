#pragma once

#include <QSqlDatabase>
#include <optional>

#include "userdata.h"
#include "dbsettings.h"

namespace DB {

class Database
{
public:
    Database();
    ~Database() noexcept;

    [[nodiscard]] bool connect(const Settings& s);
    [[nodiscard]] bool isOpen() const;
    [[nodiscard]] bool userExists(const std::string& login) const;
    [[nodiscard]] std::optional<UserData> login(const std::string& login, const std::string& password);
    [[nodiscard]] bool registration(const std::string& login, const std::string& email, const std::string& password);

private:
   QSqlDatabase m_db;
};

} // DB

