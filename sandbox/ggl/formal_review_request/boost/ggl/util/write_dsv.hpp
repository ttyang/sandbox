// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_UTIL_WRITE_DSV_HPP
#define GGL_UTIL_WRITE_DSV_HPP

#include <iostream>
#include <string>

#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>

#include <ggl/algorithms/convert.hpp>

#include <ggl/core/exterior_ring.hpp>
#include <ggl/core/interior_rings.hpp>
#include <ggl/core/ring_type.hpp>
#include <ggl/core/is_multi.hpp>

#include <ggl/geometries/concepts/check.hpp>




namespace ggl
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace dsv {


struct dsv_settings
{
    std::string coordinate_separator;
    std::string point_open;
    std::string point_close;
    std::string point_separator;
    std::string list_open;
    std::string list_close;
    std::string list_separator;

    dsv_settings(std::string const& sep
            , std::string const& open
            , std::string const& close
            , std::string const& psep
            , std::string const& lopen
            , std::string const& lclose
            , std::string const& lsep
            )
        : coordinate_separator(sep)
        , point_open(open)
        , point_close(close)
        , point_separator(psep)
        , list_open(lopen)
        , list_close(lclose)
        , list_separator(lsep)
    {}
};

/*!
\brief Stream coordinate of a point as \ref DSV
*/
template <typename Point, std::size_t Dimension, std::size_t Count>
struct stream_coordinate
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Point const& point,
            dsv_settings const& settings)
    {
        os << (Dimension > 0 ? settings.coordinate_separator : "")
            << get<Dimension>(point);

        stream_coordinate
            <
                Point, Dimension + 1, Count
            >::apply(os, point, settings);
    }
};

template <typename Point, std::size_t Count>
struct stream_coordinate<Point, Count, Count>
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&,
            Point const&,
            dsv_settings const& settings)
    {}
};


/*!
\brief Stream indexed coordinate of a box/segment as \ref DSV
*/
template
<
    typename Geometry,
    std::size_t Index,
    std::size_t Dimension,
    std::size_t Count
>
struct stream_indexed
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << (Dimension > 0 ? settings.coordinate_separator : "")
            << get<Index, Dimension>(geometry);
        stream_indexed
            <
                Geometry, Index, Dimension + 1, Count
            >::apply(os, geometry, settings);
    }
};

template <typename Geometry, std::size_t Index, std::size_t Count>
struct stream_indexed<Geometry, Index, Count, Count>
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&, Geometry const&,
            dsv_settings const& settings)
    {}
};





/*!
\brief Stream points as \ref DSV
*/
template <typename Point>
struct dsv_point
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Point const& p,
            dsv_settings const& settings)
    {
        os << settings.point_open;
        stream_coordinate<Point, 0, dimension<Point>::type::value>::apply(os, p, settings);
        os << settings.point_close;
    }
};

/*!
\brief Stream ranges as DSV
\note policy is used to stream prefix/postfix, enabling derived classes to override this
*/
template <typename Range>
struct dsv_range
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Range const& range,
            dsv_settings const& settings)
    {
        typedef typename boost::range_const_iterator<Range>::type iterator_type;

        bool first = true;

        os << settings.list_open;

        // TODO: check EMPTY here

        for (iterator_type it = boost::begin(range);
            it != boost::end(range);
            ++it)
        {
            os << (first ? "" : settings.point_separator)
                << settings.point_open;

            stream_coordinate
                <
                    point_type, 0, dimension<point_type>::type::value
                >::apply(os, *it, settings);
            os << settings.point_close;

            first = false;
        }

        os << settings.list_close;
    }

private:
    typedef typename boost::range_value<Range>::type point_type;
};

/*!
\brief Stream sequence of points as DSV-part, e.g. (1 2),(3 4)
\note Used in polygon, all multi-geometries
*/





