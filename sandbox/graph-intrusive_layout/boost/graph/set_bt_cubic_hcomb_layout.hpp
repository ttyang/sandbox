// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_SET_BT_CUBIC_HCOMB_LAYOUT_HPP
#define BOOST_GRAPH_SET_BT_CUBIC_HCOMB_LAYOUT_HPP

#include <numeric>
#include <functional>
#include <vector>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/functional/value_factory.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/detail/intrusive_layout_params.hpp>
#include <boost/graph/keywords/dimensions.hpp>
#include <boost/graph/keywords/edge_function.hpp>
#include <boost/graph/keywords/inscribed_radius.hpp>
#include <boost/graph/keywords/origin.hpp>
#include <boost/graph/keywords/point_factory.hpp>
#include <boost/graph/keywords/position_map.hpp>
#include <boost/graph/keywords/vertex_iterator.hpp>
#include <boost/graph/keywords/wraparound_policy.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/detail/index_predicate.hpp>
#include <boost/detail/make_value_factory.hpp>
#include <boost/graph/detail/default_origin.hpp>

#if BOOST_PP_LESS(8, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_ALL_PARAMS
#elif BOOST_PP_LESS(4, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_5_PARAMS
#endif

namespace boost {
  namespace detail {

    template <typename PositionIndexMap, typename Scalar, typename Dimensions>
    ::std::size_t
        count_bitruncated_cubic_honeycomb_layout_vertices_impl(
            PositionIndexMap position_index
          , Scalar inscribed_radius
          , Dimensions const& dimensions
        )
    {
        ::std::size_t const dim_count = 3;
        Scalar const inscribed_diameter = inscribed_radius * 2;

        ::boost::array< ::std::size_t,dim_count> size_1, size_2;

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            ::std::size_t const dim = position_index[dim_index];

            size_1[dim] = static_cast< ::std::size_t>(
                (dimensions[dim] + inscribed_radius) / inscribed_diameter
            );
            size_2[dim] = static_cast< ::std::size_t>(
                dimensions[dim] / inscribed_diameter
            );
        }

        return ::std::accumulate(
            size_1.begin()
          , size_1.end()
          , 1
          , ::std::multiplies< ::std::size_t>()
        ) + ::std::accumulate(
            size_2.begin()
          , size_2.end()
          , 1
          , ::std::multiplies< ::std::size_t>()
        );
    }

    template <
        typename VertexIterator
      , typename EdgeAdder
      , typename PositionMap
      , typename PositionIndexMap
      , typename Scalar
      , typename Dimensions
      , typename Point
      , typename PointFactory
      , typename WraparoundPolicy
    >
    void
        set_bitruncated_cubic_honeycomb_layout_impl(
            VertexIterator v_itr
          , EdgeAdder edge_adder
          , PositionMap position
          , PositionIndexMap position_index
          , Scalar inscribed_radius
          , Dimensions const& dimensions
          , Point const& origin
          , PointFactory point_factory
          , WraparoundPolicy const& wraparound_policy
        )
    {
        typedef typename ::boost::iterator_value<VertexIterator>::type Vertex;
        ::std::size_t const dim_count = 3;
        typedef ::boost::multi_array<Vertex,dim_count> VertexArray;
        typedef typename VertexArray::index VAI;
        typedef ::boost::array<VAI,dim_count> Index;

        Scalar const inscribed_diameter = inscribed_radius * 2;
        Index size_1, size_2;

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            ::std::size_t const dim = position_index[dim_index];

            size_1[dim] = static_cast< ::std::size_t>(
                (dimensions[dim] + inscribed_radius) / inscribed_diameter
            );
            size_2[dim] = static_cast< ::std::size_t>(
                dimensions[dim] / inscribed_diameter
            );
        }

