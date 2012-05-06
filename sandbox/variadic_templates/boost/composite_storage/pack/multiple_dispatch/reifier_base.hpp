//
#ifndef BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_BASE_HPP_INCLUDED
#define BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_BASE_HPP_INCLUDED
//  (C) Copyright Larry Evans 2010.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
#include <boost/composite_storage/pack/multiple_dispatch/replace_source_with_target_ptr.hpp>
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
struct reifier_base
;
  template
  < typename ReifyApply
  , typename... HeadConcrete
  , typename HeadAbstract
  , typename... TailAbstract
  >
struct reifier_base
  < ReifyApply
  , ptrs_target_source
    < mpl::package
      < HeadConcrete...
      >
    , HeadAbstract
    , TailAbstract...
    >
  >
  /**@brief
   *  Uses switch statment (in functor_indexed::apply)
   *  to convert HeadAbstract, which should be of type,
   *  a composite_storage<one_of_maybe, _, TailConcrete...>, 
   *  to one of the TailConcretes, and then call
   *  a ReifyApply with the converted ptrs_target_source.
   */
{
        typedef
      HeadAbstract
    head_abstract_t
    ;
      ReifyApply const&
    my_reify
    ;
        typedef
      ptrs_target_source
      < mpl::package
        < HeadConcrete...
        >
      , head_abstract_t
      , TailAbstract...
      >
    now_tar_src_type
    ;
      now_tar_src_type*
    my_tar_src
    ;
    reifier_base
      ( ReifyApply const& a_reify
      , now_tar_src_type* a_ptrs_tar_src
      )
    : my_reify(a_reify)
    , my_tar_src(a_ptrs_tar_src)
    {
    }
      head_abstract_t&
    head_abstract()const
    {
        return my_tar_src->template project
          < sizeof...(HeadConcrete)
          >();
    }
        typedef 
      typename ReifyApply::result_type 
    result_type
    ;
      template
      < typename TailConcrete
      >
      result_type
    push_back_concrete
      ( TailConcrete& a_tail_concrete
      )const
      /**@brief
       *  Casts the head abstract value in the ptrs_target_source
       *  into a TailConcrete value, and
       *  then recurses on remaining abstract args
       *  by calling on my_reify.
       */
    {
            typedef 
          ptrs_target_source
          < mpl::package
            < HeadConcrete...
            , TailConcrete
            >
          , TailAbstract...
          >
        next_tar_src_t;
          next_tar_src_t*
        next_tar_src_p=replace_source_with_target_ptr(my_tar_src,a_tail_concrete);
        return my_reify(next_tar_src_p);
    }
    
};

}//exit namespace multiple_dispatch
}//exit namespace pack

}//exit composite_storage namespace
}//exit boost namespace
#endif
