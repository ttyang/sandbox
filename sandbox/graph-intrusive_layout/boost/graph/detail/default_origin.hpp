// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_DEFAULT_ORIGIN_HPP
#define BOOST_GRAPH_DETAIL_DEFAULT_ORIGIN_HPP

#include <boost/utility/value_init.hpp>

namespace boost { namespace detail {

    template <typename Point, typename PositionIndexMap, typename Dimension>
    inline Point&
        build_default_origin(
            Point const& point
          , PositionIndexMap position_index
          , Dimension const dimension_count
        )
    {
        Point& result = const_cast<Point&>(point);

        for (Dimension dim = initialized_value; dim < dimension_count; ++dim)
        {
            result[position_index[dim]] = initialized_value;
        }

        return result;
    }

    template <typename Dimension>
    class default_origin
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
                return build_default_origin(
                    point
                  , _position_index
                  , _dimension_count
                );
            }
        };

        Dimension const _dimension_count;

     public:
        inline explicit default_origin(Dimension const dimension_count)
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
    inline default_origin<Dimension>
        make_default_origin(Dimension const dimension_count)
    {
        return default_origin<Dimension>(dimension_count);
    }

    template <typename DimensionCount>
    inline default_origin<typename DimensionCount::value_type>
        make_default_origin_ic(DimensionCount)
    {
        return make_default_origin(DimensionCount::value);
    }
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_DEFAULT_ORIGIN_HPP

