#if !defined(VMD_DETAIL_REMOVE_PARENS_HPP)
#define VMD_DETAIL_REMOVE_PARENS_HPP

#include <boost/variadic_macro_data/detail/vmd_detail_setup.hpp>

#if BOOST_VMD_VARIADICS

#if BOOST_VMD_PPLIB
#include <boost/variadic_macro_data/detail/vmd_detail_remove_parens_pplib.hpp>
#else
#include <boost/variadic_macro_data/detail/vmd_detail_remove_parens_native.hpp>
#endif /* BOOST_VMD_PPLIB */

#endif /* BOOST_VMD_VARIADICS */
#endif /* VMD_DETAIL_REMOVE_PARENS_HPP */
