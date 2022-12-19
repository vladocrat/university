#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "passport.h"

class PassportTypeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PassportTypeRoles {
        NameRole
    };
    Q_ENUM(PassportTypeRoles);

    void addType(const PassportTypeString&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QList<PassportTypeString> list() const {return m_types;}
    void clear();

    static void registerType()
    {
        qmlRegisterUncreatableType<PassportTypeModel>("PassportTypeModel", 1, 0, "PassportTypeModel",
                                               "Cant create instance of PassportTypeModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PassportTypeString> m_types;

};

