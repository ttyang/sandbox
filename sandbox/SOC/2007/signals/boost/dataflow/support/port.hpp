// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DATAFLOW_SUPPORT_PORT_HPP
#define BOOST_DATAFLOW_SUPPORT_PORT_HPP

#include <boost/dataflow/detail/enable_if_defined.hpp>
//#include <boost/dataflow/support/common.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace boost { namespace dataflow {

/// PortCategory types.
namespace ports
{
    struct producer;
    struct consumer;

    struct producer
    {
        typedef consumer complement;
    };

    struct consumer
    {
        typedef producer complement;
    };
}

/// Boolean metafunction determining whether a type is a PortCategory.
template<typename T, typename Enable=void>
struct is_port_category : public mpl::false_
{};

template<typename PortCategory>
struct is_port_category<
    PortCategory,
    typename detail::enable_if_defined<
        typename PortCategory::complement
    >::type>
 : public mpl::true_
{};

namespace concepts
{
    /// Tag
    struct producer;
    struct consumer;
}

/// Convenience class for PortTraits types.
template<typename Mechanism, typename PortCategory, typename PortConcept>
struct port_traits
{
    typedef Mechanism mechanism;
    typedef PortCategory category; 
    typedef PortConcept concept;
};

/// Boolean metafunction determining whether a type is a PortTraits.
template<typename PortTraits, typename Enable=void>
struct is_port_traits : public mpl::false_
{};

template<typename PortTraits>
struct is_port_traits<PortTraits,
    typename detail::enable_if_defined<
        detail::all_of<
            typename PortTraits::mechanism,
            typename PortTraits::category,
            typename PortTraits::concept
        >
    >::type>
 : public mpl::true_
{
    BOOST_MPL_ASSERT(( is_port_category<typename PortTraits::category> ));
};

/// Metafunction returning the PortTraits of a type.
template<typename Mechanism, typename PortCategory, typename T, typename Enable=void>
struct port_traits_of
{};

/// Specialization allowing intrusive specification of the PortTraits.
template<typename Mechanism, typename PortCategory, typename T>
struct port_traits_of<Mechanism, PortCategory, T,
    typename detail::enable_if_defined<
        typename T::template dataflow<Mechanism, PortCategory>::traits >::type
    >
{
    typedef typename T::template dataflow<Mechanism, PortCategory>::traits type;
    BOOST_MPL_ASSERT(( is_port_traits<type> ));
};

/// Boolean metafunction determining whether a type is a Port.
template<typename Mechanism, typename PortCategory, typename T, typename Enable=void>
struct is_port
    : public mpl::false_ {};

template<typename Mechanism, typename PortCategory, typename T>
struct is_port<Mechanism, PortCategory, T,
        typename detail::enable_if_defined<
            typename port_traits_of<
                Mechanism,
                PortCategory,
                typename remove_cv<T>::type
            >::type
        >::type >
    : public mpl::true_ {};

/// Convenience base class for Port types. 
template<typename PortTraits>
struct port
{
    template<typename Mechanism, typename PortCategory, typename Enable=void>
    struct dataflow;
    
    template<typename Mechanism, typename PortCategory>
    struct dataflow<
        Mechanism,
        PortCategory,
        typename boost::enable_if<
            mpl::and_<
                is_same<Mechanism, typename PortTraits::mechanism>,
                is_same<PortCategory, typename PortTraits::category>
            >
        >::type>
    {
        typedef PortTraits traits;
    };
};

// trait determining whether a type is a port proxy.
template<typename Mechanism, typename PortCategory, typename T, typename Enable=void>
struct is_proxy_port
    : public mpl::false_ {};

namespace extension
{
    template<typename Traits>
    struct get_port_impl
    {
        template<typename T>
        struct apply
        {
            typedef T & type;

            static type call(T &p)
            {
                BOOST_MPL_ASSERT(( is_port<typename Traits::mechanism, typename Traits::category, T> ));
                return p;
            }
        };
    };
}

template<typename Mechanism, typename PortCategory, typename T, typename Enable=void>
struct get_port_result_type;
/*{
    typedef T & type;
};*/

template<typename Mechanism, typename PortCategory, typename T>
struct get_port_result_type<
    Mechanism,
    PortCategory,
    T,
    typename disable_if<is_proxy_port<Mechanism, PortCategory, T> >::type>
{
    typedef
        typename
            extension::get_port_impl<
                typename port_traits_of<
                    Mechanism,
                    PortCategory,
                    typename remove_cv<T>::type
                >::type
            >::template apply<T>::type type;
};

template<typename Mechanism, typename PortCategory, typename T>
typename disable_if<
    is_proxy_port<Mechanism, PortCategory, T>,
    typename get_port_result_type<Mechanism, PortCategory, T>::type
>::type
get_port(T &p)
{
    return extension::get_port_impl<
            typename port_traits_of<Mechanism, PortCategory, T>::type
            >::template apply<T>::call(p);
}

/// Convenience class for Producer types for all Mechanisms. 
/*template<typename PortCategory, typename PortTag>
struct port<all_mechanisms, PortCategory, PortTag>
{
    template<typename M>
    struct dataflow
    {
        template<typename P, typename Enable=void>
        struct port
        {
        };
        
        template<typename P>
        struct port<P, typename boost::enable_if<is_same<P, PortCategory> >::type>
        {
            typedef PortTag category;
        };
    };
};*/

} } // namespace boost::dataflow

/// Macro simplifying non-intrusive specification of a type's PortTraits.
#define DATAFLOW_PORT_CATEGORY(Type,PortTraits) \
template<> \
struct port_traits_of< \
    PortTraits::mechanism, \
    PortTraits::category, \
    Type> \
{ \
    typedef PortTraits type; \
    BOOST_MPL_ASSERT(( is_port_traits<type> )); \
};

/// Macro simplifying non-intrusive specification of multiple types'
/// PortTraits, using a boost::enable_if condition.
#define DATAFLOW_PORT_CATEGORY_ENABLE_IF(Type,Cond,PortTraits) \
template<typename Type> \
struct port_traits_of< \
    typename PortTraits::mechanism, \
    typename PortTraits::category, \
    Type, \
    typename boost::enable_if< Cond >::type> \
{ \
    typedef PortTraits type; \
    BOOST_MPL_ASSERT(( is_port_traits<type> )); \
};

#endif // BOOST_DATAFLOW_SUPPORT_PORT_HPP
