// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_SET_BITSET_GRID_LAYOUT_HPP
#define BOOST_GRAPH_SET_BITSET_GRID_LAYOUT_HPP

#include <numeric>
#include <functional>
#include <vector>
#include <bitset>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/functional/value_factory.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/detail/intrusive_layout_params.hpp>
#include <boost/graph/keywords/dimension_count.hpp>
#include <boost/graph/keywords/edge_function.hpp>
#include <boost/graph/keywords/position_map.hpp>
#include <boost/graph/keywords/vertex_iterator.hpp>
#include <boost/detail/metafunction/data_type.hpp>

#if BOOST_PP_LESS(3, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_SET_BITSET_GRID_LAYOUT_TAKES_ALL_PARAMS
#endif

namespace boost {
  namespace detail {

    template <typename BitSet>
    struct bitset_grid_layout_bit_count
    {
        template <typename BitCount>
        struct apply
        {
            typedef BitCount type;
        };
    };

    template < ::std::size_t N>
    struct bitset_grid_layout_bit_count< ::std::bitset<N> >
    {
        template <typename T>
        struct apply
        {
            typedef ::boost::mpl::integral_c< ::std::size_t,N> type;
        };
    };

    template <typename PositionMap, typename BitCount>
    inline ::std::size_t
        count_bitset_grid_layout_vertices_impl(
            PositionMap
          , BitCount
        )
    {
        typedef typename ::boost::property_traits<PositionMap>::value_type
                PositionMapValue;
        typedef typename ::boost::mpl::apply_wrap1<
                    bitset_grid_layout_bit_count<PositionMapValue>
                  , BitCount
                >::type
                ActualBitCount;

        return 1 << ActualBitCount::value;
    }

    template <typename BitSet>
    struct bitset_grid_layout_point_factory
    {
        template <typename BitCount>
        struct apply
        {
            struct type
            {
                typedef BitSet result_type;

                result_type operator()() const
                {
                    return result_type(BitCount::value);
                }
            };
        };
    };

    template < ::std::size_t N>
    struct bitset_grid_layout_point_factory< ::std::bitset<N> >
    {
        template <typename T>
        struct apply
        {
            struct type
            {
                typedef ::std::bitset<N> result_type;

                result_type operator()() const
                {
                    return result_type();
                }
            };
        };
    };

    template <>
    struct bitset_grid_layout_point_factory<int>
    {
        template <typename BitCount>
        struct apply
        {
            struct type
            {
                typedef ::std::bitset<BitCount::value> result_type;

                result_type operator()() const
                {
                    return result_type();
                }
            };
        };
    };

    template <
        typename VertexIterator
      , typename EdgeAdder
      , typename PositionMap
      , typename BitCount
    >
    void
        set_bitset_grid_layout_impl(
            VertexIterator v_itr
          , EdgeAdder edge_adder
          , PositionMap position
          , BitCount const&
        )
    {
        typedef typename ::boost::iterator_value<VertexIterator>::type
                Vertex;
        typedef typename ::boost::property_traits<PositionMap>::value_type
                PositionMapValue;
        typedef typename ::boost::mpl::apply_wrap1<
                    bitset_grid_layout_bit_count<PositionMapValue>
                  , BitCount
                >::type
                ActualBitCount;
        typedef typename ::boost::mpl::apply_wrap1<
                    bitset_grid_layout_point_factory<PositionMapValue>
                  , BitCount
                >::type
                BitSetFactory;
        typedef typename BitSetFactory::result_type
                BitSet;
        ::std::size_t const bit_count = ActualBitCount::value;
        BOOST_STATIC_ASSERT((1 < bit_count));
        ::std::size_t const vert_count = 1 << bit_count;
        typedef ::boost::multi_array<Vertex,bit_count> VertexArray;
        typedef typename VertexArray::index VAI;
        typedef ::boost::array<VAI,bit_count> Index;

        Index size;

        for (::std::size_t bit_index = 0; bit_index < bit_count; ++bit_index)
        {
            size[bit_index] = bit_count;
        }

        VertexArray vertex_array(size);
        ::std::vector<Index> indices(1 << bit_count);
        Index index;
        typename ::std::vector<Index>::iterator i_itr, i_end = indices.end();

        for (::std::size_t bit_index = 0; bit_index < bit_count; ++bit_index)
        {
            index[bit_index] = 0;
        }

        BitSetFactory bitset_factory;

        for (i_itr = indices.begin(); i_itr != i_end; ++i_itr, ++v_itr)
        {
            BitSet bit_set = bitset_factory();
            ::std::size_t bit_index = 0;

            while (bit_index < bit_count)
            {
                bit_set[bit_index] = index[bit_index] ? true : false;
                ++bit_index;
            }

            put(position, vertex_array(*i_itr = index) = *v_itr, bit_set);

            for (
                ++index[--bit_index];
                bit_index && (index[bit_index] == 2);
                ++index[--bit_index]
            )
            {
                index[bit_index] = 0;
            }
        }

        for (i_itr = indices.begin(); i_itr != i_end; ++i_itr)
        {
            for (
                ::std::size_t bit_index = 0;
                bit_index < bit_count;
                ++bit_index
            )
            {
                index = *i_itr;

                if (!index[bit_index])
                {
                    index[bit_index] = 1;
                    edge_adder(vertex_array(*i_itr), vertex_array(index));
                }
            }
        }
    }
  }  // namespace detail

