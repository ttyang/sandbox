// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_DEFAULT_SCALE_HPP
#define BOOST_GRAPH_DETAIL_DEFAULT_SCALE_HPP

#include <boost/utility/value_init.hpp>

namespace boost { namespace detail {

    template <typename Point, typename PositionIndexMap, typename Dimension>
    inline Point&
        build_default_scale(
            Point const& point
          , PositionIndexMap position_index
          , Dimension const dimension_count
        )
    {
        Point& result = const_cast<Point&>(point);

        for (Dimension dim = initialized_value; dim < dimension_count; ++dim)
        {
            result[position_index[dim]] = typename Point::value_type(1);
        }

        return result;
    }

    template <typename Dimension>
    class default_scale
    {
        template <typename PositionIndexMap>
        class dispatch
        {
            Dimension const _dimension_count;
            PositionIndexMap _position_index;

         public:
            inline dispatch(
                Dimension const dimension_count
              , PositionIndexMap position_index
            ) : _dimension_count(dimension_count)
              , _position_index(position_index)
            {
            }

            template <typename Point>
            inline Point& operator()(Point const& point) const
            {
                return build_default_scale(
                    point
                  , _position_index
                  , _dimension_count
                );
            }
        };

        Dimension const _dimension_count;

     public:
        inline explicit default_scale(Dimension const dimension_count)
          : _dimension_count(dimension_count)
        {
        }

        template <typename PositionIndexMap>
        inline dispatch<PositionIndexMap>
            operator()(PositionIndexMap position_index) const
        {
            return dispatch<
                PositionIndexMap
            >(_dimension_count, position_index);
        }
    };

    template <typename Dimension>
    inline default_scale<Dimension>
        make_default_scale(Dimension const dimension_count)
    {
        return default_scale<Dimension>(dimension_count);
    }

    template <typename DimensionCount>
    inline default_scale<typename DimensionCount::value_type>
        make_default_scale_ic(DimensionCount)
    {
        return make_default_scale(DimensionCount::value);
    }
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_DEFAULT_SCALE_HPP

