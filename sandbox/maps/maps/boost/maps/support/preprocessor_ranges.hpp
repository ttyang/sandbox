//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--

#ifndef BOOST_PP_IS_ITERATING

# if !defined( BOOST_MAPS_SUPPORT_PREPROCESSOR_RANGES_HPP )
#  define BOOST_MAPS_SUPPORT_PREPROCESSOR_RANGES_HPP

#  include <boost/mpl/vector.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/repetition.hpp>
#  include <boost/preprocessor/iteration/iterate.hpp>

namespace boost { namespace maps { 

    // ranges0 definition
    struct ranges0
        : mpl::vector0<>
    {};

}} // namespace boost, namespace maps

// generate remaining definitions
#  define BOOST_PP_ITERATION_LIMITS (1, BOOST_MPL_LIMIT_VECTOR_SIZE)
#  define BOOST_PP_FILENAME_1 <boost/maps/support/preprocessor_ranges.hpp>
#  include BOOST_PP_ITERATE()

# endif // BOOST_MAPS_SUPPORT_PREPROCESSOR_RANGES_HPP

#else // BOOST_PP_IS_ITERATING

namespace boost { namespace maps {

    // rangesN definition
    template< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), class R) >
    struct BOOST_PP_CAT(ranges,BOOST_PP_ITERATION())
        : mpl::BOOST_PP_CAT(vector,BOOST_PP_ITERATION())< 
            BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), R) 
                > 
    {};

}} // namespace boost, namespace maps

#endif // BOOST_PP_IS_ITERATING
