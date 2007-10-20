// format.hpp

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

#ifndef JT28092007_format_HPP_DEFINED
#define JT28092007_format_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/logging/detail/fwd.hpp>
#include <boost/logging/detail/forward_constructor.hpp>
#include <boost/logging/format/op_equal.hpp>
#include <boost/logging/format/array.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace logging {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Format and write
    //

    /** 
        @brief The @c %format_and_write classes know how to call the formatter and destination @c objects. 
    
        Usually you'll be happy with the 
        format_and_write::simple class - which simply calls @c operator() on the formatters , and @c operator() on the destinations.

        Note that usually the formatter and destination class just have an @c operator(), which when called, formats the message
        or writes it to a destination. In case your formatters/destinations are more complex than that (for instance, more than 
        a member function needs to be called), you'll have to implement your own %format_and_write class.
    */
    namespace format_and_write {

    /** 
        @brief This uses a cache, when calling formatters/destinations - for writing a given message

        If a message was formatted before, it caches this info.

        FIXME this is not implemented yet
    */
    template<class formatter_base, class destination_base, class msg_type> 
    struct use_cache {
        use_cache( msg_type & msg) : m_msg(msg) {}

#if 0
        void format(const formatter_ptr & fmt) {
            // FIXME 
        }
        void write(const destination_ptr & dest) {
            // FIXME 
        }
        void clear_format() {
            // FIXME 
        }
#endif
    private:
        msg_type &m_msg;
    };


    /** 
        @brief Formats the message, and writes it to destinations - calls @c operator() on the formatters , and @c operator() on the destinations. Ignores @c clear_format() commands.

        @param msg_type The message to pass to the formatter. This is the type that is passed to the formatter objects and to the destination objects.
        Thus, it needs to be convertible to the argument to be sent to the formatter objects and to the argument to be sent to the destination objects.
        Usually, it's the argument you pass on to your destination classes.

        If you derive from @c destination::base, this type can be @c destination::base::raw_param (see below).

        Example:

        @code
        typedef destination::base<const std::string &> dest_base;
        // in this case : msg_type = std::string = dest_base::raw_param
        struct write_to_cout : dest_base {
            void operator()(param msg) const {
                std::cout << msg ;
            }
        };


        typedef destination::base<const std::string &> dest_base;
        // in this case : msg_type = cache_string = dest_base::raw_param
        struct write_to_file : dest_base, ... {
            void operator()(param msg) const {
                context() << msg ;
            }
        };

        @endcode
    */
    template<class msg_type> 
    struct simple {
        simple ( msg_type & msg) : m_msg(msg) {}

        template<class formatter_ptr> void format(const formatter_ptr & fmt) {
            (*fmt)(m_msg);
        }
        template<class destination_ptr> void write(const destination_ptr & dest) {
            (*dest)(m_msg);
        }
        void clear_format() {}
    protected:
        msg_type &m_msg;
    };


    /** 
        @brief Formats the message, and writes it to destinations - calls @c operator() on the formatters , and @c operator() on the destinations. 
        
        Cares for the @c clear_format() commands.

        @param msg_type The message to pass to the formatter. This is the type that is passed to the formatter objects and to the destination objects.
        Thus, it needs to be convertible to the argument to be sent to the formatter objects and to the argument to be sent to the destination objects.
        Usually, it's the argument you pass on to your destination classes.

        If you derive from @c destination::base, this type can be @c destination::base::raw_param (see below).

        @param string_type [optional] A class that can hold a string (that is, a copy of the message)

        Example:

        @code
        typedef destination::base<const std::string &> dest_base;
        // in this case : msg_type = std::string = dest_base::raw_param
        struct write_to_cout : dest_base {
            void operator()(param msg) const {
                std::cout << msg ;
            }
        };


        typedef destination::base<const std::string &> dest_base;
        // in this case : msg_type = cache_string = dest_base::raw_param
        struct write_to_file : dest_base, ... {
            void operator()(param msg) const {
                context() << msg ;
            }
        };

        @endcode

    */
    template<class msg_type, class string_type = hold_string_type> 
    struct simple_care_for_clear_format : simple<msg_type> {
        typedef simple<msg_type> simple_base_type;

        simple_care_for_clear_format( msg_type & msg) : simple_base_type(msg), m_original_msg( msg ) {}

        void clear_format() {
            simple_base_type::m_msg = m_original_msg;
        }
    private:
        msg_type m_original_msg;
    };

    } // namespace format_and_write



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Message routing
    //

    /** 
    @brief Specifies the route : how formatting and writing to destinations take place.

    Classes in this namespace specify when formatters and destinations are to be called. 

    @sa msg_route::simple, msg_route::with_route

    */
    namespace msg_route {

    /** 
        @brief Recomended base class for message routers that need access to the underlying formatter and/or destination array.
    */
    template<class formatter_array, class destination_array> 
    struct formatter_and_destination_array_holder {
    protected:
        formatter_and_destination_array_holder (const formatter_array & formats, const destination_array & destinations)
            : m_formats(formats), m_destinations(destinations) {}

        const formatter_array & formats() const             { return m_formats; }
        const destination_array & destinations() const      { return m_destinations; }

    private:
        const formatter_array & m_formats;
        const destination_array & m_destinations;
    };

    /** 
    @brief Represents a simple router - first calls all formatters - in the order they were added, then all destinations - in the order they were added

    Example:

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



@param format_base The base class for all formatter classes from your application. See manipulator.

@param destination_base The base class for all destination classes from your application. See manipulator.

    */
    template<
            class formatter_base, 
            class destination_base > 
    struct simple {
        typedef typename formatter_base::ptr_type formatter_ptr;
        typedef typename destination_base::ptr_type destination_ptr;

        typedef std::vector<formatter_ptr> f_array;
        typedef std::vector<destination_ptr> d_array;
        struct write_info {
            f_array formats;
            d_array destinations;
        };

        typedef typename boost::logging::types<override>::lock_resource::finder<write_info>::type data;

        template<class formatter_array, class destination_array> simple(const formatter_array&, const destination_array&) {}
        
        void append_formatter(formatter_ptr fmt) {
            typename data::write to_write(m_to_write);
            to_write->formats.push_back(fmt);
        }
        void del_formatter(formatter_ptr fmt) {
            typename data::write to_write(m_to_write);
            typename f_array::iterator del = std::remove(to_write->formats.begin(), to_write->formats.end(), fmt);
            to_write->formats.erase(del, to_write->formats.end());
        }

        void append_destination(destination_ptr dest) {
            typename data::write to_write(m_to_write);
            to_write->destinations.push_back(dest);
        }

        void del_destination(destination_ptr dest) {
            typename data::write to_write(m_to_write);
            typename d_array::iterator del = std::remove(to_write->destinations.begin(), to_write->destinations.end(), dest);
            to_write->destinations.erase(del, to_write->destinations.end());
        }

        template<class format_and_write, class msg_type> void write(msg_type & msg) const {
            format_and_write m(msg);

            // note: here, we're reading (data::read)!
            typename data::read to_write(m_to_write);
            for ( typename f_array::const_iterator b_f = to_write->formats.begin(), e_f = to_write->formats.end(); b_f != e_f; ++b_f)
                m.format(*b_f);

            for ( typename d_array::const_iterator b_d = to_write->destinations.begin(), e_d = to_write->destinations.end(); b_d != e_d; ++b_d)
                m.write(*b_d);
        }

    private:
        data m_to_write;
    };


    /** 
    @brief. Represents a router - by default, first calls all formatters, then all destinations. However you can overwrite this route

    You can append a route - with append_route(), or set the route with set_route().

    Example:

    @code
    typedef process_msg< gather::ostream_like::return_cache_str<> , 
        writer::format_write< format_base, destination_base, format_and_write::simple<cache_string>,
            msg_route::with_route<format_base,destination_base> > > process;
    logger<process, filter::no_ts> g_l;

    g_l->writer().router().set_route()
        .fmt( write_time() ) 
        .fmt( append_enter() )
        .dest( write_to_dbg() )
        .fmt( write_idx() )
        .dest( write_to_cout() )
        .clear()
        .fmt( write_idx() )
        .fmt( append_enter() )
        .fmt( write_to_file())
        ;
    @endcode

    @param format_base The base class for all formatter classes from your application. See manipulator.

    @param destination_base The base class for all destination classes from your application. See manipulator.

    @remarks In the router - we don't own the objects - the array holder does that
    */
    template<
            class formatter_base, 
            class destination_base,
            class formatter_array = boost::logging::array::shared_ptr_holder<formatter_base>,
            class destination_array = boost::logging::array::shared_ptr_holder<destination_base>
    > 
    class with_route  : protected formatter_and_destination_array_holder<formatter_array, destination_array> {
        typedef typename formatter_base::ptr_type formatter_ptr;
        typedef typename destination_base::ptr_type destination_ptr;

        typedef formatter_and_destination_array_holder<formatter_array, destination_array> holder_base_type;

        typedef with_route<formatter_base, destination_base, formatter_array, destination_array> self_type;

        typedef std::vector<formatter_ptr> f_array;
        typedef std::vector<destination_ptr> d_array;

        struct write_once {
            write_once() : do_clear_afterwards(false) {}
            f_array formats;
            d_array destinations;
            // if true, will execute clear_format() after calling all of the above
            bool do_clear_afterwards;
        };
        typedef std::vector<write_once> write_array;
        typedef typename boost::logging::types<override>::lock_resource::finder<write_array>::type data;

    public:
        with_route(const formatter_array& formatters, const destination_array & destinations) : holder_base_type(formatters, destinations) {}

        class route;
        friend class route;
        /** 
            represents a formatter/destination route to be added/set.
        */
        class route {
            friend class with_route;
            typedef enum type {
                is_fmt, is_dest, is_clear
            };
            struct item {
                item() : m_type(is_clear), m_fmt(0), m_dest(0) {}
                item& fmt(formatter_ptr f) { m_fmt = f; m_type = is_fmt; return *this; }
                item &dest(destination_ptr d) { m_dest = d; m_type = is_dest; return *this; }
                formatter_ptr m_fmt;
                destination_ptr m_dest;
                type m_type;
            };
            typedef std::vector<item> array;

        protected:
            route(self_type & self) : m_self(self) {}
        public:

            template<class formatter> route & fmt(formatter f) {
                m_items.push_back( item().fmt( m_self.formats().get_ptr(f) )) ;
                return *this;
            }
            template<class destination> route & dest(destination d) {
                m_items.push_back( item().dest( m_self.destinations().get_ptr(d) ));
                return *this;
            }
            route & clear() {
                m_items.push_back( item() );
                return *this;
            }

        protected:
            self_type & m_self;
            array m_items;
        };

        struct route_do_set;
        friend struct route_do_set;
        struct route_do_set : route {
            route_do_set(self_type &self) : route(self) {}
            ~route_do_set() {
                route::m_self.do_set_route( *this);
            }
        };

        struct route_do_append;
        friend struct route_do_append;
        struct route_do_append : route {
            route_do_append(self_type &self) : route(self) {}
            ~route_do_append() {
                route::m_self.do_append_route( *this);
            }
        };

        /** 
            sets this as the route for logging
        */
        route_do_set set_route() { return route_do_set(*this); }

        /** 
            appends this route
        */
        route_do_append append_route() { return route_do_append(*this); }

        void append_formatter(formatter_ptr fmt) {
            typename data::write to_write(m_to_write);

            if ( to_write->empty() )
                to_write->push_back( write_once() );

            // we need to add it a the end; if there are any destinations,
            // we need to add it after those
            bool can_append_to_back = to_write->back().destinations.empty();
            if ( !can_append_to_back)
                to_write->push_back( write_once() );
            to_write->back().formats.push_back(fmt);
        }
        void del_formatter(formatter_ptr fmt) {
            typename data::write to_write(m_to_write);

            for ( typename write_array::const_iterator b = to_write->begin(), e = to_write->end(); b != e; ++b) {
                typename f_array::iterator del = std::remove( b->formats.begin(), b->formats.end(), fmt);
                b->formats.erase(del, b->formats.end());
            }
        }

        void append_destination(destination_ptr dest) {
            typename data::write to_write(m_to_write);

            if ( to_write->empty() )
                to_write->push_back( write_once() );

            if ( to_write->back().do_clear_afterwards)
                // after clear, always start a new write
                to_write->push_back( write_once() );

            to_write->back().destinations.push_back(dest);
        }

        void del_destination(destination_ptr dest) {
            typename data::write to_write(m_to_write);

            for ( typename write_array::const_iterator b = to_write->begin(), e = to_write->end(); b != e; ++b) {
                typename d_array::iterator del = std::remove( b->destinations.begin(), b->destinations.end(), dest);
                b->destinations.erase(del, b->destinations.end());

                // if from a write_once - all destinations are gone, don't clear_afterwards 
                if ( b->destinations.empty() )
                    b->do_clear_afterwards = false;
            }
        }

        void append_clear_format() {
            typename data::write to_write(m_to_write);

            if ( to_write->empty() )
                to_write->push_back( write_once() );
            to_write->back().do_clear_afterwards = true;
            to_write->push_back( write_once() );
        }


        template<class format_and_write, class msg_type> void write(msg_type & msg) const {
            format_and_write m(msg);

            // note: here, we're reading (data::read)!
            typename data::read to_write(m_to_write);
            for ( typename write_array::const_iterator b = to_write->begin(), e = to_write->end(); b != e; ++b) {
                for ( typename f_array::const_iterator b_f = b->formats.begin(), e_f = b->formats.end(); b_f != e_f; ++b_f)
                    m.format(*b_f);

                for ( typename d_array::const_iterator b_d = b->destinations.begin(), e_d = b->destinations.end(); b_d != e_d; ++b_d)
                    m.write(*b_d);

                if ( b->do_clear_afterwards)
                    m.clear_format();
            }
        }

    private:
        void do_append_route(const route & r) {
            if ( r.m_items.empty() )
                return; // no route to add

            typedef typename route::array array;
            for ( typename array::const_iterator b = r.m_items.begin(), e = r.m_items.end(); b != e; ++b) {
                switch ( b->m_type) {
                case route::is_fmt:       append_formatter( b->m_fmt); break;
                case route::is_dest:      append_destination( b->m_dest); break;
                    break;  
                case route::is_clear:     append_clear_format(); break;
                    break;
                }
            }
        }

        void do_set_route(const route & r) {
            {
            typename data::write to_write(m_to_write);
            to_write->clear();
            }
            do_append_route(r);
        }

    private:
        data m_to_write;
    };


    } // namespace msg_route





}}

#include <boost/logging/detail/manipulator.hpp>
#include <boost/logging/writer/format_write.hpp>

#include <boost/logging/format/formatter/defaults.hpp>
#include <boost/logging/format/destination/defaults.hpp>
#include <boost/logging/process_msg/ostream_like.hpp>




#endif

