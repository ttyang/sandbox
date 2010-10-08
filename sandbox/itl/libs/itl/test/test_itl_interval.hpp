/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_TEST_ITL_INTERVAL_HPP_JOFA_081006
#define BOOST_ITL_TEST_ITL_INTERVAL_HPP_JOFA_081006

template <class T, class IntervalT> 
void interval_ctor_4_ordered_types()
{
    T lower_bound = given<mpl::or_<is_static_right_open<IntervalT>, is_static_open<IntervalT> >, T>
                        ::then(identity_element<T>::value(), unit_element<T>::value());

    typedef typename domain_type_of<IntervalT>::type Dom1T;
    typedef typename domain_type_of<interval_traits<IntervalT> >::type Dom2T;
    BOOST_CHECK_EQUAL(is_same<Dom1T, Dom2T>::value, true);


    // An empty interval is defined as the closed interval [1,0]
    BOOST_CHECK_EQUAL(itl::is_empty(IntervalT()), true);
    BOOST_CHECK_EQUAL(itl::cardinality(IntervalT()), itl::identity_element<typename itl::size_type_of<T>::type>::value());
    BOOST_CHECK_EQUAL(itl::size(IntervalT()), itl::identity_element<typename itl::size_type_of<T>::type>::value());
    BOOST_CHECK_EQUAL(IntervalT().lower(), lower_bound);
    BOOST_CHECK_EQUAL(IntervalT().upper(), itl::identity_element<T>::value());
    BOOST_CHECK_EQUAL(itl::lower(IntervalT()), lower_bound);
    BOOST_CHECK_EQUAL(itl::upper(IntervalT()), itl::identity_element<T>::value());

    BOOST_CHECK_EQUAL(IntervalT(), IntervalT());
    BOOST_CHECK_EQUAL(IntervalT(), IntervalT(lower_bound, itl::identity_element<T>::value()));
}

