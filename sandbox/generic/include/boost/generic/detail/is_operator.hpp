#ifndef BOOST_GENERIC_DETAIL_IS_OPERATOR_HPP
#define BOOST_GENERIC_DETAIL_IS_OPERATOR_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/num_args_is_2.hpp>
#include <boost/generic/detail/tail_is_empty.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>

// Begin "is operator name" checks
#define BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME( ... )                           \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME_IMPL                                   \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME_IMPL( ... )                      \
BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME_IMPL_                                    \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_IS_OPERATOR                                           \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

// Begin "is nonmember operator name" checks
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR_NAME( ... )                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR_NAME_IMPL                         \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR_NAME_IMPL( ... )            \
BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME_IMPL_                                    \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATOR                                 \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

// Begin "is member operator name" checks
#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR_NAME( ... )                    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR_NAME_IMPL                            \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR_NAME_IMPL( ... )               \
BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME_IMPL_                                    \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATOR                                    \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

// Helper macro
#define BOOST_GENERIC_DETAIL_IS_OPERATOR_NAME_IMPL_( ... )                     \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2( __VA_ARGS__ )               \
, BOOST_GENERIC_DETAIL_TAIL_IS_EMPTY_AFTER_RESCAN                              \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
)( __VA_ARGS__ )

// Yields 1 for comma, call, and arrow, else 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OP( op_name )                         \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_IS_NONBASIC_OP, op_name )

#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPplus 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPminus 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPmultiply 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPdivide 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPmodulus 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPunary_plus 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPnegate 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPless 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPgreater 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPless_equal 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPgreater_equal 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPequal_to 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPnot_equal_to 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPlogical_and 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPlogical_or 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPlogical_not 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPbit_and 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPbit_or 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPbit_xor 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPcomplement 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPleft_shift 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPright_shift 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPdereference 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPaddress_of 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPsubscript 1
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPcall 1
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPassign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPplus_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPminus_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPmultiply_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPdivide_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPmodulus_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPbit_and_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPbit_or_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPbit_xor_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPleft_shift_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPright_shift_assign 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPpreincrement 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPpostincrement 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPpredecrement 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPpostdecrement 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPcomma 1
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPnew 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPnew_array 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPdelete 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OPdelete_array 0
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OParrow 1
#define BOOST_GENERIC_DETAIL_IS_NONBASIC_OParrow_dereference 0

#define BOOST_GENERIC_DETAIL_IS_ASSIGN( op_name )                              \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_IS_ASSIGN, op_name )

#define BOOST_GENERIC_DETAIL_IS_ASSIGNplus 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNminus 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNmultiply 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNdivide 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNmodulus 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNunary_plus 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNnegate 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNless 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNgreater 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNless_equal 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNgreater_equal 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNequal_to 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNnot_equal_to 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNlogical_and 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNlogical_or 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNlogical_not 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNbit_and 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNbit_or 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNbit_xor 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNcomplement 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNleft_shift 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNright_shift 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNdereference 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNaddress_of 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNsubscript 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNcall 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNassign 1
#define BOOST_GENERIC_DETAIL_IS_ASSIGNplus_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNminus_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNmultiply_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNdivide_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNmodulus_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNbit_and_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNbit_or_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNbit_xor_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNleft_shift_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNright_shift_assign 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNpreincrement 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNpostincrement 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNpredecrement 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNpostdecrement 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNcomma 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNnew 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNnew_array 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNdelete 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNdelete_array 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNarrow 0
#define BOOST_GENERIC_DETAIL_IS_ASSIGNarrow_dereference 0

#define BOOST_GENERIC_DETAIL_IS_OPERATORplus ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORminus ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORmultiply ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORdivide ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORmodulus ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORunary_plus ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORnegate ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORless ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORgreater ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORless_equal ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORgreater_equal ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORequal_to ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORnot_equal_to ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORlogical_and ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORlogical_or ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORlogical_not ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORbit_and ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORbit_or ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORbit_xor ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORcomplement ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORleft_shift ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORright_shift ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORdereference ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORaddress_of ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORsubscript ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORcall ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORassign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORplus_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORminus_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORmultiply_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORdivide_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORmodulus_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORbit_and_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORbit_or_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORbit_xor_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORleft_shift_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORright_shift_assign ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORpreincrement ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORpostincrement ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORpredecrement ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORpostdecrement ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORcomma ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORnew ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORnew_array ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORdelete ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORdelete_array ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORarrow ,
#define BOOST_GENERIC_DETAIL_IS_OPERATORarrow_dereference ,

