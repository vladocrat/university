#include "gapyearrepository.h"

#include "databasecontroller.h"

void GapYearRepository::getAll()
{
    auto all = dbController->getAllGapYears();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.add(x);
    }
}

bool GapYearRepository::insert()
{
    return false;
    //return dbController->insert()
}

bool GapYearRepository::deleteOne(int)
{
    return false;
}

bool GapYearRepository::update(const QString &path, int ix)
{
return false;
}

