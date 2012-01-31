//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <iostream>
#include <string>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/utility/associative_container_gen.hpp>

//[example__output_char_tallies__definition
template <typename Selector>
void output_char_tallies(std::string const& str, Selector)
{
    typedef typename boost::mpl::apply_wrap2<
                boost::associative_container_gen<Selector>
              , char
              , std::size_t
            >::type
            FrequencyTable;

    FrequencyTable freq_table;
    char reverse_counter = 0;

    for (std::size_t i = 0; i < str.size(); ++i)
    {
        typename FrequencyTable::iterator ft_itr = freq_table.find(str[i]);

        if (ft_itr == freq_table.end())
        {
            freq_table.insert(typename FrequencyTable::value_type(str[i], 1));
        }
        else
        {
            ++ft_itr->second;
        }
    }

    for (
        typename FrequencyTable::const_iterator ft_itr = freq_table.begin();
        ft_itr != freq_table.end();
        ++ft_itr
    )
    {
        std::cout << ft_itr->first << ": " << ft_itr->second << std::endl;
    }

    std::cout << std::endl;
}
//]

//[example__output_char_tallies__calls
int main(int, char**)
{
    output_char_tallies("abacadabra", boost::hash_mapS());
    output_char_tallies("loolapalooza", boost::multimapS());
    return 0;
}
//]

