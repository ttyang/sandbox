// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_UPSILON_GRID_GRAPH_HPP
#define BOOST_GRAPH_UPSILON_GRID_GRAPH_HPP

#include <boost/graph/upsilon_grid_graph_fwd.hpp>

#include <functional>
#include <algorithm>
#include <numeric>
#include <cstddef>

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

#include <boost/assert.hpp>

#define BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS \
typename Coordinate, typename VertexIndex, typename EdgeIndex

#define BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(b) \
upsilon_grid_graph_index_function<Coordinate,VertexIndex,EdgeIndex,b>

#define BOOST_GRAPH_UPSILON_GRID_TYPE \
upsilon_grid_graph<Coordinate,VertexIndex,EdgeIndex>

#define BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS \
typename C, typename V, typename E

#define BOOST_GRAPH_UPSILON_GRID_F_T \
upsilon_grid_graph<C,V,E>

#define BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(mem) \
typename graph_traits<BOOST_GRAPH_UPSILON_GRID_TYPE>::mem

#define BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(mem) \
typename graph_traits<BOOST_GRAPH_UPSILON_GRID_F_T>::mem

#define BOOST_GRAPH_UPSILON_GRID_EDGE_KEY_TYPE \
::std::tr1::array< ::boost::int8_t,2>

namespace boost { namespace detail {

    inline bool
        is_valid_upsilon_grid_graph_edge_key(
            BOOST_GRAPH_UPSILON_GRID_EDGE_KEY_TYPE const& key
        )
    {
        switch (key[0])
        {
            case 0:
            {
                return (-1 == key[1]) || (1 == key[1]);
            }

            case -1:
            case 1:
            {
                return (-1 == key[1]) || (0 == key[1]) || (1 == key[1]);
            }

            default:
            {
                return false;
            }
        }
    }

    template <typename DegreeSize>
    inline BOOST_GRAPH_UPSILON_GRID_EDGE_KEY_TYPE
        get_upsilon_grid_graph_edge_key(DegreeSize const& index)
    {
        BOOST_GRAPH_UPSILON_GRID_EDGE_KEY_TYPE result;

        switch (index)
        {
            case 0:
            {
                result = {{-1, 0}};
                break;
            }

            case 1:
            {
                result = {{1, 0}};
                break;
            }

            case 2:
            {
                result = {{0, -1}};
                break;
            }

            case 3:
            {
                result = {{0, 1}};
                break;
            }

            case 4:
            {
                result = {{-1, -1}};
                break;
            }

            case 5:
            {
                result = {{1, -1}};
                break;
            }

            case 6:
            {
                result = {{-1, 1}};
                break;
            }

            case 7:
            {
                result = {{1, 1}};
                break;
            }

            default:
            {
                break;
            }
        }

        return result;
    }
}}  // namespace boost::detail

namespace boost {

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS, bool IsVertex>
    class upsilon_grid_graph_index_function
    {
        BOOST_GRAPH_UPSILON_GRID_TYPE const* _graph;

