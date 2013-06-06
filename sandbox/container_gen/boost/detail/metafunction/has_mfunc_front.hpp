// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_MFUNC_FRONT_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_MFUNC_FRONT_HPP_INCLUDED

#include <boost/tti/has_member_function.hpp>

namespace boost { namespace detail { namespace metafunction {

    // The has_member_function_front metafunction takes in four argument types:
    //
    // T -- the type to be checked for the presence of a nested 'front'
    //      member function declaration.
    // R -- the return type of the 'front' member function declaration.
    //      (Default: void)
    // A -- an MPL forward sequence encapsulating the argument types of the
    //      'front' member function declaration.  (Default: mpl::vector0<>)
    // Q -- a Boost.FunctionTypes tag specifying cv-qualification.
    //
    // The metafunction can also be invoked by passing in a single argument
    // with the following form:
    //
    //    R T::*(P) K
    //
    // where P is a comma-separated list of the argument types and K is a
    // whitespace-separated list of cv-qualification keywords.
    BOOST_TTI_HAS_MEMBER_FUNCTION(front)

    // The has_member_function_push_front metafunction takes in four argument
    // types:
    //
    // T -- the type to be checked for the presence of a nested 'push_front'
    //      member function declaration.
    // R -- the return type of the 'push_front' member function declaration.
    //      (Default: void)
    // A -- an MPL forward sequence encapsulating the argument types of the
    //      'push_front' member function declaration.
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
    BOOST_TTI_HAS_MEMBER_FUNCTION(push_front)

    // The has_member_function_pop_front metafunction takes in four argument
    // types:
    //
    // T -- the type to be checked for the presence of a nested 'pop_front'
    //      member function declaration.
    // R -- the return type of the 'pop_front' member function declaration.
    //      (Default: void)
    // A -- an MPL forward sequence encapsulating the argument types of the
    //      'pop_front' member function declaration.  (Default: mpl::vector0<>)
    // Q -- a Boost.FunctionTypes tag specifying cv-qualification.
    //
    // The metafunction can also be invoked by passing in a single argument
    // with the following form:
    //
    //    R T::*(P) K
    //
    // where P is a comma-separated list of the argument types and K is a
    // whitespace-separated list of cv-qualification keywords.
    BOOST_TTI_HAS_MEMBER_FUNCTION(pop_front)
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_MFUNC_FRONT_HPP_INCLUDED

