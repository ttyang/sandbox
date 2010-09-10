/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef __TEST_INTERVAL_QUANTIFIER_SHARED_H_JOFA_090119__
#define __TEST_INTERVAL_QUANTIFIER_SHARED_H_JOFA_090119__


template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void make_3_itv_maps_and_derivatives_1
                   (IntervalMap<T,U,Trt>& itv_map_a, 
					IntervalMap<T,U,Trt>& itv_map_b, 
					IntervalMap<T,U,Trt>& itv_map_c, 
					typename IntervalMap<T,U,Trt>::interval_mapping_type& val_pair,
					mapping_pair<T,U>& map_pair)
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;

    itv_map_a.add(IDv(3,6,1)).add(IIv(5,7,1));
    itv_map_b.add(CDv(1,3,1)).add(IDv(8,9,1));
    itv_map_c.add(IDv(0,9,2)).add(IIv(3,6,1)).add(IDv(5,7,1));

    val_pair = IDv(6,9,1);
    map_pair = K_v(5,1);
}


//------------------------------------------------------------------------------
// Monoid EAN
//------------------------------------------------------------------------------
template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_monoid_plus_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_MONOID_INSTANCE_WRT(plus) (map_a, map_b, map_c, val_pair, map_pair);
    CHECK_MONOID_INSTANCE_WRT(pipe) (map_a, map_b, map_c, val_pair, map_pair);
}


template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_monoid_et_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_MONOID_INSTANCE_WRT(et)   (map_a, map_b, map_c, val_pair, map_pair);
    //JODO so. CHECK_MONOID_INSTANCE_WRT(caret)(map_a, map_b, map_c, val_pair, map_pair);
}

//------------------------------------------------------------------------------
// Abelian monoid EANC
//------------------------------------------------------------------------------

template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_abelian_monoid_plus_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(plus) (map_a, map_b, map_c, val_pair, map_pair);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(pipe) (map_a, map_b, map_c, val_pair, map_pair);
}


template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_abelian_monoid_et_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(et)   (map_a, map_b, map_c, val_pair, map_pair);
    //JODO CHECK_ABELIAN_MONOID_INSTANCE_WRT(caret)(map_a, map_b, map_c, val_pair, map_pair); //valid 4 set codom only
}


//------------------------------------------------------------------------------
// Abelian partial invertive monoid 
//------------------------------------------------------------------------------
template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_partial_invertive_monoid_plus_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT(plus) (map_a, map_b, map_c, val_pair, map_pair);
    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT(pipe) (map_a, map_b, map_c, val_pair, map_pair);
}

//------------------------------------------------------------------------------
// Abelian partial invertive monoid with protonic equality for inversion
//------------------------------------------------------------------------------
template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_partial_invertive_monoid_plus_prot_inv_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(plus)(map_a, map_b, map_c, val_pair, map_pair);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(pipe)(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT_EQUAL(plus)(is_protonic_equal, map_a, map_b, map_c, val_pair, map_pair);
    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT_EQUAL(pipe)(is_protonic_equal, map_a, map_b, map_c, val_pair, map_pair);
}


//------------------------------------------------------------------------------
// Abelian group EANIC
//------------------------------------------------------------------------------
template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_abelian_group_plus_4_bicremental_types()
{
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_ABELIAN_GROUP_INSTANCE_WRT(plus) (map_a, map_b, map_c, val_pair, map_pair);
    CHECK_ABELIAN_GROUP_INSTANCE_WRT(pipe) (map_a, map_b, map_c, val_pair, map_pair);
}

//------------------------------------------------------------------------------
// (0 - x) + x =p= 0 
//------------------------------------------------------------------------------
template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, U),
                   ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, U),
                   ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, U),
                   ITL_INTERVAL(ITL_COMPARE)  Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, T, Compare),
                   ITL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap
          >
void itv_quantifier_check_abelian_group_plus_prot_inv_4_bicremental_types()
{
    // check abelian group wrt. + and inverability wrt. protonic equality =p= :
    // (1) (IntervalMapT, +) is an abelian group and
    // (2) The inverability law: (0 - x) + x =p= 0 holds.
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT map_a, map_b, map_c;
    typename IntervalMapT::interval_mapping_type val_pair;
    mapping_pair<T,U> map_pair;
    make_3_itv_maps_and_derivatives_1(map_a, map_b, map_c, val_pair, map_pair);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(plus) (map_a, map_b, map_c, val_pair, map_pair);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(pipe) (map_a, map_b, map_c, val_pair, map_pair);

    CHECK_ABELIAN_GROUP_INSTANCE_WRT_EQUAL(plus) (is_protonic_equal, map_a, map_b, map_c, val_pair, map_pair);
    CHECK_ABELIAN_GROUP_INSTANCE_WRT_EQUAL(pipe) (is_protonic_equal, map_a, map_b, map_c, val_pair, map_pair);
}


#endif // __TEST_INTERVAL_QUANTIFIER_SHARED_H_JOFA_090119__

