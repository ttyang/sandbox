// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/list_map_adaptor.hpp
/// \brief Container adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>

#include <boost/bimap/container_adaptor/list_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/detail/key_extractor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/if.hpp>

namespace boost {
namespace bimap {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator, class ReverseIterator, class ConstReverseIterator,
    class IteratorToBaseConverter, class IteratorFromBaseConverter, class ReverseIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter, class KeyFromBaseValueConverter,
    class FunctorsFromDerivedClasses
>
struct list_map_adaptor_base
{
    typedef list_adaptor
    <
        Base,

        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,

        ReverseIteratorFromBaseConverter,

        ValueToBaseConverter, ValueFromBaseConverter,

        typename mpl::push_front<

            FunctorsFromDerivedClasses,

            typename mpl::if_< ::boost::mpl::is_na<KeyFromBaseValueConverter>,
            // {
                    detail::key_from_pair_extractor< typename Iterator::value_type >,
            // }
            // else
            // {
                    KeyFromBaseValueConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Container adaptor to easily build a list map container

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
    class KeyFromBaseValueConverter        = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class list_map_adaptor :

    public list_map_adaptor_base
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyFromBaseValueConverter,
        FunctorsFromDerivedClasses

    >::type
{
    typedef typename list_map_adaptor_base
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyFromBaseValueConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef typename Iterator::value_type::first_type  key_type;
    typedef typename Iterator::value_type::second_type data_type;

    protected:

    typedef typename mpl::if_< ::boost::mpl::is_na<KeyFromBaseValueConverter>,
    // {
            detail::key_from_pair_extractor< typename Iterator::value_type >,
    // }
    // else
    // {
            KeyFromBaseValueConverter
    // }

    >::type key_from_base_value;

    // Access -----------------------------------------------------------------

    public:

    explicit list_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef list_map_adaptor list_map_adaptor_;

    // Functions -------------------------------------------------------------

    public:

    // The following functions are overwritten in order to work 
    // with key_type instead of value_type

    template<typename Predicate>
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimap::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                typename Base::value_type,
                key_from_base_value

            >( pred, this->template functor<key_from_base_value>() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimap::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<key_type>,
                typename Base::value_type,
                key_from_base_value

            >(
                std::equal_to<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        this->base().unique(
            ::boost::bimap::container_adaptor::detail::comparison_adaptor
            <
                BinaryPredicate,
                typename Base::value_type,
                key_from_base_value

            >( binary_pred, this->template functor<key_from_base_value>() )
        );
    }

    void merge(list_map_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimap::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                typename Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }

    template <typename Compare>
    void merge(list_map_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimap::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                typename Base::value_type,
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimap::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                typename Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }

    template <typename Compare>
    void sort(Compare comp)
    {
        this->base().sort(
            ::boost::bimap::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                typename Base::value_type,
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

};


} // namespace container_adaptor
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP

