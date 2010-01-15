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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_DETAIL_BLAS_NAMES_H
#define BOOST_NUMERIC_BINDINGS_BLAS_DETAIL_BLAS_NAMES_H

#include <boost/numeric/bindings/detail/config/fortran.hpp>

//
// BLAS level1 routines
//

// Value-type variants of asum
#define BLAS_SASUM FORTRAN_ID( sasum )
#define BLAS_DASUM FORTRAN_ID( dasum )
#define BLAS_SCASUM FORTRAN_ID( scasum )
#define BLAS_DZASUM FORTRAN_ID( dzasum )

// Value-type variants of axpy
#define BLAS_SAXPY FORTRAN_ID( saxpy )
#define BLAS_DAXPY FORTRAN_ID( daxpy )
#define BLAS_CAXPY FORTRAN_ID( caxpy )
#define BLAS_ZAXPY FORTRAN_ID( zaxpy )

// Value-type variants of copy
#define BLAS_SCOPY FORTRAN_ID( scopy )
#define BLAS_DCOPY FORTRAN_ID( dcopy )
#define BLAS_CCOPY FORTRAN_ID( ccopy )
#define BLAS_ZCOPY FORTRAN_ID( zcopy )

// Value-type variants of dot
#define BLAS_SDOT FORTRAN_ID( sdot )
#define BLAS_DDOT FORTRAN_ID( ddot )

// Value-type variants of dotc
#define BLAS_CDOTC FORTRAN_ID( cdotc )
#define BLAS_ZDOTC FORTRAN_ID( zdotc )

// Value-type variants of dotu
#define BLAS_CDOTU FORTRAN_ID( cdotu )
#define BLAS_ZDOTU FORTRAN_ID( zdotu )

// Value-type variants of nrm2
#define BLAS_SNRM2 FORTRAN_ID( snrm2 )
#define BLAS_DNRM2 FORTRAN_ID( dnrm2 )
#define BLAS_SCNRM2 FORTRAN_ID( scnrm2 )
#define BLAS_DZNRM2 FORTRAN_ID( dznrm2 )

// Value-type variants of rot
#define BLAS_SROT FORTRAN_ID( srot )
#define BLAS_DROT FORTRAN_ID( drot )

// Value-type variants of rotg
#define BLAS_SROTG FORTRAN_ID( srotg )
#define BLAS_DROTG FORTRAN_ID( drotg )

// Value-type variants of rotm
#define BLAS_SROTM FORTRAN_ID( srotm )
#define BLAS_DROTM FORTRAN_ID( drotm )

// Value-type variants of rotmg
#define BLAS_SROTMG FORTRAN_ID( srotmg )
#define BLAS_DROTMG FORTRAN_ID( drotmg )

// Value-type variants of scal
#define BLAS_SSCAL FORTRAN_ID( sscal )
#define BLAS_DSCAL FORTRAN_ID( dscal )
#define BLAS_CSCAL FORTRAN_ID( cscal )
#define BLAS_ZSCAL FORTRAN_ID( zscal )

// Value-type variants of sdot
#define BLAS_DSDOT FORTRAN_ID( dsdot )

// Value-type variants of swap
#define BLAS_SSWAP FORTRAN_ID( sswap )
#define BLAS_DSWAP FORTRAN_ID( dswap )
#define BLAS_CSWAP FORTRAN_ID( cswap )
#define BLAS_ZSWAP FORTRAN_ID( zswap )

//
// BLAS level2 routines
//

// Value-type variants of gbmv
#define BLAS_SGBMV FORTRAN_ID( sgbmv )
#define BLAS_DGBMV FORTRAN_ID( dgbmv )
#define BLAS_CGBMV FORTRAN_ID( cgbmv )
#define BLAS_ZGBMV FORTRAN_ID( zgbmv )

// Value-type variants of gemv
#define BLAS_SGEMV FORTRAN_ID( sgemv )
#define BLAS_DGEMV FORTRAN_ID( dgemv )
#define BLAS_CGEMV FORTRAN_ID( cgemv )
#define BLAS_ZGEMV FORTRAN_ID( zgemv )

// Value-type variants of ger
#define BLAS_SGER FORTRAN_ID( sger )
#define BLAS_DGER FORTRAN_ID( dger )

// Value-type variants of gerc
#define BLAS_CGERC FORTRAN_ID( cgerc )
#define BLAS_ZGERC FORTRAN_ID( zgerc )

// Value-type variants of geru
#define BLAS_CGERU FORTRAN_ID( cgeru )
#define BLAS_ZGERU FORTRAN_ID( zgeru )

// Value-type variants of hbmv
#define BLAS_CHBMV FORTRAN_ID( chbmv )
#define BLAS_ZHBMV FORTRAN_ID( zhbmv )

// Value-type variants of hemv
#define BLAS_CHEMV FORTRAN_ID( chemv )
#define BLAS_ZHEMV FORTRAN_ID( zhemv )

// Value-type variants of her
#define BLAS_CHER FORTRAN_ID( cher )
#define BLAS_ZHER FORTRAN_ID( zher )

// Value-type variants of her2
#define BLAS_CHER2 FORTRAN_ID( cher2 )
#define BLAS_ZHER2 FORTRAN_ID( zher2 )

// Value-type variants of hpmv
#define BLAS_CHPMV FORTRAN_ID( chpmv )
#define BLAS_ZHPMV FORTRAN_ID( zhpmv )

// Value-type variants of hpr
#define BLAS_CHPR FORTRAN_ID( chpr )
#define BLAS_ZHPR FORTRAN_ID( zhpr )

// Value-type variants of hpr2
#define BLAS_CHPR2 FORTRAN_ID( chpr2 )
#define BLAS_ZHPR2 FORTRAN_ID( zhpr2 )

