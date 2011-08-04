#if !defined(VMD_DETAIL_TUPLE_NATIVE_HPP)
#define VMD_DETAIL_TUPLE_NATIVE_HPP

#include "vmd_detail_setup.hpp"

#if BOOST_VMD_VARIADICS

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/reverse.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include "vmd_detail_data_native.hpp"
#include "vmd_detail_native.hpp"

#define VMD_DETAIL_REMOVE_TUPLE_PARENS(...) \
  __VA_ARGS__ \
/**/
#define VMD_DETAIL_PP_TUPLE_TO_DATA(tuple) \
  VMD_DETAIL_REMOVE_TUPLE_PARENS tuple \
/**/
#define VMD_DETAIL_PP_TUPLE_ELEM(size,i,tuple) \
  BOOST_PP_TUPLE_ELEM(size,i,tuple) \
/**/
#define VMD_DETAIL_PP_TUPLE_SIZE(tuple) \
  VMD_DETAIL_DATA_SIZE(VMD_DETAIL_PP_TUPLE_TO_DATA(tuple)) \
/**/
#define VMD_DETAIL_PP_TUPLE_REM_CTOR(size,tuple) \
  BOOST_PP_TUPLE_REM_CTOR(size,tuple) \
/**/
#define VMD_DETAIL_PP_TUPLE_REVERSE(size,tuple) \
  BOOST_PP_TUPLE_REVERSE(size,tuple) \
/**/

#endif // BOOST_VMD_VARIADICS
#endif // VMD_DETAIL_TUPLE_NATIVE_HPP
