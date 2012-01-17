
#include <boost/functional/overload.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestOverload
#include <boost/test/unit_test.hpp>
#include <string>

//[test_overload_make_func
template<typename F>
void check(F identity) {
    BOOST_CHECK( identity("abc") == "abc" );
    BOOST_CHECK( identity(123) == 123 );
    BOOST_CHECK( identity(1.23) == 1.23 );
}
//]

//[test_overload_decls
const std::string& identity_s(const std::string& x) { return x; }
int identity_i(int x) { return x; }
double identity_d_impl(double x) { return x; }
boost::function<double (double)> identity_d = identity_d_impl;
//]

BOOST_AUTO_TEST_CASE( test_overload ) {
    //[test_overload_funcs
    BOOST_CHECK( identity_s("abc") == "abc" );
    BOOST_CHECK( identity_i(123) == 123 );
    BOOST_CHECK( identity_d(1.23) == 1.23 );
    //]

    {
        //[test_overload_tpl
        boost::functional::overload<
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
        //[test_overload_make_var
        BOOST_AUTO(identity, boost::functional::make_overload(
                identity_s, identity_i, identity_d));
        BOOST_CHECK( identity("abc") == "abc" );
        BOOST_CHECK( identity(123) == 123 );
        BOOST_CHECK( identity(1.23) == 1.23 );
        //]
    }

    //[test_overload_make_func_call
    check(boost::functional::make_overload(identity_s, identity_i, identity_d));
    //]
}