        VertexArray vertex_array_1(size_1);
        VertexArray vertex_array_2(size_2);
        ::std::vector<Index> indices_1(
            ::std::accumulate(
                size_1.begin()
              , size_1.end()
              , 1
              , ::std::multiplies<VAI>()
            )
        );
        ::std::vector<Index> indices_2(
            ::std::accumulate(
                size_2.begin()
              , size_2.end()
              , 1
              , ::std::multiplies<VAI>()
            )
        );
        Index index;

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            index[position_index[dim_index]] = 0;
        }

        typename ::std::vector<Index>::iterator i_itr;
        typename ::std::vector<Index>::iterator i_1_end = indices_1.end();

        for (i_itr = indices_1.begin(); i_itr != i_1_end; ++i_itr, ++v_itr)
        {
            Point point = point_factory();
            ::std::size_t dim_index = 0;

            while (dim_index < dim_count)
            {
                ::std::size_t const dim = position_index[dim_index];

                point[dim] = inscribed_diameter * index[dim] + origin[dim];
                ++dim_index;
            }

            put(position, vertex_array_1(*i_itr = index) = *v_itr, point);

            for (
                ++index[position_index[--dim_index]];
                dim_index && (
                    index[position_index[dim_index]]
                 == size_1[position_index[dim_index]]
                );
                ++index[position_index[--dim_index]]
            )
            {
                index[position_index[dim_index]] = 0;
            }
        }

        for (::std::size_t dim_index = 0; dim_index < dim_count; ++dim_index)
        {
            index[position_index[dim_index]] = 0;
        }

        typename ::std::vector<Index>::iterator i_2_end = indices_2.end();

        for (i_itr = indices_2.begin(); i_itr != i_2_end; ++i_itr, ++v_itr)
        {
            Point point = point_factory();
            ::std::size_t dim_index = 0;

            while (dim_index < dim_count)
            {
                ::std::size_t const dim = position_index[dim_index];

                point[dim] = (
                    inscribed_diameter * index[dim]
                  + origin[dim]
                  + inscribed_radius
                );
                ++dim_index;
            }

            put(position, vertex_array_2(*i_itr = index) = *v_itr, point);

            for (
                ++index[position_index[--dim_index]];
                dim_index && (
                    index[position_index[dim_index]]
                 == size_2[position_index[dim_index]]
                );
                ++index[position_index[--dim_index]]
            )
            {
                index[position_index[dim_index]] = 0;
            }
        }

        bool add_diagonal;

        for (i_itr = indices_1.begin(); i_itr != i_1_end; ++i_itr)
        {
            index = *i_itr;
            add_diagonal = true;

            for (
                ::std::size_t dim_index = 0;
                dim_index < dim_count;
                ++dim_index
            )
            {
                ::std::size_t const dim = position_index[dim_index];

                if (add_diagonal && (index[dim] == size_2[dim]))
                {
                    add_diagonal = false;
                }
            }

            if (add_diagonal)
            {
                edge_adder(vertex_array_1(index), vertex_array_2(index));
            }
        }

        for (i_itr = indices_2.begin(); i_itr != i_2_end; ++i_itr)
        {
            index = *i_itr;
            add_diagonal = true;

            for (
                ::std::size_t dim_index = 0;
                dim_index < dim_count;
                ++dim_index
            )
            {
                ::std::size_t const dim = position_index[dim_index];

                if (++index[dim] == size_1[dim])
                {
                    if (wraparound_policy[dim])
                    {
                        index[dim] = 0;
                    }
                    else
                    {
                        add_diagonal = false;
                    }
                }
            }

            if (add_diagonal)
            {
                edge_adder(vertex_array_2(*i_itr), vertex_array_1(index));
            }
        }

        for (i_itr = indices_1.begin(); i_itr != i_1_end; ++i_itr)
        {
            for (
                ::std::size_t dim_index = 0;
                dim_index < dim_count;
                ++dim_index
            )
            {
                ::std::size_t const dim = position_index[dim_index];

                index = *i_itr;

                if (++index[dim] == size_1[dim])
                {
                    if (wraparound_policy[dim])
                    {
                        index[dim] = 0;
                        edge_adder(
                            vertex_array_1(*i_itr)
                          , vertex_array_1(index)
                        );
                    }
                }
                else
                {
                    edge_adder(vertex_array_1(*i_itr), vertex_array_1(index));
                }
            }
        }

        Index other_index;

        for (i_itr = indices_2.begin(); i_itr != i_2_end; ++i_itr)
        {
            for (
                ::std::size_t dim_index = 0;
                dim_index < dim_count;
                ++dim_index
            )
            {
                ::std::size_t const dim = position_index[dim_index];

                index = *i_itr;
                add_diagonal = false;

                if (++index[dim] == size_2[dim])
                {
                    if (wraparound_policy[dim] && (size_1[dim] == size_2[dim]))
                    {
                        index[dim] = 0;
                        edge_adder(
                            vertex_array_2(*i_itr)
                          , vertex_array_2(index)
                        );
                        edge_adder(
                            vertex_array_2(*i_itr)
                          , vertex_array_1(index)
                        );
                        add_diagonal = true;
                    }
                }
                else
                {
                    edge_adder(vertex_array_2(*i_itr), vertex_array_2(index));
                    edge_adder(vertex_array_2(*i_itr), vertex_array_1(index));
                    add_diagonal = true;
                }

                if (add_diagonal)
                {
                    for (
                        ::std::size_t dim_index2 = dim_index + 1;
                        dim_index2 < dim_count;
                        ++dim_index2
                    )
                    {
                        ::std::size_t const dim2 = position_index[dim_index2];

                        other_index = index;

                        if (++other_index[dim2] == size_2[dim2])
                        {
                            if (
                                wraparound_policy[dim2]
                             && (size_1[dim2] == size_2[dim2])
                            )
                            {
                                other_index[dim2] = 0;
                                edge_adder(
                                    vertex_array_1(other_index)
                                  , vertex_array_2(*i_itr)
                                );
                            }
                        }
                        else
                        {
                            edge_adder(
                                vertex_array_1(other_index)
                              , vertex_array_2(*i_itr)
                            );
                        }
                    }
                }
            }
        }
    }
  }  // namespace detail

    template <typename T, typename Tag, typename Base>
    inline ::std::size_t
        count_bitruncated_cubic_honeycomb_layout_vertices(
            detail::intrusive_layout_params<T,Tag,Base> const& params
        )
    {
        typedef detail::intrusive_layout_params<T,Tag,Base> Params;
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        return detail::count_bitruncated_cubic_honeycomb_layout_vertices_impl(
            arg_pack[
                ::boost::graph::keywords::_position_index_map
             || value_factory<identity_property_map>()
            ]
          , arg_pack[::boost::graph::keywords::_inscribed_radius | 1]
          , arg_pack[::boost::graph::keywords::_dimensions]
        );
    }

