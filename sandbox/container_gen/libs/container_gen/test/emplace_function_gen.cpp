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
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include "type_definitions.hpp"
#include <boost/test/minimal.hpp>

template <typename Emplacer, typename C>
void
    test_emplacer(
        Emplacer const& emplacer
      , C& c
      , bool should_be_successful
      , char const* value
    )
{
    typename C::size_type old_size = c.size();
    std::pair<typename C::iterator,bool> p = emplacer(c, value);

    BOOST_CHECK(p.second == should_be_successful);

    if (p.second)
    {
        BOOST_CHECK(!strcmp((*p.first).c_str(), value));
        BOOST_CHECK(c.size() == old_size + 1);
    }
    else
    {
        BOOST_CHECK(c.size() == old_size);
    }
}

template <typename Selector>
void test_emplace_function_gen()
{
    typename boost::container_gen<Selector,test_string>::type
        test_container_1, test_container_2;
    typename boost::emplace_function_gen<Selector>::type emplacer;
    bool is_multi = !boost::is_unique_associative_selector<Selector>::value;

    test_emplacer(emplacer, test_container_1, true, "able");
    test_emplacer(emplacer, test_container_1, true, "fox");
    test_emplacer(emplacer, test_container_1, true, "easy");
    test_emplacer(emplacer, test_container_1, true, "baker");
    test_emplacer(emplacer, test_container_1, true, "charlie");
    test_emplacer(emplacer, test_container_1, true, "dog");
    test_emplacer(emplacer, test_container_1, is_multi, "able");
    test_emplacer(emplacer, test_container_1, is_multi, "fox");
    test_emplacer(emplacer, test_container_1, is_multi, "easy");
    test_emplacer(emplacer, test_container_1, is_multi, "baker");
    test_emplacer(emplacer, test_container_1, is_multi, "charlie");
    test_emplacer(emplacer, test_container_1, is_multi, "dog");

    emplacer[test_container_2]
        ("able")("fox")("easy")("baker")("charlie")("dog")
        ("able")("fox")("easy")("baker")("charlie")("dog");

    BOOST_CHECK(boost::range::equal(test_container_1, test_container_2));
}

template <typename T>
void test_recursive_element(T const& t)
{
    BOOST_CHECK(
        !strcmp(t.word.c_str(), "")
     || !strcmp(t.word.c_str(), "sol")
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
        BOOST_CHECK((*itr).previous_level == &t);
        test_recursive_element(*itr);
    }
}

template <typename Emplacer, typename T>
void test_emplacer_recursive(Emplacer const& emplacer, T& t)
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(t.next_level);

    (*p.first).previous_level = &t;
    BOOST_CHECK(p.second);
    test_recursive_element(t);
    BOOST_CHECK(!strcmp((*p.first).word.c_str(), ""));
    BOOST_CHECK((*p.first).number == 0);
    BOOST_CHECK((*p.first).letter == '\0');
    BOOST_CHECK((*p.first).flag == false);
    BOOST_CHECK(t.next_level.size() == old_size + 1);
}

template <typename Emplacer, typename T>
void test_emplacer_recursive(Emplacer const& emplacer, T& t, char const* word)
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(t.next_level, word);

    (*p.first).previous_level = &t;
    BOOST_CHECK(p.second);
    test_recursive_element(t);
    BOOST_CHECK(!strcmp((*p.first).word.c_str(), word));
    BOOST_CHECK((*p.first).number == 0);
    BOOST_CHECK((*p.first).letter == '\0');
    BOOST_CHECK((*p.first).flag == false);
    BOOST_CHECK(t.next_level.size() == old_size + 1);
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , char const* word
      , long n
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(t.next_level, word, n);

    (*p.first).previous_level = &t;
    BOOST_CHECK(p.second);
    test_recursive_element(t);
    BOOST_CHECK(!strcmp((*p.first).word.c_str(), word));
    BOOST_CHECK((*p.first).number == n);
    BOOST_CHECK((*p.first).letter == '\0');
    BOOST_CHECK((*p.first).flag == false);
    BOOST_CHECK(t.next_level.size() == old_size + 1);
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , char const* word
      , long n
      , char letter
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(
        t.next_level
      , word
      , n
      , letter
    );

    (*p.first).previous_level = &t;
    BOOST_CHECK(p.second);
    test_recursive_element(t);
    BOOST_CHECK(!strcmp((*p.first).word.c_str(), word));
    BOOST_CHECK((*p.first).number == n);
    BOOST_CHECK((*p.first).letter == letter);
    BOOST_CHECK((*p.first).flag == false);
    BOOST_CHECK(t.next_level.size() == old_size + 1);
}

