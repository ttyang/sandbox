// format_write.hpp

// Boost Logging library
//
// Author: John Torjo, www.torjo.com
//
// Copyright (C) 2007 John Torjo (see www.torjo.com for email)
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
// See http://www.torjo.com/log2/ for more details


#ifndef JT28092007_format_write_HPP_DEFINED
#define JT28092007_format_write_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/logging/detail/fwd.hpp>

namespace boost { namespace logging {

/** 
@brief Classes that write the message, once it's been @ref gather "gathered".

The most important class is writer::format_write

*/
namespace writer {

/** 
@brief Allows custom formatting of the message before %logging it, and writing it to several destinations.

Once the message has been @ref boost::logging::gather "gathered", it's time to write it.
The current class defines the following concepts:
- formatter - allows formatting the message before writing it
- destination - is a place where the message is to be written to (like, the console, a file, a socket, etc)

You can add several formatters and destinations. Note that each formatter class and each destination class is a @c %manipulator.
Make sure you know what a manipulator is before using formatters and destinations.



\n\n
@section object_router The router object

Once you've added the formatters and destinations, the @ref msg_route "router" comes into play. The @ref msg_route "router" 
specifies how formatters and destinations are called. By default, all formatters are called first, in the order they were added,
and then all destinations are called, in the order they were added. You can easily access the router() instance.

@code
typedef process_msg< gather::ostream_like::return_cache_str<> , format_write<...> > process;
logger<process, filter::no_ts> g_l;
#define L_ if ( !g_l) ; else g_l->read_msg().gather().out()

// add formatters : [idx] [time] message [enter]
g_l->writer().add_formatter( write_idx() );
g_l->writer().add_formatter( write_time() );
g_l->writer().add_formatter( append_enter() );

// write to cout and file
g_l->writer().add_destination( write_to_cout() );
g_l->writer().add_destination( write_to_file("out.txt") );

// usage
int i = 1;
L_ << "testing " << i << i+1 << i+2;
@endcode

In the above case, @c write_idx() is called, then @c write_time(), then @c append_enter(). Now, the destinations are called:
@c write_to_cout(), and then @c write_to_file().

Most of the time this is ok, and this is what the @ref msg_route::simple "default router" does. However, there are other routers
in the msg_route namespace. For instance, take a look at msg_route::with_route class.



\n\n
@section apply_format_and_write_object The apply_format_and_write object

Once the formatters and destinations are added, and you know the route, you have an extra object - the format_and_write - which
contains the logic for calling the formatters and destinations. 
The format_and_write class knows how to call the formatters and destination @c objects. Usually you'll be happy with the 
format_and_write::simple class - which simply calls @c operator() on the formatters , and @c operator() on the destinations.
Otherwise, take a look at format_and_write namespace.

An object of this type (apply_format_and_write) is created for each new logged message.


\n\n
@note This class is not thread-safe. If you want thread-safety, check out the other writer classes: on_dedicated_thread and ts_write 



\n\n
@param format_base The base class for all formatter classes from your application. See manipulator.

@param destination_base The base class for all destination classes from your application. See manipulator.

@param apply_format_and_write [optional] The class that knows how to call the formatters and destinations. See @ref apply_format_and_write_object

@param router_type [optional] The class that knows when to call the formatters, and when to call the destinations. See @ref object_router.



\n\n
@remarks Normally the router could own the formatters and destination objects. However, then, it would need to own the objects,
which would mean needing to come up with a smart pointer strategy. This would complicate the router logic.
Also, iterating over formatters/destinations would be slower, if we were to keep smart pointers within the router itself.
*/
template<
        class formatter_base, 
        class destination_base, 
        class apply_format_and_write = boost::logging::format_and_write::simple<typename destination_base::raw_param>,
        class router_type = msg_route::simple<formatter_base, destination_base> ,
        class formatter_array = array::shared_ptr_holder<formatter_base> , 
        class destination_array = array::shared_ptr_holder<destination_base> >
struct format_write {
    typedef typename formatter_base::ptr_type formatter_ptr;
    typedef typename destination_base::ptr_type destination_ptr;

    format_write() : m_router(m_formatters, m_destinations) {}

    /** 
        adds a formatter
    */
    template<class formatter> void add_formatter(formatter fmt) {
        formatter_ptr p = m_formatters.append(fmt);
        m_router.append_formatter(p);
    }

    /** 
        deletes a formatter
    */
    template<class formatter> void del_formatter(formatter fmt) {
        formatter_ptr p = m_formatters.get_ptr(fmt);
        m_router.del_formatter(p);
        m_formatters.del(fmt);
    }

    /** 
        adds a destination
    */
    template<class destination> void add_destination(destination dest) {
        destination_ptr p = m_destinations.append(dest);
        m_router.append_destination(p);
    }

    /** 
        deletes a destination
    */
    template<class destination> void del_destination(destination dest) {
        destination_ptr p = m_destinations.get_ptr(dest);
        m_router.del_destination(p);
        m_destinations.del(dest);
    }

    /** 
    returns the object that actually routes the message
    */
    router_type& router()                         { return m_router; }

    /** 
    returns the object that actually routes the message
    */
    const router_type& router() const             { return m_router; }

    /** 
        does the actual write
    */
    template<class msg_type> void operator()(msg_type & msg) const {
        router().template write<apply_format_and_write>(msg);
    }

private:
    formatter_array m_formatters;
    destination_array m_destinations;
    router_type m_router;
};

} // namespace writer


}}

#endif

