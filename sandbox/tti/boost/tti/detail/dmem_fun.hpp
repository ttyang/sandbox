#if !defined(TTI_DETAIL_MEM_FUN_HPP)
#define TTI_DETAIL_MEM_FUN_HPP

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include "dptmf.hpp"

#if defined(BOOST_NO_NULLPTR)

#define TTI_DETAIL_TRAIT_HAS_MEMBER_FUNCTION(trait,name) \
  template<class T,class C> \
  struct trait \
    { \
    template<T> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type check(helper<&U::name> *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type check(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=sizeof(check<C>(0))==sizeof(::boost::type_traits::yes_type)); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#else // !defined(BOOST_NO_NULLPTR)

#define TTI_DETAIL_TRAIT_HAS_MEMBER_FUNCTION(trait,name) \
  template<class T,class C> \
  struct trait \
    { \
    template<T> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type check(helper<&U::name> *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type check(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=sizeof(check<C>(nullptr))==sizeof(::boost::type_traits::yes_type)); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#endif // defined(BOOST_NO_NULLPTR)

#endif // TTI_DETAIL_MEM_FUN_HPP