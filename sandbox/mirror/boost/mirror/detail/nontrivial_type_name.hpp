/**
 * \file boost/mirror/detail/nontrivial_type_name.hpp
 * Helpers for composing a nontrivial typenames
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MIRROR_META_DETAIL_NONTRIVIAL_TYPE_NAME_HPP
#define BOOST_MIRROR_META_DETAIL_NONTRIVIAL_TYPE_NAME_HPP

namespace boost {
namespace mirror {
namespace detail {

template <class meta_type, bool true_or_false>
struct nontrivial_type_base_or_full_name;

/** Base name 
 */
template <class meta_type>
struct nontrivial_type_base_or_full_name<meta_type, true>
{
	BOOST_MIRROR_CONST_MEMBER_ATTRIB(
		size_t,
		name_length,
		meta_type::base_name_length
	)
	inline static const bchar* name(void)
	{
		return meta_type::base_name();
	}
};

/** Full name 
 */
template <class meta_type>
struct nontrivial_type_base_or_full_name<meta_type, false>
{
	BOOST_MIRROR_CONST_MEMBER_ATTRIB(
		size_t,
		name_length,
		meta_type::full_name_length
	)
	inline static const bchar* name(void)
	{
		return meta_type::full_name();
	}
};

template <class meta_type, typename meta_data, template <class, typename, bool> class implementation>
struct static_nontrivial_type_name
: implementation<meta_type, meta_data, true>
, implementation<meta_type, meta_data, false>
{
private:
	typedef typename implementation<meta_type, meta_data, true>  implementation_base_name;
	typedef typename implementation<meta_type, meta_data, false> implementation_full_name;

	template <bool base_name>
	static const bchar* get_name(mpl::bool_<base_name>)
	{
		typedef typename implementation<meta_type, meta_data, base_name>
			impl;
		static bchar the_name[impl::name_length+1] 
			= {BOOST_STR_LIT("")};
		if(!the_name[0]) 
			impl::init_name(the_name);
		return the_name;
	}
public:
	BOOST_MIRROR_CONST_MEMBER_ATTRIB(
		size_t,
		base_name_length,
		implementation_base_name::name_length
	)
	BOOST_MIRROR_CONST_MEMBER_ATTRIB(
		size_t,
		full_name_length,
		implementation_full_name::name_length
	)
	static const bchar* base_name(void)
	{
		return get_name(mpl::bool_<true>());
	}
	static const bchar* full_name(void)
	{
		return get_name(mpl::bool_<false>());
	}
};

} // namespace detail
} // namespace mirror
} // namespace boost

#endif //include guard