/*JODO
template <class T> 
void interval_ctor_4_bicremental_types()
{
    BOOST_CHECK_EQUAL( T(), pred(succ(T())));
    BOOST_CHECK_EQUAL( itl::identity_element<T>::value(), pred(succ(itl::identity_element<T>::value()))       );
    BOOST_CHECK_EQUAL( itl::unit_element<T>::value(),    succ(itl::identity_element<T>::value())             );
    BOOST_CHECK_EQUAL( interval<T>().length(),   itl::identity_element<typename difference_type_of<T>::type>::value() );

    T v4 = make<T>(4);
    itl::interval<T> I4_4I(v4);
    BOOST_CHECK_EQUAL( I4_4I.is(closed_bounded),         true  );
    BOOST_CHECK_EQUAL( I4_4I.is(left_open),       false );
    BOOST_CHECK_EQUAL( I4_4I.is(right_open),      false );
    BOOST_CHECK_EQUAL( I4_4I.is(open_bounded),           false );
    BOOST_CHECK_EQUAL( I4_4I.is_left(closed_bounded),  true  );
    BOOST_CHECK_EQUAL( I4_4I.is_right(closed_bounded), true  );
    BOOST_CHECK_EQUAL( I4_4I.is_left(open_bounded),    false );
    BOOST_CHECK_EQUAL( I4_4I.is_right(open_bounded),   false );

    BOOST_CHECK_EQUAL( I4_4I.lower(),             v4    );
    BOOST_CHECK_EQUAL( I4_4I.upper(),             v4    );

    BOOST_CHECK_EQUAL( I4_4I.contains(v4),        true  );
    BOOST_CHECK_EQUAL( I4_4I.contains(I4_4I),     true  );
    BOOST_CHECK_EQUAL( I4_4I.contained_in(I4_4I), true  );
    BOOST_CHECK_EQUAL( I4_4I,                     I4_4I );

    BOOST_CHECK_EQUAL( I4_4I.cardinality(),       unit_element<typename interval<T>::size_type>::value()          );
    BOOST_CHECK_EQUAL( I4_4I.size(),              unit_element<typename interval<T>::size_type>::value()          );
    //BOOST_CHECK_EQUAL( I4_4I.length(),          identity_element<typename interval<T>::difference_type>::value() );

    itl::interval<T> j_4_4(I4_4I);
    BOOST_CHECK_EQUAL( I4_4I, j_4_4 );
    interval<T> k_4_4;
    k_4_4 = j_4_4;
    BOOST_CHECK_EQUAL( I4_4I, k_4_4 );

    T v2 = make<T>(2);
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4),    interval<T>(v2, v4) );
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4),    interval<T>(v2, v4, closed_bounded) );
    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4), interval<T>(v2, v4, right_open) );
    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4),  interval<T>(v2, v4, left_open) );
    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4),      interval<T>(v2, v4, open_bounded) );

    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4).lower(),               v2 );
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4).upper(),               v4 );
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4).boundtype(),           closed_bounded );
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4).is(closed_bounded),    true );
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4).is_left(closed_bounded),    true );
    BOOST_CHECK_EQUAL( interval<T>::closed(v2, v4).is_right(closed_bounded),   true );

    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4).lower(),            v2 );
    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4).upper(),            v4 );
    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4).boundtype(),        right_open );
    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4).is(right_open),     true );
    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4).is_left(closed_bounded), true );
    BOOST_CHECK_EQUAL( interval<T>::right_open(v2, v4).is_right(open_bounded),  true );

    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4).lower(),             v2 );
    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4).upper(),             v4 );
    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4).boundtype(),         left_open );
    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4).is(left_open),       true );
    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4).is_left(open_bounded),    true );
    BOOST_CHECK_EQUAL( interval<T>::left_open(v2, v4).is_right(closed_bounded), true );

    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4).lower(),                 v2 );
    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4).upper(),                 v4 );
    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4).boundtype(),            open_bounded );
    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4).is(open_bounded),               true );
    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4).is_left(open_bounded),        true );
    BOOST_CHECK_EQUAL( interval<T>::open(v2, v4).is_right(open_bounded),       true );    
}

template <class T> 
void interval_ctor_4_integral_types()
{
    BOOST_CHECK_EQUAL(interval<T>().first(),  itl::unit_element<T>::value());
    BOOST_CHECK_EQUAL(interval<T>().last(),   itl::identity_element<T>::value());
    BOOST_CHECK_EQUAL(interval<T>().length(), itl::identity_element<typename interval<T>::difference_type>::value());

    BOOST_CHECK_EQUAL(interval<T>(0,0).length(), itl::unit_element<typename interval<T>::difference_type>::value());
}

void interval_ctor_specific()//JODO 
{
    BOOST_CHECK_EQUAL(interval<double>().length(), 0.0);
    BOOST_CHECK_EQUAL(interval<double>(5.0,5.0).cardinality(), 1);
    BOOST_CHECK_EQUAL(interval<std::string>("test","test").cardinality(), 1);
    BOOST_CHECK_EQUAL(interval<std::string>("best","test").cardinality(), interval<double>(0.0,0.1).cardinality());
}

template <class T> 
void interval_equal_4_integral_types()
{
    T v2 = make<T>(2);
    T v3 = make<T>(3);
    T v7 = make<T>(7);
    T v8 = make<T>(8);
    BOOST_CHECK_EQUAL(interval<T>(), interval<T>(v7,v3));

    //I: (I)nside  = closed bound
    //C: left open bound
    //D: right open bound
    interval<T>  I3_7I  = interval<T>::closed(v3,v7);
    interval<T>  I3__8D = interval<T>::right_open(v3,v8);
    interval<T> C2__7I  = interval<T>::left_open(v2,v7);
    interval<T> C2___8D = interval<T>::open(v2,v8);

    BOOST_CHECK_EQUAL(  I3_7I ,  I3_7I  );    
    BOOST_CHECK_EQUAL(  I3_7I ,  I3__8D );    
    BOOST_CHECK_EQUAL(  I3_7I , C2__7I  );    
    BOOST_CHECK_EQUAL(  I3_7I , C2___8D );    

    BOOST_CHECK_EQUAL(  I3__8D,  I3__8D );    
    BOOST_CHECK_EQUAL(  I3__8D, C2__7I  );    
    BOOST_CHECK_EQUAL(  I3__8D, C2___8D );    

    BOOST_CHECK_EQUAL( C2__7I , C2__7I  );    
    BOOST_CHECK_EQUAL( C2__7I , C2___8D );    

    BOOST_CHECK_EQUAL( C2___8D, C2___8D );    
}


template <class T> 
void interval_less_4_integral_types()
{
    T v2 = make<T>(2);
    T v3 = make<T>(3);
    T v4 = make<T>(4);
    T v7 = make<T>(7);
    T v8 = make<T>(8);
    BOOST_CHECK_EQUAL(interval<T>() < interval<T>(v7,v3), false);
    BOOST_CHECK_EQUAL(interval<T>::open(v2,v3) < interval<T>::right_open(v7,v7), false);
    BOOST_CHECK_EQUAL(interval<T>::left_open(v3,v3) < interval<T>::closed(v7,v3), false);

    BOOST_CHECK_EQUAL(interval<T>() < interval<T>(v3,v3), true);
    BOOST_CHECK_EQUAL(interval<T>::open(v2,v3) < interval<T>::right_open(v7,v8), true);

    //I: (I)nside  = closed bound
    //C: left open bound
    //D: right open bound
    interval<T>  I3_7I  = interval<T>::closed(v3,v7);
    interval<T>  I4_7I  = interval<T>::closed(v4,v7);

    interval<T>  I3__8D = interval<T>::right_open(v3,v8);
    interval<T> C2__7I  = interval<T>::left_open(v2,v7);
    interval<T> C2___8D = interval<T>::open(v2,v8);

    BOOST_CHECK_EQUAL(  I3_7I <  I3_7I  , false);    
    BOOST_CHECK_EQUAL(  I3_7I <  I3__8D , false);    
    BOOST_CHECK_EQUAL(  I3_7I < C2__7I  , false);    
    BOOST_CHECK_EQUAL(  I3_7I < C2___8D , false);    

    BOOST_CHECK_EQUAL(  I3_7I <  I4_7I  , true);    


    BOOST_CHECK_EQUAL(  I3__8D<  I3__8D , false);    
    BOOST_CHECK_EQUAL(  I3__8D< C2__7I  , false);    
    BOOST_CHECK_EQUAL(  I3__8D< C2___8D , false);    

    BOOST_CHECK_EQUAL( C2__7I < C2__7I  , false);    
    BOOST_CHECK_EQUAL( C2__7I < C2___8D , false);    

    BOOST_CHECK_EQUAL( C2___8D< C2___8D , false);    
}


template <class T> 
void interval_equal_4_bicremental_continuous_types()
{
    T v3 = make<T>(3);
    T v7 = make<T>(7);
    BOOST_CHECK_EQUAL(interval<T>(), interval<T>(v7,v3));

    //I: (I)nside  = closed bound
    //O: (O)utside = open bound
    interval<T> I3_7I = interval<T>::closed(v3,v7);
    interval<T> I3_7D = interval<T>::right_open(v3,v7);
    interval<T> C3_7I = interval<T>::left_open(v3,v7);
    interval<T> C3_7D = interval<T>::open(v3,v7);

    BOOST_CHECK_EQUAL( I3_7I ,  I3_7I  );    
    BOOST_CHECK_EQUAL( I3_7I == I3_7D, false  );    
    BOOST_CHECK_EQUAL( I3_7I == C3_7D, false  );    
    BOOST_CHECK_EQUAL( I3_7I == C3_7D, false );    
    BOOST_CHECK_EQUAL( I3_7I != I3_7D, true  );    
    BOOST_CHECK_EQUAL( I3_7I != C3_7D, true  );    
    BOOST_CHECK_EQUAL( I3_7I != C3_7D, true );    

    BOOST_CHECK_EQUAL( I3_7D ,  I3_7D  );    
    BOOST_CHECK_EQUAL( I3_7D == C3_7I, false  );    
    BOOST_CHECK_EQUAL( I3_7D == C3_7D, false );    
    BOOST_CHECK_EQUAL( I3_7D != C3_7I, true  );    
    BOOST_CHECK_EQUAL( I3_7D != C3_7D, true );    

    BOOST_CHECK_EQUAL( C3_7I ,  C3_7I  );    
    BOOST_CHECK_EQUAL( C3_7I == C3_7D, false );    
    BOOST_CHECK_EQUAL( C3_7I != C3_7D, true );    

    BOOST_CHECK_EQUAL( C3_7D,   C3_7D  );    
} 

template <class T> 
void interval_touches_4_bicremental_types()
{
    T v3 = make<T>(3);
    T v7 = make<T>(7);
    T v9 = make<T>(9);

    interval<T> I3_7D = interval<T>::right_open(v3,v7);
    interval<T> I7_9I = interval<T>::closed(v7,v9);
    BOOST_CHECK_EQUAL( I3_7D.touches(I7_9I), true );    

    interval<T> I3_7I = interval<T>::closed(v3,v7);
    interval<T> C7_9I = interval<T>::left_open(v7,v9);
    BOOST_CHECK_EQUAL( I3_7I.touches(C7_9I), true );

    BOOST_CHECK_EQUAL( I3_7D.touches(C7_9I), false );    
    BOOST_CHECK_EQUAL( I3_7I.touches(I7_9I), false );    
}

template <class T> 
void interval_touches_4_integral_types()
{
    T v3 = make<T>(3);
    T v6 = make<T>(6);
    T v7 = make<T>(7);
    T v9 = make<T>(9);

    interval<T> I3_6I = interval<T>::closed(v3,v6);
    interval<T> I7_9I = interval<T>::closed(v7,v9);
    BOOST_CHECK_EQUAL( I3_6I.touches(I7_9I), true );    

    interval<T> I3_7D = interval<T>::right_open(v3,v7);
    interval<T> C6_9I = interval<T>::left_open(v6,v9);
    BOOST_CHECK_EQUAL( I3_7D.touches(C6_9I), true );
}


template <class T> 
void interval_inplace_intersect_4_bicremental_types()
{
    T v0 = make<T>(0);
    T v3 = make<T>(3);
    T v4 = make<T>(4);
    T v5 = make<T>(5);
    T v6 = make<T>(6);
    T v7 = make<T>(7);
    T v9 = make<T>(9);

    interval<T> section;
    interval<T> I3_7D = interval<T>::right_open(v3,v7);

    interval<T> I0_3D = interval<T>::right_open(v0,v3);
    section = I3_7D; section &= I0_3D;
    BOOST_CHECK_EQUAL( I0_3D.is_disjoint(I3_7D), true );
    BOOST_CHECK_EQUAL( !I0_3D.intersects(I3_7D), true );
    BOOST_CHECK_EQUAL( is_disjoint(I0_3D,I3_7D), true );
    BOOST_CHECK_EQUAL( !intersects(I0_3D,I3_7D), true );
    BOOST_CHECK_EQUAL( section.empty(), true );
    BOOST_CHECK_EQUAL( section, interval<T>() );

    interval<T> I0_5D = interval<T>::right_open(v0,v5);
    section = I3_7D; section &= I0_5D;
    BOOST_CHECK_EQUAL( section, interval<T>::right_open(v3, v5) );

    interval<T> I0_9D = interval<T>::right_open(v0,v9);
    section = I3_7D; section &= I0_9D;
    BOOST_CHECK_EQUAL( section, I3_7D );

    interval<T> I4_5I = interval<T>::closed(v4,v5);
    section = I3_7D; section &= I4_5I;
    BOOST_CHECK_EQUAL( section, I4_5I );

    interval<T> C4_6D = interval<T>::open(v4,v6);
    section = I3_7D; section &= C4_6D;
    BOOST_CHECK_EQUAL( section, C4_6D );

    interval<T> C4_9I = interval<T>::left_open(v4,v9);
    section = I3_7D; section &= C4_9I;
    BOOST_CHECK_EQUAL( section, interval<T>::open(v4,v7) );

    interval<T> I7_9I = interval<T>::closed(v7,v9);
    section = I3_7D; section &= I7_9I;
    BOOST_CHECK_EQUAL( I3_7D.exclusive_less(I7_9I), true );
    BOOST_CHECK_EQUAL( I3_7D.is_disjoint(I7_9I), true );
    BOOST_CHECK_EQUAL( !I3_7D.intersects(I7_9I), true );
    BOOST_CHECK_EQUAL( is_disjoint(I3_7D,I7_9I), true );
    BOOST_CHECK_EQUAL( !intersects(I3_7D,I7_9I), true );
    BOOST_CHECK_EQUAL( section.empty(), true );
}

template <class T> 
void interval_infix_intersect_4_bicremental_types()
{
    T v0 = make<T>(0);
    T v3 = make<T>(3);
    T v4 = make<T>(4);
    T v5 = make<T>(5);
    T v6 = make<T>(6);
    T v7 = make<T>(7);
    T v9 = make<T>(9);

    interval<T> section;
    interval<T> I3_7D = interval<T>::right_open(v3,v7);

    interval<T> I0_3D = interval<T>::right_open(v0,v3);
    section = I3_7D & I0_3D;
    BOOST_CHECK_EQUAL( I0_3D.is_disjoint(I3_7D), true );
    BOOST_CHECK_EQUAL( section.empty(), true );
    BOOST_CHECK_EQUAL( section, interval<T>() );

    interval<T> I0_5D = interval<T>::right_open(v0,v5);
    section = I3_7D & I0_5D;
    BOOST_CHECK_EQUAL( section, interval<T>::right_open(v3, v5) );

    interval<T> I0_9D = interval<T>::right_open(v0,v9);
    section = I3_7D & I0_9D;
    BOOST_CHECK_EQUAL( section, I3_7D );

    interval<T> I4_5I = interval<T>::closed(v4,v5);
    section = I3_7D & I4_5I;
    BOOST_CHECK_EQUAL( section, I4_5I );

    interval<T> C4_6D = interval<T>::open(v4,v6);
    section = I3_7D & C4_6D;
    BOOST_CHECK_EQUAL( section, C4_6D );

    interval<T> C4_9I = interval<T>::left_open(v4,v9);
    section = I3_7D & C4_9I;
    BOOST_CHECK_EQUAL( section, interval<T>::open(v4,v7) );

    interval<T> I7_9I = interval<T>::closed(v7,v9);
    section = I3_7D & I7_9I;
    BOOST_CHECK_EQUAL( I3_7D.exclusive_less(I7_9I), true );
    BOOST_CHECK_EQUAL( I3_7D.is_disjoint(I7_9I), true );
    BOOST_CHECK_EQUAL( section.empty(), true );
}

template <class T> 
void interval_subtract_4_bicremental_types()
{
    T v0 = make<T>(0);
    T v2 = make<T>(2);
    T v3 = make<T>(3);
    T v4 = make<T>(4);
    T v6 = make<T>(6);
    T v7 = make<T>(7);

    interval<T> diff_1, diff_2;
    interval<T> I0_3D = interval<T>::right_open(v0,v3);
    interval<T> I2_6D = interval<T>::right_open(v2,v6);
    interval<T> I4_7D = interval<T>::right_open(v4,v7);
    interval<T> I6_7D = interval<T>::right_open(v6,v7);
    interval<T> I2_4D = interval<T>::right_open(v2,v4);

    diff_1 = right_subtract(I2_6D, I4_7D);
    BOOST_CHECK_EQUAL( diff_1, I2_4D );

    diff_2 = I2_6D;
    diff_2.right_subtract(I4_7D);
    BOOST_CHECK_EQUAL( diff_2, I2_4D );

    diff_1.clear();
    diff_1 = right_subtract(I0_3D, I4_7D);
    BOOST_CHECK_EQUAL( diff_1, I0_3D );
    
    // ---------------------------------
    diff_1 = left_subtract(I4_7D, I2_6D);
    BOOST_CHECK_EQUAL( diff_1, I6_7D );

    diff_2 = I4_7D;
    diff_2.left_subtract(I2_6D);
    BOOST_CHECK_EQUAL( diff_2, I6_7D );

    diff_1.clear();
    diff_1 = left_subtract(I4_7D, I0_3D);
    BOOST_CHECK_EQUAL( diff_1, I4_7D );

    diff_2 = I4_7D;
    diff_2.left_subtract(I0_3D);
    BOOST_CHECK_EQUAL( diff_2, I4_7D );
}
*/

/*JODO
template <class T> 
void interval_inner_complement_4_bicremental_types()
{
    test_inner_complement(interval<T>(), interval<T>());
    test_inner_complement(interval<T>(), I_D(6,9));
    test_inner_complement(C_D(2,4), interval<T>());
    test_inner_complement(I_I(2,5), C_I(3,9));
    test_inner_complement(I_I(2,4), I_D(6,9));
    test_inner_complement(I_D(7,9), C_I(0,3));
}
*/

#endif // __test_itl_interval_hpp_JOFA_081006__
