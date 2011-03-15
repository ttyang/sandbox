
// Test
//#include <libs/assign/v2/test/detail.h>
#include <libs/assign/v2/test/ref.h>
//#include <libs/assign/v2/test/mix.h>
//#include <libs/assign/v2/test/put.h>
//#include <libs/assign/v2/test/utility.h>

// Speed
//#include <fstream>
//#include <libs/assign/v2/speed/put_ref.h>

#include <string>
#include <iostream>
#include <boost/config.hpp>
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>


int main (int argc, char * const argv[])
{

    // Do not put libs/assign/v2/test/unit_testing in this project
    {
        std::string cpp0x = "RVALUE_REFERENCES : ";
        #ifdef BOOST_NO_RVALUE_REFERENCES
        cpp0x += "NO";
        #else
        cpp0x += "YES";
        #endif
        cpp0x += ", VARIADIC_TEMPLATES : ";
        #ifdef BOOST_NO_VARIADIC_TEMPLATES
        cpp0x += "NO";
        #else
        cpp0x += "YES";
        #endif
        cpp0x += ", 0X_HDR_TUPLE : ";
        #ifdef BOOST_NO_0X_HDR_TUPLE
        cpp0x += "NO";
        #else
        cpp0x += "YES";
        #endif
        cpp0x += ", ENABLE_CPP0X : " + std::string(BOOST_ASSIGN_V2_ENABLE_CPP0X ? "YES" : "NO");

        std::cout << cpp0x << std::endl;
    }
    {
        using namespace test_assign_v2;
        //xxx_put::test();
        //xxx_mix::test();
        xxx_ref::test();
        //xxx_utility::test();
    }

    /*
     {
     using namespace speed_assign_v2;
     std::ofstream ofs("results");
     xxx_put_ref::run(ofs);
     }
     */

    return 0;

}
