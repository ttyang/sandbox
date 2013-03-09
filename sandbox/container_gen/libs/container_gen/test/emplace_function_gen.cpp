// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <utility>
#include <cstring>
#include <boost/mpl/bool.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/utility/get_iterator_second.hpp>
#include <boost/utility/get_iterator_value_second.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_assoc_function_gen.hpp>
#include <boost/container_gen/is_multiple_assoc_selector.hpp>
#include "type_definitions.hpp"
#include <boost/test/minimal.hpp>

template <typename Emplacer, typename C>
void
    test_emplacer(
        Emplacer const& emplacer
      , C& c
      , bool should_be_successful
      , typename C::key_type const& key
    )
{
    typename C::size_type old_size = c.size();
    std::pair<typename C::iterator,bool> p = emplacer(c, key);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        BOOST_CHECK(!strcmp(boost::get_iterator_second(p.first).c_str(), ""));
        BOOST_CHECK(c.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(c.size() == old_size);
    }
}

template <typename Emplacer, typename C>
void
    test_emplacer(
        Emplacer const& emplacer
      , C& c
      , bool should_be_successful
      , typename C::key_type const& key
      , char const* value
    )
{
    typename C::size_type old_size = c.size();
    std::pair<typename C::iterator,bool> p = emplacer(c, key, value);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        BOOST_CHECK(
            !strcmp(boost::get_iterator_second(p.first).c_str(), value)
        );
        BOOST_CHECK(c.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(c.size() == old_size);
    }
}

template <typename Selector>
void test_empl_assoc_func_gen()
{
    typename boost::container_gen<Selector,int,test_string>::type
        test_container_1, test_container_2;
    typename boost::emplace_associative_function_gen<Selector>::type emplacer;
    bool is_multi = boost::is_multiple_associative_selector<Selector>::value;

    test_emplacer(emplacer, test_container_1, true, 3, "able");
    test_emplacer(emplacer, test_container_1, true, -3, "fox");
    test_emplacer(emplacer, test_container_1, true, 2);
    test_emplacer(emplacer, test_container_1, true, -2, "baker");
    test_emplacer(emplacer, test_container_1, true, 1, "charlie");
    test_emplacer(emplacer, test_container_1, true, -1, "dog");
    test_emplacer(emplacer, test_container_1, is_multi, -1, "able");
    test_emplacer(emplacer, test_container_1, is_multi, 1, "fox");
    test_emplacer(emplacer, test_container_1, is_multi, -2);
    test_emplacer(emplacer, test_container_1, is_multi, 2, "baker");
    test_emplacer(emplacer, test_container_1, is_multi, -3, "charlie");
    test_emplacer(emplacer, test_container_1, is_multi, 3, "dog");

    emplacer[test_container_2]
        (3, "able")(-3, "fox")(2)(-2, "baker")(1, "charlie")(-1, "dog")
        (-1, "able")(1, "fox")(-2)(2, "baker")(-3, "charlie")(3, "dog");

    BOOST_CHECK(boost::range::equal(test_container_1, test_container_2));
}

