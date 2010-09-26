/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_CONCEPT_INTERVAL_HPP_JOFA_100323
#define BOOST_ITL_CONCEPT_INTERVAL_HPP_JOFA_100323

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/itl/detail/design_config.hpp>
#include <boost/itl/type_traits/is_discrete.hpp>
#include <boost/itl/type_traits/is_asymmetric_interval.hpp>
#include <boost/itl/type_traits/is_universal_interval.hpp>
#include <boost/itl/type_traits/is_discrete_interval.hpp>
#include <boost/itl/type_traits/is_continuous_interval.hpp>
#include <boost/itl/type_traits/has_dynamic_bounds.hpp>
#include <boost/itl/concept/domain_comparable.hpp>


namespace boost{namespace itl
{

typedef unsigned char bound_type; //JODO encapsulation in a small class

//==============================================================================
//= Construct
//==============================================================================

class interval_bounds; //JODO separate dynamically and statically bounded interval concepts
template<class DomainT> class bounded_value;

//------------------------------------------------------------------------------
//- Adapter classes
//------------------------------------------------------------------------------
template<class Type>
struct intervals
{
    typedef typename Type::domain_type    domain_type;
    typedef typename Type::domain_compare domain_compare;

    static Type construct(const domain_type& lo, const domain_type& up);

    static domain_type upper(const Type& inter_val);
    static domain_type lower(const Type& inter_val);
};


template<class Type>
struct dynamic_intervals
{
    typedef typename Type::domain_type    domain_type;
    typedef typename Type::domain_compare domain_compare;

