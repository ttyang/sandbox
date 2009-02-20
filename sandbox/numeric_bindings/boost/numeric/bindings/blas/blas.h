//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_BLAS_H
#define BOOST_NUMERIC_BINDINGS_BLAS_BLAS_H

#include <boost/numeric/bindings/traits/type.h>
#include <boost/numeric/bindings/blas/blas_names.h>

extern "C" {

//
// BLAS level1 routines
//

// Value-type variants of asum
float BLAS_SASUM( integer_t const* n, float const* x, integer_t const* incx );
double BLAS_DASUM( integer_t const* n, double const* x,
        integer_t const* incx );

// Value-type variants of axpy
void BLAS_SAXPY( integer_t const* n, float const* a, float const* x,
        integer_t const* incx, float* y, integer_t const* incy );
void BLAS_DAXPY( integer_t const* n, double const* a, double const* x,
        integer_t const* incx, double* y, integer_t const* incy );
void BLAS_CAXPY( integer_t const* n, fcomplex_t const* a, fcomplex_t const* x,
        integer_t const* incx, fcomplex_t* y, integer_t const* incy );
void BLAS_ZAXPY( integer_t const* n, dcomplex_t const* a, dcomplex_t const* x,
        integer_t const* incx, dcomplex_t* y, integer_t const* incy );

// Value-type variants of copy
void BLAS_SCOPY( integer_t const* n, float const* x, integer_t const* incx,
        float const* y, integer_t const* incy );
void BLAS_DCOPY( integer_t const* n, double const* x, integer_t const* incx,
        double const* y, integer_t const* incy );
void BLAS_CCOPY( integer_t const* n, fcomplex_t const* x,
        integer_t const* incx, fcomplex_t const* y, integer_t const* incy );
void BLAS_ZCOPY( integer_t const* n, dcomplex_t const* x,
        integer_t const* incx, dcomplex_t const* y, integer_t const* incy );

// Value-type variants of dot
float BLAS_SDOT( integer_t const* n, float const* x, integer_t const* incx,
        float const* y, integer_t const* incy );
double BLAS_DDOT( integer_t const* n, double const* x, integer_t const* incx,
        double const* y, integer_t const* incy );

// Value-type variants of dotc
fcomplex_t BLAS_CDOTC( integer_t const* n, fcomplex_t const* x,
        integer_t const* incx, fcomplex_t const* y, integer_t const* incy );
dcomplex_t BLAS_ZDOTC( integer_t const* n, dcomplex_t const* x,
        integer_t const* incx, dcomplex_t const* y, integer_t const* incy );

// Value-type variants of dotu
fcomplex_t BLAS_CDOTU( integer_t const* n, fcomplex_t const* x,
        integer_t const* incx, fcomplex_t const* y, integer_t const* incy );
dcomplex_t BLAS_ZDOTU( integer_t const* n, dcomplex_t const* x,
        integer_t const* incx, dcomplex_t const* y, integer_t const* incy );

// Value-type variants of drot
void BLAS_ZDROT( integer_t const* n, dcomplex_t const* cx,
        integer_t const* incx, dcomplex_t const* cy, integer_t const* incy,
        double const* c, double const* s );

// Value-type variants of nrm2
float BLAS_SNRM2( integer_t const* n, float const* x, integer_t const* incx );
double BLAS_DNRM2( integer_t const* n, double const* x,
        integer_t const* incx );

// Value-type variants of rot
void BLAS_SROT( integer_t const* n, float const* x, integer_t const* incx,
        float* y, integer_t const* incy, float const* c, float const* s );
void BLAS_DROT( integer_t const* n, double const* x, integer_t const* incx,
        double* y, integer_t const* incy, double const* c, double const* s );

// Value-type variants of rotg
void BLAS_SROTG( float* a, float* b, float* c, float* s );
void BLAS_DROTG( double* a, double* b, double* c, double* s );
void BLAS_CROTG( fcomplex_t* a, fcomplex_t* b, float* c, fcomplex_t* s );
void BLAS_ZROTG( dcomplex_t* a, dcomplex_t* b, double* c, dcomplex_t* s );

// Value-type variants of rotm
void BLAS_SROTM( integer_t const* n, float* x, integer_t const* incx,
        float* y, integer_t const* incy, float* param );
void BLAS_DROTM( integer_t const* n, double* x, integer_t const* incx,
        double* y, integer_t const* incy, double* param );

// Value-type variants of rotmg
void BLAS_SROTMG( float* d1, float* d2, float* x1, float const* y1,
        float* sparam );
void BLAS_DROTMG( double* d1, double* d2, double* x1, double const* y1,
        double* dparam );

// Value-type variants of scal
void BLAS_SSCAL( integer_t const* n, float const* a, float const* x,
        integer_t const* incx );
void BLAS_DSCAL( integer_t const* n, double const* a, double const* x,
        integer_t const* incx );
void BLAS_CSCAL( integer_t const* n, fcomplex_t const* a, fcomplex_t const* x,
        integer_t const* incx );
void BLAS_ZSCAL( integer_t const* n, dcomplex_t const* a, dcomplex_t const* x,
        integer_t const* incx );

// Value-type variants of sdot
double BLAS_DSDOT( integer_t const* n, float const* sx, integer_t const* incx,
        float const* sy, integer_t const* incy );

// Value-type variants of srot
void BLAS_CSROT( integer_t const* n, fcomplex_t const* cx,
        integer_t const* incx, fcomplex_t const* cy, integer_t const* incy,
        float const* c, float const* s );

// Value-type variants of swap
void BLAS_SSWAP( integer_t const* n, float* x, integer_t const* incx,
        float* y, integer_t const* incy );
void BLAS_DSWAP( integer_t const* n, double* x, integer_t const* incx,
        double* y, integer_t const* incy );
void BLAS_CSWAP( integer_t const* n, fcomplex_t* x, integer_t const* incx,
        fcomplex_t* y, integer_t const* incy );
void BLAS_ZSWAP( integer_t const* n, dcomplex_t* x, integer_t const* incx,
        dcomplex_t* y, integer_t const* incy );

//
// BLAS level2 routines
//

// Value-type variants of gbmv
void BLAS_SGBMV( char const* trans, integer_t const* m, integer_t const* n,
        integer_t const* kl, integer_t const* ku, float const* alpha,
        float const* a, integer_t const* lda, float const* x,
        integer_t const* incx, float const* beta, float* y,
        integer_t const* incy );
void BLAS_DGBMV( char const* trans, integer_t const* m, integer_t const* n,
        integer_t const* kl, integer_t const* ku, double const* alpha,
        double const* a, integer_t const* lda, double const* x,
        integer_t const* incx, double const* beta, double* y,
        integer_t const* incy );
void BLAS_CGBMV( char const* trans, integer_t const* m, integer_t const* n,
        integer_t const* kl, integer_t const* ku, fcomplex_t const* alpha,
        fcomplex_t const* a, integer_t const* lda, fcomplex_t const* x,
        integer_t const* incx, fcomplex_t const* beta, fcomplex_t* y,
        integer_t const* incy );
void BLAS_ZGBMV( char const* trans, integer_t const* m, integer_t const* n,
        integer_t const* kl, integer_t const* ku, dcomplex_t const* alpha,
        dcomplex_t const* a, integer_t const* lda, dcomplex_t const* x,
        integer_t const* incx, dcomplex_t const* beta, dcomplex_t* y,
        integer_t const* incy );

// Value-type variants of gemv
void BLAS_SGEMV( char const* trans, integer_t const* m, integer_t const* n,
        float const* alpha, float const* a, integer_t const* lda,
        float const* x, integer_t const* incx, float const* beta, float* y,
        integer_t const* incy );
void BLAS_DGEMV( char const* trans, integer_t const* m, integer_t const* n,
        double const* alpha, double const* a, integer_t const* lda,
        double const* x, integer_t const* incx, double const* beta, double* y,
        integer_t const* incy );
void BLAS_CGEMV( char const* trans, integer_t const* m, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t const* x, integer_t const* incx, fcomplex_t const* beta,
        fcomplex_t* y, integer_t const* incy );
void BLAS_ZGEMV( char const* trans, integer_t const* m, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t const* x, integer_t const* incx, dcomplex_t const* beta,
        dcomplex_t* y, integer_t const* incy );

// Value-type variants of ger
void BLAS_SGER( integer_t const* m, integer_t const* n, float const* alpha,
        float const* x, integer_t const* incx, float const* y,
        integer_t const* incy, float* a, integer_t const* lda );
void BLAS_DGER( integer_t const* m, integer_t const* n, double const* alpha,
        double const* x, integer_t const* incx, double const* y,
        integer_t const* incy, double* a, integer_t const* lda );

// Value-type variants of gerc
void BLAS_CGERC( integer_t const* m, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* x, integer_t const* incx,
        fcomplex_t const* y, integer_t const* incy, fcomplex_t* a,
        integer_t const* lda );
void BLAS_ZGERC( integer_t const* m, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* x, integer_t const* incx,
        dcomplex_t const* y, integer_t const* incy, dcomplex_t* a,
        integer_t const* lda );

// Value-type variants of geru
void BLAS_CGERU( integer_t const* m, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* x, integer_t const* incx,
        fcomplex_t const* y, integer_t const* incy, fcomplex_t* a,
        integer_t const* lda );
void BLAS_ZGERU( integer_t const* m, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* x, integer_t const* incx,
        dcomplex_t const* y, integer_t const* incy, dcomplex_t* a,
        integer_t const* lda );

// Value-type variants of hbmv
void BLAS_CHBMV( char const* uplo, integer_t const* n, integer_t const* k,
        fcomplex_t const* alpha, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t const* x, integer_t const* incx, fcomplex_t const* beta,
        fcomplex_t* y, integer_t const* incy );
void BLAS_ZHBMV( char const* uplo, integer_t const* n, integer_t const* k,
        dcomplex_t const* alpha, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t const* x, integer_t const* incx, dcomplex_t const* beta,
        dcomplex_t* y, integer_t const* incy );

// Value-type variants of hemv
void BLAS_CHEMV( char const* uplo, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t const* x, integer_t const* incx, fcomplex_t const* beta,
        fcomplex_t* y, integer_t const* incy );
void BLAS_ZHEMV( char const* uplo, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t const* x, integer_t const* incx, dcomplex_t const* beta,
        dcomplex_t* y, integer_t const* incy );

// Value-type variants of her
void BLAS_CHER( char const* uplo, integer_t const* n, float const* alpha,
        fcomplex_t const* x, integer_t const* incx, fcomplex_t* a,
        integer_t const* lda );
void BLAS_ZHER( char const* uplo, integer_t const* n, double const* alpha,
        dcomplex_t const* x, integer_t const* incx, dcomplex_t* a,
        integer_t const* lda );

// Value-type variants of her2
void BLAS_CHER2( char const* uplo, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* x, integer_t const* incx,
        fcomplex_t const* y, integer_t const* incy, fcomplex_t* a,
        integer_t const* lda );
void BLAS_ZHER2( char const* uplo, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* x, integer_t const* incx,
        dcomplex_t const* y, integer_t const* incy, dcomplex_t* a,
        integer_t const* lda );

// Value-type variants of hpmv
void BLAS_CHPMV( char const* uplo, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* ap, fcomplex_t const* x,
        integer_t const* incx, fcomplex_t const* beta, fcomplex_t* y,
        integer_t const* incy );
void BLAS_ZHPMV( char const* uplo, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* ap, dcomplex_t const* x,
        integer_t const* incx, dcomplex_t const* beta, dcomplex_t* y,
        integer_t const* incy );

// Value-type variants of hpr
void BLAS_CHPR( char const* uplo, integer_t const* n, float const* alpha,
        fcomplex_t const* x, integer_t const* incx, fcomplex_t* ap );
void BLAS_ZHPR( char const* uplo, integer_t const* n, double const* alpha,
        dcomplex_t const* x, integer_t const* incx, dcomplex_t* ap );

// Value-type variants of hpr2
void BLAS_CHPR2( char const* uplo, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* x, integer_t const* incx,
        fcomplex_t const* y, integer_t const* incy, fcomplex_t* ap );
void BLAS_ZHPR2( char const* uplo, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* x, integer_t const* incx,
        dcomplex_t const* y, integer_t const* incy, dcomplex_t* ap );

// Value-type variants of sbmv
void BLAS_SSBMV( char const* uplo, integer_t const* n, integer_t const* k,
        float const* alpha, float const* a, integer_t const* lda,
        float const* x, integer_t const* incx, float const* beta, float* y,
        integer_t const* incy );
void BLAS_DSBMV( char const* uplo, integer_t const* n, integer_t const* k,
        double const* alpha, double const* a, integer_t const* lda,
        double const* x, integer_t const* incx, double const* beta, double* y,
        integer_t const* incy );

// Value-type variants of spmv
void BLAS_SSPMV( char const* uplo, integer_t const* n, float const* alpha,
        float const* ap, float const* x, integer_t const* incx,
        float const* beta, float* y, integer_t const* incy );
void BLAS_DSPMV( char const* uplo, integer_t const* n, double const* alpha,
        double const* ap, double const* x, integer_t const* incx,
        double const* beta, double* y, integer_t const* incy );

// Value-type variants of spr
void BLAS_SSPR( char const* uplo, integer_t const* n, float const* alpha,
        float const* x, integer_t const* incx, float* ap );
void BLAS_DSPR( char const* uplo, integer_t const* n, double const* alpha,
        double const* x, integer_t const* incx, double* ap );

// Value-type variants of spr2
void BLAS_SSPR2( char const* uplo, integer_t const* n, float const* alpha,
        float const* x, integer_t const* incx, float const* y,
        integer_t const* incy, float* ap );
void BLAS_DSPR2( char const* uplo, integer_t const* n, double const* alpha,
        double const* x, integer_t const* incx, double const* y,
        integer_t const* incy, double* ap );

// Value-type variants of symv
void BLAS_SSYMV( char const* uplo, integer_t const* n, float const* alpha,
        float const* a, integer_t const* lda, float const* x,
        integer_t const* incx, float const* beta, float* y,
        integer_t const* incy );
void BLAS_DSYMV( char const* uplo, integer_t const* n, double const* alpha,
        double const* a, integer_t const* lda, double const* x,
        integer_t const* incx, double const* beta, double* y,
        integer_t const* incy );

// Value-type variants of syr
void BLAS_SSYR( char const* uplo, integer_t const* n, float const* alpha,
        float const* x, integer_t const* incx, float* a,
        integer_t const* lda );
void BLAS_DSYR( char const* uplo, integer_t const* n, double const* alpha,
        double const* x, integer_t const* incx, double* a,
        integer_t const* lda );

// Value-type variants of syr2
void BLAS_SSYR2( char const* uplo, integer_t const* n, float const* alpha,
        float const* x, integer_t const* incx, float const* y,
        integer_t const* incy, float* a, integer_t const* lda );
void BLAS_DSYR2( char const* uplo, integer_t const* n, double const* alpha,
        double const* x, integer_t const* incx, double const* y,
        integer_t const* incy, double* a, integer_t const* lda );

// Value-type variants of tbmv
void BLAS_STBMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, float const* a,
        integer_t const* lda, float* x, integer_t const* incx );
