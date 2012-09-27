#ifndef BOOST_GENERIC_DETAIL_MAP_SPECIFIER_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_MAP_SPECIFIER_VISITOR_HPP


#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#define BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( def_or_empty_in_paren )  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( def_or_empty_in_paren )   \
            , BOOST_PP_IDENTITY(;)                                             \
            , BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON_                    \
            ) def_or_empty_in_paren

#define BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON_( ... ) __VA_ARGS__

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERtypedef( i, d, typedef_ )            \
typedef BOOST_GENERIC_DETAIL_REMOVE_PAREN( typedef_ );

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERfunction( i, d, return_type, name    \
                                                  , param_dets, definition     \
                                                  )                            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS( param_dets, name )    \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERmember_function( i, d                \
                                                         , return_type         \
                                                         , this_type           \
                                                         , name                \
                                                         , param_dets          \
                                                         , definition          \
                                                         )                     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type )                               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_NAME_AND_PARAMS         \
( param_dets, name )                                                           \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERstatic_member_function( i, d         \
                                                                , return_type  \
                                                                , this_type    \
                                                                , name         \
                                                                , param_dets   \
                                                                , definition   \
                                                                )              \
static                                                                         \
BOOST_GENERIC_DETAIL_MAP_SPECIFIERmember_function                              \
( i, d, return_type, this_type, name, param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIER_BASIC_OPERATOR( i, d, return_type   \
                                                         , operator_           \
                                                         , param_dets          \
                                                         , definition          \
                                                         )                     \
BOOST_GENERIC_DETAIL_MAP_SPECIFIERfunction                                     \
( i, d, return_type, operator operator_, param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERprefix_unary_operator                \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERpostfix_unary_operator               \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERbinary_operator                      \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_BASIC_OPERATOR

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERcall_operator( i, d, return_type     \
                                                       , param_dets, definition\
                                                                 )             \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_BASIC_OPERATOR                              \
( i, d, return_type, (), param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERcomma_operator( i, d, return_type    \
                                                        , param_dets           \
                                                        , definition           \
                                                        )                      \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( return_type ) operator ,                    \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )               \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERarrow_operator( i, d, return_type    \
                                                        , param_dets           \
                                                        , definition           \
                                                        )                      \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_BASIC_OPERATOR                              \
( i, d, return_type, ->, param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIER_MEMBER_OPERATOR( i, d, return_type  \
                                                          , this_type          \
                                                          , operator_          \
                                                          , param_dets         \
                                                          , definition         \
                                                          )                    \
BOOST_GENERIC_DETAIL_MAP_SPECIFIERmember_function                              \
( i, d, return_type, this_type, operator operator_, param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERassign_operator( i, d, return_type   \
                                                         , this_type           \
                                                         , param_dets          \
                                                         , definition          \
                                                         )                     \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_MEMBER_OPERATOR                             \
( i, d, return_type, this_type, =, param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERallocation_operator                  \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERdeallocation_operator                \
BOOST_GENERIC_DETAIL_MAP_SPECIFIER_MEMBER_OPERATOR

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERconstructor( i, d, this_type         \
                                                     , param_dets, definition  \
                                                     )                         \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::BOOST_GENERIC_DETAIL_REMOVE_PAREN                               \
( this_type )( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )  \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERexplicit_constructor( i, d, this_type\
                                                              , param_dets     \
                                                              , definition     \
                                                              )                \
explicit                                                                       \
BOOST_GENERIC_DETAIL_MAP_SPECIFIERconstructor                                  \
( i, d, this_type, param_dets, definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERdestructor( i, d, this_type          \
                                                    , definition               \
                                                    )                          \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( this_type )::~BOOST_GENERIC_DETAIL_REMOVE_PAREN( this_type )()               \
BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERconversion( i, d, target_type        \
                                                    , param_dets, definition   \
                                                    )                          \
operator BOOST_GENERIC_DETAIL_REMOVE_PAREN                                     \
( target_type )( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets ) )\
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_POST_PARAM_LIST_PART( param_dets )     \
BOOST_GENERIC_DETAIL_DEFINITION_OR_SEMICOLON( definition )

#define BOOST_GENERIC_DETAIL_MAP_SPECIFIERexplicit_conversion( i, d            \
                                                             , target_type     \
                                                             , param_dets      \
                                                             , definition      \
                                                             )                 \
explicit                                                                       \
BOOST_GENERIC_DETAIL_MAP_SPECIFIERconversion                                   \
( i, d, target_type, param_dets, definition )

#endif // BOOST_GENERIC_DETAIL_MAP_SPECIFIER_VISITOR_HPP
