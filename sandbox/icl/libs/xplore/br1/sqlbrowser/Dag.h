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
#include "Dag.h"

//JODO CL ..
#include "Dag/Decoration.h" //CL
#include "Dag/DecoratedGraph.h" //CL
#include "Dag/TypeGraph.h" //CL
#include "data/concept/CreatorTraits.h" //CL
#include "data/concept/SelectorTraits.h" //CL
#include "data/concept/IsQuerySelector.h" //CL
#include "data/qsql/QSqlSelector.h" //CL
#include "data/qsql/QSqlCreator.h" //CL


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
// vertex_attr_tag,  boost::property<vertex_attr_tag,  VertexAttributes>
class VertexAttributes
{
public:
    typedef dag::db::tKey              tKey;
    typedef dag::db::tObject           tObject;
    typedef dag::db::tObjectSharedPtr  tObjectSharedPtr;

public:
    VertexAttributes(): m_aKey(), m_depth() {}

    VertexAttributes(tKey key, const tObjectSharedPtr& pObject) //JODO REMOVE
        : m_aKey(key), m_pObject(pObject), m_depth(), p_dagItem() {}

    VertexAttributes(tKey key, const QString& aName)
        : m_aKey(key), m_pObject(boost::make_shared<tObject>())
        , m_depth(), p_dagItem()
    {
        m_pObject->setName(aName);
    }

    void setName(const QString& name) { m_pObject->setName(name); }
    QString name()const { return m_pObject->name(); }

    void setDepth(int depth){ m_depth = depth; }
    int depth()const { return m_depth; }

    void setKey(tKey aKey) { m_aKey = aKey; }
    tKey key()const { return m_aKey; }

    void setDagItem(DagItem* dagItem) { p_dagItem = dagItem; }
    DagItem* dagItem()const { return p_dagItem; }

    void setParentItem(DagItem* parentItem) { p_parentItem = parentItem; }
    DagItem* parentItem()const { return p_parentItem; }

    int inc(){ return ++m_depth; }

private:
    tKey  m_aKey;
    int   m_depth;

    //---- Db::Object associated to the Vertex ---------------------------------
    dag::db::tObjectSharedPtr m_pObject;

    //---- DagModel ------------------------------------------------------------
    DagItem* p_dagItem;
    DagItem* p_parentItem;
};

class EdgeAttributes
{
public:
    typedef dag::db::tKey  tKey;
public:
    EdgeAttributes(): m_aKey() {}
    EdgeAttributes(tKey aKey): m_aKey(aKey) {}

private:
    tKey      m_aKey;

    //---- Db::Object associated to the Edge -----------------------------------
    dag::db::tObjectSharedPtr m_pObject;
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
        target[dag::node::posId]   = QVariant(src.key());
        target[dag::node::posName] = QVariant(src.name());
    }
}//namespace dag

struct Dag
{
    // The kind of vertex_attr_tag is a vertex_property_tag
    struct vertex_attr_tag  { typedef boost::vertex_property_tag kind; };

    // The kind of edge_attr_tag is a edge_property_tag
    struct edge_attr_tag  { typedef boost::edge_property_tag kind; };

    // Here we associate a real type for content 'VertexAttributes' to the tag type
    // vertex_attr_tag -> VertexAttributes
    typedef boost::property<vertex_attr_tag,  VertexAttributes> tVertexAttrTag;
    typedef boost::property<edge_attr_tag,    EdgeAttributes>   tEdgeAttrTag;

    typedef boost::adjacency_list
    < boost::vecS
    , boost::vecS
    , boost::directedS
    , tVertexAttrTag
    , tEdgeAttrTag
    > DagType;

    typedef DagType type;
    typedef DagType::vertex_descriptor vertex_descriptor;
    typedef DagType::edge_descriptor   edge_descriptor;

    //
    typedef boost::property_map<Dag::type, vertex_attr_tag>::type tAttributesMap;

    typedef std::map<vertex_descriptor, vertex_descriptor> tParentMap;//CL
};


