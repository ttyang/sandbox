/* Boost test_or.inl header file
 *
 * Copyright 2007 Arseny Kapoulkine
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#define TEST_BITWISE_SMALL test_or_small
#define TEST_BITWISE_LARGE test_or_large
#define BITWISE_OP |

#include "impl_bitwise.inl"

#undef BITWISE_OP
#undef TEST_BITWISE_LARGE
#undef TEST_BITWISE_SMALL
