// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_MFUNC_EMPLACE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_MFUNC_EMPLACE_HPP_INCLUDED

#include <boost/tti/has_member_function.hpp>

namespace boost { namespace detail { namespace metafunction {

    // The has_member_function_emplace metafunction takes in four argument
    // types:
    //
    // T -- the type to be checked for the presence of a nested 'emplace'
    //      member function declaration.
    // R -- the return type of the 'emplace' member function declaration.
    //      (Default: void)
    // A -- an MPL forward sequence encapsulating the argument types of the
    //      'emplace' member function declaration.  (Default: mpl::vector0<>)
    // Q -- a Boost.FunctionTypes tag specifying cv-qualification.
    //
    // The metafunction can also be invoked by passing in a single argument
    // with the following form:
    //
    //    R T::*(P) K
    //
    // where P is a comma-separated list of the argument types and K is a
    // whitespace-separated list of cv-qualification keywords.
    BOOST_TTI_HAS_MEMBER_FUNCTION(emplace)

    // The has_member_function_emplace_front metafunction takes in four
    // argument types:
    //
    // T -- the type to be checked for the presence of a nested 'emplace_front'
    //      member function declaration.
    // R -- the return type of the 'emplace_front' member function declaration.
    //      (Default: void)
    // A -- an MPL forward sequence encapsulating the argument types of the
    //      'emplace_front' member function declaration.
    //      (Default: mpl::vector0<>)
    // Q -- a Boost.FunctionTypes tag specifying cv-qualification.
    //
    // The metafunction can also be invoked by passing in a single argument
    // with the following form:
    //
    //    R T::*(P) K
    //
    // where P is a comma-separated list of the argument types and K is a
    // whitespace-separated list of cv-qualification keywords.
    BOOST_TTI_HAS_MEMBER_FUNCTION(emplace_front)

    // The has_member_function_emplace_back metafunction takes in four argument
    // types:
    //
    // T -- the type to be checked for the presence of a nested 'emplace_back'
    //      member function declaration.
    // R -- the return type of the 'emplace_back' member function declaration.
    //      (Default: void)
    // A -- an MPL forward sequence encapsulating the argument types of the
    //      'emplace_back' member function declaration.
    //      (Default: mpl::vector0<>)
    // Q -- a Boost.FunctionTypes tag specifying cv-qualification.
    //
    // The metafunction can also be invoked by passing in a single argument
    // with the following form:
    //
    //    R T::*(P) K
    //
    // where P is a comma-separated list of the argument types and K is a
    // whitespace-separated list of cv-qualification keywords.
    BOOST_TTI_HAS_MEMBER_FUNCTION(emplace_back)
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_MFUNC_EMPLACE_HPP_INCLUDED

