#ifndef A_COMPILE_REQUIREMENTS
#error A_COMPILE_REQUIREMENTS
#endif
#ifndef A_SHARED_COMPILE_REQUIREMENTS
#error A_SHARED_COMPILE_REQUIREMENTS
#endif

#ifdef B_COMPILE_REQUIREMENTS
#error B_COMPILE_REQUIREMENTS
#endif
#ifdef B_SHARED_COMPILE_REQUIREMENTS
#error B_SHARED_COMPILE_REQUIREMENTS
#endif

#ifndef C_COMPILE_REQUIREMENTS
#error C_COMPILE_REQUIREMENTS
#endif
#ifndef C_SHARED_COMPILE_REQUIREMENTS
#error C_SHARED_COMPILE_REQUIREMENTS
#endif


#include "a.hpp"
#include "c.hpp"
#include <cassert>
int main(int argc, char**argv)
{
  assert(c_linktype() == "shared");
  assert(a_linktype() == "shared");
}

