//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <cmath> // MSVC #include <math.h>
#include <deque>
#include <list>
#include <vector>
#include <boost/array.hpp>
#include <boost/assign/v2/detail/config/check.hpp>

#include <boost/assign/v2/value/put.hpp>
#include <boost/assign/v2/deque.hpp>
#include <boost/assign/v2/fun.hpp>
#include <boost/function.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/typeof/typeof.hpp>
#include <libs/assign/v2/test/fun.h>

#include <boost/lexical_cast.hpp>

namespace test_assign_v2{
namespace xxx_value{
namespace xxx_fun{

    void test()
    {
        using namespace boost;
        namespace as2 = assign::v2;
        {
        	// (*fp) resolves error C2440 using MSVC
            //[test_value_fun_math
            std::vector<double> exponent;
            typedef double(*fp)(double);
            typedef function<double(double)> f_;
            (
                as2::put( exponent ) % ( as2::_fun = f_( fp(log10) ) )
            )/*<<Equivalent to `as2::put( exponent )( log10( 1000.0 ) )( log10( 10.0 ) )( log10( 10000.0 ) )( log10( 1.0 ) )( log10( 100.0 ) )`>>*/( 1000.0 )( 10.0 )( 10000.0 )( 1.0 )( 100.0 );

            double eps = numeric::bounds<double>::smallest();
            BOOST_ASSIGN_V2_CHECK( fabs( exponent.front() - 3.0 ) < eps );
            BOOST_ASSIGN_V2_CHECK( fabs( exponent.back() - 2.0 ) < eps );
            //]
        }
        {
            //[test_value_fun_recursive
        	using namespace lambda;
            int i = 1, k = 1;
            BOOST_AUTO(
                factorials, (
                    as2::deque<int>( as2::_nil ) % (
                        as2::_fun = ( var(k) *= ( var(i)++ ) )
                    )
                )/*<<Equivalent to `factorials( k *= i++ )` for [^i = 1, ..., 5]>>*/()()()()()
            );

            BOOST_ASSIGN_V2_CHECK( range::equal( factorials, as2::csv_deque( 1, 2, 6, 24, 120 ) ) );
            //]
        }

    }

}// xxx_fun
}// xxx_value
}// test_assign_v2
