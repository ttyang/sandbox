// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_NEXT_STATE_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_NEXT_STATE_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 2)
#error Set BOOST_PARAMETER_MAX_ARITY to 2 or more.
#endif

#include <vector>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/assert.hpp>

//[reference__next_state_transition_function
namespace boost { namespace automata {

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    class next_state_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::optional<
                        keyword::tag::_AssociativeContainerSelector
                    >
                  , ::boost::parameter::optional<
                        keyword::tag::_RandomAccessContainerSelector
                    >
                >::BOOST_NESTED_TEMPLATE bind<
                    T0
                  , T1
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , ::boost::parameter::void_
#endif
                >::type
                Args;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AssociativeContainerSelector
                  , ::boost::setS
                >::type
                AssociativeContainerSelector;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_RandomAccessContainerSelector
                  , ::boost::vecS
                >::type
                RandomAccessContainerSelector;
        //->

     public:
        typedef next_state_transition_function_tag tag;
        typedef ::std::size_t                      state;
        typedef state                              result_type;
        typedef state                              first_argument_type;
        typedef state                              second_argument_type;

     private:
        // typedef implementation_defined Adder;
        //<-
        class Adder
        {
            next_state_transition_function& _function;
            first_argument_type const       _current_state;

         public:
            Adder(
                next_state_transition_function& f
              , first_argument_type current_state
            );

            void operator+=(result_type next_state);
        };

        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , second_argument_type
                >::type
                InputSet;
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , InputSet
                >::type
                Transitions;

        Transitions _transitions;
        //->

     public:
        next_state_transition_function();

        next_state_transition_function(
            next_state_transition_function const& copy
        );

        next_state_transition_function&
            operator=(next_state_transition_function const& copy);

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
            add_transition(
                first_argument_type current_state
              , second_argument_type next_state
            );

        Adder operator()(first_argument_type current_state);

        void reset(::std::size_t state_count);

        //<-
        template <typename T0_, typename T1_, typename T2_, typename T3_>
        friend bool
            operator==(
                next_state_transition_function<T0_,T1_> const& lhs
              , next_state_transition_function<T2_,T3_> const& rhs
            );
        //->
    };

    //<-
    template <typename T0, typename T1>
    next_state_transition_function<T0,T1>::next_state_transition_function()
      : _transitions()
    {
    }

    template <typename T0, typename T1>
    next_state_transition_function<T0,T1>::next_state_transition_function(
        next_state_transition_function const& copy
    ) : _transitions(copy._transitions)
    {
    }

    template <typename T0, typename T1>
    inline next_state_transition_function<T0,T1>&
        next_state_transition_function<T0,T1>::operator=(
            next_state_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _transitions = copy._transitions;
        }

        return *this;
    }

    template <typename T0, typename T1>
    inline bool
        next_state_transition_function<T0,T1>::recognizes_input(
            second_argument_type const i
        ) const
    {
        return i < _transitions.size();
    }

    template <typename T0, typename T1>
    inline bool
        next_state_transition_function<T0,T1>::recognizes_state(
            first_argument_type const s
        ) const
    {
        return s < _transitions.size();
    }

    template <typename T0, typename T1>
    inline ::std::size_t
        next_state_transition_function<T0,T1>::get_state_count() const
    {
        return _transitions.size();
    }

    template <typename T0, typename T1>
    inline typename next_state_transition_function<T0,T1>::result_type
        next_state_transition_function<T0,T1>::operator()(
            first_argument_type const current_state
          , second_argument_type const i
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));

        InputSet const& input_set = _transitions[current_state];

        return (input_set.find(i) == input_set.end()) ? current_state : i;
    }

    template <typename T0, typename T1>
    template <typename Iterator>
    void
        next_state_transition_function<T0,T1>::make_nontrivial_inputs(
            first_argument_type const current_state
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));

        InputSet const& input_set = _transitions[current_state];
        typename InputSet::const_iterator set_end = input_set.end();

        for (
            typename InputSet::const_iterator set_itr = input_set.begin();
            set_itr != set_end;
            ++set_itr
        )
        {
            *itr = *set_itr;
            ++itr;
        }
    }

    template <typename T0, typename T1>
    inline void
        next_state_transition_function<T0,T1>::add_transition(
            first_argument_type const current_state
          , second_argument_type const next_state
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_state(next_state));

        if (current_state != next_state)
        {
            InputSet& input_set = _transitions[current_state];

            if (input_set.find(next_state) == input_set.end())
            {
                input_set.insert(next_state);
            }
        }
        // The else case is degenerate.
    }

    template <typename T0, typename T1>
    next_state_transition_function<T0,T1>::Adder::Adder(
        next_state_transition_function& f
      , first_argument_type const current_state
    ) : _function(f), _current_state(current_state)
    {
    }

    template <typename T0, typename T1>
    void
        next_state_transition_function<T0,T1>::Adder::operator+=(
            second_argument_type const next_state
        )
    {
        _function.add_transition(_current_state, next_state);
    }

    template <typename T0, typename T1>
    typename next_state_transition_function<T0,T1>::Adder
        next_state_transition_function<T0,T1>::operator()(
            first_argument_type const current_state
        )
    {
        return Adder(*this, current_state);
    }

    template <typename T0, typename T1>
    void
        next_state_transition_function<T0,T1>::reset(::std::size_t state_count)
    {
        _transitions.resize(state_count);

        while (state_count)
        {
            _transitions[--state_count].clear();
        }
    }
    //->

    template <typename T0, typename T1, typename T2, typename T3>
    bool
        operator==(
            next_state_transition_function<T0,T1> const& lhs
          , next_state_transition_function<T2,T3> const& rhs
        );

    //<-
    template <typename T0, typename T1, typename T2, typename T3>
    bool
        operator==(
            next_state_transition_function<T0,T1> const& lhs
          , next_state_transition_function<T2,T3> const& rhs
        )
    {
        if (lhs.get_state_count() != rhs.get_state_count())
        {
            return false;
        }

        typedef typename next_state_transition_function<T0,T1>::InputSet
                LHS_InputSet;
        typedef typename LHS_InputSet::const_iterator
                LHS_InputSetIterator;
        typedef typename next_state_transition_function<T2,T3>::InputSet
                RHS_InputSet;
        typedef typename RHS_InputSet::const_iterator
                RHS_InputSetIterator;

        LHS_InputSetIterator lhs_itr, lhs_end;
        RHS_InputSetIterator rhs_end;
        ::std::size_t s = lhs._transitions.size();

        while (s)
        {
            LHS_InputSet const& lhs_set = lhs._transitions[--s];
            RHS_InputSet const& rhs_set = rhs._transitions[s];

            if (lhs_set.size() != rhs_set.size())
            {
                return false;
            }

            lhs_end = lhs_set.end();
            rhs_end = rhs_set.end();

            for (lhs_itr = lhs_set.begin(); lhs_itr != lhs_end; ++lhs_itr)
            {
                if (rhs_set.find(*lhs_itr) == rhs_end)
                {
                    return false;
                }
            }
        }

        return true;
    }
    //->

    template <typename T0, typename T1, typename T2, typename T3>
    bool
        operator!=(
            next_state_transition_function<T0,T1> const& lhs
          , next_state_transition_function<T2,T3> const& rhs
        );

    //<-
    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        operator!=(
            next_state_transition_function<T0,T1> const& lhs
          , next_state_transition_function<T2,T3> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_NEXT_STATE_HPP_INCLUDED

