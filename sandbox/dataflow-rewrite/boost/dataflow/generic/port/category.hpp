// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST__DATAFLOW__GENERIC__PORT__CATEGORY_HPP
#define BOOST__DATAFLOW__GENERIC__PORT__CATEGORY_HPP


#include <boost/dataflow/utility/enable_if_type.hpp>
#include <boost/mpl/bool.hpp>


namespace boost { namespace dataflow {

/// PortCategory types.
namespace ports
{
    struct producer;
    struct consumer;

    /// producer PortCategory.
    struct producer
    {
        typedef consumer complement; ///< complement PortCategory type.
    };

    /// consumer PortCategory.
    struct consumer
    {
        typedef producer complement; ///< complement PortCategory type.
    };

    /// consumer PortCategory.
    struct producer_consumer
    {
        typedef producer_consumer complement; ///< complement PortCategory type.
    };
}

/// Boolean Metafunction determining whether a type is a PortCategory.
/** is_port_category<T> is an Integral Constant of type bool.
    It evaluates to true if T models PortCategory, false otherwise.
*/
template<typename T, typename Enable=void>
struct is_port_category : public mpl::false_
{
#ifdef DOXYGEN_DOCS_BUILD
    /// Integral Constant value type
    typedef bool value_type;
    /// true if T models PortCategory, false otherwise.
    typedef detail::unspecified value;
    /// Integral Constant
    typedef detail::unspecified type;
#endif
};

/// INTERNAL ONLY
template<typename PortCategory>
struct is_port_category<
    PortCategory,
    typename utility::enable_if_type<
        typename PortCategory::complement
    >::type>
 : public mpl::true_
{};

} } // namespace boost::dataflow


#endif // BOOST__DATAFLOW__GENERIC__PORT__CATEGORY_HPP
