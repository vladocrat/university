#include "studentrepository.h"

#include "databasecontroller.h"
#include "filecontroller.h"

void StudentRepository::getAll()
{
    auto all = dbController->getAllStudents();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.add(x);
    }
}

bool StudentRepository::insert(const QString &name, QString groupName)
{
    auto groupId = dbController->groupId(groupName);
    Student s;
    s.fullName = name;
    s.group.name = groupName;

    return dbController->insert(s, groupId);
}

bool StudentRepository::deleteOne(int ix)
{
    return dbController->deleteOne(m_model.list().at(ix));
}

bool StudentRepository::update(const QString &name, int ix)
{
    return {};
}
