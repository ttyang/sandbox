/**
 * \file test/classes_ct_08.cpp
 *
 * This file is part of the Mirror library testsuite.
 *
 * Testing class registration and reflection.
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

// MPL_ASSERT
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
//
#include <boost/mirror/meta_class.hpp>
#include <boost/mirror/intrinsic/at.hpp>
//
#include "./namespaces.hpp"
#include "./classes.hpp"
#include "./test.hpp"

template <class MetaAttribute>
void test_offset_of(MetaAttribute*)
{
	MetaAttribute::offset_of();
}

void test_main()
{
	using namespace ::std;
	using namespace ::boost;
	using namespace ::boost::mirror;
	//
	typedef BOOST_MIRRORED_CLASS(::test::H) meta_H;
	//
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 0> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 1> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 2> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 3> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 4> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 5> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 6> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 7> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 8> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_< 9> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<10> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<11> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<12> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<13> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<14> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<15> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<16> >::type*)0);
	test_offset_of((at<meta_H::all_attributes, mpl::int_<17> >::type*)0);
	//
}

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("Mirror: classes compile test 08");
    test->add(BOOST_TEST_CASE(&test_main));
    return test;
}

