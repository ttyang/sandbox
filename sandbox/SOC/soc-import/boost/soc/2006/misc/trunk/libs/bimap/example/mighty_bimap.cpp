// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.Bimap Example
//-----------------------------------------------------------------------------
// This is the translator example from the tutorial.
// In this example the set type of relation is changed to allow the iteration
// of the container.


#include <iostream>
#include <string>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>

struct english {};
struct spanish {};

int main()
{
    using namespace boost::bimap;

    typedef bimap
    <
        tagged< unordered_set_of< std::string >, spanish >,
        tagged< unordered_set_of< std::string >, english >,
        list_of_relation

    > translator_bimap;

    typedef translator_bimap::relation translation;
    translator_bimap translator;
    translator.insert( translation("hola"  ,"hello"   ) );
    translator.insert( translation("adios" ,"goodbye" ) );
    translator.insert( translation("rosa"  ,"rose"    ) );
    translator.insert( translation("mesa"  ,"table"   ) );

    std::cout << "enter a word" << std::endl;
    std::string word;
    std::getline(std::cin,word);

    // Search the queried word on the from index (Spanish) */

    iterator_type_by<spanish,translator_bimap>::type is = map_by<spanish>(d).find(word);

    if( is != map_by<spanish>(d).end() )
    {
        std::cout << word << " is said " << get<english>(*is) << " in English" << std::endl;
    }
    else
    {
        // Word not found in Spanish, try our luck in English

        iterator_type_by<english,translator_bimap>::type ie = map_by<english>(d).find(word);
        if( ie != map_by<english>(d).end() )
        {
            std::cout << word << " is said " << get<spanish>(*ie) << " in Spanish" << std::endl;
        }
        else
        {
            // Word not found, show the possible translations

            std::cout << "No such word in the dictionary" << std::endl;
            std::cout << "These are the possible translations" << std::endl;
            for( translator_bimap::iterator i = translator.begin(), i_end = translator.end();
                    i != i_end ; ++i )
            {
                std::cout << get<spanish>(*i) << " <---> " << get<english>(*i) << std::endl;
            }
        }
    }
    return 0;
}
