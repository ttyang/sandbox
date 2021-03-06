//////////////////////////////////////////////////////////////////////////////
//
//  smart_ptr_test.cpp
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) David B. Held 2002-2003.
//
//  See http://www.boost.org/ for most recent version, including documentation.
//
//  Permission is hereby granted, free of charge, to any person or organization
//  obtaining a copy of the software and accompanying documentation covered by
//  this license (the "Software") to use, reproduce, display, distribute,
//  execute, and transmit the Software, and to prepare derivative works of the
//  Software, and to permit third-parties to whom the Software is furnished to
//  do so, all subject to the following:
//
//  The copyright notices in the Software and this entire statement, including
//  the above license grant, this restriction and the following disclaimer,
//  must be included in all copies of the Software, in whole or in part, and
//  all derivative works of the Software, unless such copies or derivative
//  works are solely in the form of machine-executable object code generated by
//  a source language processor.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//  FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////////
//
//  This is the main test program for the policy-based smart pointer library.
//  All tests should pass.  The ordering_test.cpp tests the ordering comparison
//  operators (in a separate file, because they are enabled via a macro).  See
//  libs/policy_ptr/doc/index.html
//
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SMART_POINTER_BASIC_INTERFACE

#include <string>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "../smart_ptr.hpp"

// Hack for VC's lack of ADL
namespace boost
{
namespace test = unit_test_framework;
using mpl::_;

class object
{
public:
    object(bool& dead) : dead_(dead), dummy_(3.14159) { }
    virtual ~object(void) { BOOST_CHECK(!dead_); dead_ = true; }

    int foo(void) const { return 42; }
    double bar(void) const { return dummy_; }
private:
    bool& dead_;
    double dummy_;
};

class child : public object
{
public:
    child(bool& dead, int age) : object(dead), age_(age) { }

    int age(void) const { return age_; }
private:
    int age_;
};

void default_test(void)
{
    smart_ptr<object> p;
    object* q = 0;
    BOOST_CHECK_EQUAL(sizeof(p), sizeof(object*) + sizeof(int));
    BOOST_CHECK(!p);
    BOOST_CHECK(p == q);
    BOOST_CHECK(!get_impl(p));
}

void init_const_test(smart_ptr<object> const& p)
{
    BOOST_CHECK_EQUAL(p->foo(), 42);
    BOOST_CHECK_EQUAL((*p).bar(), 3.14159);
}

void init_test(void)
{
    bool dead(false);
    {
        smart_ptr<object> p(new object(dead));
        BOOST_CHECK_EQUAL(p->foo(), 42);
        BOOST_CHECK_EQUAL((*p).bar(), 3.14159);
        init_const_test(p);
        smart_ptr<object> q;
        BOOST_CHECK(p != q);
        BOOST_CHECK(p ? true : false);
    }
    BOOST_CHECK(dead);
}

void copy_test(void)
{
    bool dead(false);
    {
        smart_ptr<object, ref_counted<_>, assert_check<_> > p(new object(dead));
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        bool dead_child(false);
        {
            smart_ptr<object, scalar_storage<_> > q(p);
            BOOST_CHECK(p == q);
            BOOST_CHECK_EQUAL(q->foo(), 42);
            BOOST_CHECK_EQUAL(use_count(p), 2u );
            BOOST_CHECK_EQUAL(use_count(q), 2u );

            reset(q, new child(dead_child, 3));
            smart_ptr<child> c(
                static_pointer_cast<child>(q)
            );
            BOOST_CHECK_EQUAL(use_count(c), 2u );
            smart_ptr<child> d(dynamic_pointer_cast<child>(q));
            BOOST_CHECK_EQUAL(use_count(q), 3u );
        }
        BOOST_CHECK(dead_child);
        BOOST_CHECK_EQUAL(use_count(p), 1u );
    }
    BOOST_CHECK(dead);
}

void assign_test(void)
{
    using boost::swap;
    bool dead(false);
    bool dead2(false);
    child* x = 0;
    {
        smart_ptr<child> p(new child(dead, 14));
        smart_ptr<object> q;
        q = p;
        BOOST_CHECK(p == q);
        BOOST_CHECK_EQUAL(use_count(p), 2u );
        smart_ptr<child> c;
        c = p;
        BOOST_CHECK_EQUAL(use_count(p), 3u );
        smart_ptr<child> d(new child(dead2, 27));
        swap(c, d);
        BOOST_CHECK_EQUAL(d->age(), 14);
        BOOST_CHECK_EQUAL(c->age(), 27);
        BOOST_CHECK_EQUAL(use_count(c), 1u );
        release(c, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK_EQUAL(use_count(c), 0u );
        BOOST_CHECK(!c);
    }
    BOOST_CHECK(dead);
    BOOST_CHECK(!dead2);
    delete x;
}

class element
{
public:
    ~element(void) { ++deaths_; }
    int x(void) const { return x_; }
    element& operator=(int x) { x_ = x; return *this; }

    static int deaths(void) { return deaths_; }
private:
    static int deaths_;
    int x_;
};

int element::deaths_ = 0;

void array_test(void)
{
    {
        smart_ptr<element, array_storage<_> > p(new element[4]);
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(element*) + sizeof(int));
        p[0] = 3;
        p[1] = 5;
        p[2] = 7;
        p[3] = 11;
        BOOST_CHECK_EQUAL(p[2].x(), 7);
        BOOST_CHECK_EQUAL(p[0].x(), 3);
        BOOST_CHECK_EQUAL(p[3].x(), 11);
        BOOST_CHECK_EQUAL(p[1].x(), 5);
        smart_ptr<element, array_storage<_> > q;
        q = p;
        BOOST_CHECK(q == p);
        element* x;
        reset(q, 0);
        release(p, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!p);
        reset(q, x);
    }
    BOOST_CHECK_EQUAL(element::deaths(), 4);
}

struct com_base
{
    virtual void AddRef(void) = 0;
    virtual long Release(void) = 0;
};

class com_object
{
public:
    com_object(int x) : x_(x), count_(1) { }
    int x(void) const { return x_; }
    int count(void) const { return count_; }
    void AddRef(void) { ++count_; }
    long Release(void) { return --count_; }
private:
    int x_;
    int count_;
};

void com_test(void)
{
    com_object c(37);
    {
        smart_ptr<com_object, com_ref_counted<_> > p(&c);
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(com_object*));
        BOOST_CHECK_EQUAL(p->x(), 37);
        BOOST_CHECK_EQUAL(p->count(), 1);
        smart_ptr<com_object, com_ref_counted<_> > q = p;
        BOOST_CHECK(p == q);
        BOOST_CHECK_EQUAL(p->count(), 2);
        reset(q, new com_object(99));
        BOOST_CHECK_EQUAL(p->count(), 1);
        com_object* x = 0;
        release(q, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK_EQUAL(x->count(), 1);
        BOOST_CHECK(!q);
        delete x;
    }
    BOOST_CHECK_EQUAL(c.count(), 0);
}

void ref_linked_test(void)
{
#ifndef BOOST_MSVC
    bool dead(false);
    bool dead2(false);
    {
        smart_ptr<object, ref_linked<_> > p(new object(dead));
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(object*) + sizeof(&p) * 2);
        BOOST_CHECK_EQUAL(p->foo(), 42);
        smart_ptr<object, ref_linked<_> > q = p;
        BOOST_CHECK(p == q);
        reset(q, new object(dead2));
        BOOST_CHECK(p != q);
        object* x = 0;
        release(q, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!q);
        BOOST_CHECK(!dead2);
        delete x;
    }
    BOOST_CHECK(dead);
    BOOST_CHECK(dead2);
#else
    bool ref_linked_unsupported_on_mscv = false;
    BOOST_CHECK(ref_linked_unsupported_on_mscv);
#endif
}

