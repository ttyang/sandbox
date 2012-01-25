
#include <boost/local_function.hpp>
#include <boost/utility/identity_type.hpp>
#include <boost/config.hpp>
//#define BOOST_TEST_MODULE TestMacroCommas
//#include <boost/test/unit_test.hpp>
#include <map>
#include <string>

std::string cat(const std::string& x, const std::string& y) { return x + y; }

template<typename V, typename K>
struct key_sizeof {
    BOOST_STATIC_CONSTANT(size_t, value = sizeof(K));
};

typedef int sign_t;

//BOOST_AUTO_TEST_CASE( test_macro_commas ) {
int main(void) {
    //[test_macro_commas
    void BOOST_LOCAL_FUNCTION(
        ((const std::map<std::string, size_t>&)) m,
        BOOST_IDENTITY_TYPE((::sign_t)) sign,
        const size_t& factor,
                default (key_sizeof<std::string, size_t>::value),
        const std::string& separator, default cat(":", " ")
    ) {
        // Do something...
    } BOOST_LOCAL_FUNCTION_NAME(f)
    //]

    std::map<std::string, size_t> m;
    ::sign_t sign = -1;
    f(m, sign);
    return 0;
}

