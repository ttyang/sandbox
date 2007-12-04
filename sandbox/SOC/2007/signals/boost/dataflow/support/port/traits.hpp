// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DATAFLOW_SUPPORT_PORT_TRAITS_HPP
#define BOOST_DATAFLOW_SUPPORT_PORT_TRAITS_HPP

#include <boost/dataflow/detail/enable_if_defined.hpp>
#include <boost/dataflow/support/port/category.hpp>
#include <boost/dataflow/support/tags.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace boost { namespace dataflow {

/// Convenience class for PortTraits types.
template<typename PortCategory, typename PortConcept=concepts::port,
    typename Tag=default_tag>
struct port_traits
{
    /// The PortCategory of the port.
    typedef PortCategory category;
    /// The PortConcept of the port.
    typedef PortConcept concept;
    /// The Tag of the port.
    typedef Tag tag;
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT(( is_port_category<PortCategory> ));
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT(( is_base_of<concepts::port, PortConcept> ));
};

namespace detail {
    struct enable_guard;
}

/// Boolean Metafunction determining whether a type is a PortTraits.
template<typename PortTraits, typename Enable=detail::enable_guard>
struct is_port_traits : public mpl::false_
{
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT(( is_same<Enable, detail::enable_guard> ));
};

/// INTERNAL ONLY
template<typename PortTraits>
struct is_port_traits<PortTraits,
    typename detail::enable_if_defined<
        detail::all_of<
            typename PortTraits::category,
            typename PortTraits::concept,
            typename PortTraits::tag
        >,
        detail::enable_guard
    >::type>
 : public mpl::true_
{
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT(( is_port_category<typename PortTraits::category> ));
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT((is_base_of<concepts::port, typename PortTraits::concept>));
};

/// Metafunction returning the PortTraits of a type.
template<typename T, typename Tag=default_tag, typename Enable=void>
struct port_traits_of
{
#ifdef DOXYGEN_DOCS_BUILD
    typedef detail::unspecified type; ///< PortTraits type.
#endif
};

/// INTERNAL ONLY
/** Specialization allowing intrusive specification of the PortTraits.
*/
template<typename T>
struct port_traits_of<
    T,
    typename T::port_traits::tag,
    typename enable_if<
        mpl::not_<mpl::is_sequence<typename T::port_traits> >
    >::type
>
{
    /// INTERNAL ONLY
    typedef typename T::port_traits type;
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT(( is_port_traits<type> ));
};

} }

// Specialization allowing intrusive specification of a sequence of PortTraits.
#include <boost/dataflow/support/port/detail/port_traits_sequence.hpp>

namespace boost { namespace dataflow {

/// Allows registration of PortTraits for all cv-qualified versions of a type.
template<typename T, typename Tag=default_tag, typename Enable=void>
struct register_port_traits
{};


// Specialization allowing non-intrusive specification of the PortTraits.

/// INTERNAL ONLY
template<typename T, typename Tag>
struct port_traits_of<
    T,
    Tag,
    typename detail::enable_if_defined<
        typename register_port_traits<
            typename remove_cv<T>::type,
            Tag
        >::type
    >::type
>
{
    /// INTERNAL ONLY
    typedef
        typename register_port_traits<
            typename remove_cv<T>::type,
            Tag
        >::type type;
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT(( is_port_traits<type> ));
};

} } // namespace boost::dataflow

/// Macro simplifying non-intrusive specification of a type's PortTraits.
#define DATAFLOW_PORT_TRAITS(Type,PortTraits)   \
namespace boost { namespace dataflow {          \
template<>                                      \
struct register_port_traits<                    \
    Type,                                       \
    PortTraits::tag>                            \
{                                               \
    typedef PortTraits type;                    \
    BOOST_MPL_ASSERT(( is_port_traits<type> )); \
};                                              \
}}

/// Macro simplifying non-intrusive specification of multiple types'
/// PortTraits, using a boost::enable_if condition.
#define DATAFLOW_PORT_TRAITS_ENABLE_IF(Type,Cond,PortTraits)    \
namespace boost { namespace dataflow {                          \
template<typename Type>                                         \
struct register_port_traits<                                    \
    Type,                                                       \
    PortTraits::tag,                                             \
    typename boost::enable_if< Cond >::type>                    \
{                                                               \
    typedef PortTraits type;                                    \
    BOOST_MPL_ASSERT(( is_port_traits<type> ));                 \
};                                                              \
}}

#endif // BOOST_DATAFLOW_SUPPORT_PORT_TRAITS_HPP
