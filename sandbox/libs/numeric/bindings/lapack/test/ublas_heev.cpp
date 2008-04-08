//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//  Copyright Toon Knapen, Karl Meerbergen
//

#include "../../blas/test/random.hpp"

#include <boost/numeric/bindings/lapack/heev.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#include <boost/numeric/bindings/traits/ublas_vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <iostream>
#include <limits>


namespace ublas = boost::numeric::ublas;
namespace lapack = boost::numeric::bindings::lapack;


// Fill a matrix
template <typename M>
void fill(M& m) {
   typedef typename M::size_type  size_type ;
   typedef typename M::value_type value_type ;

   typedef typename boost::numeric::bindings::traits::type_traits<value_type>::real_type real_type ;

   int size = m.size2() ;

   for (int i=0; i<size; ++i) {
      for (int j=0; j<i; ++j) {
         m(j,i) = random_value<value_type>();
         m(i,j) = conj( m(j,i ) ) ;
      }
      m(i,i) = random_value<real_type>();
   }
} // randomize()


template <typename H, typename E, typename Z>
int check_residual(H const& h, E const& e, Z const& z) {
   typedef typename H::value_type value_type ;
   typedef typename E::value_type real_type ;

   // Check eigen decomposition
   int n = h.size1();
   ublas::matrix<value_type> error( n, n ); error.clear();

   // Copy band matrix in error
   error.assign( h );
   assert( norm_frobenius( error - herm( error ) ) == 0.0 ) ;

   for (int i=0; i<n; ++i) {
      error .minus_assign( outer_prod( column(z, i), e(i) * conj( column(z, i) ) ) ) ;
   }
   return (norm_frobenius( error )
           >= n* norm_2( e ) * std::numeric_limits< real_type >::epsilon() ) ;
} // check_residual()


template <typename T, typename W, char UPLO>
int do_memory_uplo(int n, W& workspace ) {
   typedef typename boost::numeric::bindings::traits::type_traits<T>::real_type real_type ;

   typedef ublas::matrix<T, ublas::column_major>     matrix_type ;
   typedef ublas::vector<real_type>                  vector_type ;

   // Set matrix
   matrix_type a( n, n ); a.clear();
   vector_type e1( n );
   vector_type e2( n );

   fill( a );
   matrix_type a2( a );

   // Compute Schur decomposition.
   lapack::heev( 'V', UPLO, a, e1, workspace ) ;

   if (check_residual( a2, e1, a )) return 255 ;

   lapack::heev( 'N', UPLO, a2, e2, workspace ) ;
   if (norm_2( e1 - e2 ) > n * norm_2( e1 ) * std::numeric_limits< real_type >::epsilon()) return 255 ;

   // Test for a matrix range
   fill( a ); a2.assign( a );

   typedef ublas::matrix_range< matrix_type > matrix_range ;

   ublas::range r(1,n-1) ;
   matrix_range a_r( a, r, r );
   ublas::vector_range< vector_type> e_r( e1, r );

   lapack::heev( 'V', UPLO, a_r, e_r, workspace );

   matrix_range a2_r( a2, r, r );
   if (check_residual( a2_r, e_r, a_r )) return 255 ;

   return 0 ;
} // do_memory_uplo()


template <typename T, typename W>
int do_memory_type(int n, W workspace) {
   std::cout << "  upper\n" ;
   if (do_memory_uplo<T,W,'U'>(n, workspace)) return 255 ;
   std::cout << "  lower\n" ;
   if (do_memory_uplo<T,W,'L'>(n, workspace)) return 255 ;
   return 0 ;
}


template <typename T>
struct Workspace {
   typedef typename ublas::type_traits<T>::real_type                        real_type ;
   typedef ublas::vector< real_type >                                       real_array_type ;
   typedef ublas::vector< T >                                               complex_array_type ;
   typedef lapack::detail::workspace2< complex_array_type,real_array_type > type ;

   Workspace(size_t n)
   : work_( 2*n-1 )
   , rwork_( 3*n-2 )
   {}

   type operator() () {
      return type( work_, rwork_ );
   }

   complex_array_type work_ ;
   real_array_type    rwork_ ;
};


template <typename T>
int do_value_type() {
   const int n = 8 ;

   std::cout << " optimal workspace\n";
   if (do_memory_type<T,lapack::optimal_workspace>( n, lapack::optimal_workspace() ) ) return 255 ;

   std::cout << " minimal workspace\n";
   if (do_memory_type<T,lapack::minimal_workspace>( n, lapack::minimal_workspace() ) ) return 255 ;

   std::cout << " workspace array\n";
   Workspace<T> work( n );
   do_memory_type<T,typename Workspace<T>::type >( n, work() );
   return 0;
} // do_value_type()


int main() {
   // Run tests for different value_types
   std::cout << "complex<float>\n" ;
   if (do_value_type< std::complex<float> >()) return 255;

   std::cout << "complex<double>\n" ;
   if (do_value_type< std::complex<double> >()) return 255;

   std::cout << "Regression test succeeded\n" ;
   return 0;
}

