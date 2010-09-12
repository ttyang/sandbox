/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef __interval_base_map_h_JOFA_990223__
#define __interval_base_map_h_JOFA_990223__

#include <limits>
#include <boost/type_traits/ice.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>

#include <boost/itl/detail/notate.hpp>
#include <boost/itl/detail/design_config.hpp>
#include <boost/itl/type_traits/is_interval_splitter.hpp>
#include <boost/itl/map.hpp>
#include <boost/itl/interval_base_set.hpp>
#include <boost/itl/detail/interval_map_algo.hpp>


#define const_FOR_IMPLMAP(iter) for(typename ImplMapT::const_iterator iter=_map.begin(); (iter)!=_map.end(); (iter)++)
#define FOR_IMPLMAP(iter) for(typename ImplMapT::iterator iter=_map.begin(); (iter)!=_map.end(); (iter)++)

namespace boost{namespace itl
{

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif                        


template<class DomainT, class CodomainT>
struct mapping_pair
{
    DomainT   key;
    CodomainT data;

    mapping_pair():key(), data(){}

    mapping_pair(const DomainT& key_value, const CodomainT& data_value)
        :key(key_value), data(data_value){}

    mapping_pair(const std::pair<DomainT,CodomainT>& std_pair)
        :key(std_pair.first), data(std_pair.second){}
};

template<class Type>
inline typename enable_if<is_interval_map<Type>, typename Type::segment_type>::type
make_segment(const typename Type::element_type& element)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::segment_type  segment_type;
    return segment_type(interval_type(element.key), element.data);
}

/** \brief Implements a map as a map of intervals (base class) */
template
<
    class SubType,
    typename DomainT,
    typename CodomainT,
    class Traits = itl::partial_absorber,
    ITL_COMPARE Compare  = ITL_COMPARE_INSTANCE(std::less, DomainT),
    ITL_COMBINE Combine  = ITL_COMBINE_INSTANCE(itl::inplace_plus, CodomainT),
    ITL_SECTION Section  = ITL_SECTION_INSTANCE(itl::inter_section, CodomainT), 
    ITL_INTERVAL(ITL_COMPARE) Interval = ITL_INTERVAL_INSTANCE(ITL_INTERVAL_DEFAULT, DomainT, Compare),
    ITL_ALLOC   Alloc    = std::allocator
>
class interval_base_map
{
public:
    //==========================================================================
    //= Associated types
    //==========================================================================
    typedef interval_base_map<SubType,DomainT,CodomainT,
                              Traits,Compare,Combine,Section,Interval,Alloc>
                              type;

    /// The designated \e derived or \e sub_type of this base class
    typedef SubType sub_type;

    /// Auxilliary type for overloadresolution
    typedef type overloadable_type;

    /// Traits of an itl map
    typedef Traits traits;

    //--------------------------------------------------------------------------
    //- Associated types: Related types
    //--------------------------------------------------------------------------
    /// The atomized type representing the corresponding container of elements
    typedef typename itl::map<DomainT,CodomainT,
                              Traits,Compare,Combine,Section,Alloc> atomized_type;

    //--------------------------------------------------------------------------
    //- Associated types: Data
    //--------------------------------------------------------------------------
    /// Domain type (type of the keys) of the map
    typedef DomainT   domain_type;
    /// Domain type (type of the keys) of the map
    typedef CodomainT codomain_type;
    /// Auxiliary type to help the compiler resolve ambiguities when using std::make_pair
    typedef mapping_pair<domain_type,codomain_type> domain_mapping_type;
    /// Conceptual is a map a set of elements of type \c element_type
    typedef domain_mapping_type element_type;
    /// The interval type of the map
    typedef ITL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    /// Auxiliary type for overload resolution
    typedef std::pair<interval_type,CodomainT> interval_mapping_type;
    /// Type of an interval containers segment, that is spanned by an interval
    typedef std::pair<interval_type,CodomainT> segment_type;

    //--------------------------------------------------------------------------
    //- Associated types: Size
    //--------------------------------------------------------------------------
    /// The difference type of an interval which is sometimes different form the domain_type
    typedef typename interval_type::difference_type difference_type;
    /// The size type of an interval which is mostly std::size_t
    typedef typename interval_type::size_type size_type;

