
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

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
        for index in range(1, size):
            s = s + '''
#define BOOST_CONTRACT_DETAIL_PP_ARRAY_REST_N_{0}_{1}({2}) \\
    ({3}, ({4})) \
'''.format(size, index, placeholders(0, size), str(size - index),
        placeholders(index, size))
    return s

BOOST_PP_LIMIT_TUPLE = raw_input("BOOST_PP_LIMIT_TUPLE" +
        " (as in <boost/preprocessor/limits.hpp>) [64] = ")
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

#ifndef BOOST_CONTRACT_DETAIL_PP_ARRAY_REST_N_HPP_
#define BOOST_CONTRACT_DETAIL_PP_ARRAY_REST_N_HPP_

#include <boost/preprocessor/limits.hpp>
#if BOOST_PP_LIMIT_TUPLE != {0}
#   error "Code generation used incorrect BOOST_PP_LIMIT_TUPLE"
#endif

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/array/data.hpp>

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_ARRAY_REST_N(n, array) \\
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_ARRAY_REST_N_, \\
            BOOST_PP_CAT(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_CAT(_, n))) \\
    BOOST_PP_ARRAY_DATA(array)

// DATA //
{1}

#endif // #include guard

'''.format(BOOST_PP_LIMIT_TUPLE, data(BOOST_PP_LIMIT_TUPLE)))

h.close()
print "Generated:", header

