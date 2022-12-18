#pragma once

#include "databasecontroller.h"
#include "accessrightsmodel.h"

#include <QObject>
#include <QQmlEngine>

class AccessRightsRepository final : public QObject
{
    Q_OBJECT
public:
    static AccessRightsRepository* instance()
    {
        static AccessRightsRepository ar;
        return &ar;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& name);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& name, int ix);

    AccessRightsModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<AccessRightsRepository>
                ("AccessRightsRepository", 1, 0,"AccessRightsRepository",
                 AccessRightsRepository::instance());
    }
private:
    AccessRightsRepository() = default;
    ~AccessRightsRepository() = default;
    AccessRightsRepository(const AccessRightsRepository&) = delete;
    AccessRightsRepository(AccessRightsRepository&&) = delete;
    AccessRightsRepository operator=(const AccessRightsRepository&) = delete;

    AccessRightsModel m_model;
};

#define accessRightsRepository AccessRightsRepository::instance()
