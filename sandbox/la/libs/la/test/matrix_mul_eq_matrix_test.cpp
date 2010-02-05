//Copyright (c) 2008-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/la/matrix_mul_eq_matrix.hpp>
#include "test_la_matrix.hpp"
#include "gold.hpp"

namespace
	{
	template <int Dim>
	void
	test()
		{
		using namespace boost::la;
			{
			test_la::matrix<M1,Dim,Dim> x(42,1);
			test_la::matrix<M1,Dim,Dim> const y(42,2);
			test_la::multiply_m(x.b,x.a,y.a);
			x *= y;
			BOOST_TEST_LA_EQ(x.a,x.b);
			}
			{
			test_la::matrix<M1,Dim,Dim> x(42,1);
			test_la::matrix<M2,Dim,Dim> const y(42,2);
			test_la::multiply_m(x.b,x.a,y.a);
			x *= y;
			BOOST_TEST_LA_EQ(x.a,x.b);
			}
		}
	}

int
main()
	{
	test<2>();
	test<3>();
	test<4>();
	test<5>();
    return boost::report_errors();
	}
