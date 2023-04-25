#ifndef MEINMODEL_H
#define MEINMODEL_H

#include <QSqlRelationalTableModel>


class MeinModel : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    explicit MeinModel(QObject *parent = nullptr);
    ~MeinModel();
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    Q_INVOKABLE QVariant getRelation(const QModelIndex &item, int role = Qt::EditRole);
    Q_INVOKABLE QVariant hasRelation(const QModelIndex &item, QVariant value);

       void generateRoleNames();
       Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)  ;
       Q_INVOKABLE void updateModel();
       Q_INVOKABLE void deleteRows(const QList<int> rows);

private:
     QHash<int, QByteArray> roles;
     QList<MeinModel> *mData;
};

#endif // MEINMODEL_H