template <typename Polygon>
struct dsv_poly
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Polygon const& poly,
                dsv_settings const& settings)
    {
        typedef typename ring_type<Polygon>::type ring;
        typedef typename boost::range_const_iterator
            <
                typename interior_type<Polygon>::type
            >::type iterator_type;

        os << settings.list_open;

        dsv_range<ring>::apply(os, exterior_ring(poly), settings);
        for (iterator_type it = boost::begin(interior_rings(poly));
            it != boost::end(interior_rings(poly));
            ++it)
        {
            os << settings.list_separator;
            dsv_range<ring>::apply(os, *it, settings);
        }
        os << settings.list_close;
    }
};

template <typename Geometry, std::size_t Index>
struct dsv_per_index
{
    typedef typename point_type<Geometry>::type point_type;

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << settings.point_open;
        stream_indexed
            <
                Geometry, Index, 0, dimension<Geometry>::type::value
            >::apply(os, geometry, settings);
        os << settings.point_close;
    }
};


template <typename Geometry>
struct dsv_indexed
{
    typedef typename point_type<Geometry>::type point_type;

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << settings.list_open;
        dsv_per_index<Geometry, 0>::apply(os, geometry, settings);
        os << settings.point_separator;
        dsv_per_index<Geometry, 1>::apply(os, geometry, settings);
        os << settings.list_close;
    }
};

}} // namespace detail::dsv
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

template <typename Tag, bool IsMulti, typename Geometry>
struct dsv {};


template <typename Point>
struct dsv<point_tag, false, Point>
    : detail::dsv::dsv_point<Point>
{};


template <typename Linestring>
struct dsv<linestring_tag, false, Linestring>
    : detail::dsv::dsv_range<Linestring>
{};


template <typename Box>
struct dsv<box_tag, false, Box>
    : detail::dsv::dsv_indexed<Box>
{};

template <typename Segment>
struct dsv<segment_tag, false, Segment>
    : detail::dsv::dsv_indexed<Segment>
{};


template <typename Ring>
struct dsv<ring_tag, false, Ring>
    : detail::dsv::dsv_range<Ring>
{};


template <typename Polygon>
struct dsv<polygon_tag, false, Polygon>
    : detail::dsv::dsv_poly<Polygon>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Generic geometry template manipulator class, takes corresponding output class from traits class
\ingroup dsv
\details Stream manipulator, streams geometry classes as \ref DSV streams
\par Example:
Small example showing how to use the dsv class
\dontinclude doxygen_examples.cpp
\skip example_as_dsv_point
\line {
\until }
\note the template parameter must be specified. If that is inconvient, users might use streamdsv
which streams geometries as manipulators, or the object generator make_dsv
*/
template <typename Geometry>
class dsv_manipulator
{
public:

    inline dsv_manipulator(Geometry const& g,
            detail::dsv::dsv_settings const& settings)
        : m_geometry(g)
        , m_settings(settings)
    {}

    template <typename Char, typename Traits>
    inline friend std::basic_ostream<Char, Traits>& operator<<(
            std::basic_ostream<Char, Traits>& os,
            dsv_manipulator const& m)
    {
        dispatch::dsv
            <
                typename tag<Geometry>::type,
                is_multi<Geometry>::type::value,
                Geometry
            >::apply(os, m.m_geometry, m.m_settings);
        os.flush();
        return os;
    }

private:
    Geometry const& m_geometry;
    detail::dsv::dsv_settings m_settings;
};

/*!
\brief Main DSV-streaming function
\ingroup dsv
*/
template <typename Geometry>
inline dsv_manipulator<Geometry> dsv(Geometry const& geometry
    , std::string const& coordinate_separator = ", "
    , std::string const& point_open = "("
    , std::string const& point_close = ")"
    , std::string const& point_separator = ", "
    , std::string const& list_open = "("
    , std::string const& list_close = ")"
    , std::string const& list_separator = ", "
    )
{
    concept::check<const Geometry>();

    return dsv_manipulator<Geometry>(geometry,
        detail::dsv::dsv_settings(coordinate_separator,
            point_open, point_close, point_separator,
            list_open, list_close, list_separator));
}



} // namespace ggl

#endif // GGL_UTIL_WRITE_DSV_HPP
