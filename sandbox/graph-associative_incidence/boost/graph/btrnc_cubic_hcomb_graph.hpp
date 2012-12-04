// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_GRAPH_HPP
#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_GRAPH_HPP

#include <boost/graph/btrnc_cubic_hcomb_graph_fwd.hpp>

#include <iterator>
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

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS \
typename Coordinate, typename VertexIndex, typename EdgeIndex

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(b) \
bitruncated_cubic_honeycomb_graph_idx_func<Coordinate,VertexIndex,EdgeIndex,b>

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE \
bitruncated_cubic_honeycomb_graph<Coordinate,VertexIndex,EdgeIndex>

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS \
typename C, typename V, typename E

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T \
bitruncated_cubic_honeycomb_graph<C,V,E>

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(mem) \
typename graph_traits<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE>::mem

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(mem) \
typename graph_traits<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T>::mem

#define BOOST_GRAPH_BTRNC_CUBIC_HCOMB_EDGE_KEY_TYPE \
::std::tr1::array< ::boost::int8_t,3>

namespace boost { namespace detail {

    inline bool
        is_valid_bitruncated_cubic_honeycomb_graph_edge_key(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_EDGE_KEY_TYPE const& key
        )
    {
        switch (key[0])
        {
            case 0:
            {
                return (
                    (
                        (0 == key[1]) && ((-2 == key[2]) || (2 == key[2]))
                    ) || (
                        (0 == key[2]) && ((-2 == key[1]) || (2 == key[1]))
                    )
                );
            }

            case -1:
            case 1:
            {
                return (
                    (
                        (-1 == key[1]) || (1 == key[1])
                    ) && (
                        (-1 == key[2]) || (1 == key[2])
                    )
                );
            }

            case -2:
            case 2:
            {
                return (0 == key[1]) && (0 == key[2]);
            }

            default:
            {
                return false;
            }
        }
    }

    template <typename DegreeSize>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_EDGE_KEY_TYPE
        get_bitruncated_cubic_honeycomb_graph_edge_key(DegreeSize const& index)
    {
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_EDGE_KEY_TYPE result;

        switch (index)
        {
            case 0:
            {
                result = {{-1, -1, -1}};
                break;
            }

            case 1:
            {
                result = {{1, -1, -1}};
                break;
            }

            case 2:
            {
                result = {{-1, 1, -1}};
                break;
            }

            case 3:
            {
                result = {{1, 1, -1}};
                break;
            }

            case 4:
            {
                result = {{-1, -1, 1}};
                break;
            }

            case 5:
            {
                result = {{1, -1, 1}};
                break;
            }

            case 6:
            {
                result = {{-1, 1, 1}};
                break;
            }

            case 7:
            {
                result = {{1, 1, 1}};
                break;
            }

            case 8:
            {
                result = {{-2, 0, 0}};
                break;
            }

            case 9:
            {
                result = {{2, 0, 0}};
                break;
            }

            case 10:
            {
                result = {{0, -2, 0}};
                break;
            }

            case 11:
            {
                result = {{0, 2, 0}};
                break;
            }

            case 12:
            {
                result = {{0, 0, -2}};
                break;
            }

            case 13:
            {
                result = {{0, 0, 2}};
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

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS, bool IsVertex>
    class bitruncated_cubic_honeycomb_graph_idx_func
    {
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const* _graph;

     public:
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                        vertices_size_type
                    )
                  , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edges_size_type)
                >::type
                result_type;
        typedef typename ::boost::mpl::if_c<
                    IsVertex
                  , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_descriptor)
                  , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)
                >::type const&
                argument_type;

        explicit bitruncated_cubic_honeycomb_graph_idx_func(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const* graph
        );

