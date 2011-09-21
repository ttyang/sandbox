// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_MAPPED_INPUT_TABULAR_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_MAPPED_INPUT_TABULAR_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 3)
#error Set BOOST_PARAMETER_MAX_ARITY to 3 or more.
#endif

#include <boost/mpl/apply_wrap.hpp>
#include <boost/concept_check.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/assert.hpp>

//[reference__mapped_input_tabular_transition_function
namespace boost { namespace automata {

    template <
        typename T0
      , typename T1
      , typename T2 = ::boost::parameter::void_
    >
    class mapped_input_tabular_transition_function
    {
        // typedef implementation_defined Function;
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_Input>
                  , ::boost::parameter::required<keyword::tag::_Function>
                  , ::boost::parameter::optional<
                        keyword::tag::_AssociativeContainerSelector
                    >
                >::BOOST_NESTED_TEMPLATE bind<
                    T0
                  , T1
                  , T2
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , ::boost::parameter::void_
#endif
                >::type
                Args;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_Function
                >::type
                Function;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AssociativeContainerSelector
                  , ::boost::mapS
                >::type
                AssociativeContainerSelector;
        //->

        BOOST_CONCEPT_ASSERT((TabularTransitionFunction<Function>));

     public:
        typedef mapped_input_tabular_transition_function_tag
                tag;
        typedef typename Function::state
                state;
        typedef typename Function::result_type
                result_type;
        typedef typename Function::first_argument_type
                first_argument_type;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_Input
                >::type
                //->
                second_argument_type;

     private:
        // typedef implementation_defined Setter;
        //<-
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , second_argument_type
                  , typename Function::second_argument_type
                >::type
                InputMap;

        class Setter
        {
            mapped_input_tabular_transition_function& _function;
            first_argument_type                       _current_state;
            second_argument_type                      _i;

         public:
            Setter(
                mapped_input_tabular_transition_function& f
              , first_argument_type current_state
              , second_argument_type i
            );

            void operator=(result_type next_state);
        };

        Function _function;
        InputMap _input_map;
        //->

     public:
        mapped_input_tabular_transition_function();

        mapped_input_tabular_transition_function(
            mapped_input_tabular_transition_function const& copy
        );

        mapped_input_tabular_transition_function&
            operator=(mapped_input_tabular_transition_function const& copy);

        bool recognizes_input(second_argument_type i) const;

        bool recognizes_state(first_argument_type s) const;

        ::std::size_t get_state_count() const;

        result_type
            operator()(
                first_argument_type current_state
              , second_argument_type i
            ) const;

        template <typename Iterator>
        void
            make_nontrivial_inputs(
                first_argument_type current_state
              , Iterator itr
            ) const;

        void
            set_transition(
                first_argument_type current_state
              , second_argument_type i
              , result_type next_state
            );

        Setter
            operator()(
                first_argument_type current_state
              , second_argument_type i
            );

        template <typename Iterator>
        void reset(::std::size_t state_count, Iterator itr, Iterator itr_end);

        //<-
        template <
            typename T0_
          , typename T1_
          , typename T2_
          , typename T3_
          , typename T4_
          , typename T5_
        >
        friend bool
            operator==(
                mapped_input_tabular_transition_function<
                    T0_
                  , T1_
                  , T2_
                > const& lhs
              , mapped_input_tabular_transition_function<
                    T3_
                  , T4_
                  , T5_
                > const& rhs
            );
        //->
    };

    //<-
    template <typename T0, typename T1, typename T2>
    mapped_input_tabular_transition_function<
        T0
      , T1
      , T2
    >::mapped_input_tabular_transition_function() : _function(), _input_map()
    {
    }

    template <typename T0, typename T1, typename T2>
    mapped_input_tabular_transition_function<
        T0
      , T1
      , T2
    >::mapped_input_tabular_transition_function(
        mapped_input_tabular_transition_function const& copy
    ) : _function(copy._function), _input_map(copy._input_map)
    {
    }

    template <typename T0, typename T1, typename T2>
    mapped_input_tabular_transition_function<T0,T1,T2>&
        mapped_input_tabular_transition_function<T0,T1,T2>::operator=(
            mapped_input_tabular_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _function  = copy._function;
            _input_map = copy._input_map;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2>
    inline bool
        mapped_input_tabular_transition_function<T0,T1,T2>::recognizes_input(
            second_argument_type i
        ) const
    {
        return _input_map.find(i) != _input_map.end();
    }

    template <typename T0, typename T1, typename T2>
    inline bool
        mapped_input_tabular_transition_function<T0,T1,T2>::recognizes_state(
            first_argument_type s
        ) const
    {
        return _function.recognizes_state(s);
    }

    template <typename T0, typename T1, typename T2>
    inline ::std::size_t
        mapped_input_tabular_transition_function<
            T0
          , T1
          , T2
        >::get_state_count() const
    {
        return _function.get_state_count();
    }

    template <typename T0, typename T1, typename T2>
    inline typename mapped_input_tabular_transition_function<
        T0
      , T1
      , T2
    >::result_type
        mapped_input_tabular_transition_function<T0,T1,T2>::operator()(
            first_argument_type current_state
          , second_argument_type i
        ) const
    {
        BOOST_ASSERT(recognizes_input(i));

        return _function(current_state, _input_map.find(i)->second);
    }

    template <typename T0, typename T1, typename T2>
    template <typename Iterator>
    void
        mapped_input_tabular_transition_function<
            T0
          , T1
          , T2
        >::make_nontrivial_inputs(
            first_argument_type current_state
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));