void BLAS_DTBMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, double const* a,
        integer_t const* lda, double* x, integer_t const* incx );
void BLAS_CTBMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t* x, integer_t const* incx );
void BLAS_ZTBMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t* x, integer_t const* incx );

// Value-type variants of tbsv
void BLAS_STBSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, float const* a,
        integer_t const* lda, float* x, integer_t const* incx );
void BLAS_DTBSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, double const* a,
        integer_t const* lda, double* x, integer_t const* incx );
void BLAS_CTBSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t* x, integer_t const* incx );
void BLAS_ZTBSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, integer_t const* k, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t* x, integer_t const* incx );

// Value-type variants of tpmv
void BLAS_STPMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, float const* ap, float* x, integer_t const* incx );
void BLAS_DTPMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, double const* ap, double* x,
        integer_t const* incx );
void BLAS_CTPMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, fcomplex_t const* ap, fcomplex_t* x,
        integer_t const* incx );
void BLAS_ZTPMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, dcomplex_t const* ap, dcomplex_t* x,
        integer_t const* incx );

// Value-type variants of tpsv
void BLAS_STPSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, float const* ap, float* x, integer_t const* incx );
void BLAS_DTPSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, double const* ap, double* x,
        integer_t const* incx );
void BLAS_CTPSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, fcomplex_t const* ap, fcomplex_t* x,
        integer_t const* incx );
