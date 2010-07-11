//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_MSVC9_MAKE_BFT_FIX_HPP
#define BOOST_BFT_MSVC9_MAKE_BFT_FIX_HPP


namespace boost { namespace detail { namespace msvc_fixes {

/** Used to help generate psudo variadic template paramerer apperance.
 *  This make the typename T##N = mpl::void_ pattern.
 */
#define BOOST_MAKE_BFT_PARAM(z, n, data ) \
    typename T ## n

/** Makes the T0 through TN parameter list for the 
 *  Generates pattern.
 *  typename T0, ... typename TN
 */
#define BOOST_MAKE_BFT_TEMPLATE_PARAMETERS(N) \
    BOOST_PP_ENUM(  N,\
                    BOOST_MAKE_BFT_PARAM, \
                    BOOST_BFT_NOTHING )


/** Used for generating a single funciton parameter for the make_bitfield_tuple
 *  function template.
 */
#define BOOST_MAKE_BFT_FUNCTION_PARAM(z, n, data ) \
    T ## n parameter ## n

/** used for generating the parameters for a the make_bitfield_tuple
 *  funciton.
 *  Generates pattern
 *  T0 parameter0 , ... TN parametern 
 */
#define BOOST_MAKE_BFT_FUNCTION_PARAMETERS(N) \
    BOOST_PP_ENUM(  N,\
                    BOOST_MAKE_BFT_FUNCTION_PARAM, \
                    BOOST_BFT_NOTHING )

#define BOOST_MAKE_BFT_ASSIGN_FUNCTION_CALL(z,n,data)\
    detail::assign_parameter_to_bft<n>(bft, parameter##n);

#define BOOST_MAKE_BFT_GENERATE_ASSIGNMENT_CALLS( TO ) \
    BOOST_PP_REPEAT_FROM_TO( \
        0,\
        TO, \
        BOOST_MAKE_BFT_ASSIGN_FUNCTION_CALL,\
        BOOST_BFT_NOTHING )


#define BOOST_MAKE_BFT_FUNCTION(z, N, data)                                     \
    template <typename BitfieldTuple, BOOST_MAKE_BFT_TEMPLATE_PARAMETERS(N)>  \
    BitfieldTuple make_bitfield_tuple(BOOST_MAKE_BFT_FUNCTION_PARAMETERS(N)){ \
        BitfieldTuple bft;                                                    \
        BOOST_MAKE_BFT_GENERATE_ASSIGNMENT_CALLS(N);                          \
        return bft;                                                           \
    }

#define BOOST_MAKE_BFT_OVERLOADS() \
    BOOST_PP_REPEAT_FROM_TO( \
        1,\
        BOOST_BFT_PARAM_COUNT, \
        BOOST_MAKE_BFT_FUNCTION,\
        BOOST_BFT_NOTHING )

}}

BOOST_MAKE_BFT_OVERLOADS();

} // end boost::detail::msvc_fixes
#endif
