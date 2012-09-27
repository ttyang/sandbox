/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/param_list.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#if 0

BOOST_GENERIC_DETAIL_PARAMS( ((0)((class) a), (1)((class) b)) )
BOOST_GENERIC_DETAIL_ARGS( ((0)((class) a), (1)((class) b)) )
BOOST_GENERIC_DETAIL_DECLVAL_ARGS( ((0)((class) a), (1)((class) b)) )
BOOST_GENERIC_DETAIL_FUN_CALL_DECLVAL_ARGS( ((0)((class) a), (1)((class) b)) )

#else

/////////////////////////
// Prepare Test Inputs //
/////////////////////////
#define UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS                             \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( class X )

#define PARENTHESIZED_INVALID_PARAM_LIST_DETAILS                               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( class X ) )

#define PARTIALLY_VALID_PARAM_LIST_DETAILS                                     \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (class) X, class Y ) )

#define NULLARY_PARAM_LIST_DETAILS                                             \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( () )

#define UNARY_PARAM_LIST_DETAILS                                               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (class) X ) )

#define NO_PARAM_NAME_PARAM_LIST_DETAILS                                       \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (class) ) )

#define BINARY_PARAM_LIST_DETAILS                                              \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (class) X, (X) Y ) )

#define VARIADIC_PARAM_LIST_DETAILS                                            \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (class,,,) X ) )

#define VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS                                \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( () const )

#define NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS                             \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (int) x ) const )

#define DECLVAL_PARAM_LIST                                                     \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( ( (a), (b) ) )

