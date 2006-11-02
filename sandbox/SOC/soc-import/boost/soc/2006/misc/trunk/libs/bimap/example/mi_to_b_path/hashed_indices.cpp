// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.Bimap Example
//-----------------------------------------------------------------------------
// Hashed indices can be used as an alternative to ordered indices when fast
// lookup is needed and sorting information is of no interest. The example
// features a word counter where duplicate entries are checked by means of a 
// hashed index.


/********************************************************************************
Boost.MultiIndex
*********************************************************************************

// word_counter keeps the ocurrences of words inserted. A hashed
// index allows for fast checking of preexisting entries.

struct word_counter_entry
{
    std::string  word;
    unsigned int occurrences;

    word_counter_entry( std::string word_ ) : word(word_), occurrences(0) {}
};

typedef multi_index_container
<
    word_counter_entry,
    indexed_by
    <
        ordered_non_unique
        <
            BOOST_MULTI_INDEX_MEMBER(word_counter_entry,unsigned int,occurrences),
            std::greater<unsigned int>
        >,
        hashed_unique
        <
            BOOST_MULTI_INDEX_MEMBER(word_counter_entry,std::string,word)
        >
  >

> word_counter;

typedef boost::tokenizer<boost::char_separator<char> > text_tokenizer;

int main()
{

    std::string text=
        "En un lugar de la Mancha, de cuyo nombre no quiero acordarme... "
        "...snip..."
        "...no se salga un punto de la verdad.";

    // feed the text into the container

    word_counter   wc;
    text_tokenizer tok(text,boost::char_separator<char>(" \t\n.,;:!?'\"-"));
    unsigned int   total_occurrences = 0;

    for( text_tokenizer::iterator it = tok.begin(), it_end = tok.end();
         it != it_end ; ++it )
    {
        ++total_occurrences;
        word_counter::iterator wit = wc.insert(*it).first;
        wc.modify_key(wit,++_1);
    }

    // list words by frequency of appearance

    std::cout << std::fixed << std::setprecision(2);

    for( word_counter::iterator wit = wc.begin(), wit_end=wc.end();
         wit != wit_end; ++wit )
    {
        std::cout << std::setw(11) << wit->word << ": "
                  << std::setw(5)
                  << 100.0 * wit->occurrences / total_occurrences << "%"
                  << std::endl;
    }

    return 0;
}

******************************************************************************/


/******************************************************************************
Boost.Bimap
******************************************************************************/


typedef bimap
<
    tagged< std::string, word >,
    tagged
    <
        multi_set_of
        <
            unsigned int,
            std::greater<unsigned int>
        >,
        occurrences
    >

> word_counter;

typedef boost::tokenizer<boost::char_separator<char> > text_tokenizer;

int main()
{

    std::string text=
        "Relations between data in the STL are represented with maps."
        "A map is a directed relation, by using it you are representing"
        "a mapping. In this directed relation, the first type is related to"
        "the second type but it is not true that the inverse relationship"
        "holds. This is useful in a lot of situations, but there are some"
        "relationships that are bidirectional by nature.";

    // feed the text into the container

    word_counter   wc;
    text_tokenizer tok(text,boost::char_separator<char>(" \t\n.,;:!?'\"-"));
    unsigned int   total_occurrences = 0;

    for( text_tokenizer::iterator it = tok.begin(), it_end = tok.end();
         it != it_end ; ++it )
    {
        ++total_occurrences;
        ++map_by<word>(wc)[*it];
    }

    // list words by frequency of appearance

    std::cout << std::fixed << std::setprecision(2);

    typedef iterator_type_by<occurrences,word_counter>::type iterator;

    for( iterator wit     = map_by<occurrences>(wc).begin(),
                  wit_end = map_by<occurrences>(wc).end();

         wit != wit_end; ++wit )
    {
        std::cout << std::setw(11) << get<word>(*wit) << ": "
                  << std::setw(5)
                  << 100.0 * get<occurrences>(*wit) / total_occurrences << "%"
                  << std::endl;
    }

    return 0;
}

