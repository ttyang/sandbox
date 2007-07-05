// Copyright Stjepan Rajko 2007. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef SIGNAL_NETWORK_CONNECT_HPP
#define SIGNAL_NETWORK_CONNECT_HPP

namespace boost { namespace signals {

template<typename Input, typename Output, typename Enable=void>
struct connect_impl;
    
template<typename Input, typename Output>
void connect(Input &input, Output &output)
{
    connect_impl<Input, Output>()(input, output);
};
             
template<typename Input, typename Output>
void connect(Input &input, const Output &output)
{
    connect_impl<Input, Output>()(input, output);
};

template<typename Input, typename Output>
void connect(const Input &input, Output &output)
{
    connect_impl<Input, Output>()(input, output);
};

template<typename Input, typename Output>
void connect(const Input &input, const Output &output)
{
    connect_impl<Input, Output>()(input, output);
};

} } // namespace boost::signals

#endif // SIGNAL_NETWORK_CONNECT_HPP