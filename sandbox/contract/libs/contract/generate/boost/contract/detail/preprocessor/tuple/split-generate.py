
# Copyright (C) 2008-2013 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

import sys
import os
import shutil

# $ python <NAME>-generate.py [DIR]
header = sys.argv[0].replace("-generate.py", ".hpp", 1)
if(len(sys.argv) > 1): header = os.path.join(sys.argv[1], header)

def placeholders(start, stop):
    (s, comma) = ('', '')
    for i in range(start, stop):
        (s, comma) = (s + comma + '_' + str(i + 1), ', ')
    return s

def data(max_size):
    s = ''
    for size in range(1, max_size + 1):
        s = s + '''
#define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_{0}({1}) \\
    ({1}) , /* comma splits */ \
'''.format(size, placeholders(0, size))
    return s

BOOST_PP_LIMIT_TUPLE = raw_input("BOOST_PP_LIMIT_TUPLE" +
        " (as in <boost/preprocessor/limit.hpp>) [64] = ")
if BOOST_PP_LIMIT_TUPLE == "": BOOST_PP_LIMIT_TUPLE = 64
else: BOOST_PP_LIMIT_TUPLE = int(BOOST_PP_LIMIT_TUPLE)

try: shutil.copyfile(header, header + ".bak")
except: pass
h = open(header, 'w')

h.write('''
/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used: #define BOOST_PP_LIMIT_TUPLE {0}

#ifndef BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_HPP_

#include <boost/preprocessor/limits.hpp>
#if BOOST_PP_LIMIT_TUPLE != {0}
#   error "Code generation used incorrect BOOST_PP_LIMIT_TUPLE"
#endif

// PRIVATE //

// Own version of PP_CAT for reentrancy.
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#   define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_(a, b) \\
        BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_(a, b)
#else
#   define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_(a, b) \\
        BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_OO_((a, b))
#   define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_OO_(par) \\
        BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_ ## par
#endif
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#   define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_(a, b) \\
        a ## b
#else
#   define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_(a, b) \\
        BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_II_(~, a ## b)
#   define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_II_(p, res) \\
        res
#endif

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT(size) \\
    BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_( \\
            BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT_, size)

// DATA //
{1}

#endif // #include guard

'''.format(BOOST_PP_LIMIT_TUPLE, data(BOOST_PP_LIMIT_TUPLE)))

h.close()
print "Generated:", header

