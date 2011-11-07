#ifndef BOOST_ARRAY_STEPPER_INDICES_AT_OFFSET_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_INDICES_AT_OFFSET_HPP_INCLUDED
#include <numeric>
#include <boost/iterator/transform_iterator.hpp>

namespace boost
{
namespace array_stepper
{
    template
    < typename Index
    , typename LengthStride
    , typename GetLengthStride
    , typename Offset
    >
    struct 
  index_at_offset
    /**@brief
     *  Functor used by indexs_at_offset.
     */
    {
          Offset
        my_offset
          /**@brief
           *  offset in multitimensional array.
           *  from beginning of array.
           */
          ;
          GetLengthStride
        my_get_length_stride
          /**@brief
           *  offset in multitimensional array.
           *  from beginning of array.
           */
          ;
        index_at_offset( Offset a_offset, GetLengthStride a_get_length_stride)
          : my_offset(a_offset)
          , my_get_length_stride(a_get_length_stride)
          {}
            typedef 
          Index
        result_type
          /**@brief
           *  required by make_transform_iterator
           *  used in indexs_at_offset.
           */
          ;
          result_type
        operator()( LengthStride const& ls)const
          /**@brief
           *  this is equation (5.7) in @reference
           *  for an axis described by ls.
           */
          { 
              result_type div_v=my_offset/my_get_length_stride.stride(ls);
              result_type index_v=div_v%my_get_length_stride.length(ls);
              return index_v;
          }
    };
    
    template
    < typename Indices
    , typename LengthStrideIter
    , typename GetLengthStride
    , typename Offset
    >
    Indices
  indices_at_offset 
    ( LengthStrideIter first_ls
    , LengthStrideIter last_ls
    , GetLengthStride get_length_stride 
      //provides length and stride funcitons to access lengths
      //and strides of elements in LengthStrideIter.
    , Offset offset0
    )
    /**@brief
     *  Returns the indices corresponding to offset0
     *  in array with length and strides given by
     *  first_ls...last_ls.
     *
     *  This corresponds to equation (5.7) in @reference
     *  for each axis.
     *  
     **@reference:
     *  _An APL Compiler_
     *  Timothy Budd
     *  Springer-Verlag, 1988
     */
    {
        std::size_t const
      size=last_ls-first_ls
        ;
        Indices 
      indices(size)
        ;
          typedef
        index_at_offset
        < typename Indices::value_type
        , typename LengthStrideIter::value_type
        , GetLengthStride
        , Offset
        >
      iao_t
        ;
          typedef 
        transform_iterator
        < iao_t
        , LengthStrideIter
        > 
      xiter_t
        ;
        iao_t
      iao_v(offset0,get_length_stride)
        ;
        xiter_t
      beg_index( first_ls, iao_v)
        ;
        xiter_t 
      end_index( last_ls, iao_v)
        ;
        typename Indices::iterator 
      beg_is=indices.begin()
        ;
        std::copy
          ( beg_index
          , end_index
          , beg_is
          );
        return indices;
    }
         
}//exit array_stepper namespace
}//exit boost namespace
#endif
