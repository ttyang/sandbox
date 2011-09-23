//stack of loop indices and length_strides_for an array.
#ifndef BOOST_ARRAY_STEPPER_INDEX_STACK_LENGTH_STRIDE_CRTP_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_INDEX_STACK_LENGTH_STRIDE_CRTP_HPP_INCLUDED
//  (C) Copyright Larry Evans 2011.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//====================================================================
#include <boost/array_stepper/length_strides_offset.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/assert.hpp>
namespace boost
{
namespace array_stepper
{

enum index_bounds_value_enum
{ index_bound_lower
, index_bound_upper
, index_value
};
enum 
{ index_bounds_value_size=index_value+1
};
enum mutable_enum
{ mutable_not
, mutable_yes
};

  template
  < typename Stride=int
  >
  struct
index_stack_length_stride_crtp_types
{
        typedef
      Stride
    stride_t
    ;
        typedef
      length_strides_offset
      < stride_t
      >
    length_strides_offset_t
    ;
        typedef
      typename length_strides_offset_t::length_stride_t
    length_stride_t
    ;
        typedef
      typename length_strides_offset_t::length_strides_t
    length_strides_t
    ;
        typedef
      typename length_strides_t::const_iterator
    length_stride_iter_t
    ;
        typedef
      typename length_strides_offset_t::index_t
    index_t
    ;
        typedef
      typename length_strides_offset_t::axis_t
    axis_t
    ;
        typedef
      std::vector<index_t>
    indices_t
    ;
      struct
    offset_space
      /**@brief
       *  offset from beginning or the array's storage.
       */
    {
        offset_space()
        : my_offset(0)
        {} 
          stride_t
        offset_space_val()const
        {
            return my_offset;
        }
          stride_t&
        offset_space_ref()
        {
            return my_offset;
        }
     private:        
          stride_t
        my_offset
        ;
    };
    
      struct
    offset_index_bounds
      /**@brief
       *  Offset from front and back of
       *  an index range and current index.
       */
    : private array
      < index_t
      , std::size_t(index_bounds_value_size)
      >
    {
            typedef
          array
          < index_t
          , std::size_t(index_bounds_value_size)
          >
        super_t
        ;
        offset_index_bounds
          (
          )
        : super_t
          ({{ 0
            , 0
            , 0
            }
           }
          )
        {}
          template
          < index_bounds_value_enum IBV
          >
          index_t
        val
          (
          )const
        {
            super_t const&me=*this;
            return me[IBV];
        }
          template
          < index_bounds_value_enum IBV
          >
          index_t&
        ref
          (
          )
        {
            super_t&me=*this;
            return me[IBV];
        }
          template
          < index_bounds_value_enum IBV
          >
          index_t
        get
          (
          )const
        {
            return val<IBV>();
        }
          template
          < index_bounds_value_enum IBV
          >
          index_t&
        get
          (
          )
        {
            return ref<IBV>();
        }
    };
    
      template
      < mutable_enum MutEnum
      >
    struct index_bound_stride
    {
            typedef
          typename ::boost::mpl::if_c
          < MutEnum==mutable_yes
          , offset_index_bounds
          , offset_index_bounds const
          >::type
        offset_index_bounds_t
        ;
     private:
          offset_index_bounds_t&
        my_oib
        ;
          length_stride_t const&
        my_ls
        ;
     public:
        index_bound_stride
        ( offset_index_bounds_t& a_oib
        , length_stride_t const& a_ls
        )
        : my_oib(a_oib)
        , my_ls(a_ls)
        {}
          template
          < index_bounds_value_enum IBV
          >
          index_t
        get
          (
          )const
        {
            return my_oib.template get<IBV>();
        }
          template
          < index_bounds_value_enum IBV
          >
          typename ::boost::mpl::if_c
          < MutEnum==mutable_yes
          , index_t&
          , index_t
          >::type
        get
          (
          )
        {
            return my_oib.template get<IBV>();
        }
        
          template
          < index_bounds_value_enum IBV
          >
          typename ::boost::enable_if_c
          < IBV!=index_value
          , index_t
          >::type
        bound()const
        {
            index_t offset=my_oib.template val<IBV>();
            if(IBV==index_bound_lower) return offset;
            return my_ls.length()-1-offset;
        }
          stride_t
        stride_val()const
        {
            my_ls.stride();
        }
          stride_t
        length_val()const
        {
            index_t index_upper=bound<index_bound_upper>();
            index_t index_lower=bound<index_bound_lower>();
            return index_upper-index_lower+1;
        }
    };
    
    struct indices_bounds_strides
    {
     private:
            typedef
          std::vector
          < offset_index_bounds
          >
        offset_indices_bounds_t
        ;
          offset_indices_bounds_t
        my_oib
        ;
          length_stride_iter_t
        my_lsi
        ;
     public:
        indices_bounds_strides
          ( axis_t a_rank
          , length_stride_iter_t const& a_lsi
          )
        : my_oib
          ( a_rank
          )
        , my_lsi
          ( a_lsi
          )
        {}
        
          axis_t
        rank()const
        {
            return my_oib.size();
        }

          index_bound_stride<mutable_yes>
        operator[](axis_t a_axis)
        {
            offset_index_bounds&oib=my_oib[a_axis];
            length_stride_t const&ls=my_lsi[a_axis];
            return index_bound_stride<mutable_yes>( oib, ls);
        }
          index_bound_stride<mutable_not>
        operator[](axis_t a_axis)const
        {
            offset_index_bounds const&oib=my_oib[a_axis];
            length_stride_t const&ls=my_lsi[a_axis];
            return index_bound_stride<mutable_not>( oib, ls);
        }
    };
};

enum inc_dec_enum
{ inc_ator
, dec_ator
};

