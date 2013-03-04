
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import os
import shutil

iterations = raw_input("Maximum number of iterations [1] = ")
if iterations == "": iterations = 1
else: iterations = int(iterations)

for i in range(0, iterations + 1): # 0 and iterations included in range.
    if i == 0: p = ''
    else: p = '_' + str(i)

    # $ python <NAME>-generate.py [DIR]
    header = sys.argv[0].replace("-generate.py", p + ".hpp", 1)
    if(len(sys.argv) > 1): header = os.path.join(sys.argv[1], header)
    
    try: shutil.copyfile(header, header + ".bak")
    except: pass
    h = open(header, 'w')

    h.write('''
/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used maximum number of iterations: {1}

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY{0}_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY{0}_HPP_

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// From BOOST_PP_ARRAY_PUSH_BACK.
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK{0}_( \\
            array, elem) \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_I_( \\
                BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
#else
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK{0}_( \\
            array, elem) \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_D{0}_(array, elem)
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_D{0}_( \\
            array, elem) \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_I_( \\
                BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
#endif
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_I{0}_( \\
        size, data, elem) \\
    ( \\
        BOOST_PP_INC(size) \\
    , \\
        (BOOST_PP_TUPLE_REM(size) data BOOST_PP_COMMA_IF(size) elem) \\
    )

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT{0}( \\
        traits_sign, trait_macro, sign_macro) \\
    ( \\
        ( 1 /* create 1-array */, ( trait_macro( \\
          BOOST_PP_TUPLE_ELEM(2, 1, traits_sign)) ) ) \\
    , \\
        sign_macro(BOOST_PP_TUPLE_ELEM(2, 1, traits_sign)) \\
    )

// Expand to next `traits_sign` applying `trait_macro(sign)` and
// `sign_macro(macro)`.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY{0}( \\
        traits_sign, trait_macro, sign_macro) \\
    ( \\
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK{0}_( \\
                BOOST_PP_TUPLE_ELEM(2, 0, traits_sign), \\
                trait_macro(BOOST_PP_TUPLE_ELEM(2, 1, traits_sign))) \\
    , \\
        sign_macro(BOOST_PP_TUPLE_ELEM(2, 1, traits_sign)) \\
    )

#endif // #include guard

'''.format(p, iterations))

    h.close()
    print "Generated:", header

