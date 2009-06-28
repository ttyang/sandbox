// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

#include <string>
#include <iostream>
#include <boost/heterogenous/vector.hpp>
#include <boost/bind.hpp>
#include <boost/any.hpp>

using namespace std;
using namespace boost;
using namespace heterogenous;

struct derived : base<derived>
{
	int num;
	derived() : num(0) { }
	explicit derived(int n) : num(n) { }
};

struct derived2 : base<derived2>
{
	std::string str;

	derived2() { }
	explicit derived2(std::string const &n) : str(n) { }
};

struct derived3 : base<derived3>
{
	float real;
	int num;
	std::string str;

	derived3() { }
	explicit derived3(float f, int n, std::string const &s) : real(f), num(n), str(s) { }

	void print() const
	{
		cout << "derived3: " << real << ", " << num << ", " << str << endl;
	}
};

// naive way of allowing reuse in derived types: factor out the implementation
struct derived4_impl
{
};

struct derived4 : derived4_impl, base<derived4>
{
};

struct derived5 : derived4_impl, base<derived5>
{
};

void test_any();

int main()
{
	test_any();

	// a 'heterogenous' container of objects of any type that derives from common_base
	typedef heterogenous::vector<> vec;

	{
		vec bases;

		// type of thing to insert must be passed explicitly, and must derive from common_base.
		// arguments to push_back are passed directly to ctor
		bases.push_back<derived>(42);						
		bases.push_back<derived2>("foo");
		bases.push_back<derived3>(3.14f, -123, "spam");

		// perform functor on each contained object of the given type
		bases.foreach<derived3>(boost::bind(&derived3::print, _1));

		BOOST_ASSERT(bases.size() == 3);

		// does a deep copy, preserving concrete types
		vec copy = bases;

		BOOST_ASSERT(copy.size() == 3);

		// each object in the container can be retrieved generically as a common_base
		common_base &generic0 = copy[0];
		common_base &generic1 = copy[1];
		common_base &generic2 = copy[2];

		// get a reference; will throw bad_cast on type mismatch
		derived &p1 = copy.ref_at<derived>(0);

		// get a pointer; returns null on type mismatch
		derived2 *p2 = copy.ptr_at<derived2>(1);
		derived3 *p3 = copy.ptr_at<derived3>(2);
		
		BOOST_ASSERT(p2);
		BOOST_ASSERT(p3);
		
		BOOST_ASSERT(p1.num == 42);
		BOOST_ASSERT(p2->str == "foo");
		BOOST_ASSERT(p3->real == 3.14f);BOOST_ASSERT(p3->num == -123);BOOST_ASSERT(p3->str == "spam");

		bool caught = false;
		try
		{
			common_base &base = copy.ref_at<derived2>(0);
		}
		catch (std::bad_cast)
		{
			caught = true;
		}
		BOOST_ASSERT(caught);

	}
	return 0;
}

void test_any()
{
	typedef std::vector<any<monotonic::allocator<char> >, monotonic::allocator<any<monotonic::allocator<char> > > > vec;
	vec v;
	v.push_back(derived(42));
	cout << "storage.used: " << monotonic::static_storage<>::used() << endl;
	v.push_back(derived2("foo"));
	cout << "storage.used: " << monotonic::static_storage<>::used() << endl;

	vec v2 = v;
	cout << "storage.used: " << monotonic::static_storage<>::used() << endl;

	BOOST_ASSERT(any_cast<derived2 &>(v2[1]).str == "foo");
}

//EOF
