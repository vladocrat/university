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

int Database::groupId(const QString &s)
{
    int ix = -1;

    if (!isOpen())
    {
        ERR("db connection isn't open");
        return ix;
    }

    QSqlQuery query;

    if (!query.prepare("select student_group_id from groups where student_group_name = :name"))
    {
        ERR(m_db.lastError());
        return ix;
    }

    query.bindValue(":name", s, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to select student id");
        return ix;
    }

    auto gorupIx = query.record().indexOf("student_group_id");

    while (query.next())
    {
       ix = query.value(gorupIx).toInt();
    }

    LOGL("group index: " + QString::number(ix) + " fetched successfully");

    return ix;
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

QList<ContractType> Database::getAllContractTypes()
{
    QList<ContractType> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all ContractTypes, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("SELECT * FROM contract_type"))
    {
       ERR(m_db.lastError());
       return ret;
    }

    if (!executeQuery(query))
    {
       ERR(m_db.lastError());
       return ret;
    }

    auto nameIx = query.record().indexOf("contract_type");

    while (query.next())
    {
        ContractType ct;
        ct.name = query.value(nameIx).toString();

        ret.append(ct);
    }

    LOGL("contract types fetched successfully");

    return ret;
}

bool Database::insert(const ContractType& ct)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("insert into contract_type (contract_type) \
                       values (?)"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(0, ct.name);

    if (!executeQuery(query))
    {
        ERR("failed to insert ContractType: " + ct.name);
        return false;
    }

    LOGL("ContractType added successfully");

    return true;
}

bool Database::deleteOne(const ContractType& ct)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from contract_type where contract_type=:name"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(":name", ct.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete ContractType: " + ct.name);
        return false;
    }

    LOGL("ContractType: " + ct.name +"  deleted successfully");

    return true;
}

bool Database::update(const ContractType& oldData, const ContractType& newData)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("update contract_type set \
                        contract_type = :new \
                        where contract_type = :old"))
    {
        ERR("failed to update contract_type: " + oldData.name);
        return false;
    }

    query.bindValue(":new", newData.name, QSql::In);
    query.bindValue(":old", oldData.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated contract_type:" + newData.name + " successfully");

                       return true;
}

QList<Document> Database::getAllDocuments()
{
    QList<Document> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all Documents, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("SELECT * FROM documents"))
    {
       ERR(m_db.lastError());
       return ret;
    }

    if (!executeQuery(query))
    {
       ERR(m_db.lastError());
       return ret;
    }

    auto pathIx = query.record().indexOf("documents_file_location");

    while (query.next())
    {
        Document d;
        d.path = query.value(pathIx).toString();

        ret.append(d);
    }

    LOGL("documents fetched successfully");

    return ret;
}

bool Database::insert(const Document& d)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("insert into documents (documents_file_location) \
                       values (?)"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(0, d.path);

    if (!executeQuery(query))
    {
        ERR("failed to insert documents: " + d.path);
        return false;
    }

    LOGL("documents added successfully");

    return true;
}

bool Database::deleteOne(const Document& d)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from documents where documents_file_location=:path"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(":path", d.path, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete documents: " + d.path);
        return false;
    }

    LOGL("documents: " + d.path + "  deleted successfully");

    return true;
}

bool Database::update(const Document& oldData, const Document& newData)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("update documents set \
                        documents_file_location = :new \
                        where documents_file_location = :old"))
    {
        ERR("failed to update Document: " + oldData.path);
        return false;
    }

    query.bindValue(":new", newData.path, QSql::In);
    query.bindValue(":old", oldData.path, QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated Document:" + newData.path + " successfully");

    return true;
}

