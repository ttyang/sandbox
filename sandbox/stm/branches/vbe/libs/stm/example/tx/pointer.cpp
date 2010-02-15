//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/stm for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/stm.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <assert.h>
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace boost;

struct A {
    A() : i(0), ptr(&i) {

    }
    stm::tx::int_t i;
    stm::tx::pointer<stm::tx::int_t> const ptr;
};

struct B {
    B() : a_ptr() {}
    stm::tx::pointer<A> a_ptr;
};


bool test_ptr_to_tx_const() {
    #if 0
    {
    const int ci = 10;
    const int cj = 20;
    const int * pc = &ci;
    const int * pc2 = &cj;
    pc=&cj;
    const int * const cpc = pc;
    //cpc=pc2; // this must not compile
    const int ** ppc;
    }
    #endif
    const stm::tx::int_t ci = 10;
    const stm::tx::int_t cj = 20;
    stm::tx::pointer<const stm::tx::int_t > pc = &ci;
    stm::tx::pointer<const stm::tx::int_t > pc2 = &cj;
    pc=&cj;
    stm::tx::pointer<const stm::tx::int_t > const cpc = pc;
    //cpc=pc2; // this must not compile
    stm::tx::pointer<stm::tx::pointer<const stm::tx::int_t > > ppc;
    return true;
}
bool test_ptr_to_const() {
    const int ci = 10;
    const int cj = 20;
    stm::tx::pointer<const int> pc = &ci;
    stm::tx::pointer<const int> pc2 = &cj;
    stm::tx::pointer<const int> const cpc = pc;
    //cpc=pc2; // this must not compile
    stm::tx::pointer<stm::tx::pointer<const int> > ppc;
    BOOST_STM_OUTER_TRANSACTION(_) {
        pc=&cj;
    } BOOST_STM_RETRY
    BOOST_STM_OUTER_TRANSACTION(_) {
        BOOST_STM_TX_RETURN(_, (pc==&cj)&&(*pc==20)&&(*cpc==10));
    } BOOST_STM_RETRY
    return false;
}

bool test_ptr_to_const2() {
    const int ci = 10;
    const int cj = 20;
    stm::tx::pointer<const int> pc = &ci;
    stm::tx::pointer<const int> pc2 = &cj;
    stm::tx::pointer<const int> const cpc = pc;
    //cpc=pc2; // this must not compile
    stm::tx::pointer<stm::tx::pointer<const int> > ppc;
    BOOST_STM_OUTER_TRANSACTION(_) {
        pc=pc2;
    } BOOST_STM_RETRY
    BOOST_STM_OUTER_TRANSACTION(_) {
        BOOST_STM_TX_RETURN(_, (pc==&cj)&&(*pc==20)&&(*cpc==10));
    } BOOST_STM_RETRY
    return false;
}


bool test_ptr_to_tx() {
    stm::tx::int_t i;
    stm::tx::pointer<stm::tx::int_t > p;
    stm::tx::pointer<stm::tx::int_t > const cp = &i;
    BOOST_STM_OUTER_TRANSACTION(_) {
        i=5;
        p=&i;
    } BOOST_STM_RETRY
    BOOST_STM_OUTER_TRANSACTION(_) {
        BOOST_STM_TX_RETURN(_, (i==5)&&(p==&i));
    } BOOST_STM_RETRY
    return false;
}

bool test_ptr_to_tx_assignment() {
    A a;
    B b;
    BOOST_STM_OUTER_TRANSACTION(_) {
        b.a_ptr=&a;
        b.a_ptr->i =1;
    } BOOST_STM_RETRY
    BOOST_STM_OUTER_TRANSACTION(_) {
        BOOST_STM_TX_RETURN(_, (b.a_ptr->i==1)&&(*b.a_ptr->ptr==1));
    } BOOST_STM_RETRY
    return false;
}

int test_all() {


    int fails=0;
    fails += !test_ptr_to_tx_const();
    fails += !test_ptr_to_tx();
    fails += !test_ptr_to_const();
    fails += !test_ptr_to_tx_assignment();
    return fails;
}

int main() {
    stm::transaction::enable_dynamic_priority_assignment();
    stm::transaction::do_deferred_updating();
    stm::transaction::initialize();
    stm::thread_initializer thi;
    return test_all();
}
