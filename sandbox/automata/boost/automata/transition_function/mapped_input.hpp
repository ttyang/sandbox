// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_MAPPED_INPUT_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_MAPPED_INPUT_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 3)
#error Set BOOST_PARAMETER_MAX_ARITY to 3 or more.
#endif

#include <boost/config.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/assert.hpp>

//[reference__mapped_input_transition_function
namespace boost { namespace automata {

    template <
        typename T0
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    class mapped_input_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_Input>
                  , ::boost::parameter::optional<
                        keyword::tag::_AssociativeContainerSelector
                    >
                  , ::boost::parameter::optional<
                        keyword::tag::_RandomAccessContainerSelector
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
                  , keyword::tag::_AssociativeContainerSelector
                  , ::boost::mapS
                >::type
                AssociativeContainerSelector;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_RandomAccessContainerSelector
                  , ::boost::vecS
                >::type
                RandomAccessContainerSelector;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_Input
                >::type
                input;
        //->

     public:
        typedef mapped_input_transition_function_tag
                tag;
        typedef ::std::size_t
                state;
        typedef state
                result_type;
        typedef state
                first_argument_type;
        typedef // implementation_defined
                // <-
                input
                // ->
                second_argument_type;

     private:
        // typedef implementation_defined Setter;
        //<-
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , input
                >::type
                InputSet;
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , input
                  , state
                >::type
                TransitionMap;
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , TransitionMap
                >::type
                Transitions;

        class Setter
        {
            mapped_input_transition_function& _function;
            first_argument_type const&        _current_state;
            second_argument_type const&       _i;

         public:
            Setter(
                mapped_input_transition_function& f
              , first_argument_type const& current_state
              , second_argument_type const& i
            );

            void operator=(result_type next_state);
        };

        Transitions _transitions;
        InputSet    _inputs;
        //->

     public:
        mapped_input_transition_function();

        mapped_input_transition_function(
            mapped_input_transition_function const& copy
        );

        mapped_input_transition_function&
            operator=(mapped_input_transition_function const& copy);

        bool recognizes_input(second_argument_type const& i) const;

        bool recognizes_state(first_argument_type const& s) const;

        ::std::size_t get_state_count() const;

        result_type const&
            operator()(
                first_argument_type const& current_state
              , second_argument_type const& i
            ) const;

        template <typename Iterator>
        void
            make_nontrivial_inputs(
                first_argument_type const& current_state
              , Iterator itr
            ) const;

        void
            set_transition(
                first_argument_type const& current_state
              , second_argument_type const& i
              , result_type next_state
            );

        Setter
            operator()(
                first_argument_type const& current_state
              , second_argument_type const& i
            );