  template
  < inc_dec_enum ID
  >
  struct
inc_dec_concrete
  /**@brief
   *  Specializations provide operations & values
   *  used by:
   *      index_stack_length_stride_crtp_abstract::
   *    inc_dec_ator<ID>
   *  templated member function.
   */
;
  template
  <
  >
  struct
inc_dec_concrete
  < inc_ator
  >
{
        static
      index_bounds_value_enum const
    bound_limit=index_bound_upper
    ;
        static
      index_bounds_value_enum const
    bound_reset=index_bound_lower
    ;
      template
      < typename Index
      , typename Offset
      , typename Stride
      >
        static
      void
    change
      ( Index& index
      , Offset& offset
      , Stride stride
      )
    {
        ++index;
        offset+=stride;
    }
};

  template
  <
  >
  struct
inc_dec_concrete
  < dec_ator
  >
{
        static
      index_bounds_value_enum const
    bound_limit=index_bound_lower
    ;
        static
      index_bounds_value_enum const
    bound_reset=index_bound_upper
    ;
      template
      < typename Index
      , typename Offset
      , typename Stride
      >
        static
      void
    change
      ( Index& index
      , Offset& offset
      , Stride stride
      )
    {
        --index;
        offset-=stride;
    }
};

  template
  < typename IndexStackConcrete
  >
  struct
index_stack_length_stride_crtp_abstract
  /**@brief
   *  An "abstract stack" of indices like those
   *  for a N nested for loops, where N is the
   *  value from rank() function of derived().
   *  This class is abstract because the concrete
   *  values are supplied by derived().
   */
{
        typedef
      IndexStackConcrete
    index_stack_concrete_t
    ;
      index_stack_concrete_t&
    derived()
    {
        *static_cast<index_stack_concrete_t*>(this);
    }
      index_stack_concrete_t const&
    derived()const
    {
        *static_cast<index_stack_concrete_t const*>(this);
    }
      template
      < inc_dec_enum ID
      >
      int
    inc_dec_ator()
      /**@brief
       *  increment (if ID==inc_ator) or decrement(if ID==dec_ator) the indices
       *  1 at a time, from rightmost to leftmost.
       *  IOW, the rightmost index increments fastest, and 
       *  the leftmost index increments slowest.
       */
    {
        index_stack_concrete_t&der=derived();
        typedef inc_dec_concrete<ID> conc_t;
        auto& offset_space=der.offset_space_ref();
        int const n=der.rank();
        int axis=n-1;//increment 1st rightmost index.
      //#define TRACE_INC_DEC_ATOR
        while( 0<=axis)
        {
            auto ibs=der[axis];
            auto& index_axis=ibs.template get<index_value>();
            auto bound_limit_axis=ibs.template bound<conc_t::bound_limit>();
            auto stride_axis=ibs.stride_val();
          #ifdef TRACE_INC_DEC_ATOR
            std::cout
              <<"inc_dec_ator::before:axis="<<axis
              <<":index_axis="<<index_axis
              <<":bound_limit_axis="<<bound_limit_axis
              <<"\n";
          #endif
            if( index_axis == bound_limit_axis)//if axis-th index at triggeer bound, then
            {
                { //reset index_axis to bound opposite to bound_limit_axis:
                    auto bound_reset_axis=ibs.template bound<conc_t::bound_reset>();
                      //First, change offset_space to reflect future
                      //change in index_axis to bounds_reset_axis.
                    offset_space-=(index_axis-bound_reset_axis)*stride_axis;
                      //Next, change index_axis.
                    index_axis=bound_reset_axis;
                }
                  //then proceed to increment/decrement next (in left direction) index in loop.
                --axis;
            }
            else
            { //just cnahge index_axis, offset_space, and exit loop.
                conc_t::change( index_axis, offset_space, stride_axis);
                break;
            }
          #ifdef TRACE_INC_DEC_ATOR
            std::cout
              <<"inc_dec_ator::after:axis="<<axis
              <<":index_axis="<<index_axis
              <<"\n";
          #endif
        }
        return axis;
    }
      int
    operator++()
    {
        return inc_dec_ator<inc_ator>();
    }
      int
    operator--()
    {
        return inc_dec_ator<dec_ator>();
    }

};
  
