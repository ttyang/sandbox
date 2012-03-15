/****************************************************************************
**
**
****************************************************************************/

#ifndef DAGMODEL_H
#define DAGMODEL_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

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

    DagItem* fromSql(QSqlQuery& query, DagItem* node, int depth);

    //JOFA Iteration example: The container as String
    QString toString()const;

    QString nodeToString(DagItem* node, int depth)const;


private:
    void setupModelData(const QStringList &lines, DagItem *parent);
    DagItem *getItem(const QModelIndex &index) const;

    void fillData(QVector<QVariant>& data, QSqlQuery& query);
    QString indentation(int depth)const;


    DagItem *rootItem;

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
    struct name_tag {
        typedef boost::vertex_property_tag kind;
    };

    typedef boost::property<name_tag, QString> tNameTag;

    typedef boost::adjacency_list
    < boost::vecS
    , boost::vecS
    , boost::directedS
    , tNameTag
    > tDag;

    tDag m_dag;

    typedef boost::property_map<tDag, name_tag>::type
        tNameTagMap;

    tNameTagMap m_nameTags;

    //--------------------------------------------------------------------------
    // Visitors
    struct node_arrival : public boost::base_visitor<node_arrival>
    {
        node_arrival(QString* result, const tNameTagMap& names)
            : p_result(result), r_names(names){}

        typedef boost::on_discover_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& dag)
        {
            if(boost::out_degree(node, dag) > 0)
            {
                *p_result += "(";
                *p_result += r_names[node];
                *p_result += "\n";
            }
        }

        //CL Example for iterating over edges.
        template<class Vertex, class Graph>
        int edge_count(Vertex node, Graph& dag)
        {
            typedef graph_traits<Graph> GraphTraits;
            typename GraphTraits::out_edge_iterator out_i, out_end;
            typename GraphTraits::edge_descriptor ed;

            int edge_cnt = 0;
            for(boost::tie(out_i, out_end) = boost::out_edges(node, dag); out_i != out_end; ++out_i)
                ++edge_cnt;

            return edge_cnt;
        }

        QString*           p_result;
        const tNameTagMap& r_names;
    };

    struct edge_visit : public boost::base_visitor<edge_visit>
    {
        edge_visit(QString* result, const tNameTagMap& names)
            : p_result(result), r_names(names){}

        typedef boost::on_examine_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& dag)
        {
            *p_result += " ->" + r_names[target(edge, dag)];
            *p_result += "\n";
        }

        QString*           p_result;
        const tNameTagMap& r_names;
    };

    struct node_final : public boost::base_visitor<node_final>
    {
        node_final(QString* result, const tNameTagMap& names)
            : p_result(result), r_names(names){}

        typedef boost::on_finish_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& dag)
        {
            if(boost::out_degree(node, dag) > 0)
            {
                *p_result += ")";
                *p_result += "\n";
            }
        }

        QString*           p_result;
        const tNameTagMap& r_names;
    };

};

#endif
