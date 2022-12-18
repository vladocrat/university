#include "accessrightsrepository.h"

void AccessRightsRepository::getAll()
{
    auto all = dbController->getAllRoles();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.addRole(x);
    }
}

bool AccessRightsRepository::insert(const QString &name)
{
    RoleString s;
    s.name = name;

    return dbController->insert(s);
}

bool AccessRightsRepository::deleteOne(int ix)
{
    return dbController->deleteOne(m_model.list().at(ix));
}

bool AccessRightsRepository::update(const QString& name, int ix)
{
    auto roleToUpdate = m_model.list().at(ix);
    RoleString rs;
    rs.name = name;

    return dbController->update(roleToUpdate, rs);
}


