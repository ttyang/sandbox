// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TAGS_BASE_HPP_INCLUDED
#define BOOST_AUTOMATA_TAGS_BASE_HPP_INCLUDED

namespace boost { namespace automata {

    struct automaton_base_tag
    {
    };

    struct discrete_automaton_base_tag
      : automaton_base_tag
    {
    };

    struct input_enumerable_automaton_base_tag
      : discrete_automaton_base_tag
    {
    };
}}  // namespace boost::automata

#endif  // BOOST_AUTOMATA_TAGS_BASE_HPP_INCLUDED

