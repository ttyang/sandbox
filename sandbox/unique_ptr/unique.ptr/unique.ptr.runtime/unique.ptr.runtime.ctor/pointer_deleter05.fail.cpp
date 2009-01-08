// Copyright 2009 Howard Hinnant.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation

// [unique.ptr.runtime.ctor]
// Test unique_ptr(pointer, deleter) ctor

#include "unique_ptr.hpp"
#include <cassert>

// unique_ptr(pointer, deleter) should not work with derived pointers

struct A
{
    static int count;
    A() {++count;}
    A(const A&) {++count;}
    virtual ~A() {--count;}
};

int A::count = 0;

struct B
    : public A
{
    static int count;
    B() {++count;}
    B(const B&) {++count;}
    virtual ~B() {--count;}
};

int B::count = 0;

class Deleter
{
    int state_;

public:
    Deleter() : state_(5) {}

    int state() const {return state_;}

    void operator()(A* p) {delete [] p;}
};

int main()
{
    B* p = new B[3];
    boost::unique_ptr<A[], Deleter> s(p, Deleter());
}