    //--------------------------------------------------------------------------
    //- Associated types: Functors
    //--------------------------------------------------------------------------
    /// Comparison functor for domain values
    typedef ITL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    /// Combine functor for codomain value aggregation
    typedef ITL_COMBINE_CODOMAIN(Combine,CodomainT) codomain_combine;
    /// Inverse Combine functor for codomain value aggregation
    typedef typename inverse<codomain_combine>::type inverse_codomain_combine;
    /// Intersection functor for codomain values
    //CL typedef ITL_SECTION_CODOMAIN(Section,CodomainT) codomain_intersect;

    typedef typename mpl::if_
    <has_set_semantics<codomain_type>
    , ITL_SECTION_CODOMAIN(Section,CodomainT)     
    , codomain_combine
    >::type                                            codomain_intersect; //JODO extra metafuction?
    //JODO What, if codomain is not a set but the user want's to use a special intersection functor?


    /// Inverse Combine functor for codomain value intersection
    typedef typename inverse<codomain_intersect>::type inverse_codomain_intersect;

    /// Comparison functor for intervals which are keys as well
    typedef exclusive_less_than<interval_type> interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less_than<interval_type> key_compare;

    //--------------------------------------------------------------------------
    //- Associated types: Implementation and stl related
    //--------------------------------------------------------------------------
    /// The allocator type of the set
    typedef Alloc<std::pair<const interval_type, codomain_type> > 
        allocator_type;

    /// Container type for the implementation 
    typedef ITL_IMPL_SPACE::map<interval_type,codomain_type,
                                key_compare,allocator_type> ImplMapT;

    /// key type of the implementing container
    typedef typename ImplMapT::key_type   key_type;
    /// value type of the implementing container
    typedef typename ImplMapT::value_type value_type;
    /// data type of the implementing container
    typedef typename ImplMapT::value_type::second_type data_type;

    /// pointer type
    typedef typename ImplMapT::pointer         pointer;
    /// const pointer type
    typedef typename ImplMapT::const_pointer   const_pointer;
    /// reference type
    typedef typename ImplMapT::reference       reference;
    /// const reference type
    typedef typename ImplMapT::const_reference const_reference;

    /// iterator for iteration over intervals
    typedef typename ImplMapT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplMapT::const_iterator const_iterator;
    /// iterator for reverse iteration over intervals
    typedef typename ImplMapT::reverse_iterator reverse_iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplMapT::const_reverse_iterator const_reverse_iterator;

    /// element iterator: Depreciated, see documentation.
    typedef boost::itl::element_iterator<iterator> element_iterator; 
    /// const element iterator: Depreciated, see documentation.
    typedef boost::itl::element_iterator<const_iterator> element_const_iterator; 
    /// element reverse iterator: Depreciated, see documentation.
    typedef boost::itl::element_iterator<reverse_iterator> element_reverse_iterator; 
    /// element const reverse iterator: Depreciated, see documentation.
    typedef boost::itl::element_iterator<const_reverse_iterator> element_const_reverse_iterator; 
    
public:
    enum { is_itl_container = true };
    enum { fineness = 0 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor for the empty object */
    interval_base_map()
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    /** Copy constructor */
    interval_base_map(const interval_base_map& src): _map(src._map)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    /** Assignment operator */
    interval_base_map& operator = (const interval_base_map& src) 
    { 
        this->_map = src._map;
        return *this; 
    }

    /** swap the content of containers */
    void swap(interval_base_map& object) { _map.swap(object._map); }

    //==========================================================================
    //= Containedness
    //==========================================================================
    /** clear the map */
    void clear() { itl::clear(*that()); }

    /** is the map empty? */
    bool empty()const { return itl::is_empty(*that()); }

    
    /** Does the map contain some object \c sub of type \c CoType */
    template<class CoType>
    bool contains(const CoType& sub)const
    {
        return itl::contains(*that(), sub);
    }

    /** Is <tt>*this</tt> container within <tt>super</tt>? */
    template<class CoType>
    bool within(const CoType& super)const
    {
        return itl::within(*that(), super);
    }

    //==========================================================================
    //= Size
    //==========================================================================

    /** Number of elements in the map (cardinality). */
    size_type cardinality()const
    {
        return itl::cardinality(*that());
    }

    /** An interval map's size is it's cardinality */
    size_type size()const
    {
        return itl::cardinality(*that());
    }

    /** The length of the interval container which is the sum of interval lengths */
    difference_type length()const
    {
        return itl::length(*that());
    }

    /** Number of intervals which is also the size of the 
        iteration over the object */
    size_t interval_count()const 
    { 
        return itl::interval_count(*that()); 
    }

