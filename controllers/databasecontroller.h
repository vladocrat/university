#pragma once

#include "database.h"
#include "dbsettings.h"
#include "contracttype.h"
#include "document.h"
#include "GapYear.h"
#include "passport.h"
#include "Dormitory.h"

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

    ///! accessrights
    [[nodiscard]] QList<RoleString> getAllRoles();
    [[nodiscard]] bool insert(const RoleString&);
    [[nodiscard]] bool deleteOne(const RoleString&);
    [[nodiscard]] bool update(const RoleString& oldData, const RoleString& newData);

    ///! group
    [[nodiscard]] QList<Group> getAllGroups();
    [[nodiscard]] bool insert(const Group&);
    [[nodiscard]] bool deleteOne(const Group&);
    [[nodiscard]] bool update(const Group& oldData, const Group& newData);

    ///! contracttype
    [[nodiscard]] QList<ContractType> getAllContractTypes();
    [[nodiscard]] bool insert(const ContractType&);
    [[nodiscard]] bool deleteOne(const ContractType&);
    [[nodiscard]] bool update(const ContractType& oldData, const ContractType& newData);

    ///! documents
    [[nodiscard]] QList<Document> getAllDocuments();
    [[nodiscard]] bool insert(const Document&);
    [[nodiscard]] bool deleteOne(const Document&);
    [[nodiscard]] bool update(const Document& oldData, const Document& newData);

    ///! gayear
    [[nodiscard]] QList<GapYear> getAllGapYears();
    [[nodiscard]] bool insert(const GapYear&);
    [[nodiscard]] bool deleteOne(const GapYear&);
    [[nodiscard]] bool update(const GapYear& oldData, const GapYear& newData);

    ///! passportType
    [[nodiscard]] QList<PassportTypeString> getAllPassportTypes();
    [[nodiscard]] bool insert(const PassportTypeString&);
    [[nodiscard]] bool deleteOne(const PassportTypeString&);
    [[nodiscard]] bool update(const PassportTypeString& oldData, const PassportTypeString& newData);

    ///! Dormitory
    [[nodiscard]] QList<Dormitory> getAllDormitories();
    [[nodiscard]] bool insert(const Dormitory&);
    [[nodiscard]] bool deleteOne(const Dormitory&);
    [[nodiscard]] bool update(const Dormitory& oldData, const Dormitory& newData);

    ///! student
    [[nodiscard]] QList<Student> getAllStudents();

private:
    DatabaseController() = default;
    ~DatabaseController() = default;
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController(DatabaseController&&) = delete;
    DatabaseController operator=(const DatabaseController&) = delete;

    DB::Database m_db;
};

#define dbController DatabaseController::instance()