template <typename T>
void test_recursive_element(T const& t)
{
    BOOST_CHECK(
        !strcmp(t.word.c_str(), "")
     || !strcmp(t.word.c_str(), "secret")
    );
    BOOST_CHECK((t.number == 0) || (t.number == 42));
    BOOST_CHECK((t.letter == '\0') || (t.letter == 'X'));

    typedef typename T::next_level_t C;
    typename C::const_iterator itr_end = t.next_level.end();

    for (
        typename C::const_iterator itr = t.next_level.begin();
        itr != itr_end;
        ++itr
    )
    {
        BOOST_CHECK(boost::get_iterator_second(itr).previous_level == &t);
        test_recursive_element(boost::get_iterator_second(itr));
    }
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , bool should_be_successful
      , typename T::next_level_t::key_type const& key
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(t.next_level, key);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        test_recursive_element(boost::get_iterator_second(p.first));
        BOOST_CHECK(
            !strcmp(boost::get_iterator_second(p.first).word.c_str(), "")
        );
        BOOST_CHECK(boost::get_iterator_second(p.first).number == 0);
        BOOST_CHECK(boost::get_iterator_second(p.first).letter == '\0');
        BOOST_CHECK(boost::get_iterator_second(p.first).flag == false);
        BOOST_CHECK(t.next_level.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(t.next_level.size() == old_size);
    }
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , bool should_be_successful
      , typename T::next_level_t::key_type const& key
      , char const* word
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(t.next_level, key, word);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        test_recursive_element(boost::get_iterator_second(p.first));
        BOOST_CHECK(
            !strcmp(boost::get_iterator_second(p.first).word.c_str(), word)
        );
        BOOST_CHECK(boost::get_iterator_second(p.first).number == 0);
        BOOST_CHECK(boost::get_iterator_second(p.first).letter == '\0');
        BOOST_CHECK(boost::get_iterator_second(p.first).flag == false);
        BOOST_CHECK(t.next_level.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(t.next_level.size() == old_size);
    }
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , bool should_be_successful
      , typename T::next_level_t::key_type const& key
      , char const* word
      , long n
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<
        typename C::iterator
      , bool
    > p = emplacer(t.next_level, key, word, n);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        test_recursive_element(boost::get_iterator_second(p.first));
        BOOST_CHECK(
            !strcmp(boost::get_iterator_second(p.first).word.c_str(), word)
        );
        BOOST_CHECK(boost::get_iterator_second(p.first).number == n);
        BOOST_CHECK(boost::get_iterator_second(p.first).letter == '\0');
        BOOST_CHECK(boost::get_iterator_second(p.first).flag == false);
        BOOST_CHECK(t.next_level.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(t.next_level.size() == old_size);
    }
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , bool should_be_successful
      , typename T::next_level_t::key_type const& key
      , char const* word
      , long n
      , char letter
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<
        typename C::iterator
      , bool
    > p = emplacer(t.next_level, key, word, n, letter);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        test_recursive_element(boost::get_iterator_second(p.first));
        BOOST_CHECK(
            !strcmp(boost::get_iterator_second(p.first).word.c_str(), word)
        );
        BOOST_CHECK(boost::get_iterator_second(p.first).number == n);
        BOOST_CHECK(boost::get_iterator_second(p.first).letter == letter);
        BOOST_CHECK(boost::get_iterator_second(p.first).flag == false);
        BOOST_CHECK(t.next_level.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(t.next_level.size() == old_size);
    }
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , bool should_be_successful
      , typename T::next_level_t::key_type const& key
      , char const* word
      , long n
      , char letter
      , bool b
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<
        typename C::iterator
      , bool
    > p = emplacer(t.next_level, key, word, n, letter, b);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(p.first->first == key);
        test_recursive_element(boost::get_iterator_second(p.first));
        BOOST_CHECK(
            !strcmp(boost::get_iterator_second(p.first).word.c_str(), word)
        );
        BOOST_CHECK(boost::get_iterator_second(p.first).number == n);
        BOOST_CHECK(boost::get_iterator_second(p.first).letter == letter);
        BOOST_CHECK(boost::get_iterator_second(p.first).flag == b);
        BOOST_CHECK(t.next_level.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(t.next_level.size() == old_size);
    }
}

template <typename Selector>
void test_empl_assoc_func_gen_recursive()
{
    test_recursive_data<Selector,int> top;
    typename boost::emplace_associative_function_gen<Selector>::type emplacer;

    test_emplacer_recursive(emplacer, top, true, 0);
    test_emplacer_recursive(emplacer, top, true, 1, "secret");
    test_emplacer_recursive(
        emplacer
      , boost::get_iterator_second(top.next_level.find(1))
      , true
      , 2
      , "secret"
      , 42
    );
    test_emplacer_recursive(
        emplacer
      , boost::get_iterator_second(top.next_level.find(1))
      , true
      , 3
      , "secret"
      , 42
      , 'X'
    );
    test_emplacer_recursive(emplacer, top, true, 4, "secret", 42, 'X', true);
}

template <typename Pair1, typename Pair2>
void test_emplace_results(Pair1 const& p1, Pair2 const& p2)
{
    BOOST_CHECK(p1.second == p2.second);

    if (p1.second)
    {
        BOOST_CHECK(p1.first->first == p2.first->first);
        BOOST_CHECK(
            boost::get_iterator_second(p1.first)
         == boost::get_iterator_second(p2.first)
        );
    }
}

struct test_string_comparator
{
    template <typename Pair1, typename Pair2>
    bool operator()(Pair1 const& p1, Pair2 const& p2) const
    {
        return (
            (p1.first == p2.first)
         && (
                boost::get_iterator_value_second(p1)
             == boost::get_iterator_value_second(p2)
            )
        );
    }
};

template <typename Selector1, typename Selector2>
void test_empl_assoc_func_gens()
{
    typename boost::container_gen<Selector1,int,test_string>::type container_1;
    typename boost::container_gen<Selector2,int,test_string>::type container_2;
    typename boost::emplace_associative_function_gen<Selector1>::type adder_1;
    typename boost::emplace_associative_function_gen<Selector2>::type adder_2;
    test_string_comparator comparator;

    test_emplace_results(
        adder_1(container_1, 3, "able")
      , adder_2(container_2, 3, "able")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, -3, "fox")
      , adder_2(container_2, -3, "fox")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(adder_1(container_1, 2), adder_2(container_2, 2));
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, -2, "baker")
      , adder_2(container_2, -2, "baker")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, 1, "charlie")
      , adder_2(container_2, 1, "charlie")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, -1, "dog")
      , adder_2(container_2, -1, "dog")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, -1, "able")
      , adder_2(container_2, -1, "able")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, 1, "fox")
      , adder_2(container_2, 1, "fox")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(adder_1(container_1, -2), adder_2(container_2, -2));
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, 2, "baker")
      , adder_2(container_2, 2, "baker")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, -3, "charlie")
      , adder_2(container_2, -3, "charlie")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
    test_emplace_results(
        adder_1(container_1, 3, "dog")
      , adder_2(container_2, 3, "dog")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2, comparator));
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

