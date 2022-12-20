#pragma once

#include <QObject>

#include "studentmodel.h"

class StudentRepository : public QObject
{
    Q_OBJECT
public:
    static StudentRepository* instance()
    {
        static StudentRepository s;
        return &s;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& name, QString groupName);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& name, int ix);

    StudentModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<StudentRepository>
                ("StudentRepository", 1, 0,"StudentRepository",
                 StudentRepository::instance());
    }

private:
    StudentRepository() = default;
    ~StudentRepository() = default;
    StudentRepository(const StudentRepository&) = delete;
    StudentRepository(StudentRepository&&) = delete;
    StudentRepository operator=(const StudentRepository&) = delete;

    StudentModel m_model;
};

#define studentRepository StudentRepository::instance()

