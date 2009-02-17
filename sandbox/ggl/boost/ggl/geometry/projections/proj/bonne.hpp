#ifndef _PROJECTIONS_BONNE_HPP
#define _PROJECTIONS_BONNE_HPP

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

#include <geometry/projections/impl/base_static.hpp>
#include <geometry/projections/impl/base_dynamic.hpp>
#include <geometry/projections/impl/projects.hpp>
#include <geometry/projections/impl/factory_entry.hpp>
#include <geometry/projections/impl/pj_mlfn.hpp>

namespace projection
{
	#ifndef DOXYGEN_NO_IMPL
	namespace impl
	{
		namespace bonne
		{
			static const double EPS10 = 1e-10;

			struct par_bonne
			{
				double phi1;
				double cphi1;
				double am1;
				double m1;
				double en[EN_SIZE];
			};

			// template class, using CRTP to implement forward/inverse
			template <typename LL, typename XY, typename PAR>
			struct base_bonne_ellipsoid : public base_t_fi<base_bonne_ellipsoid<LL, XY, PAR>, LL, XY, PAR>
			{

				typedef typename base_t_fi<base_bonne_ellipsoid<LL, XY, PAR>, LL, XY, PAR>::LL_T LL_T;
				typedef typename base_t_fi<base_bonne_ellipsoid<LL, XY, PAR>, LL, XY, PAR>::XY_T XY_T;

				par_bonne m_proj_parm;

				inline base_bonne_ellipsoid(const PAR& par)
					: base_t_fi<base_bonne_ellipsoid<LL, XY, PAR>, LL, XY, PAR>(*this, par) {}

				inline void fwd(LL_T& lp_lon, LL_T& lp_lat, XY_T& xy_x, XY_T& xy_y) const
				{
					double rh, E, c;

					rh = this->m_proj_parm.am1 + this->m_proj_parm.m1 - pj_mlfn(lp_lat, E = sin(lp_lat), c = cos(lp_lat), this->m_proj_parm.en);
					E = c * lp_lon / (rh * sqrt(1. - this->m_par.es * E * E));
					xy_x = rh * sin(E);
					xy_y = this->m_proj_parm.am1 - rh * cos(E);
				}

				inline void inv(XY_T& xy_x, XY_T& xy_y, LL_T& lp_lon, LL_T& lp_lat) const
				{
					double s, rh;

					rh = hypot(xy_x, xy_y = this->m_proj_parm.am1 - xy_y);
					lp_lat = pj_inv_mlfn(this->m_proj_parm.am1 + this->m_proj_parm.m1 - rh, this->m_par.es, this->m_proj_parm.en);
					if ((s = fabs(lp_lat)) < HALFPI) {
						s = sin(lp_lat);
						lp_lon = rh * atan2(xy_x, xy_y) *
						   sqrt(1. - this->m_par.es * s * s) / cos(lp_lat);
					} else if (fabs(s - HALFPI) <= EPS10)
						lp_lon = 0.;
					else throw proj_exception();;
				}
			};

			// template class, using CRTP to implement forward/inverse
			template <typename LL, typename XY, typename PAR>
			struct base_bonne_spheroid : public base_t_fi<base_bonne_spheroid<LL, XY, PAR>, LL, XY, PAR>
			{

				typedef typename base_t_fi<base_bonne_spheroid<LL, XY, PAR>, LL, XY, PAR>::LL_T LL_T;
				typedef typename base_t_fi<base_bonne_spheroid<LL, XY, PAR>, LL, XY, PAR>::XY_T XY_T;

				par_bonne m_proj_parm;

				inline base_bonne_spheroid(const PAR& par)
					: base_t_fi<base_bonne_spheroid<LL, XY, PAR>, LL, XY, PAR>(*this, par) {}

				inline void fwd(LL_T& lp_lon, LL_T& lp_lat, XY_T& xy_x, XY_T& xy_y) const
				{
					double E, rh;

					rh = this->m_proj_parm.cphi1 + this->m_proj_parm.phi1 - lp_lat;
					if (fabs(rh) > EPS10) {
						xy_x = rh * sin(E = lp_lon * cos(lp_lat) / rh);
						xy_y = this->m_proj_parm.cphi1 - rh * cos(E);
					} else
						xy_x = xy_y = 0.;
				}

