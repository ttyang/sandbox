#ifndef BOOST_GEOMETRY_PROJECTIONS_WINK2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WINK2_HPP

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
    namespace detail { namespace wink2{ 
            static const int MAX_ITER = 10;
            static const double LOOP_TOL = 1e-7;
            static const double TWO_D_PI = 0.636619772367581343;

            struct par_wink2
            {
                double    cosphi1;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_wink2_spheroid : public base_t_f<base_wink2_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_wink2 m_proj_parm;

                inline base_wink2_spheroid(const Parameters& par)
                    : base_t_f<base_wink2_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double k, V;
                    int i;
                
                    xy_y = lp_lat * TWO_D_PI;
                    k = PI * sin(lp_lat);
                    lp_lat *= 1.8;
                    for (i = MAX_ITER; i ; --i) {
                        lp_lat -= V = (lp_lat + sin(lp_lat) - k) /
                            (1. + cos(lp_lat));
                        if (fabs(V) < LOOP_TOL)
                            break;
                    }
                    if (!i)
                        lp_lat = (lp_lat < 0.) ? -HALFPI : HALFPI;
                    else
                        lp_lat *= 0.5;
                    xy_x = 0.5 * lp_lon * (cos(lp_lat) + this->m_proj_parm.cosphi1);
                    xy_y = FORTPI * (sin(lp_lat) + xy_y);
                }
            };

            // Winkel II
            template <typename Parameters>
            void setup_wink2(Parameters& par, par_wink2& proj_parm)
            {
                proj_parm.cosphi1 = cos(pj_param(par.params, "rlat_1").f);
                par.es = 0.;
                // par.inv = 0;
                // par.fwd = s_forward;
            }

        }} // namespace detail::wink2
    #endif // doxygen 

    /*!
        \brief Winkel II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - no inverse
         - lat_1=
        \par Example
        \image html ex_wink2.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct wink2_spheroid : public detail::wink2::base_wink2_spheroid<Geographic, Cartesian, Parameters>
    {
        inline wink2_spheroid(const Parameters& par) : detail::wink2::base_wink2_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::wink2::setup_wink2(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class wink2_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<wink2_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void wink2_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("wink2", new wink2_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail 
    #endif // doxygen

}}} // namespace boost::geometry::projection

#endif // BOOST_GEOMETRY_PROJECTIONS_WINK2_HPP

