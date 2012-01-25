
#include <map>

//[test_var_err
#define VAR(type, postfix) type var_ ## postfix

VAR(int, a);                    // OK.
VAR(std::map<char, int>, b);    // Error.
//]

int main() { return 0; }

