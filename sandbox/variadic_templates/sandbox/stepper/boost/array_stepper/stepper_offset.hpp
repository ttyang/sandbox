#ifndef BOOST_ARRAY_STEPPER_STEPPER_OFFSET_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_STEPPER_OFFSET_HPP_INCLUDED
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/make_signed.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/array_stepper/permutation0_last.hpp>
#include <limits>

namespace boost
{
namespace array_stepper
{

enum stepr_index
/**@brief
 *  Indices into stepper_one struct (see below).
 */
{ stepr_length  
  //axis length
, stepr_stride  
  //difference between successive
  //elements on this axis.
, stepr_axis
  //axis of array described
  //by the stepper_one.
};
enum
{ stepr_size=stepr_axis+1
};
  
  template
  < typename Value=int 
    //Value must include negative values(i.e. be signed) 
    //to indicate reverse direction for axis.
  >
struct stepper_one
: array< Value, stepr_size>
{
        typedef
      array< Value, stepr_size>
    super_t
    ;
 private:
    BOOST_STATIC_ASSERT(std::numeric_limits<Value>::is_signed);
 public:
        typedef
      Value
    value_t
    ;
        typedef
      value_t
    offset_diff_t
    ;
        typedef
      typename make_unsigned<value_t>::type
    space_t
    ;
        typedef
      space_t
    index_t
    ;
      space_t
    space()const
      /**@brief
       *   Space occupied by all elements on axis
       *   described by this stepper_one.
       */
    { 
        value_t const length=(*this)[stepr_length];
        space_t const stride=abs((*this)[stepr_stride]);
        return length*stride;
    }
      offset_diff_t
    offset(index_t a_index)const
    {
        return (*this)[stepr_stride]*a_index;
    }
      space_t
    offset()const
      /**@brief
       *   Offset caused by negative strides.
       */
    {
        super_t const& me=*this;
        if(me[stepr_stride]<0)
        {
            return abs(this->offset(me[stepr_length]-1));
        }
        else
        {
            return 0;
        }
    }
};

  template
  < stepr_index Index
  , typename Value
  >
  Value&
get( stepper_one<Value>& x)
{
    return x[Index];
}    

