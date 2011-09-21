// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_GENERATOR_DETERMINISTIC_HPP_INCLUDED
#define BOOST_AUTOMATA_GENERATOR_DETERMINISTIC_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/tags/base.hpp>

//[reference__deterministic_generator
namespace boost { namespace automata {
  //<-
  namespace _detail {

    template <typename Tag>
    struct deterministic_state_1
    {
        template <typename Function, typename Input>
        static inline void
            evaluate(
                typename Function::state& state
              , Function const& function
              , Input const& i
            )
        {
            state = function(state, i);
        }
    };

    template <>
    struct deterministic_state_1<combinatorial_transition_function_tag>
    {
        template <typename Function, typename Input>
        static inline void
            evaluate(
                typename Function::state& state
              , Function const& function
              , Input const& i
            )
        {
            state = function(i);
        }
    };

    template <typename IsComplexState>
    struct deterministic_state_2
    {
        template <typename Function, typename Input>
        static inline bool
            evaluate(
                typename Function::state& state
              , Function const& function
              , Input const& i
            )
        {
            return function(state, i);
        }
    };

    template <>
    struct deterministic_state_2< ::std::tr1::false_type>
    {
        template <typename Function, typename Input>
        static inline bool
            evaluate(
                typename Function::state& state
              , Function const& function
              , Input const& i
            )
        {
            deterministic_state_1<typename Function::tag>::evaluate(
                state
              , function
              , i
            );
            return true;
        }
    };
  }  // namespace _detail
  //->

    struct deterministic_generator
    {
        template <typename Function>
        struct apply
        {
            struct type
            {
             protected:
                typedef automaton_base_tag tag;
                typedef void               traits;

                static void reset_impl();

                template <typename Input>
                static bool
                    process_input_impl(
                        Function const& function
                      , typename Function::state& current_state
                      , Input const& i
                    );
            };
        };
    };

    //<-
    template <typename Function>
    inline void
        deterministic_generator::apply<Function>::type::reset_impl()
    {
    }

    template <typename Function>
    template <typename Input>
    inline bool
        deterministic_generator::apply<Function>::type::process_input_impl(
            Function const& function
          , typename Function::state& current_state
          , Input const& i
        )
    {
        typedef typename Function::result_type r_type;

        return _detail::deterministic_state_2<
            typename ::boost::mpl::if_<
                ::std::tr1::is_same<r_type,typename Function::state>
              , ::std::tr1::false_type
              , ::std::tr1::is_same<r_type,bool>
            >::type
        >::evaluate(current_state, function, i);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_GENERATOR_DETERMINISTIC_HPP_INCLUDED

