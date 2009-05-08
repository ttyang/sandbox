/**
 * \file examples/factories/tetrahedron.hpp
 *
 *  Two classes used in some of the examples showing 
 *  the use of meta-constructors and factories
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MIRROR_EXAMPLES_FACTORIES_TETRAHEDRON_HPP
#define BOOST_MIRROR_EXAMPLES_FACTORIES_TETRAHEDRON_HPP

#include <math.h>
#include <boost/mirror/meta_class.hpp>
#include <boost/mirror/meta_constructors.hpp>
#include <boost/mirror/meta_mem_functions.hpp>
	
namespace test {
	
struct vector
{
	double x,y,z;

	vector(double _x, double _y, double _z)
	 : x(_x)
	 , y(_y)
	 , z(_z)
	{ }

	vector(double _w)
	 : x(_w)
	 , y(_w)
	 , z(_w)
	{ }

	vector(void)
	 : x(0.0)
	 , y(0.0)
	 , z(0.0)
	{ }

	friend vector operator + (const vector& a, const vector& b)
	{
		return vector(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	friend vector operator - (const vector& a, const vector& b)
	{
		return vector(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	// cross product
	friend vector operator % (const vector& a, const vector& b)
	{
		return vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	// dot product
	friend double operator * (const vector& a, const vector& b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	double length(void) const
	{
		return sqrt(x*x + y*y + z*z);
	}
};

struct triangle
{
	vector a, b, c;

	triangle(const vector& _a, const vector& _b, const vector& _c)
	 : a(_a)
	 , b(_b)
	 , c(_c)
	{ }

	triangle(void){ }


	double area(void) const 
	{
		return ((b-a)%(c-a)).length()/2.0;
	}
};

struct tetrahedron
{
	triangle base;
	vector apex;

	tetrahedron(const triangle& _base, const vector& _apex)
	 : base(_base)
	 , apex(_apex)
	{ }

	const vector& a(void) const {return base.a;}
	const vector& b(void) const {return base.b;}
	const vector& c(void) const {return base.c;}
	const vector& d(void) const {return apex;}

	void reset_apex(const vector& _apex)
	{
		apex = _apex;
	}

	double volume(void) const
	{
		return fabs(((a()-d())*((b()-d())%(c()-d()))))/6.0;
	}
};


} // namespace test 


namespace boost {
namespace mirror {

// register the ::test namespace
BOOST_MIRROR_REG_NAMESPACE( (test) )

// register the vector, triangle and tetrahedron classes
// abnnd their constructor
//
// ::test::vector
BOOST_MIRROR_QREG_CLASS_NO_BASE( ::test, vector, (x)(y)(z))
BOOST_MIRROR_QREG_CONSTRUCTORS(
	::test::vector,
	// ::test::vector(double x, double y, double z)
	(((double)(x))((double)(y))((double)(z)))
	// ::test::vector(double w)
	(((double)(w)))
	// ::test::vector(void)
	(((void)))
)
// ::test::triangle
BOOST_MIRROR_QREG_CLASS_NO_BASE( ::test, triangle, (a)(b)(c))
BOOST_MIRROR_QREG_CONSTRUCTORS(
	::test::triangle,
	(((::test::vector)(a))((::test::vector)(b))((::test::vector)(c)))
	(((void)))
)
// ::test::tetrahedron
BOOST_MIRROR_QREG_CLASS_NO_BASE( ::test, tetrahedron, (base)(apex))
BOOST_MIRROR_QREG_CONSTRUCTORS(
	::test::tetrahedron,
	(((::test::triangle)(base))((::test::vector)(apex)))
)
BOOST_MIRROR_REG_MEM_FUNCTIONS_BEGIN(::test::tetrahedron)
BOOST_MIRROR_REG_MEM_FUNCTION(
	0, void, reset_apex, ((const ::test::vector&)(apex))
)
BOOST_MIRROR_REG_MEM_FUNCTIONS_END

} // namespace mirror
} // namespace boost

#endif

