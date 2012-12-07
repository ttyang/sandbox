#ifndef RETURN_ENABLE_IF_DEFAULTS_HPP_INCLUDED
#define RETURN_ENABLE_IF_DEFAULTS_HPP_INCLUDED
//ChangeLog:
//  2012-10-27.1005CST
//    WHAT:
//      Copied following code from parts of the code in
//      https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//    WHY:
//      To enable reuse in other code using #include's.
//
//=====================================================
// C++11 eliminates the need for macros! Oh, wait ...
#define RETURN(...) -> decltype(__VA_ARGS__) { return __VA_ARGS__; }

#include "./ENABLE_IF.hpp"
#include "./DEFAULTS.hpp"

#endif