template <typename Emplacer, typename T>
void
    test_emplacer_recursive(
        Emplacer const& emplacer
      , T& t
      , char const* word
      , long n
      , char letter
      , bool b
    )
{
    typedef typename T::next_level_t C;
    typename C::size_type old_size = t.next_level.size();
    std::pair<typename C::iterator,bool> p = emplacer(
        t.next_level
      , word
      , n
      , letter
      , b
    );

    (*p.first).previous_level = &t;
    BOOST_CHECK(p.second);
    test_recursive_element(t);
    BOOST_CHECK(!strcmp((*p.first).word.c_str(), word));
    BOOST_CHECK((*p.first).number == n);
    BOOST_CHECK((*p.first).letter == letter);
    BOOST_CHECK((*p.first).flag == b);
    BOOST_CHECK(t.next_level.size() == old_size + 1);
}

template <typename Selector>
struct test_mri_element
{
    template <typename T>
    T& operator()(T& t)
    {
        return t.next_level.back();
    }
};

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <>
struct test_mri_element<boost::slistS>
{
    template <typename T>
    T& operator()(T& t)
    {
        return t.next_level.front();
    }
};

template <>
struct test_mri_element<boost::stable_vecS>
{
    template <typename T>
    T& operator()(T& t)
    {
        return *(t.next_level.begin() + t.next_level.size() - 1);
    }
};
#endif

template <typename Selector>
void test_emplace_function_gen_recursive()
{
    test_recursive_data<Selector> top;
    typename boost::emplace_function_gen<Selector>::type emplacer;

    test_emplacer_recursive(emplacer, top);
    test_emplacer_recursive(emplacer, top, "sol");

    {
        test_recursive_data<Selector>& t = test_mri_element<Selector>()(top);
        test_emplacer_recursive(emplacer, t, "sol", 42);
    }

    {
        test_recursive_data<Selector>& t = test_mri_element<Selector>()(top);
        test_emplacer_recursive(emplacer, t, "sol", 42, 'X');
    }

    test_emplacer_recursive(emplacer, top, "sol", 42, 'X', true);
}

template <typename Pair1, typename Pair2>
void test_emplace_results(Pair1 const& p1, Pair2 const& p2)
{
    BOOST_CHECK(p1.second == p2.second);

    if (p1.second)
    {
        BOOST_CHECK(*p1.first == *p2.first);
    }
}

template <typename Selector1, typename Selector2>
void test_emplace_function_gens()
{
    typename boost::container_gen<Selector1,test_string>::type container_1;
    typename boost::container_gen<Selector2,test_string>::type container_2;
    typename boost::emplace_function_gen<Selector1>::type emplacer_1;
    typename boost::emplace_function_gen<Selector2>::type emplacer_2;

    test_emplace_results(
        emplacer_1(container_1, "able")
      , emplacer_2(container_2, "able")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "fox")
      , emplacer_2(container_2, "fox")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "easy")
      , emplacer_2(container_2, "easy")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "baker")
      , emplacer_2(container_2, "baker")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "charlie")
      , emplacer_2(container_2, "charlie")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "dog")
      , emplacer_2(container_2, "dog")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "able")
      , emplacer_2(container_2, "able")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "fox")
      , emplacer_2(container_2, "fox")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "easy")
      , emplacer_2(container_2, "easy")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "baker")
      , emplacer_2(container_2, "baker")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "charlie")
      , emplacer_2(container_2, "charlie")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
    test_emplace_results(
        emplacer_1(container_1, "dog")
      , emplacer_2(container_2, "dog")
    );
    BOOST_CHECK(boost::range::equal(container_1, container_2));
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

