/*=============================================================
    Boost Overload
    Example - Overview
==============================================================*/

//[ overview_cpp
#include <boost/overload.hpp>

int foo(int a) { return a + 1; };
long bar(int a, int b) { return a + b; };

int main()
{
    boost::overload<int (int ), long (int, int )> functions;
    functions.set(&foo);
    functions.set(&bar);

    assert(functions(1) == 2);
    assert(functions(2, 3) == 5L);
    return 0;
}
//]
