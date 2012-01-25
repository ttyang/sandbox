
#include <map>

#define VAR(type, postfix) type var_ ## count

VAR(int, a); // OK.

//[test_var_ok
#include <boost/utility/identity_type.hpp>

VAR(BOOST_IDENTITY_TYPE((std::map<char, int>)), b); // OK.
//]

int main() { return 0; }

