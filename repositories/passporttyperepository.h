#pragma once

#include <QObject>
#include <QQmlEngine>

#include "passporttypemodel.h"

class PassportTypeRepository : public QObject
{
    Q_OBJECT
public:
    static PassportTypeRepository* instance()
    {
        static PassportTypeRepository s;
        return &s;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& name);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& name, int ix);

    PassportTypeModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<PassportTypeRepository>
                ("PassportTypeRepository", 1, 0,"PassportTypeRepository",
                 PassportTypeRepository::instance());
    }

private:
    PassportTypeRepository() = default;
    ~PassportTypeRepository() = default;
    PassportTypeRepository(const PassportTypeRepository&) = delete;
    PassportTypeRepository(PassportTypeRepository&&) = delete;
    PassportTypeRepository operator=(const PassportTypeRepository&) = delete;

    PassportTypeModel m_model;
};

#define passportTypeRepository PassportTypeRepository::instance()
