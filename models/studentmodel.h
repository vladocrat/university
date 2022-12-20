#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "student.h"

class StudentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum StudentRoles {
        NameRole,
        GroupRole
    };
    Q_ENUM(StudentRoles);

    void add(const Student&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QList<Student> list() const {return m_list;}
    void clear();

    static void registerType()
    {
        qmlRegisterUncreatableType<StudentModel>("StudentModel", 1, 0, "StudentModel",
                                               "Cant create instance of StudentModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Student> m_list;

};

