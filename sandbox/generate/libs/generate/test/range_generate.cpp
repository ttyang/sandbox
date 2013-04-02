// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)



#include <boost/generate/generate.hpp>
#include <vector>
#include <list>
#include <iostream>

template<class T>
struct simple_generator
{
	T operator()()
	{
		return 0;
	}
}; 

struct simple_range_generator
{

	typedef boost::range_generate::unit_stride_range_generator_type_checked<int> is_range_generator;

	template <class Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		std::cout << "range generate" << std::endl;
	}
}; 


struct simple_range_generator2
{

	template <class Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		std::cout << "range generate 2" << std::endl;
	}

};

struct simple_range_generator3
{

	typedef boost::range_generate::unit_stride_range_generator is_range_generator;

	template <class Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		std::cout << "range generate 3" << std::endl;
	}
}; 

struct myclass {};

BOOST_IS_CONSTANT_STRIDE_ITERATOR(myclass,1)

int main()
{

	simple_generator<int> s_gen;
	simple_range_generator gen;
	simple_range_generator2 gen2;
	simple_range_generator3 gen3;
	
	std::vector<int> vec(10,0);
	std::vector<float> vecf(10,0);
	std::list<int> lst(10,0);
	int* arr = new int[10];

	std::cout << boost::is_constant_stride_iterator<typename std::list<int>::iterator>::value << std::endl;
	//std::cout << boost::is_constant_stride_iterator<int>::value << std::endl;
	std::cout << boost::is_unit_stride_iterator<typename std::list<int>::iterator>::value << std::endl;
	//std::cout << boost::is_unit_stride_iterator<int>::value << std::endl;

	std::cout << boost::is_constant_stride_iterator<myclass>::value << std::endl;
	std::cout << boost::is_unit_stride_iterator<myclass>::value << std::endl;

	boost::generate(vec.begin(), vec.end(), gen);
	
	boost::generate(vec.begin(), vec.end(), gen2);

	boost::generate(vec.begin(), vec.end(), gen3);
	

	// boost::generate(lst.begin(), lst.end(), gen); 
	// Does not compile because std::list<int>::iterator does not model a Unit Stride Iterator

	// boost::generate(lst.begin(), lst.end(), gen2); 
	// Does not compile because std::list<int>::iterator does not model a Unit Stride iterator

	// boost::generate(lst.begin(), lst.end(), gen3); 
	// Does not compile because std::list<int>::iterator does not model a Unit Stride iterator
	

	// boost::generate(vecf.begin(), vecf.end(), gen);
	// Does not compile because std::vector<float>::iterator::value_type (==float) is not equal to int as required by the template meta function is_vectorizable_type_checked.

	boost::generate(vecf.begin(), vecf.end(), gen2);

	boost::generate(vecf.begin(), vecf.end(), gen3);


	boost::generate(arr, arr+10, gen);

	boost::generate(arr, arr+10, gen2);

	boost::generate(arr, arr+10, gen3);


	// std::cout << simple_range_generator::is_vectorizable::apply<int>::value << std::endl;
	// Does not compile: int is not an iterator

	// std::cout << simple_range_generator2::is_vectorizable::apply<int>::value << std::endl;
	// Does not compile: int is not an iterator

	// std::cout << simple_range_generator3::is_vectorizable::apply<int>::value << std::endl;
	// Does compile: int is not an iterator
	

	boost::generate(vec.begin(), vec.end(), s_gen);
	boost::generate(lst.begin(), lst.end(), s_gen);

	delete[] arr;

	return 0;
}


