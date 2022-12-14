#pragma once

#include <QSqlDatabase>

#include "dbsettings.h"

namespace DB {

class Database
{
public:
    Database();
    ~Database() noexcept;

    bool connect(const Settings& s);
    bool isOpen() const;
    bool login(const std::string& login, const std::string& password);
    bool registration(const std::string& login, const std::string& email, const std::string& password);

private:
   QSqlDatabase m_db;
};

} // DB