     public:
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertices_size_type)
                  , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edges_size_type)
                >::type
                result_type;
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor)
                  , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)
                >::type const&
                argument_type;

        explicit upsilon_grid_graph_index_function(
            BOOST_GRAPH_UPSILON_GRID_TYPE const* graph
        );

        result_type operator()(argument_type key) const;
    };

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS, bool IsVertex>
    BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(
        IsVertex
    )::upsilon_grid_graph_index_function(
        BOOST_GRAPH_UPSILON_GRID_TYPE const* graph
    ) : _graph(graph)
    {
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS, bool IsVertex>
    inline typename BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(
        IsVertex
    )::result_type
        BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(IsVertex)::operator()(
            argument_type key
        ) const
    {
        return this->_graph->_index_of(key);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_UPSILON_GRID_TYPE,vertex_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(true)
                  , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_UPSILON_GRID_TYPE,edge_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(false)
                  , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    struct vertex_dimension_trait<BOOST_GRAPH_UPSILON_GRID_TYPE>
    {
        typedef typename ::std::tr1::array<Coordinate,2>::value_type type;
    };

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    struct vertex_coordinate_trait<BOOST_GRAPH_UPSILON_GRID_TYPE>
    {
        typedef Coordinate type;
    };

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    struct edge_key_trait<BOOST_GRAPH_UPSILON_GRID_TYPE>
    {
        typedef ::std::tr1::array< ::boost::int8_t,2> type;
    };

    template <
        typename Coordinate = ::std::size_t
      , typename VertexIndex = void
      , typename EdgeIndex = void
    >
    class upsilon_grid_graph
    {
        typedef ::std::tr1::array<bool,2> WraparoundArray;

     public:
        typedef BOOST_GRAPH_UPSILON_GRID_TYPE type;

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
        typedef Coordinate
                degree_size_type;

        // descriptors
        typedef ::std::tr1::array<Coordinate,2>
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
            upsilon_grid_graph const* _graph;
            bool _is_out;

         public:
            typedef edge_descriptor result_type;
            typedef degree_size_type const& argument_type;

            AdjEdgeFunction();

            AdjEdgeFunction(
                vertex_descriptor const& vertex
              , upsilon_grid_graph const* graph
              , bool is_out
            );

            result_type operator()(argument_type adjacent_index) const;
        };

        class AdjacencyFunction
        {
            vertex_descriptor _vertex;
            upsilon_grid_graph const* _graph;

         public:
            typedef vertex_descriptor result_type;
            typedef degree_size_type const& argument_type;

            AdjacencyFunction();

            AdjacencyFunction(
                vertex_descriptor const& vertex
              , upsilon_grid_graph const* graph
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

        BOOST_STATIC_CONSTANT(Dimension, _dimension_count = 2);
        BOOST_STATIC_CONSTANT(degree_size_type, _edge_key_count = 8);

        vertex_descriptor  _dimension_lengths;
        WraparoundArray    _wrap_dimension;
        vertices_size_type _vertex_count;
        bool               _has_octagon_origin;

        upsilon_grid_graph();

     public:
        explicit upsilon_grid_graph(
            vertex_descriptor const& dimension_lengths
          , bool wrap_all_dimensions = false
          , bool has_octagon_origin = true
        );

        upsilon_grid_graph(
            vertex_descriptor const& dimension_lengths
          , WraparoundArray const& wraparound_dimension
          , bool has_octagon_origin = true
        );

        template <typename DimensionIterator>
        upsilon_grid_graph(
            DimensionIterator dimension_lengths_itr
          , DimensionIterator dimension_lengths_end
          , bool wrap_all_dimensions = false
          , bool has_octagon_origin = true
        );

        template <typename DimensionIterator, typename WraparoundIterator>
        upsilon_grid_graph(
            DimensionIterator dimension_lengths_itr
          , DimensionIterator dimension_lengths_end
          , WraparoundIterator wraparound_dimension_itr
          , WraparoundIterator wraparound_dimension_end
          , bool has_octagon_origin = true
        );

        static vertex_descriptor null_vertex();

        bool is_octagon(vertex_descriptor const& vertex) const;

     private:
        void _precalculate();

        vertices_size_type const& _get_vertex_count() const;

        bool _is_valid(vertex_descriptor const& vertex) const;

        bool _is_octagon(vertex_descriptor const& vertex) const;

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
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type)
            num_edge_keys(BOOST_GRAPH_UPSILON_GRID_F_T const& graph);

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename edge_key_trait<BOOST_GRAPH_UPSILON_GRID_F_T>::type
            edge_key(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // ===============
        // VertexListGraph
        // ===============
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_iterator)
          , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_iterator)
        >
            vertices(BOOST_GRAPH_UPSILON_GRID_F_T const& graph);

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertices_size_type) const&
            num_vertices(BOOST_GRAPH_UPSILON_GRID_F_T const& graph);

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor)
            vertex(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertices_size_type) const& i
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // =============
        // EdgeListGraph
        // =============
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edge_iterator)
          , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edge_iterator)
        >
            edges(BOOST_GRAPH_UPSILON_GRID_F_T const& graph);

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edges_size_type) const&
            num_edges(BOOST_GRAPH_UPSILON_GRID_F_T const& graph);

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edge_descriptor)
            edge_at(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edges_size_type) const& i
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // ==============
        // IncidenceGraph
        // ==============
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(out_edge_iterator)
          , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(out_edge_iterator)
        >
            out_edges(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type)
            out_degree(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edge_descriptor)
            out_edge_at(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // ==============
        // AdjacencyGraph
        // ==============
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(adjacency_iterator)
          , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(adjacency_iterator)
        >
            adjacent_vertices(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // ==================
        // BidirectionalGraph
        // ==================
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(in_edge_iterator)
          , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(in_edge_iterator)
        >
            in_edges(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type)
            in_degree(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type)
            degree(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edge_descriptor)
            in_edge_at(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(degree_size_type) const& i
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // ===============
        // AdjacencyMatrix
        // ===============
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(edge_descriptor)
          , bool
        >
            edge(
                BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& u
              , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
            );

        // =============
        // PropertyGraph
        // =============
        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend typename ::boost::property_map<
            BOOST_GRAPH_UPSILON_GRID_F_T
          , vertex_index_t
        >::type
            get(vertex_index_t, BOOST_GRAPH_UPSILON_GRID_F_T const& graph);

        template <BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertices_size_type)
            get(
                vertex_index_t
              , BOOST_GRAPH_UPSILON_GRID_F_T const& graph
              , BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM(vertex_descriptor) const& v
            );

        template <
            BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS
          , bool IsVertex
        >
        friend class upsilon_grid_graph_index_function;
    };

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction::AdjEdgeFunction()
      : _vertex(), _graph(0), _is_out(false)
    {
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction::AdjEdgeFunction(
        vertex_descriptor const& vertex
      , upsilon_grid_graph const* graph
      , bool is_out
    ) : _vertex(vertex), _graph(graph), _is_out(is_out)
    {
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction::result_type
        BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction::operator()(
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

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_UPSILON_GRID_TYPE::AdjacencyFunction::AdjacencyFunction()
      : _vertex(), _graph(0)
    {
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_UPSILON_GRID_TYPE::AdjacencyFunction::AdjacencyFunction(
        vertex_descriptor const& vertex
      , upsilon_grid_graph const* graph
    ) : _vertex(vertex), _graph(graph)
    {
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjacencyFunction::result_type
        BOOST_GRAPH_UPSILON_GRID_TYPE::AdjacencyFunction::operator()(
            argument_type adjacency_index
        ) const
    {
        return this->_graph->_get_neighbor_at(_vertex, adjacency_index);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::null_vertex()
    {
        vertex_descriptor result;
        ::std::fill(
            result.begin()
          , result.end()
          , (::std::numeric_limits<Coordinate>::max)()
        );
        return result;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_UPSILON_GRID_TYPE::upsilon_grid_graph(
        vertex_descriptor const& dimension_lengths
      , bool wrap_all_dimensions
      , bool has_octagon_origin
    ) : _dimension_lengths(dimension_lengths)
      , _wrap_dimension()
      , _vertex_count(::boost::initialized_value)
      , _has_octagon_origin(has_octagon_origin)
    {
        ::std::fill(
            this->_wrap_dimension.begin()
          , this->_wrap_dimension.end()
          , wrap_all_dimensions
        );
        this->_precalculate();
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_UPSILON_GRID_TYPE::upsilon_grid_graph(
        vertex_descriptor const& dimension_lengths
      , WraparoundArray const& wraparound_dimension
      , bool has_octagon_origin
    ) : _dimension_lengths(dimension_lengths)
      , _wrap_dimension(wraparound_dimension)
      , _vertex_count(::boost::initialized_value)
      , _has_octagon_origin(has_octagon_origin)
    {
        this->_precalculate();
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    template <typename DimensionIterator>
    BOOST_GRAPH_UPSILON_GRID_TYPE::upsilon_grid_graph(
        DimensionIterator dimension_lengths_itr
      , DimensionIterator dimension_lengths_end
      , bool wrap_all_dimensions
      , bool has_octagon_origin
    ) : _dimension_lengths()
      , _wrap_dimension()
      , _vertex_count(::boost::initialized_value)
      , _has_octagon_origin(has_octagon_origin)
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

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    template <typename DimensionIterator, typename WraparoundIterator>
    BOOST_GRAPH_UPSILON_GRID_TYPE::upsilon_grid_graph(
        DimensionIterator dimension_lengths_itr
      , DimensionIterator dimension_lengths_end
      , WraparoundIterator wraparound_dimension_itr
      , WraparoundIterator wraparound_dimension_end
      , bool has_octagon_origin
    ) : _dimension_lengths()
      , _wrap_dimension()
      , _vertex_count(::boost::initialized_value)
      , _has_octagon_origin(has_octagon_origin)
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

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_UPSILON_GRID_TYPE::is_octagon(
            vertex_descriptor const& vertex
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        return this->_is_octagon(vertex);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    void BOOST_GRAPH_UPSILON_GRID_TYPE::_precalculate()
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
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertices_size_type const&
        BOOST_GRAPH_UPSILON_GRID_TYPE::_get_vertex_count() const
    {
        return this->_vertex_count;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_UPSILON_GRID_TYPE::_is_valid(
            vertex_descriptor const& vertex
        ) const
    {
        return (vertex[0] < this->_dimension_lengths[0]) && (
            vertex[1] < this->_dimension_lengths[1]
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_UPSILON_GRID_TYPE::_is_octagon(
            vertex_descriptor const& vertex
        ) const
    {
        return (
            (vertex[0] & 1) == (vertex[1] & 1)
        ) == this->_has_octagon_origin;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertices_size_type
        BOOST_GRAPH_UPSILON_GRID_TYPE::_index_of(
            vertex_descriptor const& vertex
        ) const
    {
        return vertex[1] * this->_dimension_lengths[0] + vertex[0];
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_at(
            vertices_size_type const& index
        ) const
    {
        vertex_descriptor result;

        result[0] = index % this->_dimension_lengths[0];
        result[1] = (
            index / this->_dimension_lengths[0]
        ) % this->_dimension_lengths[1];

        return result;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::edges_size_type const&
        BOOST_GRAPH_UPSILON_GRID_TYPE::_get_edge_count() const
    {
        // TODO
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::edges_size_type
        BOOST_GRAPH_UPSILON_GRID_TYPE::_index_of(
            edge_descriptor const& edge
        ) const
    {
        // TODO
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::edge_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::edge_at(
            edges_size_type const& index
        ) const
    {
        // TODO
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::degree_size_type
        BOOST_GRAPH_UPSILON_GRID_TYPE::_get_neighborhood_size(
            vertex_descriptor const& vertex
        ) const
    {
        degree_size_type result = ::boost::initialized_value;

        ++result;

        if (this->_is_octagon(vertex))
        {
            degree_size_type count = ::boost::initialized_value;

            for (
                Dimension d = ::boost::initialized_value;
                d < this->_dimension_count;
                ++d
            )
            {
                Coordinate d_len_m1 = this->_dimension_lengths[d];

                --d_len_m1;

                if (vertex[d] && (vertex[d] < d_len_m1))
                {
                    result += (result << 1);
                }
                else if (this->_wrap_dimension[d])
                {
                    if (d_len_m1 & 1)
                    {
                        result += (result << 1);
                    }
                    else
                    {
                        result <<= 1;
                        ++count;
                    }
                }
                else
                {
                    result <<= 1;
                }
            }

            result += count;
        }
        else  // Square vertex.
        {
            for (
                Dimension d = ::boost::initialized_value;
                d < this->_dimension_count;
                ++d
            )
            {
                Coordinate d_len_m1 = this->_dimension_lengths[d];

                --d_len_m1;

                if (
                    (this->_wrap_dimension[d] && (d_len_m1 & 1)) || (
                        vertex[d] && (vertex[d] < d_len_m1)
                    )
                )
                {
                    result += 2;
                }
                else
                {
                    ++result;
                }
            }
        }

        return result;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::_get_neighbor_at(
            vertex_descriptor const& vertex
          , degree_size_type index
        ) const
    {
        BOOST_ASSERT(index + 1 < this->_get_neighborhood_size(vertex));

        vertex_descriptor result(vertex);

        if (this->_is_octagon(vertex))
        {
            static const ::boost::uint8_t is_min_at_dim_0  = 0x01;
            static const ::boost::uint8_t is_max_at_dim_0  = 0x02;
            static const ::boost::uint8_t is_wrap_dim_0    = 0x04;
            static const ::boost::uint8_t is_odd_len_dim_0 = 0x08;
            static const ::boost::uint8_t is_min_at_dim_1  = 0x10;
            static const ::boost::uint8_t is_max_at_dim_1  = 0x20;
            static const ::boost::uint8_t is_wrap_dim_1    = 0x40;
            static const ::boost::uint8_t is_odd_len_dim_1 = 0x80;

            ::boost::uint8_t vertex_case = 0;

            if (vertex[0] + 1 == this->_dimension_lengths[0])
            {
                vertex_case |= is_max_at_dim_0;
            }
            else if (!vertex[0])
            {
                vertex_case |= is_min_at_dim_0;
            }

            if (vertex_case && this->_wrap_dimension[0])
            {
                vertex_case |= is_wrap_dim_0;

                if (this->_dimension_lengths[0] & 1)
                {
                    vertex_case |= is_odd_len_dim_0;
                }
            }

            if (vertex[1] + 1 == this->_dimension_lengths[1])
            {
                vertex_case |= is_max_at_dim_1;
            }
            else if (!vertex[1])
            {
                vertex_case |= is_min_at_dim_1;
            }

            if (
                (
                    vertex_case & (is_max_at_dim_1 | is_min_at_dim_1)
                ) && this->_wrap_dimension[1]
            )
            {
                vertex_case |= is_wrap_dim_1;

                if (this->_dimension_lengths[1] & 1)
                {
                    vertex_case |= is_odd_len_dim_1;
                }
            }

            Coordinate d_max_0 = this->_dimension_lengths[0];
            Coordinate d_max_1 = this->_dimension_lengths[1];

            --d_max_0;
            --d_max_1;

            switch (vertex_case)
            {
                case 0xEE:
                {
                    switch (index)
                    {
                        case 0:
                        {
                            --result[0];
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            --result[0];
                            break;
                        }

                        case 2:
                        {
                            --result[1];
                            break;
                        }

                        case 3:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }

                        case 4:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0xED:
                {
                    switch (index)
                    {
                        case 0:
                        {
                            ++result[0];
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }

                        case 2:
                        {
                            --result[1];
                            break;
                        }

                        case 3:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 4:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0xDE:
                {
                    switch (index)
                    {
                        case 0:
                        {
                            --result[0];
                            ++result[1];
                            break;
                        }

                        case 1:
                        {
                            --result[0];
                            break;
                        }

                        case 2:
                        {
                            ++result[1];
                            break;
                        }

                        case 3:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }

                        case 4:
                        {
                            result[1] = d_max_1;
                            break;
                        }
                    }

                    break;
                }

                case 0xDD:
                {
                    switch (index)
                    {
                        case 0:
                        {
                            ++result[0];
                            ++result[1];
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }

                        case 2:
                        {
                            ++result[1];
                            break;
                        }

                        case 3:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 4:
                        {
                            result[1] = d_max_1;
                            break;
                        }
                    }

                    break;
                }

                case 0xE2:
                {
                    if (3 == index)
                    {
                        result[1] = ::boost::initialized_value;
                        break;
                    }

                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    if (!(index & 2))
                    {
                        --result[1];
                    }

                    break;
                }

                case 0x2E:
                {
                    if (3 == index)
                    {
                        result[0] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x22:
                {
                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    if (!(index & 2))
                    {
                        --result[1];
                    }

                    break;
                }

                case 0xE1:
                {
                    if (3 == index)
                    {
                        result[1] = ::boost::initialized_value;
                        break;
                    }

                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    if (!(index & 2))
                    {
                        --result[1];
                    }

                    break;
                }

                case 0x2D:
                {
                    if (3 == index)
                    {
                        result[0] = d_max_0;
                        break;
                    }
                }

                case 0x21:
                {
                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    if (!(index & 2))
                    {
                        --result[1];
                    }

                    break;
                }

                case 0xD2:
                {
                    if (3 == index)
                    {
                        result[1] = d_max_1;
                        break;
                    }

                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    if (!(index & 2))
                    {
                        ++result[1];
                    }

                    break;
                }

                case 0x1E:
                {
                    if (3 == index)
                    {
                        result[0] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x12:
                {
                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    if (!(index & 2))
                    {
                        ++result[1];
                    }

                    break;
                }

                case 0xD1:
                {
                    if (3 == index)
                    {
                        result[1] = d_max_1;
                        break;
                    }

                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    if (!(index & 2))
                    {
                        ++result[1];
                    }

                    break;
                }

                case 0x1D:
                {
                    if (3 == index)
                    {
                        result[0] = d_max_0;
                        break;
                    }
                }

                case 0x11:
                {
                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    if (!(index & 2))
                    {
                        ++result[1];
                    }

                    break;
                }

                case 0xE6:
                {
                    if (5 == index)
                    {
                        result[1] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x26:
                {
                    if (!(index & 1))
                    {
                        --result[1];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 2:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0xE5:
                {
                    if (5 == index)
                    {
                        result[1] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x25:
                {
                    if (!(index & 1))
                    {
                        --result[1];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 2:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    break;
                }

                case 0xE0:
                {
                    if (5 == index)
                    {
                        result[1] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x20:
                {
                    if (!(index & 1))
                    {
                        --result[1];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 2:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    break;
                }

                case 0xD6:
                {
                    if (5 == index)
                    {
                        result[1] = d_max_1;
                        break;
                    }
                }

                case 0x16:
                {
                    if (!(index & 1))
                    {
                        ++result[1];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 2:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0xD5:
                {
                    if (5 == index)
                    {
                        result[1] = d_max_1;
                        break;
                    }
                }

                case 0x15:
                {
                    if (!(index & 1))
                    {
                        ++result[1];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 2:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    break;
                }

                case 0xD0:
                {
                    if (5 == index)
                    {
                        result[1] = d_max_1;
                        break;
                    }
                }

                case 0x10:
                {
                    if (!(index & 1))
                    {
                        ++result[1];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 2:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    break;
                }

                case 0x6E:
                {
                    if (5 == index)
                    {
                        result[0] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x62:
                {
                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 2:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0x5E:
                {
                    if (5 == index)
                    {
                        result[0] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x52:
                {
                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            result[1] = d_max_1;
                            break;
                        }

                        case 2:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x0E:
                {
                    if (5 == index)
                    {
                        result[0] = ::boost::initialized_value;
                        break;
                    }
                }

                case 0x02:
                {
                    if (!(index & 1))
                    {
                        --result[0];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 2:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x6D:
                {
                    if (5 == index)
                    {
                        result[0] = d_max_0;
                        break;
                    }
                }

                case 0x61:
                {
                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 2:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0x5D:
                {
                    if (5 == index)
                    {
                        result[0] = d_max_0;
                        break;
                    }
                }

                case 0x51:
                {
                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            result[1] = d_max_1;
                            break;
                        }

                        case 2:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x0D:
                {
                    if (5 == index)
                    {
                        result[0] = d_max_0;
                        break;
                    }
                }

                case 0x01:
                {
                    if (!(index & 1))
                    {
                        ++result[0];
                    }

                    switch (index & ~1)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 2:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x66:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 1:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0x65:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    break;
                }

                case 0x60:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            result[1] = ::boost::initialized_value;
                            break;
                        }
                    }

                    return result;
                }

                case 0x56:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 1:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            result[1] = d_max_1;
                            break;
                        }

                        case 1:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x55:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            result[1] = d_max_1;
                            break;
                        }

                        case 1:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x50:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            result[1] = d_max_1;
                            break;
                        }

                        case 1:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x06:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 1:
                        {
                            result[0] = ::boost::initialized_value;
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                case 0x05:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            result[0] = d_max_0;
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }

                default:
                {
                    switch (index / 3)
                    {
                        case 0:
                        {
                            --result[0];
                            break;
                        }

                        case 1:
                        {
                            ++result[0];
                            break;
                        }
                    }

                    switch (index % 3)
                    {
                        case 0:
                        {
                            --result[1];
                            break;
                        }

                        case 1:
                        {
                            ++result[1];
                            break;
                        }
                    }

                    break;
                }
            }
        }
        else  // Square vertex.
        {
            ++index;

            Dimension d = ::boost::initialized_value;
            bool is_forward = false;

            for (;;)
            {
                if (
                    !this->_wrap_dimension[d] || (
                        this->_dimension_lengths[d] & 1
                    )
                )
                {
                    Coordinate v_d = vertex[d];

                    if (!is_forward && !v_d)
                    {
                        is_forward = true;
                        continue;
                    }
                    else if (
                        is_forward && (++v_d == this->_dimension_lengths[d])
                    )
                    {
                        is_forward = false;
                        ++d;
                        continue;
                    }
                }

                if (--index)
                {
                    if (is_forward)
                    {
                        ++d;
                    }

                    is_forward = !is_forward;
                }
                else
                {
                    break;
                }
            }

            if (is_forward)
            {
                if (++result[d] == this->_dimension_lengths[d])
                {
                    result[d] = ::boost::initialized_value;
                }
            }
            else if (result[d])
            {
                --result[d];
            }
            else
            {
                result[d] = this->_dimension_lengths[d];
                --result[d];
            }
        }

        return result;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::_get_next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , Coordinate const& distance
        ) const
    {
        if (!this->_is_octagon(vertex) && !(0 == key[0]) && !(0 == key[1]))
        {
            return vertex;
        }

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
                        break;
                    }

                    if (this->_wrap_dimension[d])
                    {
                        if (!(d_len & 1))
                        {
                            result[d] += d_len;
                            result[d] -= distance % d_len;
                            result[d] %= d_len;
                            break;
                        }

                        if (0 == key[d ^ 1])
                        {
                            vertex_descriptor side_v(vertex);

                            side_v[d] = ::boost::initialized_value;

                            if (this->_is_octagon(side_v))
                            {
                                // The vertex on the other side
                                // is also an octagon.
                                result[d] += d_len;
                                result[d] -= distance % d_len;
                                result[d] %= d_len;
                                break;
                            }
                        }
                    }

                    if (result[d] < truncated_distance)
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
                        break;
                    }

                    if (this->_wrap_dimension[d])
                    {
                        if (!(d_len & 1))
                        {
                            result[d] += distance;
                            result[d] %= d_len;
                            break;
                        }

                        if (0 == key[d ^ 1])
                        {
                            vertex_descriptor side_v(vertex);

                            side_v[d] = ::boost::initialized_value;

                            if (this->_is_octagon(side_v))
                            {
                                // The vertex on the other side
                                // is also an octagon.
                                result[d] += distance;
                                result[d] %= d_len;
                                break;
                            }
                        }
                    }

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

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::Dimension
        BOOST_GRAPH_UPSILON_GRID_TYPE::dimensions() const
    {
        return _dimension_count;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline Coordinate const&
        BOOST_GRAPH_UPSILON_GRID_TYPE::length(Dimension const& dimension) const
    {
        return this->_dimension_lengths[dimension];
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_UPSILON_GRID_TYPE::wrapped(
            Dimension const& dimension
        ) const
    {
        return this->_wrap_dimension[dimension];
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , typename vertex_coordinate_trait<type>::type const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(detail::is_valid_upsilon_grid_graph_edge_key(key));
        return this->_get_next(vertex, key, distance);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_UPSILON_GRID_TYPE::vertex_descriptor
        BOOST_GRAPH_UPSILON_GRID_TYPE::previous(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , typename vertex_coordinate_trait<type>::type const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(detail::is_valid_upsilon_grid_graph_edge_key(key));
        typename edge_key_trait<type>::type opposite_key;
        opposite_key[0] = -key[0];
        opposite_key[1] = -key[1];
        return this->_get_next(vertex, opposite_key, distance);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
        num_edge_keys(BOOST_GRAPH_UPSILON_GRID_TYPE const& graph)
    {
        return graph._edge_key_count;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename edge_key_trait<BOOST_GRAPH_UPSILON_GRID_TYPE>::type
        edge_key(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < ::boost::num_edge_keys(graph));
        return detail::get_upsilon_grid_graph_edge_key(index);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_iterator)
      , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_iterator)
    >
        vertices(BOOST_GRAPH_UPSILON_GRID_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::VertexIndexIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertices_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::VertexFunction(&graph)
            )
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::VertexIndexIterator(
                    graph._get_vertex_count()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::VertexFunction(&graph)
            )
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertices_size_type) const&
        num_vertices(BOOST_GRAPH_UPSILON_GRID_TYPE const& graph)
    {
        return graph._get_vertex_count();
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor)
        vertex(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertices_size_type) const& i
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(i < graph._get_vertex_count());
        return graph.vertex_at(i);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_iterator)
      , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_iterator)
    >
        edges(BOOST_GRAPH_UPSILON_GRID_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::EdgeIndexIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edges_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::EdgeFunction(&graph)
            )
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::EdgeIndexIterator(
                    graph._get_edge_count()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::EdgeFunction(&graph)
            )
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edges_size_type)
        num_edges(BOOST_GRAPH_UPSILON_GRID_TYPE const& graph)
    {
        return graph._get_edge_count();
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)
        edge_at(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edges_size_type) const& index
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_edge_count());
        return graph.edge_at(index);
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(out_edge_iterator)
      , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(out_edge_iterator)
    >
        out_edges(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(out_edge_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , true
                )
            )
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(out_edge_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::DegreeIterator(
                    graph._get_neighborhood_size(v) - 1
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , true
                )
            )
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
        out_degree(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighborhood_size(v) - 1;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)
        out_edge_at(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)(
            v
          , graph._get_neighbor_at(v, index)
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(adjacency_iterator)
      , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(adjacency_iterator)
    >
        adjacent_vertices(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& g
        )
    {
        BOOST_ASSERT(g._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(adjacency_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjacencyFunction(
                    v
                  , &g
                )
            )
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(adjacency_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::DegreeIterator(
                    g._get_neighborhood_size(v) - 1
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjacencyFunction(
                    v
                  , &g
                )
            )
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(in_edge_iterator)
      , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(in_edge_iterator)
    >
        in_edges(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(in_edge_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::DegreeIterator(
                    (::std::numeric_limits<
                        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
                    >::min)()
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , false
                )
            )
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(in_edge_iterator)(
                typename BOOST_GRAPH_UPSILON_GRID_TYPE::DegreeIterator(
                    graph._get_neighborhood_size(v) - 1
                )
              , typename BOOST_GRAPH_UPSILON_GRID_TYPE::AdjEdgeFunction(
                    v
                  , &graph
                  , false
                )
            )
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
        in_degree(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighborhood_size(v) - 1;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type)
        degree(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return (graph._get_neighborhood_size(v) - 1) << 1;
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)
        in_edge_at(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)(
            graph._get_neighbor_at(v, index)
          , v
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    ::std::pair<BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor),bool>
        edge(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& u
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(u));
        BOOST_ASSERT(graph._is_valid(v));

        BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(
            vertex_descriptor
        ) const& d_len = graph._dimension_lengths;
        Coordinate const d0 = ::boost::initialized_value;
        bool const u_is_octagon = graph._is_octagon(u);

        // Check for vertices with the same coordinate value in a dimension.
        bool is_orthogonal = false;

        // No self-edges.
        bool is_different = false;

        // Unless both dimensions have even lengths, edge cannot wraparound
        // from origin to farthest vertex, or vice-versa.
        bool is_not_forbidden = false;

        for (
            typename vertex_dimension_trait<
                BOOST_GRAPH_UPSILON_GRID_TYPE
            >::type d = ::boost::initialized_value;
            d < graph._dimension_count;
            ++d
        )
        {
            if (
                graph._wrap_dimension[d] && (
                    (
                        (d0 == u[d]) && (d_len[d] == v[d] + 1)
                    ) || (
                        (d0 == v[d]) && (d_len[d] == u[d] + 1)
                    )
                )
            )
            {
                if (d_len[d] & 1)
                {
                    if (!u_is_octagon)
                    {
                        // Edge cannot wraparound from square.
                        // (Adjacent octagons prevent physical connection.)
                        return ::std::make_pair(
                            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(
                                edge_descriptor
                            )(u, v)
                          , false
                        );
                    }
                }
                else
                {
                    is_not_forbidden = true;
                }

                is_different = true;
            }
            else if ((u[d] + 1 < v[d]) || (v[d] + 1 < u[d]))
            {
                // Vertices are too far away from each other.
                return ::std::make_pair(
                    BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)(u, v)
                  , false
                );
            }
            else
            {
                is_not_forbidden = true;

                if (u[d] == v[d])
                {
                    is_orthogonal = true;
                }
                else
                {
                    is_different = true;
                }
            }
        }

        return ::std::make_pair(
            BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(edge_descriptor)(u, v)
          , is_different && is_not_forbidden && (
                is_orthogonal || (u_is_octagon && graph._is_octagon(v))
            )
        );
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline typename ::boost::property_map<
        BOOST_GRAPH_UPSILON_GRID_TYPE
      , vertex_index_t
    >::type
        get(vertex_index_t, BOOST_GRAPH_UPSILON_GRID_TYPE const& graph)
    {
        return typename ::boost::property_map<
            BOOST_GRAPH_UPSILON_GRID_TYPE
          , vertex_index_t
        >::type(BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE(true)(&graph));
    }

    template <BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertices_size_type)
        get(
            vertex_index_t
          , BOOST_GRAPH_UPSILON_GRID_TYPE const& graph
          , BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM(vertex_descriptor) const& v
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._index_of(v);
    }
}  // namespace boost

#undef BOOST_GRAPH_UPSILON_GRID_F_TYPE_MEM
#undef BOOST_GRAPH_UPSILON_GRID_TRAITS_MEM
#undef BOOST_GRAPH_UPSILON_GRID_F_TYPE
#undef BOOST_GRAPH_UPSILON_GRID_FRIEND_TEMPLATE_PARAMS
#undef BOOST_GRAPH_UPSILON_GRID_TYPE
#undef BOOST_GRAPH_UPSILON_GRID_IDX_FUNC_TYPE
#undef BOOST_GRAPH_UPSILON_GRID_TEMPLATE_PARAMS

#endif  // BOOST_GRAPH_UPSILON_GRID_GRAPH_HPP

