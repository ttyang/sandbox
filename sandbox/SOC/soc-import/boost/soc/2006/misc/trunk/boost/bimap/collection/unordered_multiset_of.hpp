// Boost.bimap
//
// Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/bimap for library home page.

/// \file collection/unordered_multiset_of.hpp
/// \brief Include support for unordered_multiset constrains for the bimap container

#ifndef BOOST_BIMAP_COLLECTION_UNORDERED_MULTISET_OF_HPP
#define BOOST_BIMAP_COLLECTION_UNORDERED_MULTISET_OF_HPP

#include <functional>
#include <boost/functional/hash.hpp>

#include <boost/bimap/collection/detail/is_key_type_of_builder.hpp>
#include <boost/bimap/collection/detail/register_key_type.hpp>
#include <boost/bimap/collection/detail/view_binder.hpp>
#include <boost/bimap/collection/detail/generate_relation_binder.hpp>
#include <boost/bimap/collection/key_type_of_tag.hpp>

#include <boost/multi_index/hashed_index.hpp>

#include <boost/bimap/views/unordered_multimap_view.hpp>
#include <boost/bimap/views/unordered_multiset_view.hpp>

namespace boost {
namespace bimap {
namespace collection {

/// \brief Set Type Specification
/**
This struct is used to specify an unordered_multiset specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an tr1::unordered_multiset instantiation,
except that the allocator can not be specified. The rationale behind
this difference is that the allocator is not part of the
unordered_multiset type specification, rather it is a container
configuration parameter.
The first parameter is the type of the objects in the set, the
second one is a Hash Functor that takes objects of this type, and
the third one is a Functor that compares them for equality.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_key_type_of< unordered_multiset_of<Type> >::value );

BOOST_STATIC_ASSERT
(
     is_same
     <
        compute_index_type
        <
            unordered_multiset_of<Type,HashFunctor,EqualKey>,
            KeyExtractor,
            Tag

        >::type
        ,
        hashed_nonunique< tag<Tag>, KeyExtractor, HashFunctor, EqualKey >

    >::value
);

typedef bimap
<
    unordered_multiset_of<Type>, RightKeyType

> bimap_with_left_type_as_unordered_multiset;

BOOST_STATIC_ASSERT
(
    is_same
    <
        compute_map_view_type
        <
            member_at::left,
            bimap_with_left_type_as_unordered_multiset

        >::type,

        unordered_multimap_view
        <
            member_at::left,
            bimap_with_left_type_as_unordered_multiset
        >

    >::value
);

\endcode

See also unordered_multiset_of_relation, is_unordered_multiset_of,
compute_index_type, compute_map_view_type, compute_set_type_view.
                                                                        **/

template
<
    class KeyType,
    class HashFunctor   = hash< KeyType >,
    class EqualKey      = std::equal_to< KeyType >
>
struct unordered_multiset_of : public key_type_of_tag
{
    /// The type that will be stored in the container
    typedef KeyType         value_type;

    /// Hash Functor that takes value_type objects
    typedef HashFunctor     hasher;

    /// Functor that compare two value_type objects for equality
    typedef EqualKey        key_equal;
};

BOOST_BIMAP_IS_KEY_TYPE_OF_BUILDER_2CP
(
    // template< class Type > class
    is_unordered_multiset_of,
    // evaluates to true if type is a
    unordered_multiset_of
);


BOOST_BIMAP_REGISTER_KEY_TYPE_2CP
(
    support::is_unordered_multiset_of, /* --------> */  multi_index::hashed_non_unique,
    KeyType,
    typename KeyType::hasher,
    typename KeyType::key_equal
);

BOOST_BIMAP_COLLECTION_TO_MAP_VIEW_TYPE
(
    is_unordered_multiset_of, /* binds to */ views::unordered_multimap_view
);

BOOST_BIMAP_COLLECTION_TO_SET_VIEW_TYPE
(
    is_unordered_multiset_of, /* binds to */ views::unordered_multiset_view
);

/// \brief Set Of Relation Specification
/**
This struct is similar to unordered_multiset_of but it is bind logically
to a relation. It is used in the bimap instantiation to specify the
desired type of the main view. This struct implements internally
a metafunction named bind_to that manages the quite complicated
task of finding the right type of the set for the relation.

\code
template<class Relation,class DefaultKeyCompare = use_default >
struct bind_to
{
    typedef -UNDEFINED- type;
};
\endcode

See also unordered_multiset_of, is_set_type_of_relation.
                                                                **/

template
<
    class HashFunctor   = use_default,
    class EqualKey      = use_default
>
struct unordered_multiset_of_relation : public set_type_of_relation_tag
{
    /// Hash Functor that takes value_type objects
    typedef HashFunctor     hasher;

    /// Functor that compare two value_type objects for equality
    typedef EqualKey        key_equal;

    /*
        template<class Relation,class HashFunctor = use_default, class EqualKey = use_default >
        struct bind_to
        {
            typedef -UNDEFINED- type;
        }
    */
    BOOST_BIMAP_GENERATE_RELATION_BINDER_2CP(unordered_multiset_of,HashFunctor,EqualKey);
};


} // namespace collection
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_COLLECTION_UNORDERED_MULTISET_OF_HPP

