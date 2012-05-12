// Boost.TypeErasure library
//
// Copyright 2011 Steven Watanabe
//
// Distributed under the Boost Software License Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#include <boost/type_erasure/operators.hpp>
#include <typeinfo>

namespace mpl = boost::mpl;
using namespace boost::type_erasure;

//[concept_map1
/*`
    Sometimes it is useful to non-intrusively adapt a
    type to model a concept.  For example, suppose that
    we want to make `std::type_info` model __less_than_comparable.
    To do this, we simply specialize the concept definition.
*/
namespace boost {
namespace type_erasure {

template<>
struct less_than_comparable<std::type_info>
{
    static bool apply(const std::type_info& lhs, const std::type_info& rhs)
    { return lhs.before(rhs) != 0; }
};

}
}
//]

//[concept_map
//` (For the source of the examples in this section see
//` [@boost:/libs/type_erasure/example/concept_map.cpp concept_map.cpp])
//` [concept_map1]
//]
