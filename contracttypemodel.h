#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>
#include <QList>

#include "contracttype.h"

class ContractTypeModel : public QAbstractListModel
{
  Q_OBJECT
public:
    enum ContractTypeRoles {
        NameRole
    };
    Q_ENUM(ContractTypeRoles);

    void addType(const ContractType&);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QList<ContractType> list() const {return m_types;}
    void clear();

    static void registerType()
    {
        qmlRegisterUncreatableType<ContractTypeModel>("ContractTypeModel", 1, 0, "ContractTypeModel",
                                               "Cant create instance of ContractTypeModel");
    }

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ContractType> m_types;
};


