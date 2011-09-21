// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_MDP_BEST_INPUT_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_MDP_BEST_INPUT_HPP_INCLUDED

#include <iterator>
#include <vector>
#include <boost/config.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/function.hpp>
#include <boost/automata/tags/builder.hpp>
#include <boost/automata/observer/base.hpp>

//[reference__mdp_best_input_policy
namespace boost { namespace automata {

    template <typename Input, typename RealNumber = double>
    class mdp_best_input_policy
    {
        //<-
        ::boost::function3<
            RealNumber
          , ::std::size_t
          , Input const&
          , ::std::size_t
        > _reward;
        RealNumber _discount_rate;
        //->

     public:
        template <typename Function>
        mdp_best_input_policy(
            Function function
          , RealNumber const& discount_rate = RealNumber()
        );

        mdp_best_input_policy(mdp_best_input_policy const& copy);

        template <typename SubjectAutomaton>
        struct apply
        {
            class type : public base_observer<SubjectAutomaton>
            {
                //<-
                mdp_best_input_policy _policy;
                ::std::vector<Input> _best_inputs;
                //->

             public:
                type(
                    mdp_best_input_policy const& policy
                  , SubjectAutomaton const& automaton
                )
                //<-
                  : base_observer<SubjectAutomaton>(automaton)
                  , _policy(policy)
                  , _best_inputs()
                {
                }
                //->
                ;

                type(
                    type const& copy
                  , SubjectAutomaton const& automaton
                )
                //<-
                  : base_observer<SubjectAutomaton>(automaton)
                  , _policy(copy._policy)
                  , _best_inputs(copy._best_inputs)
                {
                }
                //->
                ;

                type(type const& copy)
                //<-
                  : base_observer<SubjectAutomaton>(
                        copy.get_subject_automaton()
                    )
                  , _policy(copy._policy)
                  , _best_inputs(copy._best_inputs)
                {
                }
                //->
                ;

                type& operator=(type const& copy)
                //<-
                {
                    return *this;
                }
                //->
                ;

                //<-
                inline
                //->
                Input const& get_current_best() const
                //<-
                {
                    return _best_inputs[
                        this->get_subject_automaton().get_current_state()
                    ];
                }
                //->
                ;

                template <typename Builder>
                //<-
                inline
                //->
                void
                    on_construction(
                        Builder const& builder
                      , function_setter_tag
                    )
                //<-
                {
                    _precompute();
                }
                //->
                ;

                template <typename Builder>
                //<-
                inline
                //->
                void
                    on_construction(
                        Builder const& builder
                      , function_builder_tag
                    )
                //<-
                {
                    _precompute();
                }
                //->
                ;

                template <typename Builder>
                //<-
                inline
                //->
                void
                    on_construction(
                        Builder const& builder
                      , state_and_function_builder_tag
                    )
                //<-
                {
                    _precompute();
                }
                //->
                ;

                template <typename Builder>
                //<-
                inline
                //->
                void
                    on_initialize(
                        Builder const& builder
                      , function_setter_tag
                    )
                //<-
                {
                    _precompute();
                }
                //->
                ;

                template <typename Builder>
                //<-
                inline
                //->
                void
                    on_initialize(
                        Builder const& builder
                      , function_builder_tag
                    )
                //<-
                {
                    _precompute();
                }
                //->
                ;

                template <typename Builder>
                //<-
                inline
                //->
                void
                    on_initialize(
                        Builder const& builder
                      , state_and_function_builder_tag
                    )
                //<-
                {
                    _precompute();
                }
                //->
                ;

                //<-
             private:
                void _precompute();
                //->
            };
        };
    };

    //<-
    template <typename Input, typename RealNumber>
    template <typename Function>
    mdp_best_input_policy<Input,RealNumber>::mdp_best_input_policy(
        Function function
      , RealNumber const& discount_rate
    ) : _reward(function), _discount_rate(discount_rate)
    {
    }

    template <typename Input, typename RealNumber>
    mdp_best_input_policy<Input,RealNumber>::mdp_best_input_policy(
        mdp_best_input_policy const& copy
    ) : _reward(copy._reward), _discount_rate(copy._discount_rate)
    {
    }

    template <typename Input, typename RealNumber>
    template <typename SubjectAutomaton>
    void
        mdp_best_input_policy<Input,RealNumber>::apply<
            SubjectAutomaton
        >::type::_precompute()
    {
        typename SubjectAutomaton::transition_function const&
            f = this->get_subject_automaton().get_transition_function();
        ::std::size_t const state_count = f.get_state_count();
        Input const zero_input = initialized_value;

        ::std::vector<Input> inputs;

        _best_inputs.resize(state_count, zero_input);

        for (::std::size_t s = 0; s < state_count; ++s)
        {
            inputs.clear();
            f.make_nontrivial_inputs(s, ::std::back_inserter(inputs));

            if (!inputs.empty())
            {
                RealNumber max_sum = initialized_value;

                for (::std::size_t i = 0; i < inputs.size(); ++i)
                {
                    Input const& input = inputs[i];

                    RealNumber sum = initialized_value;

                    for (
                        ::std::size_t s_tick = 0;
                        s_tick < state_count;
                        ++s_tick
                    )
                    {
                        sum
                         += _policy._reward(s, input, s_tick)
                          * f.get_probability(s, input, s_tick);
                    }

                    if (max_sum < sum)
                    {
                        _best_inputs[s] = input;
                        max_sum = sum;
                    }
                }
            }
        }

        RealNumber const& discount_rate = _policy._discount_rate;

        ::std::vector<RealNumber> values(state_count);
        bool is_not_done;

        do
        {
            for (;;)
            {
                ::std::vector<RealNumber> new_values(state_count);
                bool has_converged = true;

                for (::std::size_t s = 0; s < state_count; ++s)
                {
                    Input const& input = _best_inputs[s];

                    new_values[s] = initialized_value;

                    for (
                        ::std::size_t s_tick = 0;
                        s_tick < state_count;
                        ++s_tick
                    )
                    {
                        new_values[s] += (
                            values[s_tick] * discount_rate
                          + _policy._reward(s, input, s_tick)
                        ) * f.get_probability(s, input, s_tick);
                    }

                    if (
                        (new_values[s] < values[s])
                     || (values[s] < new_values[s])
                    )
                    {
                        has_converged = false;
                    }
                }

                if (has_converged)
                {
                    break;
                }
                else
                {
                    values = new_values;
                }
            }

            is_not_done = false;

            for (::std::size_t s = 0; s < state_count; ++s)
            {
                inputs.clear();
                f.make_nontrivial_inputs(s, ::std::back_inserter(inputs));

                if (!inputs.empty())
                {
                    Input best_input = inputs[0];
                    RealNumber max_sum = initialized_value;

                    for (::std::size_t i = 0; i < inputs.size(); ++i)
                    {
                        Input const& input = inputs[i];

                        RealNumber sum = initialized_value;

                        for (
                            ::std::size_t s_tick = 0;
                            s_tick < state_count;
                            ++s_tick
                        )
                        {
                            sum += (
                                values[s_tick] * discount_rate
                              + _policy._reward(s, input, s_tick)
                            ) * f.get_probability(s, input, s_tick);
                        }

                        if (max_sum < sum)
                        {
                            best_input = inputs[i];
                            max_sum = sum;
                        }
                    }

                    if (best_input != _best_inputs[s])
                    {
                        is_not_done = true;
                        _best_inputs[s] = best_input;
                    }
                }
            }
        }
        while (is_not_done);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_MDP_BEST_INPUT_HPP_INCLUDED

