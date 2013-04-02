


#include <mkl_vsl.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#include <limits>

//#define VLS_ENGINE_CODE VSL_BRNG_MCG31         // ok
//#define VLS_ENGINE_CODE VSL_BRNG_R250          // ok
//#define VLS_ENGINE_CODE VSL_BRNG_MRG32K3A      // ok
//#define VLS_ENGINE_CODE VSL_BRNG_MCG59         // ok
//#define VLS_ENGINE_CODE VSL_BRNG_WH            // ok
//#define VLS_ENGINE_CODE VSL_BRNG_MT19937       // fails test1, but passes test2 and test3!!
//#define VLS_ENGINE_CODE VSL_BRNG_MT2203        // fails test1, but passes test2 and test3!!
//#define VLS_ENGINE_CODE VSL_BRNG_SFMT19937     // fails test1 and test2, but passes test3!!
//#define VLS_ENGINE_CODE VSL_BRNG_SOBOL         // fails test1 and test3, but passes test2!!
#define VLS_ENGINE_CODE VSL_BRNG_NIEDERR       // fails test1 and test3, but passes test2!!

static const unsigned int seed_value = 42;

void check_errcode(int status)
{
	assert(status == VSL_ERROR_OK || status == VSL_STATUS_OK);
}

bool equal(VSLStreamStatePtr& stream1, VSLStreamStatePtr& stream2)
{
	//if (stream1 == stream2) return true;
	VSLStreamStatePtr str1;
	VSLStreamStatePtr str2;
	check_errcode(vslCopyStream(&str1, stream1));
	check_errcode(vslCopyStream(&str2, stream2));
	const unsigned int nchecks = 50;
	std::vector<int> r1(nchecks), r2(nchecks);
	check_errcode(viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, str1, nchecks, &r1[0], std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
	check_errcode(viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, str2, nchecks, &r2[0], std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
	check_errcode( vslDeleteStream( &str1 ) );
	check_errcode( vslDeleteStream( &str2 ) );
	return std::equal(r1.begin(), r1.end(), r2.begin());
/*
    const std::size_t memsize_1(vslGetStreamSize(stream1));
    const std::size_t memsize_2(vslGetStreamSize(stream2));
	if (memsize_1 != memsize_2) return false;
	//return std::memcmp ( (const void *) stream1, (const void *) stream2, memsize_1 ) == 0;
    std::vector<char> mem_1(memsize_1, 0);
    std::vector<char> mem_2(memsize_2, 0);
    check_errcode( vslSaveStreamM(stream1, &mem_1[0]) );
    check_errcode( vslSaveStreamM(stream2, &mem_2[0]) );	
    bool result = std::equal(mem_1.begin(), mem_1.end(), mem_2.begin());
	return result;*/
}

void invoke(VSLStreamStatePtr stream)
{
	int result;
	check_errcode( viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, 1u, &result, 0, 10) );
}


void test_case1()
{
	VSLStreamStatePtr stream1, stream2;

	stream1 = 0;
	stream2 = 0;

	// initialize stream1 and stream2 with same seed value
	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	// stream1 and stream2 should be identical
	assert( equal(stream1,stream2) );
	
	// draw one random number from stream2
	invoke(stream2);

	// stream1 and stream2 must no longer be identical
	assert(!equal(stream1,stream2));
	
	//{
		// Prepare a new stream initialized to the very same seed value
		VSLStreamStatePtr new_stream;
		check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
		// swap streams
		std::swap(stream2,new_stream);
		// destroy unused stream
		check_errcode( vslDeleteStream( &new_stream ) );
	//}

	// stream1 and stream2 should now be identical again!
	assert(equal(stream1,stream2));
	
	// clean up
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
}

void test_case2()
{
	VSLStreamStatePtr stream1, stream2;

	// initialize stream1 and stream2 with same seed value
	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	// stream1 and stream2 should be identical
	assert( equal(stream1,stream2) );
	
	// draw one random number from stream2
	invoke(stream2);

	// stream1 and stream2 must no longer be identical
	assert(!equal(stream1,stream2));
	
	{
		// unsafe variant
		check_errcode( vslDeleteStream( &stream2 ) );
		check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );
	}

	// stream1 and stream2 should now be identical again!
	assert(equal(stream1,stream2));
	
	// clean up
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
}

void test_case3()
{
	VSLStreamStatePtr stream1, stream2;

	// initialize stream1 and stream2 with same seed value
	check_errcode( vslNewStream(&stream1, VLS_ENGINE_CODE, seed_value) );
	check_errcode( vslNewStream(&stream2, VLS_ENGINE_CODE, seed_value) );

	// stream1 and stream2 should be identical
	assert( equal(stream1,stream2) );
	
	// draw one random number from stream2
	invoke(stream2);

	// stream1 and stream2 must no longer be identical
	assert(!equal(stream1,stream2));
	
	{
		// Prepare a new stream initialized to the very same seed value
		VSLStreamStatePtr new_stream;
		check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
		// once again (works for some streams)
		check_errcode( vslNewStream(&new_stream, VLS_ENGINE_CODE, seed_value) );
		// swap streams
		std::swap(stream2,new_stream);
		// destroy unused stream
		check_errcode( vslDeleteStream( &new_stream ) );
	}

	// stream1 and stream2 should now be identical again!
	assert(equal(stream1,stream2));
	
	// clean up
	check_errcode( vslDeleteStream( &stream1 ) );
	check_errcode( vslDeleteStream( &stream2 ) );
}


int main()
{
	std::cout << "test" << std::endl;
	test_case1();
	test_case2();
	//test_case3();
	return 0;
}


