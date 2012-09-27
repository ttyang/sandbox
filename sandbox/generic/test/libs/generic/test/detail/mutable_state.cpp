/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/generic/detail/mutable_state.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/lambda.hpp>

#include <type_traits>

template< class T >
struct mutable_push_back
{
  template< class PreviousState >
  struct apply : boost::mpl::push_back< PreviousState, T > {};
};

struct type_list_tag {};

BOOST_GENERIC_DETAIL_INITIALIZE_STATE( type_list_tag, boost::mpl::vector<> )

typedef BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ) empty_list;

static_assert
( boost::mpl::empty< empty_list >::value
, "Newly-started type list is not an empty type list."
);

BOOST_GENERIC_DETAIL_MODIFY_STATE( type_list_tag, mutable_push_back< int > )

typedef BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ) one_element_list;

static_assert
( boost::mpl::size< one_element_list >::value == 1
, "Type list size is not correct after one push_back."
);

static_assert
( std::is_same
  < boost::mpl::at_c< one_element_list, 0 >::type
  , int
  >::value
, "Type list element is not correct after one push_back."
);

BOOST_GENERIC_DETAIL_MODIFY_STATE( type_list_tag, mutable_push_back< float > )

typedef BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ) two_element_list;

static_assert
( boost::mpl::size< two_element_list >::value == 2
, "Type list size is not correct after two push_backs."
);

static_assert
( std::is_same
  < boost::mpl::at_c< two_element_list, 0 >::type
  , int
  >::value
, "Type list first element is not correct after two push_backs."
);

static_assert
( std::is_same
  < boost::mpl::at_c< two_element_list, 1 >::type
  , float
  >::value
, "Type list second element is not correct after two push_backs."
);

BOOST_GENERIC_DETAIL_MODIFY_STATE( type_list_tag, mutable_push_back< char > )

typedef BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ) three_element_list;

static_assert
( boost::mpl::size< three_element_list >::value == 3
, "Type list size is not correct after three push_backs."
);

static_assert
( std::is_same
  < boost::mpl::at_c< three_element_list, 0 >::type
  , int
  >::value
, "Type list first element is not correct after three push_backs."
);

static_assert
( std::is_same
  < boost::mpl::at_c< three_element_list, 1 >::type
  , float
  >::value
, "Type list second element is not correct after three push_backs."
);

static_assert
( std::is_same
  < boost::mpl::at_c< three_element_list, 2 >::type
  , char
  >::value
, "Type list second element is not correct after three push_backs."
);

BOOST_GENERIC_DETAIL_SET_STATE( type_list_tag, int )

static_assert
( std::is_same< BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ), int >::value
, "State not int after explicit set."
);

BOOST_GENERIC_DETAIL_SET_STATE( type_list_tag, char )

static_assert
( std::is_same< BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ), char >::value
, "State not char after explicit set."
);

BOOST_GENERIC_DETAIL_MODIFY_STATE
( type_list_tag, std::add_pointer< boost::mpl::_1 > )

static_assert
( std::is_same< BOOST_GENERIC_DETAIL_GET_STATE( type_list_tag ), char* >::value
, "State not char* after add_pointer operation."
);

template< class = void >
struct unary_template_detector
{
  template< template< class > class UnaryTypeTemplate >
  static void is_unary_type_template_impl();

#define UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( type )                             \
template< template< type > class UnaryValueTemplate >                          \
static type unary_value_template_type_impl();

UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( bool )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( char )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( unsigned char )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( signed char )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( char16_t )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( char32_t )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( short )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( unsigned short )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( int )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( unsigned )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( long )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( unsigned long )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( long long )
UNARY_VALUE_TEMPLATE_TYPE_DETECTOR( unsigned long long )
// TODO do pointer and reference types

};

//( foo )( ((UnaryMetafunction) template( template< class > class ) )

template< class >
struct unary_type_template;

template< class, class >
struct binary_type_template;

template< int >
struct unary_int_template;

template< int, int >
struct binary_int_template;

template< class > struct always_true : std::true_type {};

#define UNARY_TYPE_TEMPLATE_DETECTOR( name )                                   \
template< class Dummy = void, class = void >                                   \
struct name ## is_unary_type_template_impl : std::false_type {};               \
                                                                               \
template< class Dummy >                                                        \
struct name ## is_unary_type_template_impl                                     \
       < Dummy                                                                 \
       , typename ::std::enable_if                                             \
         < always_true                                                         \
           < decltype                                                          \
             ( unary_template_detector< Dummy >                                \
               ::template is_unary_type_template_impl< name >()                \
             )                                                                 \
           >::value                                                            \
         >::type                                                               \
       >                                                                       \
  : std::true_type {};                                                         \
                                                                               \
static bool constexpr name ## is_unary_type_template                           \
  = name ## is_unary_type_template_impl<>::value;

#define UNARY_VALUE_TEMPLATE_DETECTOR( name )                                  \
template< class Dummy = void, class = void >                                   \
struct name ## is_unary_value_template_impl : std::false_type {};              \
                                                                               \
template< class Dummy >                                                        \
struct name ## is_unary_value_template_impl                                    \
       < Dummy                                                                 \
       , typename ::std::enable_if                                             \
         < always_true                                                         \
           < decltype                                                          \
             ( unary_template_detector< Dummy >                                \
               ::template unary_value_template_type_impl< name >()             \
             )                                                                 \
           >::value                                                            \
         >::type                                                               \
       >                                                                       \
{                                                                              \
  typedef std::true_type type;                                                 \
  typedef decltype                                                             \
          ( unary_template_detector< Dummy >                                   \
            ::template unary_value_template_type_impl< name >()                \
          ) value_type;                                                        \
};                                                                             \
                                                                               \
