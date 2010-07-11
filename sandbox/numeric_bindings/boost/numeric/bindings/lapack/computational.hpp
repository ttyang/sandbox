//
// Copyright (c) 2002--2010
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HPP

#include <boost/numeric/bindings/lapack/computational/hbgst.hpp>
#include <boost/numeric/bindings/lapack/computational/hegst.hpp>
#include <boost/numeric/bindings/lapack/computational/pbstf.hpp>
#include <boost/numeric/bindings/lapack/computational/sbgst.hpp>
#include <boost/numeric/bindings/lapack/computational/sygst.hpp>
#include <boost/numeric/bindings/lapack/computational/ggqrf.hpp>
#include <boost/numeric/bindings/lapack/computational/ggrqf.hpp>
#include <boost/numeric/bindings/lapack/computational/gelqf.hpp>
#include <boost/numeric/bindings/lapack/computational/geqlf.hpp>
#include <boost/numeric/bindings/lapack/computational/geqp3.hpp>
#include <boost/numeric/bindings/lapack/computational/geqrf.hpp>
#include <boost/numeric/bindings/lapack/computational/gerqf.hpp>
#include <boost/numeric/bindings/lapack/computational/orglq.hpp>
#include <boost/numeric/bindings/lapack/computational/orgql.hpp>
#include <boost/numeric/bindings/lapack/computational/orgqr.hpp>
#include <boost/numeric/bindings/lapack/computational/orgrq.hpp>
#include <boost/numeric/bindings/lapack/computational/ormlq.hpp>
#include <boost/numeric/bindings/lapack/computational/ormql.hpp>
#include <boost/numeric/bindings/lapack/computational/ormqr.hpp>
#include <boost/numeric/bindings/lapack/computational/ormrq.hpp>
#include <boost/numeric/bindings/lapack/computational/ormrz.hpp>
#include <boost/numeric/bindings/lapack/computational/tzrzf.hpp>
#include <boost/numeric/bindings/lapack/computational/unglq.hpp>
#include <boost/numeric/bindings/lapack/computational/ungql.hpp>
#include <boost/numeric/bindings/lapack/computational/ungqr.hpp>
#include <boost/numeric/bindings/lapack/computational/ungrq.hpp>
#include <boost/numeric/bindings/lapack/computational/unmlq.hpp>
#include <boost/numeric/bindings/lapack/computational/unmql.hpp>
#include <boost/numeric/bindings/lapack/computational/unmqr.hpp>
#include <boost/numeric/bindings/lapack/computational/unmrq.hpp>
#include <boost/numeric/bindings/lapack/computational/unmrz.hpp>
#include <boost/numeric/bindings/lapack/computational/bdsdc.hpp>
#include <boost/numeric/bindings/lapack/computational/bdsqr.hpp>
#include <boost/numeric/bindings/lapack/computational/gbbrd.hpp>
#include <boost/numeric/bindings/lapack/computational/gebrd.hpp>
//#include <boost/numeric/bindings/lapack/computational/orgbr.hpp>
// #include <boost/numeric/bindings/lapack/computational/ormbr.hpp>
#include <boost/numeric/bindings/lapack/computational/ungbr.hpp>
// #include <boost/numeric/bindings/lapack/computational/unmbr.hpp>
#include <boost/numeric/bindings/lapack/computational/gebak.hpp>
#include <boost/numeric/bindings/lapack/computational/gebal.hpp>
#include <boost/numeric/bindings/lapack/computational/gehrd.hpp>
//#include <boost/numeric/bindings/lapack/computational/hsein.hpp>
#include <boost/numeric/bindings/lapack/computational/hseqr.hpp>
#include <boost/numeric/bindings/lapack/computational/orghr.hpp>
#include <boost/numeric/bindings/lapack/computational/ormhr.hpp>
#include <boost/numeric/bindings/lapack/computational/trevc.hpp>
//#include <boost/numeric/bindings/lapack/computational/trexc.hpp>
#include <boost/numeric/bindings/lapack/computational/trsen.hpp>
#include <boost/numeric/bindings/lapack/computational/trsna.hpp>
#include <boost/numeric/bindings/lapack/computational/trsyl.hpp>
#include <boost/numeric/bindings/lapack/computational/unghr.hpp>
#include <boost/numeric/bindings/lapack/computational/unmhr.hpp>
#include <boost/numeric/bindings/lapack/computational/gbcon.hpp>
#include <boost/numeric/bindings/lapack/computational/gbequ.hpp>
#include <boost/numeric/bindings/lapack/computational/gbrfs.hpp>
#include <boost/numeric/bindings/lapack/computational/gbtrf.hpp>
#include <boost/numeric/bindings/lapack/computational/gbtrs.hpp>
#include <boost/numeric/bindings/lapack/computational/gecon.hpp>
#include <boost/numeric/bindings/lapack/computational/geequ.hpp>
#include <boost/numeric/bindings/lapack/computational/gerfs.hpp>
#include <boost/numeric/bindings/lapack/computational/getrf.hpp>
#include <boost/numeric/bindings/lapack/computational/getri.hpp>
#include <boost/numeric/bindings/lapack/computational/getrs.hpp>
// #include <boost/numeric/bindings/lapack/computational/gtrfs.hpp>
// #include <boost/numeric/bindings/lapack/computational/gttrs.hpp>
#include <boost/numeric/bindings/lapack/computational/hecon.hpp>
#include <boost/numeric/bindings/lapack/computational/herfs.hpp>
#include <boost/numeric/bindings/lapack/computational/hetrf.hpp>
#include <boost/numeric/bindings/lapack/computational/hetri.hpp>
#include <boost/numeric/bindings/lapack/computational/hetrs.hpp>
#include <boost/numeric/bindings/lapack/computational/hpcon.hpp>
#include <boost/numeric/bindings/lapack/computational/hprfs.hpp>
#include <boost/numeric/bindings/lapack/computational/hptrf.hpp>
#include <boost/numeric/bindings/lapack/computational/hptri.hpp>
#include <boost/numeric/bindings/lapack/computational/hptrs.hpp>
// #include <boost/numeric/bindings/lapack/computational/pbcon.hpp>
#include <boost/numeric/bindings/lapack/computational/pbequ.hpp>
#include <boost/numeric/bindings/lapack/computational/pbrfs.hpp>
#include <boost/numeric/bindings/lapack/computational/pbtrf.hpp>
// #include <boost/numeric/bindings/lapack/computational/pbtrs.hpp>
// #include <boost/numeric/bindings/lapack/computational/pftrs.hpp>
#include <boost/numeric/bindings/lapack/computational/pocon.hpp>
#include <boost/numeric/bindings/lapack/computational/poequ.hpp>
#include <boost/numeric/bindings/lapack/computational/porfs.hpp>
#include <boost/numeric/bindings/lapack/computational/potrf.hpp>
#include <boost/numeric/bindings/lapack/computational/potri.hpp>
#include <boost/numeric/bindings/lapack/computational/potrs.hpp>
#include <boost/numeric/bindings/lapack/computational/ppcon.hpp>
#include <boost/numeric/bindings/lapack/computational/ppequ.hpp>
#include <boost/numeric/bindings/lapack/computational/pprfs.hpp>
#include <boost/numeric/bindings/lapack/computational/pptrf.hpp>
#include <boost/numeric/bindings/lapack/computational/pptri.hpp>
#include <boost/numeric/bindings/lapack/computational/pptrs.hpp>
#include <boost/numeric/bindings/lapack/computational/ptcon.hpp>
#include <boost/numeric/bindings/lapack/computational/ptrfs.hpp>
#include <boost/numeric/bindings/lapack/computational/pttrf.hpp>
#include <boost/numeric/bindings/lapack/computational/pttrs.hpp>
#include <boost/numeric/bindings/lapack/computational/spcon.hpp>
#include <boost/numeric/bindings/lapack/computational/sprfs.hpp>
#include <boost/numeric/bindings/lapack/computational/sptrf.hpp>
#include <boost/numeric/bindings/lapack/computational/sptri.hpp>
#include <boost/numeric/bindings/lapack/computational/sptrs.hpp>
#include <boost/numeric/bindings/lapack/computational/sycon.hpp>
#include <boost/numeric/bindings/lapack/computational/syrfs.hpp>
#include <boost/numeric/bindings/lapack/computational/sytrf.hpp>
#include <boost/numeric/bindings/lapack/computational/sytri.hpp>
#include <boost/numeric/bindings/lapack/computational/sytrs.hpp>
#include <boost/numeric/bindings/lapack/computational/tbcon.hpp>
// #include <boost/numeric/bindings/lapack/computational/tbrfs.hpp>
#include <boost/numeric/bindings/lapack/computational/tbtrs.hpp>
#include <boost/numeric/bindings/lapack/computational/tpcon.hpp>
// #include <boost/numeric/bindings/lapack/computational/tprfs.hpp>
#include <boost/numeric/bindings/lapack/computational/tptri.hpp>
// #include <boost/numeric/bindings/lapack/computational/tptrs.hpp>
#include <boost/numeric/bindings/lapack/computational/trcon.hpp>
#include <boost/numeric/bindings/lapack/computational/trrfs.hpp>
#include <boost/numeric/bindings/lapack/computational/trtri.hpp>
#include <boost/numeric/bindings/lapack/computational/trtrs.hpp>
#include <boost/numeric/bindings/lapack/computational/hbtrd.hpp>
#include <boost/numeric/bindings/lapack/computational/hetrd.hpp>
#include <boost/numeric/bindings/lapack/computational/hptrd.hpp>
#include <boost/numeric/bindings/lapack/computational/opgtr.hpp>
// #include <boost/numeric/bindings/lapack/computational/opmtr.hpp>
#include <boost/numeric/bindings/lapack/computational/orgtr.hpp>
#include <boost/numeric/bindings/lapack/computational/ormtr.hpp>
#include <boost/numeric/bindings/lapack/computational/pteqr.hpp>
#include <boost/numeric/bindings/lapack/computational/sbtrd.hpp>
#include <boost/numeric/bindings/lapack/computational/sptrd.hpp>
#include <boost/numeric/bindings/lapack/computational/stebz.hpp>
#include <boost/numeric/bindings/lapack/computational/stedc.hpp>
#include <boost/numeric/bindings/lapack/computational/stegr.hpp>
#include <boost/numeric/bindings/lapack/computational/stein.hpp>
//#include <boost/numeric/bindings/lapack/computational/stemr.hpp>
#include <boost/numeric/bindings/lapack/computational/steqr.hpp>
#include <boost/numeric/bindings/lapack/computational/sterf.hpp>
#include <boost/numeric/bindings/lapack/computational/sytrd.hpp>
// #include <boost/numeric/bindings/lapack/computational/ungtr.hpp>
#include <boost/numeric/bindings/lapack/computational/unmtr.hpp>
#include <boost/numeric/bindings/lapack/computational/upgtr.hpp>
// #include <boost/numeric/bindings/lapack/computational/upmtr.hpp>
#include <boost/numeric/bindings/lapack/computational/ggbak.hpp>
#include <boost/numeric/bindings/lapack/computational/ggbal.hpp>
#include <boost/numeric/bindings/lapack/computational/gghrd.hpp>
#include <boost/numeric/bindings/lapack/computational/hgeqz.hpp>
#include <boost/numeric/bindings/lapack/computational/tgevc.hpp>
//#include <boost/numeric/bindings/lapack/computational/tgexc.hpp>
//#include <boost/numeric/bindings/lapack/computational/tgsen.hpp>
#include <boost/numeric/bindings/lapack/computational/tgsna.hpp>
#include <boost/numeric/bindings/lapack/computational/tgsyl.hpp>
#include <boost/numeric/bindings/lapack/computational/ggsvp.hpp>
#include <boost/numeric/bindings/lapack/computational/tgsja.hpp>

#endif
