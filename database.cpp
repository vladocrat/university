#include "database.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCryptographicHash>

#include "filecontroller.h"

using namespace DB;

Database::Database()
{

}

Database::~Database() noexcept
{
    m_db.close();
}

bool Database::connect(const Settings& s)
{
    m_settings = s;

    if (!isOpen())
    {
        auto db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName(s.hostName);
        db.setDatabaseName(s.dbName);
        db.setUserName(s.username);
        db.setPassword(s.password);
        db.setPort(s.port);
        m_db = db;
        LOGL("trying to connect to db");

        if (!m_db.open())
        {
            ERR("failed to open connection to db");
        }

        return m_db.open();
    }

    return false;
}

bool Database::isOpen() const
{
    return m_db.isOpen();
}

bool Database::userExists(const std::string& login) const
{
    //TODO
    return false;
}

std::optional<UserData> Database::login(const std::string &login, const std::string &password)
{
    if (!isOpen())
    {
        ERR("database is closed");
        return {};
    }

    UserData d;

    if (!userExists(login))
    {
        ERR(QString::fromStdString("user with login: " + login + " doesn't exist"));
    }

    /*d = select * from users where login = login and password = hash(password)
        if (d == null)
        {
            LOGL("user: " << login << " doesn't exist")
            return {};
        }
        d.login = q.login
        d.email = q.email
        d.role = q.role
    */

    return d;
}

QList<UserData> Database::getAllUsers()
{
    QList<UserData> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all users, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("SELECT * FROM users join access_rights as ar \
                       on users.access_rights_id = ar.access_rights_id"))
    {
        ERR(m_db.lastError());
    }

    if (!executeQuery(query))
    {
        return ret;
    }

    auto loginIx = query.record().indexOf("user_login");
    auto emailIx = query.record().indexOf("user_email");
    auto roleIx = query.record().indexOf("access_rights_type");

    QString login;
    QString email;
    QString role;

    while (query.next())
    {
        login = query.value(loginIx).toString();
        email = query.value(emailIx).toString();
        role = query.value(roleIx).toString();

        UserData d;
        d.login = login.toStdString();
        d.email = email.toStdString();
        d.role = stringToRole(role);
        ret.append(d);
    }

    LOGL("users fetched successfully");

    return ret;
}

bool Database::insert(const UserData& ud, const QString& password)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    QSqlQuery query;

    auto passwordHash = QCryptographicHash::hash(password.toUtf8(),
                                                 QCryptographicHash::Algorithm::Sha256);

    if (!query.prepare("insert into users (access_rights_id, user_password_hash, \
                      user_login, user_email) values (?,?,?,?)"))
    {
        ERR(m_db.lastError());
        qDebug() << m_db.lastError();
        return false;
    }

    query.bindValue(0, roleToInt(ud.role));
    query.bindValue(1, passwordHash);
    query.bindValue(2, QString::fromStdString(ud.login));
    query.bindValue(3, QString::fromStdString(ud.email));

    if (!executeQuery(query))
    {
        ERR("failed to insert user: " + ud.toString());
        return false;
    }

    LOGL("user added successfully");

    return true;
}

bool Database::deleteOne(const UserData &d)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from users where \
                        user_login = :login and user_email = :email \
                        and access_rights_id = :role"))
    {
        ERR(m_db.lastError());
    }

    query.bindValue(":login", QString::fromStdString(d.login), QSql::In);
    query.bindValue(":email", QString::fromStdString(d.email), QSql::In);
    query.bindValue(":role", QString::number(roleToInt(d.role)), QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete user: " + d.toString());
        return false;
    }

    LOGL("user: " + d.toString() +"  deleted successfully");

    return true;
}

