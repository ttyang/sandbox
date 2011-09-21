// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_MDP_MAPPED_INPUT_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_MDP_MAPPED_INPUT_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 4)
#error Set BOOST_PARAMETER_MAX_ARITY to 4 or more.
#endif

#include <iterator>
#include <algorithm>
#include <numeric>
#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/random.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/assert.hpp>

//[reference__mdp_mapped_input_transition_function
namespace boost { namespace automata {

    template <
        typename T0
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    class mdp_mapped_input_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_Input>
                  , ::boost::parameter::optional<keyword::tag::_RealNumber>
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
                  , T3
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , ::boost::parameter::void_
#endif
                >::type
                Args;
        //->

     public:
        typedef mdp_transition_function_tag
                tag;
        typedef ::std::size_t
                state;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_Input
                >::type
                //->
                input;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_RealNumber
                  , double
                >::type
                real_number;
        typedef bool
                result_type;

        //<-
     private:
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
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , input
                >::type
                InputSet;
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , real_number
                >::type
                Probabilities;
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , input
                  , Probabilities
                >::type
                TransitionMap;
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , TransitionMap
                >::type
                Transitions;

        class Setter
        {
            Probabilities&                        _probabilities;
            mdp_mapped_input_transition_function& _function;

         public:
            Setter(
                Probabilities& probabilities
              , mdp_mapped_input_transition_function& f
            );

            template <typename Integral>
            typename ::boost::enable_if<
                ::std::tr1::is_integral<Integral>
              , Setter&
            >::type
                operator=(Integral const& next_state)
            {
                BOOST_ASSERT(_function.recognizes_state(next_state));

                real_number const zero_value = initialized_value;

                for (::std::size_t i = 0; i < _probabilities.size(); ++i)
                {
                    _probabilities[i] = zero_value;
                }

                _probabilities[next_state] += 1;
                return *this;
            }

            template <typename PairContainer>
            typename ::boost::disable_if<
                ::std::tr1::is_integral<PairContainer>
              , Setter&
            >::type
                operator=(PairContainer const& container)
            {
                real_number const zero_value = initialized_value;

                for (::std::size_t i = 0; i < _probabilities.size(); ++i)
                {
                    _probabilities[i] = zero_value;
                }

                *this += container;
                return *this;
            }

            template <typename PairContainer>
            void operator+=(PairContainer const& container);
        };

        Transitions _transitions;
        InputSet    _inputs;
        //->
        // typedef implementation_defined Setter;

     public:
        mdp_mapped_input_transition_function();

        mdp_mapped_input_transition_function(
            mdp_mapped_input_transition_function const& copy
        );

        mdp_mapped_input_transition_function&
            operator=(mdp_mapped_input_transition_function const& copy);

        bool recognizes_input(input const& i) const;

        bool recognizes_state(state s) const;

        ::std::size_t get_state_count() const;

        bool
            is_nontrivial_input(
                state current_state
              , input const& i
            ) const;

        template <typename Iterator>
        void
            make_nontrivial_inputs(
                state current_state
              , Iterator itr
            ) const;

        real_number
            get_probability(
                state current_state
              , input const& i
              , state next_state
            ) const;

        template <typename RNGEngine>
        result_type
            operator()(
                state& current_state
              , input const& i
              , RNGEngine& rng_engine
            ) const;

        Setter operator()(state current_state, input const& i);

        void reset(::std::size_t state_count);
    };