  template
  < stepr_index Index
  , typename Value
  >
  Value
get( stepper_one<Value> const& x)
{
    return x[Index];
}
  template
  < typename Value
  >
  int
isign
  ( Value a_value
  )
  {
      return
        (a_value<0)
        ? -1
        : (a_value>0)
          ? +1
          : 0
        ;
  }
  template
  < typename Value=int
  >
struct stepper_offset
{
        typedef
      stepper_one<Value>
    stepper_one_t
    ;
        typedef typename
      stepper_one_t::value_t
    value_t
    ;
        typedef typename
      stepper_one_t::index_t
    index_t
    ;
        typedef
      std::vector<stepper_one_t>
    stepper_ones_t
    ;
        typedef
      typename stepper_ones_t::const_iterator
    const_iterator
    ;
        typedef
      std::vector<Value>
    lengths_t
     /**@brief
      *  length of axes in an array.
      *  Negative Value means axis is reversed.
      */
    ;
        typedef
      unsigned
    offset_t
     /**@brief
      *  offset into array.
      */
    ;
        typedef
      unsigned
    axis_t
     /**@brief
      *  Axis index.
      *  Value in [0,this->rank() )
      */
    ;
        typedef
      typename permutation0_last<axis_t>::permute_t
    axes_permutation_t
      /**@brief
       *  size()==this->rank().
       *  Value is permutation of values of axis_t.
       */
    ;
      axis_t
    rank()const
    {
        return my_stepper_ones.size();
    }
      stepper_ones_t const&
    stepper_ones()const
    {
        return my_stepper_ones;
    }
      index_t
    size()const
    {
        return my_stepper_ones[0][stepr_length];
    }
      offset_t
    offset()const
    {
        return my_offset;
    }
      offset_t
    offset(index_t a_index)const
    {
        axis_t const a_axis= my_stepper_ones[0][stepr_axis];
        return offset()+my_stepper_ones[a_axis].offset(a_index);
    }
      const_iterator
    begin()const
    {
        return my_stepper_ones.begin();
    }
      void
    permute_axes
      ( axes_permutation_t a_permut
      , axis_t a_from=0
      )
    {
        unsigned r=rank()-a_from;
        std::vector<value_t> axes(r);
        for( unsigned i=a_from; i<r; ++i)
        {
            axes[i]=my_stepper_ones[i][stepr_axis];
        }
        for( unsigned i=a_from; i<r; ++i)
        {
            unsigned p=a_permut[i];
            my_stepper_ones[i][stepr_axis]=axes[p];
        }
    }
      void
    rotate_axes
      ( axis_t a_from=0
      )
    {
        unsigned r=rank();
        axis_t a_axis=my_stepper_ones[a_from][stepr_axis];
        for( unsigned i=a_from; i<r-1; ++i)
        {
            my_stepper_ones[i][stepr_axis]=my_stepper_ones[i+1][stepr_axis];
        }
        my_stepper_ones[r-1][stepr_axis]=a_axis;
    }
 protected:
      offset_t
    init_strides
      ( lengths_t const& a_lengths
      , axes_permutation_t a_permut//Must be a permutation of 0..a_length.size().
      )
    {
        unsigned size=a_lengths.size();
        if(0<size)
        {
          #if 0
            unsigned leng_indx=0;
            unsigned perm_indx=a_permut[leng_indx];
            value_t  leng_valu=a_lengths[perm_indx];
            int      leng_sign=isign(leng_valu);
            my_stepper_ones[perm_indx][stepr_length]=abs(leng_valu);
            my_stepper_ones[perm_indx][stepr_stride]=leng_sign;
            my_stepper_ones[perm_indx][stepr_axis  ]=size-1-leng_indx;
            my_offset+=my_stepper_ones[perm_indx].offset();
            for(++leng_indx; leng_indx<size; ++leng_indx)
            {
                value_t pre_space=my_stepper_ones[perm_indx].space();
                perm_indx=a_permut[leng_indx];
                leng_valu=a_lengths[perm_indx];
                leng_sign=isign(leng_valu);
                my_stepper_ones[perm_indx][stepr_length]=abs(leng_valu);
                my_stepper_ones[perm_indx][stepr_stride]=leng_sign*pre_space;
                my_stepper_ones[perm_indx][stepr_axis  ]=size-1-leng_indx;
                my_offset+=my_stepper_ones[perm_indx].offset();
            }
            return my_stepper_ones[perm_indx].space();
          #elif 0
            unsigned leng_indx=0;
            unsigned perm_indx=a_permut[leng_indx];
            value_t  leng_valu=a_lengths[perm_indx];
            int      leng_sign=isign(leng_valu);
            my_stepper_ones[perm_indx][stepr_length]=abs(leng_valu);
            my_stepper_ones[perm_indx][stepr_stride]=leng_sign;
            my_stepper_ones[perm_indx][stepr_axis  ]=leng_indx;
            my_offset+=my_stepper_ones[perm_indx].offset();
            for(++leng_indx; leng_indx<size; ++leng_indx)
            {
                value_t pre_space=my_stepper_ones[perm_indx].space();
                perm_indx=a_permut[leng_indx];
                leng_valu=a_lengths[perm_indx];
                leng_sign=isign(leng_valu);
                my_stepper_ones[perm_indx][stepr_length]=abs(leng_valu);
                my_stepper_ones[perm_indx][stepr_stride]=leng_sign*pre_space;
                my_stepper_ones[perm_indx][stepr_axis  ]=leng_indx;
                my_offset+=my_stepper_ones[perm_indx].offset();
            }
            return my_stepper_ones[perm_indx].space();
          #else
            unsigned maxm_indx=size-1;//MAXiMum index
            for( unsigned leng_indx=0; leng_indx<size; ++leng_indx)
            {
                unsigned perm_indx=maxm_indx-a_permut[leng_indx];
                value_t  leng_valu=a_lengths[leng_indx];
                int      leng_sign=isign(leng_valu);
                my_stepper_ones[perm_indx][stepr_length]=abs(leng_valu);
                my_stepper_ones[perm_indx][stepr_stride]=leng_sign;
                my_stepper_ones[leng_indx][stepr_axis  ]=perm_indx;
            }
            {
                my_offset=my_stepper_ones[maxm_indx].offset();
                for( int axis_indx=maxm_indx-1; 0<=axis_indx; --axis_indx)
                {
                    my_stepper_ones[axis_indx][stepr_stride]*=my_stepper_ones[axis_indx+1].space();
                    my_offset+=my_stepper_ones[axis_indx].offset();
                }
            }
            return my_stepper_ones[maxm_indx].space();
          #endif
        }
        else
        {
            return 0;
        }
    }

    stepper_offset
      ( std::size_t a_rank
      )
    : my_stepper_ones(a_rank)//subclass should call init_strides
    , my_offset(0)
    {
    }
      stepper_ones_t&
    stepper_ones()
    {
        return my_stepper_ones;
    }
 public:
      offset_t
    space()const
      {
        unsigned i=0;
        unsigned r=rank();
        for(; i<r; ++i)
        {
            if(my_stepper_ones[i][stepr_axis]==0) break;
        }
        return my_stepper_ones[i].space();
      }
            
    stepper_offset
      ( lengths_t const& a_lengths
      , axes_permutation_t a_permut//Must be a permutation of 0..a_length.size().
      )
      : my_stepper_ones(a_lengths.size())
      , my_offset(0)
      {
        init_strides( a_lengths, a_permut);
      }
 private:    
      stepper_ones_t
    my_stepper_ones
    ;
      offset_t
    my_offset
    ;
};

}//exit array_stepper namespace
}//exit boost namespace
#endif
