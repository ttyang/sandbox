
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/string.hpp>

int main()
{
    std::string const volatile s;
    BOOST_SCOPE_EXIT( (&s) )
    {
        s = "";
    } BOOST_SCOPE_EXIT_END
}

