/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// ToDo: Test to make sure that the sequence size and extra data are correct

#include <boost/generic/detail/seq_details.hpp>

#define BG_EMPTY BOOST_GENERIC_DETAIL_SEQ_DETS()

#define BG_NONEMPTY                                                            \
BOOST_GENERIC_DETAIL_SEQ_DETS( something thats not a sequence )

#define BG_SEQ_WITH_EXTRA_DATA                                                 \
BOOST_GENERIC_DETAIL_SEQ_DETS( (0)(1)(2) extra data )

#define BG_SEQ BOOST_GENERIC_DETAIL_SEQ_DETS( (0)(1)(2) )

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( BG_EMPTY )
#error Empty argument detected as valid sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_EMPTY )
#error Empty argument detected as having extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITHOUT_EXTRA_DATA( BG_EMPTY )
#error Empty argument detected as sequence without extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITH_EXTRA_DATA( BG_EMPTY )
#error Empty argument detected as sequence with extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( BG_EMPTY )
#error Empty argument detected as starting as a sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_EMPTY )
#error Empty argument detected as having data after the sequence.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_IS_EMPTY( BG_EMPTY )
#error Empty argument detected as not empty.
#endif



#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( BG_NONEMPTY )
#error Nonempty argument detected as valid sequence.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_NONEMPTY )
#error Nonempty argument detected as not having extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITHOUT_EXTRA_DATA( BG_NONEMPTY )
#error Nonempty argument detected as sequence without extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITH_EXTRA_DATA( BG_NONEMPTY )
#error Nonempty argument detected as sequence with extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( BG_NONEMPTY )
#error Nonempty argument detected as starting as a sequence.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_NONEMPTY )
#error Nonempty argument detected as not having data after the sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_EMPTY( BG_NONEMPTY )
#error Nonempty argument detected as empty.
#endif



#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( BG_SEQ_WITH_EXTRA_DATA )
#error Sequence with extra data detected as valid sequence.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_SEQ_WITH_EXTRA_DATA )
#error Sequence with extra data detected as not having extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITHOUT_EXTRA_DATA(                   \
                                                         BG_SEQ_WITH_EXTRA_DATA\
                                                       )
#error Sequence with extra data detected as sequence without extra data.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITH_EXTRA_DATA(                     \
                                                         BG_SEQ_WITH_EXTRA_DATA\
                                                       )
#error Sequence with extra data detected as not sequence with extra data.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( BG_SEQ_WITH_EXTRA_DATA )
#error Sequence with extra data detected as not starting as a sequence.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_SEQ_WITH_EXTRA_DATA )
#error Sequence with extra data detected as not having data after the sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_EMPTY( BG_SEQ_WITH_EXTRA_DATA )
#error Sequence with extra data detected as empty.
#endif




#if !BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( BG_SEQ )
#error Sequence detected as not a valid sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_SEQ )
#error Sequence detected as having extra data.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITHOUT_EXTRA_DATA( BG_SEQ )
#error Sequence detected as not sequence without extra data.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITH_EXTRA_DATA( BG_SEQ )
#error Sequencet detected as sequence with extra data.
#endif

#if !BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( BG_SEQ )
#error Sequence detected as not starting as a sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( BG_SEQ )
#error Sequence detected as having data after the sequence.
#endif

#if BOOST_GENERIC_DETAIL_SEQ_DETS_IS_EMPTY( BG_SEQ )
#error Sequence detected as empty.
#endif
