/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_SFINAE_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_SFINAE_VISITOR_HPP

#include <boost/generic/detail/always_void.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace generic { namespace detail {

template< class Tag, unsigned Index >
struct unknown_type {};

} } }

#define BOOST_GENERIC_DETAIL_SFINAE_STRUCT( param_index, param_dets, ... )     \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        , class ConceptMap, class Enabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( is_valid_param, param_index )                             \
  : ::boost::mpl::false_ {};                                                   \
                                                                               \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        , class ConceptMap                                                     \
        >                                                                      \
struct BOOST_PP_CAT( is_valid_param, param_index )                             \
       < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( param_dets )            \
       , ConceptMap                                                            \
       , typename ::boost::generic::detail::always_void< __VA_ARGS__ >::type   \
       >                                                                       \
  : boost::mpl::true_ {};

#define BOOST_GENERIC_DETAIL_ENABLE_IF_STRUCT( param_index, param_dets, ... )  \
BOOST_GENERIC_DETAIL_SFINAE_STRUCT                                             \
( param_index, param_dets, typename ::boost::enable_if< __VA_ARGS__ >::type )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORaxiom( arg )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORrequires( arg )                     \
BOOST_GENERIC_DETAIL_ENABLE_IF_STRUCT                                          \
( decltype( boost_generic_detail_validity_checker                              \
            ( ::boost::generic::detail::type_< arg >() )                       \
          )                                                                    \
)

struct deducers
{
  struct result_type {};
  struct other_stuff {};

  template< class result_type >
  static ::boost::mpl::identity< result_type >
  deduce_result_type( std::pair< int, result_type > );
};

struct deduce_result_type
  : types_base
{
template< class result_type >
boost::mpl::identity< result_type >
deduce( pair< int, result_type >

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORtypename( name, default_ )          \
template< class ConceptMap, class Enabler = void >                             \
struct BOOST_PP_CAT( has_typename_, name ) : ::boost::mpl::false_ {};          \
                                                                               \
template< class ConceptMap >                                                   \
struct BOOST_PP_CAT( has_typename_, name )                                     \
       < ConceptMap                                                            \
       , typename ::boost::generic::detail::always_void                        \
         < typename ConceptMap::name >::type                                   \
       > : ::boost::mpl::true_ {};                                             \
                                                                               \
template< class ConceptMap >                                                   \
struct BOOST_PP_CAT( get_typename_, name )                                     \
{                                                                              \
  typedef typename ConceptMap::name type;                                      \
};                                                                             \
                                                                               \
typedef typename ::boost::mpl::eval_if                                         \
        < BOOST_PP_CAT( has_typename_, name )< ConceptMap >                    \
        , BOOST_PP_CAT( get_typename_, name )< ConceptMap >                    \
        , ::boost::mpl::identity< ::boost::generic::detail::unknown_type >     \
        >::type BOOST_PP_CAT( boost_generic_detail_typename_first_pass, name );\
                                                                               \
BOOST_GENERIC_DETAIL_SFINAE_STRUCT(

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORconstrained_typename(      \
                                                                     constraint\
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( constraint )                                \
name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORmember_typename( this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
typename BOOST_GENERIC_DETAIL_REMOVE_PAREN                                     \
( this_type )::name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORconstrained_member_typename(\
                                                                     constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )           \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( constraint )                                \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::name BOOST_GENERIC_DETAIL_EQ_DEFAULT_OR_EMPTY( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORfunction( return_type, name\
                                                            , param_dets       \
                                                            , default_         \
                                                            )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                               \
name( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )           \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORmember_function(           \
                                                                    return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::name(                                                           \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )                 \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORstatic_member_function(    \
                                                                    return_type\
                                                                  , this_type  \
                                                                  , name       \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
static                                                                         \
BOOST_GENERIC_DETAIL_SFINAE_VISITORmember_function                    \
( return_type, this_type, name, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR(           \
                                                                    return_type\
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_SFINAE_VISITORfunction                           \
( return_type, operator operator_, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORprefix_unary_operator      \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORpostfix_unary_operator     \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORbinary_operator            \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORcall_operator( return_type \
                                                                 , param_dets  \
                                                                 , default_    \
                                                                 )             \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR                    \
( return_type, (), param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORcomma_operator( return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type ) operator ,                    \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORarrow_operator( return_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR                    \
( return_type, ->, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORsubscript_operator( return_type     \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_BASIC_OPERATOR                             \
( return_type, [], param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITOR_MEMBER_OPERATOR(          \
                                                                    return_type\
                                                                  , this_type  \
                                                                  , operator_  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_SFINAE_VISITORmember_function                    \
( return_type, this_type, operator operator_, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORassign_operator(           \
                                                                    return_type\
                                                                  , this_type  \
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_MEMBER_OPERATOR                   \
( return_type, this_type, =, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORallocation_operator        \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORdeallocation_operator      \
BOOST_GENERIC_DETAIL_SFINAE_VISITOR_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORconstructor( this_type     \
                                                               , param_dets    \
                                                               , default_      \
                                                               )               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )                  \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORexplicit_constructor(      \
                                                                     this_type \
                                                                   , param_dets\
                                                                   , default_  \
                                                                   )           \
explicit                                                                       \
BOOST_GENERIC_DETAIL_SFINAE_VISITORconstructor                        \
( this_type, param_dets, default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORdestructor( this_type      \
                                                              , default_       \
                                                              )                \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::~BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )()               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORconversion( target_type    \
                                                              , param_dets     \
                                                              , default_       \
                                                              )                \
operator BOOST_GENERIC_DETAIL_REMOVE_PAREN                                     \
( target_type )( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )\
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ )

#define BOOST_GENERIC_DETAIL_SFINAE_VISITORexplicit_conversion(       \
                                                                    target_type\
                                                                  , param_dets \
                                                                  , default_   \
                                                                  )            \
explicit                                                                       \
BOOST_GENERIC_DETAIL_SFINAE_VISITORconversion                         \
( target_type, param_dets, default_ )

#endif // BOOST_GENERIC_DETAIL_SFINAE_VISITOR_HPP
