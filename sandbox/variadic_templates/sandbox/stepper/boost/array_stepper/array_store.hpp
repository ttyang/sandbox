#ifndef BOOST_ARRAY_STEPPER_ARRAY_STORE_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_STORE_HPP_INCLUDED
#include <boost/array_stepper/length_strides_offset.hpp>

namespace boost
{
namespace array_stepper
{
  template
  < typename T
  , typename Domain=length_strides_offset<>
  >
  struct  
array_store
/**@brief
 *  Multidimensional array whose
 *  'shape' is defined at runtime.
 *  'Shape' means lengths of 
 *  (or upper bounds on indices to) 
 *  the array's axes.
 */
: Domain
{
        typedef
      Domain
    domain_t
    ;
        typedef
      typename domain_t::indices_t
    indices_t
    ;
        typedef
      std::vector<T>
    data_t
    ;
 private:    
      data_t
    my_data
    /**@brief
     *  data in the array.
     */
    ;
 public:    
      data_t&
    data()
    {
        return my_data;
    }
      data_t const&
    data()const
    {
        return my_data;
    }
      template
      < typename Lengths
      >
    array_store
      ( Lengths const& a_lengths
      , typename domain_t::permute_t const& a_permute
      )
    : domain_t
      ( a_lengths.size()
      )
    , my_data
      ( this->domain_t::init_strides( a_lengths, a_permute)
      )
    {
    }
    
      T&
    at_indices_seq( indices_t const& a_indices_seq)
    {
        return my_data[offset_at_indices_seq(a_indices_seq)];
    }
      T const&
    at_indices_seq( indices_t const& a_indices_seq)const
    {
        return my_data[offset_at_indices_seq(a_indices_seq)];
    }
    
  #if !defined(__clang__) && defined(CXX0X_VARIADIC_TEMPLATES)
      template
      < typename... Index
      >
      T&
    operator()( Index... a_index)
    {
        indices_t const indices({a_index...});
        return at_indices_seq(indices);
    }        
      template
      < typename... Index
      >
      T const&
    operator()( Index... a_index)const
    {
        indices_t const indices({a_index...});
        return at_indices_seq(indices);
    }
  #endif

};

}//exit array_stepper namespace
}//exit boost namespace
#endif