int test_main(int argc, char** argv)
{
    test_emplace_function_gen<boost::vecS>();
    test_emplace_function_gen<boost::dequeS>();
    test_emplace_function_gen<boost::listS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    test_emplace_function_gen<boost::slistS>();
#endif
    test_emplace_function_gen<boost::setS>();
    test_emplace_function_gen<boost::mapS>();
    test_emplace_function_gen<boost::multisetS>();
    test_emplace_function_gen<boost::multimapS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    test_emplace_function_gen<boost::hash_setS>();
    test_emplace_function_gen<boost::hash_mapS>();
    test_emplace_function_gen<boost::hash_multisetS>();
    test_emplace_function_gen<boost::hash_multimapS>();
#endif
    test_emplace_function_gen<boost::ptr_vecS>();
    test_emplace_function_gen<boost::ptr_dequeS>();
    test_emplace_function_gen<boost::ptr_listS>();
    test_emplace_function_gen<boost::ptr_setS>();
    test_emplace_function_gen<boost::ptr_mapS>();
    test_emplace_function_gen<boost::ptr_multisetS>();
    test_emplace_function_gen<boost::ptr_multimapS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_emplace_function_gen<boost::ptr_hash_setS>();
    test_emplace_function_gen<boost::ptr_hash_mapS>();
    test_emplace_function_gen<boost::ptr_hash_multisetS>();
    test_emplace_function_gen<boost::ptr_hash_multimapS>();
    test_emplace_function_gen<boost::vector_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::stable_vecS>();
    test_emplace_function_gen<boost::deque_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::list_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::set_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::map_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::multiset_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::multimap_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::hash_set_selector<boost::mpl::true_> >();
    test_emplace_function_gen<boost::hash_map_selector<boost::mpl::true_> >();
    test_emplace_function_gen<
        boost::hash_multiset_selector<boost::mpl::true_>
    >();
    test_emplace_function_gen<
        boost::hash_multimap_selector<boost::mpl::true_>
    >();
    test_emplace_function_gen<boost::flat_setS>();
    test_emplace_function_gen<boost::flat_mapS>();
    test_emplace_function_gen<boost::flat_multisetS>();
    test_emplace_function_gen<boost::flat_multimapS>();
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    test_emplace_function_gen_recursive<boost::ptr_vecS>();
    test_emplace_function_gen_recursive<boost::ptr_dequeS>();
    test_emplace_function_gen_recursive<boost::ptr_listS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_emplace_function_gen_recursive<boost::stable_vecS>();
    test_emplace_function_gen_recursive<
        boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gen_recursive<
        boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gen_recursive<
        boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gen_recursive<boost::slistS>();
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    test_emplace_function_gens<boost::vecS,boost::dequeS>();
    test_emplace_function_gens<boost::vecS,boost::listS>();
    test_emplace_function_gens<boost::vecS,boost::ptr_vecS>();
    test_emplace_function_gens<boost::vecS,boost::ptr_dequeS>();
    test_emplace_function_gens<boost::vecS,boost::ptr_listS>();
    test_emplace_function_gens<boost::dequeS,boost::listS>();
    test_emplace_function_gens<boost::dequeS,boost::ptr_vecS>();
    test_emplace_function_gens<boost::dequeS,boost::ptr_dequeS>();
    test_emplace_function_gens<boost::dequeS,boost::ptr_listS>();
    test_emplace_function_gens<boost::listS,boost::ptr_vecS>();
    test_emplace_function_gens<boost::listS,boost::ptr_dequeS>();
    test_emplace_function_gens<boost::listS,boost::ptr_listS>();
    test_emplace_function_gens<boost::ptr_vecS,boost::ptr_dequeS>();
    test_emplace_function_gens<boost::ptr_vecS,boost::ptr_listS>();
    test_emplace_function_gens<boost::ptr_dequeS,boost::ptr_listS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_emplace_function_gens<boost::vecS,boost::stable_vecS>();
    test_emplace_function_gens<boost::dequeS,boost::stable_vecS>();
    test_emplace_function_gens<boost::listS,boost::stable_vecS>();
    test_emplace_function_gens<boost::ptr_vecS,boost::stable_vecS>();
    test_emplace_function_gens<boost::ptr_dequeS,boost::stable_vecS>();
    test_emplace_function_gens<
        boost::vecS
      , boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::vecS
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::vecS
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::dequeS
      , boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::dequeS
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::dequeS
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::listS
      , boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::listS
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::listS
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::ptr_vecS
      , boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::ptr_vecS
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::ptr_vecS
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::ptr_dequeS
      , boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::ptr_dequeS
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::ptr_dequeS
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::stable_vecS
      , boost::vector_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::stable_vecS
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::stable_vecS
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::vector_selector<boost::mpl::true_>
      , boost::deque_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::vector_selector<boost::mpl::true_>
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::deque_selector<boost::mpl::true_>
      , boost::list_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<boost::setS,boost::flat_setS>();
    test_emplace_function_gens<boost::mapS,boost::flat_mapS>();
    test_emplace_function_gens<boost::multisetS,boost::flat_multisetS>();
    test_emplace_function_gens<boost::multimapS,boost::flat_multimapS>();
    test_emplace_function_gens<
        boost::setS
      , boost::set_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::mapS
      , boost::map_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::multisetS
      , boost::multiset_selector<boost::mpl::true_>
    >();
    test_emplace_function_gens<
        boost::multimapS
      , boost::multimap_selector<boost::mpl::true_>
    >();
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    return 0;
}