//////////////////
// Begin Tests  //
//////////////////
#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                   \
    ( UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Unparenthesized invalid param list recognized as parenthesized
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                           \
    ( UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Unparenthesized invalid param list recognized as valid
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS           \
    ( UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Unparenthesized invalid param list recognized as valid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID                            \
    ( UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Unparenthesized invalid param list recognized as void
#endif
//////////
#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( PARENTHESIZED_INVALID_PARAM_LIST_DETAILS )

#error Parenthesized invalid param list recognized as not parenthesized
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                           \
    ( PARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Parenthesized invalid param list recognized as valid
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS           \
    ( PARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Parenthesized invalid param list recognized as valid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID                            \
    ( PARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Parenthesized invalid param list recognized as void
#endif
//////////
#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( PARTIALLY_VALID_PARAM_LIST_DETAILS )

#error Partially valid param list recognized as not parenthesized
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                           \
    ( PARTIALLY_VALID_PARAM_LIST_DETAILS )
#error Partially valid param list recognized as valid
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS           \
    ( PARTIALLY_VALID_PARAM_LIST_DETAILS )
#error Partially valid param list recognized as valid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID                            \
    ( PARTIALLY_VALID_PARAM_LIST_DETAILS )
#error Partially valid param list recognized as void
#endif
//////////
#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( NULLARY_PARAM_LIST_DETAILS )

#error Nullary param list recognized as not parenthesized
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( NULLARY_PARAM_LIST_DETAILS )
#error Nullary param list recognized as not valid
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS          \
    ( NULLARY_PARAM_LIST_DETAILS )
#error Nullary param list param list recognized as invalid template params
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID                           \
    ( NULLARY_PARAM_LIST_DETAILS )
#error Nullary param list recognized as not void
#endif

void nullary_function_receiver() {}

void nullary_function
     ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
       ( NULLARY_PARAM_LIST_DETAILS )
     ) BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART
       ( NULLARY_PARAM_LIST_DETAILS )
{
  nullary_function_receiver
  ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS
    ( NULLARY_PARAM_LIST_DETAILS )
  );
}

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( UNARY_PARAM_LIST_DETAILS )

#error Unary param list recognized as not parenthesized
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( UNARY_PARAM_LIST_DETAILS )
#error Unary param list recognized as not valid
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS          \
    ( UNARY_PARAM_LIST_DETAILS )
#error Unary param list param list recognized as invalid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( UNARY_PARAM_LIST_DETAILS )
#error Unary param list recognized as void
#endif

template< class T >
void unary_function_template_receiver() {}

template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
          ( UNARY_PARAM_LIST_DETAILS )
        >
void unary_function_template
     ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS
       ( UNARY_PARAM_LIST_DETAILS )
     )
{
  unary_function_template_receiver
  < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( UNARY_PARAM_LIST_DETAILS ) >
  ();
}

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( NO_PARAM_NAME_PARAM_LIST_DETAILS )

#error Unary param list with no parameter name recognized as not parenthesized.
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( NO_PARAM_NAME_PARAM_LIST_DETAILS )
#error Unary param list with no parameter name recognized as not valid
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS          \
    ( NO_PARAM_NAME_PARAM_LIST_DETAILS )
#error Unary param list param list with no parameter name recognized as invalid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( NO_PARAM_NAME_PARAM_LIST_DETAILS )
#error Unary param list with no parameter name recognized as void
#endif

template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
          ( NO_PARAM_NAME_PARAM_LIST_DETAILS )
        >
void no_name_unary_function_template_receiver();

template< class T >
void no_name_unary_function_template_receiver() {}

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( BINARY_PARAM_LIST_DETAILS )

#error Binary param list incorrectly recognized as not parenthesized
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( BINARY_PARAM_LIST_DETAILS )
#error Binary param list incorrectly recognized as not valid
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS          \
    ( BINARY_PARAM_LIST_DETAILS )
#error Binary param list param list recognized as invalid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( BINARY_PARAM_LIST_DETAILS )
#error Binary param list incorrectly recognized as void
#endif

template< class T, int X >
void binary_function_template_receiver() {}

template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
          ( BINARY_PARAM_LIST_DETAILS )
        >
void binary_function_template()
{
  binary_function_template_receiver
  < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( BINARY_PARAM_LIST_DETAILS ) >
  ();
}


#if 0


#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( VARIADIC_PARAM_LIST_DETAILS )

#error Variadic param list incorrectly recognized as not parenthesized
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( VARIADIC_PARAM_LIST_DETAILS )
#error Variadic param list incorrectly recognized as not valid
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS          \
    ( VARIADIC_PARAM_LIST_DETAILS )
#error Variadic param list param list recognized as invalid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( VARIADIC_PARAM_LIST_DETAILS )
#error Variadic param list incorrectly recognized as void
#endif

template< class... T >
void variadic_function_template_receiver() {}

template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
          ( VARIADIC_PARAM_LIST_DETAILS )
        >
void variadic_function_template()
{
  binary_function_template_receiver
  < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( VARIADIC_PARAM_LIST_DETAILS ) >
  ();
}



#endif


#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )

#error Void param list with extra data recognized as not parenthesized
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
#error Void param list with extra data recognized as not valid
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS           \
    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
#error Void param list with extra data recognized as valid template params
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID                           \
    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
#error Void param list with extra data not recognized as void
#endif

struct success_type {};
struct failure_type {};

struct void_extra_data_helper
{
  void_extra_data_helper() {}

  failure_type foo( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
                    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
                  );

  success_type foo( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
                    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
                  ) BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART
                    ( VOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS );
};

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_PARENTHESIZED                  \
    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )

#error Nonvoid param list with extra data recognized as not parenthesized
#endif

#if !BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID                          \
    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
#error Nonvoid param list with extra data recognized as not valid
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID_TEMPLATE_PARAMS           \
    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
#error Nonvoid param list with extra data recognized as valid template params
#endif

#if BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID                            \
    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
#error Nonvoid param list with extra data recognized as void
#endif

struct nonvoid_extra_data_helper
{
  nonvoid_extra_data_helper() {}

  failure_type foo( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
                    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
                  );

  success_type foo( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS
                    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS )
                  ) BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART
                    ( NONVOID_PARAM_LIST_WITH_EXTRA_DATA_DETAILS );
};

void testing_function()
{
  nullary_function();

  unary_function_template( 0 );

  binary_function_template< int, 0 >();

  void_extra_data_helper const void_extra_data_tester;
  BOOST_STATIC_ASSERT( (boost::is_same< decltype( void_extra_data_tester.foo() )
                                      , success_type
                                      >::value
                       )
                     );

  nonvoid_extra_data_helper const nonvoid_extra_data_tester;
  BOOST_STATIC_ASSERT
  ( ( boost::is_same< decltype( nonvoid_extra_data_tester.foo( 0 ) )
                    , success_type
                    >::value
    )
  );
}

struct a {};
struct b {};

void a_b_fun( a, b );

void a_b_test()
{
  typedef decltype( a_b_fun( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARGS( DECLVAL_PARAM_LIST ) ) ) foo;
  typedef decltype( a_b_fun( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( DECLVAL_PARAM_LIST, 0 )
                           , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_DECLVAL_ARG_I( DECLVAL_PARAM_LIST, 1 )
                           )
                  ) bar;
}

#endif