// Value-type variants of sbmv
#define BLAS_SSBMV FORTRAN_ID( ssbmv )
#define BLAS_DSBMV FORTRAN_ID( dsbmv )

// Value-type variants of spmv
#define BLAS_SSPMV FORTRAN_ID( sspmv )
#define BLAS_DSPMV FORTRAN_ID( dspmv )

// Value-type variants of spr
#define BLAS_SSPR FORTRAN_ID( sspr )
#define BLAS_DSPR FORTRAN_ID( dspr )

// Value-type variants of spr2
#define BLAS_SSPR2 FORTRAN_ID( sspr2 )
#define BLAS_DSPR2 FORTRAN_ID( dspr2 )

// Value-type variants of symv
#define BLAS_SSYMV FORTRAN_ID( ssymv )
#define BLAS_DSYMV FORTRAN_ID( dsymv )

// Value-type variants of syr
#define BLAS_SSYR FORTRAN_ID( ssyr )
#define BLAS_DSYR FORTRAN_ID( dsyr )

// Value-type variants of syr2
#define BLAS_SSYR2 FORTRAN_ID( ssyr2 )
#define BLAS_DSYR2 FORTRAN_ID( dsyr2 )

// Value-type variants of tbmv
#define BLAS_STBMV FORTRAN_ID( stbmv )
#define BLAS_DTBMV FORTRAN_ID( dtbmv )
#define BLAS_CTBMV FORTRAN_ID( ctbmv )
#define BLAS_ZTBMV FORTRAN_ID( ztbmv )

// Value-type variants of tbsv
#define BLAS_STBSV FORTRAN_ID( stbsv )
#define BLAS_DTBSV FORTRAN_ID( dtbsv )
#define BLAS_CTBSV FORTRAN_ID( ctbsv )
#define BLAS_ZTBSV FORTRAN_ID( ztbsv )

// Value-type variants of tpmv
#define BLAS_STPMV FORTRAN_ID( stpmv )
#define BLAS_DTPMV FORTRAN_ID( dtpmv )
#define BLAS_CTPMV FORTRAN_ID( ctpmv )
#define BLAS_ZTPMV FORTRAN_ID( ztpmv )

// Value-type variants of tpsv
#define BLAS_STPSV FORTRAN_ID( stpsv )
#define BLAS_DTPSV FORTRAN_ID( dtpsv )
#define BLAS_CTPSV FORTRAN_ID( ctpsv )
#define BLAS_ZTPSV FORTRAN_ID( ztpsv )

// Value-type variants of trmv
#define BLAS_STRMV FORTRAN_ID( strmv )
#define BLAS_DTRMV FORTRAN_ID( dtrmv )
#define BLAS_CTRMV FORTRAN_ID( ctrmv )
#define BLAS_ZTRMV FORTRAN_ID( ztrmv )

// Value-type variants of trsv
#define BLAS_STRSV FORTRAN_ID( strsv )
#define BLAS_DTRSV FORTRAN_ID( dtrsv )
#define BLAS_CTRSV FORTRAN_ID( ctrsv )
#define BLAS_ZTRSV FORTRAN_ID( ztrsv )

//
// BLAS level3 routines
//

// Value-type variants of gemm
#define BLAS_SGEMM FORTRAN_ID( sgemm )
#define BLAS_DGEMM FORTRAN_ID( dgemm )
#define BLAS_CGEMM FORTRAN_ID( cgemm )
#define BLAS_ZGEMM FORTRAN_ID( zgemm )

// Value-type variants of hemm
#define BLAS_CHEMM FORTRAN_ID( chemm )
#define BLAS_ZHEMM FORTRAN_ID( zhemm )

// Value-type variants of her2k
#define BLAS_CHER2K FORTRAN_ID( cher2k )
#define BLAS_ZHER2K FORTRAN_ID( zher2k )

// Value-type variants of herk
#define BLAS_CHERK FORTRAN_ID( cherk )
#define BLAS_ZHERK FORTRAN_ID( zherk )

// Value-type variants of symm
#define BLAS_SSYMM FORTRAN_ID( ssymm )
#define BLAS_DSYMM FORTRAN_ID( dsymm )
#define BLAS_CSYMM FORTRAN_ID( csymm )
#define BLAS_ZSYMM FORTRAN_ID( zsymm )

// Value-type variants of syr2k
#define BLAS_SSYR2K FORTRAN_ID( ssyr2k )
#define BLAS_DSYR2K FORTRAN_ID( dsyr2k )
#define BLAS_CSYR2K FORTRAN_ID( csyr2k )
#define BLAS_ZSYR2K FORTRAN_ID( zsyr2k )

// Value-type variants of syrk
#define BLAS_SSYRK FORTRAN_ID( ssyrk )
#define BLAS_DSYRK FORTRAN_ID( dsyrk )
#define BLAS_CSYRK FORTRAN_ID( csyrk )
#define BLAS_ZSYRK FORTRAN_ID( zsyrk )

// Value-type variants of trmm
#define BLAS_STRMM FORTRAN_ID( strmm )
#define BLAS_DTRMM FORTRAN_ID( dtrmm )
#define BLAS_CTRMM FORTRAN_ID( ctrmm )
#define BLAS_ZTRMM FORTRAN_ID( ztrmm )

// Value-type variants of trsm
#define BLAS_STRSM FORTRAN_ID( strsm )
#define BLAS_DTRSM FORTRAN_ID( dtrsm )
#define BLAS_CTRSM FORTRAN_ID( ctrsm )
#define BLAS_ZTRSM FORTRAN_ID( ztrsm )



#endif

