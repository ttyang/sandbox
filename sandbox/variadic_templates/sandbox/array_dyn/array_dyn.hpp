#ifndef ARRAY_DYN_HPP_INCLUDED
#define ARRAY_DYN_HPP_INCLUDED
//  (C) Copyright Larry Evans 2012.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//====================================================================
#include <iostream>
#include <iomanip>

#include "box_domain.hpp"

  template
  < typename T
  >
  struct  
array_dyn
/**@brief
 *  Multidimensional array whose
 *  'shape' is defined at runtime.
 *  'Shape' means upper bounds on indices
 *  for each dimension (or axis in apl terminology).
 */
: box_domain<>
{
        typedef
      box_domain<>
    super_t
    ;
        using typename
      super_t::
    index_t
    ;
        typedef
      std::vector<T>
    data_t
    ;
      data_t
    my_data
    /**@brief
     *  data in the array.
     */
    ;

  //[Template interface:
  // This is more general than the
  // Initializer_list interface below.
      template
      < typename Sizes
      >
    array_dyn( dirs a_dir, Sizes const& a_sizes={})
    : super_t( a_dir, a_sizes)
    , my_data( super_t::size())
    {
    }
    
      template
      < typename Sizes
      >
      void
    reshape( Sizes const& a_sizes)
    {
        my_data.resize(super_t::reshape(a_sizes));
    }
    
      template
      < typename Indices
      >
      T&
    operator()( Indices const& a_indices)
    {
        return my_data[offset_at_indices(a_indices)];
    }
    
      template
      < typename Indices
      >
      T const&
    operator()( Indices const& a_indices)const
    {
        return my_data[offset_at_indices(a_indices)];
    }

  //]
  //[Initializer_list interface:
  // Similar to above Template interface, but using 
  // init_list_t(see below) instead of templates.
  // This makes interfaces slightly more user friendly.
        using typename
      super_t::
    init_list_t
    ;
    array_dyn( dirs a_dir, init_list_t const& a_sizes={})
    : super_t( a_dir, a_sizes)
    , my_data( super_t::size())
    {
    }
    
      void
    reshape( init_list_t const& a_sizes)
    {
        this->template reshape<init_list_t>(a_sizes);
    }
    
      T&
    operator()( init_list_t const& a_indices)
    {
        return this->template operator()<init_list_t>(a_indices);
    }
    
      T const&
    operator()( init_list_t const& a_indices)const
    {
        return this->template operator()<init_list_t>(a_indices);
    }
  //]
    
};

  template
  < typename Array
  >
  struct
array_host
{
      Array&
    my_array
    ;
        typedef typename
      Array::index_t
    index_t
    ;
      int const
    my_axis_dir
    /**@brief
     *  +1 or -1: the direction in which axis changes.
     */
    ;
      index_t const
    my_axis_beg
    ;
      index_t const
    my_axis_end
    ;
    array_host
      ( Array& a_array
      , dirs a_dir=dir_fwd
      )
    : my_array(a_array)
    , my_axis_dir
      ( (a_dir==dir_fwd)
      ? +1
      : -1
      )
    , my_axis_beg
      ( (a_dir==dir_fwd)
      ? 0
      : my_array.rank()-1
      )
    , my_axis_end
      ( (a_dir==dir_fwd)
      ? my_array.rank()-1
      : 0
      )
    {
    }
    
      template
      < typename Visitor
      >
      void
    accept
      ( Visitor& a_viz
      )
    {
        accept_off_ax
        ( a_viz
        , 0
        , my_axis_beg
        );
    }
 private:
      template
      < typename Visitor
      >
      void
    accept_off_ax
      ( Visitor& a_viz
      , index_t offset
      , index_t axis_now
      )
    {
        index_t const axis_size=my_array.size(axis_now);
        bool const is_leaf=axis_now==my_axis_end;
        index_t const axis_stride=my_array.stride(axis_now);
        a_viz.visit_pre(is_leaf, axis_now);
        for(index_t i=0; i<axis_size; ++i)
        {
            a_viz.visit_pre(is_leaf, axis_now, i);
            if(is_leaf)
            {
                a_viz.visit_node(my_array.my_data[offset]);
            }
            else
            {
                this->accept_off_ax
                  ( a_viz
                  , offset
                  , axis_now+my_axis_dir
                  );
            }
            offset+=axis_stride;
        }
        a_viz.visit_post(is_leaf, axis_now);
    }
};  

  template
  < typename T
  >
  struct
print_array
  /**@brief
   *  an instance of Array Visitor (i.e. argument to array_host<Array>::accept)
   *  where Array is array_dyn<T> for some T.
   */
{
      std::ostream&
    my_sout
      /**@brief
       *  Where the array_dyn<T> is to be printed.
       */
    ;
      unsigned
    my_indent
      /**@brief
       *  Margin indentation increment.
       *  Each successive axis of the array_dyn<T> is printed
       *  at offset that's a multiple of my_indent.
       *  For example, at axis, Iaxis, indentation is at my_indent*Iaxis.
       */
    ;
        typedef typename
      array_dyn<T>::index_t
    index_t
    ;
    print_array(std::ostream& a_sout, unsigned a_indent=2)
    : my_sout(a_sout)
    , my_indent(a_indent)
    {}
    
    void visit_pre( bool is_leaf, index_t axis)
    {
        my_sout<<std::left<<std::setw(my_indent)<<"{";
    }
    
    void visit_pre( bool is_leaf, index_t axis, index_t index)
    {
        if(index==0)
        {
        }
        else
        {
            if(!is_leaf)
            {
                my_sout<<std::setw(my_indent*axis)<<"";
            }
            my_sout<<std::left<<std::setw(my_indent)<<",";
        }
    }
    
    void visit_node(T const& a_t)
    {
        my_sout<<a_t;
    }
        
    void visit_post( bool is_leaf, index_t axis)
    {
        if(!is_leaf)
        {
            my_sout<<std::setw(my_indent*axis)<<"";
        }
        my_sout<<"}\n";
    }
    
};

  template
  < typename T
  >
  std::ostream&
operator<<
( std::ostream& sout
, array_dyn<T>const& a_arr
)
{
    print_array<T> a_viz(sout);
    array_host<array_dyn<T> const> host_arr(a_arr);
    host_arr.accept(a_viz);
    return sout;
}    

#endif
