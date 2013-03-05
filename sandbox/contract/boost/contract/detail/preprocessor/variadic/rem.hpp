
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_VARIADIC_REM_HPP_
#define BOOST_CONTRACT_DETAIL_PP_VARIADIC_REM_HPP_

// Do not use Boost.PP variadic because they use a different config macro.
#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_VARIADIC_REM(...) __VA_ARGS__

#endif

#endif // #include guard

