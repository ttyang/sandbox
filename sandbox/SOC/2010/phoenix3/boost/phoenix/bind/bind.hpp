
#if !defined(PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef PHOENIX_BIND_BIND_HPP
#define PHOENIX_BIND_BIND_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/utility/result_of.hpp>

#include <boost/phoenix/bind/preprocessed/bind.hpp>

#endif
#else

#if !PHOENIX_IS_ITERATING

#ifndef PHOENIX_BIND_BIND_HPP
#define PHOENIX_BIND_BIND_HPP

#include <boost/phoenix/limits.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/utility/result_of.hpp>

#if defined(__WAVE__) && defined(PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_" PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    // Bind
    ////////////////////////////////////////////////////////////////////////////
    
    template <typename F>
    typename expression::function<F>::type
    bind(F f)
    {
        return function<F>(f)();
    }

#define PHOENIX_ITERATION_PARAMS                                                \
    (3, (1, PHOENIX_ARG_LIMIT,                                                  \
    <boost/phoenix/bind/bind.hpp>))
#include PHOENIX_ITERATE()

}}

#if defined(__WAVE__) && defined(PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
    
    template <typename F, PHOENIX_typename_A>
    typename expression::function<F, PHOENIX_A>::type const
    bind(F f, PHOENIX_A_const_ref_a)
    {
        return function<F>(f)(PHOENIX_a);
    }

#endif

#endif // PHOENIX_DONT_USE_PREPROCESSED_FILES