    /** Size of the iteration over this container */
    size_t iterative_size()const 
    { 
        return _map.size(); 
    }

    //==========================================================================
    //= Range
    //==========================================================================

    //JODO remove lower, upper, first, last from the interface of all interval containers and docs

    //==========================================================================
    //= Selection
    //==========================================================================

    /** Find the interval value pair, that contains \c key */
    const_iterator find(const domain_type& key)const
    { 
        return _map.find(interval_type(key)); 
    }

    const_iterator find(const key_type& key)const
    { 
        return _map.find(key); 
    }

    /** Total select function. */
    codomain_type operator()(const domain_type& key)const
    {
        const_iterator it_ = _map.find(interval_type(key)); 
        return it_==end() ? neutron<codomain_type>::value()
                          : it_->second;
    }


    //==========================================================================
    //= Addition
    //==========================================================================

    /** Addition of a key value pair to the map */
    SubType& add(const element_type& key_value_pair) 
    {
        return itl::add(*that(), key_value_pair);
    }

    /** Addition of an interval value pair to the map. */
    SubType& add(const segment_type& interval_value_pair) 
    {
        return itl::add(*that(), interval_value_pair);
    }

    /** Addition of an interval value pair \c interval_value_pair to the map. 
        Iterator \c prior_ is a hint to the position \c interval_value_pair can be 
        inserted after. */
    iterator add(iterator prior_, const segment_type& interval_value_pair) 
    {
        return itl::add(*that(), prior_, interval_value_pair);
    }

    //==========================================================================
    //= Subtraction
    //==========================================================================

    /** Subtraction of a key value pair from the map */
    SubType& subtract(const element_type& key_value_pair)
    { 
        return itl::subtract(*that(), key_value_pair);
    }

    /** Subtraction of an interval value pair from the map. */
    SubType& subtract(const segment_type& interval_value_pair)
    {
        return itl::subtract(*that(), interval_value_pair);
    }

    //==========================================================================
    //= Insertion
    //==========================================================================

    std::pair<iterator,bool> _insert(const value_type& value_pair){ return _map.insert(value_pair); }
    iterator _insert(iterator prior, const value_type& value_pair){ return _map.insert(prior, value_pair); }

    /** Insertion of a \c key_value_pair into the map. */
    SubType& insert(const element_type& key_value_pair) 
    {
        return itl::insert(*that(), key_value_pair);
    }

    /** Insertion of an \c interval_value_pair into the map. */
    SubType& insert(const segment_type& interval_value_pair)
    { 
        return itl::insert(*that(), interval_value_pair);
    }

    /** Insertion of an \c interval_value_pair into the map. Iterator \c prior_. 
        serves as a hint to insert after the element \c prior point to. */
    iterator insert(iterator prior, const segment_type& interval_value_pair)
    { 
        return itl::insert(*that(), prior, interval_value_pair);
    }

    /** With <tt>key_value_pair = (k,v)</tt> set value \c v for key \c k */
    SubType& set(const element_type& key_value_pair) 
    { 
        return itl::set_at(*that(), key_value_pair);
    }

    /** With <tt>interval_value_pair = (I,v)</tt> set value \c v 
        for all keys in interval \c I in the map. */
    SubType& set(const segment_type& interval_value_pair)
    { 
        return itl::set_at(*that(), interval_value_pair);
    }


    //==========================================================================
    //= Erasure
    //==========================================================================

    template<class CoType>
    SubType& erase(const CoType& operand) 
    {
        return itl::erase(*that(), operand);
    }

    /** Erase all value pairs within the range of the interval that iterator 
        \c position points to. */
    void erase(iterator position){ _map.erase(position); }

    /** Erase all value pairs for a range of iterators <tt>[first,past)</tt>. */
    void erase(iterator first, iterator past){ _map.erase(first, past); }

    //==========================================================================
    //= Intersection
    //==========================================================================
    /** Returns \c true, if element \c key is found in \c *this map.
        Complexity: logarithmic. */
    bool intersects(const domain_type& key)const
    {
        return itl::intersects(*that(), key);
    }

    /** Returns \c true, if \c inter_val intersects with \c *this map.
        Complexity: Logarithmic in iterative size. */
    bool intersects(const interval_type& inter_val)const
    { 
        return itl::intersects(*that(), inter_val);
    }

