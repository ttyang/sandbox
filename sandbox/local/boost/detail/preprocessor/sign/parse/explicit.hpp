
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the
// Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_DETAIL_PP_SIGN_PARSE_EXPLICIT_HPP_
#define BOOST_DETAIL_PP_SIGN_PARSE_EXPLICIT_HPP_

#include "../aux_/parse/opt.hpp"
#include "../aux_/parse/not.hpp"
#include <boost/detail/preprocessor/keyword/is_explicit.hpp>

#define BOOST_DETAIL_PP_SIGN_PARSE_EXPLICIT_OPT(seq_sign_err) \
    BOOST_DETAIL_PP_SIGN_AUX_PARSE_OPT(seq_sign_err, \
            BOOST_DETAIL_PP_KEYWORD_IS_EXPLICIT)

#define BOOST_DETAIL_PP_SIGN_PARSE_EXPLICIT_NOT(seq_sign_err) \
    BOOST_DETAIL_PP_SIGN_AUX_PARSE_NOT(seq_sign_err, \
            BOOST_DETAIL_PP_KEYWORD_IS_EXPLICIT, \
            ERROR_unexpected_explicit_specifier)

#endif // #include guard
