#include "documentrepository.h"

#include "databasecontroller.h"
#include "document.h"
#include "filecontroller.h"

void DocumentRepository::getAll()
{
    auto all = dbController->getAllDocuments();
    m_model.clear();

    for (const auto& x: all)
    {
        m_model.addDocument(x);
    }
}

bool DocumentRepository::insert(const QString &path)
{
    Document d;
    d.path = path;
    return dbController->insert(d);
}

bool DocumentRepository::deleteOne(int ix)
{
    return dbController->deleteOne(m_model.list().at(ix));
}

bool DocumentRepository::update(const QString &path, int ix)
{
    auto docToUpdate = m_model.list().at(ix);
    Document d;
    d.path = path;
    return dbController->update(docToUpdate, d);
}
