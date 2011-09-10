// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_HPP
#define BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_HPP

#include <numeric>
#include <functional>
#include <vector>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/static_assert.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/functional/value_factory.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/detail/intrusive_layout_params.hpp>
#include <boost/graph/keywords/dimensions.hpp>
#include <boost/graph/keywords/dimension_count.hpp>
#include <boost/graph/keywords/edge_function.hpp>
#include <boost/graph/keywords/is_zeta.hpp>
#include <boost/graph/keywords/origin.hpp>
#include <boost/graph/keywords/point_factory.hpp>
#include <boost/graph/keywords/position_map.hpp>
#include <boost/graph/keywords/scale.hpp>
#include <boost/graph/keywords/vertex_iterator.hpp>
#include <boost/graph/keywords/wraparound_policy.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/detail/index_predicate.hpp>
#include <boost/detail/make_value_factory.hpp>
#include <boost/graph/detail/default_scale.hpp>
#include <boost/graph/detail/default_origin.hpp>

#if BOOST_PP_LESS(10, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_TAKES_ALL_PARAMS
#elif BOOST_PP_LESS(4, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_TAKES_5_PARAMS
#endif

namespace boost {
  namespace detail {

    template <
        typename PositionIndexMap
      , typename Dimensions
      , typename Scale
      , typename DimensionCount
    >
    ::std::size_t
        count_orthogonal_grid_layout_vertices_impl(
            PositionIndexMap position_index
          , Dimensions const& dimensions
          , Scale const& scale
          , DimensionCount const&
        )
    {
        ::std::size_t const dim_count = DimensionCount::value;
        BOOST_STATIC_ASSERT((1 < dim_count));

        ::boost::array< ::std::size_t,dim_count> size;

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            ::std::size_t const dim = position_index[dim_index];

            size[dim] = static_cast< ::std::size_t>(
                dimensions[dim] / scale[dim]
            );
        }

        return ::std::accumulate(
            size.begin()
          , size.end()
          , 1
          , ::std::multiplies< ::std::size_t>()
        );
    }

    template <
        typename VertexIterator
      , typename EdgeAdder
      , typename PositionMap
      , typename PositionIndexMap
      , typename Dimensions
      , typename Scale
      , typename Point
      , typename DimensionCount
      , typename PointFactory
      , typename WraparoundPolicy
    >
    void
        set_orthogonal_grid_layout_impl(
            VertexIterator v_itr
          , EdgeAdder edge_adder
          , bool is_zeta
          , PositionMap position
          , PositionIndexMap position_index
          , Dimensions const& dimensions
          , Scale const& scale
          , Point const& origin
          , DimensionCount const&
          , PointFactory point_factory
          , WraparoundPolicy const& wraparound_policy
        )
    {
        typedef typename ::boost::iterator_value<VertexIterator>::type Vertex;
        ::std::size_t const dim_count = DimensionCount::value;
        BOOST_STATIC_ASSERT((1 < dim_count));
        typedef ::boost::multi_array<Vertex,dim_count> VertexArray;
        typedef typename VertexArray::index VAI;
        typedef ::boost::array<VAI,dim_count> Index;

        Index size;

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            ::std::size_t const dim = position_index[dim_index];

            size[dim] = static_cast< ::std::size_t>(
                dimensions[dim] / scale[dim]
            );
        }

