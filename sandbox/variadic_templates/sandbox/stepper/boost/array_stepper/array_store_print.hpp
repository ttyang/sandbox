#ifndef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_HPP_INCLUDED

#include <boost/array_stepper/array_store.hpp>
#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
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
    char const*const open_delim   ="{";
    char const*const between_delim=",";
    char const*const close_delim  ="}";
    auto get_margin=[ &sout]( unsigned defmarg)->unsigned
      {
          typedef boost::iostreams::indent_scoped_ostreambuf<> filt_scoped_type;
          typedef typename filt_scoped_type::push_filt_strmbuf filt_strmbuf_type;
          filt_strmbuf_type*buf_ptr = dynamic_cast<filt_strmbuf_type*>(sout.rdbuf());
          unsigned width=defmarg;
          if (buf_ptr) 
          {
              typedef typename filt_strmbuf_type::filt_type filt_type;
              filt_type* filt_ptr=buf_ptr->filt_get();
              int w=filt_ptr->width();
              if(0<w)width=w;
          }
          return width;
      };
      unsigned 
    margin=
      get_margin( 2)
      //MAINTENANCE_NOTE: 2011-11-25: LJEVANS
      //  with ftp://gcc.gnu.org/pub/gcc/snapshots/4.7-20111008 compiler
      //  and with const qualifier, the compiler issues warning saying
      //  margin may be uninitialized in one of the lambda functions below
      //  and when run, the program goes into infinite loop.  
      //
      //  However, without const qualifier, no warning is issued 
      //  and program runs to completion.
      ;
    auto fmtflags0=sout.flags(std::ios_base::left);
    iter_t data_v(a_arr_iter.my_iter);
    lsos_t lsos_v(a_arr_iter.my_lsos);
    int const n=lsos_v.space();
    if( 0==n) return sout;
    axis_depth_t const axis_max= lsos_v.axis_begin();
    axis_depth_t axis_now=axis_max;
    axis_depth_t axis_pre=lsos_t::axis_end;
  #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE
    std::cout
      <<":n="<<n
      <<":axis_max="<<axis_max
      <<"\n";
  #endif
    auto put_open_delims=[ =, &sout]( axis_depth_t ax_beg, axis_depth_t ax_end)
      {
        for(axis_depth_t l=ax_beg; l<ax_end; ++l) 
        {
            sout<<std::setw(margin)<<open_delim;
            sout<<indent_buf_in;
        }
      };
    auto put_close_delims=[ =, &sout]( axis_depth_t ax_beg, axis_depth_t ax_end)
      {
        for(axis_depth_t l=ax_beg; l<ax_end; ++l)
        {
            sout<<indent_buf_out;
            sout<<std::setw(margin)<<close_delim<<"\n";
        }
      };
    auto put_between_delim=[ =, &sout]()
      {
        sout<<std::setw(margin)<<between_delim;
      };
    auto put_between_delims=[ =, &sout]( axis_depth_t ax_beg, axis_depth_t ax_end)
      {
        put_close_delims( ax_beg, ax_end);
        sout<<indent_buf_out;
        put_between_delim();
        sout<<indent_buf_in;
        put_open_delims ( ax_beg, ax_end);
      };
  #if defined(BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE)
    sout
      <<"(\n";
  #endif
    put_open_delims( axis_pre, axis_now);
    for
      ( int i=0
      ; i<n
      ; ++i
        , axis_pre=axis_max
        , axis_now=++lsos_v
      )
    {
        auto indices_rotated=lsos_v.indices_rotated();
      #if defined(BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE)
        sout
          <<":i="<<std::setw(2)<<i
          <<":axis_pre="<<axis_pre
          <<":axis_now="<<axis_now
          <<":indices_rotated="<<indices_rotated
          <<";";
      #endif
      #if 1
        if(axis_pre==axis_now)
        {
            put_between_delim();
        }
        else if(0<axis_pre)
        {
            if( axis_pre<axis_now)
              put_between_delim();
            else
              put_between_delims( axis_now, axis_pre);
        }
      #endif
        auto const offset=lsos_v.offset_space_val();
      #ifdef BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE      
        sout
          <<":offset="<<offset
          <<":v="
          ;
        sout.flush();
      #endif
        sout<<data_v[offset];
    }
  #if defined(BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE)
    sout
      <<":axis_pre="<<axis_pre
      <<":axis_now="<<axis_now
      <<"."
      ;
  #endif
    put_close_delims( axis_now, axis_pre);
  #if defined(BOOST_ARRAY_STEPPER_ARRAY_STORE_PRINT_TRACE)
    sout
      <<")"
      <<".\n"
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
