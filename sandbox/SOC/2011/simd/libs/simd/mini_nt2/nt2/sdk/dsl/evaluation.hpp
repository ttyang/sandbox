/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_EVALUATION_HPP_INCLUDED
#define NT2_SDK_DSL_EVALUATION_HPP_INCLUDED

#include <nt2/sdk/functor/functor.hpp>

namespace nt2
{
  namespace tag { struct evaluate_ {}; }

  NT2_FUNCTION_IMPLEMENTATION_SELF(tag::evaluate_, evaluate, 2)
}

#endif
