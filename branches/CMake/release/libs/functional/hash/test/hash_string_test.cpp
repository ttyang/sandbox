
// Copyright 2005-2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_STD_INCLUDES
#  include <functional>
#else
#  include <boost/functional/hash.hpp>
#endif

#include <boost/test/minimal.hpp>

#include <boost/limits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <string>

#include "./compile_time.hpp"

void string_tests()
{
    compile_time_tests((std::string*) 0);

    HASH_NAMESPACE::hash<std::string> x1;
    HASH_NAMESPACE::hash<std::string> x2;

    BOOST_CHECK(x1("Hello") == x2(std::string("Hel") + "lo"));
    BOOST_CHECK(x1("") == x2(std::string()));

#if defined(TEST_EXTENSIONS)
    std::string value1;
    std::string value2("Hello");

    BOOST_CHECK(x1(value1) == HASH_NAMESPACE::hash_value(value1));
    BOOST_CHECK(x1(value2) == HASH_NAMESPACE::hash_value(value2));
    BOOST_CHECK(HASH_NAMESPACE::hash_value(value1) ==
            HASH_NAMESPACE::hash_range(value1.begin(), value1.end()));
    BOOST_CHECK(HASH_NAMESPACE::hash_value(value2) ==
            HASH_NAMESPACE::hash_range(value2.begin(), value2.end()));
#endif
}

#if !defined(BOOST_NO_STD_WSTRING)
void wstring_tests()
{
    compile_time_tests((std::wstring*) 0);

    HASH_NAMESPACE::hash<std::wstring> x1;
    HASH_NAMESPACE::hash<std::wstring> x2;

    BOOST_CHECK(x1(L"Hello") == x2(std::wstring(L"Hel") + L"lo"));
    BOOST_CHECK(x1(L"") == x2(std::wstring()));

#if defined(TEST_EXTENSIONS)
    std::wstring value1;
    std::wstring value2(L"Hello");

    BOOST_CHECK(x1(value1) == HASH_NAMESPACE::hash_value(value1));
    BOOST_CHECK(x1(value2) == HASH_NAMESPACE::hash_value(value2));
    BOOST_CHECK(HASH_NAMESPACE::hash_value(value1) ==
            HASH_NAMESPACE::hash_range(value1.begin(), value1.end()));
    BOOST_CHECK(HASH_NAMESPACE::hash_value(value2) ==
            HASH_NAMESPACE::hash_range(value2.begin(), value2.end()));
#endif
}
#endif

int test_main(int, char**)
{
    string_tests();
#if !defined(BOOST_NO_STD_WSTRING)
    wstring_tests();
#endif
    return 0;
}
