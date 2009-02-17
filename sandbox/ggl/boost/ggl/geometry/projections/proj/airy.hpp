#ifndef _PROJECTIONS_AIRY_HPP
#define _PROJECTIONS_AIRY_HPP

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
		namespace airy
		{
			static const double EPS = 1.e-10;
			static const int N_POLE = 0;
			static const int S_POLE = 1;
			static const int EQUIT = 2;
			static const int OBLIQ = 3;

			struct par_airy
			{
				double p_halfpi;
				double sinph0;
				double cosph0;
				double Cb;
				int  mode;
				int  no_cut; /* do not cut at hemisphere limit */
			};





			// template class, using CRTP to implement forward/inverse
			template <typename LL, typename XY, typename PAR>
			struct base_airy_spheroid : public base_t_f<base_airy_spheroid<LL, XY, PAR>, LL, XY, PAR>
			{

				typedef typename base_t_f<base_airy_spheroid<LL, XY, PAR>, LL, XY, PAR>::LL_T LL_T;
				typedef typename base_t_f<base_airy_spheroid<LL, XY, PAR>, LL, XY, PAR>::XY_T XY_T;

				par_airy m_proj_parm;

				inline base_airy_spheroid(const PAR& par)
					: base_t_f<base_airy_spheroid<LL, XY, PAR>, LL, XY, PAR>(*this, par) {}

				inline void fwd(LL_T& lp_lon, LL_T& lp_lat, XY_T& xy_x, XY_T& xy_y) const
				{
					double  sinlam, coslam, cosphi, sinphi, t, s, Krho, cosz;

					sinlam = sin(lp_lon);
					coslam = cos(lp_lon);
					switch (this->m_proj_parm.mode) {
					case EQUIT:
					case OBLIQ:
						sinphi = sin(lp_lat);
						cosphi = cos(lp_lat);
						cosz = cosphi * coslam;
						if (this->m_proj_parm.mode == OBLIQ)
							cosz = this->m_proj_parm.sinph0 * sinphi + this->m_proj_parm.cosph0 * cosz;
						if (!this->m_proj_parm.no_cut && cosz < -EPS)
							throw proj_exception();;
						if (fabs(s = 1. - cosz) > EPS) {
							t = 0.5 * (1. + cosz);
							Krho = -log(t)/s - this->m_proj_parm.Cb / t;
						} else
							Krho = 0.5 - this->m_proj_parm.Cb;
						xy_x = Krho * cosphi * sinlam;
						if (this->m_proj_parm.mode == OBLIQ)
							xy_y = Krho * (this->m_proj_parm.cosph0 * sinphi -
								this->m_proj_parm.sinph0 * cosphi * coslam);
						else
							xy_y = Krho * sinphi;
						break;
					case S_POLE:
					case N_POLE:
						lp_lat = fabs(this->m_proj_parm.p_halfpi - lp_lat);
						if (!this->m_proj_parm.no_cut && (lp_lat - EPS) > HALFPI)
							throw proj_exception();;
						if ((lp_lat *= 0.5) > EPS) {
							t = tan(lp_lat);
							Krho = -2.*(log(cos(lp_lat)) / t + t * this->m_proj_parm.Cb);
							xy_x = Krho * sinlam;
							xy_y = Krho * coslam;
							if (this->m_proj_parm.mode == N_POLE)
								xy_y = -xy_y;
						} else
							xy_x = xy_y = 0.;
					}
				}
			};

			// Airy
			template <typename PAR>
			void setup_airy(PAR& par, par_airy& proj_parm)
			{
				double beta;
				proj_parm.no_cut = pj_param(par.params, "bno_cut").i;
				beta = 0.5 * (HALFPI - pj_param(par.params, "rlat_b").f);
				if (fabs(beta) < EPS)
					proj_parm.Cb = -0.5;
				else {
					proj_parm.Cb = 1./tan(beta);
					proj_parm.Cb *= proj_parm.Cb * log(cos(beta));
				}
				if (fabs(fabs(par.phi0) - HALFPI) < EPS)
					if (par.phi0 < 0.) {
						proj_parm.p_halfpi = -HALFPI;
						proj_parm.mode = S_POLE;
					} else {
						proj_parm.p_halfpi =  HALFPI;
						proj_parm.mode = N_POLE;
					}
				else {
					if (fabs(par.phi0) < EPS)
						proj_parm.mode = EQUIT;
					else {
						proj_parm.mode = OBLIQ;
						proj_parm.sinph0 = sin(par.phi0);
						proj_parm.cosph0 = cos(par.phi0);
					}
				}
				// par.fwd = s_forward;
				par.es = 0.;
			}

		} // namespace airy
	} //namespaces impl
	#endif // doxygen

	/*!
		\brief Airy projection
		\ingroup projections
		\tparam LL latlong point type
		\tparam XY xy point type
		\tparam PAR parameter type
		\par Projection characteristics
		 - Miscellaneous
		 - Spheroid
		 - no inverse
		 - no_cut lat_b=
		\par Example
		\image html ex_airy.gif
	*/
	template <typename LL, typename XY, typename PAR = parameters>
	struct airy_spheroid : public impl::airy::base_airy_spheroid<LL, XY, PAR>
	{
		inline airy_spheroid(const PAR& par) : impl::airy::base_airy_spheroid<LL, XY, PAR>(par)
		{
			impl::airy::setup_airy(this->m_par, this->m_proj_parm);
		}
	};

	#ifndef DOXYGEN_NO_IMPL
	namespace impl
	{

		// Factory entry(s)
		template <typename LL, typename XY, typename PAR>
		class airy_entry : public impl::factory_entry<LL, XY, PAR>
		{
			public :
				virtual projection<LL, XY>* create_new(const PAR& par) const
				{
					return new base_v_f<airy_spheroid<LL, XY, PAR>, LL, XY, PAR>(par);
				}
		};

		template <typename LL, typename XY, typename PAR>
		inline void airy_init(impl::base_factory<LL, XY, PAR>& factory)
		{
			factory.add_to_factory("airy", new airy_entry<LL, XY, PAR>);
		}

	} // namespace impl
	#endif // doxygen

}

#endif // _PROJECTIONS_AIRY_HPP

