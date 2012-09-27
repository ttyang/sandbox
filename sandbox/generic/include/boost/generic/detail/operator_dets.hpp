/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_OPERATOR_DETS_HPP
#define BOOST_GENERIC_DETAIL_OPERATOR_DETS_HPP

#include <boost/generic/detail/is_operator.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Takes operator of the form:
//   operator nonempty_nonparenthesized_type
// And yields:
// (validity_bit)(partial_bit)(type)
#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS( ... )                   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL               \
            , BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_INVALID       \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IS_VALID( dets )         \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IS_PARTIAL( dets )       \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_TYPE( dets )             \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_INVALID( ... )      \
(0)(0)(invalid_operator)

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_PARTIAL( ... )      \
(0)(1)(invalid_operator)

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_VALID( ... )        \
(1)(1)((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL( ... )              \
BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_                            \
( BOOST_GENERIC_DETAIL_EAT_OPERATOR( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_( ... )              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ ) \
            , BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_PARTIAL        \
            , BOOST_GENERIC_DETAIL_CONVERSION_OPERATOR_DETS_IMPL_VALID          \
            )( __VA_ARGS__ )

// Takes operator of the form:
//   operator nonmember_operator_name
// And yields:
// (validity_bit)(partial_bit)(nonmember_operator_name)
#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS( ... )                    \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL                \
            , BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_INVALID        \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_VALID( dets )          \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_PARTIAL( dets )        \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_NAME( dets )              \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IS_NONBASIC( dets )       \
BOOST_GENERIC_DETAIL_IS_NONBASIC_OP                                            \
( BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_NAME( dets ) )

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_INVALID( ... )       \
(0)(0)(invalid_operator)

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_PARTIAL( ... )       \
(0)(1)(invalid_operator)

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_VALID( name )        \
(1)(1)(name)

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL( ... )               \
BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_                             \
( BOOST_GENERIC_DETAIL_EAT_OPERATOR( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_( ... )              \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR_NAME( __VA_ARGS__ )   \
            , BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_VALID          \
            , BOOST_GENERIC_DETAIL_NONMEMBER_OPERATOR_DETS_IMPL_PARTIAL        \
            )( __VA_ARGS__ )

// Takes operator of the form:
//   operator member_operator_name
// And yields:
// (validity_bit)(partial_bit)(member_operator_name)
#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS( ... )                       \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL                   \
            , BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_INVALID           \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_VALID( dets )             \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IS_PARTIAL( dets )           \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_NAME( dets )                 \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_INVALID( ... )          \
(0)(0)(invalid_operator)

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_PARTIAL( ... )          \
(0)(1)(invalid_operator)

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_VALID( name )           \
(1)(1)(name)

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL( ... )                  \
BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_                                \
( BOOST_GENERIC_DETAIL_EAT_OPERATOR( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_( ... )                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR_NAME( __VA_ARGS__ )      \
            , BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_VALID             \
            , BOOST_GENERIC_DETAIL_MEMBER_OPERATOR_DETS_IMPL_PARTIAL           \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_OPERATOR( op_name )                               \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_OPERATOR, op_name )

#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYplus                2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYminus               2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYmultiply            2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYdivide              2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYmodulus             2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYunary_plus          1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYnegate              1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYless                2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYgreater             2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYless_equal          2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYgreater_equal       2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYequal_to            2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYnot_equal_to        2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYlogical_and         2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYlogical_or          2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYlogical_not         1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYbit_and             2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYbit_or              2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYbit_xor             2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYcomplement          1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYleft_shift          2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYright_shift         2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYdereference         1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYaddress_of          1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYsubscript           2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYcall                0
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYassign              1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYplus_assign         2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYminus_assign        2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYmultiply_assign     2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYdivide_assign       2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYmodulus_assign      2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYbit_and_assign      2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYbit_or_assign       2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYbit_xor_assign      2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYleft_shift_assign   2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYright_shift_assign  2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYpreincrement        1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYpostincrement       2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYpredecrement        1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYpostdecrement       2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYcomma               2
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYnew                 0
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYnew_array           0
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYdelete              0
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYdelete_array        0
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYarrow               1
#define BOOST_GENERIC_DETAIL_OPERATOR_ARITYarrow_dereference   2

#define BOOST_GENERIC_DETAIL_OPERATORplus                +
#define BOOST_GENERIC_DETAIL_OPERATORminus               -
#define BOOST_GENERIC_DETAIL_OPERATORmultiply            *
#define BOOST_GENERIC_DETAIL_OPERATORdivide              /
#define BOOST_GENERIC_DETAIL_OPERATORmodulus             %
#define BOOST_GENERIC_DETAIL_OPERATORunary_plus          +
#define BOOST_GENERIC_DETAIL_OPERATORnegate              -
#define BOOST_GENERIC_DETAIL_OPERATORless                <
#define BOOST_GENERIC_DETAIL_OPERATORgreater             >
#define BOOST_GENERIC_DETAIL_OPERATORless_equal          <=
#define BOOST_GENERIC_DETAIL_OPERATORgreater_equal       >=
#define BOOST_GENERIC_DETAIL_OPERATORequal_to            ==
#define BOOST_GENERIC_DETAIL_OPERATORnot_equal_to        !=
#define BOOST_GENERIC_DETAIL_OPERATORlogical_and         &&
#define BOOST_GENERIC_DETAIL_OPERATORlogical_or          ||
#define BOOST_GENERIC_DETAIL_OPERATORlogical_not         !
#define BOOST_GENERIC_DETAIL_OPERATORbit_and             &
#define BOOST_GENERIC_DETAIL_OPERATORbit_or              |
#define BOOST_GENERIC_DETAIL_OPERATORbit_xor             ^
#define BOOST_GENERIC_DETAIL_OPERATORcomplement          ~
#define BOOST_GENERIC_DETAIL_OPERATORleft_shift          <<
#define BOOST_GENERIC_DETAIL_OPERATORright_shift         >>
#define BOOST_GENERIC_DETAIL_OPERATORdereference         *
#define BOOST_GENERIC_DETAIL_OPERATORaddress_of          &
#define BOOST_GENERIC_DETAIL_OPERATORsubscript           []
#define BOOST_GENERIC_DETAIL_OPERATORcall                ()
#define BOOST_GENERIC_DETAIL_OPERATORassign              =
#define BOOST_GENERIC_DETAIL_OPERATORplus_assign         +=
#define BOOST_GENERIC_DETAIL_OPERATORminus_assign        -=
#define BOOST_GENERIC_DETAIL_OPERATORmultiply_assign     *=
#define BOOST_GENERIC_DETAIL_OPERATORdivide_assign       /=
#define BOOST_GENERIC_DETAIL_OPERATORmodulus_assign      %=
#define BOOST_GENERIC_DETAIL_OPERATORbit_and_assign      &=
#define BOOST_GENERIC_DETAIL_OPERATORbit_or_assign       |=
#define BOOST_GENERIC_DETAIL_OPERATORbit_xor_assign      ^=
#define BOOST_GENERIC_DETAIL_OPERATORleft_shift_assign   <<=
#define BOOST_GENERIC_DETAIL_OPERATORright_shift_assign  >>=
#define BOOST_GENERIC_DETAIL_OPERATORpreincrement        ++
#define BOOST_GENERIC_DETAIL_OPERATORpostincrement       ++
#define BOOST_GENERIC_DETAIL_OPERATORpredecrement        --
#define BOOST_GENERIC_DETAIL_OPERATORpostdecrement       --
#define BOOST_GENERIC_DETAIL_OPERATORcomma               ,
#define BOOST_GENERIC_DETAIL_OPERATORnew                 new
#define BOOST_GENERIC_DETAIL_OPERATORnew_array           new[]
#define BOOST_GENERIC_DETAIL_OPERATORdelete              delete
#define BOOST_GENERIC_DETAIL_OPERATORdelete_array        delete[]
#define BOOST_GENERIC_DETAIL_OPERATORarrow               ->
#define BOOST_GENERIC_DETAIL_OPERATORarrow_dereference   ->*

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATOR( name, arg_dets )                 \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_INVOKE_OPERATOR, name )( arg_dets )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORplus( arg_dets )                   \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
+ BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORminus( arg_dets )                  \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
- BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORmultiply( arg_dets )               \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
* BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORdivide( arg_dets )                 \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
/ BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORmodulus( arg_dets )                \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
% BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORunary_plus( arg_dets )             \
+BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORnegate( arg_dets )                 \
-BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORless( arg_dets )                   \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
< BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORgreater( arg_dets )                \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
> BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORless_equal( arg_dets )             \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
<= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORgreater_equal( arg_dets )          \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
>= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORequal_to( arg_dets )               \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
== BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORnot_equal_to( arg_dets )           \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
!= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORlogical_and( arg_dets )            \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
&& BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORlogical_or( arg_dets )             \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
|| BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORlogical_not( arg_dets )            \
!BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORbit_and( arg_dets )                \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
& BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORbit_or( arg_dets )                 \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
| BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORbit_xor( arg_dets )                \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
^ BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORcomplement( arg_dets )             \
~BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORleft_shift( arg_dets )             \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
<< BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORright_shift( arg_dets )            \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
>> BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORdereference( arg_dets )            \
*BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORaddress_of( arg_dets )             \
&BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORsubscript( arg_dets )              \
BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                       \
[ BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 ) ]

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORcall( arg_dets )                   \
BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARGS_WITHOUT_FRONT( arg_dets ) )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORassign( arg_dets )                 \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
^ BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORplus_assign( arg_dets )            \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
+= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORminus_assign( arg_dets )           \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
-= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORmultiply_assign( arg_dets )        \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
*= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORdivide_assign( arg_dets )          \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
/= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORmodulus_assign( arg_dets )         \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
%= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORbit_and_assign( arg_dets )         \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
&= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORbit_or_assign( arg_dets )          \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
|= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORbit_xor_assign( arg_dets )         \
   BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                    \
^= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORleft_shift_assign( arg_dets )      \
    BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                   \
<<= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORright_shift_assign( arg_dets )     \
    BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                   \
>>= BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORpreincrement( arg_dets )           \
++BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORpostincrement( arg_dets )          \
BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )++

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORpredecrement( arg_dets )           \
--BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORpostdecrement( arg_dets )          \
BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )--

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORcomma( arg_dets )                  \
  BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                     \
, BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

// ToDo: Fix this (detect num params and call accordingly as mem or nonmem)
#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORnew( arg_dets )                    \
new BOOST_GENERIC_DETAIL_ARG_DETS_CLASS_TYPE( arg_dets )

// ToDo: Fix this (detect num params and call accordingly as mem or nonmem)
#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORnew_array( arg_dets )              \
new BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )[1]

// ToDo: Fix this (detect num params and call accordingly as mem or nonmem)
#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORdelete( arg_dets )                 \
delete BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )[1]

// ToDo: Fix this (detect num params and call accordingly as mem or nonmem)
#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORdelete_array( arg_dets )

// ToDo: Fix -- only call it this way if it's not a pointer
#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORarrow( arg_dets )                  \
BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 ).operator ->()

#define BOOST_GENERIC_DETAIL_INVOKE_OPERATORarrow_dereference( arg_dets )      \
    BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 0 )                   \
->* BOOST_GENERIC_DETAIL_ARG_DETS_DECLVAL_ARG( arg_dets, 1 )

#endif // BOOST_GENERIC_DETAIL_OPERATOR_DETS_HPP
