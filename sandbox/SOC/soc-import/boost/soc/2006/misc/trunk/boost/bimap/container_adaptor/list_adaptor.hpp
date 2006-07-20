// Boost.bimap
//
// Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/bimap for library home page.

/// \file container_adaptor/list_adaptor.hpp
/// \brief Container adaptor to easily build a std::list signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_ADAPTOR_HPP

#include <boost/bimap/container_adaptor/detail/sequence_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>

namespace boost {
namespace bimap {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::list signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = use_default,
    class IteratorFromBaseConverter        = use_default,
    class ReverseIteratorFromBaseConverter = use_default,
    class ValueToBaseConverter             = use_default,
    class ValueFromBaseConverter           = use_default,

    class FunctorsFromDerivedClasses = mpl::list<>
>
class list_adaptor :

    public detail::sequence_container_adaptor
    <
        Base,

        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,

        FunctorsFromDerivedClasses
    >
{
    typedef list_adaptor this_type;

    // Access -----------------------------------------------------------------

    public:

    list_adaptor() {}

    explicit list_adaptor(Base & c) :
        list_adaptor::sequence_container_adaptor_(c) {}

    protected:

    typedef list_adaptor
    <
        Base,

        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,

        FunctorsFromDerivedClasses

    > list_adaptor_;

    // Interface -------------------------------------------------------------

    public:

    // TODO This require some work... later...
    /*

    void splice(iterator position,index class name& x)
    {

    }

    void splice(iterator position,index class name& x,iterator i)
    {

    }

    void splice(
        iterator position,index class name& x,iterator first,iterator last)
    {

    }

    */

    void remove(const typename this_type::value_type& value)
    {
        this_type::base().remove(
            this_type::template functor<typename this_type::value_to_base>()(value)
        );
    }

    template<typename Predicate>
    void remove_if(Predicate pred)
    {
        this_type::base().remove_if(
            detail::comparison_adaptor
            <
                Predicate,
                typename Base::value_type,
                typename this_type::value_to_base

            >( pred, this_type::template functor<typename this_type::value_to_base>() )
        );
    }

    void unique()
    {
        this_type::base().unique();
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        this_type::base().unique(
            detail::comparison_adaptor
            <
                BinaryPredicate,
                typename Base::value_type,
                typename this_type::value_to_base

            >( binary_pred, this_type::template functor<typename this_type::value_to_base>() )
        );
    }

    // TODO This require some work... later...
    /*

    void merge(index class name& x)
    {

    }

    template <typename Compare>
    void merge(index class name& x,Compare comp)
    {

    }

    */

    void sort()
    {
        this_type::base().sort();
    }

    template <typename Compare>
    void sort(Compare comp)
    {
        this_type::base().sort(
            detail::comparison_adaptor
            <
                Compare,
                typename Base::value_type,
                typename this_type::value_to_base

            >( comp, this_type::template functor<typename this_type::value_to_base>() )
        );
    }

    void reverse()
    {
        this_type::base().reverse();
    }

};



/* TODO
// Tests two maps for equality.
template<class BimapType, class Tag>
bool operator==(const map_view<BimapType,Tag>&, const map_view<BimapType,Tag>&)
{
}

// Lexicographical comparison.
template<class BimapType, class Tag>
bool operator<(const map_view<BimapType,Tag>&, const map_view<BimapType,Tag>&)
{
}
*/




} // namespace container_adaptor
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP


