/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/function_decl_details.hpp>
#include <boost/type_traits/is_same.hpp>

// ToDo: Add tests for incorrect input

/////////////////////////
// Prepare Test Inputs //
/////////////////////////
#define SIMPL_DECL                                                             \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS( ( iterator )( begin )() )

#define DECL_WITH_EXTRA_DATA                                                   \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS( ( const_iterator )( cbegin )() const )

#define DECL_WITH_DEFINITION                                                   \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS                                        \
( ( void )( swap_float )( (float) a, (float) b ),                              \
  {                                                                            \
    float const temp = a;                                                      \
    a = b;                                                                     \
    b = temp;                                                                  \
  }                                                                            \
)

#define MEMBER_DECL                                                            \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS                                        \
( ( void )( this(T) foo )( (std::size_t) size_ ) )

#define OPERATOR_DECL                                                          \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS                                        \
( ( void )( operator plus )( (float) a, (float) b ) )

#define OPERATOR_NONMEMBER_MISMATCH_DECL                                       \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS                                        \
( ( void )( operator new )( (float) a, (float) b ) )

#define OPERATOR_MEMBER_MISMATCH_DECL                                          \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS                                        \
( ( void )( this(T) operator plus )( (float) a, (float) b ) )

#define MEMBER_OPERATOR_DECL                                                   \
BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS                                        \
( ( void )( this(T) operator new )( (std::size_t) size_ ) )

////////////
#if !BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( MEMBER_DECL )
#error Associated member function not considered valid.
#endif

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( OPERATOR_NONMEMBER_MISMATCH_DECL )
#error Member operator considered valid nonmember operator.
#endif

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( OPERATOR_MEMBER_MISMATCH_DECL )
#error Nonmember operator considered valid member operator.
#endif

#if !BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( OPERATOR_DECL )
#error Associated operator not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( MEMBER_OPERATOR_DECL )
#error Associated member operator not considered valid.
#endif

////////////

struct iterator {};
struct const_iterator {};
struct begin {};
struct cbegin {};
struct swap_float {};

#if !BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( SIMPL_DECL )
#error Simple function declaration detected as invalid.
#endif

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_ERRORS( SIMPL_DECL )
#error Simple function declaration detected as having errors.
#endif

static_assert
( ( boost::is_same
    < iterator
    , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( SIMPL_DECL )
    >::value
  )
, "Simple function declaration return type is incorrect."
);

static_assert
( ( boost::is_same
    < begin
    , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME( SIMPL_DECL )
    >::value
  )
, "Simple function declaration name is incorrect."
);

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_DEFINITION( SIMPL_DECL )
#error Simple function declaration detected as having a definition.
#endif




#if !BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( DECL_WITH_EXTRA_DATA )
#error Const function declaration detected as invalid.
#endif

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_ERRORS( DECL_WITH_EXTRA_DATA )
#error Const function declaration detected as having errors.
#endif

static_assert
( ( boost::is_same
    < const_iterator
    , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE(DECL_WITH_EXTRA_DATA)
    >::value
  )
, "Const function declaration return type is incorrect."
);

static_assert
( ( boost::is_same
    < cbegin
    , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME(DECL_WITH_EXTRA_DATA)
    >::value
  )
, "Const function declaration name is incorrect."
);

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_DEFINITION(DECL_WITH_EXTRA_DATA)
#error Const function declaration detected as having a definition.
#endif

#if !BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( DECL_WITH_DEFINITION )
#error Function declaration with definition detected as invalid.
#endif

#if BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_ERRORS( DECL_WITH_DEFINITION )
#error Function declaration with definition detected as having errors.
#endif

static_assert
( ( boost::is_same
    < void
    , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE(DECL_WITH_DEFINITION)
    >::value
  )
, "Function declaration with definition return type is incorrect."
);

static_assert
( ( boost::is_same
    < swap_float
    , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME(DECL_WITH_DEFINITION)
    >::value
  )
, "Function declaration with definition name is incorrect."
);

#if! BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_HAS_DEFINITION(                   \
                                                          DECL_WITH_DEFINITION )
#error Function declaration with definition detected as not having a definition.
#endif


#define VALID_VISIT_MACRO( return_type, name_, param_dets, definition )        \
static_assert( BOOST_GENERIC_DETAIL_IS_EMPTY( definition )                     \
             , "Nonempty definition in visit to function without a definition" \
             );                                                                \
static_assert                                                                  \
( boost::is_same< void return_type, void( iterator ) >                         \
  ::value                                                                      \
, "Function return type not deduced correctly."                                \
);                                                                             \
static_assert                                                                  \
( boost::is_same< name_, begin >                                               \
  ::value                                                                      \
, "Function name not deduced correctly."                                       \
);

// ToDo: Define this macro
#define INVALID_VISIT_MACRO( ... )

BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_VISIT
( SIMPL_DECL, VALID_VISIT_MACRO, INVALID_VISIT_MACRO )
