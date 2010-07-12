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

namespace boost {
namespace numeric {
namespace odeint {


/*
 * have to be changed if thrust device_vector or gsl_vector are used
 */
template< class Time >
struct standard_operations
{
	typedef Time time_type;

	struct increment
	{
		time_type m_dt;

		increment( time_type dt ) : m_dt( dt ) { }

		template< class T1 , class T2 >
		void operator()( T1 &t1 , const T2 &t2 ) const
		{
			t1 += m_dt * t2;
		}
	};

	struct scale_sum2
	{
		time_type m_alpha1;
		time_type m_alpha2;

		scale_sum2( time_type alpha1 , time_type alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

		template< class T1 , class T2 , class T3 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3;
		}
	};

	struct scale_sum3
	{
		time_type m_alpha1 , m_alpha2 , m_alpha3;

		scale_sum3( time_type alpha1 , time_type alpha2 , time_type alpha3 )
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

		template< class T1 , class T2 , class T3 , class T4 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
		}
	};

	struct scale_sum4
	{
		time_type m_alpha1 , m_alpha2 , m_alpha3 , m_alpha4;

		scale_sum4( time_type alpha1 , time_type alpha2 , time_type alpha3 , time_type alpha4)
				: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

		template< class T1 , class T2 , class T3 , class T4 , class T5 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
		}
	};

	struct scale_sum5
	{
		time_type m_alpha1 , m_alpha2 , m_alpha3 , m_alpha4 , m_alpha5;

		scale_sum5( time_type alpha1 , time_type alpha2 , time_type alpha3 , time_type alpha4 , time_type alpha5)
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

		template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
		void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6) const
		{
			t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
		}
	};

	struct scale_sum6
	{
		time_type m_alpha1 , m_alpha2 , m_alpha3 , m_alpha4 , m_alpha5 , m_alpha6;

		scale_sum6( time_type alpha1 , time_type alpha2 , time_type alpha3 , time_type alpha4 , time_type alpha5 , time_type alpha6 )
			: m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ){ }

			template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
			void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ,const T7 &t7) const
			{
				t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7;
			}
		};

};


} // odeint
} // numeric
} // boost


#endif //BOOST_BOOST_NUMERIC_ODEINT_STANDARD_OPERATIONS_HPP_INCLUDED
