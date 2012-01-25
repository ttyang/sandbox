
#include <map>

//[var_err
#define VAR(type, n) type var ## n

VAR( int, 1 );                  // OK.
VAR( std::map<int, char>, 2 );  // Error.
//]

int main() { return 0; }

