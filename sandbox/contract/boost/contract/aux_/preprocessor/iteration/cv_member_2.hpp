
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#undef BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER
#undef BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
#undef BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE

#if BOOST_PP_FRAME_ITERATION(2) == 0 // Free func.
#   define BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER 0
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST /* empty */
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE /* empty */
#elif BOOST_PP_FRAME_ITERATION(2) == 1 // Member func.
#   define BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST /* empty */
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE /* empty */
#elif BOOST_PP_FRAME_ITERATION(2) == 2 // Const member func.
#   define BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST const
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE /* empty */
#elif BOOST_PP_FRAME_ITERATION(2) == 3 // Volatile member func.
#   define BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST /* empty */
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE volatile
#elif BOOST_PP_FRAME_ITERATION(2) == 4 // Const volatile member func.
#   define BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST const
#   define BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE volatile
#else
#   error "INTERNAL ERROR: invalid iteration index (in frame 2)"
#endif

