#pragma once

#include <QObject>
#include <QQmlEngine>

#include "documentmodel.h"

class DocumentRepository : public QObject
{
    Q_OBJECT
public:
    static DocumentRepository* instance()
    {
        static DocumentRepository dr;
        return &dr;
    }

    Q_INVOKABLE void getAll();
    Q_INVOKABLE bool insert(const QString& path);
    Q_INVOKABLE bool deleteOne(int);
    Q_INVOKABLE bool update(const QString& path, int ix);


    DocumentModel* model() {return &m_model;}

    static void registerType()
    {
        qmlRegisterSingletonInstance<DocumentRepository>
                ("DocumentRepository", 1, 0,"DocumentRepository",
                 DocumentRepository::instance());
    }

private:
    DocumentRepository() = default;
    ~DocumentRepository() = default;
    DocumentRepository(const DocumentRepository&) = delete;
    DocumentRepository(DocumentRepository&&) = delete;
    DocumentRepository operator=(const DocumentRepository&) = delete;

    DocumentModel m_model;
};

#define documentRepository DocumentRepository::instance()
