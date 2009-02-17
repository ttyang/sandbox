#ifndef _PROJECTIONS_URMFPS_HPP
#define _PROJECTIONS_URMFPS_HPP

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

namespace projection
{
	#ifndef DOXYGEN_NO_IMPL
	namespace impl
	{
		namespace urmfps
		{
			static const double C_x = 0.8773826753;
			static const double Cy = 1.139753528477;

			struct par_urmfps
			{
				double n, C_y;
			};

			// template class, using CRTP to implement forward/inverse
			template <typename LL, typename XY, typename PAR>
			struct base_urmfps_spheroid : public base_t_fi<base_urmfps_spheroid<LL, XY, PAR>, LL, XY, PAR>
			{

				typedef typename base_t_fi<base_urmfps_spheroid<LL, XY, PAR>, LL, XY, PAR>::LL_T LL_T;
				typedef typename base_t_fi<base_urmfps_spheroid<LL, XY, PAR>, LL, XY, PAR>::XY_T XY_T;

				par_urmfps m_proj_parm;

				inline base_urmfps_spheroid(const PAR& par)
					: base_t_fi<base_urmfps_spheroid<LL, XY, PAR>, LL, XY, PAR>(*this, par) {}

				inline void fwd(LL_T& lp_lon, LL_T& lp_lat, XY_T& xy_x, XY_T& xy_y) const
				{
					lp_lat = aasin(this->m_proj_parm.n * sin(lp_lat));
					xy_x = C_x * lp_lon * cos(lp_lat);
					xy_y = this->m_proj_parm.C_y * lp_lat;
				}

				inline void inv(XY_T& xy_x, XY_T& xy_y, LL_T& lp_lon, LL_T& lp_lat) const
				{
					xy_y /= this->m_proj_parm.C_y;
					lp_lat = aasin(sin(xy_y) / this->m_proj_parm.n);
					lp_lon = xy_x / (C_x * cos(xy_y));
				}
			};

			template <typename PAR>
			void setup(PAR& par, par_urmfps& proj_parm)
			{
				proj_parm.C_y = Cy / proj_parm.n;
				par.es = 0.;
				// par.inv = s_inverse;
				// par.fwd = s_forward;
			}


			// Urmaev Flat-Polar Sinusoidal
			template <typename PAR>
			void setup_urmfps(PAR& par, par_urmfps& proj_parm)
			{
				if (pj_param(par.params, "tn").i) {
					proj_parm.n = pj_param(par.params, "dn").f;
					if (proj_parm.n <= 0. || proj_parm.n > 1.)
						throw proj_exception(-40);
				} else
					throw proj_exception(-40);
				setup(par, proj_parm);
			}

			// Wagner I (Kavraisky VI)
			template <typename PAR>
			void setup_wag1(PAR& par, par_urmfps& proj_parm)
			{
				proj_parm.n = 0.8660254037844386467637231707;
				setup(par, proj_parm);
			}

		} // namespace urmfps
	} //namespaces impl
	#endif // doxygen

	/*!
		\brief Urmaev Flat-Polar Sinusoidal projection
		\ingroup projections
		\tparam LL latlong point type
		\tparam XY xy point type
		\tparam PAR parameter type
		\par Projection characteristics
		 - Pseudocylindrical
		 - Spheroid
		 - n=
		\par Example
		\image html ex_urmfps.gif
	*/
	template <typename LL, typename XY, typename PAR = parameters>
	struct urmfps_spheroid : public impl::urmfps::base_urmfps_spheroid<LL, XY, PAR>
	{
		inline urmfps_spheroid(const PAR& par) : impl::urmfps::base_urmfps_spheroid<LL, XY, PAR>(par)
		{
			impl::urmfps::setup_urmfps(this->m_par, this->m_proj_parm);
		}
	};

	/*!
		\brief Wagner I (Kavraisky VI) projection
		\ingroup projections
		\tparam LL latlong point type
		\tparam XY xy point type
		\tparam PAR parameter type
		\par Projection characteristics
		 - Pseudocylindrical
		 - Spheroid
		\par Example
		\image html ex_wag1.gif
	*/
	template <typename LL, typename XY, typename PAR = parameters>
	struct wag1_spheroid : public impl::urmfps::base_urmfps_spheroid<LL, XY, PAR>
	{
		inline wag1_spheroid(const PAR& par) : impl::urmfps::base_urmfps_spheroid<LL, XY, PAR>(par)
		{
			impl::urmfps::setup_wag1(this->m_par, this->m_proj_parm);
		}
	};

	#ifndef DOXYGEN_NO_IMPL
	namespace impl
	{

		// Factory entry(s)
		template <typename LL, typename XY, typename PAR>
		class urmfps_entry : public impl::factory_entry<LL, XY, PAR>
		{
			public :
				virtual projection<LL, XY>* create_new(const PAR& par) const
				{
					return new base_v_fi<urmfps_spheroid<LL, XY, PAR>, LL, XY, PAR>(par);
				}
		};

		template <typename LL, typename XY, typename PAR>
		class wag1_entry : public impl::factory_entry<LL, XY, PAR>
		{
			public :
				virtual projection<LL, XY>* create_new(const PAR& par) const
				{
					return new base_v_fi<wag1_spheroid<LL, XY, PAR>, LL, XY, PAR>(par);
				}
		};

		template <typename LL, typename XY, typename PAR>
		inline void urmfps_init(impl::base_factory<LL, XY, PAR>& factory)
		{
			factory.add_to_factory("urmfps", new urmfps_entry<LL, XY, PAR>);
			factory.add_to_factory("wag1", new wag1_entry<LL, XY, PAR>);
		}

	} // namespace impl
	#endif // doxygen

}

#endif // _PROJECTIONS_URMFPS_HPP

