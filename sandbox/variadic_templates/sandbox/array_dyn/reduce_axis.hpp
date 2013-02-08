#ifndef REDUCE_AXIS_HPP_INCLUDED
#define REDUCE_AXIS_HPP_INCLUDED
//  (C) Copyright Larry Evans 2012.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//====================================================================
struct loop
/**@brief
 *  loop variables for some axis in array.
 */
{
    unsigned offset;//offset in array from start of axis
    unsigned stride;//increment to offset
    unsigned limit;//limit to offset
    loop()
    : offset(0)
    , stride(0)
    , limit(0)
    {}
};

  template
  < typename Iter
  >
struct iter_stride
: Iter
{
      int const
    my_stride
      ;
      int
    stride()const
    {
        return my_stride;
    }
    iter_stride
    ( Iter a_iter
    , int a_stride=1
    )
    : Iter(a_iter)
    , my_stride(a_stride)
    {}
        typedef
      typename Iter::difference_type
    difference_type
      ;
      difference_type
    distance
      ( iter_stride const& last
      )
    {
        difference_type d=std::distance(*this,last);
        d=d/my_stride;
        return d;
    }
        
    Iter& operator++()
    {
        this->operator+=(my_stride);
        return *this;
    }
};  

#include "array_dyn.hpp"

  template
  < typename Reducer
  , typename Value
  >
  array_dyn<Value>
reduce_axis
  ( Reducer a_reducer
  , array_dyn<Value>const& a_source
  , unsigned oper_axis=0
  )
  /**@brief
   *  Apply a_reducer to axis, oper_axis, of a_source,
   *  producing another array_dyn, a_target, where
   *  a_target.size(oper_axis)==1, and that single
   *  value is the result of the reduction on a_source.
   *  This does, essentially, what the apl reduce
   *  statement:
   *    operator(a_reducer)/[oper_axis] a_source
   *  would do,  where operator(a_reducer) is the
   *  operation which a_reducer applies along the oper_axis.
   *  See:
   *    http://aplwiki.com/LearnApl/AplOperators#Reduce_and_scan  
   */
{
    unsigned const rank=a_source.rank();
    enum
      { outer //outer loop axis tag (larger strides).
      , oper    //oper axis tag.
      , inner //inner loop axis tag (smaller strides).
      };
  //[following assumes a_source.my_dir==dir_rev.
    unsigned max_stride_axis=0;//axis with maximum stride.
    unsigned min_stride_axis=rank-1;//axis with minimum stride.
    int greater_axis=-1;//axis increment to axis with greater stride.
  //]preceding assumed a_source.my_dir==dir_rev.
    if(a_source.my_dir != dir_rev)
    {
      //Adjust if above assumption about a_source.my_dir wrong.
        std::swap(min_stride_axis,max_stride_axis);
        greater_axis=1;
    }
    std::vector<loop> loops(inner+1);
    if(oper_axis==max_stride_axis)
    {
      //Since oper_axis already at maximum stride,
      //created a pseudo axis of size 1 and stride 1
      //so that outer loop just executes once.
        loops[outer].stride=1;
        loops[outer].limit =1;
    }
    else
    {
        loops[outer].stride=a_source.stride(oper_axis+greater_axis);
        loops[outer].limit =a_source.size  ();
    }
    loops[oper ].stride=a_source.stride(oper_axis);
    loops[oper ].limit =a_source.size  (oper_axis)*loops[oper].stride;
    loops[inner].stride=a_source.stride(min_stride_axis);
    loops[inner].limit =a_source.stride(oper_axis);
      auto
    shape_target=a_source.shape()
      ;
    shape_target[oper_axis]=1;
        typedef
      Value
    val_t
      ;
        typedef
      array_dyn<val_t>
    array_t
      ;
      array_t
    a_target(a_source.dir(),shape_target)
      ;
    unsigned offset_target=0;
    for
    ( loops[outer].offset = 0
    ; loops[outer].offset < loops[outer].limit
    ; loops[outer].offset+= loops[outer].stride
    )
    {
        for
        ( loops[inner].offset = 0
        ; loops[inner].offset < loops[inner].limit
        ; loops[inner].offset+= loops[inner].stride
          , ++offset_target
        )
        {
            unsigned const offset_in_out
            = loops[outer].offset
            + loops[inner].offset
            ;
                typedef typename
              array_t::data_t::const_iterator
            iter_base_t
              ;
                typedef
              iter_stride<iter_base_t>
            iter_t
              ;
              iter_t
            beg_stride
              ( a_source.my_data.begin()+offset_in_out
              , loops[oper].stride
              )
              ;
              iter_t
            end_stride
              ( a_source.my_data.begin()+offset_in_out
                + loops[oper].limit
              , loops[oper].stride
              )
              ;
            val_t&oper_val=a_target.my_data[offset_target];
            oper_val=a_reducer(beg_stride,end_stride);
        }//exit for(oper...)
    }//exit for(outer...)
    return a_target;
};

#endif
