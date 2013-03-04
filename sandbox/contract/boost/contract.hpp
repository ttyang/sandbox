
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

#include <boost/contract/limits.hpp>
#include <boost/contract/config.hpp>

#include <boost/contract/broken.hpp>

#include <boost/contract/oldof.hpp>
#include <boost/contract/copy.hpp>

#include <boost/contract/class.hpp>
#include <boost/contract/class_invariant.hpp>

#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/body.hpp>

#include <boost/contract/block_invariant.hpp>
#include <boost/contract/loop_variant.hpp>

#include <boost/contract/parameter.hpp>

// NOTE: This header allows to use the alternative operator spelling `not`, etc
// so user code can write assertions starting with alphanumeric symbols as
// `not ...` instead of `! ...`. This header is NOT used by the library
// implementation, it is included here only to allow the operator keywords in
// the user contract code. This header is required on MSVC but it has no effect
// on C++ compliant compilers like GCC that correctly define `not`, etc.
#include <ciso646>

#endif // #include guard

