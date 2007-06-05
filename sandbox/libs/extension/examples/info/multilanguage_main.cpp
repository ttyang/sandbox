/* (C) Copyright Mariano G. Consoni 2007
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/extension/factory_map.hpp>
#include <boost/extension/shared_library.hpp>
#include <boost/extension/convenience.hpp>

#include <iostream>

#include "word_description.hpp"

int main()
{
	using namespace boost::extensions;
	//  Create the factory_map object - it will hold all of the available
	//  constructors. Multiple factory_maps can be constructed.
	factory_map fm;

	// load the shared library with 
	load_single_library(fm, "libMultilanguageHelloWorld.extension", "extension_export_multilanguage_word");
	//  Get a reference to the list of constructors for words.
	std::list<factory<word, word_description> > & factory_list = fm.get<word, word_description>();  

	if (factory_list.size() < 4+4) {
		std::cout << "Error - the classes were not found (" << factory_list.size() << " classes)" << std::endl;
		return 1;
	}

	for (std::list<factory<word, word_description> >::iterator current_word = factory_list.begin();
	     current_word != factory_list.end(); ++current_word)
	{
		//  Using auto_ptr to avoid needing delete. Using smart_ptrs is recommended.
		//  Note that this has a zero argument constructor - currently constructors
		//  with up to six arguments can be used.
		std::auto_ptr<word> word_ptr(current_word->create());
		std::cout << word_ptr->get_val() << " is " << current_word->get_info().english_translation 
			  << " in " << current_word->get_info().language << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
