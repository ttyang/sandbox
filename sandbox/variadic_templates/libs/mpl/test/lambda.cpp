
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date: 2010/07/31 11:52:44 $
// $Revision: 1.2 $

#include <boost/mpl/logical.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/lambdav.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/mpl/aux_/test.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_float.hpp>

struct my
{
    char a[100];
};

MPL_TEST_CASE()
{
    // !(x == char) && !(x == double) || sizeof(x) > 8
    typedef lambda<
        or_<
              and_<
                    not_< boost::is_same<_1, char> >
                  , not_< boost::is_float<_1> >
                  >
            , greater< sizeof_<_1>, mpl::size_t<8> >
            >
        >::type f;

    MPL_ASSERT_NOT(( apply_wrap<f,char> ));
    MPL_ASSERT_NOT(( apply_wrap<f,double> ));
    MPL_ASSERT(( apply_wrap<f,long> ));
    MPL_ASSERT(( apply_wrap<f,my> ));
}

MPL_TEST_CASE()
{
    // x == y || x == my || sizeof(x) == sizeof(y)
    typedef lambda<
        or_< 
              boost::is_same<_1, _2>
            , boost::is_same<_2, my>
            , equal_to< sizeof_<_1>, sizeof_<_2> >
            >
        >::type f;

    MPL_ASSERT_NOT(( apply_wrap<f,double,char> ));
    MPL_ASSERT_NOT(( apply_wrap<f,my,int> ));
    MPL_ASSERT_NOT(( apply_wrap<f,my,char[99]> ));
    MPL_ASSERT(( apply_wrap<f,int,int> ));
    MPL_ASSERT(( apply_wrap<f,my,my> ));
    MPL_ASSERT(( apply_wrap<f,signed long, unsigned long> ));
}

MPL_TEST_CASE()
{
    // bind <-> lambda interaction
    typedef lambda< less<_1,_2> >::type pred;
    typedef bind< pred, _1, int_<4> > f;
    
    MPL_ASSERT(( apply_wrap< f,int_<3> > ));
}