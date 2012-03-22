/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include "Dag.h"



struct CreatorVisitor
{
    //--------------------------------------------------------------------------
    // Visitors
    struct OnDiscoverVertex : public boost::base_visitor<OnDiscoverVertex>
    {
        OnDiscoverVertex(DagItem* curItem, QString* result, Dag::tAttributesMap& attrs)
            : p_curItem(curItem), p_result(result), r_attrs(attrs)
        {
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
            dag::copyBoostNode2DagItem(r_attrs[node], itemData);

            // Discoverage is always on the way down. So we should maintain the invariant
            // p_curItem should be initialized to the DagModel's DatItem* rootItem

            if(boost::out_degree(node, dag) > 0)
            {
                *p_result += indentation(r_attrs[node].depth()) + "(";
                *p_result += r_attrs[node].name();
                *p_result += QString(" d:%1").arg(r_attrs[node].depth());
                *p_result += " -> " + (p_curItem==0 ? QString("{}") : p_curItem->data()[dag::node::posName].toString());
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

        DagItem*             p_curItem;
        QString*             p_result;
        Dag::tAttributesMap& r_attrs;
    };

    struct OnExamineEdge : public boost::base_visitor<OnExamineEdge>
    {
        OnExamineEdge(DagItem* curItem, QString* result, Dag::tAttributesMap& names)
            : p_curItem(curItem), p_result(result), r_attrs(names)
        {
            //CL r_attrs[0].setDagItem(p_curItem); //Root node
        }

        typedef boost::on_examine_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& dag)
        {
            Dag::vertex_descriptor source_node = source(edge, dag);
            Dag::vertex_descriptor target_node = target(edge, dag);
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
                dag::copyBoostNode2DagItem(r_attrs[target_node], itemData);
                DagItem* newDagItem = new DagItem(itemData, p_curItem);
                sourceDagItem->addChild(newDagItem);
                r_attrs[target_node].setDagItem(newDagItem);
                newDagItem->setData(dag::node::posParentId, newDagItem->parent()->data(dag::node::posId));
                newDagItem->setData(dag::node::posParentName, newDagItem->parent()->data(dag::node::posName));
            }

            if(boost::out_degree(target(edge, dag), dag)==0)
            {
                *p_result += indentation(target_depth) + r_attrs[target(edge, dag)].name() + " ?";
                *p_result += "\n";
            }
        }

        DagItem*             p_curItem;
        QString*             p_result;
        Dag::tAttributesMap& r_attrs;
    };

    struct OnFinishVertex : public boost::base_visitor<OnFinishVertex>
    {
        OnFinishVertex(DagItem* curItem, QString* result, Dag::tAttributesMap& names)
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
        Dag::tAttributesMap& r_attrs;
    };

}; // CreatorVisitor

