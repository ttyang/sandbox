
#ifndef BOOST_LOCAL_AUX_PP_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_HPP_
#define BOOST_LOCAL_AUX_PP_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_HPP_

#include "../../../keyword/const_bind.hpp"
#include "../../../keyword/bind.hpp"
#include <boost/detail/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>

// Private API.

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_UNBIND_( \
        elem) \
    BOOST_PP_NOT(BOOST_PP_BITOR( \
          BOOST_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(elem) \
        , BOOST_PP_BITOR( \
            BOOST_LOCAL_AUX_PP_KEYWORD_IS_CONST_BIND_FRONT(elem) \
            , BOOST_LOCAL_AUX_PP_KEYWORD_IS_BIND_FRONT(elem) \
        ) \
    ))

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_PREV_( \
        params_seq, index, error) \
    BOOST_PP_IIF( \
        BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_UNBIND_(\
                BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(index), params_seq)), \
        error /* no err, fwd existing one if any */ \
    , \
        BOOST_PP_CAT(BOOST_PP_CAT(ERROR_default_value_at_element_, \
                BOOST_PP_INC(index)), _must_follow_an_unbound_parameter) \
        BOOST_PP_EMPTY /* because error might not be present */ \
    )

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_INDEX_( \
        params_seq, index, error) \
    BOOST_PP_IF(index, /* can't use IIF because index can be any number */ \
        BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_PREV_ \
    , \
        ERROR_default_value_cannot_be_specified_as_the_first_element \
        BOOST_PP_EMPTY /* because error might not be present */ \
        BOOST_PP_TUPLE_EAT(3) \
    )(params_seq, index, error)

// Private: While's operation.

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_OP_DATA_( \
        params_seq, index, error) \
    ( \
        params_seq \
    , \
        BOOST_PP_INC(index) \
    , \
        BOOST_PP_IIF(BOOST_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT( \
                BOOST_PP_SEQ_ELEM(index, params_seq)), \
            BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_INDEX_ \
        , \
            error BOOST_PP_TUPLE_EAT(3) /* no err, fwd existing one if any */\
        )(params_seq, index, error) \
    )

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_OP_(d, \
        params_index_error) \
    BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_OP_DATA_( \
            BOOST_PP_TUPLE_ELEM(3, 0, params_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 1, params_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 2, params_index_error))

// Private: While's predicate.

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_PRED_DATA_( \
        params_seq, index, error) \
    BOOST_PP_BITAND( \
          BOOST_PP_IS_EMPTY(error (/* expand empty */) ) \
        , BOOST_PP_LESS(index, BOOST_PP_SEQ_SIZE(params_seq)) \
    )

#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_PRED_(d, \
        params_index_error) \
    BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_PRED_DATA_( \
            BOOST_PP_TUPLE_ELEM(3, 0, params_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 1, params_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 2, params_index_error))

// Public API.

// Validate parameter sequence's default values: `default ...` cannot be 1st
// element and it must follow an unbind param.
// Expand to `EMPTY` if no error, or `ERROR_message EMPTY` if error.
#define BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS( \
        params_seq) \
    BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE( \
            BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_PRED_, \
            BOOST_LOCAL_AUX_PP_SIGN_PARSE_PARAMS_SEQ_VALIDATE_DEFAULTS_OP_, \
            (params_seq, 0, BOOST_PP_EMPTY)))

#endif // #include guard

