// (-*- C++ -*- header)  

/*
 * 
 * Copyright (c) 2002, 2003 Kresimir Fresl, Toon Knapen and Karl Meerbergen
 *
 * Permission to copy, modify, use and distribute this software 
 * for any non-commercial or commercial purpose is granted provided 
 * that this license appear on all copies of the software source code.
 *
 * Authors assume no responsibility whatsoever for its use and makes 
 * no guarantees about its quality, correctness or reliability.
 *
 * First author acknowledges the support of the Faculty of Civil 
 * Engineering, University of Zagreb, Croatia.
 *
 */

#ifndef BOOST_NUMERIC_BINDINGS_TRAITS_MATRIX_TRAITS_HPP
#define BOOST_NUMERIC_BINDINGS_TRAITS_MATRIX_TRAITS_HPP

#include <boost/numeric/bindings/traits/config.hpp> 

#ifndef BOOST_NUMERIC_BINDINGS_POOR_MANS_TRAITS

#include <boost/type_traits/remove_const.hpp> 

namespace boost { namespace numeric { namespace bindings { namespace traits {

  /// Auxiliary traits class to reduce the number of specializations.
  /// MType is the actual matrix type.
  /// MIdentifier is used to specialize the traits for a specific matrix type, e.g.
  /// matrix_detail_traits< ublas::matrix<double>, ublas::matrix<double> const >
  /// matrix_detail_traits< ublas::matrix<double>, ublas::matrix<double> >
  /// Note that  remove_const<MType>::type  == MIdentifier²
  template <typename MIdentifier, typename MType>
  struct matrix_detail_traits {};

  /// matrix_traits<> generic version: 
  /// There is default implemented since there is no
  /// reasonable default. Most matrix libraries
  /// provide totally different functions.
  template <typename M>
  struct matrix_traits : matrix_detail_traits< typename boost::remove_const<M>::type, M> {
    // typedefs:
    //   value_type
    //   pointer
    //   matrix_structure 
    //   ordering_type
    // static functions:
    //   pointer storage()
    //   int storage_size()
    //   int size1()
    //   int size2()
    //   int leading_dimension()  // not all matrix types 
    // symmetric/hermitian typedefs:
    //   uplo_type 
  }; 

  // matrix structure tags:
  struct general_t {}; 
  struct symmetric_t {}; 
  struct symmetric_packed_t {}; 
  struct hermitian_t {}; 
  struct hermitian_packed_t {}; 
  // triangular, banded etc. 
  struct unknown_structure_t {}; 

  // storage ordering tags: 
  struct row_major_t {};
  struct column_major_t {};

  // upper/lower tags:
  struct upper_t {};
  struct lower_t {};


  ///////////////////////////
  //
  // free accessor functions
  //
  ///////////////////////////

  template <typename M>
  inline
  typename matrix_traits<M>::pointer matrix_storage (M& m) { 
    return matrix_traits<M>::storage (m); 
  }
  
  template <typename M>
  inline
  int matrix_size1 (M& m) { 
    return matrix_traits<M>::size1 (m); 
  }
  
  template <typename M>
  inline
  int matrix_size2 (M& m) { 
    return matrix_traits<M>::size2 (m); 
  }
  
  template <typename M>
  inline
  int matrix_storage_size (M& m) { 
    return matrix_traits<M>::storage_size (m); 
  }
  
  template <typename M>
  inline
  int matrix_stride1 (M& m) { 
    return matrix_traits<M>::stride1 (m); 
  }
  
  template <typename M>
  inline
  int matrix_stride2 (M& m) { 
    return matrix_traits<M>::stride2 (m); 
  }
  
  template <typename M>
  inline
  int leading_dimension (M& m) { 
    return matrix_traits<M>::leading_dimension (m); 
  }
  
  namespace detail {

    inline char m_uplo_tag (upper_t const&) { return 'U'; } 
    inline char m_uplo_tag (lower_t const&) { return 'L'; } 

  }

  template <typename SymmM> 
  inline 
  char matrix_uplo_tag (SymmM&) {
      typedef typename matrix_traits<SymmM>::uplo_type uplo_t; 
      return detail::m_uplo_tag (uplo_t());
  }
  
}}}}  

#else // BOOST_NUMERIC_BINDINGS_POOR_MANS_TRAITS

#include <boost/numeric/bindings/traits/matrix_raw.hpp> 

#endif // BOOST_NUMERIC_BINDINGS_POOR_MANS_TRAITS

#endif // BOOST_NUMERIC_BINDINGS_TRAITS_MATRIX_TRAITS_HPP