        VertexArray vertex_array(size);
        ::std::vector<Index> indices(
            ::std::accumulate(
                size.begin()
              , size.end()
              , 1
              , ::std::multiplies<VAI>()
            )
        );
        Index index;
        typename ::std::vector<Index>::iterator i_itr, i_end = indices.end();

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            index[position_index[dim_index]] = 0;
        }

        for (i_itr = indices.begin(); i_itr != i_end; ++i_itr, ++v_itr)
        {
            Point point = point_factory();
            ::std::size_t dim_index = 0;

            while (dim_index < dim_count)
            {
                ::std::size_t const dim = position_index[dim_index];

                point[dim] = scale[dim] * index[dim] + origin[dim];
                ++dim_index;
            }

            put(position, vertex_array(*i_itr = index) = *v_itr, point);

            for (
                ++index[position_index[--dim_index]];
                dim_index && (
                    index[position_index[dim_index]]
                 == size[position_index[dim_index]]
                );
                ++index[position_index[--dim_index]]
            )
            {
                index[position_index[dim_index]] = 0;
            }
        }

        if (is_zeta)
        {
            ::std::size_t neighbor_count = 1;

            for (::std::size_t dim = 0; dim < dim_count; ++dim)
            {
                neighbor_count *= 3;
            }

            neighbor_count >>= 1;

            for (i_itr = indices.begin(); i_itr != i_end; ++i_itr)
            {
                for (::std::size_t neighbor_index = neighbor_count;;)
                {
                    bool can_add_edge = true, is_not_loop_edge = false;
                    std::size_t neighbor_mod = neighbor_index;

                    index = *i_itr;

                    for (
                        ::std::size_t dim_index = 0;
                        dim_index < dim_count;
                        ++dim_index
                    )
                    {
                        ::std::size_t const dim = position_index[dim_index];

                        switch (neighbor_mod % 3)
                        {
                            case 0:
                            {
                                if (index[dim])
                                {
                                    --index[dim];
                                    is_not_loop_edge = true;
                                }
                                else if (wraparound_policy[dim])
                                {
                                    index[dim] = size[dim] - 1;
                                    is_not_loop_edge = true;
                                }
                                else
                                {
                                    can_add_edge = false;
                                }

                                break;
                            }

                            case 2:
                            {
                                if (++index[dim] == size[dim])
                                {
                                    if (wraparound_policy[dim])
                                    {
                                        index[dim] = 0;
                                        is_not_loop_edge = true;
                                    }
                                    else
                                    {
                                        can_add_edge = false;
                                    }
                                }
                                else
                                {
                                    is_not_loop_edge = true;
                                }

                                break;
                            }
                        }

                        neighbor_mod /= 3;
                    }

                    if (can_add_edge && is_not_loop_edge)
                    {
                        edge_adder(vertex_array(*i_itr), vertex_array(index));
                    }

                    if (neighbor_index)
                    {
                        --neighbor_index;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            for (i_itr = indices.begin(); i_itr != i_end; ++i_itr)
            {
                for (
                    ::std::size_t dim_index = 0;
                    dim_index < dim_count;
                    ++dim_index
                )
                {
                    ::std::size_t const dim = position_index[dim_index];

                    index = *i_itr;

                    if (++index[dim] == size[dim])
                    {
                        index[dim] = 0;

                        if (wraparound_policy[dim])
                        {
                            edge_adder(
                                vertex_array(*i_itr)
                              , vertex_array(index)
                            );
                        }
                    }
                    else
                    {
                        edge_adder(vertex_array(*i_itr), vertex_array(index));
                    }
                }
            }
        }
    }
  }  // namespace detail

    template <typename T, typename Tag, typename Base>
    inline ::std::size_t
        count_orthogonal_grid_layout_vertices(
            detail::intrusive_layout_params<T,Tag,Base> const& params
        )
    {
        typedef detail::intrusive_layout_params<T,Tag,Base> Params;
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typedef typename ::boost::parameter::binding<
                    arg_pack_type
                  , ::boost::graph::keywords::tag::position_index_map
                  , identity_property_map
                >::type
                PositionIndexMap;
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::dimensions
                    >::type
                >::type
                Point;
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::dimension_count
                      , ::boost::mpl::integral_c< ::std::size_t,2>
                    >::type
                >::type
                DimensionCount;

        PositionIndexMap position_index = arg_pack[
            ::boost::graph::keywords::_position_index_map
         || value_factory<identity_property_map>()
        ];

        return detail::count_orthogonal_grid_layout_vertices_impl(
            position_index
          , arg_pack[::boost::graph::keywords::_dimensions]
          , arg_pack[
                ::boost::graph::keywords::_scale
              | detail::build_default_scale(
                    arg_pack[
                        ::boost::graph::keywords::_point_factory
                     || value_factory<value_factory<Point> >()
                    ]()
                  , position_index
                  , DimensionCount::value
                )
            ]
          , arg_pack[
                ::boost::graph::keywords::_dimension_count
             || value_factory<DimensionCount>()
            ]
        );
    }

#if BOOST_PP_LESS(4, BOOST_PARAMETER_MAX_ARITY)
    BOOST_PARAMETER_FUNCTION(
        (::std::size_t)
      , count_orthogonal_grid_layout_vertices
      , ::boost::graph::keywords::tag
      , (required
            (dimensions, *)
        )
        (optional
            (dimension_count
              , *
              , (::boost::mpl::integral_c< ::std::size_t,2>())
            )
            (point_factory
              , *
              , detail::make_value_factory(dimensions)
            )
            (position_index_map
              , *
              , identity_property_map()
            )
            (scale
              , *
              , detail::make_default_scale_ic
                (dimension_count)(position_index_map)(point_factory())
            )
        )
    )
    {
        return detail::count_orthogonal_grid_layout_vertices_impl(
            position_index_map
          , dimensions
          , scale
          , dimension_count
        );
    }
#endif  // 4 < BOOST_PARAMETER_MAX_ARITY

    template <
        typename VertexIterator
      , typename EdgeFunction
      , typename T
      , typename Tag
      , typename Base
    >
    inline void
        set_orthogonal_grid_layout(
            VertexIterator vertex_iterator
          , EdgeFunction edge_function
          , detail::intrusive_layout_params<T,Tag,Base> const& params
        )
    {
        typedef detail::intrusive_layout_params<T,Tag,Base> Params;
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typedef typename ::boost::parameter::binding<
                    arg_pack_type
                  , ::boost::graph::keywords::tag::position_index_map
                  , identity_property_map
                >::type
                PositionIndexMap;
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::dimensions
                    >::type
                >::type
                Point;
        typedef typename ::boost::parameter::binding<
                    arg_pack_type
                  , ::boost::graph::keywords::tag::point_factory
                  , value_factory<Point>
                >::type
                PointFactory;
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::dimension_count
                      , ::boost::mpl::integral_c< ::std::size_t,2>
                    >::type
                >::type
                DimensionCount;

        PointFactory point_factory = arg_pack[
            ::boost::graph::keywords::_point_factory
         || value_factory<value_factory<Point> >()
        ];
        PositionIndexMap position_index = arg_pack[
            ::boost::graph::keywords::_position_index_map
         || value_factory<boost::identity_property_map>()
        ];

        detail::set_orthogonal_grid_layout_impl(
            vertex_iterator
          , edge_function
          , arg_pack[::boost::graph::keywords::_is_zeta | false]
          , arg_pack[
                ::boost::graph::keywords::_position_map
             || value_factory<dummy_property_map>()
            ]
          , position_index
          , arg_pack[::boost::graph::keywords::_dimensions]
          , arg_pack[
                ::boost::graph::keywords::_scale
              | detail::build_default_scale(
                    point_factory()
                  , position_index
                  , DimensionCount::value
                )
            ]
          , arg_pack[
                ::boost::graph::keywords::_origin
              | detail::build_default_origin(
                    point_factory()
                  , position_index
                  , DimensionCount::value
                )
            ]
          , arg_pack[
                ::boost::graph::keywords::_dimension_count
             || value_factory<DimensionCount>()
            ]
          , point_factory
          , arg_pack[
                ::boost::graph::keywords::_wraparound_policy
              | detail::index_predicate<false>()
            ]
        );
    }

#if defined(BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_TAKES_ALL_PARAMS)
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , set_orthogonal_grid_layout
      , ::boost::graph::keywords::tag
      , (required
            (vertex_iterator, *)
            (edge_function, *)
            (dimensions, *)
        )
        (optional
            (dimension_count
              , *
              , (::boost::mpl::integral_c< ::std::size_t,2>())
            )
            (is_zeta
              , *
              , false
            )
            (wraparound_policy
              , *
              , detail::index_predicate<false>()
            )
            (point_factory
              , *
              , detail::make_value_factory(dimensions)
            )
            (position_index_map
              , *
              , identity_property_map()
            )
            (scale
              , *
              , detail::make_default_scale_ic
                (dimension_count)(position_index_map)(point_factory())
            )
            (position_map
              , *
              , dummy_property_map()
            )
            (origin
              , *
              , detail::make_default_origin_ic
                (dimension_count)(position_index_map)(point_factory())
            )
        )
    )
    {
        detail::set_orthogonal_grid_layout_impl(
            vertex_iterator
          , edge_function
          , is_zeta
          , position_map
          , position_index_map
          , dimensions
          , scale
          , origin
          , dimension_count
          , point_factory
          , wraparound_policy
        );
        return true;
    }
#elif defined(BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_TAKES_5_PARAMS)
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , set_orthogonal_grid_layout
      , ::boost::graph::keywords::tag
      , (required
            (vertex_iterator, *)
            (edge_function, *)
            (dimensions, *)
        )
        (optional
            (dimension_count
              , *
              , (::boost::mpl::integral_c< ::std::size_t,2>())
            )
            (is_zeta
              , *
              , false
            )
        )
    )
    {
        set_orthogonal_grid_layout(
            vertex_iterator
          , edge_function
          , make_intrusive_layout_params().dimensions(
                dimensions
            ).dimension_count(
                dimension_count
            ).is_zeta(
                is_zeta
            )
        );
        return true;
    }
#endif  // BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_TAKES_*_PARAMS
}  // namespace boost

#endif  // BOOST_GRAPH_SET_ORTHOGONAL_GRID_LAYOUT_HPP