QList<GapYear> Database::getAllGapYears()
{
    QList<GapYear> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all GapYears, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("select cap_year_start, cap_year_end, documents_file_location, user_login, \
                       user_email, access_rights_type from cap_year_journal c \
                       join documents on c.documents_document_id = documents.documents_document_id \
                       join users on c.user_id = users.user_id \
                       join access_rights as ar on ar.access_rights_id = users.access_rights_id"))
    {
       ERR(m_db.lastError());
       return ret;
    }

    if (!executeQuery(query))
    {
       ERR(m_db.lastError());
       return ret;
    }

    auto gapYearStartIx = query.record().indexOf("cap_year_start");
    auto gapYearEndIx = query.record().indexOf("cap_year_end");
    auto pathIx = query.record().indexOf("documents_file_location");
    auto userLoginIx = query.record().indexOf("user_login");
    auto userEmailIx = query.record().indexOf("user_email");
    auto userRoleIx = query.record().indexOf("access_rights_type");

    while (query.next())
    {
        UserData* ud = new UserData;
        ud->login = query.value(userLoginIx).toString().toStdString();
        ud->email = query.value(userEmailIx).toString().toStdString();
        ud->role = stringToRole(query.value(userRoleIx).toString());
        Document d;
        d.path = query.value(pathIx).toString();
        GapYear gy;
        gy.creator = ud;
        gy.document = d;
        gy.start_date = query.value(gapYearStartIx).toString();
        gy.end_date = query.value(gapYearEndIx).toString();

        ret.append(gy);
    }

    LOGL("GapYears fetched successfully");

    return ret;
}

bool Database::insert(const GapYear &)
{
    return false;
}

bool Database::deleteOne(const GapYear &)
{
return false;
}

bool Database::update(const GapYear &, const GapYear &)
{
 return false;
}

QList<PassportTypeString> Database::getAllPassportTypes()
{
    QList<PassportTypeString> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all pts, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("SELECT * FROM passport_type"))
    {
       ERR(m_db.lastError());
       return ret;
    }

    if (!executeQuery(query))
    {
       ERR(m_db.lastError());
       return ret;
    }

    auto typeIx = query.record().indexOf("passport_type");

    while (query.next())
    {
        PassportTypeString pts;
        pts.name = query.value(typeIx).toString();

        ret.append(pts);
    }

    LOGL("passport_type fetched successfully");

    return ret;
}

bool Database::insert(const PassportTypeString& pst)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("insert into passport_type (passport_type) \
                       values (?)"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(0, pst.name);

    if (!executeQuery(query))
    {
        ERR("failed to insert passport_type: " + pst.name);
        return false;
    }

    LOGL("passport_type added successfully");

    return true;
}

bool Database::deleteOne(const PassportTypeString& pst)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from passport_type where passport_type=:name"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(":name", pst.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete passport_type: " + pst.name);
        return false;
    }

    LOGL("passport_type: " + pst.name + "  deleted successfully");

    return true;
}

bool Database::update(const PassportTypeString& oldData, const PassportTypeString& newData)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("update passport_type set \
                        passport_type = :new \
                        where passport_type = :old"))
    {
        ERR("failed to update Document: " + oldData.name);
        return false;
    }

    query.bindValue(":new", newData.name, QSql::In);
    query.bindValue(":old", oldData.name, QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated passport_type:" + newData.name + " successfully");

    return true;
}

QList<Dormitory> Database::getAllDormitories()
{
    QList<Dormitory> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all Dormitories, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("select dormitory_address, dormitory_room_number, dormitory_status, \
                       student_full_name, student_group_name from dormitory \
                       join student s on dormitory.student_id = s.student_id \
                       join groups g on s.student_group_id = g.student_group_id"))
    {
       ERR(m_db.lastError());
       return ret;
    }

    if (!executeQuery(query))
    {
       ERR(m_db.lastError());
       return ret;
    }

    auto addressIx = query.record().indexOf("dormitory_address");
    auto roomNumberIx = query.record().indexOf("dormitory_room_number");
    auto statusIx = query.record().indexOf("dormitory_status");
    auto studentNameIx = query.record().indexOf("student_full_name");
    auto studentGroupNameIx = query.record().indexOf("student_group_name");

    while (query.next())
    {
        Dormitory d;
        d.address = query.value(addressIx).toString();
        d.roomNumber = query.value(roomNumberIx).toInt();
        d.status = stringToStatus(query.value(statusIx).toString());
        Student* s = new Student;
        s->fullName = query.value(studentNameIx).toString();
        Group g;
        g.name = query.value(studentGroupNameIx).toString();
        s->group = g;
        d.student = s;
        ret.append(d);
    }

    LOGL("Dormitory fetched successfully");

    return ret;
}