    //<-
    template <typename T0, typename T1, typename T2, typename T3>
    mdp_mapped_input_transition_function<
        T0
      , T1
      , T2
      , T3
    >::mdp_mapped_input_transition_function()
      : _transitions(), _inputs()
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    mdp_mapped_input_transition_function<
        T0
      , T1
      , T2
      , T3
    >::mdp_mapped_input_transition_function(
        mdp_mapped_input_transition_function const& copy
    ) : _transitions(copy._transitions), _inputs(copy._inputs)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    mdp_mapped_input_transition_function<T0,T1,T2,T3>&
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::operator=(
            mdp_mapped_input_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _transitions = copy._transitions;
            _inputs      = copy._inputs;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::recognizes_input(
            input const& i
        ) const
    {
        return _inputs.find(i) != _inputs.end();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::recognizes_state(
            state const s
        ) const
    {
        return s < _transitions.size();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline ::std::size_t
        mdp_mapped_input_transition_function<
            T0
          , T1
          , T2
          , T3
        >::get_state_count() const
    {
        return _transitions.size();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::is_nontrivial_input(
            state const current_state
          , input const& i
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));

        TransitionMap const& t_map = _transitions[current_state];
        return t_map.find(i) != t_map.end();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    template <typename Iterator>
    void
        mdp_mapped_input_transition_function<
            T0
          , T1
          , T2
          , T3
        >::make_nontrivial_inputs(
            state const current_state
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));

        TransitionMap const& t_map = _transitions[current_state];
        typename TransitionMap::const_iterator t_end = t_map.end();

        for (
            typename TransitionMap::const_iterator t_itr = t_map.begin();
            t_itr != t_end;
            ++t_itr
        )
        {
            *itr = t_itr->first;
            ++itr;
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    typename mdp_mapped_input_transition_function<
        T0
      , T1
      , T2
      , T3
    >::real_number
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::get_probability(
            state const current_state
          , input const& i
          , state const next_state
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));
        BOOST_ASSERT(recognizes_state(next_state));

        TransitionMap const& t_map = _transitions[current_state];
        typename TransitionMap::const_iterator map_itr = t_map.find(i);

        if (map_itr == t_map.end())
        {
            real_number const zero_value = initialized_value;
            return zero_value;
        }
        else
        {
            return map_itr->second[next_state];
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    template <typename RNGEngine>
    typename mdp_mapped_input_transition_function<
        T0
      , T1
      , T2
      , T3
    >::result_type
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::operator()(
            state& current_state
          , input const& i
          , RNGEngine& rng_engine
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));

        TransitionMap const& t_map = _transitions[current_state];
        typename TransitionMap::const_iterator map_itr = t_map.find(i);

        if (map_itr == t_map.end())
        {
            return false;
        }
        else
        {
            typedef ::std::tr1::uniform_real<real_number> Distribution;

            Probabilities const& probabilities = map_itr->second;
            Probabilities cumulative;
            real_number const zero_value = initialized_value;

            ::std::partial_sum(
                probabilities.begin()
              , probabilities.end()
              , std::back_inserter(cumulative)
            );

            ::std::tr1::variate_generator<RNGEngine&,Distribution> rng(
                rng_engine
              , Distribution(zero_value, cumulative.back())
            );
            current_state = ::std::distance(
                cumulative.begin()
              , std::lower_bound(cumulative.begin(), cumulative.end(), rng())
            );
            return true;
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    mdp_mapped_input_transition_function<T0,T1,T2,T3>::Setter::Setter(
        Probabilities& probabilities
      , mdp_mapped_input_transition_function& function
    ) : _probabilities(probabilities), _function(function)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    template <typename PairContainer>
    inline void
        mdp_mapped_input_transition_function<
            T0
          , T1
          , T2
          , T3
        >::Setter::operator+=(PairContainer const& container)
    {
        real_number const zero_value = initialized_value;
        typename PairContainer::const_iterator c_end = container.end();

        for (
            typename PairContainer::const_iterator c_itr = container.begin();
            c_itr != c_end;
            ++c_itr
        )
        {
            BOOST_ASSERT(_function.recognizes_state(c_itr->second));
            BOOST_ASSERT(zero_value < c_itr->second);
            _probabilities[c_itr->first] = c_itr->second;
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    typename mdp_mapped_input_transition_function<T0,T1,T2,T3>::Setter
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::operator()(
            state const current_state
          , input const& i
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));

        if (_inputs.find(i) == _inputs.end())
        {
            _inputs.insert(i);
        }

        TransitionMap& t_map = _transitions[current_state];
        typename TransitionMap::iterator t_itr = t_map.find(i);

        if (t_itr == t_map.end())
        {
            return Setter(
                t_map[i] = Probabilities(_transitions.size())
              , *this
            );
        }
        else
        {
            return Setter(t_itr->second, *this);
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    void
        mdp_mapped_input_transition_function<T0,T1,T2,T3>::reset(
            std::size_t state_count
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
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_MDP_MAPPED_INPUT_HPP_INCLUDED

