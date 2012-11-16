#ifndef AS_TUPLE_ELEMENT_HPP_INCLUDED
#define AS_TUPLE_ELEMENT_HPP_INCLUDED
//ChangeLog:
//  2012-10-27.1130CST
//    WHAT:
//      Copied following code from parts of the code in
//      https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//    WHY:
//      To enable reuse in other code using #include's.
//
///////////////////////////////////////////////////
#include <functional>
namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // unrefwrap
    template<typename T>
    struct unrefwrap
    {
        typedef T type;
    };

    template<typename T>
    struct unrefwrap<std::reference_wrapper<T> >
    {
        typedef T &type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // as_tuple_element
    template<typename T>
    using as_tuple_element = typename unrefwrap<typename std::decay<T>::type>::type;

}
#endif
