// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_STORAGE_HPP
#define BOOST_OBJECT_MODEL_GENERIC_STORAGE_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/dictionary.hpp>

BOOST_OM_BEGIN

namespace generic
{
	struct const_storage : const_object
	{
		dictionary dict;
	};

	struct storage : const_storage
	{

	};
}

BOOST_OM_END

#include <boost/object_model/detail/prefix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_STORAGE_HPP

//EOF
