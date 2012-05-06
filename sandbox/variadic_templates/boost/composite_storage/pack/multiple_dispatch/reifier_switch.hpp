//
#ifndef BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_SWITCH_HPP_INCLUDED
#define BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_SWITCH_HPP_INCLUDED
//  (C) Copyright Larry Evans 2010.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
#include <boost/composite_storage/pack/multiple_dispatch/reifier_indexed_base.hpp>

namespace boost
{
namespace composite_storage
{
namespace pack
{
namespace multiple_dispatch
{

  template
  < typename ReifyApply
  , typename ArgsConcreteAbstract
  >
struct reifier_switch
: reifier_indexed_base
  < ReifyApply
  , ArgsConcreteAbstract
  >
  /**@brief
   *  Uses switch statment (in functor_indexed::apply)
   *  to convert "abstract" head of an ArgsConcreteAbstract to
   *  its "concrete" counterpart, and then call
   *  a ReifyApply with the converted ArgsConcreteAbstract.
   */
{
        typedef
      reifier_indexed_base
      < ReifyApply
      , ArgsConcreteAbstract
      >
    super_t
    ;
    reifier_switch
      ( ReifyApply const& a_reify
      , ArgsConcreteAbstract* a_ptrs_tar_src
      )
    : super_t
      ( a_reify
      , a_ptrs_tar_src
      )
    {
    }
        typedef 
      typename ReifyApply::result_type 
    result_type
    ;
      result_type
    reify_rest
      ( void
      )const
      /**@brief
       *  Indirectly, calls this->super_t::operator()( mpl::integral_c<case_type,CaseValue> index)
       *  where CaseValue == head_abstract().which().
       */
    {
        return functor_indexed::apply
          ( *this
          , this->head_abstract().which()
          );
    }
};

}//exit namespace multiple_dispatch
}//exit namespace pack

}//exit composite_storage namespace
}//exit boost namespace
#endif
