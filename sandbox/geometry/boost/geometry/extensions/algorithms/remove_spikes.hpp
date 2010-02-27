// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2010, Geodan, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGORITHMS_REMOVE_SPIKES_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGORITHMS_REMOVE_SPIKES_HPP

#include <algorithm>
#include <deque>

#include <boost/range.hpp>
#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>

#include <boost/geometry/multi/core/tags.hpp>


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/iterators/ever_circling_iterator.hpp>

/*
Remove spikes from a ring/polygon.
Ring (having 8 vertices, including closing vertex)
+------+
|      |
|      +--+
|      |  ^this "spike" is removed, can be located outside/inside the ring
+------+
(the actualy determination if it is removed is done by a strategy, TODO)

*/


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace remove_spikes
{


template <typename Range, typename Policy>
struct range_remove_spikes
{
    typedef typename strategy_side
    <
        typename cs_tag<Range>::type
    >::type side_strategy_type;

    typedef typename coordinate_type<Range>::type coordinate_type;



    static inline void apply(Range& range, Policy const& policy)
    {
        std::size_t n = boost::size(range);
        if (n < 3)
        {
            return;
        }

        typedef typename boost::range_iterator<Range>::type iterator;
        ever_circling_iterator<iterator> it(boost::begin(range), boost::end(range), true);
        ever_circling_iterator<iterator> next(boost::begin(range), boost::end(range), true);
        ever_circling_iterator<iterator> prev(boost::begin(range), boost::end(range), true);
        // If it is "closed", skip the last (or actually the first coming after last) one.
        n--;

        it++;
        next++;
        next++;

        bool close = false;

        std::deque<std::size_t> vertices;
        for (std::size_t i = 0;
            i < n;
            ++i, ++prev, ++it, ++next)
        {
            if (policy(*prev, *it, *next))
            {
                // It is collinear, middle point (i == 1) will be removed below
                vertices.push_back(i + 1);
                if (i == n - 1)
                {
                    vertices.push_front(0);
                    close = true;
                }
            }
        }
        for (std::deque<std::size_t>::reverse_iterator rit = vertices.rbegin();
            rit != vertices.rend(); ++rit)
        {
            range.erase(range.begin() + *rit);
        }
        if (close)
        {
            typename point_type<Range>::type p = range.front();
            range.push_back(p);
        }
    }
};


template <typename Polygon, typename Policy>
struct polygon_remove_spikes
{
    static inline void apply(Polygon& polygon, Policy const& policy)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        typedef range_remove_spikes<ring_type, Policy> per_range;
        per_range::apply(exterior_ring(polygon), policy);

        for (typename boost::range_iterator
                <
                    typename interior_type<Polygon>::type
                >::type it = boost::begin(interior_rings(polygon));
             it != boost::end(interior_rings(polygon));
             ++it)
        {
            per_range::apply(*it, policy);
        }
    }
};


template <typename MultiGeometry, typename Policy, typename SinglePolicy>
struct multi_remove_spikes
{
    static inline void apply(MultiGeometry& multi, Policy const& policy)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            SinglePolicy::apply(*it, policy);
        }
    }
};


}} // namespace detail::remove_spikes
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Tag,
    typename Geometry,
    typename Policy
>
struct remove_spikes
{
    static inline void apply(Geometry&, Policy const&)
    {}
};


template <typename Ring, typename Policy>
struct remove_spikes<ring_tag, Ring, Policy>
    : detail::remove_spikes::range_remove_spikes<Ring, Policy>
{};



template <typename Polygon, typename Policy>
struct remove_spikes<polygon_tag, Polygon, Policy>
    : detail::remove_spikes::polygon_remove_spikes<Polygon, Policy>
{};


template <typename MultiPolygon, typename Policy>
struct remove_spikes<multi_polygon_tag, MultiPolygon, Policy>
    : detail::remove_spikes::multi_remove_spikes
        <
            MultiPolygon,
            Policy,
            detail::remove_spikes::polygon_remove_spikes
            <
                typename boost::range_value<MultiPolygon>::type,
                Policy
            >
        >
{};



} // namespace dispatch
#endif


/*!
    \ingroup remove_spikes
    \tparam Geometry geometry type
    \param geometry the geometry to make remove_spikes
*/
template <typename Geometry, typename Policy>
inline void remove_spikes(Geometry& geometry, Policy const& policy)
{
    concept::check<Geometry>();

    dispatch::remove_spikes
        <
            typename tag<Geometry>::type,
            Geometry,
            Policy
        >::apply(geometry, policy);
}



template <typename Point>
struct remove_elongated_spikes
{
    typedef typename coordinate_type<Point>::type coordinate_type;
    coordinate_type m_area_div_peri;
    coordinate_type m_dist_div_peri;
    coordinate_type m_area_limit;
    coordinate_type m_distance_limit;
    coordinate_type m_zero;


    inline remove_elongated_spikes(coordinate_type const& area_div_peri = 0.001
        , coordinate_type const& dist_div_peri = 0.001
        , coordinate_type const& area_limit = 0.01
        , coordinate_type const& distance_limit = 1
        )
            : m_area_div_peri(area_div_peri)
            , m_dist_div_peri(dist_div_peri)
            , m_area_limit(area_limit)
            , m_distance_limit(distance_limit)
            , m_zero(coordinate_type())
    {}


    inline bool operator()(Point const& prev,
                Point const& current, Point const& next) const
    {
        coordinate_type d1 = geometry::distance(prev, current);
        if (d1 < m_distance_limit)
        {
            geometry::linear_ring<Point> triangle;
            triangle.push_back(prev);
            triangle.push_back(current);
            triangle.push_back(next);
            triangle.push_back(prev);

            coordinate_type p = geometry::perimeter(triangle);
            if (p > m_zero)
            {
                coordinate_type a = abs(geometry::area(triangle));
                coordinate_type prop1 = a / p;
                coordinate_type prop2 = d1 / p;

                bool remove = prop1 < m_area_div_peri
                    && prop2 < m_dist_div_peri
                    && a < m_area_limit;

                /*
                {
                    coordinate_type d2 = geometry::distance(prev, next);
                    std::cout << std::endl;
                    std::cout << "Distance1: "  << d1 << std::endl;
                    std::cout << "Distance2: "  << d2 << std::endl;
                    std::cout << "Area:      "  << a << std::endl;
                    std::cout << "Perimeter: "  << p << std::endl;
                    std::cout << "Prop1:     "  << prop1 << std::endl;
                    std::cout << "Prop2:     "  << prop2 << std::endl;
                    std::cout << "Remove:    "  << (remove ? "true" : "false") << std::endl;
                }
                */

                return remove;

            }
        }
        return false;
    }
};



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_EXTENSIONS_ALGORITHMS_REMOVE_SPIKES_HPP
