#if !defined(TUPLE_SIZE)
  //This only used when not running several benchmarks where
  //macro values are set on command line with -DMACRO=VALUE.
  //See tuple.benchmark.mk.
  #define TUPLE_IMPL tuple_impl_horizontal.hpp
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
  #define LAST_LESS 4
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
