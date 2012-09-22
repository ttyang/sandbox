#include "tuple_test_impl_macros.hpp"

#if !defined(TUPLE_SIZE)
  //This only used when not running several benchmarks where
  //macro values are set on command line with -DMACRO=VALUE.
  //See tuple.benchmark.mk.
  #define TUPLE_TEST_IMPL TUPLE_TEST_HORIZONTAL
    //TUPLE_TEST_IMPL selects the tuple implementation method.
    //TUPLE_TEST_VERTICAL selects the preprocessor generated
    //  tuples.
    //TUPLE_TEST_HORIZONTAL selects the variadic template generated
    //  tuples (using a multiple inheritance method similar to
    //  that mentioned here:
    //    https://groups.google.com/forum/?fromgroups=#!msg/comp.std.c++/_-6X_xZlKlA/3Fw9_QnZSWQJ
    //  with subject:
    //    Variadic Templates in C++0x need some additional features to come closer to fulfilling their promise 
    //  and date:
    //    01/12/2009
    //  )
  #define TUPLE_SIZE 4
    //^size of the tuple used.
    //Also, the number of at_test calls in test_row<I,J>::exec.
  #define LAST_LESS 2
    //^determines number of instantiations of test_col and test_row.
  #define VALU_AT
    //^Decides whether value of tuple elements is retrieved
    //or some dummy value is used
    //in test_row<I,J>::at_test.
  //#define TRACE_BENCHMARK
  #ifdef TRACE_BENCHMARK
    #define USE_DEMANGLER
    #ifdef USE_DEMANGLER
      #include <boost/utility/demangled_type_name.hpp>
    #endif
  #endif
#endif
  //#define VERT_AMORT
    //Purpose:
    //  Account for the amortized cost of
    //  amortized::make_indexes
  //Use something less than TUPLE_SIZE as LAST_LESS
  //if compile times become too large.
#define LAST_RC ((LAST_LESS>TUPLE_SIZE)?TUPLE_SIZE:LAST_LESS)
#define LAST_ROW LAST_RC
#define LAST_COL LAST_RC
    //test_row<I,J>::exec for I=0...LAST_ROW-1, for J=0...LAST_COL-1
    //is called.

/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//OriginalVersion:
//  On 2009-09-27, downloaded from attachment to:
//    http://article.gmane.org/gmane.comp.lib.boost.devel/194407
//Purpose:
//  Timing benchmark for 2 methods of tuple implmentation.
//  The method used is dependent on macro, TUPLE_TEST_IMPL:
//    when TUPLE_TEST_IMPL == TUPLE_TEST_VERTICAL:
//      This method uses the boost preprocessor to generate
//      member variables for the tuple elements:
//        HI tI;
//      where I=0...N-1, where N is the size of the tuple.
//    when TUPLE_TEST_IMPL == TUPLE_TEST_HORIZONTAL:
//      This method uses multiple inheritance of the
//      tuple elements "paired" with a key in a
//      superclass:
//        element<int_key<I>,HI>
//      where I is as for the 'TUPLE_TEST_IMPL == TUPLE_TEST_VERTICAL' method and
//      where the member variable is:
//        HI element<int_key<I>,HI>::a;
//

#if TUPLE_TEST_IMPL == TUPLE_TEST_HORIZONTAL
  #define SLIM_TAGGED_VECTOR
#else
#endif

//#include <slim/container/vector/detail/pp/vector_n.hpp>
#include <slim/container/vector.hpp>

template<int Value>
struct int_value //values stored in tuple
{
    int_value(void)
    : value(Value)
    {}
    int const value;
};

template<int I,int J, int Max, typename... Args>
struct make_tuple:
	make_tuple<I,J,Max-1,int_value<I*TUPLE_SIZE*TUPLE_SIZE+J*TUPLE_SIZE+Max>,Args...>
{};
template<int I,int J, typename... Args>
struct make_tuple<I,J,0, Args...>
{
	typedef slim::vector<Args...> type;
};

#include <iostream>

template<int I,int J=0>
struct test_row
{
 private:
	typedef typename make_tuple<I, J, TUPLE_SIZE>::type tuple_type;

	template<int K>
	static int at_test(tuple_type& t,boost::mpl::int_<K> key)
	{
		int const value=
#ifdef VALU_AT
                  #if TUPLE_TEST_IMPL == TUPLE_TEST_HORIZONTAL
		    slim::detail::at_helper<K>(t)
                  #else
                    t.at_impl(key)
                  #endif
                    .value
#else
		  K
#endif
		;
	      #ifdef TRACE_BENCHMARK
		std::cout<<"at_test:K="<<K<<"\n";
	      #endif
		return value+at_test(t,boost::mpl::int_<K+1>());
	}
	static int at_test(tuple_type&,boost::mpl::int_<TUPLE_SIZE>)
	{
	  #ifdef TRACE_BENCHMARK
	    std::cout<<"at_test:TUPLE_SIZE="<<TUPLE_SIZE<<"\n";
	  #endif
	    return 0;
	}
 public:
	static int exec()
	{
	      #ifdef TRACE_BENCHMARK
		std::cout<<"test_row<I="<<I<<",J="<<J<<">:\n";
                #ifdef USE_DEMANGLER
		  std::cout<<"tuple_type="<<utility::demangled_type_name<tuple_type>()<<"\n";
                #endif
	      #endif
		tuple_type t;
		int const value=at_test(t,boost::mpl::int_<0>());
		//The combination of the above at_test specialized function
		//and the at_test general function means the above call
		//actually calls:
		//  at_test'<K>
		//for k=0...J%TUPLE_SIZE-1
		//where at_test' is just at_test without the
		//recursive call to at_test<K+1>(...).
		return value+test_row<I,J+1>::exec();
	}
};
template<int I>
struct test_row<I,LAST_ROW>
{
	static int exec()
	{
	    return 0;
	}
};

//The combination of the above test_row special and the preceding general
//templates means the call:
//  test_row<I>::exec()
//executes:
//  test_row<I,J>::exec'()
//for J=0...LAST_ROW
//where exec' is exec without the recursive call to test_row<I,J+1>::exec().

template<int I=0>
struct test_col
{
	static int exec()
	{
		int const value=test_row<I>::exec();
		return value+test_col<I+1>::exec();
	}
};

template<>
struct test_col<LAST_COL>
{
	static int exec()
	{
	    return 0;
	}
};

int main()
{
	std::cout<<"TUPLE_SIZE="<<TUPLE_SIZE<<"\n";
	std::cout<<"LAST_ROW="<<LAST_ROW<<"\n";
	int const value=test_col<>::exec();
	//The combination of the test_col general and special templates
	//means the above call executes:
	//  test_row<I>::exec()
	//for I=0...LAST_COL
	std::cout<<"value="<<value<<"\n";
      #if defined(BOOST_NO_VARIADIC_TEMPLATES)
        std::cout<<"BOOST_NOT_VARIADIC_TEMPLATES\n";
      #else
        std::cout<<"BOOST_YES_VARIADIC_TEMPLATES\n";
      #endif
	return value==0;
}