    static Type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds);
    static Type construct_bounded(const bounded_value<domain_type>& lo, 
                                       const bounded_value<domain_type>& up);
};




//==============================================================================
//= Construct
//==============================================================================

template<class Type>
typename enable_if<is_asymmetric_interval<Type>, Type>::type
construct(const typename Type::domain_type& low, //JODO Parameter passing DomainP
          const typename Type::domain_type& up,
          interval_bounds bounds = interval_bounds::right_open()) //JODO separate static intervals to avoid dependency
{
    return intervals<Type>::construct(low, up);
}


template<class Type>
typename enable_if<is_dynamic_bounded<Type>, Type>::type
construct(const typename Type::domain_type& low,
          const typename Type::domain_type& up,
          interval_bounds bounds = interval_bounds::right_open())
{
    return dynamic_intervals<Type>::construct(low, up, bounds);
}


//- construct form bounded values ----------------------------------------------
template<class Type>
typename enable_if<is_dynamic_bounded<Type>, Type>::type
construct(const typename Type::bounded_domain_type& low,
          const typename Type::bounded_domain_type& up)
{
    return dynamic_intervals<Type>::construct_bounded(low, up);
}

template<class Type>
typename enable_if<is_interval<Type>, Type>::type
span(const typename Type::domain_type& lhs,
     const typename Type::domain_type& rhs)
{
    if(Type::domain_compare(lhs,rhs))
        return construct(lhs, rhs);
    else
        return construct(rhs, lhs);
}


//==============================================================================
//= Selection
//==============================================================================

template<class Type>
inline typename enable_if<is_interval<Type>, 
                          typename Type::domain_type>::type
lower(const Type& object)
{ 
    return intervals<Type>::lower(object);
}

template<class Type>
inline typename enable_if<is_interval<Type>, 
                          typename Type::domain_type>::type
upper(const Type& object)
{ 
    return intervals<Type>::upper(object);
}


//- first ----------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_static_rightopen<Type>, 
                          typename Type::domain_type>::type
first(const Type& object)
{ 
    return lower(object);
}

template<class Type>
inline typename enable_if<is_discrete_interval<Type>, 
                          typename Type::domain_type>::type
first(const Type& object)
{ 
    return is_left_closed(object.bounds()) ? 
                    lower(object) : 
               succ(lower(object));
}

//- last -----------------------------------------------------------------------
template<class Type>
inline typename enable_if<mpl::and_<is_static_rightopen<Type>,
                                    is_discrete<typename Type::domain_type> >,
                          typename Type::domain_type>::type
last(const Type& object)
{ 
    return pred(upper(object));
}

template<class Type>
inline typename enable_if<is_discrete_interval<Type>, 
                          typename Type::domain_type>::type
last(const Type& object)
{ 
    return is_right_closed(object.bounds()) ? 
                    upper(object) : 
               pred(upper(object));
}


//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_dynamic_bounded<Type>, 
                   typename Type::bounded_domain_type>::type
bounded_lower(const Type& object)
{ 
    return typename 
        Type::bounded_domain_type(lower(object), 
                                       object.bounds().left()); 
}

template<class Type>
typename enable_if<is_dynamic_bounded<Type>, 
                   typename Type::bounded_domain_type>::type
reverse_bounded_lower(const Type& object)
{ 
    return typename 
        Type::bounded_domain_type(lower(object), 
                                       object.bounds().reverse_left()); 
}

template<class Type>
typename enable_if<is_dynamic_bounded<Type>, 
                   typename Type::bounded_domain_type>::type
bounded_upper(const Type& object)
{ 
    return typename 
        Type::bounded_domain_type(upper(object), 
                                       object.bounds().right()); 
}

template<class Type>
typename enable_if<is_dynamic_bounded<Type>, 
                   typename Type::bounded_domain_type>::type
reverse_bounded_upper(const Type& object)
{ 
    return typename 
        Type::bounded_domain_type(upper(object), 
                                       object.bounds().reverse_right()); 
}


//==============================================================================
//= Containedness
//==============================================================================
//- is_empty -------------------------------------------------------------------
/** Is the interval empty? */
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
is_empty(const Type& object)
{ 
    return domain_less_equal<Type>(upper(object), lower(object)); 
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
is_empty(const Type& object)
{ 
    return object.empty(); 
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
is_empty(const Type& object)
{ 
    if(object.bounds() == interval_bounds::closed())
        return domain_less<Type>(upper(object), lower(object)); 
    else if(object.bounds() == interval_bounds::open())
        return domain_less_equal<Type>(upper(object), succ(lower(object))); 
    else
        return domain_less_equal<Type>(upper(object), lower(object)); 
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
is_empty(const Type& object)
{
    return     domain_less<Type>(upper(object), lower(object))
        || (   domain_equal<Type>(upper(object), lower(object))
            && object.bounds() != interval_bounds::closed()    );
}

//- contains -------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
contains(const Type& super, const Type& sub)
{ 
    return lower_less_equal(super,sub) && upper_less_equal(sub,super);
}

template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
contains(const Type& super, const typename Type::domain_type& element)
{ 
    return contains(super,Type(element));
}

//- within ---------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
within(const Type& sub, const Type& super)
{ 
    return contains(super,sub);
}


//==============================================================================
//= Equivalences and Orderings
//==============================================================================
//- exclusive_less -------------------------------------------------------------
/** Maximal element of <tt>left</tt> is less than the minimal element of 
    <tt>right</tt> */
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{ 
    return domain_less_equal<Type>(left.upper(), right.lower()); 
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{ 
    return left.exclusive_less(right); 
}


template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{ 
    return domain_less<Type>(last(left), first(right)); 
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{ 
    return     domain_less<Type>(left.upper(), right.lower())
        || (   domain_equal<Type>(left.upper(), right.lower())
            && inner_bounds(left,right) != interval_bounds::open() );
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    return domain_less<Type>(left.lower(), right.lower());
}
    
template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    return left.lower_less(right);
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    return domain_less<Type>(first(left), first(right));
}
    
template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    if(left_bounds(left,right) == interval_bounds::right_open())  //'[(' == 10
        return domain_less_equal<Type>(left.lower(), right.lower());
    else 
        return domain_less<Type>(left.lower(), right.lower());
}
    

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    return domain_less<Type>(left.upper(), right.upper());
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    return left.upper_less(right);
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    return domain_less<Type>(last(left), last(right));
}
    
template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    if(right_bounds(left,right) == interval_bounds::left_open())
        return domain_less_equal<Type>(left.upper(), right.upper());
    else
        return domain_less<Type>(left.upper(), right.upper());
}
    
//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, 
                          typename Type::bounded_domain_type   >::type
lower_min(const Type& left, const Type& right)
{
    return lower_less(left, right) ? bounded_lower(left) : bounded_lower(right);
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, 
                          typename Type::bounded_domain_type   >::type
lower_max(const Type& left, const Type& right)
{
    return lower_less(left, right) ? bounded_lower(right) : bounded_lower(left);
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, 
                          typename Type::bounded_domain_type   >::type
upper_max(const Type& left, const Type& right)
{
    return upper_less(left, right) ? bounded_upper(right) : bounded_upper(left);
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, 
                          typename Type::bounded_domain_type   >::type
upper_min(const Type& left, const Type& right)
{
    return upper_less(left, right) ? bounded_upper(left) : bounded_upper(right);
}


//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(left.lower(), right.lower());
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return left.lower_equal(right);
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(first(left), first(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return (left.bounds().left()==right.bounds().left())
        && domain_equal<Type>(left.lower(), right.lower());
}


//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(left.upper(), right.upper());
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return left.upper_equal(right);
}
    
template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(last(left), last(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return (left.bounds().right()==right.bounds().right())
        && domain_equal<Type>(left.upper(), right.upper());
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
lower_less_equal(const Type& left, const Type& right)
{
    return lower_less(left,right) || lower_equal(left,right);
}

template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
upper_less_equal(const Type& left, const Type& right)
{
    return upper_less(left,right) || upper_equal(left,right);
}


//- operator == ----------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
operator == (const Type& lhs, const Type& rhs)
{
    return (itl::is_empty(lhs) && itl::is_empty(rhs)) 
        || (lower_equal(lhs,rhs) && upper_equal(lhs,rhs));
}

//- operator < -----------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
operator < (const Type& lhs, const Type& rhs)
{
    if(itl::is_empty(lhs)) 
        return !itl::is_empty(rhs);
    else 
        return lower_less(lhs,rhs) 
            || (lower_equal(lhs,rhs) && upper_less(lhs,rhs)); 
}



//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{ 
    return domain_equal<Type>(left.upper(), right.lower()); 
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{ 
    return left.touches(right); 
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{
    return domain_equal<Type>(succ(last(left)), first(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{
    return is_complementary(inner_bounds(left,right))
        && domain_equal<Type>(left.upper(), right.lower());
}


//==============================================================================
//= Size
//==============================================================================
//- cardinality ----------------------------------------------------------------

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, 
    typename Type::size_type>::type
cardinality(const Type& object)
{
    typedef typename Type::size_type SizeT;
    if(itl::is_empty(object))
        return itl::neutron<SizeT>::value();
    else if(   object.bounds() == interval_bounds::closed() 
            && domain_equal<Type>(lower(object), upper(object)))
        return itl::unon<SizeT>::value();
    else 
        return infinity<SizeT>::value();
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, 
    typename Type::size_type>::type
cardinality(const Type& object)
{
    return (last(object) + itl::unon<typename Type::size_type>::value()) - first(object);
}


template<class Type>
typename boost::enable_if<is_continuous_asymmetric<Type>, 
    typename Type::size_type>::type
cardinality(const Type& object)
{
    typedef typename Type::size_type SizeT;
    if(itl::is_empty(object))
        return itl::neutron<SizeT>::value();
    else 
        return infinity<SizeT>::value();
}

template<class Type>
typename boost::enable_if<is_discrete_asymmetric<Type>, 
    typename Type::size_type>::type
cardinality(const Type& object)
{
    return (last(object) + itl::unon<typename Type::size_type>::value()) - first(object);
}





//- size -----------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval<Type>, 
                          typename Type::size_type>::type
size(const Type& object)
{
    return cardinality(object);
}

//- length ---------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, 
    typename Type::difference_type>::type
length(const Type& object)
{
    return upper(object) - lower(object);
}

template<class Type>
inline typename boost::enable_if<is_discrete_interval<Type>, 
    typename Type::difference_type>::type
length(const Type& object)
{
    return    (last(object) + itl::unon<typename Type::difference_type>::value()) 
            -  first(object);
}

template<class Type>
typename boost::enable_if<is_continuous_asymmetric<Type>, 
    typename Type::difference_type>::type
length(const Type& object)
{
    return upper(object) - lower(object);
}

template<class Type>
inline typename boost::enable_if<is_discrete_asymmetric<Type>, 
    typename Type::difference_type>::type
length(const Type& object)
{
    return    (last(object) + itl::unon<typename Type::difference_type>::value()) 
            -  first(object);
}

//==============================================================================
//= Addition
//==============================================================================
//- hull -----------------------------------------------------------------------
/** \c hull returns the smallest interval containing \c left and \c right. */
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
hull(Type left, const Type& right)
{
    if(itl::is_empty(right))
        return left;
    else if(itl::is_empty(left))
        return right;

    //JODO return construct
    return 
        Type
        (
            (std::min)(left.lower(), right.lower(), Type::domain_compare()), 
            (std::max)(left.upper(), right.upper(), Type::domain_compare())
        );
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, Type>::type
hull(Type left, const Type& right)
{
    return left.extend(right);
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
hull(Type left, const Type& right)
{
    if(itl::is_empty(right))
        return left;
    else if(itl::is_empty(left))
        return right;

    //JODO return  construct<Type,std::less>
    return  dynamic_intervals<Type>::construct_bounded
            (
                lower_min(left, right), 
                upper_max(left, right)
            );
}

//==============================================================================
//= Subtraction
//==============================================================================
//- left_subtract --------------------------------------------------------------
/** subtract \c left_minuend from the \c right interval on it's left side. 
    Return the difference: The part of \c right right of \c left_minuend.
\code
right_over = right - left_minuend; //on the left.
...      d) : right
... c)      : left_minuend
     [c  d) : right_over
\endcode
*/
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    if(exclusive_less(left_minuend, right))
        return right; 
    //JODO return construct(left_minuend.upper(), right.upper());
    return Type(left_minuend.upper(), right.upper());
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    return right.left_subtract(left_minuend);
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    if(exclusive_less(left_minuend, right))
        return right; 
    return  dynamic_intervals<Type>::construct_bounded
            ( reverse_bounded_upper(left_minuend), bounded_upper(right) );
}


//- right_subtract -------------------------------------------------------------
/** subtract \c right_minuend from the \c left interval on it's right side. 
    Return the difference: The part of \c left right of \c right_minuend.
\code
left_over = left - right_minuend; //on the right side.
[a      ...  : left
     [b ...  : right_minuend
[a  b)       : left_over
\endcode
*/
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    if(exclusive_less(left, right_minuend))
        return left; 
    return Type(left.lower(), right_minuend.lower());
    //JODO return construct(left.lower(), right_minuend.lower());
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    return left.right_subtract(right_minuend);
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    //JODO s.o.
    if(exclusive_less(left, right_minuend))
        return left; 
    //JODO return construct<Type,std::less>(left.lower(), right_minuend.lower(),
    return  dynamic_intervals<Type>::construct_bounded
            ( bounded_lower(left), reverse_bounded_lower(right_minuend) );
}

//==============================================================================
//= Intersection
//==============================================================================
//- operator & -----------------------------------------------------------------
/** Returns the intersection of \c left and \c right interval. */
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
operator & (Type left, const Type& right)
{
    if(itl::is_empty(left) || itl::is_empty(right))
        return Type(); //JODO return neutron<Type>::value; neutron for new interval_types.
    else
        return
        Type((std::max)(left.lower(), right.lower(), Type::domain_compare()),
                  (std::min)(left.upper(), right.upper(), Type::domain_compare()));
}

template<class Type>
typename boost::enable_if<is_universal_interval<Type>, Type>::type
operator & (Type left, const Type& right)
{
    return left &= right;
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
operator & (Type left, const Type& right)
{
    if(itl::is_empty(left) || itl::is_empty(right))
        return Type(); //JODO return neutron<Type>::value; neutron for new interval_types.
    else 
        //JODO return  construct<Type,std::less>
        return  dynamic_intervals<Type>::construct_bounded
                (
                    lower_max(left, right), 
                    upper_min(left, right) 
                );
}


//- intersects -----------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
intersects(const Type& left, const Type& right)
{ 
    return !(exclusive_less(left,right) || exclusive_less(right,left)); 
}

//- disjoint -------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
disjoint(const Type& left, const Type& right)
{ 
    return exclusive_less(left,right) || exclusive_less(right,left); 
}

//------------------------------------------------------------------------------



}} // namespace itl boost

#endif

