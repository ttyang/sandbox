// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimap {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::multiset signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class multiset_adaptor :

    public ::boost::bimap::container_adaptor::ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        typename Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimap::container_adaptor::ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        typename Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multiset_adaptor multiset_adaptor_;

};


} // namespace container_adaptor
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP

