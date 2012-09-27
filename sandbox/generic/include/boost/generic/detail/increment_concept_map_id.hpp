/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if BOOST_GENERIC_CONCEPT_MAP_ID() < 8
# if BOOST_GENERIC_CONCEPT_MAP_ID() < 4
#  if BOOST_GENERIC_CONCEPT_MAP_ID() < 2
#   if BOOST_GENERIC_CONCEPT_MAP_ID() == 0
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 1
#   else
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 2
#   endif
#  else
#   if BOOST_GENERIC_CONCEPT_MAP_ID() == 2
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 3
#   else
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 4
#   endif
#  endif
# else
#  if BOOST_GENERIC_CONCEPT_MAP_ID() < 6
#   if BOOST_GENERIC_CONCEPT_MAP_ID() == 4
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 5
#   else
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 6
#   endif
#  else
#   if BOOST_GENERIC_CONCEPT_MAP_ID() == 6
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 7
#   else
#    undef BOOST_GENERIC_CONCEPT_MAP_ID
#    define BOOST_GENERIC_CONCEPT_MAP_ID() 8
#   endif
#  endif
# endif
#else
# error Max number of emulated concept maps reached.
#endif