				inline void inv(XY_T& xy_x, XY_T& xy_y, LL_T& lp_lon, LL_T& lp_lat) const
				{
					double rh;

					rh = hypot(xy_x, xy_y = this->m_proj_parm.cphi1 - xy_y);
					lp_lat = this->m_proj_parm.cphi1 + this->m_proj_parm.phi1 - rh;
					if (fabs(lp_lat) > HALFPI) throw proj_exception();;
					if (fabs(fabs(lp_lat) - HALFPI) <= EPS10)
						lp_lon = 0.;
					else
						lp_lon = rh * atan2(xy_x, xy_y) / cos(lp_lat);
				}
			};

			// Bonne (Werner lat_1=90)
			template <typename PAR>
			void setup_bonne(PAR& par, par_bonne& proj_parm)
			{
				double c;
				proj_parm.phi1 = pj_param(par.params, "rlat_1").f;
				if (fabs(proj_parm.phi1) < EPS10) throw proj_exception(-23);
				if (par.es) {
					pj_enfn(par.es, proj_parm.en);
					proj_parm.m1 = pj_mlfn(proj_parm.phi1, proj_parm.am1 = sin(proj_parm.phi1),
						c = cos(proj_parm.phi1), proj_parm.en);
					proj_parm.am1 = c / (sqrt(1. - par.es * proj_parm.am1 * proj_parm.am1) * proj_parm.am1);
				// par.inv = e_inverse;
				// par.fwd = e_forward;
				} else {
					if (fabs(proj_parm.phi1) + EPS10 >= HALFPI)
						proj_parm.cphi1 = 0.;
					else
						proj_parm.cphi1 = 1. / tan(proj_parm.phi1);
				// par.inv = s_inverse;
				// par.fwd = s_forward;
				}
			}

		} // namespace bonne
	} //namespaces impl
	#endif // doxygen

	/*!
		\brief Bonne (Werner lat_1=90) projection
		\ingroup projections
		\tparam LL latlong point type
		\tparam XY xy point type
		\tparam PAR parameter type
		\par Projection characteristics
		 - Conic
		 - Spheroid
		 - Ellipsoid
		 - lat_1=
		\par Example
		\image html ex_bonne.gif
	*/
	template <typename LL, typename XY, typename PAR = parameters>
	struct bonne_ellipsoid : public impl::bonne::base_bonne_ellipsoid<LL, XY, PAR>
	{
		inline bonne_ellipsoid(const PAR& par) : impl::bonne::base_bonne_ellipsoid<LL, XY, PAR>(par)
		{
			impl::bonne::setup_bonne(this->m_par, this->m_proj_parm);
		}
	};

	/*!
		\brief Bonne (Werner lat_1=90) projection
		\ingroup projections
		\tparam LL latlong point type
		\tparam XY xy point type
		\tparam PAR parameter type
		\par Projection characteristics
		 - Conic
		 - Spheroid
		 - Ellipsoid
		 - lat_1=
		\par Example
		\image html ex_bonne.gif
	*/
	template <typename LL, typename XY, typename PAR = parameters>
	struct bonne_spheroid : public impl::bonne::base_bonne_spheroid<LL, XY, PAR>
	{
		inline bonne_spheroid(const PAR& par) : impl::bonne::base_bonne_spheroid<LL, XY, PAR>(par)
		{
			impl::bonne::setup_bonne(this->m_par, this->m_proj_parm);
		}
	};

	#ifndef DOXYGEN_NO_IMPL
	namespace impl
	{

		// Factory entry(s)
		template <typename LL, typename XY, typename PAR>
		class bonne_entry : public impl::factory_entry<LL, XY, PAR>
		{
			public :
				virtual projection<LL, XY>* create_new(const PAR& par) const
				{
					if (par.es)
						return new base_v_fi<bonne_ellipsoid<LL, XY, PAR>, LL, XY, PAR>(par);
					else
						return new base_v_fi<bonne_spheroid<LL, XY, PAR>, LL, XY, PAR>(par);
				}
		};

		template <typename LL, typename XY, typename PAR>
		inline void bonne_init(impl::base_factory<LL, XY, PAR>& factory)
		{
			factory.add_to_factory("bonne", new bonne_entry<LL, XY, PAR>);
		}

	} // namespace impl
	#endif // doxygen

}

#endif // _PROJECTIONS_BONNE_HPP