class dolly
{
public:
    dolly(int x) : x_(x) { ++births_; }
    ~dolly() { ++deaths_; }
    int x(void) const { return x_; }
    dolly* clone(void) const { ++births_; return new dolly(*this); }
    static int births(void) { return births_; }
    static int deaths(void) { return deaths_; }
private:
    static int births_;
    static int deaths_;
    int x_;
};

int dolly::births_;
int dolly::deaths_;

void deep_copy_test(void)
{
    {
        smart_ptr<dolly, deep_copy<_> > p(new dolly(8));
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(dolly*));
        BOOST_CHECK_EQUAL(p->x(), 8);
        smart_ptr<dolly, deep_copy<_> > q;
        q = p;
        BOOST_CHECK(p != q);
        BOOST_CHECK_EQUAL(dolly::births(), 2);
        reset(q, new dolly(16));
        BOOST_CHECK(p != q);
        BOOST_CHECK_EQUAL(dolly::deaths(), 1);
        BOOST_CHECK_EQUAL((*q).x(), 16);
        dolly* x = 0;
        release(q, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!q);
        delete x;
    }
    BOOST_CHECK_EQUAL(dolly::births(), 3);
    BOOST_CHECK_EQUAL(dolly::deaths(), 3);
}

void no_copy_test(void)
{
    bool dead(false);
    bool dead2(false);
    {
        smart_ptr<object, no_copy<_> > p(new object(dead));
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(object*));
        BOOST_CHECK_EQUAL(p->foo(), 42);
        object* x = 0;
        release(p, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!p);
        reset(p, new object(dead2));
        BOOST_CHECK(p != x);
        delete x;
        smart_ptr<object>::rebind<dolly>::other q;
    }
    BOOST_CHECK(dead);
    BOOST_CHECK(dead2);
}

void conversion_test(void)
{
    bool dead(false);
    {
        smart_ptr<object, allow_conversion<_> > p(new object(dead));
        object* x = p;
        (void) x;
    }
    BOOST_CHECK(dead);
}

void concept_interface_test(void)
{
    bool dead(false);
    bool dead2(false);
    smart_ptr<object> p(new object(dead));
    object* x = get_pointer(p);
    BOOST_CHECK(x == p);
    object y(dead2);
    smart_ptr<object> q(&y);
    less<
        object, ref_counted<_>, assert_check<_>,
        disallow_conversion<_>, scalar_storage<_>
    > comp;
    if (x < &y)
    {
        BOOST_CHECK(comp(p, q));
    }
    else
    {
        BOOST_CHECK(comp(q, p));
    }
    release(q, x);
}
}

using namespace boost;
test::test_suite* init_unit_test_suite(int argc, char* argv[])
{
    test::test_suite* test = BOOST_TEST_SUITE("Basic smart_ptr framework tests");

    test->add(BOOST_TEST_CASE(&default_test));
    test->add(BOOST_TEST_CASE(&init_test));
    test->add(BOOST_TEST_CASE(&copy_test));
    test->add(BOOST_TEST_CASE(&assign_test));
    test->add(BOOST_TEST_CASE(&array_test));
    test->add(BOOST_TEST_CASE(&com_test));
    test->add(BOOST_TEST_CASE(&ref_linked_test));
    test->add(BOOST_TEST_CASE(&deep_copy_test));
    test->add(BOOST_TEST_CASE(&no_copy_test));
    test->add(BOOST_TEST_CASE(&conversion_test));
    test->add(BOOST_TEST_CASE(&concept_interface_test));

    return test;
}
