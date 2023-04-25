#include "meinmodel.h"
#include <QSqlRecord>

MeinModel::MeinModel(QObject *parent)
    : QSqlRelationalTableModel{parent}
{

}
MeinModel::~MeinModel(){

}


QVariant MeinModel::data ( const QModelIndex & index, int role ) const {

    switch( role )
    {
    case Qt::DisplayRole:
    {
      qDebug() << role;
    }
    case   Qt::EditRole:
    {
        qDebug() << role;
    }
    }

   if(index.row() >= rowCount())
   {
       return QString("");
   }
   if(role < Qt::UserRole)
   {
       return QSqlQueryModel::data(index, role);
   }
   else
   {
       // search for relationships
       for (int i = 0; i < columnCount(); ++i)
       {
           if (this->relation(i).isValid())
           {
           return record(index.row()).value(QString(roles.value(role)));
           }
       }
   // if no valid relationship was found
   return QSqlQueryModel::data(this->index(index.row(), role - Qt::UserRole - 1), Qt::DisplayRole);
   }
}

void MeinModel::generateRoleNames() {

   roles.clear();
   int nbCols = this->columnCount();

   for (int i = 0; i < nbCols; ++i)
   {
       roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray();
   }

}

bool MeinModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
// && role == Qt::EditRole



        if (index.isValid()) {
                //bool ret = QSqlTableModel::setData(index, value, Qt::EditRole);
                bool ret = QSqlRelationalTableModel::setData( index, value, Qt::EditRole );

               // if(ret) dataChanged(index, index);
               if(ret) emit dataChanged(index, index, { Qt::EditRole, Qt::DisplayRole });
                return ret;
            }

        // Set data in model here. It can also be a good idea to check whether
        // the new value actually differs from the current value
       // QVariant v =record(index.row()).value(QString(roles.value(role)));

        //if (mData[index.row()] != value.toString()) {
        //            mData[index.row()] = value.toString();
        //            emit dataChanged(index, index, { Qt::EditRole, Qt::DisplayRole });
        //          return true;
        //        }
        //if ( v != value) {
        //   v = value;
        //    emit dataChanged(index, index, { Qt::EditRole, Qt::DisplayRole });
        //    return true;
       // }
    //}

}

void MeinModel::updateModel()
{
  this->select();
}

void MeinModel::deleteRows(QList<int> zeilen)
{

    bool success;


       for (auto it = zeilen.crbegin(); it != zeilen.crend(); ++it) {
           int row = *it;
           beginRemoveRows(QModelIndex(), row, row);
           //success = removeRow(row);
           success = this->QSqlTableModel::deleteRowFromTable(row);
           if (success == true) {
               endRemoveRows();

           }
       }

}



QVariant MeinModel::getRelation(const QModelIndex &item, int role)
{
       if (item.row() >= rowCount())
           return QString();
       QSqlRelation rela = relation(role);
       // is any realtion on this role?
       if(!rela.isValid())
           return QString();
       // get the table of the realtion
       QSqlTableModel *rModel = relationModel(role);
       QVariantList list;
       for(int i = 0; i < rModel->columnCount(); i++)
       {
           // look for the write headerName we need
           if(rModel->headerData(i, Qt::Orientation::Horizontal) == rela.displayColumn())
           {
               for(int j = 0; j < rModel->rowCount(); j++)
               {
           // use the data-method for QSqlTableModel to get all values from the RealtionCoumn and save it in a List
           QModelIndex modelIndex = rModel->index(j, i);
           QVariant value = rModel->data(modelIndex);
           list.append(value);
               }
               break;
           }
       }
       return list;
}

QVariant MeinModel::hasRelation(const QModelIndex &item, QVariant value){
       return 0;
}
