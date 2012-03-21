/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include "dagitem.h"


// An object to collect results on graph traversal.
// The object stores all the information, that shall be associated to graph nodes.
// Because we encapsulate various attributes in this class, we only need to extend
// this class, to add more information to graph nodes.
//
// The contents of this class is associated to the graph using tags:
// attribute_tag,  boost::property<attribute_tag,  NodeAttributes>
class NodeAttributes
{
public:
    NodeAttributes(): m_name(), m_depth() {}
    NodeAttributes(const QString& name): m_name(name), m_depth(), p_dagItem() {}
    NodeAttributes(const QString& name, int depth): m_name(name), m_depth(depth), p_dagItem() {}

    void setName(const QString& name) { m_name  = name;  }
    QString name()const { return m_name; }

    void setDepth(int depth){ m_depth = depth; }
    int depth()const { return m_depth; }

    void setDagItem(DagItem* dagItem) { p_dagItem = dagItem; }
    DagItem* dagItem()const { return p_dagItem; }

    int inc(){ return ++m_depth; }

private:
    QString  m_name;
    int      m_depth;
    DagItem* p_dagItem;
};

namespace dag
{
    namespace edge
    {
        enum {  posParentId  = 0
             ,  posChildId
             ,  posTypeId
             ,  posParentName
             ,  posChildName
             ,  posChildType
             ,  sizeOf_edge
             };
    }

    namespace node
    {
        enum {  posId  = 0
             ,  posName
             ,  sizeOf_node
             };
    }

    inline void copyBoostNode2DagItem(const NodeAttributes& src, tVariVector& target)//JODO cpp
    {
        target[dag::node::posId]   = QVariant(0);
        target[dag::node::posName] = QVariant(src.name());
    }
}//namespace dag

struct Dag
{
    // The kind of attribute_tag is a vertex_property_tag
    struct attribute_tag  { typedef boost::vertex_property_tag kind; };

    // Here we associate a real type for content 'NodeAttributes' to the tag type
    // attribute_tag -> NodeAttributes
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

    //
    typedef boost::property_map<Dag::type, attribute_tag>::type tAttributesMap;

    typedef std::map<vertex_descriptor, vertex_descriptor> tParentMap;//CL
};


