// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP

#include <iterator>

#include <boost/range.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits.hpp>

#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/util/closeable_view.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/length_result.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace length
{


template<typename Segment, typename Strategy>
struct segment_length
{
    static inline typename length_result<Segment>::type apply(
            Segment const& segment, Strategy const& strategy)
    {
        typedef typename point_type<Segment>::type point_type;
        point_type p1, p2;
        assign_point_from_index<0>(segment, p1);
        assign_point_from_index<1>(segment, p2);
        return strategy.apply(p1, p2);
    }
};

/*!
\brief Internal, calculates length of a linestring using iterator pairs and
    specified strategy
\note for_each could be used here, now that point_type is changed by boost
    range iterator
*/
template<typename Range, typename Strategy, bool Close>
struct range_length
{
    typedef typename length_result<Range>::type return_type;

    static inline return_type apply(
            Range const& range, Strategy const& strategy)
    {
        typedef closeable_view<Range const, Close> view_type;
        typedef typename boost::range_iterator
            <
                view_type const
            >::type iterator_type;

        return_type sum = return_type();
        view_type view(range);
        iterator_type it = boost::begin(view), end = boost::end(view);
        if(it != end)
        {
            for(iterator_type previous = it++;
                    it != end;
                    ++previous, ++it)
            {
                // Add point-point distance using the return type belonging
                // to strategy
                sum += strategy.apply(*previous, *it);
            }
        }

        return sum;
    }
};


}} // namespace detail::length
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Tag, typename Geometry, typename Strategy>
struct length : detail::calculate_null
    <
        typename length_result<Geometry>::type,
        Geometry,
        Strategy
    >
{};


template <typename Geometry, typename Strategy>
struct length<linestring_tag, Geometry, Strategy>
    : detail::length::range_length<Geometry, Strategy, false>
{};


// RING: length is currently 0; it might be argued that it is the "perimeter"


template <typename Geometry, typename Strategy>
struct length<segment_tag, Geometry, Strategy>
    : detail::length::segment_length<Geometry, Strategy>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_calc{length}
\ingroup length
\details \details_calc{length, length (the sum of distances between consecutive points)}. \details_default_strategy
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{length}

\qbk{behavior,__0dim__:[qbk_ret 0]}
\qbk{behavior,__1dim__:[qbk_ret the length]}
\qbk{behavior,__2dim__:[qbk_ret 0]}
\qbk{complexity,Linear}
\qbk{compliance,__ogc__}
\qbk{example,length}
 */
template<typename Geometry>
inline typename length_result<Geometry>::type length(
        Geometry const& geometry)
{
    concept::check<Geometry const>();

    typedef typename strategy::distance::services::default_strategy
        <
            point_tag, typename point_type<Geometry>::type
        >::type strategy_type;

    return dispatch::length
        <
            typename tag<Geometry>::type,
            Geometry,
            strategy_type
        >::apply(geometry, strategy_type());
}


/*!
\brief \brief_calc{length} \brief_strategy
\ingroup length
\details \details_calc{length, length (the sum of distances between consecutive points)} \brief_strategy. \details_strategy_reasons
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{distance}
\param geometry \param_geometry
\param strategy \param_strategy{distance}
\return \return_calc{length}

\qbk{distinguish,with strategy}
\qbk{example,length_strategy}
 */
template<typename Geometry, typename Strategy>
inline typename length_result<Geometry>::type length(
        Geometry const& geometry, Strategy const& strategy)
{
    concept::check<Geometry const>();

    return dispatch::length
        <
            typename tag<Geometry>::type,
            Geometry,
            Strategy
        >::apply(geometry, strategy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP
