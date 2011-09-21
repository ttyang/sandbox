// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_MEALY_OUTPUT_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_MEALY_OUTPUT_HPP_INCLUDED

#include <vector>
#include <iterator>
#include <iosfwd>
#include <sstream>
#include <boost/format.hpp>
#include <boost/automata/observer/output.hpp>

//[reference__mealy_output_policy
namespace boost { namespace automata {

    template <typename Functor>
    class mealy_output_policy
    {
        //<-
        Functor _output;
        //->

     public:
        mealy_output_policy();

        template <typename Function>
        mealy_output_policy(Function output);

        mealy_output_policy(mealy_output_policy const& copy);

        template <typename String>
        void process_string(String const& string);

        template <typename SubjectAutomaton>
        void process(SubjectAutomaton const& subject_automaton);

        template <typename SubjectAutomaton, typename Input>
        void
            process(SubjectAutomaton const& subject_automaton, Input const& i);

        void output();

        template <typename SubjectAutomaton>
        struct apply
        {
            typedef output_observer<mealy_output_policy,SubjectAutomaton> type;
        };
    };

    //<-
    template <typename Functor>
    mealy_output_policy<Functor>::mealy_output_policy() : _output()
    {
    }

    template <typename Functor>
    template <typename Function>
    mealy_output_policy<Functor>::mealy_output_policy(Function output)
      : _output(output)
    {
    }

    template <typename Functor>
    mealy_output_policy<Functor>::mealy_output_policy(
        mealy_output_policy const& copy
    ) : _output(copy._output)
    {
    }

    template <typename Functor>
    template <typename String>
    inline void
        mealy_output_policy<Functor>::process_string(String const& string)
    {
    }

    template <typename Functor>
    template <typename SubjectAutomaton>
    inline void
        mealy_output_policy<Functor>::process(
            SubjectAutomaton const& subject_automaton
        )
    {
    }

    template <typename Functor>
    template <typename SubjectAutomaton, typename Input>
    inline void
        mealy_output_policy<Functor>::process(
            SubjectAutomaton const& subject_automaton
          , Input const& i
        )
    {
        _output(subject_automaton, i);
    }

    template <typename Functor>
    inline void mealy_output_policy<Functor>::output()
    {
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_MEALY_OUTPUT_HPP_INCLUDED