        typename InputMap::const_iterator map_end = _input_map.end();

        for (
            typename InputMap::const_iterator map_itr = _input_map.begin();
            map_itr != map_end;
            ++map_itr
        )
        {
            if (current_state != _function(current_state, map_itr->second))
            {
                *itr = map_itr->first;
                ++itr;
            }
        }
    }

    template <typename T0, typename T1, typename T2>
    inline void
        mapped_input_tabular_transition_function<T0,T1,T2>::set_transition(
            first_argument_type current_state
          , second_argument_type i
          , result_type next_state
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));
        BOOST_ASSERT(recognizes_state(next_state));

        _function.set_transition(
            current_state
          , _input_map.find(i)->second
          , next_state
        );
    }

    template <typename T0, typename T1, typename T2>
    mapped_input_tabular_transition_function<T0,T1,T2>::Setter::Setter(
        mapped_input_tabular_transition_function& f
      , first_argument_type current_state
      , second_argument_type i
    ) : _function(f), _current_state(current_state), _i(i)
    {
    }

    template <typename T0, typename T1, typename T2>
    void
        mapped_input_tabular_transition_function<T0,T1,T2>::Setter::operator=(
            result_type next_state
        )
    {
        _function.set_transition(_current_state, _i, next_state);
    }

    template <typename T0, typename T1, typename T2>
    typename mapped_input_tabular_transition_function<T0,T1,T2>::Setter
        mapped_input_tabular_transition_function<T0,T1,T2>::operator()(
            first_argument_type current_state
          , second_argument_type i
        )
    {
        return Setter(*this, current_state, i);
    }

    template <typename T0, typename T1, typename T2>
    template <typename Iterator>
    void
        mapped_input_tabular_transition_function<T0,T1,T2>::reset(
            ::std::size_t state_count
          , Iterator itr
          , Iterator itr_end
        )
    {
        _input_map.clear();

        ::std::size_t i = std::size_t();

        while (itr != itr_end)
        {
            if (_input_map.find(*itr) == _input_map.end())
            {
                _input_map[*itr] = i;
                ++i;
            }

            ++itr;
        }

        _function.reset(state_count, i);
    }
    //->

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
    >
    bool
        operator==(
            mapped_input_tabular_transition_function<T0,T1,T2> const& lhs
          , mapped_input_tabular_transition_function<T3,T4,T5> const& rhs
        );

    //<-
    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
    >
    bool
        operator==(
            mapped_input_tabular_transition_function<T0,T1,T2> const& lhs
          , mapped_input_tabular_transition_function<T3,T4,T5> const& rhs
        )
    {
        if (
            !(lhs.get_state_count() == rhs.get_state_count())
         || !(lhs._input_map.size() == rhs._input_map.size())
        )
        {
            return false;
        }

        typedef typename mapped_input_tabular_transition_function<
                    T0
                  , T1
                  , T2
                >::InputMap
                LHS_InputMap;
        typedef typename LHS_InputMap::const_iterator
                LHS_InputMapIterator;
        typedef typename mapped_input_tabular_transition_function<
                    T3
                  , T4
                  , T5
                >::InputMap
                RHS_InputMap;
        typedef typename RHS_InputMap::const_iterator
                RHS_InputMapIterator;

        RHS_InputMapIterator r_end = rhs._input_map.end();
        LHS_InputMapIterator l_end = lhs._input_map.end();
        LHS_InputMapIterator l_itr = lhs._input_map.begin();

        while (l_itr != l_end)
        {
            if (rhs._input_map.find(l_itr->first) == r_end)
            {
                return false;
            }

            ++l_itr;
        }

        ::std::size_t s = lhs.get_state_count();

        while (s)
        {
            --s;

            for (l_itr = lhs._input_map.begin(); l_itr != l_end; ++l_itr)
            {
                if (
                    lhs._function(s, l_itr->first)
                 != rhs._function(s, l_itr->first)
                )
                {
                    return false;
                }
            }
        }

        return true;
    }
    //->

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
    >
    bool
        operator!=(
            mapped_input_tabular_transition_function<T0,T1,T2> const& lhs
          , mapped_input_tabular_transition_function<T3,T4,T5> const& rhs
        );

    //<-
    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
    >
    inline bool
        operator!=(
            mapped_input_tabular_transition_function<T0,T1,T2> const& lhs
          , mapped_input_tabular_transition_function<T3,T4,T5> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_MAPPED_INPUT_TABULAR_HPP_INCLUDED

