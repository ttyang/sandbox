// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_MOORE_OUTPUT_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_MOORE_OUTPUT_HPP_INCLUDED

#include <vector>
#include <iterator>
#include <iosfwd>
#include <sstream>
#include <boost/format.hpp>
#include <boost/automata/observer/output.hpp>

//[reference__moore_output_policy
namespace boost { namespace automata {

    template <typename Functor>
    class moore_output_policy
    {
        //<-
        Functor _output;
        //->

     public:
        moore_output_policy();

        template <typename Function>
        moore_output_policy(Function output);

        moore_output_policy(moore_output_policy const& copy);

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
            typedef output_observer<moore_output_policy,SubjectAutomaton> type;
        };
    };

    //<-
    template <typename Functor>
    moore_output_policy<Functor>::moore_output_policy() : _output()
    {
    }

    template <typename Functor>
    template <typename Function>
    moore_output_policy<Functor>::moore_output_policy(Function output)
      : _output(output)
    {
    }

    template <typename Functor>
    moore_output_policy<Functor>::moore_output_policy(
        moore_output_policy const& copy
    ) : _output(copy._output)
    {
    }

    template <typename Functor>
    template <typename String>
    inline void
        moore_output_policy<Functor>::process_string(String const& string)
    {
    }

    template <typename Functor>
    template <typename SubjectAutomaton>
    inline void
        moore_output_policy<Functor>::process(
            SubjectAutomaton const& subject_automaton
        )
    {
        _output(subject_automaton);
    }

    template <typename Functor>
    template <typename SubjectAutomaton, typename Input>
    inline void
        moore_output_policy<Functor>::process(
            SubjectAutomaton const& subject_automaton
          , Input const& i
        )
    {
        _output(subject_automaton);
    }

    template <typename Functor>
    inline void moore_output_policy<Functor>::output()
    {
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_MOORE_OUTPUT_HPP_INCLUDED

