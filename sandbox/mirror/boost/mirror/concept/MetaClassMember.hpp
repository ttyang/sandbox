/**
 * \file boost/mirror/concept/MetaClassMember.hpp
 *
 * Meta function checking whether a given type satisfies the 
 * requirements of the MetaClassMember concept
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MIRROR_CONCEPT_META_CLASS_MEMBER_HPP
#define BOOST_MIRROR_CONCEPT_META_CLASS_MEMBER_HPP

#include <boost/mirror/concept/MetaNamedScopedObject.hpp>

namespace boost {
namespace mirror {

template <typename T>
struct is_MetaClassMember
{
	BOOST_MIRROR_CONCEPT_TESTER_BEGIN

	template <class X> 
	static match test(
		X* 
	);

	typedef is_MetaNamedScopedObject<T> other_constraints;

	BOOST_MIRROR_CONCEPT_TESTER_END

};


} // namespace mirror
} // namespace boost

#endif //include guard

