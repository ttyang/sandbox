// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// This code may be used under either of the following two licences:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE. OF SUCH DAMAGE.
//
// Or:
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file list_of.hpp
/// \brief Include support for list constrains for the bimap container

#ifndef BOOST_BIMAP_LIST_OF_HPP
#define BOOST_BIMAP_LIST_OF_HPP

#ifdef BOOST_BIMAP_DISABLE_SERIALIZATION
    #define BOOST_MULTI_INDEX_DISABLE_SERIALIZATION
#endif

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/multi_index/sequenced_index.hpp>

#include <boost/bimap/views/list_map_view.hpp>
#include <boost/bimap/views/list_set_view.hpp>

namespace boost {
namespace bimap {


/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::list instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< list_of<Type> >::value );

BOOST_STATIC_ASSERT
(
     is_same
     <
        list_of<Type>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        sequenced< tag<Tag>, KeyExtractor >

    >::value
);

typedef bimap
<
    list_of<Type>, RightKeyType

> bimap_with_left_type_as_list;

BOOST_STATIC_ASSERT
(
    is_same
    <
        list_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_list

        >::type,
        list_map_view< member_at::left, bimap_with_left_type_as_list >

    >::value
);

\endcode

See also list_of_relation.
                                                                        **/

template< class Type >
struct list_of : public ::boost::bimap::detail::set_type_of_tag
{
    /// Type of the object that will be stored in the list
    typedef Type value_type;

    BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(

        // binds to
        multi_index::sequenced
    );

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::list_map_view
    );

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::list_set_view
    );

};


/// \brief List Of Relation Specification
/**
This struct is similar to list_of but it is bind logically to a
relation. It is used in the bimap instantiation to specify the
desired type of the main view. This struct implements internally
a metafunction named bind_to that manages the quite complicated
task of finding the right type of the set for the relation.

\code
template<class Relation>
struct bind_to
{
    typedef -unspecified- type;
};
\endcode

See also list_of, is_set_type_of_relation.
                                                                **/

struct list_of_relation : public ::boost::bimap::detail::set_type_of_relation_tag
{
    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        list_of
    );
};


} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_LIST_OF_HPP

