#include <iostream>
#define BOOST_ASSIGN_CHECK_EQUAL(a,b) BOOST_ASSERT(a==b)
#include <boost/assign/auto_size/check/ref_list_of.hpp>
#include <boost/assign/auto_size/check/ref_csv.hpp>
#undef BOOST_ASSIGN_CHECK_EQUAL
#include <libs/assign/example/chain.h>

int main (int argc, char * const argv[]) {

    boost::assign::detail::auto_size::check_ref_list_of<int>();
    std::cout << "check_ref_list_of : ok" << std::endl;
    //boost::assign::detail::auto_size::check_ref_csv<int>();
    //std::cout << "check_ref_csv : ok" << std::endl;

    example_chain(std::cout);

    return 0;

}
