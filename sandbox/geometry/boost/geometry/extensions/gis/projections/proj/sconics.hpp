#ifndef BOOST_GEOMETRY_PROJECTIONS_SCONICS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SCONICS_HPP

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

#include <boost/concept_check.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry { namespace projection
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace sconics{ 
            static const int EULER = 0;
            static const int MURD1 = 1;
            static const int MURD2 = 2;
            static const int MURD3 = 3;
            static const int PCONIC = 4;
            static const int TISSOT = 5;
            static const int VITK1 = 6;
            static const double EPS10 = 1.e-10;
            static const double EPS = 1e-10;

            struct par_sconics
            {
                double  n;
                double  rho_c;
                double  rho_0;
                double  sig;
                double  c1, c2;
                int     type;
            };
            /* get common factors for simple conics */
            template <typename Parameters>
                inline int
            phi12(Parameters& par, par_sconics& proj_parm, double *del) {
                double p1, p2;
                int err = 0;
            
                if (!pj_param(par.params, "tlat_1").i ||
                    !pj_param(par.params, "tlat_2").i) {
                    err = -41;
                } else {
                    p1 = pj_param(par.params, "rlat_1").f;
                    p2 = pj_param(par.params, "rlat_2").f;
                    *del = 0.5 * (p2 - p1);
                    proj_parm.sig = 0.5 * (p2 + p1);
                    err = (fabs(*del) < EPS || fabs(proj_parm.sig) < EPS) ? -42 : 0;
                    *del = *del;
                }
                return err;
            }

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_sconics_spheroid : public base_t_fi<base_sconics_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_sconics m_proj_parm;

                inline base_sconics_spheroid(const Parameters& par)
                    : base_t_fi<base_sconics_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double rho;
                
                    switch (this->m_proj_parm.type) {
                    case MURD2:
                        rho = this->m_proj_parm.rho_c + tan(this->m_proj_parm.sig - lp_lat);
                        break;
                    case PCONIC:
                        rho = this->m_proj_parm.c2 * (this->m_proj_parm.c1 - tan(lp_lat - this->m_proj_parm.sig));
                        break;
                    default:
                        rho = this->m_proj_parm.rho_c - lp_lat;
                        break;
                    }
                    xy_x = rho * sin( lp_lon *= this->m_proj_parm.n );
                    xy_y = this->m_proj_parm.rho_0 - rho * cos(lp_lon);
                }

                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    double rho;
                
                    rho = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.rho_0 - xy_y);
                    if (this->m_proj_parm.n < 0.) {
                        rho = - rho;
                        xy_x = - xy_x;
                        xy_y = - xy_y;
                    }
                    lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;
                    switch (this->m_proj_parm.type) {
                    case PCONIC:
                        lp_lat = atan(this->m_proj_parm.c1 - rho / this->m_proj_parm.c2) + this->m_proj_parm.sig;
                        break;
                    case MURD2:
                        lp_lat = this->m_proj_parm.sig - atan(rho - this->m_proj_parm.rho_c);
                        break;
                    default:
                        lp_lat = this->m_proj_parm.rho_c - rho;
                    }
                }
            };

            template <typename Parameters>
            void setup(Parameters& par, par_sconics& proj_parm) 
            {
                boost::ignore_unused_variable_warning(par);
                boost::ignore_unused_variable_warning(proj_parm);
                double del, cs;
                int i;
                if( (i = phi12(par, proj_parm, &del)) )
                    throw proj_exception(i);
                switch (proj_parm.type) {
                case TISSOT:
                    proj_parm.n = sin(proj_parm.sig);
                    cs = cos(del);
                    proj_parm.rho_c = proj_parm.n / cs + cs / proj_parm.n;
                    proj_parm.rho_0 = sqrt((proj_parm.rho_c - 2 * sin(par.phi0))/proj_parm.n);
                    break;
                case MURD1:
                    proj_parm.rho_c = sin(del)/(del * tan(proj_parm.sig)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    proj_parm.n = sin(proj_parm.sig);
                    break;
                case MURD2:
                    proj_parm.rho_c = (cs = sqrt(cos(del))) / tan(proj_parm.sig);
                    proj_parm.rho_0 = proj_parm.rho_c + tan(proj_parm.sig - par.phi0);
                    proj_parm.n = sin(proj_parm.sig) * cs;
                    break;
                case MURD3:
                    proj_parm.rho_c = del / (tan(proj_parm.sig) * tan(del)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    proj_parm.n = sin(proj_parm.sig) * sin(del) * tan(del) / (del * del);
                    break;
                case EULER:
                    proj_parm.n = sin(proj_parm.sig) * sin(del) / del;
                    del *= 0.5;
                    proj_parm.rho_c = del / (tan(del) * tan(proj_parm.sig)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    break;
                case PCONIC:
                    proj_parm.n = sin(proj_parm.sig);
                    proj_parm.c2 = cos(del);
                    proj_parm.c1 = 1./tan(proj_parm.sig);
                    if (fabs(del = par.phi0 - proj_parm.sig) - EPS10 >= HALFPI)
                        throw proj_exception(-43);
                    proj_parm.rho_0 = proj_parm.c2 * (proj_parm.c1 - tan(del));
                    break;
                case VITK1:
                    proj_parm.n = (cs = tan(del)) * sin(proj_parm.sig) / del;
                    proj_parm.rho_c = del / (cs * tan(proj_parm.sig)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    break;
                }
                // par.inv = s_inverse;
                // par.fwd = s_forward;
                par.es = 0;
            }


            // Tissot
            template <typename Parameters>
            void setup_tissot(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = TISSOT;
                setup(par, proj_parm);
            }

            // Murdoch I
            template <typename Parameters>
            void setup_murd1(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = MURD1;
                setup(par, proj_parm);
            }

            // Murdoch II
            template <typename Parameters>
            void setup_murd2(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = MURD2;
                setup(par, proj_parm);
            }

            // Murdoch III
            template <typename Parameters>
            void setup_murd3(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = MURD3;
                setup(par, proj_parm);
            }

            // Euler
            template <typename Parameters>
            void setup_euler(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = EULER;
                setup(par, proj_parm);
            }

            // Perspective Conic
            template <typename Parameters>
            void setup_pconic(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = PCONIC;
                setup(par, proj_parm);
            }

            // Vitkovsky I
            template <typename Parameters>
            void setup_vitk1(Parameters& par, par_sconics& proj_parm)
            {
                proj_parm.type = VITK1;
                setup(par, proj_parm);
            }

        }} // namespace detail::sconics
    #endif // doxygen 

    /*!
        \brief Tissot projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_tissot.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct tissot_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline tissot_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_tissot(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Murdoch I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_murd1.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct murd1_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline murd1_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_murd1(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Murdoch II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_murd2.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct murd2_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline murd2_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_murd2(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Murdoch III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_murd3.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct murd3_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline murd3_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_murd3(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Euler projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_euler.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct euler_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline euler_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_euler(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Perspective Conic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_pconic.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct pconic_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline pconic_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_pconic(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Vitkovsky I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - lat_1= and lat_2=
        \par Example
        \image html ex_vitk1.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct vitk1_spheroid : public detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>
    {
        inline vitk1_spheroid(const Parameters& par) : detail::sconics::base_sconics_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::sconics::setup_vitk1(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class tissot_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<tissot_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class murd1_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<murd1_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class murd2_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<murd2_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class murd3_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<murd3_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class euler_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<euler_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class pconic_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<pconic_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class vitk1_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<vitk1_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void sconics_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("tissot", new tissot_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("murd1", new murd1_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("murd2", new murd2_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("murd3", new murd3_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("euler", new euler_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("pconic", new pconic_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("vitk1", new vitk1_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail 
    #endif // doxygen

}}} // namespace boost::geometry::projection

#endif // BOOST_GEOMETRY_PROJECTIONS_SCONICS_HPP