bool Database::update(const UserData& newData, const UserData& userToUpdate, const QString& password)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;
    auto passwordHash = QCryptographicHash::hash(password.toUtf8(),
                        QCryptographicHash::Algorithm::Sha256);


    if (!query.prepare("update users \
                       set access_rights_id=:role, user_login=:login,\
                       user_email=:email, user_password_hash=:password \
                       where access_rights_id=:prevRole and user_login=:prevLogin \
                       and user_email=:email"))
    {
        ERR("failed to update user: " + userToUpdate.toString());
        return false;
    }

    query.bindValue(":role", QString::number(newData.roleInt()), QSql::In);
    query.bindValue(":login", QString::fromStdString(newData.login), QSql::In);
    query.bindValue(":email", QString::fromStdString(newData.email), QSql::In);
    query.bindValue(":password", passwordHash, QSql::In);
    query.bindValue(":prevRole", QString::number(userToUpdate.roleInt()), QSql::In);
    query.bindValue(":prevLogin", QString::fromStdString(userToUpdate.login), QSql::In);
    query.bindValue(":prevEmail", QString::fromStdString(userToUpdate.email), QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated user:" + userToUpdate.toString() + " successfully");

    return true;
}

QList<RoleString> Database::getAllAccessRights()
{
   QList<RoleString> ret;

   if (!isOpen())
   {
       ERR("failed to fetch all access rights, no connection to db");
       return ret;
   }

   QSqlQuery query;

   if (!query.prepare("SELECT * FROM access_rights"))
   {
      ERR(m_db.lastError());
      return ret;
   }

   if (!executeQuery(query))
   {
      ERR(m_db.lastError());
      return ret;
   }

   auto typeIx = query.record().indexOf("access_rights_type");

   while (query.next())
   {
       RoleString rs;
       rs.name = query.value(typeIx).toString();

       ret.append(rs);
   }

   LOGL("access rights fetched successfully");

   return ret;
}

bool Database::insert(const RoleString& rs)
{
   if (!isOpen())
   {
       ERR("db connection isnt open");
       return false;
   }

   QSqlQuery query;

   if (!query.prepare("insert into access_rights (access_rights_type) \
                      values (?)"))
   {
       ERR(m_db.lastError());
       return false;
   }

   query.bindValue(0, rs.name);

   if (!executeQuery(query))
   {
       ERR("failed to insert acess right: " + rs.name);
       return false;
   }

   LOGL("access rights added successfully");

   return true;
}

bool Database::deleteOne(const RoleString& rs)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from access_rights where access_rights_type=:type"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(":type", rs.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete access right: " + rs.name);
        return false;
    }

    LOGL("access right: " + rs.name +"  deleted successfully");

    return true;
}

bool Database::update(const RoleString& oldData, const RoleString& newData)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("update access_rights set \
                        access_rights_type = :new \
                        where access_rights_type = :old"))
    {
        ERR("failed to update access right: " + oldData.name);
        return false;
    }

    query.bindValue(":new", newData.name, QSql::In);
    query.bindValue(":old", oldData.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated access right:" + newData.name + " successfully");

    return true;
}

QList<Group> Database::getAllGroups()
{
    QList<Group> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all groups, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("SELECT * FROM groups"))
    {
       ERR(m_db.lastError());
       return ret;
    }

    if (!executeQuery(query))
    {
       ERR(m_db.lastError());
       return ret;
    }

    auto nameIx = query.record().indexOf("student_group_name");

    while (query.next())
    {
        Group g;
        g.name = query.value(nameIx).toString();

        ret.append(g);
    }

    LOGL("groups fetched successfully");

    return ret;
}

bool Database::insert(const Group& g)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("insert into groups (student_group_name) \
                       values (?)"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(0, g.name);

    if (!executeQuery(query))
    {
        ERR("failed to insert group: " + g.name);
        return false;
    }

    LOGL("group added successfully");

    return true;
}

bool Database::deleteOne(const Group& g)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from groups where student_group_name=:name"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(":name", g.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete group: " + g.name);
        return false;
    }

    LOGL("group: " + g.name +"  deleted successfully");

    return true;
}

bool Database::update(const Group& oldData, const Group& newData)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("update groups set \
                        student_group_name = :new \
                        where student_group_name = :old"))
    {
        ERR("failed to update group: " + oldData.name);
        return false;
    }

    query.bindValue(":new", newData.name, QSql::In);
    query.bindValue(":old", oldData.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated group:" + newData.name + " successfully");

    return true;
}

bool Database::executeQuery(QSqlQuery& query)
{
    if (!query.exec())
    {
        ERR("last query: " + query.executedQuery());
        ERR(m_db.lastError());

        return false;
    }

    return true;

}
