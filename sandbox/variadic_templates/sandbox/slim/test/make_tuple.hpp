#ifndef MAKE_TUPLE_INCLUDE_HPP
#define MAKE_TUPLE_INCLUDE_HPP
#ifndef TUPLE_TEMPLATED_CTOR
  #define TUPLE_TEMPLATED_CTOR 1
#endif
#ifndef TUPLE_IMPL
  #define TUPLE_IMPL bcon12_horizontal
#endif
#include <boost/preprocessor/stringize.hpp>
#include BOOST_PP_STRINGIZE(tuple_impl.TUPLE_IMPL.hpp)
//Acknowlegements:
//  The following code was adapted from part of the code in:
//    https://github.com/ericniebler/home/blob/master/src/tuple/unrolled_tuple.hpp
//  and repeated here:
//    https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//
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

}//detail namespace

///////////////////////////////////////////////////////////////////////////////
// make_tuple
  template<typename ...T>
    inline
  tuple_bench<detail::as_tuple_element<T>...>
make_tuple(T &&...t)
{
    typedef tuple_bench<detail::as_tuple_element<T>...> tuple_t;
#if TUPLE_TEMPLATED_CTOR == 1
    tuple_t a_tuple(static_cast<T &&>(t)...);
#else
    tuple_t a_tuple;
#endif//TUPLE_TEMPLATED_CTOR == 1
    return a_tuple;
}
#endif
