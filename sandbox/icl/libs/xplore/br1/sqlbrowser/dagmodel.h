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


inline QString indentation(int depth)
{
    QString indent;
    for(int idx=0; idx < depth; idx++)
        indent += "    ";
    return indent;
}


typedef std::map<int, int> daggy; //CL?

class QSqlQuery;
class DagItem;

// An object to collect results on graph traversal
class NodeAttributes
{
public:
    NodeAttributes(): m_name(), m_depth() {}
    NodeAttributes(const QString& name): m_name(name), m_depth() {}
    NodeAttributes(const QString& name, int depth): m_name(name), m_depth(depth) {}

    void setName(const QString& name) { m_name  = name;  }
    QString name()const { return m_name; }

    void setDepth(int depth){ m_depth = depth; }
    int depth()const { return m_depth; }

    int inc(){ return ++m_depth; }

private:
    QString m_name;
    int     m_depth;
};

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
    void setupDag(DagItem *parent);

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
    struct attribute_tag {
        typedef boost::vertex_property_tag kind;
    };

    typedef boost::property<attribute_tag, NodeAttributes> tAttributeTag;

    typedef boost::adjacency_list
    < boost::vecS
    , boost::vecS
    , boost::directedS
    , tAttributeTag
    > tDag;

    tDag m_dag;

    typedef boost::property_map<tDag, attribute_tag>::type
        tAttributesMap;

    tAttributesMap m_nodeAttributes;

    //--------------------------------------------------------------------------
    // Visitors
    struct node_arrival : public boost::base_visitor<node_arrival>
    {
        node_arrival(QString* result, tAttributesMap& names)
            : p_result(result), r_attrs(names){}

        typedef boost::on_discover_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& dag)
        {
            if(boost::out_degree(node, dag) > 0)
            {
                *p_result += indentation(r_attrs[node].depth()) + "(";
                *p_result += r_attrs[node].name();
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

        QString*        p_result;
        tAttributesMap& r_attrs;
    };

    struct edge_visit : public boost::base_visitor<edge_visit>
    {
        edge_visit(QString* result, tAttributesMap& names)
            : p_result(result), r_attrs(names){}

        typedef boost::on_examine_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& dag)
        {
            int source_depth = r_attrs[source(edge, dag)].depth();
            int target_depth = source_depth + 1;
            r_attrs[target(edge, dag)].setDepth(target_depth);

            if(boost::out_degree(target(edge, dag), dag)==0)
            {
                *p_result += indentation(target_depth) + r_attrs[target(edge, dag)].name();
                *p_result += "\n";
            }
        }

        QString*        p_result;
        tAttributesMap& r_attrs;
    };

    struct node_final : public boost::base_visitor<node_final>
    {
        node_final(QString* result, tAttributesMap& names)
            : p_result(result), r_attrs(names){}

        typedef boost::on_finish_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& dag)
        {
            if(boost::out_degree(node, dag) > 0)
            {
                *p_result += indentation(r_attrs[node].depth()) + ")";
                *p_result += "\n";
            }
        }

        QString*        p_result;
        tAttributesMap& r_attrs;
    };

};

#endif
