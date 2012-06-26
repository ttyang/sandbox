/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include "Dag/TypeGraph.h"
#include "Dag.h" //CL move indentation


template<class DbGraph>
struct StringVisitor2
{
    typedef typename DbGraph::vertex_descriptor vertex_descriptor;
    typedef typename DbGraph::tVertex2Depth     tVertex2Depth;

    //--------------------------------------------------------------------------
    // Visitors
    struct OnDiscoverVertex : public boost::base_visitor<OnDiscoverVertex>
    {
        OnDiscoverVertex(QString* result, tVertex2Depth& vertexDepth)
            : p_result(result), r_vertexDepth(vertexDepth){}

        typedef boost::on_discover_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& graph)
        {
            if(boost::out_degree(node, graph) > 0)
            {
                *p_result += indentation(depth(node)) + "(";
                *p_result += graph[node].name();
                *p_result += "\n";
            }
        }

        template<class Vertex>
        int depth(Vertex& node)
        {
            tVertex2Depth::iterator node_ = r_vertexDepth.find(node);
            return node_ == r_vertexDepth.end() ? 0 : (*node_).second;
        }


        QString* p_result;
        tVertex2Depth& r_vertexDepth;
    };

    struct OnExamineEdge : public boost::base_visitor<OnExamineEdge>
    {
        OnExamineEdge(QString* result, tVertex2Depth& vertexDepth)
            : p_result(result), r_vertexDepth(vertexDepth){}

        typedef boost::on_examine_edge event_filter;

        template<class Edge, class Graph>
        void operator()(Edge edge, Graph& graph)
        {
            //int source_depth = graph[source(edge, graph)].depth();
            vertex_descriptor sourceVertex = source(edge, graph);
            tVertex2Depth::iterator sourceVertex_ = r_vertexDepth.find(sourceVertex);
            int source_depth = sourceVertex_ == r_vertexDepth.end() ? 0 : (*sourceVertex_).second ;

            //CL int source_depth = vertexDepth[source(edge, graph)];
            int target_depth = source_depth + 1;

            //CL graph[target(edge, graph)].setDepth(target_depth);
            r_vertexDepth[target(edge, graph)] = target_depth;

            if(boost::out_degree(target(edge, graph), graph)==0)
            {
                *p_result += indentation(target_depth) + graph[target(edge, graph)].name();
                *p_result += "\n";
            }
        }

        template<class Vertex>
        int depth(Vertex& node)
        {
            tVertex2Depth::iterator node_ = r_vertexDepth.find(node);
            return node_ == r_vertexDepth.end() ? 0 : (*node_).second;
        }

        QString* p_result;
        tVertex2Depth& r_vertexDepth;
    };

    struct OnFinishVertex : public boost::base_visitor<OnFinishVertex>
    {
        OnFinishVertex(QString* result, tVertex2Depth& vertexDepth)
            : p_result(result), r_vertexDepth(vertexDepth){}

        typedef boost::on_finish_vertex event_filter;

        template<class Vertex, class Graph>
        void operator()(Vertex node, Graph& graph)
        {
            if(boost::out_degree(node, graph) > 0)
            {
                *p_result += indentation(depth(node)) + ")";
                *p_result += "\n";
            }
        }

        template<class Vertex>
        int depth(Vertex& node)
        {
            tVertex2Depth::iterator node_ = r_vertexDepth.find(node);
            return node_ == r_vertexDepth.end() ? 0 : (*node_).second;
        }

        QString* p_result;
        tVertex2Depth& r_vertexDepth;
    };

    template<class Vertex, class Graph>
    void initialize_vertex(Vertex& node, Graph& gra)
    {

    }

}; // StringVisitor

