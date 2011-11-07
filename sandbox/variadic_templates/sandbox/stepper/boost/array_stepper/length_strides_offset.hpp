#ifndef BOOST_ARRAY_STEPPER_LENGTH_STRIDES_OFFSET_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_LENGTH_STRIDES_OFFSET_HPP_INCLUDED
#include <boost/array_stepper/length_strides_make.hpp>
#include <boost/array_stepper/offset_at_indices.hpp>
#include <boost/array_stepper/indices_at_offset.hpp>
#include <boost/array_stepper/length_stride.hpp>
#include <boost/array_stepper/permutation.hpp>
#include <boost/array.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/assert.hpp>
#include <algorithm>

namespace boost
{
namespace array_stepper
{

enum storage_order_predefined
{ store_reverse //strides decrease as axis increases(as with c arrays).
, store_forward //strides increase as axis increases(as with fortran arrays).
};
enum
{ storage_order_predef_num=store_forward+1
};
enum struct_op_enum
/**@brief
 *  enumeration of the structural operations
 */
{ op_ax_permute //permute axes
, op_ax_rotate //rotate axes(a specialized & faster permute)
};
  template
  < struct_op_enum StrOp
  >
struct struct_op_tag
{};   

  template
  < typename StrideDir=int
  >
  struct
length_strides_offset
  /**@brief
   *  For each axis (or dimension) in a multi-dimentional array,
   *  this structure stores a length_stride.  In addition,
   *  to account for a negative stride for any of the axes, this
   *  class stores an offset.
   **@reference:
   *  _An APL Compiler_
   *  Timothy Budd
   *  Springer-Verlag, 1988
   */
{
        typedef
      length_stride
      < StrideDir
      >
    length_stride_t
    ;
        typedef
      typename length_stride_t::stride_t
    stride_t
    ;
        typedef
      unsigned
    axis_t
    ;
        typedef
      int
    rot_t
      /**@brief
       *  axis rotation amount.
       */
    ;
        typedef
      std::vector
      < length_stride_t
      >
    length_strides_t
    ;
        typedef
      length_stride_compose<length_stride_t> 
    comp_t
    ;
        typedef
      typename comp_t::length_dir_t
    length_dir_t
    ;
        typedef
      typename comp_t::offset_t
    offset_t
    ;
        typedef
      offset_t
    index_t
    ;
        typedef
      std::vector<index_t>
    indices_t
    ;
        typedef
      std::vector<unsigned>
    permute_t
      /**@brief
       *  Type of a permutaion of indices, 0...Rank-1
       *  for some unsigned Rank.
       */
    ;
        typedef typename
      permute_t::value_type
    permute_val_t
    ;
 public:
        typedef
      permute_t
    (*permute_0to_t) //function returning a permutation of [0,a_last)
      ( permute_val_t //a_last
      )
    ;
        static
      permute_t
    identity_permutation
      ( permute_val_t a_last
      )
    {
      return mk_iota( permute_val_t(0), a_last);
    }
    
        static
      permute_t
    reverse_permutation
      ( permute_val_t a_last
      )
    {
      return mk_iota( a_last, permute_val_t(0));
    }
    
        static
      storage_order_predefined const
    storage_order_default
    =store_reverse
    ;
      permute_0to_t
    permute_select
      ( storage_order_predefined a_so=storage_order_default
      )
    {
        static permute_0to_t mk[storage_order_predef_num]=
          { reverse_permutation
          , identity_permutation
          };
        return mk[a_so];
    }
    
 private:    
      offset_t
    my_offset
    /**@brief
     *  Offset from start of array where all 0 index
     *  is located.  my_offset != 0 iff one or more
     *  of the lengths passed to CTOR are < 0.
     */
    ;
      length_strides_t
    my_length_strides
    /**@brief
     *  The length & strides for each axis in a multidimensional array.
     */
    ;
 protected:
 
      template
      < typename Lengths
      >
      stride_t
    init_strides
      ( Lengths const& a_lengths
      , permute_t const& a_permute
      )
      /**@brief
       *  1) Calculates strides of the array with shape, a_lengths,
       *     permuted by a_permute.
       *  2) Initializes my_offset.
       *  3) returns number of elements in a multi-dimenstional
       *     array with these Lengths (which is the
       *     product of the absolute value of all a_length
       *     elements).
       */
    {
        BOOST_ASSERT
        (  ( a_lengths.size() == my_length_strides.size())
        && ( a_permute.size() == my_length_strides.size())
        && permutation::is_permutation( a_permute)
        );
            typedef 
          permutation_iterator
          < typename Lengths::const_iterator
          , permute_t::const_iterator
          >
        plenit_t;
        plenit_t len_beg( a_lengths.begin(), a_permute.begin());
        plenit_t len_end( a_lengths.begin(), a_permute.end());
            typedef 
          permutation_iterator
          < typename length_strides_t::iterator
          , permute_t::const_iterator
          >
        plss_t;
        plss_t lss_beg( my_length_strides.begin(), a_permute.begin());
        my_offset=0;
        plss_t lss_end=
          length_strides_make
            ( len_beg
            , len_end
            , lss_beg
            , my_offset
            );
        return lss_end->space();
    }
    
      template
      < typename Lengths
      >
      stride_t
    init_strides
      ( Lengths const& a_lengths
      , storage_order_predefined a_so=storage_order_default
      )
    {
        return 
        init_strides
        ( a_lengths
        , permute_select
          ( a_so
          )
          ( a_lengths.size()
          )
        );
    }
      
    length_strides_offset
      ( std::size_t a_size
      )
    /**@brief
     *  To be used by subclasses which should
     *  call this->init_strides( a_lengths, ...)
     *  where a_lengths.size() == a_size
     */
    : my_length_strides( a_size)
    {
    }
 public:    
    
    template< typename Lengths>
    length_strides_offset
      ( Lengths const& a_lengths
      , storage_order_predefined a_so=storage_order_default
      )
    : my_length_strides( a_lengths.size())
    {
        init_strides( a_lengths, a_so);
    }
    
    template< typename Lengths>
    length_strides_offset
      ( Lengths const& a_lengths
      , permute_t const& a_permute
      )
    : my_length_strides( a_lengths.size())
    {
        init_strides( a_lengths, a_permute);
    }
    
    length_strides_offset
      ( length_strides_offset const& a_iso
      , index_t a_index
      )
      /**@brief
       *  Let an array, A, be described by a_iso.
       *  This CTOR produces a description of
       *  A[a_index].
       */
      : my_offset
        ( a_iso.offset()
        + a_iso.length_strides().front().stride()
        * a_index
        )
      , my_length_strides
        ( a_iso.begin()+1
        , a_iso.end()
        )
    {
    }
    
    length_strides_offset
      ( struct_op_tag<op_ax_rotate>
      , length_strides_offset const& a_iso
      , axis_t a_axis
      )
      /**@brief
       *  Let an array, A, be described by a_iso.
       *  This CTOR produces a description of an
       *  array, B, with axes, a_axis..A.rank() 
       *  rotated by 1.
       */
      : my_offset
        ( a_iso.offset()
        )
      , my_length_strides
        ( a_iso.rank()
        )
    {
        std::copy //copy 1st part of a_iso
        ( a_iso.begin()
        , a_iso.begin()+a_axis-1
        , my_length_strides.begin()
        );
        std::rotate_copy //copy 2nd part of a_iso rotated by 1.
        ( a_iso.begin()+a_axis
        , a_iso.begin()+a_axis+1
        , a_iso.end()
        , my_length_strides.begin()+a_axis
        );
    }
    
      axis_t
    rank()const
    {
        return my_length_strides.size();
    }
      length_strides_t const&
    length_strides()const
    {
        return my_length_strides;
    }
      typename length_strides_t::const_iterator
    begin()const
    {
        return length_strides().begin();
    }
      offset_t
    offset()const
    {
        return my_offset;
    }
      axis_t
    normalize_rotation
      ( int rotation
      , axis_t a_axis
      )
    {
        axis_t const rnk=rank()-a_axis;
        int nrot=rotation%rnk;//-rnk < nrot && nrot < rnk
        axis_t mrot=(nrot+rnk)%rnk;//0<=mrot && mrot < rnk
        return mrot;
    }
      axis_t
    normalize_axis
      ( axis_t a_axis
      )
    {
        return a_axis%rank();
    }
      void
    axis_rot
      ( int a_rot=1
      , axis_t a_axis=0
      )
    {
        a_axis=normalize_axis(a_axis);
        unsigned const n_rot=normalize_rotation( a_rot, a_axis);
        typedef typename length_strides_t::iterator iter_t;
        iter_t beg=my_length_strides.begin()+a_axis;
        iter_t mid=beg+n_rot;
        iter_t end=my_length_strides.end();
        std::rotate( beg, mid, end);
    }
        static
      offset_t
    offset_at_indices_seq
      ( indices_t const& a_indices_seq
      , typename length_strides_t::const_iterator beg_ls
      , offset_t a_offset
      )
      /**@brief
       *  The offset of element in an array
       *  corresponding to indices in index sequence, a_indices.
       *
       *  This corresponds to equation (5.2) of the @reference.
       */
    {
        typename indices_t::const_iterator beg_i=a_indices_seq.begin();
        typename indices_t::const_iterator end_i=a_indices_seq.end();
        struct get_stride
        {
                typedef 
              stride_t 
            result_type
            ;
              result_type
            operator()(length_stride_t const&ls)const
            {
                return ls.stride();
            }
        };
        return boost::array_stepper::offset_at_indices
          ( beg_i
          , end_i
          , beg_ls
          , get_stride()
          , a_offset
          );
    }
      offset_t
    offset_at_indices_seq
      ( indices_t const& a_indices_seq
      )const
      /**@brief
       *  The offset of element in an array
       *  corresponding to indices in index sequence, a_indices.
       *
       *  This corresponds to equation (5.2) of the @reference.
       */
    {
        typename length_strides_t::const_iterator beg_ls=my_length_strides.begin();
        return offset_at_indices_seq( a_indices_seq, beg_ls, my_offset);
    }
    
    struct get_length_stride
    {
          typename length_stride_t::stride_t
        stride(length_stride_t const&ls)const
        {
            return ls.stride();
        }
          typename length_stride_t::length_t
        length(length_stride_t const&ls)const
        {
            return ls.length();
        }
    };
        
      indices_t
    indices_at_offset
      ( offset_t a_offset
      )const
      /**@brief
       *  The inverse of offset_at_indices_seq.
       *
       *  This corresponds to equation (5.7) in @reference
       *  for each axis.
       */
    {
        typedef typename length_strides_t::const_iterator citer;
        citer beg_ls=my_length_strides.begin();
        citer end_ls=my_length_strides.end();
        return ::boost::array_stepper::indices_at_offset
          < indices_t
          >
          ( beg_ls
          , end_ls
          , get_length_stride()
          , a_offset
          );
    }
    
};

}//exit array_stepper namespace
}//exit boost namespace
#endif