  template
  < typename IndexStackConcrete
  >
  struct
indices_space
;
  template
  < typename Stride
  , template< typename>class Tmpl
  >
  struct
indices_space
  < Tmpl<Stride>
  >
{
        typedef
      Tmpl<Stride>
    derived_t
    ;
        typedef
      Stride
    stride_t
    ;
        typedef
      index_stack_length_stride_crtp_types<stride_t>
    types_t
    ;
        typedef
      typename types_t::axis_t
    axis_t
    ;
        typedef
      typename types_t::index_t
    index_t
    ;
    indices_space()
    : my_space(this->ctor_space())
    {
    }
      stride_t
    space()const
    {
        return my_space;
    }

      void
    axis_index_put
      ( axis_t a_axis
      , index_t a_index
      )
    {
        derived_t&der=derived();
        auto ibs=der[a_axis];
        auto&index_ref=ibs.get<index_value>();
        auto&offset_space=der.offset_space_ref();
        int index_diff=a_index-index_ref;
        auto stride=ibs.stride_val();
        int offset_diff=index_diff*stride;
        offset_space+=offset_diff;
        index_ref=a_index;
    }

      void
    axis_offset_put
      ( axis_t a_axis
      , index_t a_offset_lower
      , index_t a_offset_upper
      )
    {
        derived_t&der=derived();
        auto ibs=der[a_axis];
        auto l_old=ibs.length_val();
        ibs.get<index_bound_lower>()=a_offset_lower;
        ibs.get<index_bound_upper>()=a_offset_upper;
        auto l_new=ibs.length_val();
        auto index_lower=ibs.template bound<index_bound_lower>();
        axis_index_put(a_axis,index_lower);
        if(l_old==l_new)return;
        my_space/=l_old;
        my_space*=l_new;
    }

      derived_t&
    derived()
    {
        return *static_cast<derived_t*>(this);
    }
 private:
      stride_t
    ctor_space()
      /**@brief
       *  1) returns number of elements =
       *       (bounds_upper[     0]+1-bounds_lower[     0])
       *      *(bounds_upper[     1]+1-bounds_lower[     1])
       *      ...
       *      *(bounds_upper[rank-1]+1-bounds_lower[rank-1])
       *  2) sets indices[*] to bounds_lower[*].
       *  3) sets offset_space = 
       *       bounds_lower[     0]*strides[     0]
       *      +bounds_lower[     1]*strides[     1]
       *      ...
       *      +bounds_lower[rank-1]*strides[rank-1]
       *
       *  where:
       *    rank = number of axes.
       *    indices     [a_axis] is index                of axis, a_axis.
       *    bounds_lower[a_axis] is lower bound of index of axis, a_axis.
       *    bounds_upper[a_axis] is upper bound of index of axis, a_axis.
       *    strides     [a_axis] is stride               of axis, a_axis.
       */
    {
            typedef
          typename derived_t::axis_t
        axis_t;
        derived_t&der=derived();
        auto&offset_space=der.offset_space_ref();
        stride_t s=1;
        axis_t const rank=der.rank();
        for
          ( axis_t axis=0
          ; axis<rank
          ; ++axis
          )
        {
            auto ibs=der[axis];
            offset_space+=ibs.template get<index_value>()*std::abs(ibs.stride_val());
            int l=ibs.length_val();
            if(l<0)l=0;
            s*=l;
        }
        return s;
    }
      stride_t
    my_space
    ;
};

