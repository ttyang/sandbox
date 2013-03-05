
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_DEBUG_HPP_
#define BOOST_CONTRACT_AUX_DEBUG_HPP_

#include <boost/contract/aux_/config.hpp>

#if BOOST_CONTRACT_AUX_CONFIG_DEBUG_01

#include <boost/preprocessor/stringize.hpp>
#include <typeinfo>
#include <sstream>
#include <iostream>

// IMPORTANT: In order to remove *any* logging overhead when debug
// is turned off, *all* code used to generate the debug message must
// be passed as the 'code' param of the macro below (because that
// code is executed by the macro expansion only when debug is on).
#define BOOST_CONTRACT_AUX_DEBUG(file, line, code) \
    { \
        std::ostringstream dbg; /* decl special stream named `dbg` */ \
        { code; } /* code shall set dbg stream, etc */ \
        std::clog << file << ":" << line << " " << dbg.str() << std::endl; \
    }

#define BOOST_CONTRACT_AUX_DEBUGN(file, line, name, code) \
    BOOST_CONTRACT_AUX_DEBUG(file, line, \
        dbg << "[" << BOOST_PP_STRINGIZE(name) << "] "; \
        code; \
    )

#define BOOST_CONTRACT_AUX_DEBUGT(file, line, type, code) \
    BOOST_CONTRACT_AUX_DEBUG(file, line, \
        dbg << "[" << typeid(type).name() << "] "; \
        code; \
    )

#else // debug

#define BOOST_CONTRACT_AUX_DEBUG(file, line, code) /* nothing */
#define BOOST_CONTRACT_AUX_DEBUGN(file, line, name, code) /* nothing */
#define BOOST_CONTRACT_AUX_DEBUGT(file, line, type, code) /* nothing */

#endif // debug

#endif // #include guard