        void reset(::std::size_t state_count);

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
                mapped_input_transition_function<T0_,T1_,T2_> const& lhs
              , mapped_input_transition_function<T3_,T4_,T5_> const& rhs
            );
        //->
    };

    //<-
    template <typename T0, typename T1, typename T2>
    mapped_input_transition_function<
        T0
      , T1
      , T2
    >::mapped_input_transition_function() : _transitions(), _inputs()
    {
    }

    template <typename T0, typename T1, typename T2>
    mapped_input_transition_function<
        T0
      , T1
      , T2
    >::mapped_input_transition_function(
        mapped_input_transition_function const& copy
    ) : _transitions(copy._transitions), _inputs(copy._inputs)
    {
    }

    template <typename T0, typename T1, typename T2>
    mapped_input_transition_function<T0,T1,T2>&
        mapped_input_transition_function<T0,T1,T2>::operator=(
            mapped_input_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _transitions = copy._transitions;
            _inputs      = copy._inputs;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2>
    inline bool
        mapped_input_transition_function<T0,T1,T2>::recognizes_input(
            second_argument_type const& i
        ) const
    {
        return _inputs.find(i) != _inputs.end();
    }

    template <typename T0, typename T1, typename T2>
    inline bool
        mapped_input_transition_function<T0,T1,T2>::recognizes_state(
            first_argument_type const& s
        ) const
    {
        return s < _transitions.size();
    }

    template <typename T0, typename T1, typename T2>
    inline ::std::size_t
        mapped_input_transition_function<T0,T1,T2>::get_state_count() const
    {
        return _transitions.size();
    }

    template <typename T0, typename T1, typename T2>
    inline typename mapped_input_transition_function<
        T0
      , T1
      , T2
    >::result_type const&
        mapped_input_transition_function<T0,T1,T2>::operator()(
            first_argument_type const& current_state
          , second_argument_type const& i
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));

        TransitionMap const& t_map = _transitions[current_state];
        typename TransitionMap::const_iterator map_itr = t_map.find(i);
        return (map_itr == t_map.end()) ? current_state : map_itr->second;
    }

    template <typename T0, typename T1, typename T2>
    template <typename Iterator>
    void
        mapped_input_transition_function<T0,T1,T2>::make_nontrivial_inputs(
            first_argument_type const& current_state
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));

        TransitionMap const& t_map = _transitions[current_state];
        typename TransitionMap::const_iterator map_end = t_map.end();

        for (
            typename TransitionMap::const_iterator map_itr = t_map.begin();
            map_itr != map_end;
            ++map_itr
        )
        {
            *itr = map_itr->first;
            ++itr;
        }
    }

    template <typename T0, typename T1, typename T2>
    inline void
        mapped_input_transition_function<T0,T1,T2>::set_transition(
            first_argument_type const& current_state
          , second_argument_type const& i
          , result_type next_state
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_state(next_state));

        _inputs.insert(i);
        _transitions[current_state][i] = next_state;
    }

    template <typename T0, typename T1, typename T2>
    mapped_input_transition_function<T0,T1,T2>::Setter::Setter(
        mapped_input_transition_function& f
      , first_argument_type const& current_state
      , second_argument_type const& i
    ) : _function(f), _current_state(current_state), _i(i)
    {
    }

    template <typename T0, typename T1, typename T2>
    void
        mapped_input_transition_function<T0,T1,T2>::Setter::operator=(
            result_type next_state
        )
    {
        _function.set_transition(_current_state, _i, next_state);
    }

    template <typename T0, typename T1, typename T2>
    typename mapped_input_transition_function<T0,T1,T2>::Setter
        mapped_input_transition_function<T0,T1,T2>::operator()(
            first_argument_type const& current_state
          , second_argument_type const& i
        )
    {
        return Setter(*this, current_state, i);
    }

    template <typename T0, typename T1, typename T2>
    void
        mapped_input_transition_function<T0,T1,T2>::reset(
            ::std::size_t state_count
        )
    {
        _inputs.clear();
        _transitions.resize(state_count);

        while (state_count)
        {
            _transitions[--state_count].clear();
        }
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
            mapped_input_transition_function<T0,T1,T2> const& lhs
          , mapped_input_transition_function<T3,T4,T5> const& rhs
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
            mapped_input_transition_function<T0,T1,T2> const& lhs
          , mapped_input_transition_function<T3,T4,T5> const& rhs
        )
    {
        if (
            !(lhs.get_state_count() == rhs.get_state_count())
         || !(lhs._inputs.size() == rhs._inputs.size())
        )
        {
            return false;
        }

        typedef typename mapped_input_transition_function<T0,T1,T2>::InputSet
                LHS_InputSet;
        typedef typename LHS_InputSet::const_iterator
                LHS_InputSetIterator;
        typedef typename mapped_input_transition_function<T3,T4,T5>::InputSet
                RHS_InputSet;
        typedef typename RHS_InputSet::const_iterator
                RHS_InputSetIterator;

        RHS_InputSetIterator r_end = rhs._inputs.end();
        LHS_InputSetIterator l_end = lhs._inputs.end();
        LHS_InputSetIterator l_itr = lhs._inputs.begin();

        while (l_itr != l_end)
        {
            if (rhs._inputs.find(*l_itr) == r_end)
            {
                return false;
            }

            ++l_itr;
        }

        typedef typename mapped_input_transition_function<
                    T0
                  , T1
                  , T2
                >::TransitionMap
                LHS_TransitionMap;
        typedef typename LHS_TransitionMap::const_iterator
                LHS_TransitionMapIterator;
        typedef typename mapped_input_transition_function<
                    T3
                  , T4
                  , T5
                >::TransitionMap
                RHS_TransitionMap;
        typedef typename RHS_TransitionMap::const_iterator
                RHS_TransitionMapIterator;

        LHS_TransitionMapIterator l_map_itr;
        LHS_TransitionMapIterator l_map_end;
        RHS_TransitionMapIterator r_map_itr;
        RHS_TransitionMapIterator r_map_end;
        ::std::size_t s = lhs._transitions.size();

        while (s)
        {
            LHS_TransitionMap const& lhs_map = lhs._transitions[--s];
            RHS_TransitionMap const& rhs_map = rhs._transitions[s];

            l_map_end = lhs_map.end();
            r_map_end = rhs_map.end();

            for (
                l_map_itr = lhs_map.begin();
                l_map_itr != l_map_end;
                ++l_map_itr
            )
            {
                r_map_itr = rhs_map.find(l_map_itr->first);

                if (
                    (r_map_itr == r_map_end)
                 || !(r_map_itr->second == l_map_itr->second)
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
            mapped_input_transition_function<T0,T1,T2> const& lhs
          , mapped_input_transition_function<T3,T4,T5> const& rhs
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
            mapped_input_transition_function<T0,T1,T2> const& lhs
          , mapped_input_transition_function<T3,T4,T5> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_MAPPED_INPUT_HPP_INCLUDED

