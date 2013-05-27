// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_CONTAINER_GEN_TEST_TYPE_DEFINITIONS_HPP_INCLUDED
#define LIBS_CONTAINER_GEN_TEST_TYPE_DEFINITIONS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/get_iterator_second.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/is_recursive_selector.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <string>
typedef std::string test_string;
#else
#include <boost/move/move.hpp>
#include <boost/container/string.hpp>
typedef boost::container::string test_string;
#endif

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4521) // "multiple copy constructors specified"
#endif

template <typename Selector, typename Key = void>
class test_recursive_data
{
    BOOST_MPL_ASSERT((boost::is_recursive_selector<Selector>));
    typedef typename boost::mpl::if_<
                std::tr1::is_void<Key>
              , boost::mpl::false_
              , boost::mpl::true_
            >::type
            _is_associative;

 public:
    typedef typename boost::mpl::eval_if<
                _is_associative
              , boost::container_gen<Selector,Key,test_recursive_data>
              , boost::container_gen<Selector,test_recursive_data>
            >::type
            next_level_t;

    test_recursive_data* previous_level;
    next_level_t next_level;
    test_string word;
    long number;
    char letter;
    bool flag;

    explicit test_recursive_data(
        char const* str = ""
      , long n = 0
      , char c = '\0'
      , bool b = false
    ) : previous_level()
      , next_level()
      , word(str)
      , number(n)
      , letter(c)
      , flag(b)
    {
    }

    test_recursive_data(test_recursive_data const& copy)
      : previous_level(copy.previous_level)
      , next_level(copy.next_level)
      , word(copy.word)
      , number(copy.number)
      , letter(copy.letter)
      , flag(copy.flag)
    {
        _link_levels(_is_associative());
    }

    test_recursive_data(test_recursive_data& copy)
      : previous_level(copy.previous_level)
      , next_level(copy.next_level)
      , word(copy.word)
      , number(copy.number)
      , letter(copy.letter)
      , flag(copy.flag)
    {
        _link_levels(_is_associative());
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_recursive_data& operator=(test_recursive_data const& copy)
    {
        if (this != &copy)
        {
            _copy_assign(copy);
        }

        return *this;
    }

    test_recursive_data& operator=(test_recursive_data& copy)
    {
        if (this != &copy)
        {
            _copy_assign(const_cast<test_recursive_data const&>(copy));
        }

        return *this;
    }

 private:
    void _copy_assign(test_recursive_data const& copy)
    {
        next_level = copy.next_level;
        word = copy.word;
        number = copy.number;
        _link_levels(_is_associative());
    }
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_recursive_data(BOOST_RV_REF(test_recursive_data) source)
      : previous_level(source.previous_level)
      , next_level(boost::move(source.next_level))
      , word(boost::move(source.word))
      , number(source.number)
      , letter(source.letter)
      , flag(source.flag)
    {
        _link_levels(_is_associative());
    }

#if defined BOOST_NO_RVALUE_REFERENCES
    operator boost::rv<test_recursive_data> const&() const
    {
        return *static_cast<boost::rv<test_recursive_data> const*>(this);
    }

    operator boost::rv<test_recursive_data>&()
    {
        return *static_cast<boost::rv<test_recursive_data>*>(this);
    }

    test_recursive_data&
        operator=(boost::rv<test_recursive_data> const& ca_ref)
    {
        test_recursive_data const& copy = static_cast<
            test_recursive_data const&
        >(ca_ref);

        if (this != &copy)
        {
            _copy_assign(copy);
        }

        return *this;
    }

    test_recursive_data& operator=(boost::rv<test_recursive_data>& rv_ref)
    {
        if (this != &static_cast<test_recursive_data&>(rv_ref))
        {
            _move_assign(rv_ref);
        }

        return *this;
    }

    test_recursive_data& operator=(test_recursive_data& copy)
    {
        if (this != &copy)
        {
            _copy_assign(const_cast<test_recursive_data const&>(copy));
        }

        return *this;
    }
#else  // !defined BOOST_NO_RVALUE_REFERENCES
    test_recursive_data& operator=(test_recursive_data const& copy)
    {
        if (this != &copy)
        {
            _copy_assign(copy);
        }

        return *this;
    }

    test_recursive_data& operator=(test_recursive_data&& source)
    {
        if (this != &static_cast<test_recursive_data&>(source))
        {
            _move_assign(static_cast<test_recursive_data&&>(source));
        }

        return *this;
    }
#endif  // BOOST_NO_RVALUE_REFERENCES

 private:
    void _copy_assign(BOOST_COPY_ASSIGN_REF(test_recursive_data) copy)
    {
        next_level = copy.next_level;
        word = copy.word;
        number = copy.number;
        _link_levels(_is_associative());
    }

    void _move_assign(BOOST_RV_REF(test_recursive_data) source)
    {
        next_level = boost::move(source.next_level);
        word = boost::move(source.word);
        number = source.number;
        _link_levels(_is_associative());
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    void _link_levels(boost::mpl::true_)
    {
        typename next_level_t::iterator itr_end = next_level.end();

        for (
            typename next_level_t::iterator itr = next_level.begin();
            itr != itr_end;
            ++itr
        )
        {
            boost::get_iterator_second(itr).previous_level = this;
        }
    }

    void _link_levels(boost::mpl::false_)
    {
        typename next_level_t::iterator itr_end = next_level.end();

        for (
            typename next_level_t::iterator itr = next_level.begin();
            itr != itr_end;
            ++itr
        )
        {
            itr->previous_level = this;
        }
    }
};

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

#endif  // LIBS_CONTAINER_GEN_TEST_TYPE_DEFINITIONS_HPP_INCLUDED

