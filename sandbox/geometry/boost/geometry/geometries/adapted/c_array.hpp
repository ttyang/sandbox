// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Bruno Lalande 2008, 2009
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_C_ARRAY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_C_ARRAY_HPP

#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// Create class and specialization to indicate the tag
// for normal cases and the case that the type of the c-array is arithmetic
template <bool>
struct c_array_tag
{
    typedef geometry_not_recognized_tag type;
};


template <>
struct c_array_tag<true>
{
    typedef point_tag type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Assign the point-tag, preventing arrays of points getting a point-tag
template <typename CoordinateType, std::size_t DimensionCount>
struct tag<CoordinateType[DimensionCount]>
    : detail::c_array_tag<boost::is_arithmetic<CoordinateType>::value> {};


template <typename CoordinateType, std::size_t DimensionCount>
struct coordinate_type<CoordinateType[DimensionCount]>
{
    typedef CoordinateType type;
};


template <typename CoordinateType, std::size_t DimensionCount>
struct dimension<CoordinateType[DimensionCount]>: boost::mpl::int_<DimensionCount> {};


template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct access<CoordinateType[DimensionCount], Dimension>
{
    static inline CoordinateType get(const CoordinateType p[DimensionCount])
    {
        return p[Dimension];
    }

    static inline void set(CoordinateType p[DimensionCount],
        CoordinateType const& value)
    {
        p[Dimension] = value;
    }
};

// The library user has
// 1) either to specify the coordinate system
// 2) or include <boost/geometry/geometries/adapted/c_array_@.hpp> where @=cartesian,geographic,...

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_C_ARRAY_HPP
