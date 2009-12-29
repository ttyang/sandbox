
// solving A * X = B
// A hermitian
// hetrf() & hetrs()

#include <cstddef>
#include <iostream>
#include <complex>
#include <boost/numeric/bindings/lapack/computational/hetrf.hpp>
#include <boost/numeric/bindings/lapack/computational/hetrs.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#include <boost/numeric/bindings/traits/ublas_hermitian.hpp>
#include <boost/numeric/bindings/traits/std_vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include "utils.h"

namespace ublas = boost::numeric::ublas;
namespace lapack = boost::numeric::bindings::lapack;
namespace traits = boost::numeric::bindings::traits;

using std::size_t; 
using std::cin;
using std::cout;
using std::endl; 

typedef double real_t; 
typedef std::complex<real_t> cmplx_t; 

typedef ublas::matrix<cmplx_t, ublas::column_major> cm_t;
typedef ublas::hermitian_adaptor<cm_t, ublas::lower> cherml_t; 
typedef ublas::hermitian_adaptor<cm_t, ublas::upper> chermu_t; 

int main() {

  cm_t cal (3, 3), cau (3, 3);   // matrices (storage)
  cherml_t hcal (cal);   // hermitian adaptor 
  chermu_t hcau (cau);   // hermitian adaptor 
  cm_t cx (3, 1);
  cm_t cbl (3, 1), cbu (3, 1);  // RHS

  hcal (0, 0) = cmplx_t (3, 0);
  hcal (1, 0) = cmplx_t (4, -2);
  hcal (1, 1) = cmplx_t (5, 0);
  hcal (2, 0) = cmplx_t (-7, -5);
  hcal (2, 1) = cmplx_t (0, 3);
  hcal (2, 2) = cmplx_t (2, 0);

  hcau (0, 0) = cmplx_t (3, 0);
  hcau (0, 1) = cmplx_t (4, 2);
  hcau (0, 2) = cmplx_t (-7, 5);
  hcau (1, 1) = cmplx_t (5, 0);
  hcau (1, 2) = cmplx_t (0, -3);
  hcau (2, 2) = cmplx_t (2, 0);

  print_m (cal, "cal"); 
  cout << endl; 
  print_m (cau, "cau"); 
  cout << endl; 

  for (int i = 0; i < cx.size1(); ++i) 
    cx (i, 0) = cmplx_t (1, -1); 
  print_m (cx, "cx"); 
  cout << endl; 
  cbl = prod (hcal, cx);
  cbu = prod (hcau, cx);
  print_m (cbl, "cbl"); 
  cout << endl; 
  print_m (cbu, "cbu"); 
  cout << endl; 

  cm_t cal2 (hcal), cau2 (hcau);  // for part 2
  cm_t cbl2 (cbl), cbu2 (cbu); 

  std::vector<integer_t> ipiv (3); 

  int ierr = lapack::hetrf (hcal, ipiv); 
  if (ierr == 0) {
    lapack::hetrs (traits::matrix_uplo_tag(hcal), hcal, ipiv, cbl);
    print_m (cbl, "cxl"); 
  }
  else 
    cout << "matrix is not regular: ierr = " 
         << ierr << endl;
  cout << endl; 

  std::vector<cmplx_t> cwork (3*64); 
  // 3*64 -- optimal size

  ierr = lapack::hetrf (hcau, ipiv, lapack::workspace(cwork)); 
  if (ierr == 0) {
    lapack::hetrs (traits::matrix_uplo_tag(hcau), hcau, ipiv, cbu); 
    print_v (ipiv, "ipiv"); 
    cout << endl; 
    print_m (cbu, "cxu"); 
  }
  else 
    cout << "matrix is not regular: ierr = " 
         << ierr << endl;
  cout << endl; 

  // part 2

  swap (row (cal2, 0), row (cal2, 2));
  swap (column (cal2, 0), column (cal2, 2));

  swap (row (cau2, 1), row (cau2, 2));
  swap (column (cau2, 1), column (cau2, 2));

  print_m (cal2, "cal2"); 
  cout << endl; 
  print_m (cau2, "cau2"); 
  cout << endl; 

  cbl2 = prod (cal2, cx);
  cbu2 = prod (cau2, cx);
  print_m (cbl2, "cbl2"); 
  cout << endl; 
  print_m (cbu2, "cbu2"); 
  cout << endl; 

  cherml_t hcal2 (cal2);
  ierr = lapack::hetrf (hcal2, ipiv); 
  if (ierr == 0) {
    lapack::hetrs ('L', cal2, ipiv, cbl2); 
    print_m (cbl2, "cxl2"); 
  }
  else 
    cout << "matrix is not regular: ierr = " 
         << ierr << endl;
  cout << endl; 

  chermu_t hcau2 (cau2);
  ierr = lapack::hetrf (hcau2, ipiv, lapack::workspace(cwork)); 
  if (ierr == 0) {
    lapack::hetrs ('U', cau2, ipiv, cbu2); 
    print_v (ipiv, "ipiv"); 
    cout << endl; 
    print_m (cbu2, "cxu"); 
  }
  else 
    cout << "matrix is not regular: ierr = " 
         << ierr << endl;
  cout << endl; 

}

