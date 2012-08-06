/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGMODEL_H
#define DAGMODEL_H

#include <map>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "Dag.h"
#include "Dag/ObjectGraph.h"


class QSqlQuery;
class DagItem;

class DagModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    //DagModel(const QStringList &headers, const QString &data,
    //          QObject *parent = 0);
    DagModel(QObject *parent = 0);
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

    //CL void makeDag();

    QString dagToString();
    QString setupDag();

    DagItem* fromSql(QSqlQuery& query, DagItem* node, int depth);

    //JOFA Iteration example: The container as String
    QString toString()const;

    QString nodeToString(DagItem* node, int depth)const;

    DagItem* rootItem()const { return m_rootItem; } //CL DBG

    int num_edges()const { return m_dag.num_edges(); }
    //--------------------------------------------------------------------------

private:
    DagItem* item(const QModelIndex& index)const
    {
        if (!index.isValid())
           return 0;
        return static_cast<DagItem*>(index.internalPointer());
    }

    DagItem* createDagItem();

    void setupModelData(const QStringList &lines, DagItem *parent);

    DagItem *getItem(const QModelIndex &index) const;

    void fillData(QVector<QVariant>& data, QSqlQuery& query);

public:
    // Fill edge with dummy data. JODO CL later
    void fillDummyData(QVector<QVariant>& data, int nodeId);

    void appendEdge(QVector<QVariant>& data){ m_edges.append(data);}//CL

    void insertVertex(QVector<QVariant>& edgeData, const QModelIndex& index);

private:
    void dagInsertVertex(QVector<QVariant>& edgeData, const QModelIndex& index);
    void modelInsertVertex(QVector<QVariant>& edgeData, const QModelIndex& index);

private:
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
    //CL Dag::type            m_dag;
    dag::db::ObjectGraph m_dag;
    Dag::tAttributesMap  m_aVertexAttributes;
    Dag::tParentMap      m_parentMap;
};

#endif
