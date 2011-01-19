/*
 boost header: BOOST_NUMERIC_ODEINT/standard_operations.hpp

 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky
 Copyright 2009 Andre Bergner

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_BOOST_NUMERIC_ODEINT_STANDARD_OPERATIONS_HPP_INCLUDED
#define BOOST_BOOST_NUMERIC_ODEINT_STANDARD_OPERATIONS_HPP_INCLUDED

#include <algorithm> // for std::max

namespace boost {
namespace numeric {
namespace odeint {


/*
 * have to be changed if thrust device_vector or gsl_vector are used
 */
struct standard_operations
{

	template< class Fac1 , class Fac2 >
	struct scale_sum2
	{
		const Fac1 m_alpha1;
		const Fac2 m_alpha2;

		scale_sum2( const Fac1 &alpha1 , const Fac2 &alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

		template< class T1 , class T2 , class T3 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3;
		}
	};


	template< class Fac1 , class Fac2 , class Fac3 >
	struct scale_sum3
	{
		const Fac1 m_alpha1;
		const Fac2 m_alpha2;
		const Fac3 m_alpha3;

		scale_sum3( const Fac1 &alpha1 , const Fac2 &alpha2 , const Fac3 &alpha3 )
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

		template< class T1 , class T2 , class T3 , class T4 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
		}
	};


	template< class Fac1 , class Fac2 , class Fac3 , class Fac4 >
	struct scale_sum4
	{
		const Fac1 m_alpha1;
		const Fac2 m_alpha2;
		const Fac3 m_alpha3;
		const Fac4 m_alpha4;

		scale_sum4( const Fac1 &alpha1 , const Fac2 &alpha2 , const Fac3 &alpha3 , const Fac4 &alpha4 )
				: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

		template< class T1 , class T2 , class T3 , class T4 , class T5 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
		}
	};


	template< class Fac1 , class Fac2 , class Fac3 , class Fac4 , class Fac5 >
	struct scale_sum5
	{
		const Fac1 m_alpha1;
		const Fac2 m_alpha2;
		const Fac3 m_alpha3;
		const Fac4 m_alpha4;
		const Fac5 m_alpha5;

		scale_sum5( const Fac1 &alpha1 , const Fac2 &alpha2 , const Fac3 &alpha3 , const Fac4 &alpha4 , const Fac5 &alpha5 )
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

		template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
		}
	};


	template< class Fac1 , class Fac2 , class Fac3 , class Fac4 , class Fac5 , class Fac6 >
	struct scale_sum6
	{
		const Fac1 m_alpha1;
		const Fac2 m_alpha2;
		const Fac3 m_alpha3;
		const Fac4 m_alpha4;
		const Fac5 m_alpha5;
		const Fac6 m_alpha6;

		scale_sum6( const Fac1 &alpha1 , const Fac2 &alpha2 , const Fac3 &alpha3 , const Fac4 &alpha4 , const Fac5 &alpha5 , const Fac6 &alpha6 )
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ){ }

		template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ,const T7 &t7) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7;
		}
	};


	template< class Fac1 , class Fac2 , class Fac3 , class Fac4 , class Fac5 , class Fac6 , class Fac7 >
	struct scale_sum7
	{
		const Fac1 m_alpha1;
		const Fac2 m_alpha2;
		const Fac3 m_alpha3;
		const Fac4 m_alpha4;
		const Fac5 m_alpha5;
		const Fac6 m_alpha6;
		const Fac7 m_alpha7;

		scale_sum7( const Fac1 &alpha1 , const Fac2 &alpha2 , const Fac3 &alpha3 , const Fac4 &alpha4 ,
				    const Fac5 &alpha5 , const Fac6 &alpha6 , const Fac7 &alpha7 )
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }

		template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 ) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8;
		}
	};


	template< class Fac1 , class Fac2 >
	static scale_sum2< Fac1 , Fac2 > make_scale_sum2( const Fac1 &alpha1 , const Fac2 &alpha2 )
	{
		return scale_sum2< Fac1 , Fac2 >( alpha1 , alpha2 );
	}








	template< class Fac1 >
	struct rel_error
	{
		const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

		rel_error( const Fac1 &eps_abs , const Fac1 &eps_rel , const Fac1 &a_x , const Fac1 &a_dxdt )
			: m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }


		template< class T1 , class T2 , class T3 >
		void operator()( const T1 &t1 , const T2 &t2 , T3 &t3 ) const
		{
			using std::abs;
			t3 = abs( t3 ) / ( m_eps_abs + m_eps_rel * ( m_a_x * abs( t1 ) + m_a_dxdt * abs( t2 ) ) );
		}

	};


	/* ToDo : this is a reduction-operation so it needs 2 arguments for usage in reduce() functions,
	 * but for vector spaces only one argument should be supplied - this should be rethought in details.
	 */
	template< class Fac1 >
	struct maximum
	{
		template< class T1 , class T2 >
		Fac1 operator()( const T1 &t1 , const T2 &t2 ) const
		{
			using std::max;
			return max( t1 , t2 );
		}

		template< class T >
		Fac1 operator()( const T &t1 ) const
		{ // for the vector space algebra
			return max( t1 );
		}
	};


};


} // odeint
} // numeric
} // boost


#endif //BOOST_BOOST_NUMERIC_ODEINT_STANDARD_OPERATIONS_HPP_INCLUDED
