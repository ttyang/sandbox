// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_GENERATOR_PROBABILISTIC_HPP_INCLUDED
#define BOOST_AUTOMATA_GENERATOR_PROBABILISTIC_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/tags/base.hpp>

//[reference__probabiistic_generator
namespace boost { namespace automata {

    template <typename RNGEngine>
    struct probabilistic_generator
    {
        template <typename Function>
        struct apply
        {
            class type
            {
                RNGEngine _rng_engine;

             protected:
                typedef typename ::boost::mpl::if_<
                            ::std::tr1::is_base_of<
                                mdp_transition_function_tag
                              , typename Function::tag
                            >
                          , input_enumerable_automaton_base_tag
                          , automaton_base_tag
                        >::type
                        tag;
                typedef void
                        traits;

                void reset_impl();

                template <typename Input>
                static bool
                    is_nontrivial_input_impl(
                        Function const& function
                      , typename Function::state const& current_state
                      , Input const& i
                    );

                template <typename Iterator>
                static void
                    make_nontrivial_inputs_impl(
                        Function const& function
                      , typename Function::state const& current_state
                      , Iterator itr
                    );

                template <typename Input>
                bool
                    process_input_impl(
                        Function const& function
                      , typename Function::state& current_state
                      , Input const& i
                    );

             public:
                template <typename T>
                void seed(T t);

                template <typename Iterator>
                void seed(Iterator& first, Iterator last);
            };
        };
    };

    //<-
    template <typename RNGEngine>
    template <typename Function>
    template <typename T>
    inline void
        probabilistic_generator<RNGEngine>::apply<Function>::type::seed(T t)
    {
        _rng_engine.seed(t);
    }

    template <typename RNGEngine>
    template <typename Function>
    template <typename Iterator>
    inline void
        probabilistic_generator<RNGEngine>::apply<Function>::type::seed(
            Iterator& first
          , Iterator last
        )
    {
        _rng_engine.seed(first, last);
    }

    template <typename RNGEngine>
    template <typename Function>
    inline void
        probabilistic_generator<RNGEngine>::apply<Function>::type::reset_impl()
    {
        _rng_engine.seed();
    }

    template <typename RNGEngine>
    template <typename Function>
    template <typename Input>
    inline bool
        probabilistic_generator<RNGEngine>::apply<
            Function
        >::type::is_nontrivial_input_impl(
            Function const& function
          , typename Function::state const& current_state
          , Input const& i
        )
    {
        return function.is_nontrivial_input(current_state, i);
    }

    template <typename RNGEngine>
    template <typename Function>
    template <typename Iterator>
    inline void
        probabilistic_generator<RNGEngine>::apply<
            Function
        >::type::make_nontrivial_inputs_impl(
            Function const& function
          , typename Function::state const& current_state
          , Iterator itr
        )
    {
        function.make_nontrivial_inputs(current_state, itr);
    }

    template <typename RNGEngine>
    template <typename Function>
    template <typename Input>
    inline bool
        probabilistic_generator<RNGEngine>::apply<
            Function
        >::type::process_input_impl(
            Function const& function
          , typename Function::state& current_state
          , Input const& i
        )
    {
        return function(current_state, i, _rng_engine);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_GENERATOR_PROBABILISTIC_HPP_INCLUDED

