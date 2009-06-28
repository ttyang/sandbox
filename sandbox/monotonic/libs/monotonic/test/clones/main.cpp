// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

//
// test cases for ptr_container and clone_allocator issues
//

#include <string>
#include <boost/abstract_allocator.hpp>
#include <boost/cloneable.hpp>
#include <boost/monotonic/allocator.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace std;
using namespace boost;

struct derived : cloneable::base<derived>
{
	int num;
	derived() : num(0) { }
	explicit derived(int n) : num(n) { }
};

struct derived2 : cloneable::base<derived2>
{
	std::string str;

	derived2() { }
	explicit derived2(std::string const &n) : str(n) { }
};

/*

namespace boost { namespace ptr_container {

// idea: switch allocator type ordering, default to cloneable::allcoator
template <class T, class Al = std::allocator<T>, class CloneAl = cloneable::allocator>
class ptr_vector;

}}

*/

int main()
{
	typedef ptr_vector<cloneable::common_base, cloneable::allocator, monotonic::allocator<int> > vec;

	{
		vec bases;
		BOOST_ASSERT(bases.get_allocator().get_storage() == &monotonic::static_storage<>::get_storage());

		//! bases.push_back(new derived(42));					// this doesn't use the custom allocator!
		//! derived *obj = bases.get_allocator().allocate(1);	// this has to be recast

		// do a dance to get the object into the container...
		typedef vec::allocator_type::template rebind<derived>::other derived_alloc_type;
		derived_alloc_type derived_alloc(bases.get_allocator());
		derived *obj = derived_alloc.allocate(1);
		//! derived_alloc.construct(obj, 42);		// can't pass ctor args to a v1 allocator
		new (obj) derived(42);						// bypassing allocator::construct :/

		// do a dance to get the object into the container...
		typedef vec::allocator_type::template rebind<derived2>::other derived2_alloc_type;
		derived2_alloc_type derived2_alloc(bases.get_allocator());
		derived2 *obj2 = derived2_alloc.allocate(1);
		//! derived_alloc.construct(obj, 42);		// can't pass ctor args to a v1 allocator
		new (obj2) derived2("foo");						// bypassing allocator::construct :/

		// finally get the correctly allocated objects into the container
		bases.push_back(obj);
		bases.push_back(obj2);


		// idea: use variadic template arguments for push_back etc: 
		// default to use BOOST_PP for C++03

		//! bases.push_back<derived>(ctor_args...);
		//! bases.push_back<derived2>(ctor_args...);
		//! ...
		//! bases.push_back<derivedN>(ctor_args...);

		// this now works properly; after small changes to:
		//		ptr_container/detail/scoped_ptr.hpp
		//		ptr_container/detail/reversible_ptr_container.hpp
		// and by introducing boost::abstract_allocator
		//
		// these are all in the monotonic sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

		BOOST_ASSERT(bases.size() == 2);
		vec copy = bases;
		BOOST_ASSERT(copy.size() == 2);
		derived *p0 = dynamic_cast<derived *>(&copy[0]);
		derived2 *p2 = dynamic_cast<derived2 *>(&copy[1]);
		BOOST_ASSERT(p0);
		BOOST_ASSERT(p2);
		BOOST_ASSERT(p2->str == "foo");

	}
	monotonic::static_storage<>::release();

	return 0;
}

//EOF
