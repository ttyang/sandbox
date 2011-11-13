#ifndef BOOST_ARRAY_STEPPER_LENGTH_STRIDES_MAKE_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_LENGTH_STRIDES_MAKE_HPP_INCLUDED
#include <boost/array_stepper/length_stride_compose.hpp>
#include <boost/array_stepper/scan_first_iter.hpp>

namespace boost
{
namespace array_stepper
{
    template
    < typename InpIter
    , typename OutIter
    >
    OutIter
  length_strides_make
    ( InpIter a_inp_beg
    , InpIter a_inp_end
    , OutIter a_out_beg
    , typename length_stride_compose<typename OutIter::value_type>::offset_t& a_offset
    )
    {
        typedef typename OutIter::value_type value_t;
        typedef length_stride_compose<value_t> comp_t;
        comp_t comp_v(a_offset);
        return 
          scan_first_iter
          ( comp_v
          , a_inp_beg
          , a_inp_end
          , a_out_beg
          );
    };

}//exit array_stepper namespace
}//exit boost namespace
#endif