    /** Returns \c true, if \c key_value_pair is found in \c *this map.
        Complexity: logarithmic. */
    bool intersects(const element_type& key_value_pair)const
    { 
        return itl::intersects(*that(), key_value_pair);
    }

    /** Returns \c true, if \c interval_value_pair intersects with \c *this map:
        Complexity: Linear in iterative_size. */
    bool intersects(const segment_type& interval_value_pair)const
    {
        return itl::intersects(*that(), interval_value_pair);
    }

    //==========================================================================
    //= Symmetric difference
    //==========================================================================

    /** If \c *this map contains \c key_value_pair it is erased, otherwise it is added. */
    SubType& flip(const element_type& key_value_pair)
    { 
        return itl::flip(*that(), key_value_pair); 
    }

    /** If \c *this map contains \c interval_value_pair it is erased, otherwise it is added. */
    SubType& flip(const segment_type& interval_value_pair)
    {
        return itl::flip(*that(), interval_value_pair);
    }

    //==========================================================================
    //= Iterator related
    //==========================================================================

    iterator lower_bound(const key_type& interval)
    { return _map.lower_bound(interval); }

    iterator upper_bound(const key_type& interval)
    { return _map.upper_bound(interval); }

    const_iterator lower_bound(const key_type& interval)const
    { return _map.lower_bound(interval); }

    const_iterator upper_bound(const key_type& interval)const
    { return _map.upper_bound(interval); }

    std::pair<iterator,iterator> equal_range(const key_type& interval)
    { return _map.equal_range(interval); }

    std::pair<const_iterator,const_iterator> equal_range(const key_type& interval)const
    { return _map.equal_range(interval); }

    iterator begin() { return _map.begin(); }
    iterator end()   { return _map.end(); }
    const_iterator begin()const { return _map.begin(); }
    const_iterator end()const   { return _map.end(); }
    reverse_iterator rbegin() { return _map.rbegin(); }
    reverse_iterator rend()   { return _map.rend(); }
    const_reverse_iterator rbegin()const { return _map.rbegin(); }
    const_reverse_iterator rend()const   { return _map.rend(); }

    iterator prior(iterator it_)
    { return it_ == this->_map.begin() ? this->_map.end() : --it_; }

    const_iterator prior(const_iterator it_)const
    { return it_ == this->_map.begin() ? this->_map.end() : --it_; }


    //==========================================================================
    //= Element iterator related
    //==========================================================================
    element_iterator elements_begin(){ return element_iterator(this->begin()); }
    element_iterator elements_end()  { return element_iterator(this->end());   }
    element_const_iterator elements_begin()const{ return element_const_iterator(this->begin()); }
    element_const_iterator elements_end()  const{ return element_const_iterator(this->end());   }

    element_reverse_iterator elements_rbegin(){ return element_reverse_iterator(this->rbegin()); }
    element_reverse_iterator elements_rend()  { return element_reverse_iterator(this->rend());   }
    element_const_reverse_iterator elements_rbegin()const{ return element_const_reverse_iterator(this->rbegin()); }
    element_const_reverse_iterator elements_rend()  const{ return element_const_reverse_iterator(this->rend());   }

    //==========================================================================
    //= Domain, sum
    //==========================================================================

    /** Gives the domain of the map as interval set */
  //  template 
  //  <
  //      template
  //      <class DomT, ITL_COMPARE Comp, ITL_INTERVAL2(ITL_COMPARE) Interv, ITL_ALLOC Allc>
  //      class IntervalSet
  //  >
  //  void domain(IntervalSet<DomainT,Compare,Interval,Alloc>& dom)const 
  //  { 
        //itl::domain(dom, *that());
  //      //CL dom.clear(); 
  //      //const_FOR_IMPLMAP(it_) 
  //      //    dom += it_->first; 
  //  } 

    //==========================================================================
    //= Algorithm unifiers
    //==========================================================================

    template<typename IteratorT>
    static const key_type& key_value(IteratorT value_){ return (*value_).first; }

    template<typename IteratorT>
    static codomain_type co_value(IteratorT value_){ return (*value_).second; }

    template<typename LeftIterT, typename RightIterT>
    static bool key_less(LeftIterT left_, RightIterT right_) 
    { return key_compare()((*left_).first, (*right_).first); }

