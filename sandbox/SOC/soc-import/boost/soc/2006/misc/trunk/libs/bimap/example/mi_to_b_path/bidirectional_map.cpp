// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.Bimap Example
//-----------------------------------------------------------------------------
// This example shows how to construct a bidirectional map with multi_index_container.
// By a bidirectional map we mean a container of elements of
// std::pair<const FromType,const ToType> such that no two elements exists with the
// same first or second value (std::map only guarantees uniqueness of the first member).
// Fast lookup is provided for both keys. The program features a tiny Spanish-English
// dictionary with online query of words in both languages.


/***************************************************************************************
Boost.MultiIndex
****************************************************************************************

// tags for accessing both sides of a bidirectional map

struct from {};
struct to   {};

// The class template bidirectional_map wraps the specification
// of a bidirectional map based on multi_index_container.

template<typename FromType,typename ToType>
struct bidirectional_map
{
    typedef std::pair<FromType,ToType> value_type;

    typedef multi_index_container<
        value_type,
        indexed_by
        <
            ordered_unique
            <
                tag<from>, member<value_type,FromType,&value_type::first>
            >,
            ordered_unique
            <
                tag<to>, member<value_type,ToType,&value_type::second>
            >
        >

  > type;

};

// A dictionary is a bidirectional map from strings to strings

typedef bidirectional_map<std::string,std::string>::type dictionary;

int main()
{
    dictionary d;

    // Fill up our microdictionary. first members Spanish, second members English.

    d.insert(dictionary::value_type("hola","hello"));
    d.insert(dictionary::value_type("adios","goodbye"));
    d.insert(dictionary::value_type("rosa","rose"));
    d.insert(dictionary::value_type("mesa","table"));

    std::cout << "enter a word" << std::endl;
    std::string word;
    std::getline(std::cin,word);

    // search the queried word on the from index (Spanish)

    dictionary::iterator it = d.get<from>().find(word);

    if( it != d.end() )
    {
        // the second part of the element is the equivalent in English

        std::cout << word << " is said " << it->second << " in English" << std::endl;
    }
    else
    {
        // word not found in Spanish, try our luck in English

        dictionary::index_iterator<to>::type it2 = d.get<to>().find(word);
        if( it2 != d.get<to>().end() )
        {
            std::cout << word << " is said " << it2->first << " in Spanish" << std::endl;
        }
        else
        {
            std::cout << "No such word in the dictionary" << std::endl;
        }
    }

    return 0;
}

********************************************************************************/



/********************************************************************************
Boost.Bimap
********************************************************************************/


// A dictionary is a bidirectional map from strings to strings

typedef bimap<std::string,std::string> dictionary;
typedef dictionary::relation translation;

int main()
{
    dictionary d;

    // Fill up our microdictionary. first members Spanish, second members English.

    d.insert(translation("hola","hello"));
    d.insert(translation("adios","goodbye"));
    d.insert(translation("rosa","rose"));
    d.insert(translation("mesa","table"));

    std::cout << "enter a word" << std::endl;
    std::string word;
    std::getline(std::cin,word);

    // search the queried word on the from index (Spanish) */

    iterator_type_by<member_at::left,dictionary>::type it = map_by<member_at::left>(d).find(word);

    if( it != map_by<member_at::left>(d).end() )
    {
        // the second part of the element is the equivalent in English

        std::cout << word << " is said " << it->second << " in English" << std::endl;
    }
    else
    {
        // word not found in Spanish, try our luck in English

        iterator_type_by<member_at::right,dictionary>::type it2 = map_by<member_at::right>(d).find(word);
        if( it2 != map_by<member_at::right>(d).end() )
        {
            std::cout << word << " is said " << it2->first << " in Spanish" << std::endl;
        }
        else
        {
            std::cout << "No such word in the dictionary" << std::endl;
        }
    }

    return 0;
}
