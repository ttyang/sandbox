#include "macros.benchmark.pp.hpp"
#include <boost/preprocessor/stringize.hpp>
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

template<int Index>
struct int_key //key's (or indices) to values stored in tuple.
{
};

#include BOOST_PP_STRINGIZE(TUPLE_IMPL)

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
	typedef tuple_bench<Args...> type;
};

//#define TRACE_MAIN
#if defined(TRACE_BENCHMARK)||defined(TRACE_MAIN)
  #include <iostream>
#endif

template<int I,int J=0>
struct test_row
{
 private:
	typedef typename make_tuple<I, J, TUPLE_SIZE>::type tuple_type;

	template<int K>
	static int at_test(tuple_type& t,int_key<K>)
	{
		int const value=
#ifdef VALU_AT
                  get<K>(t).value
#else
                  K
#endif
                ;
              #ifdef TRACE_BENCHMARK
                std::cout<<"at_test:K="<<K<<"\n";
              #endif
		return value+at_test(t,int_key<K+1>());
	}
	static int at_test(tuple_type&,int_key<TUPLE_SIZE>)
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
                std::cout<<"tuple_type="<<utility::demangled_type_name<tuple_type>()<<"\n";
              #endif
		tuple_type t;
		int const value=at_test(t,int_key<0>());
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
    
  #ifdef TRACE_MAIN
    std::cout<<"TUPLE_TEST_IMPL="<<TUPLE_TEST_IMPL<<"\n";
    std::cout<<"TUPLE_SIZE="<<TUPLE_SIZE<<"\n";
    std::cout<<"LAST_ROW="<<LAST_ROW<<"\n";
  #endif
	int const value=test_col<>::exec();
    //The combination of the test_col general and special templates
    //means the above call executes:
    //  test_row<I>::exec() 
    //for I=0...LAST_COL
  #ifdef TRACE_MAIN    
    std::cout<<"value="<<value<<"\n";
  #endif
    return value==0;
}
