#ifndef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED

#include <boost/array_stepper/array_store.hpp>
#if 0
#include <boost/array_stepper/array_host.hpp>
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#else
#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>
#include <iostream>
#include <iomanip>
//#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
#ifdef  BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
#include <boost/assert.hpp>
#endif
#endif

#ifndef BOOST_ARRAY_STEPPER_INDEX_STACK_LENGTH_STRIDE_CRTP_HPP_INCLUDED
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
  struct
array_iter_wrap
{
    typedef typename boost::array_stepper::array_store<T> arr_t;
    typedef typename arr_t::data_t::const_iterator iter_t;
    typedef typename arr_t::domain_t domain_t;
    typedef typename domain_t::stride_t stride_t;
        typedef 
      boost::array_stepper::index_stack_length_stride_crtp_indices<stride_t> 
    lsos_t;
    array_iter_wrap
    ( iter_t a_iter
    , lsos_t a_lsos
    )
    : my_iter(a_iter)
    , my_lsos(a_lsos)
    {}
      iter_t const
    my_iter;
      lsos_t const
    my_lsos;
};
  template
  < typename T
  >
  std::ostream&
operator<<
( std::ostream& sout
, array_iter_wrap<T>const& a_arr_iter
)
{
    typedef array_iter_wrap<T> arr_iter_t;
    typedef typename arr_iter_t::lsos_t lsos_t;
    typedef typename arr_iter_t::iter_t iter_t;
    typedef typename lsos_t::axis_depth_t axis_depth_t;
    unsigned const margin=2;
    auto depth_indent=[]( axis_depth_t ad)->int
      {
          return (ad-1)*margin;
      };
    iter_t data_v(a_arr_iter.my_iter);
    lsos_t lsos_v(a_arr_iter.my_lsos);
    int const n=lsos_v.space();
    axis_depth_t axis_now= lsos_v.axis_begin();
  #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
    axis_depth_t const axis_max=axis_now;
  #endif
    axis_depth_t axis_pre=lsos_t::axis_end;
    for(axis_depth_t l=axis_pre; l<axis_now; ++l) 
    { //open 1st element for all axes.
        sout<<"{ ";
    }
    for
      ( int i=0
      ; i<n
      ; ++i
        , axis_pre=axis_now
        , axis_now=++lsos_v
      )
    {
        if(axis_now<axis_pre)
        { //exiting one element and starting next.
            for(axis_depth_t l=axis_pre; axis_now<l; --l) 
            { //close axis_pre to axis_now elements.
                if(l!=axis_pre) 
                    sout<<std::setw(l*margin)<<"";
                sout<<"}\n";
            }
            sout<<std::setw(depth_indent(axis_now))<<""<<", ";//put delimiter between elements
            for(axis_depth_t l=axis_pre; axis_now<l; --l)
            { //open axis_now to axis_pre elements.
                sout<<"{ ";
            }
          #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
            sout<<"(:axis_now="<<axis_now<<"<"<<"axis_pre="<<axis_pre<<")";
            BOOST_ASSERT(axis_pre == axis_max);
          #endif
        }
        else if(lsos_t::axis_end<axis_pre)
        {   sout<<", ";//put delimiter between elements
          #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
            sout<<"(axis_end<axis_pre)";
            auto ibs=lsos_v[axis_now-1];
            auto index_now=ibs.template get<boost::array_stepper::index_value>();
            sout
              <<":axis_now="<<axis_now
              <<":axis_max="<<axis_max
              <<":index_now="<<index_now
              <<"\n";
            BOOST_ASSERT( axis_now==axis_max && 0<index_now);
          #endif
        }
        auto const offset=lsos_v.offset_space_val();
      #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE      
        sout
          <<":i="<<std::setw(2)<<i
          <<":axis_pre="<<axis_pre
          <<":axis_now="<<axis_now
          <<":offset="<<offset
          <<":v="
          ;
      #endif
        sout<<data_v[offset];
    }
    for(axis_depth_t l=axis_pre; axis_now<l; --l)
    {//close axis_pre to axis_now elements.
        if(l!=axis_pre) 
            sout<<std::setw(depth_indent(l))<<"";
        sout<<"}\n";
    }
    #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
    sout
      <<":axis_pre="<<axis_pre
      <<":axis_now="<<axis_now
      <<"\n"
      ;
    #endif
    return sout;
}
  template
  < typename T
  >
  std::ostream&
operator<<
( std::ostream& sout
, boost::array_stepper::array_store<T>const& a_arr
)
{
  #ifdef BOOST_ARRAY_STEPPER_INDEX_STACK_LENGTH_STRIDE_CRTP_HPP_INCLUDED
    typedef typename boost::array_stepper::array_store<T> arr_t;
    typedef typename arr_t::domain_t domain_t;
    typedef typename domain_t::stride_t stride_t;
        typedef 
      boost::array_stepper::index_stack_length_stride_crtp_indices<stride_t> 
    lsos_t;
      lsos_t 
    lsos_v
      ( a_arr.length_strides().begin()
      , a_arr.length_strides().end()
      );
    typedef typename arr_t::data_t data_t;
    auto const offset0=a_arr.offset();
  #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
    sout<<"offset0="<<offset0<<"\n";
  #endif
    typename data_t::const_iterator data_v=a_arr.data().begin()+offset0;
    array_iter_wrap<T> aiw(data_v,lsos_v);
    sout<<aiw;
  #else
    boost::array_stepper::array_store_print<T> a_viz(sout);
    boost::array_stepper::array_host<boost::array_stepper::array_store<T> const> host_arr(a_arr);
    host_arr.accept(a_viz);
  #endif
    return sout;
}    

#endif
