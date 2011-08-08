//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--

#ifndef BOOST_PP_IS_ITERATING

# if !defined( BOOST_MAPS_SUPPORT_PREPROCESSOR_BOUNDS_HPP )
#  define BOOST_MAPS_SUPPORT_PREPROCESSOR_BOUNDS_HPP

#  include <boost/mpl/vector_c.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/repetition.hpp>
#  include <boost/preprocessor/iteration/iterate.hpp>

namespace boost { namespace maps {

    // bounds0 definition
    struct bounds0
        : mpl::vector0_c< std::size_t >
    {};

}} // namespace boost, namespace maps

// generate remaining definitions
#  define BOOST_PP_ITERATION_LIMITS (1, BOOST_MPL_LIMIT_VECTOR_SIZE)
#  define BOOST_PP_FILENAME_1 <boost/maps/support/preprocessor_bounds.hpp>
#  include BOOST_PP_ITERATE()

# endif // BOOST_MAPS_SUPPORT_PREPROCESSOR_BOUNDS_HPP

#else // BOOST_PP_IS_ITERATING

namespace boost { namespace maps {

    // boundsN definition
    template< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), std::size_t S) >
    struct BOOST_PP_CAT(bounds,BOOST_PP_ITERATION())
        : public mpl::BOOST_PP_CAT(BOOST_PP_CAT(vector,BOOST_PP_ITERATION()),_c)< 
            std::size_t, BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), S) 
                > 
    {};

}} // namespace boost, namespace maps

#endif // BOOST_PP_IS_ITERATING