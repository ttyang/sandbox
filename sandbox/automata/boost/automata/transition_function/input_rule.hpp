// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_INPUT_RULE_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_INPUT_RULE_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/automata/tags/transition_function.hpp>

//[reference__input_rule_transition_function
namespace boost { namespace automata {
  //<-
  namespace _detail {

    template <typename State>
    struct in_place_input_rule_transition_function
    {
        template <typename InputRule>
        bool
            operator()(
                State& current_state
              , InputRule const& input_rule
            ) const;
    };

    template <typename State>
    template <typename InputRule>
    inline bool
        in_place_input_rule_transition_function<State>::operator()(
            State& current_state
          , InputRule const& input_rule
        ) const
    {
        return input_rule(current_state);
    }

    template <typename State>
    struct new_state_input_rule_transition_function
    {
        template <typename InputRule>
        State
            operator()(
                State const& current_state
              , InputRule const& input_rule
            ) const;
    };

    template <typename State>
    template <typename InputRule>
    inline State
        new_state_input_rule_transition_function<State>::operator()(
            State const& current_state
          , InputRule const& input_rule
        ) const
    {
        return input_rule(current_state);
    }
  }  // namespace _detail
  //->

    template <typename State, bool ModifiesInPlace = false>
    struct input_rule_transition_function
        //<-
      : ::boost::mpl::if_c<
            ModifiesInPlace
          , _detail::in_place_input_rule_transition_function<State>
          , _detail::new_state_input_rule_transition_function<State>
        >::type
        //->
    {
        typedef transition_function_tag
                tag;
        typedef // implementation_defined
                //<-
                typename ::boost::mpl::if_c<
                    ModifiesInPlace
                  , bool
                  , State
                >::type
                //->
                result_type;
        typedef State
                state;
    };
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_INPUT_RULE_HPP_INCLUDED

