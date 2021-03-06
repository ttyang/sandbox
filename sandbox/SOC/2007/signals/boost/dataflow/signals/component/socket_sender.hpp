// socket_sender.hpp

// Copyright Stjepan Rajko 2007. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef SIGNAL_NETWORK_SOCKET_SENDER_HPP
#define SIGNAL_NETWORK_SOCKET_SENDER_HPP

#include <boost/dataflow/signals/component/detail/unfused_inherited.hpp>
#include <boost/dataflow/signals/component/detail/serialize_fusion_vector.hpp>
#include <boost/dataflow/signals/component/filter.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/mpl/vector.hpp>
#include <sstream>

namespace boost { namespace signals {

namespace detail {

    template<typename Signature>
    class socket_sender_impl
    {
    public:
        /// Initializes the socket_sender to use the provided socket.
        socket_sender_impl(asio::ip::tcp::socket & socket) :
            socket(socket),
            stream(std::ios::in | std::ios::out | std::ios::binary)
        { }
        
        typedef void result_type;

        /// Serializes each of the arguments and sends them in a single packet through the socket.
        template <class Seq>
        void operator()(const Seq &vec_par)
        {
            boost::archive::binary_oarchive archive (stream);
            archive & vec_par;
            uint32_t packet_size=stream.str().size();
            boost::asio::write(socket, asio::buffer(&packet_size, 4)); 
            boost::asio::write(socket, asio::buffer(stream.str()),
                boost::asio::transfer_all());
            stream.str(empty_string);
        }
    private:
        asio::ip::tcp::socket &socket;
        std::stringstream stream;
        std::string empty_string;
    };
}
/** \brief Sends serializable signals through a Boost asio socket.
\param Signature Signature of the signal received (and sent through the socket).
\todo socket_sender only works for Signatures of return type void.
*/
template<typename Signature>
class socket_sender : public boost::fusion::unfused_inherited<
    detail::socket_sender_impl<Signature>, typename boost::function_types::parameter_types<Signature>::type >,
    public consumer<socket_sender<Signature> >
{
    typedef boost::fusion::unfused_inherited<
        detail::socket_sender_impl<Signature>,
        typename boost::function_types::parameter_types<Signature>::type>
        base_type;
public:
    socket_sender(asio::ip::tcp::socket & socket) : base_type(socket)
    { }
};

} } // namespace boost::signals

#endif
