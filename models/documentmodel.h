#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "document.h"

class DocumentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DocumentRoles {
        PathRole
    };
    Q_ENUM(DocumentRoles);

    void addDocument(const Document&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void clear();
    auto list() {return m_docs;}

    static void registerType()
    {
        qmlRegisterUncreatableType<DocumentModel>("DocumentModel", 1, 0, "DocumentModel",
                                               "Cant create instance of DocumentModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;


private:
    QList<Document> m_docs;
};
