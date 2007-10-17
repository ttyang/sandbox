// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DATAFLOW_CONNECTION_PORT_MAP_HPP
#define BOOST_DATAFLOW_CONNECTION_PORT_MAP_HPP

#include <boost/dataflow/support/keyed_port.hpp>

//#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace dataflow {

template<typename Mechanism, typename PortCategory>
struct fusion_map_port
    : public port_traits<Mechanism, PortCategory, concepts::keyed_port> {};

template<typename Mechanism, typename PortCategory, typename T>
class port_map
    : public port<fusion_map_port<Mechanism, PortCategory> >
{
public:
    typedef Mechanism mechanism_type;
    typedef PortCategory port_category_type;
    typedef T map_type;
    
    port_map(const T& t) : t(t) {}
    const map_type &map() const {return t;}
    
private:
    map_type t;

public:

/*    template<typename PT>
    struct dataflow<Mechanism, PT, typename enable_if<is_same<PT, typename PortCategory::complement> >::type >
    {
//                typedef typename boost::fusion::result_of::value_at_c<T, 0>::type::second_type
//        proxy_consumer_for;
        typedef
            typename boost::remove_const<
                typename boost::remove_reference<
                    typename boost::fusion::result_of::front<T>::type
                >::type
            >::type::second_type proxy_consumer_for;

        typedef mutable_proxy_port<Mechanism, typename PortCategory::complement, proxy_consumer_for> proxy_port_traits;
        static typename get_port_result_type<Mechanism, typename PortCategory::complement, proxy_consumer_for>::type
        get_proxied_port(const port_map &map)
        {
            return get_port<typename PortCategory::complement>(boost::fusion::front(map.t).second);
        }
    };*/
};

namespace extension
{
    template<typename Mechanism, typename PortCategory, typename KeyTag>
    struct get_keyed_port_impl<Mechanism, fusion_map_port<Mechanism, PortCategory>, KeyTag>
    {
        template<typename KeyedPort, typename Key>
        struct apply
        {
            typedef typename boost::fusion::result_of::at_key<
                        typename KeyedPort::map_type,
                        KeyTag
                    >::type type;

            static type
            call(KeyedPort &port, Key &)
            {
                return boost::fusion::at_key<
                        KeyTag
                    >(port.map());
            }
        };
    };
}
    
} } // namespace boost::dataflow

#endif // BOOST_DATAFLOW_CONNECTION_PORT_MAP_HPP


