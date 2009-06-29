// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_BASE_HPP
#define BOOST_HETEROGENOUS_BASE_HPP

#include <boost/aligned_storage.hpp>
#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/common_base.hpp>

namespace boost
{
	namespace heterogenous
	{
		/// base for the given derived type
		template <class Derived, class Base = common_base>
		struct base : Base
		{
			typedef Derived derived_type;
			typedef base<Derived, Base> this_type;

		private:
			static size_t alignment;			///< required alignment for allocation
			mutable derived_type *self_ptr;		///< pointer to derived object in this

		public:
			base() : self_ptr(0) { }

			virtual this_type *allocate(abstract_allocator &alloc) const 
			{
				abstract_allocator::pointer bytes = alloc.allocate_bytes(sizeof(derived_type), alignment);
				Derived *ptr = reinterpret_cast<Derived *>(bytes);
				ptr->this_type::self_ptr = ptr;
				return ptr;
			}

			void deallocate(common_base *object, abstract_allocator &alloc) const
			{
				Derived *ptr = static_cast<Derived *>(object);
				alloc.deallocate_bytes(reinterpret_cast<abstract_allocator::pointer>(ptr), alignment);
			}

			virtual this_type *create(abstract_allocator &alloc) const 
			{
				this_type *ptr = allocate(alloc);
				new (ptr->self_ptr) Derived();
				return ptr;
			}

			virtual this_type*copy_construct(const common_base &original, abstract_allocator &alloc) const 
			{ 
				this_type *ptr = allocate(alloc);
				new (ptr->self_ptr) Derived(static_cast<const Derived &>(original));
				return ptr;
			}
		};

		/// ensure correct alignment when allocating derived instances
		template <class Derived, class Base>
		size_t base<Derived, Base>::alignment = aligned_storage<sizeof(Derived)>::alignment;

	} // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_BASE_HPP

//EOF
