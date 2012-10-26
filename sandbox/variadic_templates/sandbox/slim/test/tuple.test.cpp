//Acknowlegements:
//  The following code was adapted from part of the code in
//    https://github.com/ericniebler/home/blob/master/src/tuple/unrolled_tuple.hpp
//ChangeLog:
//  2012-10-26 LJ Evans
//    1) Copied the code after the line:
//        #ifdef TEST
//       in the above mentioned unrolled_tuple.hpp file.
//    2) Added the boostpp #includes.
//    3) Used the boostpp stringize to #include the tuple implementation code
//       named by a macro.
//
///////////////////////////////////////////////////////////////////////////////
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/preprocessor/stringize.hpp>
#ifndef TUPLE_IMPL
#define TUPLE_IMPL tuple_impl_bcon12_vertical.hpp
#endif
#include BOOST_PP_STRINGIZE(TUPLE_IMPL)

#include <cstdio>
//////////////////////////////////////////////////////
//{copied from unrolled_tuple.hpp:

struct S
{
    S() { std::printf("not constexpr!\n"); }
};

// What is a literal type?

constexpr tuple_bench<> t0{};
static_assert(std::is_trivial<tuple_bench<>>::value, "not trivial");

constexpr tuple_bench<int> t1{42};
static_assert(std::is_trivial<tuple_bench<int>>::value, "not trivial");

constexpr tuple_bench<int, float> t2{1, 3.14f};
static_assert(std::is_trivial<tuple_bench<int, float>>::value, "not trivial");

constexpr tuple_bench<int, tuple_bench<int, float>> t3{1, tuple_bench<int, float>{2, 3.14f}};
static_assert(std::is_trivial<tuple_bench<int, tuple_bench<int, float>>>::value, "not trivial");

constexpr int i = get<0>(t1);
static_assert(i == 42, "not a compile-time constant");

constexpr float f = get<1>(t2);
static_assert(f == 3.14f, "not a compile-time constant");

//static_assert(std::is_same<int, tuple_bench_element<0, tuple_bench<int>>::type>::value, "wrong element");
//static_assert(std::is_same<float &, tuple_bench_element<1, tuple_bench<int, float &>>::type>::value, "wrong element");

// Make sure I understand how decltype, rvalues and lvalues work.
struct T { S s; };
static_assert(!std::is_reference<decltype((T().s))>::value, "not is rvalue ref");
static_assert(std::is_reference<decltype((static_cast<T &&>(T()).s))>::value, "is rvalue ref");
static_assert(!std::is_lvalue_reference<decltype((static_cast<T &&>(T()).s))>::value, "is lvalue ref");

void test()
{
    tuple_bench<S> s,t;
    t = s;
    S &ss = get<0>(s);
    get<0>(s) = get<0>(t);
    S && sss = get<0>(::make_tuple(S()));
    static_assert(std::is_reference<decltype(get<0>(::make_tuple(S())))>::value, "");
    static_assert(!std::is_lvalue_reference<decltype(get<0>(::make_tuple(S())))>::value, "");

    int i = 0;
    tuple_bench<int &> ti{i};
    tuple_bench<int &> ti2(ti);
    static_assert(std::is_lvalue_reference<decltype(get<0>(ti2))>::value, "");

    static_assert(sizeof(tuple_bench<char,char,char>)==3, "wrong size");

    std::printf("%f\n", (double)f);;
}
//}copied from unrolled_tuple.hpp:

int main()
{
    test();
    return 0;
}    
