#ifndef BOOST_ARRAY_STEPPER_LENGTH_STRIDE_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_LENGTH_STRIDE_HPP_INCLUDED
#include <limits>
#include <boost/static_assert.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace boost
{
namespace array_stepper
{
  template
  < typename StrideDir = int
  >
  struct
length_stride
  /**@brief
   *  Length and Stride of an array axis.
   **@reference:
   *  _An APL Compiler_
   *  Timothy Budd
   *  Springer-Verlag, 1988
   */
{
        typedef
      StrideDir
    stride_t
      /**@brief
       *  Stride of an axis.
       */
      ;
 private:
    BOOST_STATIC_ASSERT(std::numeric_limits<stride_t>::is_signed)
      /**@brief
       *  stride_t is be signed to allow for reverse ordering
       *  of indices.  IOW, allow the (i+1)-th value 
       *  to be located *before*  the     i-th value.
       */
      ;
 public:
        typedef
      typename make_unsigned<stride_t>::type
    length_t
      ;
 private:    
      length_t
    my_length
      /**@brief
       *  Length of the axis.
       *  Corresponds to the s_i in equation (5.1)
       *  of section:
       *    5.1 Expansion Vectors
       *  of @reference.
       */
      ;
      stride_t
    my_stride
      /**@brief
       *  Stride of the axis, i.e.
       *  the distance between adjacent
       *  elements on the axis.
       *  If < 0, this indicates the
       *  axis is reversed, IOW for
       *  indices i,j such that i<j:
       *       address of i-th element
       *    >  address of j-th element.
       *  See comments in:
       *    length_stride_compose<>::operator()(...)
       *    in length_stride_compose.hpp.
       *
       *  This corresponds to the e_i in equation (5.1)
       *  of section:
       *    5.1 Expansion Vectors
       *  of @reference, *except* it may be negative
       *  to account for axis reveral, as explained above.
       */
      ;
 public:
      length_t
    length()const
      {
        return my_length;
      }            
      stride_t
    stride()const
      {
        return my_stride;
      }
      length_t
    space()const
      {
        return length()*abs(stride());
      }
    length_stride()
      : my_length(1)
      , my_stride(1)
      {}
    length_stride(length_t a_length)
      : my_length(a_length)
      , my_stride(1)
      {}
    length_stride(length_t a_length, stride_t a_stride)
      : my_length(a_length)
      , my_stride(a_stride)
      {}
    
};

  template
  < typename LengthStride
  >
  typename LengthStride::space_t
length
  ( LengthStride const& ls
  )
  {
    return ls.length();
  }
  
  template
  < typename LengthStride
  >
  typename LengthStride::stride_t
stride
  ( LengthStride const& ls
  )
  {
    return ls.stride();
  }
  
}//exit array_stepper namespace
}//exit boost namespace
#endif
