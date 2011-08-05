#if !defined(VMD_ASSERT_IS_ARRAY_NATIVE_HPP)
#define VMD_ASSERT_IS_ARRAY_NATIVE_HPP

#include <boost/variadic_macro_data/detail/vmd_detail_setup.hpp>

#if BOOST_VMD_VARIADICS

#if BOOST_VMD_ASSERT_DATA

#if !BOOST_VMD_MSVC

#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/variadic_macro_data/vmd_assert_is_tuple.hpp>
#include <boost/variadic_macro_data/vmd_tuple.hpp>
#include <boost/variadic_macro_data/detail/vmd_detail_assert_is_array.hpp>
#include <boost/variadic_macro_data/detail/vmd_detail.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

#define BOOST_VMD_ASSERT_IS_ARRAY(x) \
    BOOST_VMD_ASSERT_IS_TUPLE(x) \
    BOOST_PP_ASSERT \
      ( \
      BOOST_PP_IIF \
        ( \
        BOOST_PP_EQUAL(2,BOOST_VMD_PP_TUPLE_SIZE(x)), \
        VMD_DETAIL_ASSERT_IS_ARRAY_CHECK_ARRAY_FORM, \
        VMD_DETAIL_GEN_ZERO \
        ) \
      (x) \
      ) \
/**/

#endif /* BOOST_VMD_MSVC */
#endif /* BOOST_VMD_ASSERT_DATA */
#endif /* BOOST_VMD_VARIADICS */
#endif /* VMD_ASSERT_IS_ARRAY_NATIVE_HPP */
