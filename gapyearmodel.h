#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "GapYear.h"

class GapYearModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum GapYearRoles {
        DocumentRole,
        CreatorLoginRole,
        CreatorEmailRole,
        CreatorRoleRole,
        StartDateRole,
        EndDateRole
    };
    Q_ENUM(GapYearRoles);

    void add(const GapYear&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void clear();
    auto list() {return m_years;}

    static void registerType()
    {
        qmlRegisterUncreatableType<GapYearModel>("GapYearModel", 1, 0, "GapYearModel",
                                               "Cant create instance of GapYearModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;


private:
    QList<GapYear> m_years;
};