#if BOOST_PP_LESS(2, BOOST_PARAMETER_MAX_ARITY)
    BOOST_PARAMETER_FUNCTION(
        (::std::size_t)
      , count_bitruncated_cubic_honeycomb_layout_vertices
      , ::boost::graph::keywords::tag
      , (required
            (dimensions, *)
        )
        (optional
            (inscribed_radius
              , *
              , 1
            )
            (position_index_map
              , *
              , identity_property_map()
            )
        )
    )
    {
        return detail::count_bitruncated_cubic_honeycomb_layout_vertices_impl(
            position_index_map
          , inscribed_radius
          , dimensions
        );
    }
#endif  // 2 < BOOST_PARAMETER_MAX_ARITY

    template <
        typename VertexIterator
      , typename EdgeFunction
      , typename T
      , typename Tag
      , typename Base
    >
    inline void
        set_bitruncated_cubic_honeycomb_layout(
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

        PointFactory point_factory = arg_pack[
            ::boost::graph::keywords::_point_factory
         || value_factory<value_factory<Point> >()
        ];
        PositionIndexMap position_index = arg_pack[
            ::boost::graph::keywords::_position_index_map
         || value_factory<identity_property_map>()
        ];

        detail::set_bitruncated_cubic_honeycomb_layout_impl(
            vertex_iterator
          , edge_function
          , arg_pack[
                ::boost::graph::keywords::_position_map
             || value_factory<dummy_property_map>()
            ]
          , position_index
          , arg_pack[::boost::graph::keywords::_inscribed_radius | 1]
          , arg_pack[::boost::graph::keywords::_dimensions]
          , arg_pack[
                ::boost::graph::keywords::_origin
              | detail::build_default_origin(
                    point_factory()
                  , position_index
                  , 3
                )
            ]
          , point_factory
          , arg_pack[
                ::boost::graph::keywords::_wraparound_policy
              | detail::index_predicate<false>()
            ]
        );
    }

#if defined(BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_ALL_PARAMS)
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , set_bitruncated_cubic_honeycomb_layout
      , ::boost::graph::keywords::tag
      , (required
            (vertex_iterator, *)
            (edge_function, *)
            (dimensions, *)
        )
        (optional
            (inscribed_radius
              , *
              , 1
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
            (position_map
              , *
              , dummy_property_map()
            )
            (origin
              , *
              , detail::make_default_origin
                (3)(position_index_map)(point_factory())
            )
        )
    )
    {
        detail::set_bitruncated_cubic_honeycomb_layout_impl(
            vertex_iterator
          , edge_function
          , position_map
          , position_index_map
          , inscribed_radius
          , dimensions
          , origin
          , point_factory
          , wraparound_policy
        );
        return true;
    }
#elif defined(BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_5_PARAMS)
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , set_bitruncated_cubic_honeycomb_layout
      , ::boost::graph::keywords::tag
      , (required
            (vertex_iterator, *)
            (edge_function, *)
            (dimensions, *)
        )
        (optional
            (inscribed_radius
              , *
              , 1
            )
            (wraparound_policy
              , *
              , detail::index_predicate<false>()
            )
        )
    )
    {
        set_bitruncated_cubic_honeycomb_layout(
            vertex_iterator
          , edge_function
          , make_intrusive_layout_params().dimensions(
                dimensions
            ).inscribed_radius(
                inscribed_radius
            ).wraparound_policy(
                wraparound_policy
            )
        );
        return true;
    }
#endif  // BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_*_PARAMS
}  // namespace boost

#endif  // BOOST_GRAPH_SET_BT_CUBIC_HCOMB_LAYOUT_HPP

