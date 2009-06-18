// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_ALLOCATOR_BASE_HPP
#define BOOST_MONOTONIC_ALLOCATOR_BASE_HPP

#include <boost/assert.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

#include <boost/monotonic/static_storage.hpp>
#include <boost/monotonic/container.hpp>

namespace boost
{
	namespace monotonic
	{
		namespace detail
		{
			template <bool is_mono_container>
			struct Construct
			{
				template <class T, class Alloc>
				static void Given(T *ptr, Alloc *allocator)
				{
					new (ptr) T();
				}
				template <class T, class Alloc>
				static void Given(T *ptr, T const &val, Alloc *allocator)
				{
					new (ptr) T(val);
				}
			};
			template <>
			struct Construct<true>
			{
				template <class T, class Alloc>
				static void Given(T *ptr, Alloc *allocator)
				{
					new (ptr) T(*allocator);
				}
				template <class T, class Alloc>
				static void Given(T *ptr, T const &val, Alloc *allocator)
				{
					// unfortunately, there is no requirement for a container to 
					// have a copy-ctor that also passes an allocator.
					new (ptr) T(*allocator);
					*ptr = val;
				}
			};

			template <bool is_monotonic_container, class T>
			struct Create
			{
				template <class Storage>
				static T Given(Storage &)
				{
					return T();
				}
			};
			template <class T>
			struct Create<true, T>
			{
				template <class Storage>
				static T Given(Storage &storage)
				{
					return T(storage);
				}
			};
		}

		/// common to other monotonic allocators for type T of type Derived
		template <class T, class Derived>
		struct allocator_base
		{
			BOOST_STATIC_CONSTANT(size_t, alignment = boost::aligned_storage<sizeof(T)>::alignment);
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef T *pointer;
			typedef const T *const_pointer;
			typedef T &reference;
			typedef const T &const_reference;
			typedef T value_type;

		private:
			storage_base *storage;

		public:
			allocator_base(storage_base &store) throw() 
				: storage(&store) { }

			allocator_base(const allocator_base& alloc) throw() 
				: storage(alloc.get_storage()) { }

			template <class U, class D> 
			allocator_base(const allocator_base<U,D> &alloc) throw()
				: storage(alloc.get_storage()) { }

			pointer address(reference x) const
			{
				return &x;
			}

			const_pointer address(const_reference x) const
			{
				return &x;
			}

			pointer allocate(size_type num, const void * /*hint*/ = 0)
			{
				BOOST_ASSERT(num > 0);
				BOOST_ASSERT(storage != 0);
				return static_cast<pointer>(storage->allocate(num*sizeof(value_type), alignment));
			}

			void deallocate(pointer, size_type)
			{
				// do nothing
			}

			size_type max_size() const throw()
			{
				if (!storage)
					return 0;
				//return storage->max_size()/(sizeof(T) + alignment);
				return storage->max_size()/sizeof(value_type);
			}

			void construct(pointer ptr)
			{
				detail::Construct<detail::is_monotonic<T>::value>::Given(ptr, static_cast<Derived *>(this));
			}

			void construct(pointer ptr, const T& val)
			{
				detail::Construct<detail::is_monotonic<T>::value>::Given(ptr, val, static_cast<Derived *>(this));
			}

			void destroy(pointer ptr)
			{
				if (!ptr)
					return;
				destroy(ptr, boost::has_trivial_destructor<value_type>());
			}

			void destroy(pointer ptr, const boost::false_type& )
			{
				(*ptr).~value_type();
			}

			void destroy(pointer, const boost::true_type& )
			{ 
			}

			void swap(allocator<value_type> &other)
			{
				std::swap(storage, other.storage);
			}

			storage_base *get_storage() const
			{
				return storage;
			}

			friend bool operator==(allocator_base<T,Derived> const &A, allocator_base<T,Derived> const &B) 
			{ 
				return A.storage == B.storage;
			}

			friend bool operator!=(allocator_base<T,Derived> const &A, allocator_base<T,Derived> const &B) 
			{ 
				return A.storage != B.storage;
			}
		};

	} // namespace monotonic

} // namespace boost

#endif // BOOST_MONOTONIC_ALLOCATOR_BASE_HPP

//EOF
