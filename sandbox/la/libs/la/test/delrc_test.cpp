//Copyright (c) 2008-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/la/delrc.hpp>
#include <boost/la/matrix_mul_eq_scalar.hpp>
#include <boost/la/array_matrix_traits.hpp>
#include <boost/la/matrix_assign.hpp>
#include "test_la.hpp"
#include "test_la_matrix.hpp"
#include "gold.hpp"

namespace
	{
	template <int Rows,int Cols,int Row,int Col>
	void
	test()
		{
		using namespace boost::la;
		test_la::matrix<M1,Rows,Cols> x(42,1);
		float r1[Rows-1][Cols-1];
		for( int i=0; i!=Rows-1; ++i )
			for( int j=0; j!=Cols-1; ++j )
				r1[i][j]=x.a[i+(i>=Row)][j+(j>=Col)];
		float r2[Rows-1][Cols-1];
		assign(r2,x|delrc<Row,Col>());
		BOOST_TEST_LA_EQ(r1,r2);
		x|delrc<Row,Col>() *= 2;
		for( int i=0; i!=Rows-1; ++i )
			for( int j=0; j!=Cols-1; ++j )
				r1[i][j]=x.a[i+(i>=Row)][j+(j>=Col)];
		assign(r2,x|delrc<Row,Col>());
		BOOST_TEST_LA_EQ(r1,r2);
		}
	}

int
main()
	{
	test<2,2,0,0>();
	test<2,2,0,1>();
	test<2,2,1,0>();
	test<2,2,1,1>();

	test<3,3,0,0>();
	test<3,3,0,1>();
	test<3,3,0,2>();
	test<3,3,1,0>();
	test<3,3,1,1>();
	test<3,3,1,2>();
	test<3,3,2,0>();
	test<3,3,2,1>();
	test<3,3,2,2>();

	test<4,4,0,0>();
	test<4,4,0,1>();
	test<4,4,0,2>();
	test<4,4,0,3>();
	test<4,4,1,0>();
	test<4,4,1,1>();
	test<4,4,1,2>();
	test<4,4,1,3>();
	test<4,4,2,0>();
	test<4,4,2,1>();
	test<4,4,2,2>();
	test<4,4,2,3>();
	test<4,4,3,0>();
	test<4,4,3,1>();
	test<4,4,3,2>();
	test<4,4,3,3>();

	test<5,5,0,0>();
	test<5,5,0,1>();
	test<5,5,0,2>();
	test<5,5,0,3>();
	test<5,5,0,4>();
	test<5,5,1,0>();
	test<5,5,1,1>();
	test<5,5,1,2>();
	test<5,5,1,3>();
	test<5,5,1,4>();
	test<5,5,2,0>();
	test<5,5,2,1>();
	test<5,5,2,2>();
	test<5,5,2,3>();
	test<5,5,2,4>();
	test<5,5,3,0>();
	test<5,5,3,1>();
	test<5,5,3,2>();
	test<5,5,3,3>();
	test<5,5,3,4>();
	test<5,5,4,0>();
	test<5,5,4,1>();
	test<5,5,4,2>();
	test<5,5,4,3>();
	test<5,5,4,4>();
	return boost::report_errors();
	}
