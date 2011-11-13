#ifndef BOOST_ARRAY_STEPPER_ARRAY_DYN_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_DYN_HPP_INCLUDED
#include <boost/array_stepper/array_store.hpp>

namespace boost
{
namespace array_stepper
{
  template
  < typename T
  >
  struct  
array_dyn
/**@brief
 *  Provide more convenient constructors
 *  for superclass.
 */
: array_store<T>
{
        typedef
      array_store<T>
    super_t
    ;
        typedef typename
      super_t::domain_t
    domain_t
    ;
      template
      < typename Lengths
      >
    array_dyn
      ( Lengths const& a_lengths
      , storage_order_predefined so=domain_t::storage_order_default
      )
    : super_t
      ( a_lengths
      , domain_t::permute_select(so)(a_lengths.size())
      )
    {
    }
    
      template
      < typename Lengths
      >
    array_dyn
      ( Lengths const& a_lengths
      , typename domain_t::permute_t const& a_permute
      )
    : super_t
      ( a_lengths
      , a_permute
      )
    {
    }
};


}//exit array_stepper namespace
}//exit boost namespace
#endif
