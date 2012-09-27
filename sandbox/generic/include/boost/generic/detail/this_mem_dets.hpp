/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_THIS_MEM_DETS_HPP
#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_HPP

#include <boost/generic/detail/eat.hpp>
#include <boost/generic/detail/eat_part_after_paren.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_this.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Takes an argument of the form:
//   this(nonempty_type) something_or_nothing
// Yields result in the form:
// (is_valid_bit)(is_partial_bit)((nonempty_type))((something_or_nothing))
#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS( ... )                              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_THIS( __VA_ARGS__ )             \
            , BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL                          \
            , BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_NOT_THIS                 \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( dets )                    \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( dets )                  \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL_INVALID( dets )          \
BOOST_PP_BITAND                                                                \
( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( dets )                        \
, BOOST_PP_COMPL( BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( dets ) )        \
)

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_TYPE( dets )                        \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME( dets )                        \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 3, dets ) )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_QUALIFIED_NAME( dets )              \
  BOOST_GENERIC_DETAIL_THIS_MEM_DETS_TYPE( dets )                              \
::BOOST_GENERIC_DETAIL_THIS_MEM_DETS_NAME( dets )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_NOT_THIS( ... )                \
(0)(0)((invalid_this_member_declaration))((invalid_this_member_declaration))

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL( ... )                         \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_THIS_EATEN                             \
( BOOST_GENERIC_DETAIL_EAT_THIS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_THIS_EATEN( ... )              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_PAREN                    \
            , BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_NO_PAREN                 \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_NO_PAREN( ... )                \
(0)(1)((invalid_this_member_declaration))((invalid_this_member_declaration))

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_PAREN( ... )                   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN_AND_EXTRA_DATA( __VA_ARGS__ ) )          \
, BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_EMPTY_TYPE                           \
, BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_VALID                                \
)( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ )                    \
 , BOOST_GENERIC_DETAIL_EAT_WRAPPED( __VA_ARGS__ )                             \
 )

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_EMPTY_TYPE( ... )              \
(0)(1)((invalid_this_member_declaration))((invalid_this_member_declaration))

#define BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IMPL_VALID( type_in_paren, ... )    \
(1)(1)(type_in_paren)((__VA_ARGS__))

#endif // BOOST_GENERIC_DETAIL_THIS_MEM_DETS_HPP
