// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

//[ initializer
#include <boost/generate/generate.hpp>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <boost/iterator/iterator_facade.hpp>

using namespace std;

// a constant stride iterator class
template <class Value, unsigned int stride>
class stride_iterator :
public boost::iterator_facade< stride_iterator<Value, stride>, Value, boost::random_access_traversal_tag>
{
	public:

	typedef typename boost::iterator_facade<stride_iterator<Value, stride>, Value, boost::random_access_traversal_tag>::difference_type difference_type;
	stride_iterator() : m(0) {}
	explicit stride_iterator(Value* p) : m(p) {}

	private:

	friend class boost::iterator_core_access;
	void increment() { m += stride; }
	void decrement() { m -= stride; }
	void advance(difference_type n) { m += n*stride;}
	difference_type distance_to(const stride_iterator& z) const { return (z.m - m) / stride; }
	bool equal(stride_iterator const& other) const { return this->m == other.m; }
	Value& dereference() const { return *m; }
	Value* m;
};

template <class ResultType>
struct initializer
{
	typedef boost::range_generate::constant_stride_range_generator_type_checked<ResultType> is_range_generator;  // metafunction class

	initializer(const ResultType& i) : initial_value(i) {}	

	// range function call
	template <class Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		const size_t s = boost::stride<Iterator>::value;		
		const size_t n = (end-begin)*s;		
		ResultType* data = &(*begin);
		#pragma omp parallel for default(shared) schedule(static)                                            // omp parallelization
		for (size_t i=0; i<n; i+=s) data[i] = initial_value;
	}
	const ResultType initial_value;
};

typedef stride_iterator<double, 4> iter;                                                                             // iterator with stride 4 and value_type double

BOOST_IS_CONSTANT_STRIDE_ITERATOR(iter, 4)                                                                           // specialize traits class

int main()
{
	omp_set_num_threads(8);
	vector<double> v(1000);
	iter begin(&*v.begin()), end(&*v.end());                                                                     // construct stride iterators
	boost::generate(begin, end, initializer<double>(3));                                                         // call boost::generate
	copy(v.begin(), v.end(), ostream_iterator<double>(cout, "\n"));                                              // print generated values
	return 0;
}
//]

