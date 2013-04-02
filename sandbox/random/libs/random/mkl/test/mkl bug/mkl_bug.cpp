// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <mkl_vsl.h>
#include <cassert>
#include <cstring>
#include <vector>
#include <iostream>
#include <typeinfo>

//#define VLS_ENGINE_CODE VSL_BRNG_SFMT19937 /*VSL_BRNG_MT2203*/ /*VSL_BRNG_MT19937*/
#define VLS_ENGINE_CODE VSL_BRNG_MT19937

static const unsigned int seed_value = 42;

bool check_errcode(int status)
{
	assert(status == VSL_ERROR_OK || status == VSL_STATUS_OK);
	return status == VSL_ERROR_OK || status == VSL_STATUS_OK;
}

bool equal(VSLStreamStatePtr stream1, VSLStreamStatePtr stream2)
{
	if (stream1 == stream2) return true;
    const std::size_t memsize_1(vslGetStreamSize(stream1));
    const std::size_t memsize_2(vslGetStreamSize(stream2));
    if (memsize_1 != memsize_2) return false;
    std::vector<char> mem_1(memsize_1);
    std::vector<char> mem_2(memsize_2);
    check_errcode( vslSaveStreamM(stream1, &mem_1[0]) );
    check_errcode( vslSaveStreamM(stream2, &mem_2[0]) );	
	/*std::cout << "memory 1: ";		
	std::cout.write((char*)&mem_1[0], mem_1.size());
	std::cout << std::endl << std::endl;
	std::cout << "memory 2: ";		
	std::cout.write((char*)&mem_2[0], mem_2.size());
	std::cout << std::endl << std::endl;*/
    return std::equal(mem_1.begin(), mem_1.end(), mem_2.begin());
	//return std::memcmp ( (const void *) stream1, (const void *) stream2, memsize_1 ) == 0;
}

VSLStreamStatePtr copy(VSLStreamStatePtr stream) 
{
	VSLStreamStatePtr new_stream;
	check_errcode( vslCopyStream(&new_stream, stream) );
	return new_stream;
}

void invoke(VSLStreamStatePtr stream)
{
	int result;
	check_errcode( viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, 1u, &result, 0, 10) );
}

void seed(VSLStreamStatePtr* stream, unsigned int s)
{
	VSLStreamStatePtr new_stream;
 	check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, s) );
    std::swap(*stream,new_stream);
}


void test_case_1()
{
	VSLStreamStatePtr stream1, stream2, stream3;

	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream3, VLS_ENGINE_CODE, seed_value) );

	assert(equal(stream1,stream2));

	invoke(stream1);
	invoke(stream3);

	assert(!equal(stream1,stream2));
	assert(equal(stream1,stream3));

	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );

	check_errcode( vslDeleteStream( &stream3 ) );
	check_errcode( vslNewStream(&stream3, VLS_ENGINE_CODE, seed_value) );

	assert(equal(stream1,stream2));
	assert(equal(stream2,stream3));

	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
	check_errcode( vslDeleteStream( &stream3 ) );
}

void test_case_2()
{
	VSLStreamStatePtr stream1, stream2, stream3;

	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	invoke(stream2);

	assert(!equal(stream1,stream2));
	
	/*
	// Works
	VSLStreamStatePtr new_stream;
	check_errcode( vslDeleteStream( &stream2 ) );
 	check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
	stream2 = new_stream;
	*/
	
	// Does not work
	VSLStreamStatePtr new_stream;
	check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
	std::swap(stream2,new_stream);
	check_errcode( vslDeleteStream( &new_stream ) );

	/*
	// Does not work
	VSLStreamStatePtr new_stream;
	seed(&new_stream, seed_value);
	check_errcode( vslDeleteStream( &stream2 ) );
	stream2 = new_stream;
	*/

	/*
	// Works
	VSLStreamStatePtr copy;
	check_errcode( vslCopyStream(&copy, stream2) );
	VSLStreamStatePtr new_stream;
	check_errcode( vslDeleteStream( &stream2 ) );
 	check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
	stream2 = new_stream;
	check_errcode( vslDeleteStream( &copy ) );
	*/

	/*
	// Works
	VSLStreamStatePtr copy;
	check_errcode( vslCopyStream(&copy, stream2) );
	VSLStreamStatePtr new_stream;
	check_errcode( vslDeleteStream( &copy ) );
 	check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslDeleteStream( &stream2 ) );	
	stream2 = new_stream;
	*/

	/*
	// Works
	VSLStreamStatePtr copy;
	check_errcode( vslCopyStream(&copy, stream2) );
	VSLStreamStatePtr new_stream;
	check_errcode( vslDeleteStream( &copy ) );
 	check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
	std::swap(stream2, new_stream);	
	check_errcode( vslDeleteStream( &new_stream ) );	
	*/

	assert(equal(stream1,stream2));
	
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
}



