// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BITSET_GRID_GRAPH_HPP
#define BOOST_GRAPH_BITSET_GRID_GRAPH_HPP

#include <boost/graph/bitset_grid_graph_fwd.hpp>

#include <numeric>

#if defined BOOST_GRAPH_USE_MPL_MATH
#include <boost/mpl/is_integral_constant.hpp>
#endif

#include <boost/cstdint.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/tr1/array.hpp>
#include <boost/bind.hpp>
#include <boost/limits.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/property_map/function_property_map.hpp>
#include <boost/graph/vertex_dimension_trait.hpp>
#include <boost/graph/vertex_coordinate_trait.hpp>
#include <boost/graph/grid_graph.hpp>

#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

#define BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS \
typename BitCount, typename VertexIndex, typename EdgeIndex, typename AllocSel

#define BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(b) \
bitset_grid_graph_index_function<BitCount,VertexIndex,EdgeIndex,AllocSel,b>

#define BOOST_GRAPH_BITSET_GRID_TYPE \
bitset_grid_graph<BitCount,VertexIndex,EdgeIndex,AllocSel>

#define BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS \
typename B, typename V, typename E, typename A

#define BOOST_GRAPH_BITSET_GRID_F_T \
bitset_grid_graph<B,V,E,A>

#define BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(mem) \
typename graph_traits<BOOST_GRAPH_BITSET_GRID_TYPE>::mem

#define BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(mem) \
typename graph_traits<BOOST_GRAPH_BITSET_GRID_F_T>::mem

namespace boost {

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS, bool IsVertex>
    class bitset_grid_graph_index_function
    {
        BOOST_GRAPH_BITSET_GRID_TYPE const* _graph;

