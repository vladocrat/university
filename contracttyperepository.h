#pragma once

#include <QObject>
#include <QQmlEngine>

#include "contracttypemodel.h"

class ContractTypeRepository : public QObject
{
    Q_OBJECT
public:
    static ContractTypeRepository* instance()
    {
        static ContractTypeRepository r;
        return &r;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& name);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& name, int ix);

    ContractTypeModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<ContractTypeRepository>
                ("ContractTypeRepository", 1, 0,"ContractTypeRepository",
                 ContractTypeRepository::instance());
    }

private:
    ContractTypeRepository() = default;
    ~ContractTypeRepository() = default;
    ContractTypeRepository(const ContractTypeRepository&) = delete;
    ContractTypeRepository(ContractTypeRepository&&) = delete;
    ContractTypeRepository operator=(const ContractTypeRepository&) = delete;

    ContractTypeModel m_model;
};

#define contractTypeRepository ContractTypeRepository::instance()