void test_case_3()
{
	unsigned int seed_value2 = 1;
	
	char seed_value2_c = static_cast<char>(seed_value2);

	VSLStreamStatePtr stream1, stream2, stream3;

	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value2) );

	seed( &stream2, seed_value2_c);

	assert(equal(stream1,stream2));
	
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
	
}

void test_case_4()
{
	const std::vector<unsigned int> v(std::size_t(9999u), 0x41);
    std::vector<unsigned int>::const_iterator it = v.begin();
    std::vector<unsigned int>::const_iterator it_end = v.end();

	VSLStreamStatePtr stream1;
	check_errcode(vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );	

	{
	std::vector<unsigned int>::const_iterator first = v.begin();
	std::vector<unsigned int>::const_iterator last = v.end();
	std::vector<unsigned int> seed_;
	while (first != last)
	{
		seed_.push_back(*first++);
	}
	VSLStreamStatePtr copy;
	check_errcode( vslCopyStream(&copy, stream1) );
	VSLStreamStatePtr new_stream;
	check_errcode( vslDeleteStream( &copy ) );
	check_errcode(vslNewStreamEx(&new_stream, VLS_ENGINE_CODE, seed_.size(), &seed_[0]));
	std::swap(stream1,new_stream);
    check_errcode(vslDeleteStream(&new_stream));	
	}

	VSLStreamStatePtr stream2;
	check_errcode(vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );	
	
	{
	std::vector<unsigned int>::const_iterator first = v.begin();
	std::vector<unsigned int>::const_iterator last = v.end();
	std::vector<unsigned int> seed_;
	while (first != last)
	{
		seed_.push_back(*first++);
	}
	VSLStreamStatePtr copy2;
	check_errcode( vslCopyStream(&copy2, stream2) );
	VSLStreamStatePtr new_stream2;
	check_errcode( vslDeleteStream( &copy2 ) );
	check_errcode(vslNewStreamEx(&new_stream2, VLS_ENGINE_CODE, seed_.size(), &seed_[0]));
	std::swap(stream2,new_stream2);
    check_errcode(vslDeleteStream(&new_stream2));
	}

	assert(equal(stream1,stream2));
	
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
    
}

void test_case_5()
{
	const std::vector<unsigned int> v(std::size_t(9999u), 0x41);
    std::vector<unsigned int>::const_iterator it = v.begin();
    std::vector<unsigned int>::const_iterator it_end = v.end();

	VSLStreamStatePtr stream1;
	check_errcode(vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );	

	{
	std::vector<unsigned int>::const_iterator first = v.begin();
	std::vector<unsigned int>::const_iterator last = v.end();
	std::vector<unsigned int> seed_;
	while (first != last)
	{
		seed_.push_back(*first++);
	}
	check_errcode(vslNewStreamEx(&stream1, VLS_ENGINE_CODE, seed_.size(), &seed_[0]));
	}

	VSLStreamStatePtr stream2;
	check_errcode(vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );	
	
	{
	std::vector<unsigned int>::const_iterator first = v.begin();
	std::vector<unsigned int>::const_iterator last = v.end();
	std::vector<unsigned int> seed_;
	while (first != last)
	{
		seed_.push_back(*first++);
	}
	check_errcode(vslNewStreamEx(&stream2, VLS_ENGINE_CODE, seed_.size(), &seed_[0]));
	}

	assert(equal(stream1,stream2));
	
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
    
}


void minimal_example_bug()
{
	VSLStreamStatePtr stream1, stream2;

	// create two identical streams
	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	// streams should be the same
	assert(equal(stream1,stream2));

	// generate 1 uniformly distributed random number 
	invoke(stream2);

	// streams should now not be the same anymore
	assert(!equal(stream1,stream2));
	
	// try to make streams equal again
	check_errcode( vslDeleteStream( &stream2 ) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	// streams should be the same
	assert(equal(stream1,stream2));

	// clean up
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
}

void minimal_example_bug2()
{
	const std::vector<unsigned int> v(std::size_t(9999u), 0x41);
    std::vector<unsigned int>::const_iterator it = v.begin();
    std::vector<unsigned int>::const_iterator it_end = v.end();

	VSLStreamStatePtr stream1, stream2;

	// create two streams which are identical
	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	// streams should be the same
	assert(equal(stream1,stream2));

	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslNewStreamEx(&stream1, VLS_ENGINE_CODE, v.size(), &v[0]) );

	// streams should not be the same
	assert(!equal(stream1,stream2));

	// try to make streams equal again
	check_errcode( vslDeleteStream( &stream2 ) );
	check_errcode( vslNewStreamEx(&stream2, VLS_ENGINE_CODE, v.size(), &v[0]) );

	// streams should be the same
	assert(equal(stream1,stream2));

	// clean up
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
}

int main()
{
	//minimal_example_bug();
	//minimal_example_bug2();
	test_case_1();
	test_case_2();
	//test_case_3();
	//test_case_4();
	//test_case_5();
	return 0;
}


