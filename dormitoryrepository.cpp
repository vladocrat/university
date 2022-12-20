#include "dormitoryrepository.h"

#include "databasecontroller.h"

void DormitoryRepository::getAll()
{
    auto all = dbController->getAllDormitories();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.add(x);
    }
}

bool DormitoryRepository::insert(const QString &name)
{
return false;
}

bool DormitoryRepository::deleteOne(int)
{
return false;
}

bool DormitoryRepository::update(const QString &name, int ix)
{
return false;
}
