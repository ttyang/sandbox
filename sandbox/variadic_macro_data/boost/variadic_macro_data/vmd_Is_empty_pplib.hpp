#if !defined(VMD_IS_EMPTY_PPLIB_HPP)
#define VMD_IS_EMPTY_PPLIB_HPP

#include <boost/variadic_macro_data/detail/vmd_detail_setup.hpp>

#if BOOST_VMD_VARIADICS

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

#if BOOST_VMD_MSVC

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/variadic_macro_data/detail/vmd_detail_is_empty.hpp>

#define BOOST_VMD_IS_EMPTY(param) \
    VMD_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_DEC \
        ( \
        BOOST_PP_VARIADIC_SIZE \
          ( \
          VMD_DETAIL_IS_EMPTY_COMMON_EXPAND param \
          ) \
        ) \
      ) \
      ( \
      VMD_DETAIL_IS_EMPTY_GEN_ZERO, \
      VMD_DETAIL_IS_EMPTY_TUPLE_BEGIN \
      ) \
    (VMD_DETAIL_IS_EMPTY_NON_FUNCTION_C param ()) \
/**/

#endif /* BOOST_VMD_MSVC */
#endif /* BOOST_VMD_VARIADICS */
#endif /* VMD_IS_EMPTY_PPLIB_HPP */