void BLAS_ZTPSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, dcomplex_t const* ap, dcomplex_t* x,
        integer_t const* incx );

// Value-type variants of trmv
void BLAS_STRMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, float const* a, integer_t const* lda, float* x,
        integer_t const* incx );
void BLAS_DTRMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, double const* a, integer_t const* lda, double* x,
        integer_t const* incx );
void BLAS_CTRMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t* x, integer_t const* incx );
void BLAS_ZTRMV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t* x, integer_t const* incx );

// Value-type variants of trsv
void BLAS_STRSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, float const* a, integer_t const* lda, float* x,
        integer_t const* incx );
void BLAS_DTRSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, double const* a, integer_t const* lda, double* x,
        integer_t const* incx );
void BLAS_CTRSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t* x, integer_t const* incx );
void BLAS_ZTRSV( char const* uplo, char const* trans, char const* diag,
        integer_t const* n, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t* x, integer_t const* incx );

//
// BLAS level3 routines
//

// Value-type variants of gemm
void BLAS_SGEMM( char const* transa, char const* transb, integer_t const* m,
        integer_t const* n, integer_t const* k, float const* alpha,
        float const* a, integer_t const* lda, float const* b,
        integer_t const* ldb, float const* beta, float* c,
        integer_t const* ldc );
void BLAS_DGEMM( char const* transa, char const* transb, integer_t const* m,
        integer_t const* n, integer_t const* k, double const* alpha,
        double const* a, integer_t const* lda, double const* b,
        integer_t const* ldb, double const* beta, double* c,
        integer_t const* ldc );
