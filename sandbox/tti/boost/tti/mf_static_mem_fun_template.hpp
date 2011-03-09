#if !defined(TTI_MF_STATIC_MEM_FUN_TEMPLATE_HPP)
#define TTI_MF_STATIC_MEM_FUN_TEMPLATE_HPP

#include <boost/config.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include "detail/dtself.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

namespace boost
  {
  namespace tti
    {
  
    /// A metafunction which checks whether a static member function template exists within an enclosing type.
    /**

        This metafunction takes its specific types, except for the optional parameters, as nullary metafunctions whose typedef 'type' member is the actual type used.
    
        The metafunction types and return:

          HasStaticMemberFunctionTemplate = a Boost MPL lambda expression using the metafunction generated from the TTI_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE ( or TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE ) macro.<br />
                                            The easiest way to generate the lambda expression is to use a Boost MPL placeholder expression of the form 'metafunction\<_,_\> ( or optionally 'metafunction\<_,_,_\> or ' 'metafunction\<_,_,_,_\> )'.
                                            You can also use the metafunction class generated by the TTI_MTFC_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE ( or TTI_MTFC_TRAIT_HAS_STATIC_MEMBER_FUNCTION_TEMPLATE ) macro.
                                    
          T               = the enclosing type as a nullary metafunction.
          
          R               = the return type of the static member function as a nullary metafunction.
          
          FS              = an optional parameter which is the parameters of the static member function, each as a nullary metafunction, as a boost::mpl forward sequence.
          
          TAG             = an optional parameter which is a boost::function_types tag to apply to the static member function.
      
          returns = 'value' is true if the member function exists within the enclosing type,
                    otherwise 'value' is false.
                          
    */
    template
      <
      class HasStaticMemberFunctionTemplate,
      class T,
      class R,
      class FS = boost::mpl::vector<>,
      class TAG = boost::function_types::null_tag
      >
    struct mf_has_static_member_function_template :
      boost::mpl::apply
        <
        HasStaticMemberFunctionTemplate,
        typename T::type,
        typename R::type,
        typename boost::mpl::transform<FS,detail::tself<boost::mpl::_1> >::type,
        TAG
        >::type
      {
      };
    }
  }
  
#endif // TTI_MF_STATIC_MEM_FUN_TEMPLATE_HPP
