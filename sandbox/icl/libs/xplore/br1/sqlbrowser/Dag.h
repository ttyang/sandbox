/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>


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


struct Dag
{
    // The kind of attribute_tag is a vertex_property_tag
    struct attribute_tag  { typedef boost::vertex_property_tag kind; };

    typedef boost::property<attribute_tag,  NodeAttributes> tAttributeTag;

    typedef boost::adjacency_list
    < boost::vecS
    , boost::vecS
    , boost::directedS
    , tAttributeTag
    > DagType;

    typedef DagType type;
    typedef DagType::vertex_descriptor vertex_descriptor;
    typedef DagType::edge_descriptor   edge_descriptor;

    typedef boost::property_map<Dag::type, attribute_tag>::type
        tAttributesMap;

    typedef std::map<vertex_descriptor, vertex_descriptor> tParentMap;
};