bool Database::insert(const Dormitory& d)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    auto studId = studentId(*d.student);

    QSqlQuery query;

    if (!query.prepare("insert into dormitory (dormitory_address, dormitory_room_number, dormitory_status, student_id) \
                       values (?,?,?,?)"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(0, d.address);
    query.bindValue(1, d.roomNumber);
    query.bindValue(2, d.statusString());
    query.bindValue(3, studId);

    if (!executeQuery(query))
    {
        ERR("failed to insert dormitory: ");
        return false;
    }

    LOGL("dormitory added successfully");

    return true;
}

bool Database::deleteOne(const Dormitory &)
{
return {};
}

bool Database::update(const Dormitory &, const Dormitory &)
{
  return {};
}

int Database::studentId(const Student& s)
{
    int ix = -1;

    if (!isOpen())
    {
        ERR("db connection isn't open");
        return ix;
    }

    QSqlQuery query;

    if (!query.prepare("select student_id from student where student_full_name = :fullName"))
    {
        ERR(m_db.lastError());
        return ix;
    }

    query.bindValue(":fullName", s.fullName, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to select student id");
        return ix;
    }

    auto studentIx = query.record().indexOf("student_id");

    while (query.next())
    {
       ix = query.value(studentIx).toInt();
    }

    LOGL("user index: " + QString::number(ix) + " fetched successfully");

    return ix;
}

QList<Student> Database::getAllStudents()
{
    QList<Student> ret;

    if (!isOpen())
    {
        ERR("db connection isn't open");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("select student_full_name, student_group_name from student \
                        join groups on student.student_group_id = groups.student_group_id"))
    {
        ERR(m_db.lastError());
        return ret;
    }

    if (!executeQuery(query))
    {
        ERR("failed to select students");
        return ret;
    }

    auto nameIx = query.record().indexOf("student_full_name");
    auto groupIx = query.record().indexOf("student_group_name");

    while (query.next())
    {
       Group g;
       Student s;
       s.fullName = query.value(nameIx).toString();
       g.name = query.value(groupIx).toString();
       s.group = g;
       ret.append(s);
    }

    LOGL("students fetched successfully");

    return ret;
}

bool Database::insert(const Student& s, int groupId)
{
    if (!isOpen())
    {
        ERR("db connection isnt open");
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("insert into student (student_full_name, student_group_id) \
                       values (?, ?)"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(0, s.fullName);
    query.bindValue(1, groupId);

    if (!executeQuery(query))
    {
        ERR("failed to insert student: " + s.toString());
        return false;
    }

    LOGL("student added successfully");

    return true;
}

bool Database::deleteOne(const Student& s)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("delete from student where student_full_name=:name"))
    {
        ERR(m_db.lastError());
        return false;
    }

    query.bindValue(":name", s.fullName, QSql::In);

    if (!executeQuery(query))
    {
        ERR("failed to delete student: " + s.fullName);
        return false;
    }

    LOGL("student: " + s.toString() + "  deleted successfully");

                       return true;
}

bool Database::update(const Student& oldData, const Student& newData, int groupId, int capYearRecordId)
{
    if (!isOpen())
    {
        ERR(m_db.lastError());
        return false;
    }

    QSqlQuery query;

    if (!query.prepare("update student set \
                        student_full_name = :new, student_group_id = :groupId, cap_year_record_id = :capYeaId\
                        where student_full_name = :old"))
    {
        ERR("failed to update Student: " + oldData.fullName);
        return false;
    }

    query.bindValue(":groupId", groupId, QSql::In);
    query.bindValue(":capYeaId", capYearRecordId, QSql::In);
    query.bindValue(":new", newData.fullName, QSql::In);
    query.bindValue(":old", oldData.fullName, QSql::In);

    if (!executeQuery(query))
    {
        ERR(m_db.lastError());
        return false;
    }

    LOGL("updated student:" + newData.toString() + " successfully");

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
