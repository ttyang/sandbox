#if !defined(TTI_DETAIL_COMP_STATIC_MEM_FUN_TEMPLATE_HPP)
#define TTI_DETAIL_COMP_STATIC_MEM_FUN_TEMPLATE_HPP

#include <boost/config.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>

#if defined(BOOST_NO_NULLPTR)

#define TTI_DETAIL_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION_TEMPLATE(trait,name,tplst) \
  template<class T,class Type> \
  struct trait \
    { \
    template<Type *> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type check(helper<&U::template name<BOOST_PP_LIST_ENUM(tplst)> > *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type check(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=sizeof(check<T>(0))==sizeof(::boost::type_traits::yes_type)); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#define TTI_DETAIL_MTFC_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION_TEMPLATE(trait,name,tplst) \
  struct trait \
    { \
    template<class T,class Type> \
    struct apply \
      { \
      template<Type *> \
      struct helper; \
      \
      template<class U> \
      static ::boost::type_traits::yes_type check(helper<&U::template name<BOOST_PP_LIST_ENUM(tplst)> > *); \
      \
      template<class U> \
      static ::boost::type_traits::no_type check(...); \
      \
      BOOST_STATIC_CONSTANT(bool,value=sizeof(check<T>(0))==sizeof(::boost::type_traits::yes_type)); \
      \
      typedef boost::mpl::bool_<value> type; \
      }; \
    }; \
/**/

#else // !defined(BOOST_NO_NULLPTR)

#define TTI_DETAIL_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION_TEMPLATE(trait,name,tplst) \
  template<class T,class Type> \
  struct trait \
    { \
    template<Type *> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type check(helper<&U::template name<BOOST_PP_LIST_ENUM(tplst)> > *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type check(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=sizeof(check<T>(nullptr))==sizeof(::boost::type_traits::yes_type)); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#define TTI_DETAIL_MTFC_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION_TEMPLATE(trait,name,tplst) \
  struct trait \
    { \
    template<class T,class Type> \
    struct apply \
      { \
      template<Type *> \
      struct helper; \
      \
      template<class U> \
      static ::boost::type_traits::yes_type check(helper<&U::template name<BOOST_PP_LIST_ENUM(tplst)> > *); \
      \
      template<class U> \
      static ::boost::type_traits::no_type check(...); \
      \
      BOOST_STATIC_CONSTANT(bool,value=sizeof(check<T>(nullptr))==sizeof(::boost::type_traits::yes_type)); \
      \
      typedef boost::mpl::bool_<value> type; \
      }; \
    }; \
/**/

#endif // defined(BOOST_NO_NULLPTR)

#endif // TTI_DETAIL_COMP_STATIC_MEM_FUN_TEMPLATE_HPP
