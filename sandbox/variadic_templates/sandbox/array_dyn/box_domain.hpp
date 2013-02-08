#ifndef BOX_DOMAIN_HPP_INCLUDED
#define BOX_DOMAIN_HPP_INCLUDED
//  (C) Copyright Larry Evans 2012.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//====================================================================
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

enum dirs //directions(used to flag order of processing an ordered sequence).
{ dir_fwd //forward direction.
, dir_rev //reverse direction.
};

  template
  < typename Index_Type = unsigned
  >
  struct
box_domain
  /**@brief
   *  Domain for indices contained within an (hyper)box.
   *  and used to index into (or as the domain of) 
   *  a multidimensional array.
   **@Acknowledgements
   *  Basic idea (and the name) from boost/index_list/domain.hpp
   *  at:
   *    http://svn.boost.org/svn/boost/sandbox/index_list/boost/index_list/domain.hpp
   *  on: 2011-04-23.
   *  
   *  I'm *guessing* that what's missing from this box_domain 
   *  but present in the index_list box_domain are(for I in
   *  0..num_dimensions_-1):
   *    ordering_[I] //Not sure what this is.
   *    ascending_[I] //Not sure what this is.
   *    index_bases_[I] //lower bound for index for I-th axis?
   *    index_tops_[I]  //upper bound for index for I-th axis?
   *  I'm also *guessing* that the my_dirs member variable here
   *  is somehow related to one of:
   *    ordering_
   *    ascending_
   */
{
        typedef
      Index_Type
    index_t
    ;
        typedef
      std::vector<index_t>
    strides_t
    ;
        typedef
      std::vector<index_t>
    indices_t
    ;
        typedef
      std::vector<index_t>
    shape_t
    ;
      strides_t
    my_strides
    /**@brief
     *  The strides for each axis in a multidimensional array.
     */
    ;
      dirs const
    my_dir
    /**@brief
     *  Either dir_fwd or dir_rev.
     *    If dir_rev, then my_strides[i]/my_strides[i+1] > 0
     *    Otherwise,  my_strides[i+1]/my_strides[i] > 0
     */
    ;
    
    ~box_domain()
    {
        //std::cout<<__FILE__<<":"<<__LINE__<<"~box_domain"<<":this="<<(void*)this<<"\n";
    }
      template
      < typename InpIter
      , typename OutIter
      >
      OutIter
    init_iter_strides
      ( InpIter sizes_beg
      , InpIter sizes_end
      , OutIter strides
      )
      /**@brief
       *  Helper function for init_strides( Sizes...)
       */
    {
        //std::cout<<__FILE__<<":"<<__LINE__<<"box_domain:init_iter_strides"<<":this="<<(void*)this<<"\n";
        *strides=1;
        return
        std::partial_sum
        ( sizes_beg
        , sizes_end
        , ++strides
        , std::multiplies<index_t>()
        );
    }
    
      template
      < typename Sizes
      >
      index_t
    init_strides
      ( Sizes const& a_sizes
      )
      /**@brief
       *  Calculates strides of the array with shape, a_size...
       *  If(my_dir==dir_fwd) then strides increase with index;
       *  otherwise, they decrease with index.
       *  Returns the size of the whole array, IOW, the
       *  product of a_size...
       */
    {
        index_t result;
        if(my_dir==dir_fwd)
        {
              auto
            it_v=init_iter_strides
              ( a_sizes.begin()
              , a_sizes.end()
              , my_strides.begin()
              );
            result=*(--it_v);
        }
        else
        {
                typedef typename
              Sizes::const_iterator
            fwd_iter;
                typedef
              std::reverse_iterator<fwd_iter>
            rev_iter;
              rev_iter
            rbeg(a_sizes.end());
              rev_iter
            rend(a_sizes.begin());
              auto
            it_v=init_iter_strides
              ( rbeg
              , rend
              , my_strides.rbegin()
              );
            result=*(--it_v);
        }
        return result;
    }
    
      dirs
    dir()const
    {
        return dirs(my_dir);
    }
      index_t
    rank()const
    {
        return my_strides.size()-1;
    }
    
      index_t
    stride(index_t Index)const
      /**@brief
       *  stride of Index-th axis.
       */
    {
        return my_strides[Index+my_dir];
    }
    
      index_t
    size(index_t Index)const
      /**@brief
       *  size of Index-th axis
       */
    {
        index_t const greater=(my_dir+1)%2;
        return my_strides[Index+greater]/my_strides[Index+my_dir];
    }
    
      index_t
    size()const
      /**@brief
       *  size of complete array.
       */
    {
        return 
          (my_dir==dir_fwd)
          ? my_strides[my_strides.size()-1]
          : my_strides[0]
          ;
    }
 
      template
      < typename InpIter
      , typename OutIter
      >
      void
    indices_at_offset
      ( index_t a_offset
      , InpIter strides_beg
      , InpIter strides_end
      , OutIter indices
      )const
      /**@brief
       *  Helper function for unary indices_at_offset(see below).
       */
    {
        std::transform
          ( strides_beg
          , strides_end
          , indices
          , [&a_offset](index_t stride)
            { 
                index_t index=a_offset/stride;
                a_offset-=index*stride;
                return index; 
            }
          );
    }
    
      indices_t
    indices_at_offset
      ( index_t offset
      )const
      /**@brief
       *  Inverse of offset_at_indices
       */
    {
        indices_t indices_v(rank());
        if(my_dir==dir_fwd)
        {
            indices_at_offset
            ( offset
            , my_strides.rbegin()+1
            , my_strides.rend()
            , indices_v.rbegin()
            );
        }
        else
        {
            indices_at_offset
            ( offset
            , my_strides.begin()+1
            , my_strides.end()
            , indices_v.begin()
            );
        }
        return indices_v;
    }

      template
      < typename StrideIter
      , typename ShapeIter
      >
        static
      void
    iter_shape
      ( StrideIter beg_stride
      , StrideIter end_stride
      , ShapeIter beg_shape
      )
    {
        for(; beg_stride!=end_stride; ++beg_stride,++beg_shape)
        {
            *beg_shape=(*(beg_stride+1))/(*beg_stride);
        }
    }
      shape_t
    shape
      (
      )const
      /**@brief
       *  Returns shape(i.e. lengths of axes).
       */
    {
        shape_t shape_v(rank());
        if(my_dir==dir_fwd)
        {
            iter_shape
            ( my_strides.begin()
            , my_strides.end()
            , shape_v.begin()
            );
        }
        else
        {   
                typedef typename
              strides_t::const_iterator
            fwd_iter;
                typedef
              std::reverse_iterator<fwd_iter>
            rev_iter;
              rev_iter
            rbeg(my_strides.end());
              rev_iter
            rend(my_strides.begin());
            iter_shape
              ( rbeg
              , rend
              , shape_v.rbegin()
              );
        }
        return shape_v;
    }
    
  //[Template interface:
  // This is more general than the
  // Initializer_list interface shown farther below.
  
      template
      < typename Sizes
      >
    box_domain( dirs a_dir, Sizes const& a_sizes)
    : my_strides( a_sizes.size()+1)
    , my_dir(a_dir)
    {
        init_strides( a_sizes);
      #if 0
        std::cout<<__FILE__<<":"<<__LINE__
          <<":a_sizes="<<a_sizes
          <<":my_strides="<<my_strides
          <<"\n";
      #endif
    }
    
    box_domain( box_domain const& a_self)
    : my_strides( a_self.my_strides)
    , my_dir(a_self.my_dir)
    {
      #if 0
        std::cout<<__FILE__<<":"<<__LINE__
          <<":my_strides="<<my_strides
          <<":my_dir="<<my_strides
          <<":this="<<(void*)this
          <<"\n";
      #endif
    }
    
      template
      < typename Indices
      >
      index_t
    offset_at_indices
      ( Indices const& a_indices
      )const
      /**@brief
       *  The offset of element in an array
       *  corresponding to indices, a_index...
       */
    {
        index_t const offset
          = std::inner_product
            ( a_indices.begin()
            , a_indices.end()
            , my_strides.begin()+my_dir
            , index_t(0)
            );
        return offset;
    }
    
      template
      < typename Indices
      >
      index_t
    reshape( Indices const& a_sizes)
    {
        index_t const rankp1=a_sizes.size()+1;
        my_strides.resize(rankp1);
        return init_strides( a_sizes);
    }
    
      template
      < typename Indices
      >
      bool
    ok_indices( Indices const& a_indices)
      /**@brief
       *  Is a_index... a valid argument to
       *  offset_at_indices?
       */
    {
        unsigned n=a_indices.size();
        bool result= n<=rank();
        auto index_iter=a_indices.begin();
        for( unsigned i=0; i<n && result; ++i,++index_iter)
        {
            index_t index_i=*index_iter;
            result = index_i<size(i);
        }
        return result;
    }
    
  //]Template interface:
  //[Initializer_list interface:
        typedef
      std::initializer_list<index_t>
    init_list_t
    ;
    
    box_domain( dirs a_dir, init_list_t const& a_sizes)
    : my_strides( a_sizes.size()+1)
    , my_dir(a_dir)
    {
        init_strides( a_sizes);
    }
    
      index_t
    offset_at_indices
      ( init_list_t const& a_indices
      )const
    {
        return this->template offset_at_indices<init_list_t>(a_indices);
    }
    
      index_t
    reshape( init_list_t const& a_sizes)
    {
        return this->template reshape<init_list_t>( a_sizes);
    }
    
      bool
    ok_indices( init_list_t const& a_indices)
    {
        return this->template ok_indices<init_list_t>(a_indices);
    }
    
  //]Initializer_list interface:
};

#endif
