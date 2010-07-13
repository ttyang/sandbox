// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP


#include <boost/concept_check.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/distance_result.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/copy.hpp>


// Helper geometries
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/segment.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance
{


/*!
    \brief Strategy for distance point to segment
    \ingroup distance
    \details Calculates distance using projected-point method, and (optionally) Pythagoras
    \author Adapted from: http://geometryalgorithms.com/Archive/algorithm_0102/algorithm_0102.htm
    \tparam P point type
    \tparam PointOfSegment segment type
    \tparam Strategy strategy, optional, defaults to pythagoras
    \par Concepts for Strategy:
    - cartesian_distance operator(Point,Point)
    \note If the Strategy is a "comparable::pythagoras", this strategy
        automatically is a comparable projected_point strategy (so without sqrt)
*/
template
<
    typename Point,
    typename PointOfSegment,
    typename CalculationType = void,
    typename Strategy = pythagoras<Point, PointOfSegment, CalculationType>
>
class projected_point
{
public :
    typedef typename strategy::distance::services::return_type<Strategy>::type calculation_type;

private :

    // The three typedefs below are necessary to calculate distances
    // from segments defined in integer coordinates.

    // Integer coordinates can still result in FP distances.
    // There is a division, which must be represented in FP.
    // So promote.
    typedef typename promote_floating_point<calculation_type>::type fp_type;

    // A projected point of points in Integer coordinates must be able to be
    // represented in FP.
    typedef boost::geometry::point
        <
            fp_type,
            dimension<PointOfSegment>::value,
            typename coordinate_system<PointOfSegment>::type
        > fp_point_type;

    // For convenience
    typedef fp_point_type fp_vector_type;

    // We have to use a strategy using FP coordinates (fp-type) which is
    // not always the same as Strategy (defined as point_strategy_type)
    // So we create a "similar" one
    typedef typename strategy::distance::services::similar_type
        <
            Strategy,
            Point,
            fp_point_type
        >::type fp_strategy_type;

public :

    inline calculation_type apply(Point const& p,
                    PointOfSegment const& p1, PointOfSegment const& p2) const
    {
        assert_dimension_equal<Point, PointOfSegment>();

        /* Algorithm
        POINT v(x2 - x1, y2 - y1);
        POINT w(px - x1, py - y1);
        c1 = w . v
        c2 = v . v
        b = c1 / c2
        RETURN POINT(x1 + b * vx, y1 + b * vy);
        */

        // v is multiplied below with a (possibly) FP-value, so should be in FP
        // For consistency we define w also in FP
        fp_vector_type v, w;

        copy_coordinates(p2, v);
        copy_coordinates(p, w);
        subtract_point(v, p1);
        subtract_point(w, p1);

        Strategy strategy;
        boost::ignore_unused_variable_warning(strategy);

        calculation_type zero = calculation_type();
        fp_type c1 = dot_product(w, v);
        if (c1 <= zero)
        {
            return strategy.apply(p, p1);
        }
        fp_type c2 = dot_product(v, v);
        if (c2 <= c1)
        {
            return strategy.apply(p, p2);
        }

        // See above, c1 > 0 AND c2 > c1 so: c2 != 0
        fp_type b = fp_type(c1) / fp_type(c2);


        fp_strategy_type fp_strategy
            = strategy::distance::services::get_similar
                <
                    Strategy, Point, fp_point_type
                >::apply(strategy);

        fp_point_type projected;
        copy_coordinates(p1, projected);
        multiply_value(v, b);
        add_point(projected, v);

        //std::cout << "distance " << dsv(p) << " .. " << dsv(projected) << std::endl;

        return fp_strategy.apply(p, projected);
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Point, typename PointOfSegment, typename CalculationType, typename Strategy>
struct tag<projected_point<Point, PointOfSegment, CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_segment type;
};


template <typename Point, typename PointOfSegment, typename CalculationType, typename Strategy>
struct return_type<projected_point<Point, PointOfSegment, CalculationType, Strategy> >
{
    typedef typename projected_point<Point, PointOfSegment, CalculationType, Strategy>::calculation_type type;
};

template <typename Point, typename PointOfSegment, typename CalculationType, typename Strategy>
struct strategy_point_point<projected_point<Point, PointOfSegment, CalculationType, Strategy> >
{
    typedef typename Strategy type;
};


template
<
    typename Point,
    typename PointOfSegment,
    typename CalculationType,
    typename Strategy,
    typename P1,
    typename P2
>
struct similar_type<projected_point<Point, PointOfSegment, CalculationType, Strategy>, P1, P2>
{
    typedef projected_point<P1, P2, CalculationType, Strategy> type;
};


template
<
    typename Point,
    typename PointOfSegment,
    typename CalculationType,
    typename Strategy,
    typename P1,
    typename P2
>
struct get_similar<projected_point<Point, PointOfSegment, CalculationType, Strategy>, P1, P2>
{
    static inline typename similar_type
        <
            projected_point<Point, PointOfSegment, CalculationType, Strategy>, P1, P2
        >::type apply(projected_point<Point, PointOfSegment, CalculationType, Strategy> const& )
    {
        return projected_point<P1, P2, CalculationType, Strategy>();
    }
};


template <typename Point, typename PointOfSegment, typename CalculationType, typename Strategy>
struct comparable_type<projected_point<Point, PointOfSegment, CalculationType, Strategy> >
{
    // Define a projected_point strategy with its underlying point-point-strategy
    // being comparable
    typedef projected_point
        <
            Point,
            PointOfSegment,
            CalculationType,
            typename comparable_type<Strategy>::type
        > type;
};


template <typename Point, typename PointOfSegment, typename CalculationType, typename Strategy>
struct get_comparable<projected_point<Point, PointOfSegment, CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            projected_point<Point, PointOfSegment, CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type apply(projected_point<Point, PointOfSegment, CalculationType, Strategy> const& )
    {
        return comparable_type();
    }
};


template <typename Point, typename PointOfSegment, typename CalculationType, typename Strategy>
struct result_from_distance<projected_point<Point, PointOfSegment, CalculationType, Strategy> >
{
private :
    typedef typename return_type<projected_point<Point, PointOfSegment, CalculationType, Strategy> >::type return_type;
public :
    template <typename T>
    static inline return_type apply(projected_point<Point, PointOfSegment, CalculationType, Strategy> const& , T const& value)
    {
        Strategy s;
        return result_from_distance<Strategy>::apply(s, value);
    }
};


template <typename Point, typename PointOfSegment>
struct default_strategy<segment_tag, Point, PointOfSegment, cartesian_tag, cartesian_tag>
{
    typedef strategy::distance::projected_point
    <
        Point,
        PointOfSegment,
        void,
        typename default_strategy
        <
            point_tag, Point, PointOfSegment,
            cartesian_tag, cartesian_tag
        >::type
    > type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP
