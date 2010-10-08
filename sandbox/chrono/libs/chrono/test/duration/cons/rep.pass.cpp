//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono.hpp>
#include <boost/detail/lightweight_test.hpp>

#include "../../rep.h"

template <class D, class R>
void
test(R r)
{
    D d(r);
    BOOST_TEST(d.count() == r);
}

int main()
{
    test<boost::chrono::duration<int> >(5);
    test<boost::chrono::duration<int, boost::ratio<3, 2> > >(5);
    test<boost::chrono::duration<Rep, boost::ratio<3, 2> > >(Rep(3));
    test<boost::chrono::duration<double, boost::ratio<2, 3> > >(5.5);
    return boost::report_errors();
}
