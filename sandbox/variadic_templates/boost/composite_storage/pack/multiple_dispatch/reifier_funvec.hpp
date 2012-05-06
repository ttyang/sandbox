//
#ifndef BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_FUNVEC_HPP_INCLUDED
#define BOOST_COMPOSITE_STORAGE_PACK_MULTIPLE_DISPATCH_REIFIER_FUNVEC_HPP_INCLUDED
//  (C) Copyright Larry Evans 2010.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies
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
struct reifier_funvec
: reifier_indexed_base
  < ReifyApply
  , ArgsConcreteAbstract
  >
  /**@brief
   *  Uses vector of functions (see static our_vec() below)
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
    reifier_funvec
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
        typedef
      reifier_funvec
      < ReifyApply
      , ArgsConcreteAbstract
      >
    this_type
    ;
    template<class Case> 
    struct fun_case
    {
            static
          result_type 
        _(this_type const& f)
        {
            Case arg;
            return f(arg);
        }
    };
        typedef
      typename super_t::cases
    cases
    ;
        typedef
      typename super_t::case_type
    case_type
    ;
    struct fun_vec
    {
            typedef
          result_type
          (*
        fun_type
          )(this_type const&)
        ;
            static
          unsigned const
        vec_size
        = boost::mpl::size<cases>::type::value
        ;
            typedef
          fun_type
        vec_type
          [ vec_size
          ]
        ;
            static
          unsigned
        case_index
          ( case_type index
          )
        {
            return index-cases::start::value;
        }
        struct fill_vec
        {
              vec_type&
            my_vec
            ;
            fill_vec(vec_type& a_vec)
            : my_vec(a_vec)
            {}
              template
              < typename Case
              >
              void
            operator()(Case)
            {
                unsigned const index=case_index(Case::value);
                my_vec[index]=fun_case<Case>::_;
            }
        };
          vec_type
        my_vec
        ;
        fun_vec(void)
        {
            boost::mpl::for_each<cases>(fill_vec(my_vec));
        }
          fun_type
        operator[](case_type i)const
        {
            unsigned const index=case_index(i);
            return my_vec[index];
        }
          
    };
        static
      fun_vec const&
    our_vec(void)
    {
        static fun_vec const a_vec;
        return a_vec;
    }
      result_type
    reify_rest
      ( void
      )const
      /**@brief
       *  Indirectly, calls this->super_t::operator()( mpl::integral_c<case_type,CaseValue> index)
       *  where CaseValue == head_abstract().which().
       */
    {
        return our_vec()[this->head_abstract().which()](*this);
    }
};

}//exit namespace multiple_dispatch
}//exit namespace pack

}//exit composite_storage namespace
}//exit boost namespace
#endif
