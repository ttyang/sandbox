/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_TEST_ICL_STATIC_INTERVAL_HPP_JOFA_100930
#define BOOST_ITL_TEST_ICL_STATIC_INTERVAL_HPP_JOFA_100930

template <class T, class IntervalT> 
void static_interval_ctor_4_ordered_types()
{
    BOOST_CHECK_EQUAL(itl::is_empty(IntervalT()), true);
    BOOST_CHECK_EQUAL(itl::cardinality(IntervalT()), itl::identity_element<typename itl::size_type_of<T>::type>::value());
    BOOST_CHECK_EQUAL(itl::size(IntervalT()), itl::identity_element<typename itl::size_type_of<T>::type>::value());

    BOOST_CHECK_EQUAL( IntervalT(), IntervalT() );
    BOOST_CHECK_EQUAL( IntervalT(), IntervalT(IntervalT().lower(), IntervalT().upper()) );
    BOOST_CHECK_EQUAL( IntervalT(), IntervalT(itl::lower(IntervalT()), itl::upper(IntervalT())) );
}


#endif // BOOST_ITL_TEST_ICL_STATIC_INTERVAL_HPP_JOFA_100930
