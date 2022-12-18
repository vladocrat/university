#pragma once

#include <QSqlDatabase>
#include <optional>
#include <QList>
#include <QDebug>

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

    ///! userdata
    [[nodiscard]] QList<UserData> getAllUsers();
    [[nodiscard]] bool insert(const UserData&, const QString& password);
    [[nodiscard]] bool deleteOne(const UserData& d);
    [[nodiscard]] bool update(const UserData& user, const UserData& userToUpdate, const QString& password);


private:
   [[nodiscard]] bool executeQuery(QSqlQuery& query);

   QSqlDatabase m_db;
   Settings m_settings;
};

} // DB

