/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_DISCRETE_INTERVAL_HPP_JOFA_100403
#define BOOST_ITL_DISCRETE_INTERVAL_HPP_JOFA_100403

#include <functional> 
#include <boost/static_assert.hpp> 
#include <boost/concept/assert.hpp>
#include <boost/itl/type_traits/succ_pred.hpp>
#include <boost/itl/type_traits/value_size.hpp>
#include <boost/itl/type_traits/type_to_string.hpp>
#include <boost/itl/type_traits/is_continuous.hpp>
#include <boost/itl/type_traits/is_discrete_interval.hpp>
#include <boost/itl/interval_bounds.hpp>
#include <boost/itl/concept/interval.hpp>

namespace boost{namespace itl
{

template <class DomainT, 
          ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, DomainT)>
class discrete_interval
{
public:
    typedef discrete_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef typename bounded_value<DomainT>::type bounded_domain_type;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    discrete_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((itl::is_discrete<DomainT>::value));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit discrete_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((itl::is_discrete<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    discrete_interval(const DomainT& low, const DomainT& up, 
                      interval_bounds bounds = interval_bounds::right_open(),
                      discrete_interval* = 0)
        : _lwb(low), _upb(up), _bounds(bounds)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((itl::is_discrete<DomainT>::value));
    }

    domain_type     lower()const { return _lwb; }
    domain_type     upper()const { return _upb; }
    interval_bounds bounds()const{ return _bounds; }

    static discrete_interval open     (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::open());      }
    static discrete_interval right_open(const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::right_open());}
    static discrete_interval left_open (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::left_open()); }
    static discrete_interval closed   (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::closed());    }

private:
    domain_type     _lwb;
    domain_type     _upb;
    interval_bounds _bounds;
};

//==============================================================================
//=T discrete_interval -> concept intervals
//==============================================================================
template<class DomainT, ITL_COMPARE Compare>
struct interval_traits< itl::discrete_interval<DomainT, Compare> >
{
    typedef interval_traits type;
    typedef DomainT domain_type;
    typedef ITL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef itl::discrete_interval<DomainT, Compare> interval_type;

    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }

    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };
    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };
};

//==============================================================================
//=T discrete_interval -> concept dynamic_interval_traits
//==============================================================================
template<class DomainT, ITL_COMPARE Compare>
struct dynamic_interval_traits<boost::itl::discrete_interval<DomainT,Compare> >
{
    typedef dynamic_interval_traits type;
    typedef boost::itl::discrete_interval<DomainT,Compare> interval_type;
    typedef DomainT domain_type;
    typedef ITL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

    static interval_type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds)
    {
        return interval_type(lo, up, bounds, static_cast<interval_type*>(0) );
    }

    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  interval_type
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<interval_type* >(0) 
                );
    }
};

//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ITL_COMPARE Compare> 
struct interval_bound_type< discrete_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(unsigned char, value = interval_bounds::dynamic);
};

template <class DomainT, ITL_COMPARE Compare> 
struct is_discrete_interval<discrete_interval<DomainT,Compare> >
{
    typedef is_discrete_interval<discrete_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = is_discrete<DomainT>::value);
};

template <class DomainT, ITL_COMPARE Compare>
struct type_to_string<itl::discrete_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "dI<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT> 
struct value_size<itl::discrete_interval<DomainT> >
{
    static std::size_t apply(const itl::discrete_interval<DomainT>& value) 
    { return 2; }
};

}} // namespace itl boost

#endif

