/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include "Dag/DbBasedGraph.h"
//CL #include "Dag.h" //JODO remove

#include <QDebug>

class DagItem;

//------------------------------------------------------------------------------
template<class DbGraph>
struct CreatorVisitor2
{
    typedef typename DbGraph::vertex_descriptor vertex_descriptor;
    typedef typename DbGraph::tVertex2Depth     tVertex2Depth;

    //JODO Auxiliary Map. Could be optimized away.
    typedef typename DbGraph::Vertex2AttributesMap Vertex2AttributesMap;

    //--------------------------------------------------------------------------
    // Visitors
    struct OnDiscoverVertex : public boost::base_visitor<OnDiscoverVertex>
    {
        OnDiscoverVertex(DagItem* curItem, QString* result, Vertex2AttributesMap& attrs)
            : p_curItem(curItem), p_result(result), r_attrs(attrs)
        {
            //JODO redundant?
            r_attrs[0].setDagItem(p_curItem); //Root node
            r_attrs[0].setParentItem(0);      //Root node
        }

        typedef boost::on_discover_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& dag)
        {
            // "Visitation by descent". All nodes are reached through this function on
            // descend, which is always done first for "depth first search. Therefore
            // we can create all nodes for the Qt DagModel in this functor:
            //
            // Create a DagItem. The node that has been visited last should be the parent.
            // While we are descending, we build a chain going "down".

            tVariVector itemData(dag::node::sizeOf_node); // ItemData node(id, name, ..)
                             // will only by a part of the data from sql that represented
                             // edges. Via r_attrs we only obtain associated node data
                             // from the boost::graph
            //JODO dag::copyBoostNode2DagItem(r_attrs[node], itemData);
            //CL itemData[dag::node::posId]   = QVariant(dag[node].key());
            //CL itemData[dag::node::posName] = QVariant(dag[node].name());

            dbg_str = QString("(%1)[%2] %3").arg(node).arg(dag[node].key()).arg(dag[node].name());

            // Discoverage is always on the way down. So we should maintain the invariant
            // p_curItem should be initialized to the DagModel's DatItem* rootItem
            Q_ASSERT(r_attrs[node].dagItem() != 0);

            if(boost::out_degree(node, dag) > 0)
            {
                *p_result += indentation(r_attrs[node].depth()) + "(";
                *p_result += dag[node].name();
                *p_result += QString(" d:%1").arg(r_attrs[node].depth());
                *p_result += " -> " + (p_curItem==0 ? QString("{}") : p_curItem->data()[dag::node::posName].toString());
                *p_result += "\n";
            }
        }

        DagItem*             p_curItem;
        QString*             p_result;
        Vertex2AttributesMap& r_attrs;
        QString              dbg_str;
    };

    struct OnExamineEdge : public boost::base_visitor<OnExamineEdge>
    {
        OnExamineEdge(DagItem* curItem, QString* result, Vertex2AttributesMap& attrs)
            : p_curItem(curItem), p_result(result), r_attrs(attrs)
        {
            //CL r_attrs[0].setDagItem(p_curItem); //Root node
        }

        typedef boost::on_examine_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& dag)
        {
            vertex_descriptor source_node = source(edge, dag);
            dbg_str = QString("(%1)[%2] %3").arg(source_node).arg(dag[source_node].key()).arg(dag[source_node].name());
            vertex_descriptor target_node = target(edge, dag);
            dbg_str = QString("(%1)[%2] %3").arg(target_node).arg(dag[target_node].key()).arg(dag[target_node].name());

            int source_depth = r_attrs[source_node].depth();
            int target_depth = source_depth + 1;

            r_attrs[target_node].setDepth(target_depth);
            DagItem* sourceDagItem = r_attrs[source_node].dagItem();
            DagItem* targetDagItem = r_attrs[target_node].dagItem();

            Q_ASSERT(sourceDagItem);

            if(p_curItem != sourceDagItem)
                p_curItem = sourceDagItem;

            if(targetDagItem)
                sourceDagItem->addChild(targetDagItem);
            else
            {
                tVariVector itemData(dag::node::sizeOf_node);
                //JODO dag::copyBoostNode2DagItem(r_attrs[target_node], itemData);
                itemData[dag::node::posId]   = QVariant(dag[target_node].key());
                itemData[dag::node::posName] = QVariant(dag[target_node].name());

                DagItem* newDagItem = new DagItem(itemData, p_curItem);
                sourceDagItem->addChild(newDagItem);
                r_attrs[target_node].setDagItem(newDagItem);
                newDagItem->setData(dag::node::posParentId, newDagItem->parent()->data(dag::node::posId));
                newDagItem->setData(dag::node::posParentName, newDagItem->parent()->data(dag::node::posName));
            }

            if(boost::out_degree(target(edge, dag), dag)==0)
            {
                *p_result += indentation(target_depth) + dag[target(edge, dag)].name() + " ?";
                *p_result += "\n";
            }
        }

        DagItem*             p_curItem;
        QString*             p_result;
        Vertex2AttributesMap& r_attrs;
        QString              dbg_str;
    };

    struct OnFinishVertex : public boost::base_visitor<OnFinishVertex>
    {
        OnFinishVertex(DagItem* curItem, QString* result, Vertex2AttributesMap& names)
            : p_curItem(curItem), p_result(result), r_attrs(names)
        {
        }

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

        DagItem*             p_curItem;
        QString*             p_result;
        Vertex2AttributesMap& r_attrs;
    };

}; // CreatorVisitor2

