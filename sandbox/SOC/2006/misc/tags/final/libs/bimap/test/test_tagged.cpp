// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// This code may be used under either of the following two licences:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE. OF SUCH DAMAGE.
//
// Or:
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Boost.Test
#include <boost/test/minimal.hpp>

#include <boost/static_assert.hpp>

// Boost.MPL
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>

// Boost.Bimap
#include <boost/bimap/detail/test/check_metadata.hpp>

// Boost.Bimap.Tags
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>
#include <boost/bimap/tags/support/is_tagged.hpp>
#include <boost/bimap/tags/support/overwrite_tagged.hpp>
#include <boost/bimap/tags/support/tag_of.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>
#include <boost/bimap/tags/support/apply_to_value_type.hpp>




BOOST_BIMAP_TEST_STATIC_FUNCTION( test_metafunctions )
{
    using namespace boost::bimap::tags::support;
    using namespace boost::bimap::tags;
    using namespace boost::mpl::placeholders;
    using namespace boost;

    struct tag      {};
    struct value    {};

    // Test apply_to_value_type metafunction
    // tagged<value,tag> ----(add_const<_>)----> tagged<value const,tag>
    typedef tagged< value, tag > ttype;
    typedef apply_to_value_type< add_const<_>,ttype>::type result;
    typedef is_same<tagged<value const,tag>,result> compare;
    BOOST_MPL_ASSERT_MSG(compare::value,tag,(result));
}

struct tag_a {};
struct tag_b {};
struct data  {};

void test_function()
{

    using namespace boost::bimap::tags::support;
    using namespace boost::bimap::tags;
    using boost::is_same;

    typedef tagged< data, tag_a > data_a;
    typedef tagged< data, tag_b > data_b;

    BOOST_CHECK(( is_same< data_a::value_type   , data  >::value ));
    BOOST_CHECK(( is_same< data_a::tag          , tag_a >::value ));

    BOOST_CHECK(( is_same< overwrite_tagged < data_a, tag_b >::type, data_b >::value ));
    BOOST_CHECK(( is_same< default_tagged   < data_a, tag_b >::type, data_a >::value ));
    BOOST_CHECK(( is_same< default_tagged   < data  , tag_b >::type, data_b >::value ));

    BOOST_CHECK(( is_tagged< data   >::value == false ));
    BOOST_CHECK(( is_tagged< data_a >::value == true  ));

    BOOST_CHECK(( is_same< value_type_of<data_a>::type, data  >::value ));
    BOOST_CHECK(( is_same< tag_of       <data_a>::type, tag_a >::value ));

}

int test_main( int, char* [] )
{
    test_function();

    // Test metanfunctions
    BOOST_BIMAP_CALL_TEST_STATIC_FUNCTION( test_metafunctions );

    return 0;
}
