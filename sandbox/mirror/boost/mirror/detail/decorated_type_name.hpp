/**
 * \file boost/mirror/detail/decorated_type_name.hpp
 *
 * Helpers for composing nontrivial typenames
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MIRROR_META_DETAIL_DECORATED_TYPE_NAME_HPP
#define BOOST_MIRROR_META_DETAIL_DECORATED_TYPE_NAME_HPP

#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mirror/detail/static_int_to_str.hpp>

namespace boost {
namespace mirror {
namespace detail {

template <class MetaType, class Decorator>
struct decorated_type_name
{
private:
	template <bool FullName>
	inline static bstring init_name(
		mpl::bool_<FullName> _full,
		const bstring& left, 
		const bstring& right
	)
	{
		bstring res(Decorator::prefix());
		res.append(MetaType::get_name(_full));
		res.append(Decorator::postfix());
		return res;
	}
public:
	template <bool FullName>
	static const bstring& get_name(
		mpl::bool_<FullName> _full,
		const bstring& left = bstring(), 
		const bstring& right = bstring()
	)
	{
		static bstring s_name(
			init_name(_full, left, right)
		);
		return s_name;
	}

	inline static const bstring& base_name(void)
	{
		return get_name(mpl::false_());
	}

	inline static const bstring& full_name(void)
	{
		return get_name(mpl::true_());
	}

};

// no-op decorator
template <typename T>
struct type_name_decorator
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void){return bstring();}
};

// pointer decorator
template <typename T>
struct type_name_decorator<T*>
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void)
	{
		return bstring(BOOST_STR_LIT(" *"));
	}
};

// array decorator
template <typename T, size_t Size>
struct type_name_decorator< T[ Size ] >
{
private:
	inline static bstring init_postfix(void)
	{
		typedef typename detail::static_int_to_str<Size>
			size_string;
		// init with '['
		bstring res(BOOST_STR_LIT(" ["));
		// 
		// setup a buffer for the number
		const size_t max_size = size_string::length::value+1;
		bchar buffer[max_size];
		// put it into the buffer
		size_string::convert(buffer, max_size);
		// append the buffer
		res.append(bstring(buffer));
		// append ']'
		res.append(bstring(BOOST_STR_LIT("]")));
		return res;
	}
public:
	inline static bstring  prefix(void){return bstring();}
	inline static const bstring& postfix(void)
	{
		static bstring s_postfix(init_postfix());
		return s_postfix;
	}
};

// array decorator
template <typename T>
struct type_name_decorator< T[] >
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void)
	{
		return bstring(BOOST_STR_LIT(" []"));
	}
};


// reference decorator
template <typename T>
struct type_name_decorator<T&>
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void)
	{
		return bstring(BOOST_STR_LIT(" &"));
	}
};

// const type decorator
template <typename T>
struct type_name_decorator<const T>
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void)
	{
		return bstring(BOOST_STR_LIT(" const"));
	}
};

// volatile type decorator
template <typename T>
struct type_name_decorator<volatile T>
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void)
	{
		return bstring(BOOST_STR_LIT(" volatile"));
	}
};

// const volatile type decorator
template <typename T>
struct type_name_decorator<const volatile T>
{
	inline static bstring  prefix(void){return bstring();}
	inline static bstring postfix(void)
	{
		return bstring(BOOST_STR_LIT(" const volatile"));
	}
};


} // namespace detail
} // namespace mirror
} // namespace boost

#endif //include guard

