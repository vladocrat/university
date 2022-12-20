#pragma once

#include <QObject>
#include <QQmlEngine>

#include "groupmodel.h"

class GroupRepository : public QObject
{
   Q_OBJECT
public:
    static GroupRepository* instance()
    {
        static GroupRepository gr;
        return &gr;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& name);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& name, int ix);

    GroupModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<GroupRepository>
                ("GroupRepository", 1, 0,"GroupRepository",
                 GroupRepository::instance());
    }
private:
    GroupRepository() = default;
    ~GroupRepository() = default;
    GroupRepository(const GroupRepository&) = delete;
    GroupRepository(GroupRepository&&) = delete;
    GroupRepository operator=(const GroupRepository&) = delete;

    GroupModel m_model;
};

#define groupRepository GroupRepository::instance()
