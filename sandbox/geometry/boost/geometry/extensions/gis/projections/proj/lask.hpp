#ifndef BOOST_GEOMETRY_PROJECTIONS_LASK_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LASK_HPP

// Generic Geometry Library - projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright Barend Gehrels (1995-2009), Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande (2008-2009)
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:
 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry { namespace projection
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace lask{ 
            static const double a10 = 0.975534;
            static const double a12 = -0.119161;
            static const double a32 = -0.0143059;
            static const double a14 = -0.0547009;
            static const double b01 = 1.00384;
            static const double b21 = 0.0802894;
            static const double b03 = 0.0998909;
            static const double b41 = 0.000199025;
            static const double b23 = -0.0285500;
            static const double b05 = -0.0491032;


            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_lask_spheroid : public base_t_f<base_lask_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;


                inline base_lask_spheroid(const Parameters& par)
                    : base_t_f<base_lask_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double l2, p2;
                
                    l2 = lp_lon * lp_lon;
                    p2 = lp_lat * lp_lat;
                    xy_x = lp_lon * (a10 + p2 * (a12 + l2 * a32 + p2 * a14));
                    xy_y = lp_lat * (b01 + l2 * (b21 + p2 * b23 + l2 * b41) +
                        p2 * (b03 + p2 * b05));
                }
            };

            // Laskowski
            template <typename Parameters>
            void setup_lask(Parameters& par)
            {
                // par.fwd = s_forward;
                // par.inv = 0;
                par.es = 0.;
            }

        }} // namespace detail::lask
    #endif // doxygen 

    /*!
        \brief Laskowski projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_lask.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct lask_spheroid : public detail::lask::base_lask_spheroid<Geographic, Cartesian, Parameters>
    {
        inline lask_spheroid(const Parameters& par) : detail::lask::base_lask_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::lask::setup_lask(this->m_par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class lask_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<lask_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void lask_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("lask", new lask_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail 
    #endif // doxygen

}}} // namespace boost::geometry::projection

#endif // BOOST_GEOMETRY_PROJECTIONS_LASK_HPP

