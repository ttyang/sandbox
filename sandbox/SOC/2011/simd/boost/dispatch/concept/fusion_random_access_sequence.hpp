/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_CONCEPT_FUSION_RANDOM_ACCESS_SEQUENCE_HPP_INCLUDED
#define BOOST_DISPATCH_CONCEPT_FUSION_RANDOM_ACCESS_SEQUENCE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Boost.Fusion Random Access Sequence concept
// Documentation:
// http://www.boost.org/doc/libs/release/libs/fusion/doc/html/fusion/sequence/concepts/random_access_sequence.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/include/at.hpp>
#include <boost/dispatch/error/concepts.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <boost/dispatch/concepts/fusion_bidirectionnal_sequence.hpp>

namespace boost { namespace dispatch
{
  template<class S>
  struct  FusionRandomAccessSequence
        : FusionBidirectionnalSequence<S>
  {
    typedef typename boost::fusion::result_of::at_c<S,0>::type at_type;
    BOOST_CONCEPT_USAGE(FusionRandomAccessSequence)
    {
      at_type a = boost::fusion::at_c<0>(s);
      ignore_unused(a);
    }

    private:
    S s;
  };
} }

#endif
