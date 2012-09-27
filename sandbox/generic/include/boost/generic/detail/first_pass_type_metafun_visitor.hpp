#ifndef BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_VISITOR_HPP

#include <boost/generic/detail/dummy_type.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNaxiom( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNrequires( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_NO_DEF( i, param_dets     \
                                                           , name              \
                                                           , default_          \
                                                           )                   \
BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_PROVIDED                          \
( i, boost_generic_detail_first_pass, name )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_PROVIDED( i, root, name ) \
template< class BoostGenericDetailConceptMap                                   \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( root, name )                                              \
{ typedef ::boost::generic::detail::dummy_type_< i > type; };                  \
                                                                               \
template< class BoostGenericDetailConceptMap >                                 \
struct BOOST_PP_CAT( root, name )                                              \
       < BoostGenericDetailConceptMap                                          \
       , typename ::boost::generic::detail::always_void                        \
         < typename BoostGenericDetailConceptMap::name >::type                 \
       > { typedef typename BoostGenericDetailConceptMap::name type; };

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_NO_DEF_( i, param_dets    \
                                                             , root, name      \
                                                             )                 \
template< class BoostGenericDetailConceptMap                                   \
        , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( root, name )                                              \
{ typedef ::boost::generic::detail::dummy_type_< i > type; };                  \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        >                                                                      \
struct BOOST_PP_CAT( root, name )                                              \
       < BoostGenericDetailConceptMap                                          \
       , typename ::boost::generic::detail::always_void                        \
         < typename BoostGenericDetailConceptMap::name >::type                 \
       > { typedef typename BoostGenericDetailConceptMap::name type; };


#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_WITH_DEF( i, param_dets   \
                                                             , name            \
                                                             , default_        \
                                                             )                 \
BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_PROVIDED                          \
( i, boost_generic_detail_provided, name )                                     \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        , class BoostGenericDetailProvidedName                                 \
            = typename BOOST_PP_CAT( boost_generic_detail_provided, name )     \
              < BoostGenericDetailConceptMap                                   \
              , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( param_dets )     \
              >::type                                                          \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_first_pass, name )                   \
{ typedef BoostGenericDetailProvidedName type; };                              \
                                                                               \
template< class BoostGenericDetailConceptMap                                   \
        , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS( param_dets )         \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_first_pass, name )                   \
       < BoostGenericDetailConceptMap                                          \
       , BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS( param_dets )            \
       , ::boost::generic::detail::dummy_type_< i >                            \
       , typename ::boost::generic::detail::always_void                        \
         < BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ ) >::type               \
       >                                                                       \
{                                                                              \
  typedef BOOST_GENERIC_DETAIL_REMOVE_PAREN( default_ ) type;                  \
};

// ToDo: Only do this if a default is not present
#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNtypename( i, d, name       \
                                                             , default_        \
                                                             )                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( default_ )                \
            , BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_NO_DEF              \
            , BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_WITH_DEF            \
            )( i, d, name, default_ )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNconstrained_typename( i, d \
                                                                  , constraint \
                                                                  , name       \
                                                                  , default_   \
                                                                  )            \
BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNtypename( i, d, name, default_ )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNmember_typename( i, d      \
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNfunction( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNmember_function( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNstatic_member_function(...)

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNprefix_unary_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNpostfix_unary_operator(...)

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNbinary_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNcall_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNcomma_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNsubscript_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNarrow_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNassign_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNdeallocation_operator(...)

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNconstructor( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNexplicit_constructor( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNdestructor( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNconversion( ... )

#define BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUNexplicit_conversion( ... )


#endif // BOOST_GENERIC_DETAIL_FIRST_PASS_TYPE_METAFUN_VISITOR_HPP