void BLAS_CGEMM( char const* transa, char const* transb, integer_t const* m,
        integer_t const* n, integer_t const* k, fcomplex_t const* alpha,
        fcomplex_t const* a, integer_t const* lda, fcomplex_t const* b,
        integer_t const* ldb, fcomplex_t const* beta, fcomplex_t* c,
        integer_t const* ldc );
void BLAS_ZGEMM( char const* transa, char const* transb, integer_t const* m,
        integer_t const* n, integer_t const* k, dcomplex_t const* alpha,
        dcomplex_t const* a, integer_t const* lda, dcomplex_t const* b,
        integer_t const* ldb, dcomplex_t const* beta, dcomplex_t* c,
        integer_t const* ldc );

// Value-type variants of hemm
void BLAS_CHEMM( char const* side, char const* uplo, integer_t const* m,
        integer_t const* n, fcomplex_t const* alpha, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t const* b, integer_t const* ldb,
        fcomplex_t const* beta, fcomplex_t* c, integer_t const* ldc );
void BLAS_ZHEMM( char const* side, char const* uplo, integer_t const* m,
        integer_t const* n, dcomplex_t const* alpha, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t const* b, integer_t const* ldb,
        dcomplex_t const* beta, dcomplex_t* c, integer_t const* ldc );

