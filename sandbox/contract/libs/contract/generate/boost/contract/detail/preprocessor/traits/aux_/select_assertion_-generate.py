
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import shutil

CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS = raw_input(
        "CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS form " + 
        "<contract/limits.hpp> [5] = ")
if CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS == "":
    CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS = 5
else:
    CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS = int(
            CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS)

# 1 and CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS included in range.
for i in range(1, CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS + 1):
    header = sys.argv[0].replace("-generate.py", str(i) + ".hpp", 1)
    shutil.copyfile(header, header + ".bak")
    h = open(header, 'w')

    h.write('''
#ifndef CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_HPP_
#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead modify the generation script "<FILE>-generate.py" and run
// `$ python <FILE_NAME>-generate.py > FILE_NAME.hpp`.
// Used CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS: {2}

#include <contract/limits.hpp>
#if CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS != {2}
#error "Code generation used incorrect CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS"
#endif

#include <contract/detail/preprocessor/traits/aux_/assertion.hpp>
#include <contract/detail/preprocessor/traits/aux_/select_assertion.hpp>
#if {1} <= {2}
#   include <contract/detail/preprocessor/traits/aux_/select_assertion_{1}.hpp>
#endif
#include <contract/detail/preprocessor/keyword/contract/requires.hpp>
#include <contract/detail/preprocessor/keyword/if.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELEM_{0}_( \\
        d, number_instruction_requirements_traits, assertion) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_IF_FRONT(assertion), \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{1} \\
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_IS_STATEMENT( \\
            assertion), \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_STATEMENT \\
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT(assertion), \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_REQUIRES \\
    , /* else: bool, const, or static assert */ \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_CONDITION \\
    )))(d, assertion \\
        , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \\
        , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits) \\
        , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits) \\
        , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits) \\
    )

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_{0}_( \\
        d, select_assertions, number_instruction_requirements_traits) \\
    BOOST_PP_LIST_FOLD_LEFT_ ## d( \\
            CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELEM_{0}_, \\
            number_instruction_requirements_traits, select_assertions)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_(d, select_traits, \\
        prev_number, prev_instruction, prev_requirements, traits) \\
    /* 6th, append right-curly to end else block */ \\
    CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY(d \\
        /* 5th, append else-assertions */ \\
        , CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_{0}_(d \\
            , CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSES( \\
                    select_traits) \\
            /* 4th, append else-statement `else` */ \\
            , CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_ELSE(d \\
                /* 3rd, append right-curly to end if block */ \\
              ,CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY(\\
                    d \\
                    /* 2nd, append then-assertions */ \\
                    ,CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_{0}_(\\
                          d \\
                        ,CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_THENS(\\
                                select_traits) \\
                        /* 1st, append if-statement `if(...)` */ \\
  , CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_IF(d \\
      , CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_IF(select_traits) \\
      , (prev_number, prev_instruction, prev_requirements, traits) \\
                        ) \\
                    ) \\
                ) \\
            ) \\
        ) \\
    )

// PROTECTED //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}(d, assertion, \\
        prev_number, prev_instruction, prev_requirements, traits)\\
    CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND_TUPLE(d, \\
            CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_{0}_(d, \\
                    CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION(assertion),\\
                    prev_number, prev_instruction, prev_requirements, traits))

#endif // #include guard

'''.format(str(i), str(i + 1), str(CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS)))

    h.close()
    print "Written:", header