    static value_type make_value(const key_type& key_value, const codomain_type& codom_val)
    { return value_type(key_value, codom_val); }

protected:
    sub_type* that() { return static_cast<sub_type*>(this); }
    const sub_type* that()const { return static_cast<const sub_type*>(this); }

protected:
    ImplMapT _map;
} ;


//==============================================================================
//= Equivalences and Orderings
//==============================================================================
//-----------------------------------------------------------------------------
// equality
//-----------------------------------------------------------------------------
template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool operator == (const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                         const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{
    return Set::lexicographical_equal(lhs, rhs);
}

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool operator != (const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                         const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{
    return !(lhs == rhs);
}


template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool is_protonic_equal(const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                              const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{
    return Map::lexicographical_protonic_equal(lhs, rhs);
}


template 
<
    class DomainT, class CodomainT, class Traits,
    ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE) Interval, ITL_ALLOC Alloc,
    template
    <    
        class, class, class, 
        ITL_COMPARE, ITL_COMBINE, ITL_SECTION, ITL_INTERVAL(ITL_COMPARE), ITL_ALLOC
    >
    class IntervalMap
>
bool is_protonic_equal
(
    const IntervalMap<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& left,
    const IntervalMap<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& right
)
{
    return Map::lexicographical_protonic_equal(left, right);
}



//-----------------------------------------------------------------------------
// order
//-----------------------------------------------------------------------------
template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool operator < (const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                        const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), 
        Compare<std::pair<ITL_INTERVAL_TYPE(Interval,DomainT,Compare),CodomainT> >()//NOTE DESIGN TTP: Why template template parameter Compare is needed
        );
}

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool operator > (const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                        const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{ return rhs < lhs; }

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool operator <= (const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                        const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{ return !(lhs > rhs); }

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
inline bool operator >= (const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& lhs,
                        const interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>& rhs)
{ return !(lhs < rhs); }

//-----------------------------------------------------------------------------
// min, max
//-----------------------------------------------------------------------------
template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, 
    ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, 
    ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
interval_base_map<SubType,DomainT,CodomainT,
                  Traits,Compare,Combine,Section,Interval,Alloc>& 
min_assign
(
          interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Compare,Combine,Section,Interval,Alloc>& object,
    const interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Compare,Combine,Section,Interval,Alloc>& operand
)
{
    typedef interval_base_map<SubType,DomainT,CodomainT,
                              Traits,Compare,Combine,Section,Interval,Alloc> map_type;
    ITL_const_FORALL(typename map_type, elem_, operand) 
        object.template _add<inplace_min >(*elem_); 

    return object; 
}

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, 
    ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, 
    ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
interval_base_map<SubType,DomainT,CodomainT,
                  Traits,Compare,Combine,Section,Interval,Alloc>& 
max_assign
(
          interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Compare,Combine,Section,Interval,Alloc>& object,
    const interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Compare,Combine,Section,Interval,Alloc>& operand
)
{
    typedef interval_base_map<SubType,DomainT,CodomainT,
                              Traits,Compare,Combine,Section,Interval,Alloc>    map_type;
    ITL_const_FORALL(typename map_type, elem_, operand) 
        object.template _add<inplace_max>(*elem_); 

    return object; 
}

//---------------------------------------------------------------------------------

template<class CharType, class CharTraits, 
    class SubType, class DomainT, class CodomainT, class Traits, 
    ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, 
    ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc>
std::basic_ostream<CharType, CharTraits>& operator <<
  (std::basic_ostream<CharType, CharTraits>& stream, 
   const interval_base_map<SubType,DomainT,CodomainT,Traits,
                           Compare,Combine,Section,Interval,Alloc>& object)
{
    typedef interval_base_map<SubType,DomainT,CodomainT,
                              Traits,Compare,Combine,Section,Interval,Alloc> IntervalMapT;
    stream << "{";
    ITL_const_FORALL(typename IntervalMapT, it_, object)
        stream << "(" << it_->first << "->" << it_->second << ")";

    return stream << "}";
}


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
struct is_map<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_map<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
struct has_inverse<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef has_inverse<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (has_inverse<CodomainT>::value)); 
};

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
struct is_interval_container<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_interval_container<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
struct absorbs_neutrons<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef absorbs_neutrons<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (Traits::absorbs_neutrons)); 
};

template 
<
    class SubType,
    class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_INTERVAL(ITL_COMPARE)  Interval, ITL_ALLOC Alloc
>
struct is_total<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef is_total<itl::interval_base_map<SubType,DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (Traits::is_total)); 
};



#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}} // namespace itl boost

#endif