// Value-type variants of her2k
void BLAS_CHER2K( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, fcomplex_t const* alpha, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t const* b, integer_t const* ldb,
        float const* beta, fcomplex_t* c, integer_t const* ldc );
void BLAS_ZHER2K( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, dcomplex_t const* alpha, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t const* b, integer_t const* ldb,
        double const* beta, dcomplex_t* c, integer_t const* ldc );

// Value-type variants of herk
void BLAS_CHERK( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, float const* alpha, fcomplex_t const* a,
        integer_t const* lda, float const* beta, fcomplex_t* c,
        integer_t const* ldc );
void BLAS_ZHERK( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, double const* alpha, dcomplex_t const* a,
        integer_t const* lda, double const* beta, dcomplex_t* c,
        integer_t const* ldc );

// Value-type variants of symm
void BLAS_SSYMM( char const* side, char const* uplo, integer_t const* m,
        integer_t const* n, float const* alpha, float const* a,
        integer_t const* lda, float const* b, integer_t const* ldb,
        float const* beta, float* c, integer_t const* ldc );
void BLAS_DSYMM( char const* side, char const* uplo, integer_t const* m,
        integer_t const* n, double const* alpha, double const* a,
        integer_t const* lda, double const* b, integer_t const* ldb,
        double const* beta, double* c, integer_t const* ldc );
