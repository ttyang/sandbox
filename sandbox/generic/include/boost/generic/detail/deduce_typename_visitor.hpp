#ifndef BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_VISITOR_HPP

// Note: d here is a sequence of id-numbers of with associated functions

#include <boost/generic/detail/deduction_result.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEaxiom( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMErequires( ... )

// data here is:
//   (concept_param_dets)(typename_id)
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_MACRO( r, data, fun_id )          \
typename BOOST_GENERIC_DETAIL_NARY_CAT                                         \
         ( boost_generic_detail_deduce_, fun_id, _                             \
         , BOOST_PP_SEQ_ELEM( 1, data )                                        \
         )                                                                     \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS                        \
           ( BOOST_PP_SEQ_ELEM( 0, data ) )                                    \
         >::type,

// d here is:
//   (concept_param_dets)((function_id_seq))
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEtypename( i, d, name, default_ )   \
template< BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS                       \
          ( BOOST_PP_SEQ_ELEM( 0, d ) )                                        \
        , class BoostGenericDetailEnabler = void                               \
        >                                                                      \
struct BOOST_PP_CAT( boost_generic_detail_deduce, name )                       \
{                                                                              \
  typedef typename ::boost::generic::detail::deduction_result                  \
          < ::boost::mpl::vector                                               \
            < BOOST_PP_SEQ_FOR_EACH                                            \
              ( BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_MACRO                     \
              , (BOOST_PP_SEQ_ELEM( 0, d ))(i)                                 \
              , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, d ) ) \
              )                                                                \
              ::boost::generic::detail::dummy_type                             \
            >                                                                  \
          >::type type;                                                        \
};

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEconstrained_typename( i, d         \
                                                                , constraint   \
                                                                , name         \
                                                                , default_     \
                                                                )              \
BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEtypename( i, d, name, default_ )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEmember_typename( i, d, this_type   \
                                                           , name              \
                                                           , default_          \
                                                           )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEconstrained_member_typename(       \
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEfunction( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEmember_function( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEstatic_member_function(...)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEprefix_unary_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEpostfix_unary_operator(...)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEbinary_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEcall_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEcomma_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEarrow_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEsubscript_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEassign_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEdeallocation_operator(...)

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEconstructor( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEexplicit_constructor( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEdestructor( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEconversion( ... )

#define BOOST_GENERIC_DETAIL_DEDUCE_TYPENAMEexplicit_conversion( ... )

#endif // BOOST_GENERIC_DETAIL_DEDUCE_TYPENAME_VISITOR_HPP
