#ifndef BOOST_ARRAY_STEPPER_OFFSET_AT_INDICES_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_OFFSET_AT_INDICES_HPP_INCLUDED
#include <numeric>
#include <boost/iterator/transform_iterator.hpp>

namespace boost
{
namespace array_stepper
{
    template
    < typename StrideIter
    , typename GetStride
    , typename IndexIter
    , typename Offset
    >
    Offset
  offset_at_indices 
    ( IndexIter first_index
    , IndexIter last_index
    , StrideIter first_stride
    , GetStride get_stride //functor returning strides in StrideIter
    , Offset offset0=Offset(0)
    )
    /**@brief
     *  Returns offset corresponding to the indices
     *  in array with strides given by
     *  first_stride...(first_stride+(last_index-first_index).
     *
     *  This corresponds to equation (5.2) of the @reference.
     *  
     **@reference:
     *  _An APL Compiler_
     *  Timothy Budd
     *  Springer-Verlag, 1988
     */
    {
          transform_iterator
          < GetStride
          , StrideIter
          > 
        beg_s
          ( first_stride
          , get_stride
          );
        return std::inner_product
          ( first_index
          , last_index
          , beg_s
          , offset0
          );
    }
         
}//exit array_stepper namespace
}//exit boost namespace
#endif
