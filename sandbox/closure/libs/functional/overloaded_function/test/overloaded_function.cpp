
#include <boost/functional/overloaded_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestOverloadedFunction
#include <boost/test/unit_test.hpp>
#include <string>

//[test_make_overloaded_function_check
template<typename F>
void check(F identity) {
    BOOST_CHECK( identity("abc") == "abc" );
    BOOST_CHECK( identity(123) == 123 );
    BOOST_CHECK( identity(1.23) == 1.23 );
}
//]

//[test_overloaded_function_declarations
const std::string& identity_s(const std::string& x) { return x; } // As pointer.

int identity_i_impl(int x) { return x; }
int (&identity_i)(int) = identity_i_impl; // Function reference.

double identity_d_impl(double x) { return x; }
boost::function<double (double)> identity_d = identity_d_impl; // Functor.
//]

BOOST_AUTO_TEST_CASE( test_overloaded_function ) {
    //[test_overloaded_function_calls
    BOOST_CHECK( identity_s("abc") == "abc" );
    BOOST_CHECK( identity_i(123) == 123 );
    BOOST_CHECK( identity_d(1.23) == 1.23 );
    //]

    {
        //[test_overloaded_function
        boost::overloaded_function<
              const std::string& (const std::string&)
            , int (int)
            , double (double)
        > identity(identity_s, identity_i, identity_d);

        BOOST_CHECK( identity("abc") == "abc" );
        BOOST_CHECK( identity(123) == 123 );
        BOOST_CHECK( identity(1.23) == 1.23 );
        //]
    }
    
    {
        //[test_make_overloaded_function
        BOOST_AUTO(identity, boost::make_overloaded_function(
                identity_s, identity_i, identity_d));

        BOOST_CHECK( identity("abc") == "abc" );
        BOOST_CHECK( identity(123) == 123 );
        BOOST_CHECK( identity(1.23) == 1.23 );
        //]
    }

    //[test_make_overloaded_function_call
    check(boost::make_overloaded_function(identity_s, identity_i, identity_d));
    //]
}

