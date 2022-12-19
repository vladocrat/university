#pragma once

#include <QQmlEngine>
#include <QObject>

#include "gapyearmodel.h"

class GapYearRepository : public QObject
{
    Q_OBJECT
public:
    static GapYearRepository* instance()
    {
        static GapYearRepository gyr;
        return &gyr;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert();
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& path, int ix);

    GapYearModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<GapYearRepository>
                ("GapYearRepository", 1, 0,"GapYearRepository",
                 GapYearRepository::instance());
    }

private:
    GapYearRepository() = default;
    ~GapYearRepository() = default;
    GapYearRepository(const GapYearRepository&) = delete;
    GapYearRepository(GapYearRepository&&) = delete;
    GapYearRepository operator=(const GapYearRepository&) = delete;

    GapYearModel m_model;
};

#define gapYearRepository GapYearRepository::instance()
