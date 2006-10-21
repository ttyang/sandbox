// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/manage_bimap_key.hpp
/// \brief Utility class to manage the set types of a bimap.

#ifndef BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP
#define BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP


// Boost.Bimap.Tags
#include <boost/bimap/tags/support/default_tagged.hpp>
#include <boost/bimap/tags/support/apply_to_value_type.hpp>

// Boost.MPL
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/bimap/detail/is_set_type_of.hpp>

#include <boost/bimap/set_of.hpp>


namespace boost {
namespace bimap {
namespace detail {

// In detail, we are free to import same namespaces to augment the
// readability of the code. No one is supposed to use this namespace.

/** \struct boost::bimap::detail::manage_bimap_key
\brief Metafunction to manage the set types of a bimap.

\code
template< class SetType, class DefaultTag >
struct manage_bimap_key
{
    typedef {TaggedSetType} type;
}
\endcode

If KeyType is not tagged, DefaultTag is used. If KeyType is not a SetOfType
specification it is converted to set_of< value_type_of<KeyType>::type > and the
it is tagged with his tag or the default one.

See also bimap, bimap_core.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class SetType, class DefaultTag >
struct manage_bimap_key
{
    // First, convert the type to a tagged one with the default tag

    typedef typename tags::support::default_tagged
    <
        SetType, DefaultTag

    >::type tagged_set_type;

    // Then manage plain key types, were the set type of the collection
    // is not specified in the instantiation

    typedef typename

       mpl::if_< typename is_set_type_of< typename tagged_set_type::value_type >::type,
    // {
            // The type is
            tagged_set_type,
    // }
    // else
    // {
            // Default it to a set
            typename tags::support::apply_to_value_type
            <
                set_of< mpl::_ >,
                tagged_set_type

            >::type
    // }

    >::type type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP


