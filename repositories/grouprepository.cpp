#include "grouprepository.h"

#include "databasecontroller.h"

void GroupRepository::getAll()
{
    auto all = dbController->getAllGroups();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.addGroup(x);
    }
}

bool GroupRepository::insert(const QString &name)
{
    Group g;
    g.name = name;

    return dbController->insert(g);
}

bool GroupRepository::deleteOne(int ix)
{
    return dbController->deleteOne(m_model.list().at(ix));
}

bool GroupRepository::update(const QString &name, int ix)
{
    auto groupToUpdate = m_model.list().at(ix);
    Group g;
    g.name = name;

    return dbController->update(groupToUpdate, g);
}
