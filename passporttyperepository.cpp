#include "passporttyperepository.h"

#include "databasecontroller.h"
#include "filecontroller.h"

void PassportTypeRepository::getAll()
{
    auto all = dbController->getAllPassportTypes();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.addType(x);
    }
}

bool PassportTypeRepository::insert(const QString &name)
{
    PassportTypeString str;
    str.name = name;
    return dbController->insert(str);
}

bool PassportTypeRepository::deleteOne(int ix)
{
    return dbController->deleteOne(m_model.list().at(ix));
}

bool PassportTypeRepository::update(const QString &name, int ix)
{
    auto oldData = m_model.list().at(ix);
    PassportTypeString pts;
    pts.name = name;

    return dbController->update(oldData, pts);
}
