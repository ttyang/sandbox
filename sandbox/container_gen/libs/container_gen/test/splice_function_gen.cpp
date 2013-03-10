// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <boost/mpl/bool.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/is_associative_selector.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/container_gen/splice_function_gen.hpp>
#include <boost/container_gen/insert_range_result_gen.hpp>
#include "type_definitions.hpp"
#include "result_range.hpp"
#include <boost/test/minimal.hpp>

//[test__splice_function_gen
template <typename Selector, typename AddedContainer>
void test_splice_function_gen(AddedContainer const& added_container)
{
    typedef typename boost::container_gen<Selector,test_string>::type C;

    C ex_seq_1, ex_seq_2, test_seq_1, test_seq_2, input_seq;
    typename boost::emplace_function_gen<Selector>::type emplacer;
    typename boost::splice_function_gen<Selector>::type splicer;

    emplacer[ex_seq_1]
        ("able")("fox")("easy")("kilo")("baker")("charlie")("dog");
    emplacer[ex_seq_2]
        ("able")("fox")("easy")
        ("able")("fox")("iota")("hotel")("jupiter")("dog")
        ("baker")("charlie")("dog");
    emplacer[test_seq_1]
        ("able")("fox")("easy")("baker")("charlie")("dog");
    emplacer[input_seq]
        ("able")("fox")("iota")("kilo")("hotel")("jupiter")("dog");
    emplacer[test_seq_2]
        ("able")("fox")("iota")("hotel")("jupiter")("dog");

    C test_seq_3(test_seq_1);
    typename C::iterator itr = splicer(
        test_seq_1
      , ++++++test_seq_1.begin()
      , input_seq
      , ++++++input_seq.begin()
    );

    BOOST_CHECK(*itr == test_string("kilo"));
    BOOST_CHECK(boost::range::equal(test_seq_1, ex_seq_1));
    BOOST_CHECK(boost::range::equal(test_seq_2, input_seq));

    typename boost::insert_range_result_gen<Selector,test_string>::type
        insert_range_result = splicer(
            test_seq_3
          , ++++++test_seq_3.begin()
          , input_seq
          , input_seq.begin()
          , input_seq.end()
        );

    BOOST_CHECK(
        test_result_range(
            insert_range_result
          , added_container
          , boost::is_associative_selector<Selector>()
        )
    );
    BOOST_CHECK(input_seq.empty());
    BOOST_CHECK(boost::range::equal(test_seq_3, ex_seq_2));
}
//]

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

//[test__splice_function_gen__main
int test_main(int argc, char** argv)
{
    boost::container_gen<boost::dequeS,test_string>::type c;
    boost::emplace_function_gen<boost::dequeS>::type emplacer;

    emplacer[c]("able")("fox")("iota")("hotel")("jupiter")("dog");
    test_splice_function_gen<boost::vecS>(c);
    test_splice_function_gen<boost::dequeS>(c);
    test_splice_function_gen<boost::listS>(c);
    test_splice_function_gen<boost::ptr_vecS>(c);
    test_splice_function_gen<boost::ptr_dequeS>(c);
    test_splice_function_gen<boost::ptr_listS>(c);
    test_splice_function_gen<boost::vector_selector<boost::mpl::true_> >(c);
    test_splice_function_gen<boost::stable_vecS>(c);
    test_splice_function_gen<boost::deque_selector<boost::mpl::true_> >(c);
    test_splice_function_gen<boost::list_selector<boost::mpl::true_> >(c);
    c.clear();
    emplacer[c]("dog")("jupiter")("hotel")("iota")("fox")("able");
    test_splice_function_gen<boost::slistS>(c);

    return 0;
}
//]