     public:
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type)
                  , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type)
                >::type
                result_type;
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor)
                  , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
                >::type const&
                argument_type;

        explicit bitset_grid_graph_index_function(
            BOOST_GRAPH_BITSET_GRID_TYPE const* graph
        );

        result_type operator()(argument_type key) const;
    };

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS, bool IsVertex>
    BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(
        IsVertex
    )::bitset_grid_graph_index_function(
        BOOST_GRAPH_BITSET_GRID_TYPE const* graph
    ) : _graph(graph)
    {
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS, bool IsVertex>
    inline typename BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(
        IsVertex
    )::result_type
        BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(IsVertex)::operator()(
            argument_type key
        ) const
    {
        return this->_graph->_index_of(key);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_BITSET_GRID_TYPE,vertex_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(true)
                  , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_BITSET_GRID_TYPE,edge_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(false)
                  , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    struct vertex_dimension_trait<BOOST_GRAPH_BITSET_GRID_TYPE>
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::degree_size_type type;
    };

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    struct vertex_coordinate_trait<BOOST_GRAPH_BITSET_GRID_TYPE>
    {
        typedef bool type;
    };

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    struct edge_key_trait<BOOST_GRAPH_BITSET_GRID_TYPE>
      : vertex_dimension_trait<BOOST_GRAPH_BITSET_GRID_TYPE>
    {
    };

    template <
        typename BitCount
      , typename VertexIndex = void
      , typename EdgeIndex = void
      , typename AllocSel = ::boost::std_allocator_selector
    >
    class bitset_grid_graph
    {
#if defined BOOST_GRAPH_USE_MPL_MATH
        BOOST_STATIC_ASSERT(
            (::boost::mpl::is_integral_constant<BitCount>::value)
        );
#endif
        BOOST_STATIC_ASSERT(1 < BitCount::value);
        typedef typename BitCount::value_type Block;

     public:
        typedef BOOST_GRAPH_BITSET_GRID_TYPE type;

        // descriptors
        typedef ::boost::dynamic_bitset<
                    Block
                  , typename ::boost::mpl::apply_wrap1<AllocSel,Block>::type
                >
                vertex_descriptor;
        typedef ::std::pair<vertex_descriptor,vertex_descriptor>
                edge_descriptor;

        // sizes
        typedef typename vertex_descriptor::size_type
                degree_size_type;
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<VertexIndex>
                  , degree_size_type
                  , VertexIndex
                >::type
                vertices_size_type;
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<EdgeIndex>
                  , vertices_size_type
                  , EdgeIndex
                >::type
                edges_size_type;

     private:
        typedef ::boost::counting_iterator<vertices_size_type>
                VertexIndexIterator;
        typedef detail::grid_graph_vertex_at<type>
                VertexFunction;
        typedef ::boost::counting_iterator<edges_size_type>
                EdgeIndexIterator;
        typedef detail::grid_graph_edge_at<type>
                EdgeFunction;
        typedef ::boost::counting_iterator<degree_size_type>
                DegreeIterator;

        class AdjEdgeFunction
        {
            vertex_descriptor _vertex;
            bitset_grid_graph const* _graph;
            bool _is_out;

         public:
            typedef edge_descriptor result_type;
            typedef degree_size_type const& argument_type;

            AdjEdgeFunction();

            AdjEdgeFunction(
                vertex_descriptor const& vertex
              , bitset_grid_graph const* graph
              , bool is_out
            );

            result_type operator()(argument_type adjacent_index) const;
        };

        class AdjacencyFunction
        {
            vertex_descriptor _vertex;
            bitset_grid_graph const* _graph;

         public:
            typedef vertex_descriptor result_type;
            typedef degree_size_type const& argument_type;

            AdjacencyFunction();

            AdjacencyFunction(
                vertex_descriptor const& vertex
              , bitset_grid_graph const* graph
            );

            result_type operator()(argument_type adjacent_index) const;
        };

     public:
        // iterators
        typedef ::boost::transform_iterator<VertexFunction,VertexIndexIterator>
                vertex_iterator;
        typedef ::boost::transform_iterator<EdgeFunction,EdgeIndexIterator>
                edge_iterator;
        typedef ::boost::transform_iterator<AdjEdgeFunction,DegreeIterator>
                out_edge_iterator;
        typedef ::boost::transform_iterator<AdjEdgeFunction,DegreeIterator>
                in_edge_iterator;
        typedef ::boost::transform_iterator<AdjacencyFunction,DegreeIterator>
                adjacency_iterator;

        // categories
        typedef bidirectional_tag          directed_category;
        typedef disallow_parallel_edge_tag edge_parallel_category;

        struct traversal_category
          : incidence_graph_tag
          , adjacency_graph_tag
          , vertex_list_graph_tag
          , edge_list_graph_tag
          , bidirectional_graph_tag
          , adjacency_matrix_tag
        {
        };

     private:
        typedef ::boost::mpl::integral_c<degree_size_type,BitCount::value>
                NumBits;

        vertices_size_type _vertex_count;
        edges_size_type _edge_count;

     public:
        bitset_grid_graph();

        static vertex_descriptor null_vertex();

     private:
        void _precalculate();

        vertices_size_type const& _get_vertex_count() const;

        bool _is_valid(vertex_descriptor const& vertex) const;

        vertices_size_type _index_of(vertex_descriptor const& vertex) const;

        vertex_descriptor vertex_at(vertices_size_type const& index) const;

        edges_size_type const& _get_edge_count() const;

        edges_size_type _index_of(edge_descriptor const& edge) const;

        edge_descriptor edge_at(edges_size_type const& index) const;

        vertex_descriptor
            _get_neighbor_at(
                vertex_descriptor const& vertex
              , degree_size_type const& index
            ) const;

     public:
        // =========
        // GridGraph
        // =========
        typename vertex_dimension_trait<type>::type dimensions() const;

        ::boost::uint8_t
            length(
                typename vertex_dimension_trait<type>::type const& dimension
            ) const;

        bool
            wrapped(
                typename vertex_dimension_trait<type>::type const& dimension
            ) const;

        template <typename Distance>
        vertex_descriptor
            next(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
              , Distance const& distance
            ) const;

        template <typename Distance>
        vertex_descriptor
            previous(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
              , Distance const& distance
            ) const;

        // =========================
        // AssociativeIncidenceGraph
        // =========================
        vertex_descriptor
            next(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
            ) const;

        vertex_descriptor
            previous(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
            ) const;

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type)
            num_edge_keys(BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename edge_key_trait<BOOST_GRAPH_BITSET_GRID_F_T>::type
            edge_key(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // ===============
        // VertexListGraph
        // ===============
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_iterator)
          , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_iterator)
        >
            vertices(BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertices_size_type) const&
            num_vertices(BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor)
            vertex(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertices_size_type) const& i
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // =============
        // EdgeListGraph
        // =============
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_iterator)
          , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_iterator)
        >
            edges(BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edges_size_type) const&
            num_edges(BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_descriptor)
            edge_at(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edges_size_type) const& i
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // ==============
        // IncidenceGraph
        // ==============
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(out_edge_iterator)
          , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(out_edge_iterator)
        >
            out_edges(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type)
            out_degree(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_descriptor)
            out_edge_at(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // ==============
        // AdjacencyGraph
        // ==============
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(adjacency_iterator)
          , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(adjacency_iterator)
        >
            adjacent_vertices(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // ==================
        // BidirectionalGraph
        // ==================
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(in_edge_iterator)
          , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(in_edge_iterator)
        >
            in_edges(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type)
            in_degree(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type)
            degree(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_descriptor)
            in_edge_at(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // ===============
        // AdjacencyMatrix
        // ===============
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_descriptor)
          , bool
        >
            edge(
                BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& u
              , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
            );

        // =============
        // PropertyGraph
        // =============
        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename ::boost::property_map<
            BOOST_GRAPH_BITSET_GRID_F_T
          , vertex_index_t
        >::type
            get(vertex_index_t, BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertices_size_type)
            get(
                vertex_index_t
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
              , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(vertex_descriptor) const& v
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename ::boost::property_map<
            BOOST_GRAPH_BITSET_GRID_F_T
          , edge_index_t
        >::type
            get(edge_index_t, BOOST_GRAPH_BITSET_GRID_F_T const& graph);

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edges_size_type)
            get(
                edge_index_t
              , BOOST_GRAPH_BITSET_GRID_F_T const& graph
              , BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM(edge_descriptor) const& v
            );

        template <BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS, bool IsVertex>
        friend class bitset_grid_graph_index_function;
    };

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction::AdjEdgeFunction()
      : _vertex(), _graph(0), _is_out(false)
    {
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction::AdjEdgeFunction(
        vertex_descriptor const& vertex
      , bitset_grid_graph const* graph
      , bool is_out
    ) : _vertex(vertex), _graph(graph), _is_out(is_out)
    {
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction::result_type
        BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction::operator()(
            argument_type adjacency_index
        ) const
    {
        return (
            this->_is_out
          ? edge_descriptor(
                this->_vertex
              , this->_graph->_get_neighbor_at(this->_vertex, adjacency_index)
            )
          : edge_descriptor(
                this->_graph->_get_neighbor_at(this->_vertex, adjacency_index)
              , this->_vertex
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TYPE::AdjacencyFunction::AdjacencyFunction()
      : _vertex(), _graph(0)
    {
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TYPE::AdjacencyFunction::AdjacencyFunction(
        vertex_descriptor const& vertex
      , bitset_grid_graph const* graph
    ) : _vertex(vertex), _graph(graph)
    {
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline
    typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjacencyFunction::result_type
        BOOST_GRAPH_BITSET_GRID_TYPE::AdjacencyFunction::operator()(
            argument_type adjacency_index
        ) const
    {
        return this->_graph->_get_neighbor_at(_vertex, adjacency_index);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::null_vertex()
    {
        return vertex_descriptor();
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TYPE::bitset_grid_graph()
      : _vertex_count(::boost::initialized_value)
      , _edge_count(::boost::initialized_value)
    {
        this->_precalculate();
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    void BOOST_GRAPH_BITSET_GRID_TYPE::_precalculate()
    {
        vertices_size_type count = ::boost::initialized_value;
        ++count;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < NumBits::value;
            ++d
        )
        {
            count <<= 1;
        }

        this->_vertex_count = count;
        this->_edge_count = count;
        this->_edge_count *= NumBits::value;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::vertices_size_type const&
        BOOST_GRAPH_BITSET_GRID_TYPE::_get_vertex_count() const
    {
        return this->_vertex_count;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_BITSET_GRID_TYPE::_is_valid(
            vertex_descriptor const& vertex
        ) const
    {
        return NumBits::value == vertex.size();
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BITSET_GRID_TYPE::vertices_size_type
        BOOST_GRAPH_BITSET_GRID_TYPE::_index_of(
            vertex_descriptor const& vertex
        ) const
    {
        vertices_size_type result = ::boost::initialized_value;
        vertices_size_type factor = ::boost::initialized_value;

        ++factor;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < NumBits::value;
            ++d
        )
        {
            if (vertex[d])
            {
                result |= factor;
            }

            factor <<= 1;
        }

        return result;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::vertex_at(
            vertices_size_type const& index
        ) const
    {
        vertex_descriptor result(NumBits::value);
        vertices_size_type divisor = ::boost::initialized_value;

        ++divisor;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < NumBits::value;
            ++d
        )
        {
            result[d] = (index & divisor) ? true : false;
            divisor <<= 1;
        }

        return result;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::edges_size_type const&
        BOOST_GRAPH_BITSET_GRID_TYPE::_get_edge_count() const
    {
        return this->_edge_count;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::edges_size_type
        BOOST_GRAPH_BITSET_GRID_TYPE::_index_of(
            edge_descriptor const& edge
        ) const
    {
        edges_size_type src_id = this->_index_of(edge.first);
        edges_size_type diff = (edge.first ^ edge.second).find_first();

        return src_id * NumBits::value + diff;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::edge_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::edge_at(
            edges_size_type const& index
        ) const
    {
        vertex_descriptor src = this->vertex_at(
            static_cast<vertices_size_type>(index / NumBits::value)
        );

        return edge_descriptor(
            src
          , this->_get_neighbor_at(
                src
              , static_cast<degree_size_type>(index % NumBits::value)
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::_get_neighbor_at(
            vertex_descriptor const& vertex
          , degree_size_type const& index
        ) const
    {
        vertex_descriptor result(vertex);

        return result.flip(index);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename vertex_dimension_trait<
        typename BOOST_GRAPH_BITSET_GRID_TYPE::type
    >::type
        BOOST_GRAPH_BITSET_GRID_TYPE::dimensions() const
    {
        return NumBits::value;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::boost::uint8_t
        BOOST_GRAPH_BITSET_GRID_TYPE::length(
            typename vertex_dimension_trait<type>::type const& dimension
        ) const
    {
        return 2;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_BITSET_GRID_TYPE::wrapped(
            typename vertex_dimension_trait<type>::type const& dimension
        ) const
    {
        return true;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    template <typename Distance>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , Distance const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(key < NumBits::value);
        return (distance & 1) ? this->_get_neighbor_at(vertex, key) : vertex;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    template <typename Distance>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::previous(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , Distance const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(key < NumBits::value);
        return (distance & 1) ? this->_get_neighbor_at(vertex, key) : vertex;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(key < NumBits::value);
        return this->_get_neighbor_at(vertex, key);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BITSET_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_BITSET_GRID_TYPE::previous(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(key < NumBits::value);
        return this->_get_neighbor_at(vertex, key);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        num_edge_keys(BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        return NumBits::value;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename edge_key_trait<BOOST_GRAPH_BITSET_GRID_TYPE>::type
        edge_key(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type) const& i
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(i < ::boost::num_edge_keys(graph));
        return i;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_iterator)
    >
        vertices(BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::VertexIndexIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::VertexFunction(&graph)
            )
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::VertexIndexIterator(
                    graph._get_vertex_count()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::VertexFunction(&graph)
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type) const&
        num_vertices(BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        return graph._get_vertex_count();
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor)
        vertex(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_vertex_count());
        return graph.vertex_at(index);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_iterator)
    >
        edges(BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::EdgeIndexIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::EdgeFunction(&graph)
            )
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::EdgeIndexIterator(
                    graph._get_edge_count()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::EdgeFunction(&graph)
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type) const&
        num_edges(BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        return graph._get_edge_count();
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
        edge_at(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_edge_count());
        return graph.edge_at(index);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(out_edge_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(out_edge_iterator)
    >
        out_edges(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(out_edge_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , true
                )
            )
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(out_edge_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::DegreeIterator(
                    NumBits::value
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , true
                )
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        out_degree(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        BOOST_ASSERT(graph._is_valid(v));
        return NumBits::value;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
        out_edge_at(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)(
            v
          , graph._get_neighbor_at(v, index)
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(adjacency_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(adjacency_iterator)
    >
        adjacent_vertices(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& g
        )
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        BOOST_ASSERT(g._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(adjacency_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjacencyFunction(v, &g)
            )
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(adjacency_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::DegreeIterator(
                    NumBits::value
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjacencyFunction(v, &g)
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(in_edge_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(in_edge_iterator)
    >
        in_edges(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(in_edge_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , false
                )
            )
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(in_edge_iterator)(
                typename BOOST_GRAPH_BITSET_GRID_TYPE::DegreeIterator(
                    NumBits::value
                )
              , typename BOOST_GRAPH_BITSET_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , false
                )
            )
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        in_degree(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        BOOST_ASSERT(graph._is_valid(v));
        return NumBits::value;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        degree(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        typedef typename BOOST_GRAPH_BITSET_GRID_TYPE::NumBits NumBits;
        BOOST_ASSERT(graph._is_valid(v));
        return NumBits::value << 1;
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
        in_edge_at(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)(
            graph._get_neighbor_at(v, index)
          , v
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
      , bool
    >
        edge(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& u
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        )
    {
        typedef BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) Vertex;

        BOOST_ASSERT(graph._is_valid(u));
        BOOST_ASSERT(graph._is_valid(v));

        return ::std::make_pair(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)(u, v)
          , (1 == (u ^ v).count())
        );
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename ::boost::property_map<
        BOOST_GRAPH_BITSET_GRID_TYPE
      , vertex_index_t
    >::type
        get(vertex_index_t, BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        return typename ::boost::property_map<
            BOOST_GRAPH_BITSET_GRID_TYPE
          , vertex_index_t
        >::type(BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(true)(&graph));
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type)
        get(
            vertex_index_t
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._index_of(v);
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline typename ::boost::property_map<
        BOOST_GRAPH_BITSET_GRID_TYPE
      , edge_index_t
    >::type
        get(edge_index_t, BOOST_GRAPH_BITSET_GRID_TYPE const& graph)
    {
        return typename ::boost::property_map<
            BOOST_GRAPH_BITSET_GRID_TYPE
          , edge_index_t
        >::type(BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE(false)(&graph));
    }

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type)
        get(
            edge_index_t
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor) const& e
        )
    {
        BOOST_ASSERT(graph._is_valid(source(e, graph)));
        BOOST_ASSERT(graph._is_valid(target(e, graph)));
        return graph._index_of(e);
    }
}  // namespace boost

#undef BOOST_GRAPH_BITSET_GRID_F_TYPE_MEM
#undef BOOST_GRAPH_BITSET_GRID_TRAITS_MEM
#undef BOOST_GRAPH_BITSET_GRID_F_TYPE
#undef BOOST_GRAPH_BITSET_GRID_FRIEND_TEMPLATE_PARAMS
#undef BOOST_GRAPH_BITSET_GRID_TYPE
#undef BOOST_GRAPH_BITSET_GRID_IDX_FUNC_TYPE
#undef BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS

#endif  // BOOST_GRAPH_BITSET_GRID_GRAPH_HPP

