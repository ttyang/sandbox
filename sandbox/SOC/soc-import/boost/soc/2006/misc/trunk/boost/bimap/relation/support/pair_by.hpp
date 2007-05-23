// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_by.hpp
/// \brief pair_by<member>(r) function

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/standard_relation_fwd.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/bimap/relation/support/pair_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>

#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/** \brief Gets a pair view of the relation.

\ingroup relation_group
                                                                        **/

template< class Tag, class Relation >
BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,Relation>::type
    pair_by( Relation & rel );

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {


// Since it is very error-prone to directly write the hole bunch
// of relation accesor. They are buil from litle macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and mantain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necesary but they help a lot to
// the reader, as they undercover what is the signature of the
// result code.
// In the end, it is not quicker to do it in this way because you
// write a lot. But this code has no complexity at all and almost
// every word writed is for documentation.

// Result of
// -------------------------------------------------------------------------
/*
    namespace result_of {

    template< class Tag, class Relation >
    struct pair_by<Tag,Relation>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of

*/

// TODO
// This works for Boost.Bimap but not for all the uses of Relation outside
// Boost.Bimap. For now it will stay as is, because if standard_relation is
// eliminated all the functions will be simplified.
// It cannot be used directly BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER here.

namespace result_of {

template< class Tag, class Relation >
struct pair_by
{
    typedef BOOST_DEDUCED_TYPENAME mpl::if_< is_const<Relation>,
    // {
           BOOST_DEDUCED_TYPENAME const_pair_reference_type_by< Tag,Relation >::type,
    // }
    // else
    // {
           BOOST_DEDUCED_TYPENAME pair_reference_type_by< Tag,Relation >::type
    // }
    >::type type;
};

} // namespace result_of


// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    pair_by,
    Relation,
    rel,
    return rel.get_left_pair(),
    return rel.get_right_pair()
);

// Interface
// --------------------------------------------------------------------------

template< class Tag, class Symmetric >
BOOST_DEDUCED_TYPENAME enable_if<
    ::boost::mpl::or_<
        is_standard_pair_view< Symmetric >,
        is_standard_relation_view< Symmetric >
    >,
BOOST_DEDUCED_TYPENAME result_of::pair_by< Tag, Symmetric >::type

>::type
pair_by( Symmetric s )
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
    member_with_tag
    <
        Tag, Symmetric

    >::type member_at_tag;

    return detail::pair_by(member_at_tag(),s);
}

template< class Tag, class Symmetric >
BOOST_DEDUCED_TYPENAME disable_if<
    ::boost::mpl::or_<
        is_standard_pair_view< Symmetric >,
        is_standard_relation_view< Symmetric >
    >,
BOOST_DEDUCED_TYPENAME result_of::pair_by< Tag, Symmetric >::type

>::type
pair_by( Symmetric & s )
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
    member_with_tag
    <
        Tag, Symmetric

    >::type member_at_tag;

    return detail::pair_by(member_at_tag(),s);
}

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP
