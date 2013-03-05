
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

def data(max_size):
    s = ''
    for i in range(0, max_size + 1): # 0 and max_size included in range.
        s = s + '''
#define BOOST_CONTRACT_DETAIL_PP_IS_DIGIT_{0} (1) /* unary */ \
'''.format(i)
    return s

BOOST_PP_LIMIT_MAG = raw_input("BOOST_PP_LIMIT_MAG" +
        " (as in <boost/preprocessor/limits.hpp>) [256] = ")
if BOOST_PP_LIMIT_MAG == "": BOOST_PP_LIMIT_MAG = 256
else: BOOST_PP_LIMIT_MAG = int(BOOST_PP_LIMIT_MAG)

try: shutil.copyfile(header, header + ".bak")
except: pass
h = open(header, 'w')

h.write('''
/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used: #define BOOST_PP_LIMIT_MAG {0}

#ifndef BOOST_CONTRACT_DETAIL_PP_IS_DIGIT_HPP_
#define BOOST_CONTRACT_DETAIL_PP_IS_DIGIT_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>

#include <boost/preprocessor/limits.hpp>
#if BOOST_PP_LIMIT_MAG != {0}
#   error "Code generation used incorrect BOOST_PP_LIMIT_MAG"
#endif

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_IS_DIGIT(tokens) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \\
            BOOST_CONTRACT_DETAIL_PP_IS_DIGIT_)

// DATA //
{1}

#endif // #include guard

'''.format(BOOST_PP_LIMIT_MAG, data(BOOST_PP_LIMIT_MAG)))

h.close()
print "Generated:", header

