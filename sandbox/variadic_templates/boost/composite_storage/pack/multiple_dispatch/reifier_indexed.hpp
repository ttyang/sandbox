//
#ifndef BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_INDEXED_HPP_INCLUDED
#define BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_INDEXED_HPP_INCLUDED
//  (C) Copyright Larry Evans 2010.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
#include <boost/composite_storage/pack/multiple_dispatch/reifier_base.hpp>
#include <boost/composite_storage/functor_indexed.hpp>

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
struct reifier_indexed
: reifier_base
  < ReifyApply
  , ArgsConcreteAbstract
  >
{
        typedef
      reifier_base
      < ReifyApply
      , ArgsConcreteAbstract
      >
    super_t
    ;
        typedef
      typename super_t::head_abstract_t
    head_abstract_t
    ;
        typedef
      typename functor_indexed::layout_domain
      < head_abstract_t
      , typename head_abstract_t::index_undefined
      >
    layout_domain
    ;
        typedef
      typename layout_domain::index_type
    index_type
    ;
        typedef
      typename layout_domain::indexes
    indexes
    ;
    reifier_indexed
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
      template
      < index_type IndexValue
      >
      result_type 
    operator()
      ( mpl::integral_c<index_type,IndexValue> index
      )const
      /**@brief
       *  "Reifies" the head_abstract() into
       *  the type indicated by the tag, IndexValue.
       *  Then calls this->push_back_concrete.
       */
    {
          index_type const 
        index_concrete=index_type(IndexValue);
          typename super_t::head_abstract_t&
        my_head_abstract=this->head_abstract();
            typedef 
          decltype(my_head_abstract.template proj_base<index_concrete>()) 
        tail_type;
        tail_type& a_tail_concrete=my_head_abstract.template proj_base<index_concrete>();
        return this->push_back_concrete(a_tail_concrete);
    }
        
      result_type
    reify_rest
      ( void
      )const
      /**@brief
       *  Indirectly, calls this->operator()( mpl::integral_c<index_type,IndexValue> index)
       *  where IndexValue == head_abstract().which().
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
