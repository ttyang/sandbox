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
#include <boost/container_gen/insert_range_function_gen.hpp>
#include <boost/container_gen/insert_range_result_gen.hpp>
#include "type_definitions.hpp"
#include "result_range.hpp"
#include <boost/test/minimal.hpp>

//[test__insert_range_function_gen
template <typename Selector, typename AddedContainer>
void test_insert_range_function_gen(AddedContainer const& added_container)
{
    typename boost::container_gen<Selector,test_string>::type
        example_container, test_container, input_container;
    typename boost::emplace_function_gen<Selector>::type emplacer;
    typename boost::insert_range_function_gen<Selector>::type range_inserter;

    emplacer[example_container]
        ("able")("fox")("easy")
        ("able")("fox")("iota")("hotel")("jupiter")("dog")
        ("baker")("charlie")("dog");
    emplacer[test_container]
        ("able")("fox")("easy")("baker")("charlie")("dog");
    emplacer[input_container]
        ("able")("fox")("iota")("hotel")("jupiter")("dog");

    typename boost::insert_range_result_gen<Selector,test_string>::type
        insert_range_result = range_inserter(
            test_container
          , ++++++test_container.begin()
          , input_container
        );

    BOOST_CHECK(
        test_result_range(
            insert_range_result
          , added_container
          , boost::is_associative_selector<Selector>()
        )
    );
    BOOST_CHECK(6 == input_container.size());
    BOOST_CHECK(boost::range::equal(test_container, example_container));
}
//]

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

//[test__insert_range_function_gen__main
int test_main(int argc, char** argv)
{
    boost::container_gen<boost::dequeS,test_string>::type added_container;
    boost::emplace_function_gen<boost::dequeS>::type emplacer;

    emplacer[added_container]
        ("able")("fox")("iota")("hotel")("jupiter")("dog");
    test_insert_range_function_gen<boost::vecS>(added_container);
    test_insert_range_function_gen<boost::dequeS>(added_container);
    test_insert_range_function_gen<boost::listS>(added_container);
    // ...
    //<-
    test_insert_range_function_gen<boost::ptr_vecS>(added_container);
    test_insert_range_function_gen<boost::ptr_dequeS>(added_container);
    test_insert_range_function_gen<boost::ptr_listS>(added_container);
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_insert_range_function_gen<boost::vector_selector<boost::mpl::true_> >(
        added_container
    );
    test_insert_range_function_gen<boost::stable_vecS>(added_container);
    test_insert_range_function_gen<boost::deque_selector<boost::mpl::true_> >(
        added_container
    );
    test_insert_range_function_gen<boost::list_selector<boost::mpl::true_> >(
        added_container
    );
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    added_container.clear();
    emplacer[added_container]
        ("able")("dog")("fox")("hotel")("iota")("jupiter");
    test_insert_range_function_gen<boost::multisetS>(added_container);
    test_insert_range_function_gen<boost::multimapS>(added_container);
    test_insert_range_function_gen<boost::ptr_multisetS>(added_container);
    test_insert_range_function_gen<boost::ptr_multimapS>(added_container);
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_insert_range_function_gen<
        boost::multiset_selector<boost::mpl::true_>
    >(added_container);
    test_insert_range_function_gen<
        boost::multimap_selector<boost::mpl::true_>
    >(added_container);
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    added_container.clear();
    emplacer[added_container]
        ("dog")("jupiter")("hotel")("iota")("fox")("able");
    test_insert_range_function_gen<boost::slistS>(added_container);
#endif
    added_container.clear();
    emplacer[added_container]("hotel")("iota")("jupiter");
    test_insert_range_function_gen<boost::setS>(added_container);
    test_insert_range_function_gen<boost::mapS>(added_container);
    test_insert_range_function_gen<boost::ptr_setS>(added_container);
    test_insert_range_function_gen<boost::ptr_mapS>(added_container);
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_insert_range_function_gen<boost::set_selector<boost::mpl::true_> >(
        added_container
    );
    test_insert_range_function_gen<boost::map_selector<boost::mpl::true_> >(
        added_container
    );
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    //->

    return 0;
}
//]

