/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef __itl_separate_interval_set_h_JOFA_080608__
#define __itl_separate_interval_set_h_JOFA_080608__

#include <boost/assert.hpp>
#include <boost/itl/interval_base_set.hpp>
#include <boost/itl/interval_set.hpp>

namespace boost{namespace itl
{

/** Implements a set as a set of intervals - leaving adjoining intervals separate */
template 
<
    typename                         DomainT, 
    ITL_COMPARE                      Compare  = ITL_COMPARE_INSTANCE(std::less, DomainT),
    template<class,ITL_COMPARE>class Interval = itl::interval,
    ITL_ALLOC                        Alloc    = std::allocator
> 
class separate_interval_set: 
    public interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>,
                             DomainT,Compare,Interval,Alloc>
{
public:
    // inherit all typedefs

    typedef interval_base_set<itl::separate_interval_set<DomainT,Compare,Interval,Alloc>,
                              DomainT,Compare,Interval,Alloc> base_type;

    typedef separate_interval_set<DomainT,Compare,Interval,Alloc> type;
	typedef type overloadable_type;

    typedef interval_set<DomainT,Compare,Interval,Alloc> joint_type;

    /// The domain type of the set
    typedef DomainT   domain_type;
    /// The codomaintype is the same as domain_type
    typedef DomainT   codomain_type;

    /// The element type of the set
    typedef DomainT   element_type;
    /// The interval type of the set
    typedef Interval<DomainT,Compare> interval_type;
    /// The segment type of the set
    typedef interval_type   segment_type;

    /// Comparison functor for domain values
    typedef ITL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    /// Comparison functor for intervals
    typedef exclusive_less<interval_type> interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less<interval_type> key_compare;

    /// The allocator type of the set
    typedef Alloc<interval_type> allocator_type;

    /// allocator type of the corresponding element set
    typedef Alloc<DomainT> domain_allocator_type;

    /// The corresponding atomized type representing this interval container of elements
    typedef typename itl::set<DomainT,Compare,Alloc> atomized_type;

    /// Container type for the implementation 
    typedef typename itl::set<interval_type,ITL_EXCLUSIVE_LESS(interval_type),Alloc> ImplSetT;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::data_type  data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;

    /// iterator for iteration over intervals
    typedef typename ImplSetT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_iterator const_iterator;


	enum { fineness = 2 };

public:
	//==========================================================================
	//= Construct, copy, destruct
	//==========================================================================
    /// Default constructor for the empty object
    separate_interval_set(): base_type() {}
    /// Copy constructor
    separate_interval_set(const separate_interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    separate_interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { assign(src); }

    /// Constructor for a single element
    explicit separate_interval_set(const domain_type& elem): base_type() { add(elem); }
    /// Constructor for a single interval
    explicit separate_interval_set(const interval_type& itv): base_type() { add(itv); }

    /// Assignment operator
    template<class SubType>
    separate_interval_set& operator =
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { assign(src); return *this; }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        typedef interval_base_set<SubType,DomainT,Compare,Interval,Alloc> base_set_type;
        this->clear();
        // Can be implemented via _set.insert: Interval joining not necessary.
        const_FORALL(typename base_set_type, it, src) 
            this->_set.insert(*it); 
    }

private:
	friend class 
		interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>,
                                                DomainT,Compare,Interval,Alloc>;

    /// Does the set contain the interval  <tt>x</tt>?
    bool contains_(const interval_type& x)const;

    /// Insertion of an interval <tt>x</tt>
    void add_(const value_type& x);

    /// Removal of an interval <tt>x</tt>
    void subtract_(const value_type& x);

private:
    /// Treatment of adjoint intervals on insertion
    void handle_neighbours(const iterator& it){}
} ;


template <typename DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
bool separate_interval_set<DomainT,Compare,Interval,Alloc>::contains_(const interval_type& interv)const
{
    if(interv.empty()) 
        return true;

    type section;
    add_intersection(section, interv);
    return is_element_equal(section, type(interv));
}


template<class DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void separate_interval_set<DomainT,Compare,Interval,Alloc>::add_(const value_type& x)
{
    if(x.empty()) return;

    std::pair<typename ImplSetT::iterator,bool> insertion = this->_set.insert(x);

    if(insertion.WAS_SUCCESSFUL)
        handle_neighbours(insertion.ITERATOR);
    else
    {
        typename ImplSetT::iterator fst_it = this->_set.lower_bound(x);
        typename ImplSetT::iterator end_it = this->_set.upper_bound(x);

        typename ImplSetT::iterator it=fst_it, nxt_it=fst_it, victim;
        interval_type leftResid;  (*it).right_subtract(leftResid,x);
        interval_type rightResid;

        while(it!=end_it)
        { 
            if((++nxt_it)==end_it) 
                (*it).left_subtract(rightResid,x);
            victim = it; it++; this->_set.erase(victim);
        }

        interval_type extended = x;
        extended.extend(leftResid).extend(rightResid);
        extended.extend(rightResid);
        add_(extended);
    }
}


template<class DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void separate_interval_set<DomainT,Compare,Interval,Alloc>::subtract_(const value_type& x)
{
    if(x.empty()) return;
    typename ImplSetT::iterator fst_it = this->_set.lower_bound(x);
    if(fst_it==this->_set.end()) return;
    typename ImplSetT::iterator end_it = this->_set.upper_bound(x);

    typename ImplSetT::iterator it=fst_it, nxt_it=fst_it, victim;
    interval_type leftResid; (*it).right_subtract(leftResid,x);
    interval_type rightResid;

    while(it!=end_it)
    { 
        if((++nxt_it)==end_it) (*it).left_subtract(rightResid,x);
        victim = it; it++; this->_set.erase(victim);
    }

    add_(leftResid);
    add_(rightResid);
}

//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_set<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
	typedef is_set<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
	static const bool value = true; 
};

template <class DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_interval_container<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
	typedef is_interval_container<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
	static const bool value = true; 
};

template <class DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_interval_separator<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
	typedef is_interval_separator<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
	static const bool value = true; 
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ITL_COMPARE Compare, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct type_to_string<itl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "se_itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};

}} // namespace itl boost

#endif