  template
  < typename Stride=int
  >
  struct
index_stack_length_stride_crtp_indices
: index_stack_length_stride_crtp_types<Stride>::indices_bounds_strides
, index_stack_length_stride_crtp_types<Stride>::offset_space
, index_stack_length_stride_crtp_abstract
  < index_stack_length_stride_crtp_indices
    < Stride
    >
  >
, indices_space
  < index_stack_length_stride_crtp_indices
    < Stride
    >
  >
{

        typedef
      index_stack_length_stride_crtp_types
      < Stride
      >
    types_t
    ;
        typedef
      typename types_t::stride_t
    stride_t
    ;
        typedef
      typename types_t::index_t
    index_t
    ;
        typedef
      typename types_t::axis_t
    axis_t
    ;
        typedef
      typename types_t::indices_bounds_strides
    indices_bounds_strides_t
    ;
        typedef
      indices_space
      < index_stack_length_stride_crtp_indices
        < Stride
        >
      >
    indices_space_t
    ;
        typedef
      typename types_t::length_stride_iter_t
    length_stride_iter_t
    ;
    index_stack_length_stride_crtp_indices
    ( length_stride_iter_t ls_iter_beg
    , length_stride_iter_t ls_iter_end
    )
    : index_stack_length_stride_crtp_types<Stride>::indices_bounds_strides
      ( axis_t(ls_iter_end-ls_iter_beg)
      , ls_iter_beg
      )
    {
    }
};
    
}//exit array_stepper namespace
}//exit boost namespace

#include <iostream>
#include <iomanip>

  template< typename Stride>
  std::ostream&
operator<<
  ( std::ostream& sout
  , boost::array_stepper::index_stack_length_stride_crtp_indices<Stride>const& lsos_v
  )
  {
      sout<<"{ offset="<<std::setw(2)<<lsos_v.offset_space_val();
      sout<<", indices=";
      sout<<"{ ";
      for(unsigned axis=0; axis<lsos_v.rank(); ++axis)
      {
          if(0<axis)sout<<", ";
          auto ibs=lsos_v[axis];
          auto index=ibs.template get<boost::array_stepper::index_value>();
          sout<<std::setw(2)<<index;
      }
      sout<<"} ";
      sout<<"}";
      return sout;
  }

#endif
