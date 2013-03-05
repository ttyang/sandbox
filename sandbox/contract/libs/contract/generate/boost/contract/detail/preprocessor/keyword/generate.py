
# Copyright (C) 2008-2013 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

import sys
import os
import shutil

keywords = [
      ("", "and")
    , ("", "and_eq")
    , ("", "asm")
    , ("", "auto")
    , ("", "bitand")
    , ("", "bitor")
    , ("", "bool")
    , ("", "break")
    , ("", "case")
    , ("", "catch")
    , ("", "char")
    , ("", "class")
    , ("", "compl")
    , ("", "const")
    , ("", "const_cast")
    , ("", "continue")
    , ("", "default")
    , ("", "delete")
    , ("", "do")
    , ("", "double")
    , ("", "dynamic_cast")
    , ("", "else")
    , ("", "enum")
    , ("", "explicit")
    , ("", "export")
    , ("", "extern")
    , ("", "false")
    , ("", "float")
    , ("", "for")
    , ("", "friend")
    , ("", "goto")
    , ("", "if")
    , ("", "inline")
    , ("", "int")
    , ("", "long")
    , ("", "mutable")
    , ("", "namespace")
    , ("", "new")
    , ("", "not")
    , ("", "not_eq")
    , ("", "operator")
    , ("", "or")
    , ("", "or_eq")
    , ("", "private")
    , ("", "protected")
    , ("", "public")
    , ("", "register")
    , ("", "reinterpret_cast")
    , ("", "return")
    , ("", "short")
    , ("", "signed")
    , ("", "sizeof")
    , ("", "static")
    , ("", "static_cast")
    , ("", "struct")
    , ("", "switch")
    , ("", "template")
    , ("", "this")
    , ("", "throw")
    , ("", "true")
    , ("", "try")
    , ("", "typedef")
    , ("", "typeid")
    , ("", "typename")
    , ("", "union")
    , ("", "unsigned")
    , ("", "using")
    , ("", "virtual")
    , ("", "void")
    , ("", "volatile")
    , ("", "wchar_t")
    , ("", "while")
    , ("", "xor")
    , ("", "xor_eq")
    , ("cstddef", "ptrdiff_t")
    , ("cstddef", "size_t")
    , ("cxx11", "char16_t")
    , ("cxx11", "char32_t")
    , ("cxx11", "constexpr")
    , ("cxx11", "decltype")
    , ("cxx11", "final")
    , ("cxx11", "nullptr")
    , ("cxx11", "override")
    , ("cxx11", "static_assert")
    , ("cxx11/cstddef", "nullptr_t")
    , ("contract", "comma")
    , ("contract", "deduce")
    , ("contract", "extends")
    , ("contract", "in")
    , ("contract", "initialize")
    , ("contract", "out")
    , ("contract", "postcondition")
    , ("contract", "precondition")
    , ("contract", "requires")
]

for k in keywords:
    dir = k[0]
    keyword = k[1]
    
    # $ python generate.py [DIR]
    header = keyword + ".hpp"
    if(dir != ""): header = os.path.join(dir, header)
    if(len(sys.argv) > 1): header = os.path.join(sys.argv[1], header)

    try: shutil.copyfile(header, header + ".bak")
    except: pass
    h = open(header, 'w')

    h.write('''
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_IS_{1} (1) /* unary */
#define {1}_BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_REMOVE_{1} /* nothing */
#define {1}_BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_{0}_FRONT(tokens) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_{0}_BACK(token) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \\
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_REMOVE_FRONT(tokens) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_{0}_FRONT, \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_REMOVE_BACK(tokens) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_{0}_BACK, \\
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_ADD_FRONT(tokens) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_{0}_FRONT, {1})

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_{0}_ADD_BACK(tokens) \\
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \\
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_{0}_BACK, {1})

#endif // #include guard

'''.format(keyword.upper(), keyword))

    h.close()
    print "Generated:", header

