// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_DICTIONARY_HPP
#define BOOST_OBJECT_MODEL_DICTIONARY_HPP

#include <map>
#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/label.hpp>

BOOST_OM_BEGIN

struct dictionary
{
	typedef std::map<label, generic::object> contents_type;

	contents_type contents;

	void set(label const &name, generic::object const &obj)
	{
		contents[name] = obj;
	}
	generic::object get(label const &name) const
	{
		contents_type::const_iterator iter = contents.find(name);
		if (iter == contents.end())
			return null_object;
		return iter->second;
	}
};

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_DICTIONARY_HPP

//EOF
