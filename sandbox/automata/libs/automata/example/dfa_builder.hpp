// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_DFA_BUILDER_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_DFA_BUILDER_HPP_INCLUDED

#include <string>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/automata/keys/observer.hpp>
#include <boost/automata/transition_function/matrix.hpp>
#include <boost/automata/transition_function/mapped_input_tabular.hpp>
#include <boost/automata/transition_function/mapped_input.hpp>
#include <boost/automata/transition_function/next_state.hpp>

//[example__dfa_builder__function_types
typedef boost::automata::matrix_transition_function<
            boost::numeric::ublas::matrix<std::size_t>
        >
        Function0;
typedef boost::automata::mapped_input_tabular_transition_function<
            std::string
          , Function0
        >
        Function1;
//<-
typedef boost::automata::mapped_input_transition_function<std::string>
        Function2;
//->
typedef boost::automata::next_state_transition_function<>
        Function3;
//]

//[example__dfa_builder__class
class sample_dfa_builder
{
    struct single_final_state_builder
    {
        std::size_t get_final_state() const;
    };

    struct multiple_final_states_builder
    {
        template <typename States>
        void make_final_states(States& states) const
        {
            states.insert(2);
            states.insert(5);
        }
    };

 public:
    typedef boost::fusion::map<
                boost::fusion::pair<
                    boost::automata::single_final_state_key<>
                  , single_final_state_builder
                >
              , boost::fusion::pair<
                    boost::automata::multiple_final_states_key<>
                  , multiple_final_states_builder
                >
            >
            observer_builder_map;

 private:
    observer_builder_map _map;

 public:
    sample_dfa_builder();
    observer_builder_map const& get_observer_builder_map() const;
    //<-
    void operator()(Function0& function) const;
    //->
    void operator()(Function1& function) const;
    //<-
    void operator()(Function2& function) const;
    //->
    void operator()(Function3& function) const;
};
//]

#endif  // LIBS_AUTOMATA_EXAMPLE_DFA_BUILDER_HPP_INCLUDED

