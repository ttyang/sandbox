
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

struct this_tester;
BOOST_TYPEOF_REGISTER_TYPE(this_tester) // Register before capture of `this_`.

struct this_tester
{
    void check()
    {
        int target;
        BOOST_SCOPE_EXIT( (&target) (this_) )
        {
            BOOST_CHECK(this_->value_ == target);
        } BOOST_SCOPE_EXIT_END
#if !defined(BOOST_NO_LAMBDAS) && !defined(BOOST_SCOPE_EXIT_CONFIG_NO_CPP11)
        BOOST_SCOPE_EXIT_ALL(&, this)
        {
            BOOST_CHECK(this->value_ == target);
        };
#endif
        value_ = target = 3;
    }
private:
    int value_;
};

void test_this() { this_tester().check(); }

test_suite* init_unit_test_suite( int, char* [] )
{
    framework::master_test_suite().p_name.value = "Unit test for ScopeExit";
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_this ) );
    return 0;
}