void BLAS_CSYMM( char const* side, char const* uplo, integer_t const* m,
        integer_t const* n, fcomplex_t const* alpha, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t const* b, integer_t const* ldb,
        fcomplex_t const* beta, fcomplex_t* c, integer_t const* ldc );
void BLAS_ZSYMM( char const* side, char const* uplo, integer_t const* m,
        integer_t const* n, dcomplex_t const* alpha, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t const* b, integer_t const* ldb,
        dcomplex_t const* beta, dcomplex_t* c, integer_t const* ldc );

// Value-type variants of syr2k
void BLAS_SSYR2K( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, float const* alpha, float const* a,
        integer_t const* lda, float const* b, integer_t const* ldb,
        float const* beta, float* c, integer_t const* ldc );
void BLAS_DSYR2K( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, double const* alpha, double const* a,
        integer_t const* lda, double const* b, integer_t const* ldb,
        double const* beta, double* c, integer_t const* ldc );
void BLAS_CSYR2K( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, fcomplex_t const* alpha, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t const* b, integer_t const* ldb,
        fcomplex_t const* beta, fcomplex_t* c, integer_t const* ldc );
void BLAS_ZSYR2K( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, dcomplex_t const* alpha, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t const* b, integer_t const* ldb,
        dcomplex_t const* beta, dcomplex_t* c, integer_t const* ldc );

// Value-type variants of syrk
void BLAS_SSYRK( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, float const* alpha, float const* a,
        integer_t const* lda, float const* beta, float* c,
        integer_t const* ldc );
void BLAS_DSYRK( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, double const* alpha, double const* a,
        integer_t const* lda, double const* beta, double* c,
        integer_t const* ldc );
void BLAS_CSYRK( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, fcomplex_t const* alpha, fcomplex_t const* a,
        integer_t const* lda, fcomplex_t const* beta, fcomplex_t* c,
        integer_t const* ldc );
void BLAS_ZSYRK( char const* uplo, char const* trans, integer_t const* n,
        integer_t const* k, dcomplex_t const* alpha, dcomplex_t const* a,
        integer_t const* lda, dcomplex_t const* beta, dcomplex_t* c,
        integer_t const* ldc );

// Value-type variants of trmm
void BLAS_STRMM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        float const* alpha, float const* a, integer_t const* lda, float* b,
        integer_t const* ldb );
void BLAS_DTRMM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        double const* alpha, double const* a, integer_t const* lda, double* b,
        integer_t const* ldb );
void BLAS_CTRMM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t* b, integer_t const* ldb );
void BLAS_ZTRMM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t* b, integer_t const* ldb );

// Value-type variants of trsm
void BLAS_STRSM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        float const* alpha, float const* a, integer_t const* lda, float* b,
        integer_t const* ldb );
void BLAS_DTRSM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        double const* alpha, double const* a, integer_t const* lda, double* b,
        integer_t const* ldb );
void BLAS_CTRSM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        fcomplex_t const* alpha, fcomplex_t const* a, integer_t const* lda,
        fcomplex_t* b, integer_t const* ldb );
void BLAS_ZTRSM( char const* side, char const* uplo, char const* transa,
        char const* diag, integer_t const* m, integer_t const* n,
        dcomplex_t const* alpha, dcomplex_t const* a, integer_t const* lda,
        dcomplex_t* b, integer_t const* ldb );

}

#endif

