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


inline QString indentation(int depth)
{
    QString indent;
    for(int idx=0; idx < depth; idx++)
        indent += "    ";
    return indent;
}


struct StringVisitor
{
    //--------------------------------------------------------------------------
    // Visitors
    struct OnDiscoverVertex : public boost::base_visitor<OnDiscoverVertex>
    {
        OnDiscoverVertex(QString* result, Dag::tAttributesMap& names)
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

        QString*             p_result;
        Dag::tAttributesMap& r_attrs;
    };

    struct OnExamineEdge : public boost::base_visitor<OnExamineEdge>
    {
        OnExamineEdge(QString* result, Dag::tAttributesMap& names, Dag::tParentMap& parents)
            : p_result(result), r_attrs(names), r_parents(parents){}

        typedef boost::on_examine_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& dag)
        {
            int source_depth = r_attrs[source(edge, dag)].depth();
            int target_depth = source_depth + 1;
            r_attrs[target(edge, dag)].setDepth(target_depth);
            //CL r_parents stuff
            Dag::vertex_descriptor child  = target(edge, dag);
            Dag::vertex_descriptor parent = source(edge, dag);
            r_parents[child]  = parent;

            if(boost::out_degree(target(edge, dag), dag)==0)
            {
                *p_result += indentation(target_depth) + r_attrs[target(edge, dag)].name();
                *p_result += "\n";
            }
        }

        QString*             p_result;
        Dag::tAttributesMap& r_attrs;
        Dag::tParentMap&     r_parents;
    };

    struct OnFinishVertex : public boost::base_visitor<OnFinishVertex>
    {
        OnFinishVertex(QString* result, Dag::tAttributesMap& names)
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

        QString*             p_result;
        Dag::tAttributesMap& r_attrs;
    };

    /*CL
    struct OnTreeEdge : public boost::base_visitor<OnTreeEdge>
    {
        OnTreeEdge(QString* result, Dag::tAttributesMap& names)
            : p_result(result), r_attrs(names){}

        typedef boost::on_tree_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& dag)
        {
            int source_depth = r_attrs[source(edge, dag)].depth();
            int target_depth = source_depth + 1;
            r_attrs[target(edge, dag)].setDepth(target_depth);

            *p_result += ".";
        }

        QString*             p_result;
        Dag::tAttributesMap& r_attrs;
    };
    */

}; // StringVisitor

