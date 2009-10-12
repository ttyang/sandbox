// Generic Geometry Library
//
// Copyright Bruno Lalande 2008, 2009
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef GGL_CORE_RADIUS_HPP
#define GGL_CORE_RADIUS_HPP


#include <cstddef>


#include <boost/type_traits/remove_const.hpp>


#include <ggl/core/tag.hpp>


namespace ggl {

namespace traits {

/*!
    \brief Traits class to get/set radius of a circle/sphere/(ellipse)
    \details the radius access meta-functions give read/write access to the radius of a circle or a sphere,
    or to the major/minor axis or an ellipse, or to one of the 3 equatorial radii of an ellipsoid.

    It should be specialized per geometry, in namespace core_dispatch. Those specializations should
    forward the call via traits to the geometry class, which could be specified by the user.

    There is a corresponding generic radius_get and radius_set function
    \par Geometries:
        - n-sphere (circle,sphere)
        - upcoming ellipse
    \par Specializations should provide:
        - inline static T get(const G& geometry)
        - inline static void set(G& geometry, const T& radius)
    \ingroup traits
*/
template <typename G, typename T, std::size_t D>
struct radius_access {};


/*!
    \brief Traits class indicating the type (double,float,...) of the radius of a circle or a sphere
    \par Geometries:
        - n-sphere (circle,sphere)
        - upcoming ellipse
    \par Specializations should provide:
        - typedef T type (double,float,int,etc)
    \ingroup traits
*/
template <typename G>
struct radius_type {};

} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename G>
struct radius_type
{
    //typedef core_dispatch_specialization_required type;
};

/*!
    \brief radius access meta-functions, used by concept n-sphere and upcoming ellipse.
*/
template <typename Tag, typename G, typename T, std::size_t D>
struct radius_access
{
    //static inline T get(const G& ) {}
    //static inline void set(G& g, const T& value) {}
};

template <typename S>
struct radius_type<nsphere_tag, S>
{
    typedef typename traits::radius_type<S>::type type;
};

template <typename S, typename T, std::size_t D>
struct radius_access<nsphere_tag, S, T, D>
{
    BOOST_STATIC_ASSERT((D == 0));
    static inline T get(const S& s)
    {
        return traits::radius_access<S, T, D>::get(s);
    }
    static inline void set(S& s, const T& radius)
    {
        traits::radius_access<S, T, D>::set(s, radius);
    }
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


template <typename G>
struct radius_type
{
    typedef typename boost::remove_const<G>::type rconst;
    typedef typename core_dispatch::radius_type<typename tag<G>::type, rconst>::type type;
};

/*!
    \brief Function to get radius
    \return radius of a circle / sphere / ellipse
    \ingroup access
    \param geometry the geometry to get the radius from
    \tparam I index, for circle/sphere always zero, for ellipse major/minor axis,
        for ellipsoid one of the 3 equatorial radii
*/
template <std::size_t I, typename G>
inline typename radius_type<G>::type get_radius(const G& geometry)
{
    typedef typename boost::remove_const<G>::type rconst;

    return core_dispatch::radius_access<typename tag<G>::type, rconst,
           typename radius_type<G>::type, I>::get(geometry);
}

/*!
    \brief Function to set the radius of a circle / sphere / (ellipse)
    \ingroup access
    \tparam I index, for circle/sphere always zero, for ellipse major/minor axis,
        for ellipsoid one of the 3 equatorial radii
    \param geometry the geometry to change
    \param radius the radius to set
*/
template <std::size_t I, typename G>
inline void set_radius(G& geometry, const typename radius_type<G>::type& radius)
{
    typedef typename boost::remove_const<G>::type rconst;

    core_dispatch::radius_access<typename tag<G>::type, G,
        typename radius_type<G>::type, I>::set(geometry, radius);
}


} // namespace ggl


#endif // GGL_RADIUS_HPP
