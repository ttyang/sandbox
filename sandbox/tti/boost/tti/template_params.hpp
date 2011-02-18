#if !defined(TTI_TEMPLATE_PARAMS_HPP)
#define TTI_TEMPLATE_PARAMS_HPP

#include <boost/config.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include "mf_template_params.hpp"
#include "detail/dtemplate_params.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether an inner class template with a particular name and signature exists.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner class template.
    
    tpSeq = a Boost PP sequence which has the class template parameters.
            Each part of the template parameters separated by a comma ( , )
            is put in a separate sequence element.

    returns = a metafunction called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                returns = 'value' is true if the 'name' class template with the signature
                          as defined by the 'tpSeq' exists within the enclosing type,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,tpSeq) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,tpSeq) \
      } \
    template<class T> \
    struct trait : \
      detail::trait<T> \
      { \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction class which tests whether an inner class template with a particular name and signature exists.
/**

    trait = the name of the metafunction class within the tti namespace.
    
    name  = the name of the inner class template.
    
    tpSeq = a Boost PP sequence which has the class template parameters.
            Each part of the template parameters separated by a comma ( , )
            is put in a separate sequence element.

    returns = a metafunction class called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction class's 'apply' metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                returns = 'value' is true if the 'name' class template with the signature
                          as defined by the 'tpSeq' exists within the enclosing type,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,tpSeq) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_MTFC_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,tpSeq) \
      } \
    struct trait \
      { \
      template<class T> \
      struct apply : \
        detail::trait::apply<T> \
        { \
        }; \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction which tests whether an inner class template with a particular name and signature exists.
/**

    name  = the name of the inner class template.
    
    tpSeq = a Boost PP sequence which has the class template parameters.
            Each part of the template parameters separated by a comma ( , )
            is put in a separate sequence element.

    returns = a metafunction called "boost::tti::has_template_check_params_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                returns = 'value' is true if the 'name' class template with the signature
                          as defined by the 'tpSeq' exists within the enclosing type,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(name,tpSeq) \
  BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS \
  ( \
  BOOST_PP_CAT(has_template_check_params_,name), \
  name, \
  tpSeq \
  ) \
/**/

/// Expands to a metafunction class which tests whether an inner class template with a particular name and signature exists.
/**

    name  = the name of the inner class template.
    
    tpSeq = a Boost PP sequence which has the class template parameters.
            Each part of the template parameters separated by a comma ( , )
            is put in a separate sequence element.

    returns = a metafunction class called "boost::tti::mtfc_has_template_check_params_name" where 'name' is the macro parameter.
    
              The metafunction class's 'apply' metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                returns = 'value' is true if the 'name' class template with the signature
                          as defined by the 'tpSeq' exists within the enclosing type,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS(name,tpSeq) \
  BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE_CHECK_PARAMS \
  ( \
  BOOST_PP_CAT(mtfc_has_template_check_params_,name), \
  name, \
  tpSeq \
  ) \
/**/

#endif // TTI_TEMPLATE_PARAMS_HPP