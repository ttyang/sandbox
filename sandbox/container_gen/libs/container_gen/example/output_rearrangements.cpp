//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#include <iostream>
#include <list>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/has_front_not_top_mfunc_sel.hpp>

//[example__output_rearrangements__functions
template <typename Value, typename Buffer>
Value output_next(Buffer& buffer, boost::mpl::true_)
{
    return buffer.front();
}

template <typename Value, typename Buffer>
Value output_next(Buffer& buffer, boost::mpl::false_)
{
    return buffer.top();
}

template <typename Selector, typename Itr>
void output_rearrangement(Itr itr, Itr itr_end)
{
    typedef typename boost::iterator_value<Itr>::type Value;

    typename boost::container_gen<Selector,Value>::type buffer;

    for (; itr != itr_end; ++itr)
    {
        buffer.push(*itr);
    }

    for (; !buffer.empty(); buffer.pop())
    {
        std::cout << " " << output_next<Value>(
            buffer
          , boost::has_front_not_top_member_function_selector<Selector>()
        );
    }

    std::cout << std::endl;
}
//]

//[example__output_rearrangements__main
int main(int, char**)
{
    std::list<int> int_list;

    int_list.push_back(2);
    int_list.push_back(3);
    int_list.push_back(1);

    std::cout << "Original list:";
    output_rearrangement<boost::queueS>(int_list.begin(), int_list.end());
    std::cout << "In reverse:";
    output_rearrangement<boost::stackS>(int_list.begin(), int_list.end());
    std::cout << "With STL heap sort:";
    output_rearrangement<
        boost::std_heap_selector<boost::greater_than_selector>
    >(int_list.begin(), int_list.end());
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
    std::cout << "With Boost priority_queue:";
    output_rearrangement<
        boost::priority_queue_selector<boost::greater_than_selector>
    >(int_list.begin(), int_list.end());
    std::cout << "With 4-ary heap sort:";
    output_rearrangement<
        boost::d_ary_heap_selector<
//<-
#if defined BOOST_MPL_CFG_NO_HAS_XXX \
 || defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
            boost::compare_selector<
#endif
//->
            boost::greater_than_selector  // deduced Boost.Parameter tpl-arg
//<-
#if defined BOOST_MPL_CFG_NO_HAS_XXX \
 || defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
            >
#endif
//->
          , boost::heap::arity<4>         // explicit Boost.Parameter tpl-arg
        >
    >(int_list.begin(), int_list.end());
    std::cout << "With binomial heap sort:";
    output_rearrangement<
        boost::binomial_heap_selector<boost::greater_than_selector>
    >(int_list.begin(), int_list.end());
    std::cout << "With Fibonacci heap sort:";
    output_rearrangement<
        boost::fibonacci_heap_selector<boost::greater_than_selector>
    >(int_list.begin(), int_list.end());
    std::cout << "With pairing heap sort:";
    output_rearrangement<
        boost::pairing_heap_selector<boost::greater_than_selector>
    >(int_list.begin(), int_list.end());
    std::cout << "With skew heap sort:";
    output_rearrangement<
        boost::skew_heap_selector<boost::greater_than_selector>
    >(int_list.begin(), int_list.end());
//<-
#endif
//->

    return 0;
}
//]

