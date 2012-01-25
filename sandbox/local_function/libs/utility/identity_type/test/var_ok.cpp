
#include <map>

#define VAR(type, n) type var ## n

VAR( int, 1 ); // OK.

//[var_typedef
typedef std::map<int, char> map_type;
VAR( map_type, 3 ); // OK.
//]

//[var_ok
#include <boost/utility/identity_type.hpp>

VAR( BOOST_IDENTITY_TYPE((std::map<int, char>)), 4 ); // OK.
//]

int main() { return 0; }

