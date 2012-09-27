#ifndef BOOST_GENERIC_DETAIL_CONCEPT_MAP_CONCEPT_AND_PARAMS_DETS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_CONCEPT_AND_PARAMS_DETS_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_details.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Checks if he argument matches the form (text)(nonempty,text)
// Gracefully handles if the argument is not a sequence or if there is more data
// after the last parameter
// Yields details in the form:
//   (is_valid_bit)(concept_name_in_parentheses)(params_in_parentheses)
#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS( ... )                    \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL                              \
( BOOST_GENERIC_DETAIL_SEQ_DETS( __VA_ARGS__ ), __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID( dets )          \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_CONCEPT( dets )           \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_PARAMS( dets )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL( seq_dets, ... )     \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( seq_dets )               \
            , BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_IS_SEQ         \
            , BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_INVALID        \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_INVALID( ... )       \
(0)                                                                            \
((invalid_concept_name_and_params_declaration))                                \
((invalid_concept_name_and_params_declaration))

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_IS_SEQ( seq )        \
BOOST_PP_IIF( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_SEQ_SIZE( seq ), 2 )        \
            , BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_SEQ_2          \
            , BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_INVALID        \
            )( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( seq ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IMPL_SEQ_2( nonvarseq )   \
( BOOST_PP_COMPL                                                               \
  ( BOOST_PP_BITOR                                                             \
    ( BOOST_GENERIC_DETAIL_IS_EMPTY                                            \
      ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                      \
        ( BOOST_PP_SEQ_ELEM( 0, nonvarseq ) )                                  \
      )                                                                        \
    , BOOST_GENERIC_DETAIL_IS_EMPTY                                            \
      ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                      \
        ( BOOST_PP_SEQ_ELEM( 1, nonvarseq ) )                                  \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)                                                                              \
( BOOST_PP_SEQ_ELEM( 0, nonvarseq ) )                                          \
( BOOST_PP_SEQ_ELEM( 1, nonvarseq ) )

#endif // BOOST_GENERIC_DETAIL_CONCEPT_MAP_CONCEPT_AND_PARAMS_DETS_HPP
