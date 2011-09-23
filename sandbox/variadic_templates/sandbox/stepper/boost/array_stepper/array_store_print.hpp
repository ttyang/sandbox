#ifndef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED

#include <boost/array_stepper/array_store.hpp>
#if 1
#include <boost/array_stepper/array_host.hpp>
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#else
#include <boost/array_stepper/length_stride_offset_iter_stack.hpp>
#include <iostream>
#include <iomanip>
//#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
#ifdef  BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
#include <boost/assert.hpp>
#endif
#endif

#ifndef BOOST_ARRAY_STEPPER_LENGTH_STRIDE_OFFSET_ITER_STACK_HPP_INCLUDED
namespace boost
{
namespace array_stepper
{
  template
  < typename T
  >
  struct
array_store_print
{
      std::ostream&
    my_sout
    ;
        typedef typename
      array_store<T>::index_t
    index_t
    ;
    array_store_print
      ( std::ostream& a_sout
      )
    : my_sout(a_sout)
    {}
    
    void null_array( )const
    {
        my_sout<<"(null_array)";
    }
    
    void pre_children()
    {
        my_sout<<"{ ";
    }
    
    void pre_child( index_t index)
    {
        if(0<index) my_sout<<", ";
        my_sout<<indent_buf_in;
    }
    
    void visit_child( T const& a_t)
    {
      #if 0
        ::operator<<( my_sout, a_t);
        //MAINTENANCE_NOTE:2011-06-29 with gcc4.6:
        //  For some strange reason, have to use above with
        //  gcc instead of what's in #else part because
        //  otherwise compiler gives error saying:
        //    no match for 'operator<<'
        //  when T is std::vector<unsigned> even though
        //  there is a:
        //      std::ostream& 
        //    operator<<
        //      ( std::ostream&
        //      , std::vector<unsigned>const&
        //      );
        //  defined.
      #else
        my_sout<<a_t;
      #endif
    }
        
    void post_child( )
    {
        my_sout<<indent_buf_out;
    }
    
    void post_children()
    {
        my_sout<<"}\n";
    }
    
};

}//exit array_stepper namespace
}//exit boost namespace
#endif

  template
  < typename T
  >
  std::ostream&
operator<<
( std::ostream& sout
, boost::array_stepper::array_store<T>const& a_arr
)
{
  #ifdef BOOST_ARRAY_STEPPER_LENGTH_STRIDE_OFFSET_ITER_STACK_HPP_INCLUDED
    typedef typename boost::array_stepper::array_store<T> arr_t;
    typedef typename arr_t::domain_t domain_t;
    typedef boost::array_stepper::length_stride_offset_iter_stack<> lsos_t;
      lsos_t 
    lsos_v
      ( a_arr.length_strides().begin()
      , a_arr.length_strides().end()
      );
    typedef typename arr_t::data_t data_t;
    data_t const& data_v=a_arr.data();
    int const n=data_v.size();
    typename lsos_t::indices_t const& indices_v=lsos_v.indices();
    int const axis_max=indices_v.size()-1;
    int axis_now= axis_max;
    int axis_pre=-1;
    for(int l=axis_pre; l<axis_now; ++l) 
    { //open 1st element for all axes.
        sout<<"{ ";
    }
    for(int i=0; i<n; ++i,axis_pre=axis_now,axis_now=++lsos_v)
    {
        if(axis_now<axis_pre)
        { //exiting one element and starting next.
            for(int l=axis_pre; axis_now<l; --l) 
            { //close axis_pre to axis_now elements.
                if(l!=axis_pre) 
                    sout<<std::setw(l*2)<<"";
                sout<<"}\n";
            }
            sout<<std::setw(axis_now*2)<<""<<", ";//put delimiter between elements
            for(int l=axis_pre; axis_now<l; --l)
            { //open axis_now to axis_pre elements.
                sout<<"{ ";
            }
          #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
            sout<<"(axis_now<axis_pre)";
            BOOST_ASSERT(axis_pre == axis_max);
          #endif
        }
        else if(-1<axis_pre)
        {   sout<<", ";//put delimiter between elements
          #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
            sout<<"(-1<axis_pre)";
            BOOST_ASSERT( axis_now==axis_max && 0<indices_v[axis_now]);
          #endif
        }
      #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE      
        sout
          <<":i="<<std::setw(2)<<i
          <<":axis_pre="<<axis_pre
          <<":axis_now="<<axis_now
          <<":v="
          ;
      #endif
        sout<<data_v[lsos_v.offset()];
    }
    for(int l=axis_pre; axis_now<l; --l)
    {//close axis_pre to axis_now elements.
        if(l!=axis_pre) 
            sout<<std::setw(l*2)<<"";
        sout<<"}\n";
    }
    #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
    sout
      <<":axis_pre="<<axis_pre
      <<":axis_now="<<axis_now
      <<"\n"
      ;
    #endif
  #else
    boost::array_stepper::array_store_print<T> a_viz(sout);
    boost::array_stepper::array_host<boost::array_stepper::array_store<T> const> host_arr(a_arr);
    host_arr.accept(a_viz);
  #endif
    return sout;
}    

#endif
