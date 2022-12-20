#pragma once

#include <QObject>
#include <QQmlEngine>

#include "dormitorymodel.h"

class DormitoryRepository : public QObject
{
    Q_OBJECT
public:
    static DormitoryRepository* instance()
    {
        static DormitoryRepository r;
        return &r;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& address, const QString& roomNumber, const QString& status, int studentIx);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& name, int ix);

    DormitoryModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<DormitoryRepository>
                ("DormitoryRepository", 1, 0,"DormitoryRepository",
                 DormitoryRepository::instance());
    }

private:
    DormitoryRepository() = default;
    ~DormitoryRepository() = default;
    DormitoryRepository(const DormitoryRepository&) = delete;
    DormitoryRepository(DormitoryRepository&&) = delete;
    DormitoryRepository operator=(const DormitoryRepository&) = delete;

    DormitoryModel m_model;
};

#define dormitoryRepository DormitoryRepository::instance()

