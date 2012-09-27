#ifndef BOOST_GENERIC_DETAIL_TYPENAME_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_TYPENAME_VISITOR_HPP

#define BOOST_GENERIC_DETAIL_TYPENAMEaxiom( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMErequires( ... )

// data here is:
//   (concept_param_dets)(typename_id)
#define BOOST_GENERIC_DETAIL_TYPENAME_MACRO( r, data, fun_id )          \
typename BOOST_GENERIC_DETAIL_NARY_CAT                                         \
         ( boost_generic_detail_deduce_, fun_id, _                             \
         , BOOST_PP_SEQ_ELEM( 1, data )                                        \
         )                                                                     \
         < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS                        \
           ( BOOST_PP_SEQ_ELEM( 0, data ) )                                    \
         >::type,

// d here is:
//   (concept_param_dets)(function_id_seq)
#define BOOST_GENERIC_DETAIL_TYPENAMEtypename( i, concept_map, name, default_ )\
typedef typename ::boost::mpl::eval_if                                         \
        < BOOST_PP_CAT( boost_generic_detail_has_, name )< concept_map >       \
        , BOOST_PP_CAT( boost_generic_detail_get_, name )                      \
        , BOOST_PP_CAT( boost_generic_detail_deduce, name )                    \
        >::type name;

#define BOOST_GENERIC_DETAIL_TYPENAMEconstrained_typename( i, d         \
                                                                , constraint   \
                                                                , name         \
                                                                , default_     \
                                                                )              \
BOOST_GENERIC_DETAIL_TYPENAMEtypename( i, d, name, default_ )

// ToDo: Define
#define BOOST_GENERIC_DETAIL_TYPENAMEmember_typename( i, d, this_type   \
                                                           , name              \
                                                           , default_          \
                                                           )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_TYPENAMEconstrained_member_typename(       \
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_TYPENAMEfunction( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEmember_function( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEstatic_member_function(...)

#define BOOST_GENERIC_DETAIL_TYPENAMEprefix_unary_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEpostfix_unary_operator(...)

#define BOOST_GENERIC_DETAIL_TYPENAMEbinary_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEcall_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEcomma_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEarrow_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEassign_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEdeallocation_operator(...)

#define BOOST_GENERIC_DETAIL_TYPENAMEconstructor( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEexplicit_constructor( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEdestructor( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEconversion( ... )

#define BOOST_GENERIC_DETAIL_TYPENAMEexplicit_conversion( ... )

#endif // BOOST_GENERIC_DETAIL_TYPENAME_VISITOR_HPP
