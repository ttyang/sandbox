// Read Unicode character properties from the database.
// Though this file is under the Boost license, it is NOT (or not yet) part of
// Boost!

// Copyright Graham Barnett, Rogier van Dalen 2005.
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/spirit/include/classic.hpp>
#include <boost/lambda/lambda.hpp>

#include "read_character_properties.hpp"
#include "read_character_properties_files.hpp"

using namespace boost::spirit::classic;
using namespace boost::unicode;
using namespace boost::unicode::ucd;
using namespace boost::lambda;

using boost::char32;

namespace boost { namespace unicode { namespace ucd {

const int PROGRESS_INDICATION_EVERY  = 200;

void read_character_properties_sentence (
	                std::map <char32, character_properties> & props, 
                                    const char* filename, bool required)
{
	std::cout << "+Reading sentence data from " << filename << "\n";

	parse_info <file_iterator<> > info;
	file_iterator<> curr, last;

	try
	{
		curr = get_file_iterator (filename);
	}
	catch (file_read_error)
	{
		if (required)
		{
			throw;
		}
		else
		{
			std::cout << "-Reading sentence data from optional file - not present\n";
			return;
		}
	}
	last = curr.make_end();

	eat_comments (curr, last);

	int progress = PROGRESS_INDICATION_EVERY;
	std::cout << " ";

	do
	{
		char32 first_code;
		char32 last_code;
        sentence_break::type sentence;

		// The line being decoded is formatted as:
		// Start Code..End Code; Type
        // or 
        // Code                ; Type
		// e.g. 
		// 0600..0603    ; Format
        // 06DD          ; Format

		info = parse (curr, last,
            (
            // start code
			(hex_p [assign_a (first_code)] >> ".." >>
			// end code
			hex_p [assign_a (last_code)])
            |
            // single code
            (hex_p [assign_a (first_code)][assign_a (last_code)])
            )
            >> ';' >>
			// block name
			// type of break
		    (identifier_p ("Sep")
			    [assign_a (sentence,
				    sentence_break::sep)] |
	        identifier_p ("Format")
			    [assign_a (sentence,
				    sentence_break::format)] |
            identifier_p ("Sp")
			    [assign_a (sentence,
				    sentence_break::sp)] |
            identifier_p ("Lower")
			    [assign_a (sentence,
				    sentence_break::lower)] |
            identifier_p ("Upper")
			    [assign_a (sentence,
				    sentence_break::upper)] |
            identifier_p ("OLetter")
			    [assign_a (sentence,
				    sentence_break::oletter)] |
            identifier_p ("Numeric")
			    [assign_a (sentence,
				    sentence_break::numeric)] |
            identifier_p ("ATerm")
			    [assign_a (sentence,
				    sentence_break::aterm)] |
            identifier_p ("STerm")
			    [assign_a (sentence,
				    sentence_break::sterm)] |
            identifier_p ("Close")
			    [assign_a (sentence,
				    sentence_break::close)] |
            identifier_p ("CR")
			    [assign_a (sentence,
				    sentence_break::cr)] |
            identifier_p ("LF")
			    [assign_a (sentence,
				    sentence_break::lf)] |
            identifier_p ("Extend")
			    [assign_a (sentence,
				    sentence_break::extend)] |
            identifier_p ("SContinue")
			    [assign_a (sentence,
				    sentence_break::scontinue)] |
            (+alnum_p)
			    [warning_assign_a (sentence,
				    sentence_break::any)]) >>
			// Skip any remaining entries, i.e., parse future versions
			// of the table as well.
			//*(anychar_p - ('#' | eol_p))
            *(anychar_p - eol_p)
			, blank_p);

		if (!info.hit)
		{
			throw syntax_error (filename, curr, last);
		}
		curr = info.stop;

		eat_comments (curr, last);

		// now process from first to last putting the grapheme type into the character data
        if (progress-- <= 0)
		{
			progress = PROGRESS_INDICATION_EVERY;
			std::cout << ".";
		}

		char32 curr_code = first_code;

		do
		{
			std::map <char32, character_properties>::iterator prop = props.find (curr_code);
			if (prop == props.end())
			{
				std::stringstream ss;
				ss << "codepoint 0x" << std::hex << curr_code
					<< " is in SentenceBreak, but not in UnicodeData.txt while processing "
					<< filename;
				throw std::runtime_error (ss.str());
			} 

			prop->second.sentence_break_kind = sentence;

            ++ curr_code;
		}
		while (curr_code <= last_code);

	} while (curr != last);
	std::cout << "\n";

	std::cout << "-Reading sentence data from " << filename << "\n";
}

}}}	// namespaces