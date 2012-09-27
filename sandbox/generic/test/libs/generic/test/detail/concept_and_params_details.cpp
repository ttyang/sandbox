/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept_and_params_details.hpp>

#define BG_EMPTY BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS()

#define BG_NOT_SEQ BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( foo )

#define BG_WRONG_SIZE_SEQ                                                      \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( (1)(2)(3) )

#define BG_SEQ_WITH_EXTRA_DATA                                                 \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( (1)(2) foo )

#define BG_SEQ_WITH_EMPTY_CONCEPT                                              \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( ()(params) )

#define BG_SEQ_WITH_EMPTY_PARAMS                                               \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( (concept)() )

#define BG_VALID                                                               \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( (concept_)( a(), b(), c() ) )


#if BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID( BG_EMPTY )
#error Empty arg detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID( BG_NOT_SEQ )
#error Nonsequence detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID( BG_WRONG_SIZE_SEQ )
#error Wrong size sequence detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID(                     \
                                                         BG_SEQ_WITH_EXTRA_DATA\
                                                       )
#error Sequence with extra data detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID(                     \
                                                      BG_SEQ_WITH_EMPTY_CONCEPT\
                                                    )
#error Sequence with empty concept detected as valid concept and params.
#endif

#if BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID(                     \
                                                       BG_SEQ_WITH_EMPTY_PARAMS\
                                                     )
#error Sequence with empty params detected as valid concept and params.
#endif

#if !BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID( BG_VALID )
#error Valid concept and params detected as invalid concept and params.
#endif

struct a {};
struct b {};
struct c {};

struct concept_and_params
{
  static void concept_( a, b, c );

  static void caller()
  {
    BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_CONCEPT( BG_VALID )
    ( BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_PARAMS( BG_VALID ) );
  }
};
