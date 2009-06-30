// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_COMMON_BASE_HPP
#define BOOST_HETEROGENOUS_COMMON_BASE_HPP

#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/abstract_allocator.hpp>

namespace boost
{
	namespace heterogenous
	{
		struct default_base_type
		{
			virtual ~default_base_type() { }
		};

		/// TODO: rename this to abstract_cloneable
		template <class Base>
		struct abstract_cloneable : Base
		{
			typedef Base base_type;
			typedef abstract_cloneable<Base> this_type;

			virtual this_type *allocate(abstract_allocator &alloc) const = 0;
			virtual void deallocate(base_type &, abstract_allocator &alloc) const = 0;

			virtual this_type *create_new(abstract_allocator &alloc) const = 0;
			virtual this_type *copy_construct(const base_type &original, abstract_allocator &alloc) const = 0;

			/// optional means to make a clone that does not use copy-construction
			virtual this_type *clone(const base_type &original, abstract_allocator &alloc) const { return 0; }

			/// make a copy of the given instance. try the custom overload first, then default to using
			/// the copy-constructor
			this_type *make_copy(const base_type &original, abstract_allocator &alloc) const
			{
				if (this_type *copy = clone(original, alloc))
					return copy;
				return copy_construct(original, alloc);
			}
		};

	} // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_COMMON_BASE_HPP

//EOF
