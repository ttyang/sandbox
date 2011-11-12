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
      typename length_stride_t::length_t
    length_t
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
      #ifndef __clang__
        : super_t
          ({{ 0
            , 0
            , 0
            }
           }
          )
      #endif
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
        
          std::ostream&
        print
          ( std::ostream& sout
          )const
        {
            sout<<"{ lower="<<get<index_bound_lower>();
            sout<<", upper="<<get<index_bound_upper>();
            sout<<", value="<<get<index_value>();
            sout<<"}";
            return sout;
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
            return my_ls.stride();
        }
          stride_t
        length_val()const
        {
            index_t index_upper=bound<index_bound_upper>();
            index_t index_lower=bound<index_bound_lower>();
            return index_upper-index_lower+1;
        }
          length_t
        length_outer()const
        {
            return my_ls.length();
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
          axis_t
        my_rotation
        ;
     public:
        indices_bounds_strides
          ( axis_t a_rank
          , length_stride_iter_t const& a_lsi
          , axis_t a_rotation=0
          )
        : my_oib
          ( a_rank
          )
        , my_lsi
          ( a_lsi
          )
        , my_rotation
          ( a_rotation
          )
        {}
        
          axis_t
        rank()const
        {
            return my_oib.size();
        }
          axis_t
        axis_rotated(axis_t a_axis)const
        {
            return (my_rotation+a_axis)%rank();
        }
          axis_t
        rotate(axis_t a_rotation)
          /**@brief
           *  Rotate axes to the left by a_rotation positions.
           */
        {
            my_rotation=axis_rotated(a_rotation);
            return my_rotation;
        }
          axis_t
        rotation()const
        {
            return my_rotation;
        }
          index_bound_stride<mutable_yes>
        operator[](axis_t a_axis)
        {
            axis_t const r_axis=axis_rotated(a_axis);
            offset_index_bounds&oib=my_oib[r_axis];
            length_stride_t const&ls=my_lsi[r_axis];
            return index_bound_stride<mutable_yes>( oib, ls);
        }
          index_bound_stride<mutable_not>
        operator[](axis_t a_axis)const
        {
            axis_t const r_axis=axis_rotated(a_axis);
            offset_index_bounds const&oib=my_oib[r_axis];
            length_stride_t const&ls=my_lsi[r_axis];
            return index_bound_stride<mutable_not>( oib, ls);
        }
            typedef
          std::vector<index_t>
        indices_t
        ;
          indices_t
        indices()const
        {
            axis_t const n_axis=rank();
            indices_t indices_v(n_axis);
            for(axis_t i_axis=0; i_axis<n_axis; ++i_axis)
            {
                offset_index_bounds const&oib=my_oib[i_axis];
                indices_v[i_axis]=oib.template val<index_value>();
            }
            return indices_v;
        }
          indices_t
        indices_rotated()const
        {
            axis_t const n_axis=rank();
            indices_t indices_v(n_axis);
            for(axis_t i_axis=0; i_axis<n_axis; ++i_axis)
            {
                axis_t const r_axis=axis_rotated(i_axis);
                offset_index_bounds const&oib=my_oib[r_axis];
                indices_v[i_axis]=oib.template val<index_value>();
            }
            return indices_v;
        }
          indices_t
        indices_at_offset
          ( typename length_strides_offset_t::offset_t a_offset
          )const
          /**@brief
           *  Indices corresponding to offset, a_offset.
           */
        {
            return ::boost::array_stepper::indices_at_offset
              < indices_t
              >
              ( my_lsi
              , my_lsi+rank()
              , typename length_strides_offset_t::get_length_stride()
              , a_offset
              );
        }
          std::ostream&
        print
          ( std::ostream& sout
          )const
        {
            axis_t const n_axis=rank();
            sout<<"{ ";
            for(axis_t i_axis=0; i_axis<n_axis; ++i_axis)
            {
                if(0<i_axis)sout<<", ";
                my_oib[i_axis].print(sout);
            }
            sout<<"}";
            return sout;
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
        return static_cast<index_stack_concrete_t&>(*this);
    }
      index_stack_concrete_t const&
    derived()const
    {
        return static_cast<index_stack_concrete_t const&>(*this);
    }
        typedef
      unsigned
    axis_depth_t
    ;
        static
      axis_depth_t const
    axis_end=0
      /**@brief
       *  The value returned from inc_dec_ator indicating
       *  all indices changed.
       */
    ;
      axis_depth_t
    axis_begin()const
    {
        return derived().rank();
    }
      template
      < inc_dec_enum ID
      >
      axis_depth_t
    inc_dec_ator()
      /**@brief
       *  increment (if ID==inc_ator) or decrement(if ID==dec_ator) the indices
       *  1 at a time, from rightmost to leftmost.
       *  IOW, the rightmost index increments fastest, and 
       *  the leftmost index increments slowest.
       *  Rightmost corresponds to top of stack.
       *  Leftmost corresponds to bottom of stack.
       *  Returns the depth of the stack containing unchanged
       *  indices.
       */
    {
        index_stack_concrete_t&der=derived();
        typedef inc_dec_concrete<ID> conc_t;
        auto& offset_space=der.offset_space_ref();
        axis_depth_t axis_depth_v=axis_begin();//change 1st rightmost index.
      //#define TRACE_INC_DEC_ATOR
        while( axis_end<axis_depth_v)
        {
            auto ibs=der[axis_depth_v-1];
            auto& index_axis=ibs.template get<index_value>();
            auto bound_limit_axis=ibs.template bound<conc_t::bound_limit>();
            auto stride_axis=ibs.stride_val();
          #ifdef TRACE_INC_DEC_ATOR
            std::cout
              <<"inc_dec_ator::before:axis_depth_v="<<axis_depth_v
              <<":index_axis="<<index_axis
              <<":bound_limit_axis="<<bound_limit_axis
              <<"\n";
          #endif
            if( index_axis == bound_limit_axis)//if axis_depth_v-th index at trigger bound, then
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
                --axis_depth_v;
            }
            else
            { //just cnahge index_axis, offset_space, and exit loop.
                conc_t::change( index_axis, offset_space, stride_axis);
                break;
            }
          #ifdef TRACE_INC_DEC_ATOR
            std::cout
              <<"inc_dec_ator::after:axis_depth_v="<<axis_depth_v
              <<":index_axis="<<index_axis
              <<"\n";
          #endif
        }
        return axis_depth_v;
    }
      axis_depth_t
    operator++()
    {
        return inc_dec_ator<inc_ator>();
    }
      axis_depth_t
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
        typedef
      typename types_t::length_t
    length_t
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

      derived_t const&
    axis_offsets_put
      ( axis_t a_axis
      , index_t a_offset_lower=0
      , index_t a_offset_upper=0
      )
    /**@brief
     *  Reset the boundary offsets for given axis.
     */
    {
        derived_t&der=derived();
        auto ibs=der[a_axis];
        auto l_old=ibs.length_val();
        ibs.get<index_bound_lower>()=a_offset_lower;
        ibs.get<index_bound_upper>()=a_offset_upper;
        auto l_new=ibs.length_val();
        auto index_lower=ibs.template bound<index_bound_lower>();
        axis_index_put(a_axis,index_lower);
        if(l_old==l_new)return der;
        if(my_space==0)
        {
            my_space=this->ctor_space();
        }
        else
        {
            my_space/=l_old;
            my_space*=l_new;
        }
        return der;
    }

      derived_t const&
    axes_offsets_put
      ( index_t offset_lower=0
      , index_t offset_upper=0
      )
    {//call axis_offset_put for each axis.
        derived_t&der=derived();
          axis_t const 
        n_axis=der.rank();
        for
          ( axis_t i_axis=0
          ; i_axis<n_axis
          ; ++i_axis
          )
        {
            axis_offsets_put( i_axis, offset_lower, offset_upper);
        }
        return der;
    }
      
      derived_t&
    derived()
    {
        return *static_cast<derived_t*>(this);
    }
      derived_t const&
    derived()const
    {
        return static_cast<derived_t const&>(*this);
    }
      length_t
    space_outer()const
    {
            typedef
          typename derived_t::axis_t
        axis_t;
        derived_t const&der=derived();
        length_t s=1;
        axis_t const rank=der.rank();
        for
          ( axis_t axis=0
          ; axis<rank
          ; ++axis
          )
        {
            auto ibs=der[axis];
            length_t l=ibs.length_outer();
            if(l<=0)return 0;
            s*=l;
        }
        return s;
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
      sout<<"\n{ offset="<<std::setw(2)<<lsos_v.offset_space_val();
      sout<<"\n, space="<<std::setw(2)<<lsos_v.space();
      sout<<"\n, rotation="<<lsos_v.rotation();
      sout<<"\n, luvs="; lsos_v.print(sout);
      sout<<"\n, rotated indices=";
      sout<<lsos_v.indices_rotated();
      sout<<"\n}";
      return sout;
  }

#endif
