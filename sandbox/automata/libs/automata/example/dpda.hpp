// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_DPDA_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_DPDA_HPP_INCLUDED

#include <iostream>
#include <string>
#include "../test/basics.hpp"

template <typename DPDA>
void test(DPDA& dpda, std::string const& word)
{
    if (accept(dpda, word))
    {
        std::cout << word << " accepted." << std::endl;
    }
    else
    {
        std::cout << word << " rejected." << std::endl;
    }
}

#endif  // LIBS_AUTOMATA_EXAMPLE_DPDA_HPP_INCLUDED

