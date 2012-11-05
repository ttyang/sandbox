// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_ZETA_GRID_GRAPH_HPP
#define BOOST_GRAPH_ZETA_GRID_GRAPH_HPP

#include <boost/graph/zeta_grid_graph_fwd.hpp>

#include <functional>
#include <algorithm>
#include <numeric>

#if defined BOOST_GRAPH_USE_MPL_MATH
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/math/integral_power.hpp>
#endif

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/value_init.hpp>
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

#define BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS \
::std::size_t DimensionCount, typename Coordinate, \
typename VertexIndex, typename EdgeIndex

#define BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(b) \
zeta_grid_graph_idx_function<DimensionCount,Coordinate,VertexIndex,EdgeIndex,b>

#define BOOST_GRAPH_ZETA_GRID_TYPE \
zeta_grid_graph<DimensionCount,Coordinate,VertexIndex,EdgeIndex>

#define BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS \
::std::size_t D, typename C, typename V, typename E

#define BOOST_GRAPH_ZETA_GRID_F_T \
zeta_grid_graph<D,C,V,E>

#define BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(mem) \
typename graph_traits<BOOST_GRAPH_ZETA_GRID_TYPE>::mem

#define BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(mem) \
typename graph_traits<BOOST_GRAPH_ZETA_GRID_F_T>::mem

namespace boost {

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS, bool IsVertex>
    class zeta_grid_graph_idx_function
    {
        BOOST_GRAPH_ZETA_GRID_TYPE const* _graph;

