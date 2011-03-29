/**
 * \file boost/char_type_switch/string.hpp
 * Narrow/Wide character type switching - cstring functions
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_CHAR_TYPE_SWITCH_CSTRING_HPP
#define BOOST_CHAR_TYPE_SWITCH_CSTRING_HPP


#include <boost/char_type_switch/char.hpp>
//
// c string functions
#include <cstring>

namespace boost {
namespace cts {

/** Wrappers around cstring functions 
 */

// disable the deprecated function warning on msvc
// this warning is issued when not using the "safe"
// versions of string functions like strcpy_s (vs. strcpy)
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4996)
#endif


/** string compare
 */

inline size_t bstrlen(const bchar* str)
{
#ifdef BOOST_CTS_USE_WIDE_CHARS
	return ::std::wcslen(str);
#else
	return ::std::strlen(str);
#endif
}


	
inline int bstrcmp(const bchar* a, const bchar* b)
{
#ifdef BOOST_CTS_USE_WIDE_CHARS
	return ::std::wcscmp(a, b);
#else
	return ::std::strcmp(a, b);
#endif
}

/** string copy
 */
inline bchar* bstrcpy(bchar* dst, const bchar* src)
{
#ifdef BOOST_CTS_USE_WIDE_CHARS
	return ::std::wcscpy(dst, src);
#else
	return ::std::strcpy(dst, src);
#endif
}

/** string copy
 */
inline bchar* bstrncpy(bchar* dst, const bchar* src, size_t count)
{
#ifdef BOOST_CTS_USE_WIDE_CHARS
	return ::std::wcsncpy(dst, src, count);
#else
	return ::std::strncpy(dst, src, count);
#endif
}

// enable the deprecated function warnings on msvc
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace cts
} // namespace boost

#endif //include guard

