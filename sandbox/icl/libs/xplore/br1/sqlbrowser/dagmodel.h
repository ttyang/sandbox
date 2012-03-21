/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGMODEL_H
#define DAGMODEL_H

#include <map>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "Dag.h"



typedef std::map<int, int> daggy; //CL?

class QSqlQuery;
class DagItem;

class DagModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    //DagModel(const QStringList &headers, const QString &data,
    //          QObject *parent = 0);
    DagModel(const QStringList &headers, //const QString &data,
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

    //--------------------------------------------------------------------------
    //JOFA Populating a DAG from an Sql-query
    void getEdges(QSqlQuery& query);
    void fromSql(QSqlQuery& query);

    void makeDag();

    QString dagToString();
    QString setupDag();

    DagItem* fromSql(QSqlQuery& query, DagItem* node, int depth);

    //JOFA Iteration example: The container as String
    QString toString()const;

    QString nodeToString(DagItem* node, int depth)const;

    DagItem* rootItem()const { return m_rootItem; } //CL DBG

private:
    void setupModelData(const QStringList &lines, DagItem *parent);

    DagItem *getItem(const QModelIndex &index) const;

    void fillData(QVector<QVariant>& data, QSqlQuery& query);

    DagItem *m_rootItem;

    int m_parentId  ;
    int m_childId   ;
    int m_typeId    ;
    int m_parentName;
    int m_childName ;
    int m_childType ;

    typedef QVector<QVariant> tEdgeData;
    typedef QList<tEdgeData>  tEdgeList;
    tEdgeList m_edges;

    //==========================================================================
    // Graph
    Dag::type           m_dag;
    Dag::tAttributesMap m_nodeAttributes;
    Dag::tParentMap     m_parentMap;
};

#endif
