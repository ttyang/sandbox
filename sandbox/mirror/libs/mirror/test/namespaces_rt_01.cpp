/**
 * \file test/namespaces.cpp
 *
 * This file is part of the Mirror library testsuite.
 *
 * Testing namespaces registration and reflection.
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/mirror/traits/reflects_global_scope.hpp>
#include "./namespaces.hpp"
#include "./test.hpp"


void test_main()
{
	using namespace ::std;
	using namespace ::boost;
	using namespace ::boost::mirror;
	//
	//
	// define an alternative name for the ::test namespace meta-data
	typedef BOOST_MIRRORED_NAMESPACE(::test) meta_ns_test;
	typedef BOOST_MIRRORED_NAMESPACE(::test::stuff) meta_ns_test_stuff;
	typedef BOOST_MIRRORED_NAMESPACE(::test::stuff::detail) meta_ns_test_stuff_detail;
	typedef BOOST_MIRRORED_NAMESPACE(::test::feature) meta_ns_test_feature;
	typedef BOOST_MIRRORED_NAMESPACE(::test::feature::detail) meta_ns_test_feature_detail;
	//
	BOOST_CHECK(
		meta_ns_test::base_name() ==
		BOOST_CTS_LIT("test")
	);
	BOOST_CHECK(
		meta_ns_test_stuff::base_name() ==
		BOOST_CTS_LIT("stuff")
	);
	BOOST_CHECK(
		meta_ns_test_stuff_detail::base_name() ==
		BOOST_CTS_LIT("detail")
	);
	BOOST_CHECK(
		meta_ns_test_feature::base_name() ==
		BOOST_CTS_LIT("feature")
	);
	BOOST_CHECK(
		meta_ns_test_feature_detail::base_name() ==
		BOOST_CTS_LIT("detail")
	);
}

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("Mirror: namespaces run-time test 01");
    test->add(BOOST_TEST_CASE(&test_main));
    return test;
}


