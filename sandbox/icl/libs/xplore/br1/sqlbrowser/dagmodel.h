/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGMODEL_H
#define DAGMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <map>

typedef std::map<int, int> daggy;

class QSqlQuery;
class DagItem;

class DagModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    DagModel(const QStringList &headers, const QString &data,
              QObject *parent = 0);
    ~DagModel();

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());


    //JOFA Populating a DAG from an Sql-query
    void fromSql(const QSqlQuery& query);

    void fromSql(const QSqlQuery& query, DagItem* node, int depth);

    //JOFA Iteration example: The container as String
    QString toString()const;

    QString nodeToString(DagItem* node, int depth)const;


private:
    void setupModelData(const QStringList &lines, DagItem *parent);
    DagItem *getItem(const QModelIndex &index) const;

    DagItem *rootItem;
};

#endif
