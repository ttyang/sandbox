//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_UNALIGNED_LOAD_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_UNALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/toolbox/operator/include/functions/unaligned_load.hpp>

namespace nt2
{
  namespace tag
  {
    using boost::simd::tag::unaligned_load_;
  }

  using boost::simd::unaligned_load;
}

#endif
