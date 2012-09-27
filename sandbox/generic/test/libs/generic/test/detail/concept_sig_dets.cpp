/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept_sig_dets.hpp>

#define BG_EMPTY BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS()

#define BG_NOT_SEQ BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS( foo )

#define BG_WRONG_SIZE_SEQ                                                      \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS( (1)(2)(3) )

#define BG_SEQ_WITH_EXTRA_DATA                                                 \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS( (1)(2) foo )

#define BG_SEQ_WITH_EMPTY_CONCEPT                                              \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS( ()( (class) T) )

#define BG_SEQ_WITH_EMPTY_PARAMS                                               \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS( (concept)() )

#define BG_VALID                                                               \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS                                          \
( (concept_)( (class) A, (class) B, (class) c ) )


#if BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( BG_EMPTY )
#error Empty arg detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( BG_NOT_SEQ )
#error Nonsequence detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( BG_WRONG_SIZE_SEQ )
#error Wrong size sequence detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID(                     \
                                                         BG_SEQ_WITH_EXTRA_DATA\
                                                       )
#error Sequence with extra data detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID(                     \
                                                      BG_SEQ_WITH_EMPTY_CONCEPT\
                                                    )
#error Sequence with empty concept detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID(                     \
                                                       BG_SEQ_WITH_EMPTY_PARAMS\
                                                     )
#error Sequence with empty params detected as valid concept and params.
#endif

#if !BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( BG_VALID )
#error Valid concept and params detected as invalid concept and params.
#endif

template< class A, class B, class C >
class concept_;

// This should be a redeclaration of the above template if everything is correct
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
          ( BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_PARAM_DETS( BG_VALID ) )
        >
class BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_CONCEPT( BG_VALID );