static bool constexpr name ## is_unary_value_template                          \
  = name ## is_unary_value_template_impl<>::type::value;

UNARY_TYPE_TEMPLATE_DETECTOR( unary_type_template )
UNARY_TYPE_TEMPLATE_DETECTOR( binary_type_template )
UNARY_TYPE_TEMPLATE_DETECTOR( unary_int_template )
UNARY_TYPE_TEMPLATE_DETECTOR( binary_int_template )

UNARY_VALUE_TEMPLATE_DETECTOR( unary_type_template )
UNARY_VALUE_TEMPLATE_DETECTOR( binary_type_template )
UNARY_VALUE_TEMPLATE_DETECTOR( unary_int_template )
UNARY_VALUE_TEMPLATE_DETECTOR( binary_int_template )
//
struct left {

  template< class T >
  static int foo( T );

};

struct right {

  template< class T >
  static int foo( T* );

};

struct child : left, right
{
  using left::foo;
  using right::foo;
};

template< class T >
decltype( child::foo( T() ) ) bloop();

int main()
{
  bloop< int* >();
}

template< class T > struct C {};
template< class T, class U > struct D : C< T > {};
template< class T > struct E {};

struct c_info;
struct d_info;
struct e_info;

template< class T > struct A {};

template< class T > struct D< A< T >, T > {};

template< class T, class U >
using C_base = C< T >;

template< class T >
void foo( C_base< A< T >, T > );

void bar()
{
  foo( C< A< int > >() );
}

#define IS_CONCEPT( name )                                                     \

struct concepts {};

struct concept_info_base
{
  void target_concept_info();
};

BOOST_GENERIC_DETAIL_INITIALIZE_STATE( concepts, concept_info_base )

struct c_concept_info
  : concept_info_base
{
  using concept_info_base::target_concept_info;
private:
  template< template< class T > class >
  struct target_concept_info_impl {};

  enum dummy { dummy_val };
public:
  template< template< class T > class Concept >
  static typename target_concept_info_impl< Concept >::type
  target_concept_info( dummy = dummy_val );
};

template<>
struct c_concept_info::target_concept_info_impl< C >
{
  struct type
  {
    typedef void void_;
    typedef std::true_type is_concept;
    typedef c_info info;
  };
};

struct d_concept_info
  : c_concept_info
{
  using c_concept_info::target_concept_info;
private:
  template< template< class T, class U > class >
  struct target_concept_info_impl {};

  enum dummy { dummy_val };
public:
  template< template< class T, class U > class Concept >
  static typename target_concept_info_impl< Concept >::type
  target_concept_info( dummy = dummy_val );
};

template<>
struct d_concept_info::target_concept_info_impl< D >
{
  struct type
  {
    typedef void void_;
    typedef std::true_type is_concept;
    typedef d_info info;
  };
};

struct e_concept_info
  : d_concept_info
{
  using d_concept_info::target_concept_info;
private:
  template< template< class T > class >
  struct target_concept_info_impl {};

  enum dummy { dummy_val };
public:
  template< template< class T > class Concept >
  static typename target_concept_info_impl< Concept >::type
  target_concept_info( dummy = dummy_val );
};

template<>
struct e_concept_info::target_concept_info_impl< E >
{
  struct type
  {
    typedef void void_;
    typedef std::true_type is_concept;
    typedef e_info info;
  };
};

template< class T > struct no_match;

template< class T, class Dummy >
struct identity
{
  typedef T type;
};

#define CONCEPT_CHECKER( name )\
template< class Dummy = void, class = void >\
struct name ## is_valid\
{\
  typedef std::false_type is_concept;\
};\
\
template< class Dummy >\
struct name ## is_valid< Dummy\
                        , typename decltype\
                          ( identity< e_concept_info, Dummy >::type\
                            ::template target_concept_info< name >()\
                          )::void_\
                        >\
  : decltype( identity< e_concept_info, Dummy >::type\
              ::template target_concept_info< name >()\
            ) {};

CONCEPT_CHECKER( C )
CONCEPT_CHECKER( D )
CONCEPT_CHECKER( E )
CONCEPT_CHECKER( no_match )

void test_get_concept_info()
{
  e_concept_info::target_concept_info< C >();
  e_concept_info::target_concept_info< D >();
  static_assert( Dis_valid<>::is_concept::value, "C not identified" );
  static_assert( Dis_valid<>::is_concept::value, "D not identified" );
  static_assert( Eis_valid<>::is_concept::value, "E not identified" );
  static_assert( !no_matchis_valid<>::is_concept::value, "no_match incorrectly identified" );
}

//void foo()
//{
//  unary_template_detector<>::is_unary_type_template_impl< unary_type_template >();
//}

static_assert( unary_type_templateis_unary_type_template, "Unary type template not detected" );
static_assert( !binary_type_templateis_unary_type_template, "Unary type template incorrectly detected" );
static_assert( !unary_int_templateis_unary_type_template, "Unary type template incorrectly detected" );
static_assert( !binary_int_templateis_unary_type_template, "Unary type template incorrectly detected" );

static_assert( !unary_type_templateis_unary_value_template, "Unary value template incorrectly detected" );
static_assert( !binary_type_templateis_unary_value_template, "Unary value template incorrectly detected" );
static_assert( unary_int_templateis_unary_value_template, "Unary value template not detected" );
static_assert( !binary_int_templateis_unary_value_template, "Unary value template incorrectly detected" );
