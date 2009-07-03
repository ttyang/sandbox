// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CLONEABLE_MAP_HPP
#define BOOST_CLONEABLE_MAP_HPP

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>

#include <boost/cloneable/detail/make_clone_allocator.hpp>
#include <boost/cloneable/detail/container_base.hpp>

namespace boost 
{
	namespace cloneable
	{
		/// a vector of heterogenous objects
		// TODO: move to boost/heterogenous/map
		template <class Base, class Pred, class Alloc>
		struct map
			: detail::container_base<Base, Alloc>
		{
			typedef detail::container_base<Base,Alloc> parent_type;
			typedef typename parent_type::base_type base_type;
			typedef typename parent_type::abstract_base_type abstract_base_type;
			typedef typename parent_type::allocator_type allocator_type;
			using parent_type::validate;
			using parent_type::new_instance;

			typedef Pred predicate_type;
			typedef ptr_map<abstract_base_type, abstract_base_type, Pred, allocator, allocator_type> implementation;

			typedef typename implementation::value_type value_type;
			typedef typename implementation::reference reference;
			typedef typename implementation::const_reference const_reference;
			typedef typename implementation::iterator iterator;
			typedef typename implementation::const_iterator const_iterator;
			typedef typename implementation::key_type key_type;
			typedef typename implementation::mapped_type mapped_type;

			typedef map<Base, Pred, Alloc> this_type;

		private:
			implementation impl;

		public:
			map() 
				: impl(predicate_type(), get_allocator())
			{
			}
			map(allocator_type &a) 
				: parent_type(a), impl(predicate_type(), get_allocator())
			{
			}

			template <class II>
			map(II F, II L)
				: impl(F,L, get_allocator())
			{
			}
			template <class II>
			map(II F, II L, allocator_type &a)
				: parent_type(a), impl(F,L, get_allocator())
			{
			}

		private:
			typedef std::pair<iterator, bool> map_insert_result;

			template <class K, class V>
			struct insert_result
			{
				//TODO: typedef const_instance<K> key_type;
				typedef instance<K> key_type;
				typedef instance<V> value_type;

				key_type key;
				value_type value;
				iterator where;
				bool inserted;

				insert_result() : inserted(false) { }
				insert_result(const key_type &K, const value_type &V, const map_insert_result &R)
					: key(K), value(V), where(R.first), inserted(R.second) { }
			};

			template <class K>
			struct value_adder
			{
			private:
				typedef instance<K> key_type;
				this_type *parent;
				key_type key;

			public:
				value_adder(this_type &P, const key_type &K)
					: parent(&P), key(K) { }

				template <class V>
				insert_result<K,V> value()
				{
					return insert(parent->new_instance<V>());
				}

				template <class V, class A0>
				insert_result<K,V> value(A0 a0)
				{
					return insert(parent->new_instance<V>(a0));
				}
				template <class V, class A0, class A1>
				insert_result<K,V> value(A0 a0, A1 a1)
				{
					return insert(parent->new_instance<V>(a0,a1));
				}

			private:
				template <class V>
				insert_result<K,V> insert(instance<V> &value)
				{
					map_insert_result result = parent->insert(key.to_abstract(), value.to_abstract());
					if (!result.second)
					{
						key.release();
						value.release();
					}
					return insert_result<K,V>(key, value, result);
				}
			};

			// TODO: make this private
			template <class A, class B>
			map_insert_result insert(A a, B b)
			{
				return map_insert_result();// impl.insert(std::make_pair(a, b));
			}
			void insert(value_type x)
			{
				impl.insert(x);
			}

		public:
			template <class K>
			value_adder<K> key()
			{
				return value_adder<K>(*this, new_instance<K>());
			}

			// TODO: use variadic arguments or BOOST_PP to pass ctor args
			template <class K, class A0>
			value_adder<K> key(A0 a0)
			{
				return value_adder<K>(*this, new_instance<K>(a0));
			}
			template <class K, class A0, class A1>
			value_adder<K> key(A0 a0, A1 a1)
			{
				return value_adder<K>(*this, new_instance<K>(a0,a1));
			}
			template <class K, class A0, class A1, class A2>
			value_adder<K> key(A0 a0, A1 a1, A2 a2)
			{
				return value_adder<K>(*this, new_instance<K>(a0,a1,a2));
			}

			template <class Fun>
			Fun for_each(Fun fun)
			{
				BOOST_FOREACH(value_type &value, *this)
				{
					fun(value);
				}
			}

			template <class Ty, class Fun>
			Fun for_each_key(Fun fun)
			{
				//BOOST_FOREACH(base_type &b, *this)
				//{
				//	if (Ty *ptr = dynamic_cast<Ty *>(&b))
				//	{
				//		fun(*ptr);
				//	}
				//}
				return fun;
			}

			template <class Ty, class Fun>
			Fun for_each_mapped(Fun fun) const
			{
				//BOOST_FOREACH(const common_base &base, *this)
				//{
				//	if (Ty *ptr = dynamic_cast<Ty *>(&base))
				//	{
				//		fun(*ptr);
				//	}
				//}
				return fun;
			}

			size_t size() const
			{
				return impl.size();
			}
			bool empty() const
			{
				return impl.empty();
			}

			iterator begin()
			{
				return impl.begin();
			}
			iterator end()
			{
				return impl.end();
			}
			const_iterator begin() const
			{
				return impl.begin();
			}
			const_iterator end() const
			{
				return impl.end();
			}

			template <class K>
			iterator find()
			{
				instance<K> k(get_allocator());
				BOOST_SCOPE_EXIT((k))
				{
					k.release();
				}
				BOOST_SCOPE_EXIT_END
				return impl.find(k.to_abstract());
			}

			template <class K, class A0>
			iterator find(A0 a0)
			{
				instance<K> k(get_allocator(), a0);
				BOOST_SCOPE_EXIT((k))
				{
					k.release();
				}
				BOOST_SCOPE_EXIT_END
				return impl.find(k.to_abstract());
			}

			//reference operator[](key_type const &key)
			//{
			//	return impl[n];
			//}
			//const_reference operator[](key_type const &key) const
			//{
			//	return impl[n];
			//}

		};
	
	} // namespace heterogenous

} // namespace boost

#include <boost/cloneable/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_MAP_HPP

//EOF
