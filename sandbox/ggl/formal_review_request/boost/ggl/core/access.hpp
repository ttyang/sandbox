// Generic Geometry Library
//
// Copyright Bruno Lalande 2008, 2009
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_CORE_ACCESS_HPP
#define GGL_CORE_ACCESS_HPP

#include <cstddef>

#include <boost/type_traits/remove_const.hpp>
#include <boost/concept_check.hpp>

#include <ggl/core/coordinate_type.hpp>
#include <ggl/core/point_type.hpp>
#include <ggl/core/tag.hpp>

namespace ggl
{

const int min_corner = 0;
const int max_corner = 1;

namespace traits
{

/*!
    \brief Traits class which gives access (get,set) to points
    \ingroup traits
    \par Geometries:
        - point
    \par Specializations should provide, per Dimension
        - static inline T get(const G&)
        - static inline void set(G&, T const&)
    \tparam Geometry geometry-type
    \tparam Dimension dimension to access
*/
template <typename Geometry, std::size_t Dimension>
struct access {};


/*!
    \brief Traits class defining "get" and "set" to get and set point coordinate values
    \tparam Geometry geometry (box, segment)
    \tparam Index index (min_corner/max_corner for box, 0/1 for segment)
    \tparam Dimension dimension
    \par Geometries:
        - box
        - segment
    \par Specializations should provide:
        - static inline T get(const G&)
        - static inline void set(G&, T const&)
    \ingroup traits
*/
template <typename Geometry, std::size_t Index, std::size_t Dimension>
struct indexed_access {};


/*!
    \brief Traits class, optional, indicating that the std-library should be used
    \details The default geometry (linestring, ring, multi*) follow std:: for
        its modifying operations (push_back, clear, size, resize, reserve, etc)
        If they NOT follow the std:: library they should specialize this traits
        class
    \ingroup traits
    \par Geometries:
        - linestring
        - linear_ring
    \par Specializations should provide:
        - value (defaults to true)
 */
template <typename Geometry>
struct use_std
{
    static const bool value = true;
};



/*!
    \brief Traits class, optional, might be implemented to clear a geometry
    \details If a geometry type should not use the std ".clear()" then it can specialize
    the "use_std" traits class to false, it should then implement (a.o.) clear
    \ingroup traits
    \par Geometries:
        - linestring
        - linear_ring
    \par Specializations should provide:
        - apply
 */
template <typename Geometry>
struct clear
{};



/*!
    \brief Traits class, optional, might be implemented to append a point
    \details If a geometry type should not use the std "push_back" then it can specialize
    the "use_std" traits class to false, it should then implement (a.o.) append_point
    \ingroup traits
    \par Geometries:
        - linestring
        - linear_ring
    \par Specializations should provide:
        - run
 */
template <typename Geometry, typename Point>
struct append_point
{
};





} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template
<
    typename Tag,
    typename Geometry,
    typename
    CoordinateType, std::size_t Dimension
>
struct access
{
    //static inline T get(const G& ) {}
    //static inline void set(G& g, T const& value) {}
};

template
<
    typename Tag,
    typename Geometry,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access
{
    //static inline T get(const G& ) {}
    //static inline void set(G& g, T const& value) {}
};

template <typename Point, typename CoordinateType, std::size_t Dimension>
struct access<point_tag, Point, CoordinateType, Dimension>
{
    static inline CoordinateType get(Point const& point)
    {
        return traits::access<Point, Dimension>::get(point);
    }
    static inline void set(Point& p, CoordinateType const& value)
    {
        traits::access<Point, Dimension>::set(p, value);
    }
};

template
<
    typename Box,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<box_tag, Box, CoordinateType, Index, Dimension>
{
    static inline CoordinateType get(Box const& box)
    {
        return traits::indexed_access<Box, Index, Dimension>::get(box);
    }
    static inline void set(Box& b, CoordinateType const& value)
    {
        traits::indexed_access<Box, Index, Dimension>::set(b, value);
    }
};

template
<
    typename Segment,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<segment_tag, Segment, CoordinateType, Index, Dimension>
{
    static inline CoordinateType get(Segment const& segment)
    {
        return traits::indexed_access<Segment, Index, Dimension>::get(segment);
    }
    static inline void set(Segment& segment, CoordinateType const& value)
    {
        traits::indexed_access<Segment, Index, Dimension>::set(segment, value);
    }
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Two dummy tags to distinguish get/set variants below.
// They don't have to be specified by the user. The functions are distinguished
// by template signature also, but for e.g. GCC this is not enough. So give them
// a different signature.
struct signature_getset_dimension {};
struct signature_getset_index_dimension {};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief get a coordinate value of a point
    \return coordinate value
    \ingroup access
    \tparam D dimension
    \tparam G geometry
    \param geometry geometry to get coordinate value from
    \param dummy does not have to be specified
*/
template <std::size_t D, typename G>
inline typename coordinate_type<G>::type get(const G& geometry,
    detail::signature_getset_dimension* dummy = 0)
{
    boost::ignore_unused_variable_warning(dummy);

    typedef typename boost::remove_const<G>::type ncg_type;

    typedef core_dispatch::access
        <
            typename tag<G>::type,
            ncg_type,
            typename coordinate_type<ncg_type>::type,
            D
        > coord_access_type;

    return coord_access_type::get(geometry);
}


/*!
    \brief assign coordinate value to a point / sphere
    \ingroup access
    \tparam D dimension
    \tparam G geometry
    \param geometry geometry to assign coordinate to
    \param value coordinate value to assign
    \param dummy does not have to be specified
*/
template <std::size_t D, typename G>
inline void set(G& geometry, const typename coordinate_type<G>::type& value,
    detail::signature_getset_dimension* dummy = 0)
{
    boost::ignore_unused_variable_warning(dummy);

    typedef typename boost::remove_const<G>::type ncg_type;

    typedef core_dispatch::access
        <
            typename tag<G>::type,
            ncg_type,
            typename coordinate_type<ncg_type>::type,
            D
        > coord_access_type;

    coord_access_type::set(geometry, value);
}

// Note: doxygen needs a construct to distinguish get/set (like the gcc compiler)

/*!
    \brief get a coordinate value of a box / segment
    \return coordinate value
    \ingroup access
    \tparam I index, for boxes: min_corner or max_corner. For segment: 0 / 1
    \tparam D dimension
    \tparam G geometry
    \param geometry geometry to get coordinate value from
    \param dummy does not have to be specified
*/
template <std::size_t I, std::size_t D, typename G>
inline typename coordinate_type<G>::type get(const G& geometry,
    detail::signature_getset_index_dimension* dummy = 0)
{
    boost::ignore_unused_variable_warning(dummy);

    typedef typename boost::remove_const<G>::type ncg_type;

    typedef core_dispatch::indexed_access
        <
        typename tag<G>::type,
        ncg_type,
        typename coordinate_type<ncg_type>::type,
        I,
        D
        > coord_access_type;

    return coord_access_type::get(geometry);
}

/*!
    \brief assign a coordinate value of a box / segment
    \ingroup access
    \tparam I index, for boxes: min_corner or max_corner. For segment: 0 / 1
    \tparam D dimension
    \tparam G geometry
    \param geometry geometry to assign coordinate to
    \param value coordinate value to assign
    \param dummy does not have to be specified
*/
template <std::size_t I, std::size_t D, typename G>
inline void set(G& geometry, const typename coordinate_type<G>::type& value,
    detail::signature_getset_index_dimension* dummy = 0)
{
    boost::ignore_unused_variable_warning(dummy);

    typedef typename boost::remove_const<G>::type ncg_type;

    typedef core_dispatch::indexed_access
        <
        typename tag<G>::type, ncg_type,
        typename coordinate_type<ncg_type>::type,
        I,
        D
        > coord_access_type;

    coord_access_type::set(geometry, value);
}

} // namespace ggl

#endif // GGL_CORE_ACCESS_HPP
