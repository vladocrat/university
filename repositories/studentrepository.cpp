#include "studentrepository.h"

#include "databasecontroller.h"
#include "filecontroller.h"

void StudentRepository::getAll()
{
    auto all = dbController->getAllStudents();
    m_model.clear();

    for (const auto& x : all)
    {
        LOGL(x.toString());
        m_model.add(x);
    }
}

bool StudentRepository::insert(const QString &name, int groupIx)
{
return {};
}

bool StudentRepository::deleteOne(int)
{
return {};
}

bool StudentRepository::update(const QString &name, int ix)
{
    return {};
}