        result_type operator()(argument_type key) const;
    };

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS, bool IsVertex>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(
        IsVertex
    )::bitruncated_cubic_honeycomb_graph_idx_func(
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const* graph
    ) : _graph(graph)
    {
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS, bool IsVertex>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(
        IsVertex
    )::result_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(IsVertex)::operator()(
            argument_type key
        ) const
    {
        return this->_graph->_index_of(key);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE,vertex_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(true)
                  , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    struct property_map<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE,edge_index_t>
    {
        typedef ::boost::function_property_map<
                    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(false)
                  , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)
                >
                type;
        typedef type
                const_type;
    };

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    struct vertex_dimension_trait<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE>
    {
        typedef typename ::std::tr1::array<Coordinate,2>::value_type type;
    };

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    struct vertex_coordinate_trait<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE>
    {
        typedef Coordinate type;
    };

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    struct edge_key_trait<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE>
    {
        typedef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_EDGE_KEY_TYPE type;
    };

    template <
        typename Coordinate = ::std::size_t
      , typename VertexIndex = void
      , typename EdgeIndex = void
    >
    class bitruncated_cubic_honeycomb_graph
    {
        typedef ::std::tr1::array<bool,3> WraparoundArray;

     public:
        typedef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE type;

        // descriptors
        typedef ::std::tr1::array<Coordinate,3>
                vertex_descriptor;
        typedef ::std::pair<vertex_descriptor,vertex_descriptor>
                edge_descriptor;

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
        typedef typename vertex_descriptor::size_type
                degree_size_type;

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
            bool _is_out;

         public:
            typedef edge_descriptor result_type;
            typedef vertex_descriptor const& argument_type;

            AdjEdgeFunction();

            AdjEdgeFunction(vertex_descriptor const& vertex, bool is_out);

            result_type operator()(argument_type neighbor) const;
        };

     public:
        // iterators
        typedef ::boost::transform_iterator<VertexFunction,VertexIndexIterator>
                vertex_iterator;
        typedef ::boost::transform_iterator<EdgeFunction,EdgeIndexIterator>
                edge_iterator;

        class adjacency_iterator
        {
            vertex_descriptor _vertex;
            bitruncated_cubic_honeycomb_graph const* _graph;
            degree_size_type _index;
            vertex_descriptor _neighbor;

         public:
            typedef ::std::bidirectional_iterator_tag iterator_category;
            typedef vertex_descriptor value_type;
            typedef vertex_descriptor const& reference;
            typedef vertex_descriptor const* pointer;
            typedef ::std::ptrdiff_t difference_type;

            explicit adjacency_iterator(bool is_forward = true);

            adjacency_iterator(
                vertex_descriptor const& vertex
              , bitruncated_cubic_honeycomb_graph const* graph
              , bool is_forward = true
            );

            reference operator*() const;

            adjacency_iterator& operator++();

            adjacency_iterator operator++(int);

            adjacency_iterator& operator--();

            adjacency_iterator operator--(int);

            inline friend bool
                operator==(
                    adjacency_iterator const& lhs
                  , adjacency_iterator const& rhs
                )
            {
                return lhs._index == rhs._index;
            }

            inline friend bool
                operator!=(
                    adjacency_iterator const& lhs
                  , adjacency_iterator const& rhs
                )
            {
                return lhs._index != rhs._index;
            }
        };

        typedef ::boost::transform_iterator<AdjEdgeFunction,adjacency_iterator>
                out_edge_iterator;
        typedef ::boost::transform_iterator<AdjEdgeFunction,adjacency_iterator>
                in_edge_iterator;

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
        BOOST_STATIC_CONSTANT(degree_size_type, _dimension_count = 3);
        BOOST_STATIC_CONSTANT(degree_size_type, _edge_key_count = 14);

        vertex_descriptor  _dimension_lengths;
        vertex_descriptor  _even_coord_counts;
        vertex_descriptor  _odd_coord_counts;
        WraparoundArray    _wrap_dimension;
        vertices_size_type _even_coord_vertex_count;
        vertices_size_type _odd_coord_vertex_count;

        bitruncated_cubic_honeycomb_graph();

     public:
        explicit bitruncated_cubic_honeycomb_graph(
            vertex_descriptor const& dimension_lengths
          , bool wrap_all_dimensions = false
        );

        bitruncated_cubic_honeycomb_graph(
            vertex_descriptor const& dimension_lengths
          , WraparoundArray const& wraparound_dimension
        );

        template <typename DimensionIterator>
        bitruncated_cubic_honeycomb_graph(
            DimensionIterator dimension_lengths_itr
          , DimensionIterator dimension_lengths_end
          , bool wrap_all_dimensions = false
        );

        template <typename DimensionIterator, typename WraparoundIterator>
        bitruncated_cubic_honeycomb_graph(
            DimensionIterator dimension_lengths_itr
          , DimensionIterator dimension_lengths_end
          , WraparoundIterator wraparound_dimension_itr
          , WraparoundIterator wraparound_dimension_end
        );

        static vertex_descriptor null_vertex();

     private:
        void _precalculate();

        vertices_size_type _get_vertex_count() const;

        bool _is_valid(vertex_descriptor const& vertex) const;

        vertices_size_type _index_of(vertex_descriptor const& vertex) const;

        vertex_descriptor vertex_at(vertices_size_type index) const;

        edges_size_type const& _get_edge_count() const;

        edges_size_type _index_of(edge_descriptor const& vertex) const;

        edge_descriptor edge_at(edges_size_type const& index) const;

        degree_size_type
            _get_neighbor_count(vertex_descriptor const& vertex) const;

#if 0
        vertex_descriptor
            _get_neighbor_at(
                vertex_descriptor const& vertex
              , degree_size_type index
            ) const;
#endif

        vertex_descriptor
            _get_next(
                vertex_descriptor const& vertex
              , typename edge_key_trait<type>::type const& key
              , Coordinate const& distance = (Coordinate() + 1)
            ) const;

     public:
        // =========
        // GridGraph
        // =========
        degree_size_type dimensions() const;

        Coordinate const& length(degree_size_type const& dimension) const;

        bool wrapped(degree_size_type const& dimension) const;

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
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(degree_size_type)
            num_edge_keys(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph);

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend typename edge_key_trait<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T>::type
            edge_key(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    degree_size_type
                ) const& index
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        // ===============
        // VertexListGraph
        // ===============
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(vertex_iterator)
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(vertex_iterator)
        >
            vertices(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph);

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(vertices_size_type)
            num_vertices(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph);

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(vertex_descriptor)
            vertex(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertices_size_type
                ) const& index
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        // =============
        // EdgeListGraph
        // =============
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(edge_iterator)
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(edge_iterator)
        >
            edges(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph);

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
            edges_size_type
        ) const&
            num_edges(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph);

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(edge_descriptor)
            edge_at(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    edges_size_type
                ) const& index
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        // ==============
        // IncidenceGraph
        // ==============
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(out_edge_iterator)
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(out_edge_iterator)
        >
            out_edges(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(degree_size_type)
            out_degree(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

#if 0
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(edge_descriptor)
            out_edge_at(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    degree_size_type
                ) const& index
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );
#endif

        // ==============
        // AdjacencyGraph
        // ==============
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(adjacency_iterator)
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(adjacency_iterator)
        >
            adjacent_vertices(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        // ==================
        // BidirectionalGraph
        // ==================
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(in_edge_iterator)
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(in_edge_iterator)
        >
            in_edges(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(degree_size_type)
            in_degree(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(degree_size_type)
            degree(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

#if 0
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(edge_descriptor)
            in_edge_at(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    degree_size_type
                ) const& index
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );
#endif

        // ===============
        // AdjacencyMatrix
        // ===============
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend ::std::pair<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(edge_descriptor)
          , bool
        >
            edge(
                BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& u
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        // =============
        // PropertyGraph
        // =============
        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend typename ::boost::property_map<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T
          , vertex_index_t
        >::type
            get(
                vertex_index_t
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
            );

        template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS>
        friend BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(vertices_size_type)
            get(
                vertex_index_t
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_T const& graph
              , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM(
                    vertex_descriptor
                ) const& v
            );

        template <
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS
          , bool IsVertex
        >
        friend class bitruncated_cubic_honeycomb_graph_idx_func;
    };

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction::AdjEdgeFunction()
      : _vertex(), _is_out(false)
    {
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction::AdjEdgeFunction(
        vertex_descriptor const& vertex
      , bool is_out
    ) : _vertex(vertex), _is_out(is_out)
    {
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction::result_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction::operator()(
            argument_type neighbor
        ) const
    {
        return (
            this->_is_out
          ? edge_descriptor(this->_vertex, neighbor)
          : edge_descriptor(neighbor, this->_vertex)
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::adjacency_iterator(
        bool is_forward
    ) : _vertex(bitruncated_cubic_honeycomb_graph::null_vertex())
      , _graph(0)
      , _index(
            is_forward
          ? bitruncated_cubic_honeycomb_graph::_edge_key_count
          : (::std::numeric_limits<degree_size_type>::max)()
        )
      , _neighbor(bitruncated_cubic_honeycomb_graph::null_vertex())
    {
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::adjacency_iterator(
        vertex_descriptor const& vertex
      , bitruncated_cubic_honeycomb_graph const* graph
      , bool is_forward
    ) : _vertex(vertex)
      , _graph(graph)
      , _index(
            is_forward
          ? ::boost::initialized_value
          : (bitruncated_cubic_honeycomb_graph::_edge_key_count - 1)
        )
      , _neighbor(
            graph->_get_next(
                vertex
              , detail::get_bitruncated_cubic_honeycomb_graph_edge_key(_index)
            )
        )
    {
        if (is_forward)
        {
            while (
                (this->_neighbor == vertex) && (
                    ++this->_index
                  < bitruncated_cubic_honeycomb_graph::_edge_key_count
                )
            )
            {
                this->_neighbor = graph->_get_next(
                    vertex
                  , detail::get_bitruncated_cubic_honeycomb_graph_edge_key(
                        this->_index
                    )
                );
            }
        }
        else
        {
            while (this->_neighbor == vertex)
            {
                if (this->_index)
                {
                    this->_neighbor = graph->_get_next(
                        vertex
                      , detail::get_bitruncated_cubic_honeycomb_graph_edge_key(
                            --this->_index
                        )
                    );
                }
                else
                {
                    this->_index = (
                        ::std::numeric_limits<degree_size_type>::max
                    )();
                    break;
                }
            }
        }
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::reference
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::operator*(
        ) const
    {
        return this->_neighbor;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator&
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::operator++()
    {
        do
        {
            if (
                ++this->_index
              < bitruncated_cubic_honeycomb_graph::_edge_key_count
            )
            {
                this->_neighbor = this->_graph->_get_next(
                    this->_vertex
                  , detail::get_bitruncated_cubic_honeycomb_graph_edge_key(
                        this->_index
                    )
                );
            }
            else
            {
                break;
            }
        }
        while (this->_neighbor == this->_vertex);

        return *this;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::operator++(int)
    {
        adjacency_iterator result(*this);
        ++(*this);
        return result;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator&
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::operator--()
    {
        do
        {
            if (this->_index)
            {
                this->_neighbor = this->_graph->_get_next(
                    this->_vertex
                  , detail::get_bitruncated_cubic_honeycomb_graph_edge_key(
                        --this->_index
                    )
                );
            }
            else
            {
                this->_index = (
                    ::std::numeric_limits<degree_size_type>::max
                )();
                break;
            }
        }
        while (this->_neighbor == this->_vertex);

        return *this;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator::operator--(int)
    {
        adjacency_iterator result(*this);
        --(*this);
        return result;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::null_vertex()
    {
        vertex_descriptor result;
        ::std::fill(
            result.begin()
          , result.end()
          , (::std::numeric_limits<Coordinate>::max)()
        );
        return result;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::bitruncated_cubic_honeycomb_graph(
        vertex_descriptor const& dimension_lengths
      , bool wrap_all_dimensions
    ) : _dimension_lengths(dimension_lengths)
      , _even_coord_counts()
      , _odd_coord_counts()
      , _wrap_dimension()
      , _even_coord_vertex_count(::boost::initialized_value)
      , _odd_coord_vertex_count(::boost::initialized_value)
    {
        ::std::fill(
            this->_wrap_dimension.begin()
          , this->_wrap_dimension.end()
          , wrap_all_dimensions
        );
        this->_precalculate();
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::bitruncated_cubic_honeycomb_graph(
        vertex_descriptor const& dimension_lengths
      , WraparoundArray const& wraparound_dimension
    ) : _dimension_lengths(dimension_lengths)
      , _even_coord_counts()
      , _odd_coord_counts()
      , _wrap_dimension(wraparound_dimension)
      , _even_coord_vertex_count(::boost::initialized_value)
      , _odd_coord_vertex_count(::boost::initialized_value)
    {
        this->_precalculate();
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    template <typename DimensionIterator>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::bitruncated_cubic_honeycomb_graph(
        DimensionIterator dimension_lengths_itr
      , DimensionIterator dimension_lengths_end
      , bool wrap_all_dimensions
    ) : _dimension_lengths()
      , _even_coord_counts()
      , _odd_coord_counts()
      , _wrap_dimension()
      , _even_coord_vertex_count(::boost::initialized_value)
      , _odd_coord_vertex_count(::boost::initialized_value)
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

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    template <typename DimensionIterator, typename WraparoundIterator>
    BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::bitruncated_cubic_honeycomb_graph(
        DimensionIterator dimension_lengths_itr
      , DimensionIterator dimension_lengths_end
      , WraparoundIterator wraparound_dimension_itr
      , WraparoundIterator wraparound_dimension_end
    ) : _dimension_lengths()
      , _even_coord_counts()
      , _odd_coord_counts()
      , _wrap_dimension()
      , _even_coord_vertex_count(::boost::initialized_value)
      , _odd_coord_vertex_count(::boost::initialized_value)
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

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    void BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_precalculate()
    {
        for (
            degree_size_type d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            BOOST_ASSERT(
                (4 < this->_dimension_lengths[d]) || (
                    !this->_wrap_dimension[d] && (
                        1 < this->_dimension_lengths[d]
                    )
                )
            );

            this->_even_coord_counts[d] = this->_dimension_lengths[d];
            (++this->_even_coord_counts[d]) >>= 1;
            this->_odd_coord_counts[d] = this->_even_coord_counts[d] - (
                this->_dimension_lengths[d] & 1
            );
        }

        vertices_size_type start = ::boost::initialized_value;

        this->_even_coord_vertex_count = ::std::accumulate(
            this->_even_coord_counts.begin()
          , this->_even_coord_counts.end()
          , ++start
          , ::std::multiplies<vertices_size_type>()
        );
        this->_odd_coord_vertex_count = ::std::accumulate(
            this->_odd_coord_counts.begin()
          , this->_odd_coord_counts.end()
          , start
          , ::std::multiplies<vertices_size_type>()
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertices_size_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_get_vertex_count() const
    {
        return this->_even_coord_vertex_count + this->_odd_coord_vertex_count;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    bool
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_is_valid(
            vertex_descriptor const& vertex
        ) const
    {
        for (
            degree_size_type d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            if (vertex[d] < this->_dimension_lengths[d])
            {
                if (d && !((vertex[d] & 1) == (vertex[0] & 1)))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertices_size_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_index_of(
            vertex_descriptor const& vertex
        ) const
    {
        vertices_size_type result = ::boost::initialized_value;
        vertices_size_type factor = ::boost::initialized_value;

        ++factor;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            if (vertex[d])
            {
                result += (vertex[d] >> 1) * factor;
            }

            factor *= (
                vertex[d] & 1
            ) ? this->_odd_coord_counts[d] : this->_even_coord_counts[d];
        }

        if (vertex[0] & 1)
        {
            return result + this->_even_coord_vertex_count;
        }
        else
        {
            return result;
        }
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_at(
            vertices_size_type index
        ) const
    {
        vertex_descriptor result;
        vertices_size_type divisor = ::boost::initialized_value;

        ++divisor;

        if (index < this->_even_coord_vertex_count)
        {
            for (
                degree_size_type d = ::boost::initialized_value;
                d < this->_dimension_count;
                ++d
            )
            {
                result[d] = (
                    (index / divisor) % this->_even_coord_counts[d]
                ) << 1;
                divisor *= this->_even_coord_counts[d];
            }
        }
        else
        {
            index -= this->_even_coord_vertex_count;

            for (
                degree_size_type d = ::boost::initialized_value;
                d < this->_dimension_count;
                ++d
            )
            {
                result[d] = (
                    (index / divisor) % this->_odd_coord_counts[d]
                ) << 1;
                ++result[d];
                divisor *= this->_odd_coord_counts[d];
            }
        }

        return result;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::edges_size_type const&
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_get_edge_count() const
    {
        // TODO
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::edges_size_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_index_of(
            edge_descriptor const& edge
        ) const
    {
        // TODO
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::edge_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::edge_at(
            edges_size_type const& index
        ) const
    {
        // TODO
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::degree_size_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_get_neighbor_count(
            vertex_descriptor const& vertex
        ) const
    {
        degree_size_type result = ::boost::initialized_value;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < this->_edge_key_count;
            ++d
        )
        {
            if (
                vertex != this->_get_next(
                    vertex
                  , detail::get_bitruncated_cubic_honeycomb_graph_edge_key(d)
                )
            )
            {
                ++result;
            }
        }

        return result;
    }

#if 0
    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_get_neighbor_at(
            vertex_descriptor const& vertex
          , degree_size_type index
        ) const
    {
    }
#endif

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_get_next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , Coordinate const& distance
        ) const
    {
        vertex_descriptor result(vertex);
        Coordinate truncated_distance = distance;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            Coordinate const d_len = this->_dimension_lengths[d];

            switch (key[d])
            {
                case -2:
                {
                    if (!(result[d] < (distance << 1)))
                    {
                        result[d] -= distance << 1;
                    }
                    else if (
                        this->_wrap_dimension[d] && (
                            !(result[d] & 1) || !(d_len & 1)
                        )
                    )
                    {
                        Coordinate const d_len_next_even = d_len + (d_len & 1);

                        result[d] += d_len_next_even;
                        result[d] -= (distance << 1) % d_len_next_even;
                        result[d] %= d_len_next_even;
                    }
                    else if (result[d] < (truncated_distance << 1))
                    {
                        if (!(truncated_distance = result[d] >> 1))
                        {
                            return vertex;
                        }
                    }

                    break;
                }

                case -1:
                {
                    if (!(result[d] < distance))
                    {
                        result[d] -= distance;
                    }
                    else if (this->_wrap_dimension[d] && !(d_len & 1))
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
                    else if (d_len & 1)
                    {
                        Coordinate const truncated = (d_len & ~1) - result[d];

                        if (truncated)
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

                case 2:
                {
                    if (result[d] + (distance << 1) < d_len)
                    {
                        result[d] += distance << 1;
                    }
                    else if (
                        this->_wrap_dimension[d] && (
                            !(result[d] & 1) || !(d_len & 1)
                        )
                    )
                    {
                        result[d] += distance << 1;
                        result[d] %= d_len + (d_len & 1);
                    }
                    else
                    {
                        Coordinate truncated = (d_len & 1) ? (
                            d_len - result[d] - (result[d] & 1)
                        ) : (
                            d_len - (result[d] | 1)
                        );

                        if (--truncated)
                        {
                            if (truncated < (truncated_distance << 1))
                            {
                                truncated_distance = truncated >> 1;
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

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::degree_size_type
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::dimensions() const
    {
        return this->_dimension_count;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline Coordinate const&
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::length(
            degree_size_type const& dimension
        ) const
    {
        return this->_dimension_lengths[dimension];
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline bool
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::wrapped(
            degree_size_type const& dimension
        ) const
    {
        return this->_wrap_dimension[dimension];
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::next(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , typename vertex_coordinate_trait<type>::type const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(
            detail::is_valid_bitruncated_cubic_honeycomb_graph_edge_key(key)
        );
        return this->_get_next(vertex, key, distance);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::vertex_descriptor
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::previous(
            vertex_descriptor const& vertex
          , typename edge_key_trait<type>::type const& key
          , typename vertex_coordinate_trait<type>::type const& distance
        ) const
    {
        BOOST_ASSERT(this->_is_valid(vertex));
        BOOST_ASSERT(
            detail::is_valid_bitruncated_cubic_honeycomb_graph_edge_key(key)
        );
        typename edge_key_trait<type>::type opposite_key;

        for (
            degree_size_type d = ::boost::initialized_value;
            d < this->_dimension_count;
            ++d
        )
        {
            opposite_key[d] = -key[d];
        }

        return this->_get_next(vertex, opposite_key, distance);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(degree_size_type)
        num_edge_keys(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph)
    {
        return BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::_edge_key_count;
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename edge_key_trait<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE>::type
        edge_key(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                degree_size_type
            ) const& index
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < ::boost::num_edge_keys(graph));
        return detail::get_bitruncated_cubic_honeycomb_graph_edge_key(index);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_iterator)
      , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_iterator)
    >
        vertices(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_iterator)(
              typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::VertexIndexIterator(
                (
                    ::std::numeric_limits<
                        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                            vertices_size_type
                        )
                    >::min
                )()
              )
            , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::VertexFunction(
                &graph
              )
            )
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_iterator)(
              typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::VertexIndexIterator(
                graph._get_vertex_count()
              )
            , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::VertexFunction(
                &graph
              )
            )
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertices_size_type)
        num_vertices(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph)
    {
        return graph._get_vertex_count();
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertex_descriptor)
        vertex(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertices_size_type
            ) const& index
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_vertex_count());
        return graph.vertex_at(index);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_iterator)
      , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_iterator)
    >
        edges(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph)
    {
        return ::std::make_pair(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::EdgeIndexIterator(
                    (
                        ::std::numeric_limits<
                            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                                edges_size_type
                            )
                        >::min
                    )()
                )
              , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::EdgeFunction(
                    &graph
                )
            )
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_iterator)(
                typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::EdgeIndexIterator(
                    graph._get_edge_count()
                )
              , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::EdgeFunction(
                    &graph
                )
            )
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edges_size_type)
        num_edges(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph)
    {
        return graph._get_edge_count();
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)
        edge_at(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                edges_size_type
            ) const& index
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(index < graph._get_edge_count());
        return graph.edge_at(index);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(out_edge_iterator)
      , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(out_edge_iterator)
    >
        out_edges(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(out_edge_iterator)(
              typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator(
                v
              , &graph
              )
            , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction(
                v
              , true
              )
            )
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(out_edge_iterator)(
              typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator()
            , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction(
                v
              , true
              )
            )
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(degree_size_type)
        out_degree(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighbor_count(v);
    }

#if 0
    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)
        out_edge_at(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                degree_size_type
            ) const& index
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)(
            v
          , graph._get_neighbor_at(v, index)
        );
    }
#endif

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(adjacency_iterator)
      , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(adjacency_iterator)
    >
        adjacent_vertices(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(adjacency_iterator)(
                v
              , &graph
            )
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(adjacency_iterator)()
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline ::std::pair<
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(in_edge_iterator)
      , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(in_edge_iterator)
    >
        in_edges(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return ::std::make_pair(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(in_edge_iterator)(
              typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator(
                v
              , &graph
              )
            , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction(
                v
              , false
              )
            )
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(in_edge_iterator)(
              typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::adjacency_iterator()
            , typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::AdjEdgeFunction(
                v
              , false
              )
            )
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(degree_size_type)
        in_degree(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighbor_count(v);
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(degree_size_type)
        degree(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._get_neighbor_count(v) << 1;
    }

#if 0
    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)
        in_edge_at(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                degree_size_type
            ) const& index
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)(
            graph._get_neighbor_at(v, index)
          , v
        );
    }
#endif

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    ::std::pair<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor),bool>
        edge(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& u
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
        )
    {
        BOOST_ASSERT(graph._is_valid(u));
        BOOST_ASSERT(graph._is_valid(v));

        typename edge_key_trait<BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE>::type key;

        for (
            typename BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE::degree_size_type d = (
                ::boost::initialized_value
            );
            d < graph._dimension_count;
            ++d
        )
        {
            if (graph._wrap_dimension[d])
            {
                Coordinate const d_len = graph._dimension_lengths[d];

                if (d_len & 1)
                {
                    if (!u[d] && (v[d] + 1 == d_len))
                    {
                        key[d] = -2;
                        continue;
                    }
                    else if (!v[d] && (u[d] + 1 == d_len))
                    {
                        key[d] = 2;
                        continue;
                    }
                }
                else if (v[d] + 1 == d_len)
                {
                    switch (u[d])
                    {
                        case 0:
                        {
                            key[d] = -1;
                            continue;
                        }

                        case 1:
                        {
                            key[d] = -2;
                            continue;
                        }
                    }
                }
                else if (!u[d] && (v[d] + 2 == d_len))
                {
                    key[d] = -2;
                    continue;
                }
                else if (u[d] + 1 == d_len)
                {
                    switch (v[d])
                    {
                        case 0:
                        {
                            key[d] = 1;
                            continue;
                        }

                        case 1:
                        {
                            key[d] = 2;
                            continue;
                        }
                    }
                }
                else if (!v[d] && (u[d] + 2 == d_len))
                {
                    key[d] = 2;
                    continue;
                }
            }

            key[d] = (
                u[d] < v[d]
            ) ? (
                ::boost::int8_t(v[d] - u[d])
            ) : (
                v[d] < u[d]
            ) ? (
                -::boost::int8_t(u[d] - v[d])
            ) : 0;
        }

        return ::std::make_pair(
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(edge_descriptor)(u, v)
          , detail::is_valid_bitruncated_cubic_honeycomb_graph_edge_key(
                key
            ) && (graph._get_next(u, key) == v)
        );
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline typename ::boost::property_map<
        BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE
      , vertex_index_t
    >::type
        get(vertex_index_t, BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph)
    {
        return typename ::boost::property_map<
            BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE
          , vertex_index_t
        >::type(BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE(true)(&graph));
    }

    template <BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS>
    inline BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(vertices_size_type)
        get(
            vertex_index_t
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE const& graph
          , BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM(
                vertex_descriptor
            ) const& v
        )
    {
        BOOST_ASSERT(graph._is_valid(v));
        return graph._index_of(v);
    }
}  // namespace boost

#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_EDGE_KEY_TYPE
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE_MEM
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TRAITS_MEM
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_F_TYPE
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_FRIEND_TEMPLATE_PARAMS
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TYPE
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_IDX_FUNC_TYPE
#undef BOOST_GRAPH_BTRNC_CUBIC_HCOMB_TEMPLATE_PARAMS

#endif  // BOOST_GRAPH_BTRNC_CUBIC_HCOMB_GRAPH_HPP

