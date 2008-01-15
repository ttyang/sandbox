/* 
    Tests destination::named
    - I have 3 stream destinations. I do simple logging (no formatting), and see that the message gets written to the destinations I specified
*/

#include <boost/logging/format.hpp>
#include <boost/logging/format/destination/named.hpp>

using namespace boost::logging::scenario::usage;
typedef use< filter_::change::single_thread, filter_::level::no_levels, logger_::change::single_thread, logger_::favor::single_thread > finder;

using namespace boost::logging;

BOOST_DEFINE_LOG_FILTER(g_log_filter, finder::filter  ) 
BOOST_DEFINE_LOG(g_l, finder::logger )

#define L_ BOOST_LOG_USE_LOG_IF_FILTER(g_l, g_log_filter->is_enabled() ) 


std::stringstream g_first;
std::stringstream g_second;
std::stringstream g_third;

destination::named_t<lock_resource_finder::single_thread> g_n;

// we're constantly writing hello world
std::string g_msg = "hello world";

void init_logs() {
    g_l->writer().add_destination( g_n
        .add( "first", destination::stream(g_first) )
        .add( "second", destination::stream(g_second) )
        .add( "third", destination::stream(g_third) ));

    g_l->writer().add_formatter( formatter::append_newline() );
    g_l->writer().add_destination( destination::cout() );
    g_l->turn_cache_off();
}

void test_use_all() {
    g_n.string("first second third");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("first +second third");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("+first second +third");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("+first +second +third");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");
}

void test_use_2() {
    g_n.string("first second -third");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("first second ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("first third -second");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("first -third +second");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "hello world\n");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("+third +second");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" second  third ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");
}


void test_use_1() {
    g_n.string(" second  -third -first ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" second  -third ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" second  ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("second");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "hello world\n");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" -second  third -first ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string("   third -first ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" third");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "hello world\n");
    g_first.str("");
    g_second.str("");
    g_third.str("");
}

void test_use_0() {
    g_n.string(" -second  -third -first ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" -second  -third ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" -second  ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");

    g_n.string(" ");
    L_ << g_msg;
    BOOST_ASSERT( g_first.str() == "");
    BOOST_ASSERT( g_second.str() == "");
    BOOST_ASSERT( g_third.str() == "");
    g_first.str("");
    g_second.str("");
    g_third.str("");
}

int main() {
    init_logs();
    test_use_all();
    test_use_2();
    test_use_1();
    test_use_0();
}
