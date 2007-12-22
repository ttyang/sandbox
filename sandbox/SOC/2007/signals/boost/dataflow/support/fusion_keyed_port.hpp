// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DATAFLOW_CONNECTION_PORT_MAP_HPP
#define BOOST_DATAFLOW_CONNECTION_PORT_MAP_HPP

#include <boost/dataflow/support/keyed_port.hpp>

#include <boost/call_traits.hpp>
//#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace dataflow {

namespace detail {
    struct get_pair_first
    {
        template<typename FArgs> struct result;
        
        template<typename F, typename First, typename Second>
        struct result<F(fusion::pair<First, Second>)>
        {
            typedef First type;
        };
    };
    struct get_pair_second_dereferenced
    {
        template<typename FArgs> struct result;
        
        template<typename F, typename First, typename Second>
        struct result<F(fusion::pair<First, Second>)>
        {
            typedef typename remove_reference<Second>::type type;
        };
    };
}

template<typename PortCategory, typename Map, typename Tag=default_tag>
struct fusion_keyed_port_traits
    : public keyed_port_traits<
        PortCategory,
        typename fusion::result_of::transform<
            typename fusion::result_of::as_vector<Map>::type,
            detail::get_pair_first
        >::type,
        typename fusion::result_of::transform<
            typename fusion::result_of::as_vector<Map>::type,
            detail::get_pair_second_dereferenced
        >::type,
        Tag>
{};

template<typename PortCategory, typename T, typename Tag=default_tag>
class fusion_keyed_port
{

public:
    typedef T map_type;
    
    fusion_keyed_port(const T& t) : t(t) {}
    map_type &map() const {return t;}
    
    typedef fusion_keyed_port_traits<PortCategory, T, Tag> dataflow_traits;

private:
    mutable map_type t;
};

namespace extension
{
    template<typename PortCategory, typename Map, typename Tag, typename KeyPortTraits>
    struct get_keyed_port_impl<fusion_keyed_port_traits<PortCategory, Map, Tag>, KeyPortTraits>
    {
        template<typename FArgs> struct result;
        
        template<typename F, typename KeyedPort>
        struct result<F(KeyedPort &)>
        {
            typedef typename boost::fusion::result_of::at_key<
                typename KeyedPort::map_type,
                KeyPortTraits
            >::type type;
        };

        template<typename KeyedPort>
        typename result<get_keyed_port_impl(KeyedPort &)>::type
            operator()(KeyedPort &port)
        {
            return boost::fusion::at_key<
                    KeyPortTraits
                >(port.map());
        }
    };
}
    
} } // namespace boost::dataflow

#endif // BOOST_DATAFLOW_CONNECTION_PORT_MAP_HPP


