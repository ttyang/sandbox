/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_INTERVAL_SET_ALGO_HPP_JOFA_081005
#define BOOST_ITL_INTERVAL_SET_ALGO_HPP_JOFA_081005

#include <boost/itl/detail/notate.hpp>
#include <boost/itl/detail/relation_state.hpp>
#include <boost/itl/type_traits/neutron.hpp>
#include <boost/itl/type_traits/is_map.hpp>
#include <boost/itl/type_traits/is_total.hpp>
#include <boost/itl/type_traits/is_combinable.hpp>
#include <boost/itl/interval.hpp>
#include <boost/itl/detail/element_comparer.hpp>
#include <boost/itl/detail/interval_subset_comparer.hpp>

namespace boost{namespace itl
{

template <class IntervalContainerT>
typename IntervalContainerT::size_type continuous_cardinality(const IntervalContainerT& object)
{
    typedef typename IntervalContainerT::size_type size_type;
    typedef typename IntervalContainerT::interval_type interval_type;

    size_type size = neutron<size_type>::value();
    size_type interval_size;
    ITL_const_FORALL(typename IntervalContainerT, it, object)
    {
        //CL interval_size = continuous_interval_<interval_type>::cardinality(IntervalContainerT::key_value(it));
        interval_size = itl::cardinality(IntervalContainerT::key_value(it));
        if(interval_size == infinity<size_type>::value())
            return interval_size;
        else
            size += interval_size;
    }
    return size;
}

template <class IntervalContainerT>
typename IntervalContainerT::size_type discrete_cardinality(const IntervalContainerT& object)
{
    typedef typename IntervalContainerT::size_type size_type;
    typedef typename IntervalContainerT::interval_type interval_type;

    size_type size = neutron<size_type>::value();
    ITL_const_FORALL(typename IntervalContainerT, it, object)
        size += discrete_interval_<interval_type>::cardinality(IntervalContainerT::key_value(it));
    return size;
}

struct continuous_interval_container
{
    template<class IntervalContainerT> 
    static typename IntervalContainerT::size_type 
        cardinality(const IntervalContainerT& cont) 
    { return continuous_cardinality(cont); }
};

struct discrete_interval_container
{
    template<class IntervalContainerT> 
    static typename IntervalContainerT::size_type 
        cardinality(const IntervalContainerT& cont) 
    { return discrete_cardinality(cont); }
};


namespace Interval_Set
{

//------------------------------------------------------------------------------
// Lexicographical comparison on ranges of two interval container 
//------------------------------------------------------------------------------

template<class LeftT, class RightT>
bool is_element_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}

template<class LeftT, class RightT>
bool is_element_less(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::less;
}

template<class LeftT, class RightT>
bool is_element_greater(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::greater;
}

//------------------------------------------------------------------------------
// Subset/superset compare on ranges of two interval container 
//------------------------------------------------------------------------------

template<class LeftT, class RightT>
bool is_inclusion_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>, 
                             is_total<RightT> >,
                   bool>::type
within(const LeftT&, const RightT&)
{
    cout << "within\n";
    return true;
}

template<class LeftT, class RightT>
typename enable_if<mpl::not_<mpl::and_<is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>, 
                                       is_total<RightT> > >,
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>, 
                             is_total<LeftT> >,
                   bool>::type
contains(const LeftT&, const RightT&)
{
    cout << "contains\n";
    return true;
}

template<class LeftT, class RightT>
typename enable_if<mpl::not_<mpl::and_<is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>, 
                                       is_total<LeftT> > >,
                   bool>::type
contains(const LeftT& super, const RightT& sub)
{
    int result =
        subset_compare
        (
            super, sub, 
            super.begin(), super.end(), 
            sub.begin(), sub.end()
        );
    return result == inclusion::superset || result == inclusion::equal;
}

template<class IntervalContainerT>
bool contains(const IntervalContainerT& super, 
              const typename IntervalContainerT::element_type& element)
{
    return super.contains(element);
}

template<class IntervalContainerT>
bool contains(const IntervalContainerT& container, 
              const typename IntervalContainerT::segment_type& sub_interval)
{
    typedef typename IntervalContainerT::const_iterator const_iterator;
    if(itl::is_empty(sub_interval)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior = container.equal_range(sub_interval);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = prior(exterior.second);

    return
          itl::contains(hull(*(exterior.first), *last_overlap), sub_interval)
      &&  Interval_Set::is_joinable(container, exterior.first, last_overlap);
}

template<class IntervalContainerT>
bool is_joinable(const IntervalContainerT& container, 
                 typename IntervalContainerT::const_iterator first, 
                 typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!itl::touches(IntervalContainerT::key_value(it_++),
                         IntervalContainerT::key_value(next_++)))
            return false;

    return true;
}


template<class IntervalContainerT>
bool is_dense(const IntervalContainerT& container, 
              typename IntervalContainerT::const_iterator first, 
              typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!itl::touches(IntervalContainerT::key_value(it_++), 
                         IntervalContainerT::key_value(next_++)))
            return false;

    return true;
}

} // namespace Interval_Set
    
}} // namespace itl boost

#endif 

