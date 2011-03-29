// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_UNICODE_READ_CHARACTER_PROPERTIES_HPP_INCLUDED
#define BOOST_UNICODE_READ_CHARACTER_PROPERTIES_HPP_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <ostream>
#include <iterator>
#include <boost/spirit/include/classic.hpp>

#include <boost/unicode/ucd/properties_types.hpp>
#include "../src/ucd/unichar_data.hpp"

namespace boost
{

	namespace unicode
	{

		namespace ucd
		{
			struct read_block
			{
				char32 first;
				char32 last;
				std::string name;
			};

			void read_blocks (std::vector <read_block> & block);

			struct complex_casing
			{
				// There are two extra problems with case-mapping: conditions
				// and locales.
				// As long as locales aren't supported, the only condition is
				// Final_Sigma. That'd better be coded explicitly.
				std::vector <char32> complex_uppercase;
				std::vector <char32> complex_lowercase;
				std::vector <char32> complex_titlecase;
				// TODO: condition
				// TODO: locale
			};

            // primitive structure compared with memcmp
            struct collation_data
			{
                bool        variable;
				uint16_t    weight1;
				uint16_t    weight2;
                uint16_t    weight3;
                uint32_t    weight4;

                collation_data()    {   variable = false;   weight1 = 0;
                                        weight2 = 0; weight3 = 0; weight4 = 0;  };
                                        
                bool operator==(const collation_data& other) const
                {
                    return variable == other.variable
                       &&  weight1 == other.weight1
                       &&  weight2 == other.weight2
                       &&  weight3 == other.weight3
                       &&  weight4 == other.weight4;
                }
                
                bool operator!=(const collation_data& other) const
                {
                    return !operator==(other);
                }
			};

            struct collation_entry
			{
                std::vector<char32>       following_chars;
				std::vector<collation_data>  data;
			};

			struct character_properties
			{
				std::string					 name;
				category::type				 general_category;
				int							 combining;
				bidi_class::type			 bidi;
				decomposition_type::type	 decomposition_kind;
				std::vector <char32>		 decomposition;
                grapheme_cluster_break::type grapheme_break;
                word_break::type             word_break_kind;
                sentence_break::type         sentence_break_kind;
				bool						 written_by_block;
				bool						 unknown_char;
                bool                         sort_variable;
                sort_type::type              sort_type_;
                uint16_t                     sort_index_or_data1;
                uint16_t                     sort_data2;
                // complex sort data is only relevant for sort type indexed
                std::vector<collation_entry> sort_data;

				// simple uppercase, lowercase and titlecase
				char32					uppercase;
				char32					lowercase;
				char32					titlecase;

				std::vector <complex_casing> complex_case;

				line_break::type			line_break_;
#ifdef BOOST_UNICODE_UCD_BIG
				join_type::type				joining;
#endif
                
                bool                        comp_ex;

				enum	{ CHARACTER_DOES_NOT_EXIST = 0x400000	};

				// ensure that values are initialised to invalid values so we know they have not yet been set
				character_properties()
				:
					general_category (category::type (-1)),
					combining (-1),
					bidi (bidi_class::type (-1)),
					decomposition_kind (decomposition_type::type (-1)),
                    grapheme_break (grapheme_cluster_break::any),
                    word_break_kind (word_break::any),
                    sentence_break_kind (sentence_break::any),
					written_by_block (false),
					unknown_char (false),
                    sort_variable(false),
                    sort_type_(sort_type::default_),
                    sort_index_or_data1(0),
                    sort_data2(0),
					uppercase (0),
					lowercase (0),
					titlecase (0),
                    line_break_(line_break::type (-1)),
#ifdef BOOST_UNICODE_UCD_BIG
                    joining (join_type::none),
#endif
                    comp_ex (false)
				{}
			};

			/**
			Read the character properties from the Unicode data files.
			Works on the console; may throw if an error occurs.
			*/
			void read_character_properties (
				std::map <char32, character_properties> & prop);

		}	// namespace ucd

	}	// namespace unicode

}	// namespace boost

template<typename T>
struct warning_assign_a_type
{
    warning_assign_a_type(T& name_, T value_) : name(name_), value(value_)
    {
    }
    
    template<typename Iterator>
    void operator()(Iterator begin, Iterator end) const
    {
        std::cout << "\nWarning: unsupported property value ";
        std::copy(begin, end, std::ostream_iterator<char>(std::cout));
        std::cout << std::flush;
        name = value;
    }
    
    T& name;
    T value;
};

template<typename T>
warning_assign_a_type<T> warning_assign_a(T& name, T value)
{
    return warning_assign_a_type<T>(name, value);
}

struct identifier_p : 
    boost::spirit::classic::sequence<
        boost::spirit::classic::strlit<char const*>,
        boost::spirit::classic::empty_match_parser<
            boost::spirit::classic::negated_char_parser<
                boost::spirit::classic::alnum_parser
            >
        >
    >
{
private:
    typedef boost::spirit::classic::sequence<
        boost::spirit::classic::strlit<char const*>,
        boost::spirit::classic::empty_match_parser<
            boost::spirit::classic::negated_char_parser<
                boost::spirit::classic::alnum_parser
            >
        >
    > base_t;
    
    base_t definition(const char* name)
    {
        using namespace boost::spirit::classic;
        return str_p(name) >> eps_p(~alnum_p);
    }

public:
    identifier_p(char const* name) : base_t(definition(name))
    {
    }
};

#endif	// BOOST_UNICODE_READ_CHARACTER_PROPERTIES_HPP_INCLUDED