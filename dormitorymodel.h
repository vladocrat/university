#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "Dormitory.h"

class DormitoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DormitoryRoles {
        AddressRole,
        RoomNumberRole,
        StatusRole,
        StudentFullNameRole,
        StudentGroupRole
    };
    Q_ENUM(DormitoryRoles);

    void add(const Dormitory&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void clear();
    auto list() {return m_list;}

    static void registerType()
    {
        qmlRegisterUncreatableType<DormitoryModel>("DormitoryModel", 1, 0, "DormitoryModel",
                                               "Cant create instance of DormitoryModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;


private:
    QList<Dormitory> m_list;
};

