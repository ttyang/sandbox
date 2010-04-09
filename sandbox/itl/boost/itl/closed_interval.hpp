/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_CLOSED_INTERVAL_HPP_JOFA_100324
#define BOOST_ITL_CLOSED_INTERVAL_HPP_JOFA_100324

#include <boost/itl/type_traits/value_size.hpp>
#include <boost/itl/type_traits/type_to_string.hpp>
#include <boost/itl/detail/base_interval.hpp>
#include <boost/itl/interval_functions.hpp>

namespace boost{namespace itl
{

template <class DomainT, 
          ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, DomainT)>
class closed_interval : public base_interval<DomainT,Compare> 
{
public:
    typedef closed_interval<DomainT,Compare> type;
    typedef DomainT domain_type;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    closed_interval() 
        : _lwb(unon<DomainT>::value()), _upb(neutron<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((!itl::is_continuous<DomainT>::value));//JODO is_discrete?
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit closed_interval(const DomainT& val)
        : _lwb(val), _upb(val)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((!itl::is_continuous<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    closed_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    domain_type lower()const{ return _lwb; }
    domain_type upper()const{ return _upb; }

    domain_type first()const{ return _lwb; }
    domain_type last() const{ return _upb; }

private:
    domain_type _lwb;
    domain_type _upb;
};


template<class CharType, class CharTraits, class DomainT, ITL_COMPARE Compare>
std::basic_ostream<CharType, CharTraits>& operator <<
  (std::basic_ostream<CharType, CharTraits> &stream, 
   closed_interval<DomainT,Compare> const& object)
{
    if(itl::is_empty(object))
        return stream << "[]";
    else
        return stream << "[" << object.lower() << "," << object.upper()<< "]";
}


//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ITL_COMPARE Compare> 
struct is_interval<closed_interval<DomainT,Compare> >
{
    typedef is_interval<closed_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT, ITL_COMPARE Compare> 
struct has_static_bounds<closed_interval<DomainT,Compare> >
{
    typedef has_static_bounds<closed_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT, ITL_COMPARE Compare>
struct type_to_string<itl::closed_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "[I]<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT> 
struct value_size<itl::closed_interval<DomainT> >
{
    static std::size_t apply(const itl::closed_interval<DomainT>& value) 
    { return 2; }
};

}} // namespace itl boost

#endif

