/**
@example mul_levels_mul_logers.cpp

@copydoc mul_levels_mul_logers 

@page mul_levels_mul_logers mul_levels_mul_logers.cpp Example


This usage:
- You have multiple levels (in this example: debug < info < error)
- You want to format the message before it's written 
  (in this example: prefix it by time, by index and append newline to it)
- You have several loggers
- Each logger has several log destinations

Optimizations:
- use a cache string (from optimize namespace), in order to make formatting the message faster

Logs:
- Error messages go into err.txt file
  - formatting - prefix each message by time, index, and append newline
- Info output goes to console, and a file called out.txt
  - formatting - prefix each message by "[app]", time, and append newline
- Debug messages go to the debug output window, and a file called out.txt
  - formatting - prefix each message by "[dbg]", time, and append newline


Here's how the output will look like:

The debug output window:
@code
07:52.30 [dbg] this is so cool 1
07:52.30 [dbg] this is so cool again 2
@endcode


The console:
@code
07:52.30 [app] hello, world
07:52.30 [app] good to be back ;) 4
@endcode


The out.txt file:
@code
07:52.30 [dbg] this is so cool 1
07:52.30 [dbg] this is so cool again 2
07:52.30 [app] hello, world
07:52.30 [app] good to be back ;) 4
@endcode


The err.txt file
@code
07:52.30 [1] first error 3
07:52.30 [2] second error 5
@endcode
*/



#include <boost/logging/format_fwd.hpp>

// Step 1: Optimize : use a cache string, to make formatting the message faster
BOOST_LOG_FORMAT_MSG( optimize::cache_string_one_str<> )

#include <boost/logging/format.hpp>

// Step 3 : Specify your logging class(es)
typedef boost::logging::logger_format_write< > log_type;


// Step 4: declare which filters and loggers you'll use (usually in a header file)
BOOST_DECLARE_LOG_FILTER(g_log_level, boost::logging::level::holder ) // holds the application log level
BOOST_DECLARE_LOG(g_log_err, log_type) 
BOOST_DECLARE_LOG(g_log_app, log_type)
BOOST_DECLARE_LOG(g_log_dbg, log_type)

// Step 5: define the macros through which you'll log
#define LDBG_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg, g_log_level, debug ) << "[dbg] "
#define LERR_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_err, g_log_level, error )
#define LAPP_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app, g_log_level, info ) << "[app] "

// Step 6: Define the filters and loggers you'll use (usually in a source file)
BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DEFINE_LOG(g_log_err, log_type)
BOOST_DEFINE_LOG(g_log_app, log_type)
BOOST_DEFINE_LOG(g_log_dbg, log_type)

using namespace boost::logging;

void mul_levels_mul_logers_example() {
    // Step 7: add formatters and destinations
    //         That is, how the message is to be formatted and where should it be written to

    // Err log
    g_log_err->writer().add_formatter( formatter::idx(), "[%] "  );
    g_log_err->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
    g_log_err->writer().add_formatter( formatter::append_newline() );
    g_log_err->writer().add_destination( destination::file("err.txt") );

    destination::file out("out.txt");
    // App log
    g_log_app->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
    g_log_app->writer().add_formatter( formatter::append_newline() );
    g_log_app->writer().add_destination( out );
    g_log_app->writer().add_destination( destination::cout() );

    // Debug log
    g_log_dbg->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
    g_log_dbg->writer().add_formatter( formatter::append_newline() );
    g_log_dbg->writer().add_destination( out );
    g_log_dbg->writer().add_destination( destination::dbg_window() );

    g_log_app->turn_cache_off();
    g_log_err->turn_cache_off();
    g_log_dbg->turn_cache_off();

    // Step 8: use it...
    int i = 1;
    LDBG_ << "this is so cool " << i++;
    LDBG_ << "this is so cool again " << i++;
    LERR_ << "first error " << i++;

    std::string hello = "hello", world = "world";
    LAPP_ << hello << ", " << world;

    g_log_level->set_enabled(level::error);
    LDBG_ << "this will not be written anywhere";
    LAPP_ << "this won't be written anywhere either";

    g_log_level->set_enabled(level::info);
    LAPP_ << "good to be back ;) " << i++;
    LERR_ << "second error " << i++;

    // Step 9 : Enjoy!
}




int main() {
    mul_levels_mul_logers_example();
}


// End of file

