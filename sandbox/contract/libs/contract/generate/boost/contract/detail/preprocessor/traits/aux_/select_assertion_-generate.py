
# Copyright (C) 2008-2013 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

import sys
import os
import shutil

BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS = raw_input(
        "BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS (as in " + 
        "<boost/contract/limits.hpp>) [5] = ")
if BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS == "":
    BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS = 5
else:
    BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS = int(
            BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS)

# 1 and BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS included in range.
for i in range(1, BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS + 1):
    # $ python <NAME>-generate.py [DIR]
    header = sys.argv[0].replace("-generate.py", str(i) + ".hpp", 1)
    if(len(sys.argv) > 1): header = os.path.join(sys.argv[1], header)

    try: shutil.copyfile(header, header + ".bak")
    except: pass
    h = open(header, 'w')

    h.write('''
/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS: {2}

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_HPP_

#include <boost/contract/limits.hpp>
#if BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS != {2}
#   error "Code generation used incorrect BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS"
#endif

#include <boost/contract/detail/preprocessor/traits/aux_/assertion.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/select_assertion.hpp>
#if {1} <= {2}
#   include <boost/contract/detail/preprocessor/traits/aux_/select_assertion_{1}.hpp>
#endif
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/contract/detail/preprocessor/keyword/if.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELEM_{0}_( \\
        d, number_instruction_requirements_traits, assertion) \\
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IF_FRONT(assertion), \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{1} \\
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_IS_STATEMENT(\\
            assertion), \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_STATEMENT \\
    , BOOST_PP_IIF( \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT(assertion), \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_REQUIRES \\
    , /* else: bool, const, or static assert */ \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_CONDITION \\
    )))(d, assertion \\
        , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \\
        , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits) \\
        , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits) \\
        , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits) \\
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_{0}_( \\
        d, select_assertions, number_instruction_requirements_traits) \\
    BOOST_PP_LIST_FOLD_LEFT_ ## d( \\
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELEM_{0}_, \\
            number_instruction_requirements_traits, select_assertions)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_( \\
        d, select_traits, prev_number, prev_instruction, prev_requirements, \\
        traits) \\
    /* 6th, append right-curly to end else block */ \\
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY(d \\
    /* 5th, append else-assertions */ \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_{0}_(d, \\
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSES( \\
                    select_traits) \\
    /* 4th, append else-statement `else` */ \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_ELSE(d \\
    /* 3rd, append right-curly to end if block */ \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY(d \\
    /* 2nd, append then-assertions */ \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_{0}_(d \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_THENS(select_traits) \\
    /* 1st, append if-statement `if(...)` */ \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_IF(d \\
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_IF(select_traits) \\
  , (prev_number, prev_instruction, prev_requirements, traits) \\
  ) ) ) ) ) )

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}( \\
        d, assertion, prev_number, prev_instruction, prev_requirements, \\
        traits) \\
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND_TUPLE(d, \\
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_(d, \\
                    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION( \\
                            assertion),\\
                    prev_number, prev_instruction, prev_requirements, traits))

#endif // #include guard

'''.format(str(i), str(i + 1), str(
        BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS)))

    h.close()
    print "Generated:", header