int test_main(int argc, char** argv)
{
    test_empl_assoc_func_gen<boost::setS>();
    test_empl_assoc_func_gen<boost::mapS>();
    test_empl_assoc_func_gen<boost::multisetS>();
    test_empl_assoc_func_gen<boost::multimapS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    test_empl_assoc_func_gen<boost::hash_setS>();
    test_empl_assoc_func_gen<boost::hash_mapS>();
    test_empl_assoc_func_gen<boost::hash_multisetS>();
    test_empl_assoc_func_gen<boost::hash_multimapS>();
#endif
    test_empl_assoc_func_gen<boost::ptr_setS>();
    test_empl_assoc_func_gen<boost::ptr_mapS>();
    test_empl_assoc_func_gen<boost::ptr_multisetS>();
    test_empl_assoc_func_gen<boost::ptr_multimapS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_empl_assoc_func_gen<boost::ptr_hash_setS>();
    test_empl_assoc_func_gen<boost::ptr_hash_mapS>();
    test_empl_assoc_func_gen<boost::ptr_hash_multisetS>();
    test_empl_assoc_func_gen<boost::ptr_hash_multimapS>();
    test_empl_assoc_func_gen<boost::set_selector<boost::mpl::true_> >();
    test_empl_assoc_func_gen<boost::map_selector<boost::mpl::true_> >();
    test_empl_assoc_func_gen<boost::multiset_selector<boost::mpl::true_> >();
    test_empl_assoc_func_gen<boost::multimap_selector<boost::mpl::true_> >();
    test_empl_assoc_func_gen<boost::hash_set_selector<boost::mpl::true_> >();
    test_empl_assoc_func_gen<boost::hash_map_selector<boost::mpl::true_> >();
    test_empl_assoc_func_gen<
        boost::hash_multiset_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen<
        boost::hash_multimap_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen<boost::flat_setS>();
    test_empl_assoc_func_gen<boost::flat_mapS>();
    test_empl_assoc_func_gen<boost::flat_multisetS>();
    test_empl_assoc_func_gen<boost::flat_multimapS>();
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    test_empl_assoc_func_gen_recursive<boost::ptr_setS>();
    test_empl_assoc_func_gen_recursive<boost::ptr_mapS>();
    test_empl_assoc_func_gen_recursive<boost::ptr_multisetS>();
    test_empl_assoc_func_gen_recursive<boost::ptr_multimapS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_empl_assoc_func_gen_recursive<boost::ptr_hash_setS>();
    test_empl_assoc_func_gen_recursive<boost::ptr_hash_mapS>();
    test_empl_assoc_func_gen_recursive<boost::ptr_hash_multisetS>();
    test_empl_assoc_func_gen_recursive<boost::ptr_hash_multimapS>();
    test_empl_assoc_func_gen_recursive<
        boost::set_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::map_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::multiset_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::multimap_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::hash_set_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::hash_map_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::hash_multiset_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<
        boost::hash_multimap_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gen_recursive<boost::flat_setS>();
    test_empl_assoc_func_gen_recursive<boost::flat_mapS>();
    test_empl_assoc_func_gen_recursive<boost::flat_multisetS>();
    test_empl_assoc_func_gen_recursive<boost::flat_multimapS>();
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    test_empl_assoc_func_gens<boost::setS,boost::ptr_setS>();
    test_empl_assoc_func_gens<boost::mapS,boost::ptr_mapS>();
    test_empl_assoc_func_gens<boost::multisetS,boost::ptr_multisetS>();
    test_empl_assoc_func_gens<boost::multimapS,boost::ptr_multimapS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_empl_assoc_func_gens<
        boost::setS
      , boost::set_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gens<
        boost::mapS
      , boost::map_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gens<
        boost::multisetS
      , boost::multiset_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gens<
        boost::multimapS
      , boost::multimap_selector<boost::mpl::true_>
    >();
    test_empl_assoc_func_gens<boost::setS,boost::flat_setS>();
    test_empl_assoc_func_gens<boost::mapS,boost::flat_mapS>();
    test_empl_assoc_func_gens<boost::multisetS,boost::flat_multisetS>();
    test_empl_assoc_func_gens<boost::multimapS,boost::flat_multimapS>();
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    return 0;
}

