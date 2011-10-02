//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ASSERT_HPP_INCLUDED
#define NT2_SDK_ERROR_ASSERT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime assertions
 */
#include <nt2/sdk/error/debug.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If NT2_ASSERTS_AS_EXCEPTIONS is defined, all runtime assertion will throw
 * an instance of assert_exception instead of triggering a runtime assertion.
 *
 * \see NT2_DISABLE_ERROR
 * \see NT2_DISABLE_ASSERTS
 */
//==============================================================================
#define NT2_ASSERTS_AS_EXCEPTIONS

//==============================================================================
/*!
 * \ingroup error_config
 * If \c NT2_DISABLE_ASSERTS is defined, all runtime assertion are disabled.
 * Note than defining \c BOOST_DISABLE_ASSERTS triggers this definition.
 *
 * \see NT2_DISABLE_ERROR
 * \see NT2_ASSERTS_AS_EXCEPTIONS
 */
//==============================================================================
#define NT2_DISABLE_ASSERTS
#endif

//==============================================================================
// Make assertion into exceptions
//==============================================================================
#include <iosfwd>
#include <nt2/sdk/error/error.hpp>

#if  !defined(NT2_NO_EXCEPTIONS) || defined(DOXYGEN_ONLY)


namespace nt2 { namespace details { NT2_ERROR_INFO(assert_info, char const*); } }

namespace nt2
{
  //============================================================================
  /*!
   * \ingroup error
   * assert_exception is the exception thrown when a runtime assertion fails and
   * NT2_ASSERTS_AS_EXCEPTIONS is defined.
   */
  //============================================================================
  struct assert_exception : virtual nt2::exception
  {
    virtual ~assert_exception() throw() {}
    virtual void display(std::ostream& os) const throw();
  };
}

#ifndef BOOST_ENABLE_ASSERT_HANDLER
#define BOOST_ENABLE_ASSERT_HANDLER
#endif

#endif

//==============================================================================
// Debug mode has SIGTRAP to the assertion
//==============================================================================
#if defined(NT2_DEBUG) && !defined(NT2_ASSERTS_AS_EXCEPTIONS)
#include <nt2/sdk/error/trap.hpp>
#ifndef BOOST_ENABLE_ASSERT_HANDLER
#define BOOST_ENABLE_ASSERT_HANDLER
#endif
#endif

//==============================================================================
// Include assert and forward the macro
//==============================================================================
#include <boost/assert.hpp>

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
#if defined(NT2_DEBUG)
#include <cstdio>
#endif

namespace boost
{
  void inline
  assertion_failed(char const* expr,char const* fn,char const* f,int l)
  {
    #if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(NT2_NO_EXCEPTIONS)
    ::boost::exception_detail
    ::throw_exception_(   ::nt2::assert_exception()
                      <<  ::nt2::details::assert_info(expr)
                        , fn,f,l
                      );
    #elif defined(NT2_DEBUG)
    fprintf(stderr,"%s:%d: %s: Assertion %s failed.\n",f,l,fn,expr);
    ::nt2::trap();
    #else
    boost::dispatch::ignore_unused(expr);
    boost::dispatch::ignore_unused(fn);
    boost::dispatch::ignore_unused(f);
    boost::dispatch::ignore_unused(l);
    #endif
  }
}

#undef BOOST_ENABLE_ASSERT_HANDLER
#endif

#endif