    template <typename T, typename Tag, typename Base>
    inline ::std::size_t
        count_bitset_grid_layout_vertices(
            detail::intrusive_layout_params<T,Tag,Base> const& params
        )
    {
        typedef detail::intrusive_layout_params<T,Tag,Base> Params;
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::dimension_count
                      , ::boost::mpl::integral_c< ::std::size_t,0>
                    >::type
                >::type
                BitCount;

        return detail::count_bitset_grid_layout_vertices_impl(
            position_map
          , arg_pack[
                ::boost::graph::keywords::_dimension_count
             || value_factory<BitCount>()
            ]
        );
    }

#if BOOST_PP_LESS(1, BOOST_PARAMETER_MAX_ARITY)
    BOOST_PARAMETER_FUNCTION(
        (::std::size_t)
      , count_bitset_grid_layout_vertices
      , ::boost::graph::keywords::tag
      , (deduced
            (optional
                (position_map
                  , *(is_property_map< ::boost::mpl::_>)
                  , dummy_property_map()
                )
                (dimension_count
                  , *(::boost::mpl::not_<is_property_map< ::boost::mpl::_> >)
                  , (::boost::mpl::integral_c< ::std::size_t,0>())
                )
            )
        )
    )
    {
        return detail::count_bitset_grid_layout_vertices_impl(
            position_map
          , dimension_count
        );
    }
#endif  // 1 < BOOST_PARAMETER_MAX_ARITY

    template <
        typename VertexIterator
      , typename EdgeFunction
      , typename T
      , typename Tag
      , typename Base
    >
    inline void
        set_bitset_grid_layout(
            VertexIterator vertex_iterator
          , EdgeFunction edge_function
          , detail::intrusive_layout_params<T,Tag,Base> const& params
        )
    {
        typedef detail::intrusive_layout_params<T,Tag,Base> Params;
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::dimension_count
                      , ::boost::mpl::integral_c< ::std::size_t,0>
                    >::type
                >::type
                BitCount;

        detail::set_bitset_grid_layout_impl(
            vertex_iterator
          , edge_function
          , arg_pack[
                ::boost::graph::keywords::_position_map
             || value_factory<dummy_property_map>()
            ]
          , arg_pack[
                ::boost::graph::keywords::_dimension_count
             || value_factory<BitCount>()
            ]
        );
    }

#if defined(BOOST_GRAPH_SET_BITSET_GRID_LAYOUT_TAKES_ALL_PARAMS)
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , set_bitset_grid_layout
      , ::boost::graph::keywords::tag
      , (required
            (vertex_iterator, *)
            (edge_function, *)
        )
        (deduced
            (optional
                (position_map
                  , *(is_property_map< ::boost::mpl::_>)
                  , dummy_property_map()
                )
                (dimension_count
                  , *(::boost::mpl::not_<is_property_map< ::boost::mpl::_> >)
                  , (::boost::mpl::integral_c< ::std::size_t,0>())
                )
            )
        )
    )
    {
        detail::set_bitset_grid_layout_impl(
            vertex_iterator
          , edge_function
          , position_map
          , dimension_count
        );
        return true;
    }
#endif  // BOOST_GRAPH_SET_BITSET_GRID_LAYOUT_TAKES_ALL_PARAMS
}  // namespace boost

#endif  // BOOST_GRAPH_SET_BITSET_GRID_LAYOUT_HPP

