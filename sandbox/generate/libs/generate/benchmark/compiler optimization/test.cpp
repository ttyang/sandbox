/*
 * test.cpp
 * 
 * Copyright 2013 Fabian Bösch <boeschf@ethz.ch>
 * 
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt
 * or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//#include <vector>
#include <iterator>

template <class Value>
struct initializer_generator
{
	initializer_generator(const Value& init) : _init(init) {}
	inline Value operator()() { return _init; }
	const Value _init;
};


//[while_generate
template <class ForwardIterator, class Generator>
void while_generate( ForwardIterator first, ForwardIterator last, Generator gen )
{
	while (first != last)  *first++ = gen();
}
//]
//[for_generate
template <class UnitStrideIterator, class Generator>
void for_generate( UnitStrideIterator first, UnitStrideIterator last, Generator gen )
{
	typedef typename std::iterator_traits<UnitStrideIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<UnitStrideIterator>::pointer pointer;

	const difference_type n(last-first);
	pointer data(&*first);
	for ( difference_type i=0; i<n; ++i) data[i] = gen();
}
//]
//[for_generate2
template <class UnitStrideIterator, class Generator>
void for_generate2( UnitStrideIterator first, UnitStrideIterator last, Generator gen )
{
	typedef typename std::iterator_traits<UnitStrideIterator>::pointer pointer;

	pointer end(&*last);
	for ( pointer i=&*first; i!=end; ++i) *i = gen();
}
//]


int main()
{
		
	//std::vector<double> vec(100);
	double* arr = new double[100];
	initializer_generator<double> gen(0);
	//while_generate(vec.begin(), vec.end(), gen);
	//for_generate(vec.begin(), vec.end(), gen);
	//for_generate2(vec.begin(), vec.end(), gen);
	while_generate(arr, arr+100, gen);
	//for_generate(arr, arr+100, gen);
}
