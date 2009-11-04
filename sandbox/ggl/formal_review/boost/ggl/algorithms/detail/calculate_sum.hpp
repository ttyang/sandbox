// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP
#define GGL_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP

namespace ggl
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename ReturnType,
    typename Polygon,
    typename Strategy,
    typename Policy
>
struct calculate_polygon_sum
{
    static inline ReturnType apply(Polygon const& poly, Strategy const& strategy)
    {
        ReturnType sum = Policy::apply(exterior_ring(poly), strategy);

        for (typename boost::range_const_iterator
                <
                    typename interior_type<Polygon>::type
                >::type it = boost::begin(interior_rings(poly));
             it != boost::end(interior_rings(poly));
             ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

} // namespace ggl

#endif // GGL_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP
