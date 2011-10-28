#ifndef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED

#include <boost/array_stepper/array_store.hpp>
#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>
#include <iostream>
#include <iomanip>
//#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
#ifdef  BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
#include <boost/assert.hpp>
#endif

  template
  < typename T
  >
  struct
array_iter_wrap
  /**@brief
   *   Simple wrapper to allow printing of array_store<T>
   *   "configured" with index_stack_length_stride_crtp_indices.
   */
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
    char const open_delim='{';
    char const between_delim=',';
    char const close_delim='}';
    unsigned const margin=2;
    auto fmtflags0=sout.flags(std::ios_base::left);
    auto between_close_width=[]( axis_depth_t ad)->int
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
    
    auto open_delims=[ &]( axis_depth_t ax_beg, axis_depth_t ax_end)
      {
        for(axis_depth_t l=ax_beg; l<ax_end; ++l) 
        { //open 1st element for axes ax_beg...ax_end-1.
            sout<<std::setw(margin)<<open_delim;
        }
      };
    auto close_delims=[ &]( )
      {
        for(axis_depth_t l=axis_pre; axis_now<l; --l)
        {//close axis_pre to axis_now elements.
            if(l!=axis_pre) 
                sout<<std::setw(between_close_width(l))<<"";
            sout<<close_delim<<"\n";
        }
      };
      
    open_delims( axis_pre, axis_now);
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
            close_delims();
            sout<<std::setw(between_close_width(axis_now))<<""
              <<std::setw(margin)<<between_delim;//put delimiter between elements
            open_delims( axis_now, axis_pre);
          #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
            sout<<"(:axis_now="<<axis_now<<"<"<<"axis_pre="<<axis_pre<<")";
            BOOST_ASSERT(axis_pre == axis_max);
          #endif
        }
        else if(lsos_t::axis_end<axis_pre)
        {   sout<<std::setw(margin)<<between_delim;//put delimiter between elements
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
    close_delims();
    #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE          
    sout
      <<":axis_pre="<<axis_pre
      <<":axis_now="<<axis_now
      <<"\n"
      ;
    #endif
    sout.flags(fmtflags0);
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
