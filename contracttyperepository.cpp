#include "contracttyperepository.h"

#include "databasecontroller.h"

void ContractTypeRepository::getAll()
{
    auto all = dbController->getAllContractTypes();
    m_model.clear();

    for (const auto& x : all)
    {
        m_model.addType(x);
    }
}

bool ContractTypeRepository::insert(const QString &name)
{
    ContractType t;
    t.name = name;
    return dbController->insert(t);
}

bool ContractTypeRepository::deleteOne(int ix)
{
    return dbController->deleteOne(m_model.list().at(ix));
}

bool ContractTypeRepository::update(const QString &name, int ix)
{
    ContractType newData;
    newData.name = name;
    auto typeToUpdate = m_model.list().at(ix);
    return dbController->update(typeToUpdate, newData);
}
