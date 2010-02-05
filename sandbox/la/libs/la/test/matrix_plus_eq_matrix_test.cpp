//Copyright (c) 2008-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/la/matrix_plus_eq_matrix.hpp>
#include "test_la_matrix.hpp"
#include "gold.hpp"

namespace
	{
	template <int Rows,int Cols>
	void
	test()
		{
		using namespace boost::la;
		test_la::matrix<M1,Rows,Cols> x(42,2);
			{
			test_la::matrix<M1,Rows,Cols> const y(42,1);
			test_la::add_m(x.b,x.a,y.a);
			x+=y;
			BOOST_TEST_LA_EQ(x.a,x.b);
			}
			{
			test_la::matrix<M2,Rows,Cols> const y(42,1);
			test_la::add_m(x.b,x.a,y.a);
			x+=y;
			BOOST_TEST_LA_EQ(x.a,x.b);
			}
		}
	}

int
main()
	{
	test<1,2>();
	test<2,1>();
	test<2,2>();
	test<1,3>();
	test<3,1>();
	test<3,3>();
	test<1,4>();
	test<4,1>();
	test<4,4>();
	test<1,5>();
	test<5,1>();
	test<5,5>();
    return boost::report_errors();
	}
