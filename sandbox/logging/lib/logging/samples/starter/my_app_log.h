// my_app_log.h
#ifndef my_app_LOG_H_header
#define my_app_LOG_H_header

#include <boost/logging/format_fwd.hpp>

// uncomment if you're using Named Formatters and Destinations
//#include <boost/logging/format/named_write_fwd.hpp>

namespace bl = boost::logging;
typedef bl::tag::holder<
    // string class
    bl::optimize::cache_string_one_str<>,
    // tags
    bl::tag::thread_id, bl::tag::time> log_string_type;
// note: if you don't use tags, you can simply use a string class:
// typedef bl::optimize::cache_string_one_str<> log_string_type;
BOOST_LOG_FORMAT_MSG( log_string_type )

// if not compiling fast...
#ifndef BOOST_LOG_COMPILE_FAST
// uncomment if you want to do logging on a dedicated thread
// #include <boost/logging/writer/on_dedicated_thread.hpp>
#endif


using namespace boost::logging::scenario::usage;
typedef use<
        //  how often do you manipulate (change) the filter?
        filter_::change::often<10>,
        //  does the filter use levels?
        filter_::level::no_levels,
        // how often do you manipulate (change) the logger?
        logger_::change::often<10>,
        // for the logger: do you favor speed or correctness?
        logger_::favor::correctness> finder;

BOOST_DECLARE_LOG_FILTER(g_l_filter, finder::filter)
BOOST_DECLARE_LOG(g_l, finder::logger)

#define L_ BOOST_LOG_USE_LOG_IF_FILTER(g_l(), g_log_filter()->is_enabled() ) 

// initialize thy logs..
void init_logs();

#endif