#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORplus ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORminus ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORmultiply ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORdivide ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORmodulus ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORunary_plus ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORnegate ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORless ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORgreater ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORless_equal ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORgreater_equal ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORequal_to ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORnot_equal_to ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORlogical_and ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORlogical_or ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORlogical_not ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORbit_and ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORbit_or ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORbit_xor ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORcomplement ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORleft_shift ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORright_shift ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORdereference ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORaddress_of ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORsubscript ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORcall ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORplus_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORminus_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORmultiply_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORdivide_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORmodulus_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORbit_and_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORbit_or_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORbit_xor_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORleft_shift_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORright_shift_assign ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORpreincrement ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORpostincrement ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORpredecrement ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORpostdecrement ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORcomma ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORarrow ,
#define BOOST_GENERIC_DETAIL_IS_NONMEMBER_OPERATORarrow_dereference ,

#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATORassign ,
#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATORnew ,
#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATORnew_array ,
#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATORdelete ,
#define BOOST_GENERIC_DETAIL_IS_MEMBER_OPERATORdelete_array ,

#define BOOST_GENERIC_DETAIL_OPERATOR_KIND( op_name )                          \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_OP_KIND, op_name )

#define BOOST_GENERIC_DETAIL_OP_KINDplus               binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDminus              binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDmultiply           binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDdivide             binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDmodulus            binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDunary_plus         prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDnegate             prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDless               binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDgreater            binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDless_equal         binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDgreater_equal      binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDequal_to           binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDnot_equal_to       binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDlogical_and        binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDlogical_or         binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDlogical_not        prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDbit_and            binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDbit_or             binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDbit_xor            binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDcomplement         prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDleft_shift         binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDright_shift        binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDdereference        prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDaddress_of         prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDsubscript          subscript_operator
#define BOOST_GENERIC_DETAIL_OP_KINDcall               call_operator
#define BOOST_GENERIC_DETAIL_OP_KINDassign             assign_operator
#define BOOST_GENERIC_DETAIL_OP_KINDplus_assign        binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDminus_assign       binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDmultiply_assign    binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDdivide_assign      binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDmodulus_assign     binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDbit_and_assign     binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDbit_or_assign      binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDbit_xor_assign     binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDleft_shift_assign  binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDright_shift_assign binary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDpreincrement       prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDpostincrement      postfix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDpredecrement       prefix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDpostdecrement      postfix_unary_operator
#define BOOST_GENERIC_DETAIL_OP_KINDcomma              comma_operator
#define BOOST_GENERIC_DETAIL_OP_KINDnew                allocation_operator
#define BOOST_GENERIC_DETAIL_OP_KINDnew_array          allocation_operator
#define BOOST_GENERIC_DETAIL_OP_KINDdelete             deallocation_operator
#define BOOST_GENERIC_DETAIL_OP_KINDdelete_array       deallocation_operator
#define BOOST_GENERIC_DETAIL_OP_KINDarrow              arrow_operator
#define BOOST_GENERIC_DETAIL_OP_KINDarrow_dereference  binary_operator

// Begin "starts with operator" macros
#define BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR( ... )                       \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR_IMPL                               \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR_IMPL( ... )                  \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATOR                                  \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_OPERATORoperator ,

// Begin "eat operator" macros
#define BOOST_GENERIC_DETAIL_EAT_OPERATOR( ... )                               \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_OPERATOR, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_OPERATORoperator

#endif // BOOST_GENERIC_DETAIL_IS_OPERATOR_HPP