     public:
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertices_size_type)
                  , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edges_size_type)
                >::type
                result_type;
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor)
                  , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)
                >::type const&
                argument_type;

        explicit zeta_grid_graph_idx_function(
            BOOST_GRAPH_ZETA_GRID_TYPE const* graph
        );

        result_type operator()(argument_type key) const;
    };

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS, bool IsVertex>
    BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(
        IsVertex
    )::zeta_grid_graph_idx_function(BOOST_GRAPH_ZETA_GRID_TYPE const* graph)
      : _graph(graph)
    {
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS, bool IsVertex>
    inline typename BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(IsVertex)::result_type
        BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(IsVertex)::operator()(
            argument_type key
        ) const
    {
        return this->_graph->_index_of(key);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_ZETA_GRID_TYPE,vertex_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(true)
                  , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_ZETA_GRID_TYPE,edge_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(false)
                  , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    struct vertex_dimension_trait<BOOST_GRAPH_ZETA_GRID_TYPE>
    {
        typedef typename ::std::tr1::array<
                    Coordinate
                  , DimensionCount
                >::size_type
                type;
    };

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    struct vertex_coordinate_trait<BOOST_GRAPH_ZETA_GRID_TYPE>
    {
        typedef Coordinate type;
    };

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    struct edge_key_trait<BOOST_GRAPH_ZETA_GRID_TYPE>
    {
        typedef ::std::tr1::array< ::boost::int8_t,DimensionCount> type;
    };

    template <
        ::std::size_t DimensionCount
      , typename Coordinate = ::std::size_t
      , typename VertexIndex = void
      , typename EdgeIndex = void
    >
    class zeta_grid_graph
    {
        BOOST_STATIC_ASSERT(1 < DimensionCount);
        typedef ::std::tr1::array<bool,DimensionCount> WraparoundArray;

     public:
        typedef BOOST_GRAPH_ZETA_GRID_TYPE type;

        // sizes
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<VertexIndex>
                  , Coordinate
                  , VertexIndex
                >::type
                vertices_size_type;
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<EdgeIndex>
                  , vertices_size_type
                  , EdgeIndex
                >::type
                edges_size_type;
        typedef edges_size_type
                degree_size_type;

        // descriptors
        typedef ::std::tr1::array<Coordinate,DimensionCount>
                vertex_descriptor;
        typedef ::std::pair<vertex_descriptor,vertex_descriptor>
                edge_descriptor;

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
            zeta_grid_graph const* _graph;
            bool _is_out;

         public:
            typedef edge_descriptor result_type;
            typedef degree_size_type const& argument_type;

            AdjEdgeFunction();

            AdjEdgeFunction(
                vertex_descriptor const& vertex
              , zeta_grid_graph const* graph
              , bool is_out
            );

            result_type operator()(argument_type adjacent_index) const;
        };

        class AdjacencyFunction
        {
            vertex_descriptor _vertex;
            zeta_grid_graph const* _graph;

         public:
            typedef vertex_descriptor result_type;
            typedef degree_size_type const& argument_type;

            AdjacencyFunction();

            AdjacencyFunction(
                vertex_descriptor const& vertex
              , zeta_grid_graph const* graph
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
//          , edge_list_graph_tag
          , bidirectional_graph_tag
          , adjacency_matrix_tag
        {
        };

     private:
        typedef typename vertex_descriptor::size_type Dimension;

        BOOST_STATIC_CONSTANT(Dimension, _dimension_count = DimensionCount);

#if defined BOOST_GRAPH_USE_MPL_MATH
        typedef typename ::boost::mpl::prior<
                    ::boost::mpl::math::integral_power<
                        ::boost::mpl::integral_c<degree_size_type,3>
                      , ::boost::mpl::integral_c<Dimension,_dimension_count>
                    >
                >::type
                EdgeKeyCount;
#endif

        vertex_descriptor  _dimension_lengths;
        WraparoundArray    _wrap_dimension;
        vertices_size_type _vertex_count;

#if !defined BOOST_GRAPH_USE_MPL_MATH
        degree_size_type   _edge_key_count;
#endif

        zeta_grid_graph();

     public:
        explicit zeta_grid_graph(
            vertex_descriptor const& dimension_lengths
          , bool wrap_all_dimensions = false
        );

        zeta_grid_graph(
            vertex_descriptor const& dimension_lengths
          , WraparoundArray const& wraparound_dimension
        );

        template <typename DimensionIterator>
        zeta_grid_graph(
            DimensionIterator dimension_lengths_itr
          , DimensionIterator dimension_lengths_end
          , bool wrap_all_dimensions = false
        );

        template <typename DimensionIterator, typename WraparoundIterator>
        zeta_grid_graph(
            DimensionIterator dimension_lengths_itr
          , DimensionIterator dimension_lengths_end
          , WraparoundIterator wraparound_dimension_itr
          , WraparoundIterator wraparound_dimension_end
        );

        static vertex_descriptor null_vertex();

     private:
        void _precalculate();

        vertices_size_type const& _get_vertex_count() const;

        bool _is_valid(vertex_descriptor const& vertex) const;

        vertices_size_type _index_of(vertex_descriptor const& vertex) const;

        vertex_descriptor vertex_at(vertices_size_type const& index) const;

        edges_size_type const& _get_edge_count() const;

        edges_size_type _index_of(edge_descriptor const& vertex) const;

        edge_descriptor edge_at(edges_size_type const& index) const;

        degree_size_type
            _get_neighborhood_size(vertex_descriptor const& vertex) const;

        vertex_descriptor
            _get_neighbor_at(
                vertex_descriptor const& vertex
              , degree_size_type index
            ) const;

        vertex_descriptor
            _get_next(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
              , Coordinate const& distance
            ) const;

#if defined BOOST_GRAPH_USE_MPL_MATH
        static typename edge_key_trait<type>::type
            _get_edge_key_at(degree_size_type index);
#else
        typename edge_key_trait<type>::type
            _get_edge_key_at(degree_size_type index) const;
#endif

        static bool _is_valid(typename edge_key_trait<type>::type const& key);

     public:
        // =========
        // GridGraph
        // =========
        Dimension dimensions() const;

        Coordinate const& length(Dimension const& dimension) const;

        bool wrapped(Dimension const& dimension) const;

        vertex_descriptor
            next(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
              , typename vertex_coordinate_trait<type>::type const& dist = (
                    typename vertex_coordinate_trait<type>::type() + 1
                )
            ) const;

        vertex_descriptor
            previous(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
              , typename vertex_coordinate_trait<type>::type const& dist = (
                    typename vertex_coordinate_trait<type>::type() + 1
                )
            ) const;

        // =========================
        // AssociativeIncidenceGraph
        // =========================
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type)
#if !defined BOOST_GRAPH_USE_MPL_MATH
        const&
#endif
            num_edge_keys(BOOST_GRAPH_ZETA_GRID_F_T const& graph);

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename edge_key_trait<BOOST_GRAPH_ZETA_GRID_F_T>::type
            edge_key(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // ===============
        // VertexListGraph
        // ===============
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_iterator)
          , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_iterator)
        >
            vertices(BOOST_GRAPH_ZETA_GRID_F_T const& graph);

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertices_size_type) const&
            num_vertices(BOOST_GRAPH_ZETA_GRID_F_T const& graph);

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor)
            vertex(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertices_size_type) const& i
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // =============
        // EdgeListGraph
        // =============
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edge_iterator)
          , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edge_iterator)
        >
            edges(BOOST_GRAPH_ZETA_GRID_F_T const& graph);

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edges_size_type) const&
            num_edges(BOOST_GRAPH_ZETA_GRID_F_T const& graph);

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edge_descriptor)
            edge_at(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edges_size_type) const& i
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // ==============
        // IncidenceGraph
        // ==============
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(out_edge_iterator)
          , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(out_edge_iterator)
        >
            out_edges(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type)
            out_degree(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edge_descriptor)
            out_edge_at(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // ==============
        // AdjacencyGraph
        // ==============
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(adjacency_iterator)
          , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(adjacency_iterator)
        >
            adjacent_vertices(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // ==================
        // BidirectionalGraph
        // ==================
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(in_edge_iterator)
          , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(in_edge_iterator)
        >
            in_edges(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type)
            in_degree(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type)
            degree(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edge_descriptor)
            in_edge_at(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // ===============
        // AdjacencyMatrix
        // ===============
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(edge_descriptor)
          , bool
        >
            edge(
                BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& u
              , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
            );

        // =============
        // PropertyGraph
        // =============
        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename ::boost::property_map<
            BOOST_GRAPH_ZETA_GRID_F_T
          , vertex_index_t
        >::type
            get(vertex_index_t, BOOST_GRAPH_ZETA_GRID_F_T const& graph);

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertices_size_type)
            get(
                vertex_index_t
              , BOOST_GRAPH_ZETA_GRID_F_T const& graph
              , BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM(vertex_descriptor) const& v
            );

        template <BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS, bool IsVertex>
        friend class zeta_grid_graph_idx_function;
    };

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction::AdjEdgeFunction()
      : _vertex(), _graph(0), _is_out(false)
    {
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction::AdjEdgeFunction(
        vertex_descriptor const& vertex
      , zeta_grid_graph const* graph
      , bool is_out
    ) : _vertex(vertex), _graph(graph), _is_out(is_out)
    {
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction::result_type
        BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction::operator()(
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

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_ZETA_GRID_TYPE::AdjacencyFunction::AdjacencyFunction()
      : _vertex(), _graph(0)
    {
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_ZETA_GRID_TYPE::AdjacencyFunction::AdjacencyFunction(
        vertex_descriptor const& vertex
      , zeta_grid_graph const* graph
    ) : _vertex(vertex), _graph(graph)
    {
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjacencyFunction::result_type
        BOOST_GRAPH_ZETA_GRID_TYPE::AdjacencyFunction::operator()(
            argument_type adjacency_index
        ) const
    {
        return this->_graph->_get_neighbor_at(_vertex, adjacency_index);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::null_vertex()
    {
        vertex_descriptor result;
        ::std::fill(
            result.begin()
          , result.end()
          , (::std::numeric_limits<Coordinate>::max)()
        );
        return result;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_ZETA_GRID_TYPE::zeta_grid_graph(
        vertex_descriptor const& dimension_lengths
      , bool wrap_all_dimensions
    ) : _dimension_lengths(dimension_lengths)
      , _wrap_dimension()
      , _vertex_count(::boost::initialized_value)
#if !defined BOOST_GRAPH_USE_MPL_MATH
      , _edge_key_count(::boost::initialized_value)
#endif
    {
        ::std::fill(
            this->_wrap_dimension.begin()
          , this->_wrap_dimension.end()
          , wrap_all_dimensions
        );
        this->_precalculate();
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_ZETA_GRID_TYPE::zeta_grid_graph(
        vertex_descriptor const& dimension_lengths
      , WraparoundArray const& wraparound_dimension
    ) : _dimension_lengths(dimension_lengths)
      , _wrap_dimension(wraparound_dimension)
      , _vertex_count(::boost::initialized_value)
#if !defined BOOST_GRAPH_USE_MPL_MATH
      , _edge_key_count(::boost::initialized_value)
#endif
    {
        this->_precalculate();
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    template <typename DimensionIterator>
    BOOST_GRAPH_ZETA_GRID_TYPE::zeta_grid_graph(
        DimensionIterator dimension_lengths_itr
      , DimensionIterator dimension_lengths_end
      , bool wrap_all_dimensions
    ) : _dimension_lengths()
      , _wrap_dimension()
      , _vertex_count(::boost::initialized_value)
#if !defined BOOST_GRAPH_USE_MPL_MATH
      , _edge_key_count(::boost::initialized_value)
#endif
    {
        ::std::copy(
            dimension_lengths_itr
          , dimension_lengths_end
          , this->_dimension_lengths.begin()
        );
        ::std::fill(
            this->_wrap_dimension.begin()
          , this->_wrap_dimension.end()
          , wrap_all_dimensions
        );
        this->_precalculate();
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    template <typename DimensionIterator, typename WraparoundIterator>
    BOOST_GRAPH_ZETA_GRID_TYPE::zeta_grid_graph(
        DimensionIterator dimension_lengths_itr
      , DimensionIterator dimension_lengths_end
      , WraparoundIterator wraparound_dimension_itr
      , WraparoundIterator wraparound_dimension_end
    ) : _dimension_lengths()
      , _wrap_dimension()
      , _vertex_count(::boost::initialized_value)
#if !defined BOOST_GRAPH_USE_MPL_MATH
      , _edge_key_count(::boost::initialized_value)
#endif
    {
        ::std::copy(
            dimension_lengths_itr
          , dimension_lengths_end
          , this->_dimension_lengths.begin()
        );
        ::std::copy(
            wraparound_dimension_itr
          , wraparound_dimension_end
          , this->_wrap_dimension.begin()
        );
        this->_precalculate();
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    void BOOST_GRAPH_ZETA_GRID_TYPE::_precalculate()
    {
#if defined _DEBUG
        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            BOOST_ASSERT(
                (2 < this->_dimension_lengths[d]) || (
                    !this->_wrap_dimension[d] && (
                        2 == this->_dimension_lengths[d]
                    )
                )
            );
        }
#endif

        vertices_size_type start = ::boost::initialized_value;
        this->_vertex_count = ::std::accumulate(
            this->_dimension_lengths.begin()
          , this->_dimension_lengths.end()
          , ++start
          , ::std::multiplies<vertices_size_type>()
        );

#if !defined BOOST_GRAPH_USE_MPL_MATH
        degree_size_type edge_keys = ::boost::initialized_value;
        ++edge_keys;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            edge_keys += (edge_keys << 1);
        }

        this->_edge_key_count = --edge_keys;
#endif
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_ZETA_GRID_TYPE::vertices_size_type const&
        BOOST_GRAPH_ZETA_GRID_TYPE::_get_vertex_count() const
    {
        return this->_vertex_count;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    bool
        BOOST_GRAPH_ZETA_GRID_TYPE::_is_valid(
            vertex_descriptor const& vertex
        ) const
    {
        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            if (!(vertex[d] < this->_dimension_lengths[d]))
            {
                return false;
            }
        }

        return true;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::vertices_size_type
        BOOST_GRAPH_ZETA_GRID_TYPE::_index_of(
            vertex_descriptor const& vertex
        ) const
    {
        vertices_size_type result = ::boost::initialized_value;
        vertices_size_type factor = ::boost::initialized_value;

        ++factor;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            result += vertex[d] * factor;
            factor *= this->_dimension_lengths[d];
        }

        return result;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::vertex_at(
            vertices_size_type const& index
        ) const
    {
        vertex_descriptor result;
        Coordinate divisor = ::boost::initialized_value;

        ++divisor;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            result[d] = (index / divisor) % this->_dimension_lengths[d];
            divisor *= this->_dimension_lengths[d];
        }

        return result;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_ZETA_GRID_TYPE::edges_size_type const&
        BOOST_GRAPH_ZETA_GRID_TYPE::_get_edge_count() const
    {
        // TODO
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::edges_size_type
        BOOST_GRAPH_ZETA_GRID_TYPE::_index_of(
            edge_descriptor const& edge
        ) const
    {
        // TODO
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::edge_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::edge_at(
            edges_size_type const& index
        ) const
    {
        // TODO
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::degree_size_type
        BOOST_GRAPH_ZETA_GRID_TYPE::_get_neighborhood_size(
            vertex_descriptor const& vertex
        ) const
    {
        degree_size_type result = ::boost::initialized_value;

        ++result;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            Coordinate d_len_m1 = this->_dimension_lengths[d];

            if (
                this->_wrap_dimension[d] || (
                    vertex[d] && (vertex[d] < --d_len_m1)
                )
            )
            {
                result += (result << 1);
            }
            else
            {
                result <<= 1;
            }
        }

        return result;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::_get_neighbor_at(
            vertex_descriptor const& vertex
          , degree_size_type index
        ) const
    {
        degree_size_type n = this->_get_neighborhood_size(vertex);
        BOOST_ASSERT_MSG(index + 1 < n, "index >= out_degree");
        vertex_descriptor result(vertex);

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            Coordinate d_len_m1 = this->_dimension_lengths[d];

            --d_len_m1;

            if (this->_wrap_dimension[d])
            {
                n /= 3;

                if (index < n)
                {
                    if (vertex[d])
                    {
                        --result[d];
                    }
                    else
                    {
                        result[d] = d_len_m1;
                    }
                }
                else if (index < n << 1)
                {
                    if (vertex[d] == d_len_m1)
                    {
                        result[d] = ::boost::initialized_value;
                    }
                    else
                    {
                        ++result[d];
                    }

                    index -= n;
                }
                else
                {
                    index -= n << 1;
                }
            }
            else if (vertex[d] == d_len_m1)
            {
                n >>= 1;

                if (index < n)
                {
                    --result[d];
                }
                else
                {
                    index -= n;
                }
            }
            else if (vertex[d])
            {
                n /= 3;

                if (index < n)
                {
                    --result[d];
                }
                else if (index < n << 1)
                {
                    ++result[d];
                    index -= n;
                }
                else
                {
                    index -= n << 1;
                }
            }
            else
            {
                n >>= 1;

                if (index < n)
                {
                    ++result[d];
                }
                else
                {
                    index -= n;
                }
            }
        }

        return result;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::_get_next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , Coordinate const& distance
        ) const
    {
        vertex_descriptor result(vertex);
        Coordinate truncated_distance = distance;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            Coordinate const d_len = this->_dimension_lengths[d];

            switch (key[d])
            {
                case -1:
                {
                    if (!(result[d] < distance))
                    {
                        result[d] -= distance;
                    }
                    else if (this->_wrap_dimension[d])
                    {
                        result[d] += d_len;
                        result[d] -= distance % d_len;
                        result[d] %= d_len;
                    }
                    else if (result[d] < truncated_distance)
                    {
                        if (!(truncated_distance = result[d]))
                        {
                            return vertex;
                        }
                    }

                    break;
                }

                case 0:
                {
                    break;
                }

                case 1:
                {
                    if (result[d] + distance < d_len)
                    {
                        result[d] += distance;
                    }
                    else if (this->_wrap_dimension[d])
                    {
                        result[d] += distance;
                        result[d] %= d_len;
                    }
                    else
                    {
                        Coordinate truncated = d_len - result[d];

                        if (--truncated)
                        {
                            if (truncated < truncated_distance)
                            {
                                truncated_distance = truncated;
                            }
                        }
                        else
                        {
                            return vertex;
                        }
                    }

                    break;
                }

                default:
                {
                    return vertex;
                }
            }
        }

        if (truncated_distance == distance)
        {
            return result;
        }
        else
        {
            return this->_get_next(vertex, key, truncated_distance);
        }
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename edge_key_trait<typename BOOST_GRAPH_ZETA_GRID_TYPE::type>::type
        BOOST_GRAPH_ZETA_GRID_TYPE::_get_edge_key_at(degree_size_type index)
#if !defined BOOST_GRAPH_USE_MPL_MATH
        const
#endif
    {
#if defined BOOST_GRAPH_USE_MPL_MATH
        degree_size_type n = EdgeKeyCount::value;
#else
        degree_size_type n = this->_edge_key_count;
#endif
        typename edge_key_trait<type>::type result;

        ++n;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            result[d] = ::boost::initialized_value;
            n /= 3;

            if (index < n)
            {
                --result[d];
            }
            else if (index < n << 1)
            {
                ++result[d];
                index -= n;
            }
            else
            {
                index -= n << 1;
            }
        }

        return result;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    bool
        BOOST_GRAPH_ZETA_GRID_TYPE::_is_valid(
            typename edge_key_trait<type>::type const& key
        )
    {
        bool has_at_least_one_positive_or_negative_one = false;

        for (
            Dimension d = ::boost::initialized_value;
            d < BOOST_GRAPH_ZETA_GRID_TYPE::_dimension_count;
            ++d
        )
        {
            switch (key[d])
            {
                case -1:
                case 1:
                {
                    has_at_least_one_positive_or_negative_one = true;
                }

                case 0:
                {
                    break;
                }

                default:
                {
                    return false;
                }
            }
        }

        return has_at_least_one_positive_or_negative_one;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_ZETA_GRID_TYPE::Dimension
        BOOST_GRAPH_ZETA_GRID_TYPE::dimensions() const
    {
        return this->_dimension_count;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline Coordinate const&
        BOOST_GRAPH_ZETA_GRID_TYPE::length(Dimension const& dimension) const
    {
        return this->_dimension_lengths[dimension];
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_ZETA_GRID_TYPE::wrapped(Dimension const& dimension) const
    {
        return this->_wrap_dimension[dimension];
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_ZETA_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , typename vertex_coordinate_trait<type>::type const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(this->_is_valid(key));
        return this->_get_next(vertex, key, distance);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_ZETA_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_ZETA_GRID_TYPE::previous(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , typename vertex_coordinate_trait<type>::type const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(this->_is_valid(key));
        typename edge_key_trait<type>::type opposite_key;

        for (
            Dimension d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            opposite_key[d] = -key[d];
        }

        return this->_get_next(vertex, opposite_key, distance);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
#if !defined BOOST_GRAPH_USE_MPL_MATH
        const&
#endif
        num_edge_keys(BOOST_GRAPH_ZETA_GRID_TYPE const& graph)
    {
#if defined BOOST_GRAPH_USE_MPL_MATH
        typedef typename BOOST_GRAPH_ZETA_GRID_TYPE::EdgeKeyCount EdgeKeyCount;
        return EdgeKeyCount::value;
#else
        return graph._edge_key_count;
#endif
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename edge_key_trait<BOOST_GRAPH_ZETA_GRID_TYPE>::type
        edge_key(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < ::boost::num_edge_keys(graph));
        return graph._get_edge_key_at(index);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_iterator)
      , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_iterator)
    >
        vertices(BOOST_GRAPH_ZETA_GRID_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::VertexIndexIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertices_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::VertexFunction(&graph)
            )
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::VertexIndexIterator(
                    graph._get_vertex_count()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::VertexFunction(&graph)
            )
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertices_size_type) const&
        num_vertices(BOOST_GRAPH_ZETA_GRID_TYPE const& graph)
    {
        return graph._get_vertex_count();
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor)
        vertex(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertices_size_type) const& index
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_vertex_count());
        return graph.vertex_at(index);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_iterator)
      , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_iterator)
    >
        edges(BOOST_GRAPH_ZETA_GRID_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::EdgeIndexIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edges_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::EdgeFunction(&graph)
            )
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::EdgeIndexIterator(
                    graph._get_edge_count()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::EdgeFunction(&graph)
            )
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edges_size_type)
        num_edges(BOOST_GRAPH_ZETA_GRID_TYPE const& graph)
    {
        return graph._get_edge_count();
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)
        edge_at(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edges_size_type) const& index
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_edge_count());
        return graph.edge_at(index);
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(out_edge_iterator)
      , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(out_edge_iterator)
    >
        out_edges(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(out_edge_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , true
                )
            )
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(out_edge_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::DegreeIterator(
                    graph._get_neighborhood_size(v) - 1
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , true
                )
            )
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
        out_degree(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighborhood_size(v) - 1;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)
        out_edge_at(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)(
            v
          , graph._get_neighbor_at(v, index)
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(adjacency_iterator)
      , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(adjacency_iterator)
    >
        adjacent_vertices(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& g
        )
    {
        BOOST_ASSERT(g._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(adjacency_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjacencyFunction(v, &g)
            )
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(adjacency_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::DegreeIterator(
                    g._get_neighborhood_size(v) - 1
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjacencyFunction(v, &g)
            )
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(in_edge_iterator)
      , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(in_edge_iterator)
    >
        in_edges(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(in_edge_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , false
                )
            )
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(in_edge_iterator)(
                typename BOOST_GRAPH_ZETA_GRID_TYPE::DegreeIterator(
                    graph._get_neighborhood_size(v) - 1
                )
              , typename BOOST_GRAPH_ZETA_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , false
                )
            )
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
        in_degree(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighborhood_size(v) - 1;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type)
        degree(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return (graph._get_neighborhood_size(v) - 1) << 1;
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)
        in_edge_at(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)(
            graph._get_neighbor_at(v, index)
          , v
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    ::std::pair<BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor),bool>
        edge(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& u
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(u));
        BOOST_ASSERT(graph._is_valid(v));

        Coordinate const d0 = ::boost::initialized_value;
        bool is_different = false;

        for (
            typename BOOST_GRAPH_ZETA_GRID_TYPE::Dimension d = (
                ::boost::initialized_value
            );
            d < graph._dimension_count;
            ++d
        )
        {
            Coordinate const d_len = graph._dimension_lengths[d];

            if (
                graph._wrap_dimension[d] && (
                    (
                        (d0 == u[d]) && (d_len == v[d] + 1)
                    ) || (
                        (d0 == v[d]) && (d_len == u[d] + 1)
                    )
                )
            )
            {
                is_different = true;
            }
            else if ((u[d] + 1 < v[d]) || (v[d] + 1 < u[d]))
            {
                return ::std::make_pair(
                    BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)(u, v)
                  , false
                );
            }
            else if (u[d] != v[d])
            {
                is_different = true;
            }
        }

        return ::std::make_pair(
            BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(edge_descriptor)(u, v)
          , is_different
        );
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline typename ::boost::property_map<
        BOOST_GRAPH_ZETA_GRID_TYPE
      , vertex_index_t
    >::type
        get(vertex_index_t, BOOST_GRAPH_ZETA_GRID_TYPE const& graph)
    {
        return typename ::boost::property_map<
            BOOST_GRAPH_ZETA_GRID_TYPE
          , vertex_index_t
        >::type(BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE(true)(&graph));
    }

    template <BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertices_size_type)
        get(
            vertex_index_t
          , BOOST_GRAPH_ZETA_GRID_TYPE const& graph
          , BOOST_GRAPH_ZETA_GRID_TRAITS_MEM(vertex_descriptor) const& v
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._index_of(v);
    }
}  // namespace boost

#undef BOOST_GRAPH_ZETA_GRID_F_TYPE_MEM
#undef BOOST_GRAPH_ZETA_GRID_TRAITS_MEM
#undef BOOST_GRAPH_ZETA_GRID_F_TYPE
#undef BOOST_GRAPH_ZETA_GRID_FRIEND_TEMPLATE_PARAMS
#undef BOOST_GRAPH_ZETA_GRID_TYPE
#undef BOOST_GRAPH_ZETA_GRID_IDX_FUNC_TYPE
#undef BOOST_GRAPH_ZETA_GRID_TEMPLATE_PARAMS

#endif  // BOOST_GRAPH_ZETA_GRID_GRAPH_HPP

