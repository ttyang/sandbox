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
#include "Dag/DbType.h"

inline QString indentation(int depth)
{
    QString indent;
    for(int idx=0; idx < depth; idx++)
        indent += "    ";
    return indent;
}



// An object to collect results on graph traversal.
// The object stores all the information, that shall be associated to graph nodes.
// Because we encapsulate various attributes in this class, we only need to extend
// this class, to add more information to graph nodes.
//
// The contents of this class is associated to the graph using tags:
// attribute_tag,  boost::property<attribute_tag,  VertexAttributes>
class VertexAttributes
{
public:
    VertexAttributes(): m_nodeId(), m_name(), m_depth() {}
    VertexAttributes(const QString& name, int id): m_nodeId(id), m_name(name), m_depth(), p_dagItem() {}

    void setName(const QString& name) { m_name  = name;  }
    QString name()const { return m_name; }

    void setDepth(int depth){ m_depth = depth; }
    int depth()const { return m_depth; }

    void setNodeId(int nodeId) { m_nodeId = nodeId; }
    int nodeId()const { return m_nodeId; }

    void setDagItem(DagItem* dagItem) { p_dagItem = dagItem; }
    DagItem* dagItem()const { return p_dagItem; }

    void setParentItem(DagItem* parentItem) { p_parentItem = parentItem; }
    DagItem* parentItem()const { return p_parentItem; }

    int inc(){ return ++m_depth; }

private:
    int      m_nodeId;
    QString  m_name;
    int      m_depth;
    DagItem* p_dagItem;
    DagItem* p_parentItem;
};

//JODO: m_depth/depth() may be removed. It's currently only needed for debugging.

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
             ,  posParentId
             ,  posParentName
             ,  sizeOf_node
             };
    }

    inline void copyBoostNode2DagItem(const VertexAttributes& src, tVariVector& target)//JODO cpp
    {
        target[dag::node::posId]   = QVariant(src.nodeId());
        target[dag::node::posName] = QVariant(src.name());
    }
}//namespace dag

struct Dag
{
    // The kind of attribute_tag is a vertex_property_tag
    struct attribute_tag  { typedef boost::vertex_property_tag kind; };

    // Here we associate a real type for content 'VertexAttributes' to the tag type
    // attribute_tag -> VertexAttributes
    typedef boost::property<attribute_tag,  VertexAttributes> tAttributeTag;

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


