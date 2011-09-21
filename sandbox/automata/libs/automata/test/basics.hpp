// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_TEST_BASICS_HPP_INCLUDED
#define LIBS_AUTOMATA_TEST_BASICS_HPP_INCLUDED

#include <string>

//[test__accept__function_template
template <typename DPDA>
bool accept(DPDA& dpda, std::string const& word)
{
    std::size_t i = 0;

    while (i < word.length())
    {
        if (dpda(word[i]))
        {
            ++i;
        }
        else
        {
            return false;
        }
    }

    return dpda.has_empty_stack();
}
//]

#endif  // LIBS_AUTOMATA_TEST_BASICS_HPP_INCLUDED

