//
//  Copyright Toon Knapen, Karl Meerbergen
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "../../blas/test/random.hpp"

#include <boost/numeric/bindings/ublas/matrix.hpp>
#include <boost/numeric/bindings/ublas/vector.hpp>
#include <boost/numeric/bindings/lapack/computational/geqrf.hpp>
#include <boost/numeric/bindings/lapack/computational/ormqr.hpp>
#include <boost/numeric/bindings/lapack/computational/orgqr.hpp>
#include <boost/numeric/bindings/lapack/computational/unmqr.hpp>
#include <boost/numeric/bindings/lapack/computational/ungqr.hpp>
#include <boost/numeric/bindings/ublas/matrix.hpp>
#include <boost/numeric/bindings/ublas/vector.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/type_traits/is_complex.hpp>
#include <boost/mpl/if.hpp>

#include <iostream>
#include <limits>


namespace ublas = boost::numeric::ublas;
namespace lapack = boost::numeric::bindings::lapack;
namespace bindings = boost::numeric::bindings;

struct apply_real {
  template< typename MatrixA, typename VectorTAU, typename Workspace >
  static inline integer_t orgqr( const integer_t m, const integer_t n,
        const integer_t k, MatrixA& a, const VectorTAU& tau, Workspace work ) {
    return lapack::orgqr( m, n, k, a, tau, work );
  }
  template< typename MatrixA, typename VectorTAU, typename MatrixC,
        typename Workspace >
  static inline integer_t ormqr( const char side, const char trans,
        const integer_t k, const MatrixA& a, const VectorTAU& tau, MatrixC& c,
        Workspace work ) {
    return lapack::ormqr( side, trans, k, a, tau, c, work );
  }
};

struct apply_complex {
  template< typename MatrixA, typename VectorTAU, typename Workspace >
  static inline integer_t orgqr( const integer_t m, const integer_t n,
        const integer_t k, MatrixA& a, const VectorTAU& tau, Workspace work ) {
    return lapack::ungqr( m, n, k, a, tau, work );
  }
  template< typename MatrixA, typename VectorTAU, typename MatrixC,
        typename Workspace >
  static inline integer_t ormqr( const char side, const char trans,
        const integer_t k, const MatrixA& a, const VectorTAU& tau, MatrixC& c,
        Workspace work ) {
    return lapack::unmqr( side, trans, k, a, tau, c, work );
  }
};


// Randomize a matrix
template <typename M>
void randomize(M& m) {
   typedef typename M::size_type  size_type ;
   typedef typename M::value_type value_type ;

   size_type size1 = m.size1() ;
   size_type size2 = m.size2() ;

   for (size_type i=0; i<size2; ++i) {
      for (size_type j=0; j<size1; ++j) {
         m(j,i) = random_value< value_type >() ;
      }
   }
} // randomize()


template <typename T>
struct transpose {
   static const char value ;
};

template <typename T>
const char transpose<T>::value = 'T';



template <typename T>
struct transpose< std::complex<T> > {
   static const char value ;
};

template <typename T>
const char transpose< std::complex<T> >::value = 'C';

template <typename M>
ublas::triangular_adaptor<const M, ublas::upper> upper_part(const M& m) {
   return ublas::triangular_adaptor<const M, ublas::upper>( m );
}

template <typename T, typename W>
int do_memory_type(int n, W workspace) {
   typedef typename boost::mpl::if_<boost::is_complex<T>, apply_complex, apply_real>::type apply_t;
   typedef typename bindings::remove_imaginary<T>::type real_type ;
   typedef std::complex< real_type >                                            complex_type ;

   typedef ublas::matrix<T, ublas::column_major> matrix_type ;
   typedef ublas::vector<T>                      vector_type ;

   // Set matrix
   matrix_type a( n, n );
   vector_type tau( n );

   randomize( a );
   matrix_type a2( a );
   matrix_type a3( a );

   // Compute QR factorization.
   lapack::geqrf( a, tau, workspace ) ;

   // Apply the orthogonal transformations to a2
   apply_t::ormqr( 'L', transpose<T>::value, bindings::size (tau), a, tau, a2, workspace );

   // The upper triangular parts of a and a2 must be equal.
   if (norm_frobenius( upper_part( a - a2 ) )
            > std::numeric_limits<real_type>::epsilon() * 10.0 * norm_frobenius( upper_part( a ) ) ) return 255 ;

   // Generate orthogonal matrix
   apply_t::orgqr( bindings::size_row (a), bindings::size_column (a), bindings::size (tau), a, tau, workspace );

   // The result of lapack::ormqr and the equivalent matrix product must be equal.
   if (norm_frobenius( a2 - prod(herm(a), a3) )
            > std::numeric_limits<real_type>::epsilon() * 10.0 * norm_frobenius( a2 ) ) return 255 ;

   return 0 ;
} // do_value_type()



template <typename T>
int do_value_type() {
   const int n = 8 ;
   
   if (do_memory_type<T,lapack::optimal_workspace>( n, lapack::optimal_workspace() ) ) return 255 ;
   if (do_memory_type<T,lapack::minimal_workspace>( n, lapack::minimal_workspace() ) ) return 255 ;

   ublas::vector<T> work( n );
   if (do_memory_type<T, lapack::detail::workspace1<ublas::vector<T> > >( n, lapack::workspace(work) ) ) return 255 ;
   return 0;
} // do_value_type()


int main() {
   // Run tests for different value_types
   if (do_value_type<float>()) return 255;
   if (do_value_type<double>()) return 255;
   if (do_value_type< std::complex<float> >()) return 255;
   if (do_value_type< std::complex<double> >()) return 255;

   std::cout << "Regression test succeeded\n" ;
   return 0;
}

