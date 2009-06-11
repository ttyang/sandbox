/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef __itl_interval_map_h_JOFA_080705__
#define __itl_interval_map_h_JOFA_080705__

#include <boost/assert.hpp>
#include <boost/itl/type_traits/is_map.hpp>
#include <boost/itl/interval_set.hpp>
#include <boost/itl/interval_base_map.hpp>
#include <boost/itl/interval_maps.hpp>

namespace boost{namespace itl
{

template<class DomainT, class CodomainT, class Traits, 
         ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, 
         template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
class split_interval_map;

/** implements a map as a map of intervals - on insertion overlapping intervals are split and associated values are combined.*/
template
<
    typename DomainT,
    typename CodomainT,
    class Traits = itl::partial_absorber,
    ITL_COMPARE Compare  = ITL_COMPARE_INSTANCE(std::less, DomainT),
    ITL_COMBINE Combine  = ITL_COMBINE_INSTANCE(itl::inplace_plus, CodomainT),
    ITL_SECTION Section  = ITL_SECTION_INSTANCE(itl::inplace_et, CodomainT), 
    template<class,ITL_COMPARE>class Interval = itl::interval,
    ITL_ALLOC   Alloc    = std::allocator
>
class interval_map:

    public interval_base_map<interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                             DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
{
public:
    typedef Traits traits;
    typedef       interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> type;
    typedef split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> split_type;
    typedef type overloadable_type;
    typedef type joint_type;
    typedef interval_base_map <interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                               DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> base_type;

    typedef Interval<DomainT,Compare> interval_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::value_type value_type;
    typedef typename base_type::element_type element_type;
    typedef typename base_type::segment_type segment_type;
    typedef typename base_type::domain_mapping_type domain_mapping_type;
    typedef typename base_type::interval_mapping_type interval_mapping_type;
    typedef typename base_type::ImplMapT ImplMapT;

    typedef typename base_type::codomain_combine codomain_combine;

    typedef interval_set<DomainT,Compare,Interval,Alloc> interval_set_type;
    typedef interval_set_type set_type;

    enum { fineness = 1 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    interval_map(): base_type() {}
    /// Copy constructor
    interval_map(const interval_map& src): base_type(src) {}


    /// Copy constructor for base_type
    template<class SubType>
    explicit interval_map
        (const interval_base_map<SubType,DomainT,CodomainT,
                                 Traits,Compare,Combine,Section,Interval,Alloc>& src)
    { assign(src); }

    explicit interval_map(domain_mapping_type& base_pair): base_type()
    { add(base_pair); }

    explicit interval_map(const value_type& value_pair): base_type()
    { add(value_pair); }

    /// Assignment operator
    template<class SubType>
    interval_map& operator =
        (const interval_base_map<SubType,DomainT,CodomainT,
                                 Traits,Compare,Combine,Section,Interval,Alloc>& src)
    { assign(src); return *this; }

    /// Assignment from a base interval_map.
    template<class SubType>
    void assign(const interval_base_map<SubType,DomainT,CodomainT,
                                        Traits,Compare,Combine,Section,Interval,Alloc>& src)
    {
        typedef interval_base_map<SubType,DomainT,CodomainT,
                                  Traits,Compare,Combine,Section,Interval,Alloc> base_map_type;
        this->clear();
        // Can be implemented via _map.insert: Interval joining not necessary.
        const_FORALL(typename base_map_type, it, src) 
            this->add(*it); 
    }
 
private:
    // The following _suffixed function templates funx_ are implementations
    // correspoding unsuffixed function templates funx of the base class.
    // For funx_ want to be used in the base class via derived SubType pointer:
    // that()->funx_. So they must be either public or made accessible by a
    // friend declaration:
    friend class
        interval_base_map <interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                                        DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>;

    bool contains_(const value_type& x)const;

    template<class Combiner>
    void add_(const value_type&);

    template<class Combiner>
    void subtract_(const value_type&);

    void insert_(const value_type& value);
    void erase_(const value_type& value);

private:
    bool insertable(const value_type& value)const
    { 
        return !value.KEY_VALUE.empty() 
            && !(Traits::absorbs_neutrons && value.CONT_VALUE == codomain_combine::neutron()); 
    }

    bool join_left(iterator& it);
    bool join_right(iterator& it);
    void join_neighbours(iterator& it){ join_left(it); join_right(it); };
    bool joinable(const iterator& some, const iterator& next)const;
    iterator joint_insert(iterator& some, const iterator& next);

    template<class Combiner>
    iterator fill_gap_join_left(const value_type&);

    template<class Combiner>
    iterator fill_gap_join_both(const value_type&);

    iterator fill_join_left(const value_type&);
    iterator fill_join_both(const value_type&);

    template<class Combiner>
    void add_rest(const interval_type& x_itv, const CodomainT& x_val, 
                  iterator& it, iterator& end_it);

    template<class Combiner>
    void add_rear(const interval_type& x_itv, const CodomainT& x_val, 
                  iterator& it);

    template<class Combiner>
    void subtract_rest(const interval_type& x_itv, const CodomainT& x_val, 
                       iterator& it, iterator& end_it);

    void insert_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it);
    void insert_rear(const interval_type& x_itv, const CodomainT& x_val, iterator& it);

    void erase_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it);

} ;


template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
bool interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::contains_(const value_type& interv_value)const
{
    interval_type interv = interv_value.KEY_VALUE;
    if(interv.empty()) 
        return true;

    type section;
    add_intersection(section, interv);
    return is_element_equal(section, type(interv_value));
}


template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
bool interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::joinable(const iterator& some, const iterator& next)const
{
    // assert: next != end && some++ == next
    return some->KEY_VALUE.touches(next->KEY_VALUE) 
        && some->CONT_VALUE == next->CONT_VALUE; 
}

template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
typename interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>::iterator 
    interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::joint_insert(iterator& left_it, const iterator& right_it)
{
    // both left and right are in the set and they are neighbours
    BOOST_ASSERT(right_it != this->_map.end());
    BOOST_ASSERT(left_it->KEY_VALUE.exclusive_less(right_it->KEY_VALUE));
    BOOST_ASSERT(left_it->KEY_VALUE.touches(right_it->KEY_VALUE));

    interval_type interval    = left_it->KEY_VALUE;
    //It has to be a copy, because is location will be erased 
    CodomainT value = left_it->CONT_VALUE;
    interval.extend(right_it->KEY_VALUE);

    this->_map.erase(left_it);
    this->_map.erase(right_it);
    
    std::pair<iterator,bool> insertion = this->_map.insert(make_pair(interval, value));
    iterator new_it = insertion.ITERATOR;
    BOOST_ASSERT(insertion.WAS_SUCCESSFUL);
    BOOST_ASSERT(new_it!=this->_map.end());
    left_it = new_it;
    return new_it;
}



template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
bool interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::join_left(iterator& it)
{
    if(it == this->_map.begin())
        return false;

    // there is a predecessor
    iterator it_pred = it; it_pred-- ;

    if(joinable(it_pred, it)) 
    {
        iterator it_leftExtended = joint_insert(it_pred, it);
        //CAUTION: it is now invalidated
        it = it_leftExtended;
        return true;
    }

    return false;
}

template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
bool interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::join_right(iterator& it)
{
    if(it == this->_map.end())
        return false;

    // there is a successor
    iterator it_succ = it; it_succ++ ;

    if(it_succ != this->_map.end() && joinable(it, it_succ)) 
    {
        joint_insert(it, it_succ);
        return true;
    }

    return false;
}



template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
typename interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>::iterator
interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::fill_join_left(const value_type& value)
{
    //collision free insert is asserted
    if(value.KEY_VALUE.empty())
        return this->_map.end();
    if(Traits::absorbs_neutrons && value.CONT_VALUE == codomain_combine::neutron())
        return this->_map.end();

    std::pair<iterator,bool> insertion = this->_map.insert(value);

    join_left(insertion.ITERATOR);

    return insertion.ITERATOR;
}

template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
typename interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>::iterator
interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::fill_join_both(const value_type& value)
{
    //collision free insert is asserted
    if(value.KEY_VALUE.empty())
        return this->_map.end();
    if(Traits::absorbs_neutrons && value.CONT_VALUE == codomain_combine::neutron())
        return this->_map.end();

    std::pair<iterator,bool> insertion = this->_map.insert(value);

    join_neighbours(insertion.ITERATOR);

    return insertion.ITERATOR;
}

//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
typename interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>::iterator
interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::fill_gap_join_left(const value_type& value)
{
    //collision free insert is asserted
    if(value.KEY_VALUE.empty())
        return this->_map.end();
    if(Traits::absorbs_neutrons && value.CONT_VALUE == Combiner::neutron())
        return this->_map.end();

    std::pair<iterator,bool> insertion;
    if(Traits::is_total)
    {
        CodomainT added_val = Combiner::neutron();
        Combiner()(added_val, value.CONT_VALUE);
        if(Traits::absorbs_neutrons && added_val == Combiner::neutron())
            return this->_map.end();
        else
            insertion = this->_map.insert(value_type(value.KEY_VALUE, added_val));
    }
    else
        insertion = this->_map.insert(value);

    join_left(insertion.ITERATOR);

    return insertion.ITERATOR;
}

template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
typename interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>::iterator
interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::fill_gap_join_both(const value_type& value)
{
    //collision free insert is asserted
    if(value.KEY_VALUE.empty())
        return this->_map.end();
    if(Traits::absorbs_neutrons && value.CONT_VALUE == Combiner::neutron())
        return this->_map.end();

    std::pair<iterator,bool> insertion;
    if(Traits::is_total)
    {
        CodomainT added_val = Combiner::neutron();
        Combiner()(added_val, value.CONT_VALUE);
        if(Traits::absorbs_neutrons && added_val == Combiner::neutron())
            return this->_map.end();
        else
            insertion = this->_map.insert(value_type(value.KEY_VALUE, added_val));
    }
    else
        insertion = this->_map.insert(value);

    join_neighbours(insertion.ITERATOR);

    return insertion.ITERATOR;
}


//-----------------------------------------------------------------------------
// add<Combinator>(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::add_(const value_type& x)
{
    const interval_type& x_itv = x.KEY_VALUE;
    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==Combiner::neutron()) 
        return;

    std::pair<iterator,bool> insertion;
    if(Traits::is_total)
    {
        CodomainT added_val = Combiner::neutron();
        Combiner()(added_val, x_val);
        if(Traits::absorbs_neutrons && added_val == Combiner::neutron())
            return;
        else
            insertion = this->_map.insert(value_type(x_itv, added_val));
    }
    else
        insertion = this->_map.insert(x);

    if(insertion.WAS_SUCCESSFUL)
        join_neighbours(insertion.ITERATOR);
    else
    {
        // Detect the first and the end iterator of the collision sequence
        iterator fst_it = this->_map.lower_bound(x_itv);
        iterator end_it = insertion.ITERATOR;
        if(end_it != this->_map.end())
            end_it++; 
        //assert(end_it == this->_map.upper_bound(x_itv));

        interval_type fst_itv = (*fst_it).KEY_VALUE;
        CodomainT cur_val     = (*fst_it).CONT_VALUE;

        interval_type leadGap; x_itv.right_subtract(leadGap, fst_itv);
        // this is a new Interval that is a gap in the current map
        //The first collision interval may grow by joining neighbours after insertion

        // only for the first there can be a leftResid: a part of *it left of x
        interval_type leftResid;  
        fst_itv.right_subtract(leftResid, x_itv);

        // handle special case for first

        interval_type interSec = fst_itv & x_itv;

        CodomainT cmb_val = cur_val;
        Combiner()(cmb_val, x_val);

        iterator snd_it = fst_it; snd_it++; 

        if(snd_it == end_it) 
        {
            // first == last

            interval_type endGap; x_itv.left_subtract(endGap, fst_itv);
            // this is a new Interval that is a gap in the current map

            // only for the last there can be a rightResid: a part of *it right of x
            interval_type rightResid;  (*fst_it).KEY_VALUE.left_subtract(rightResid, x_itv);

            this->_map.erase(fst_it);
            fill_join_left(value_type(leftResid,  cur_val));

            if(endGap.empty() && rightResid.empty())
                fill_join_both(value_type(interSec,   cmb_val));
            else
                fill_join_left(value_type(interSec,   cmb_val));

            if(!leadGap.empty())
                fill_gap_join_both<Combiner>(value_type(leadGap, x_val));
            if(!endGap.empty())
                fill_gap_join_both<Combiner>(value_type(endGap, x_val));
            else
                fill_join_left(value_type(rightResid, cur_val));
        }
        else
        {
            this->_map.erase(fst_it);
            fill_join_left(value_type(leftResid, cur_val));
            fill_join_left(value_type(interSec,  cmb_val));

            if(!leadGap.empty())
                fill_gap_join_both<Combiner>(value_type(leadGap, x_val));

            // shrink interval
            interval_type x_rest(x_itv);
            x_rest.left_subtract(fst_itv);

            add_rest<Combiner>(x_rest, x_val, snd_it, end_it);
        }
    }
}

template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::add_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it)
{
    iterator nxt_it = it; nxt_it++;
    interval_type x_rest = x_itv, left_gap, common, cur_itv;

    while(nxt_it!=end_it)
    {
        cur_itv = (*it).KEY_VALUE ;            
        x_rest.right_subtract(left_gap, cur_itv);

        Combiner()(it->CONT_VALUE, x_val);
        fill_gap_join_left<Combiner>(value_type(left_gap, x_val)); //A posteriori

        if(Traits::absorbs_neutrons && it->CONT_VALUE == Combiner::neutron())
            this->_map.erase(it++);
        else
        {
            // after filling that gap there may be another joining opportunity
            join_left(it);
            it++;
        }

        // shrink interval
        x_rest.left_subtract(cur_itv);
        nxt_it++;
    }

    add_rear<Combiner>(x_rest, x_val, it);
}

template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::add_rear(const interval_type& x_rest, const CodomainT& x_val, iterator& it)
{
    interval_type cur_itv = (*it).KEY_VALUE ;
    CodomainT     cur_val = (*it).CONT_VALUE ;

    interval_type lead_gap;
    x_rest.right_subtract(lead_gap, cur_itv);

    interval_type common = cur_itv & x_rest;
    CodomainT cmb_val = cur_val;
    Combiner()(cmb_val, x_val);

    interval_type end_gap; 
    x_rest.left_subtract(end_gap, cur_itv);
    
    // only for the last there can be a rightResid: a part of *it right of x
    interval_type right_resid;  
    cur_itv.left_subtract(right_resid, x_rest);

    this->_map.erase(it);
    if(end_gap.empty() && right_resid.empty())
        fill_join_both(value_type(common,   cmb_val));
    else
        fill_join_left(value_type(common,   cmb_val));

    if(!lead_gap.empty())
        fill_gap_join_both<Combiner>(value_type(lead_gap, x_val));
    if(!end_gap.empty())
        fill_gap_join_both<Combiner>(value_type(end_gap, x_val));
    else
        fill_join_left(value_type(right_resid, cur_val));
}


//-----------------------------------------------------------------------------
// subtract<Combinator>(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::subtract_(const value_type& x)
{
    const interval_type& x_itv = x.KEY_VALUE;

    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==Combiner::neutron()) 
        return;

    iterator fst_it = this->_map.lower_bound(x_itv);
    if(fst_it==this->_map.end()) return;
    iterator end_it = this->_map.upper_bound(x_itv);
    if(fst_it==end_it) return;

    interval_type fst_itv = (*fst_it).KEY_VALUE ;
    // must be copies because fst_it will be erased
    CodomainT fst_val = (*fst_it).CONT_VALUE ;

    // only for the first there can be a leftResid: a part of *it left of x
    interval_type leftResid;  
    fst_itv.right_subtract(leftResid, x_itv);

    // handle special case for first

    interval_type interSec = fst_itv & x_itv;

    CodomainT cmb_val = fst_val;
    Combiner()(cmb_val, x_val);

    iterator snd_it = fst_it; snd_it++;
    if(snd_it == end_it) 
    {
        // only for the last there can be a rightResid: a part of *it right of x
        interval_type rightResid;  (*fst_it).KEY_VALUE.left_subtract(rightResid, x_itv);

        this->_map.erase(fst_it);
        fill_join_left(value_type(leftResid, fst_val));

        if(rightResid.empty())
            fill_join_both(value_type(interSec,   cmb_val));
        else
            fill_join_left(value_type(interSec,   cmb_val));

        fill_join_both(value_type(rightResid, fst_val));
    }
    else
    {
        // first AND NOT last
        this->_map.erase(fst_it);
        
        fill_join_left(value_type(leftResid, fst_val));
        fill_join_left(value_type(interSec,  cmb_val));

        // shrink interval
        interval_type x_rest(x_itv);
        x_rest.left_subtract(fst_itv);

        subtract_rest<Combiner>(x_rest, x_val, snd_it, end_it);
    }
}



template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
    template<class Combiner>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::subtract_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it)
{
    iterator nxt_it=it; nxt_it++;

    while(nxt_it!=end_it)
    {
        CodomainT& cur_val = (*it).CONT_VALUE ;
        Combiner()(cur_val, x_val);

        if(Traits::absorbs_neutrons && cur_val==Combiner::neutron())
            this->_map.erase(it++); 
        else
        {
            join_left(it);
            it++;
        }

        nxt_it=it; nxt_it++;
    }

    // it refers the last overlaying intervals of x_itv
    const interval_type& cur_itv = (*it).KEY_VALUE ;

    interval_type rightResid; 
    cur_itv.left_subtract(rightResid, x_itv);

    if(rightResid.empty())
    {
        CodomainT& cur_val = (*it).CONT_VALUE ;
        Combiner()(cur_val, x_val);
        if(Traits::absorbs_neutrons && cur_val==Combiner::neutron())
            this->_map.erase(it);
        else
        {
            join_left(it);
            // cur_val is the last -= modified value. There may be an
            // adjoint right neighbour that is now joinable.
            if(it != this->_map.end())
            {
                iterator out_it = it; out_it++;
                if(out_it != this->_map.end() && joinable(it, out_it))
                    joint_insert(it,out_it);
            }
        }
    }
    else
    {
        CodomainT cur_val = (*it).CONT_VALUE ;
        CodomainT cmb_val = cur_val ;
        Combiner()(cmb_val, x_val);
        interval_type interSec = cur_itv & x_itv; 

        this->_map.erase(it);
        if(rightResid.empty())
            fill_join_both(value_type(interSec, cmb_val));
        else
            fill_join_left(value_type(interSec, cmb_val));

        fill_join_both(value_type(rightResid, cur_val));
    }
}



//-----------------------------------------------------------------------------
// insert(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::insert_(const value_type& x)
{
    const interval_type& x_itv = x.KEY_VALUE;
    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==codomain_combine::neutron()) 
        return;

    std::pair<typename ImplMapT::iterator,bool> 
        insertion = this->_map.insert(x);

    if(insertion.WAS_SUCCESSFUL)
        join_neighbours(insertion.ITERATOR);
    else
    {
        // Detect the first and the end iterator of the collision sequence
        iterator fst_it = this->_map.lower_bound(x_itv);
        iterator end_it = insertion.ITERATOR;
        if(end_it != this->_map.end())
            end_it++; 
        //assert(end_it == this->_map.upper_bound(x_itv));

        interval_type fst_itv = (*fst_it).KEY_VALUE ;
        interval_type leadGap; x_itv.right_subtract(leadGap, fst_itv);
        // this is a new Interval that is a gap in the current map

        // only for the first there can be a leftResid: a part of *it left of x
        interval_type leftResid;  fst_itv.right_subtract(leftResid, x_itv);

        // handle special case for first

        iterator snd_it = fst_it; snd_it++;
        if(snd_it == end_it) 
        {
            //Fill gap after iterator compare bcause iterators are modified by joining
            if(!leadGap.empty())
                fill_join_both(value_type(leadGap, x_val));

            interval_type endGap; x_itv.left_subtract(endGap, fst_itv);
            // this is a new Interval that is a gap in the current map
            fill_join_both(value_type(endGap, x_val));
        }
        else
        {
            if(!leadGap.empty())
                fill_join_both(value_type(leadGap, x_val));

            // shrink interval
            interval_type x_rest(x_itv);
            x_rest.left_subtract(fst_itv);

            insert_rest(x_rest, x_val, snd_it, end_it);
        }
    }
}


template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::insert_rest(const interval_type& x_itv, const CodomainT& x_val, 
                  iterator& it, iterator& end_it)
{
    iterator nxt_it = it; nxt_it++;
    interval_type x_rest = x_itv, gap, common, cur_itv;

    for(; nxt_it!=end_it; ++it, ++nxt_it)
    {
        cur_itv = (*it).KEY_VALUE ;            
        x_rest.right_subtract(gap, cur_itv);

        if(!gap.empty())
        {
            fill_join_left(value_type(gap, x_val));
            // after filling that gap there may be another joining opportunity
            join_left(it);
        }

        // shrink interval
        x_rest.left_subtract(cur_itv);
    }

    insert_rear(x_rest, x_val, it);
}

template <typename DomainT, typename CodomainT, class Traits,
          ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::insert_rear(const interval_type& x_rest, const CodomainT& x_val, 
                  iterator& it)
{
    interval_type cur_itv = (*it).KEY_VALUE ;

    interval_type left_gap;
    x_rest.right_subtract(left_gap, cur_itv);

    if(!left_gap.empty())
    {
        fill_join_left(value_type(left_gap, x_val));
        // after filling that gap there may be another joining opportunity
        join_left(it);
    }

    interval_type end_gap; 
    x_rest.left_subtract(end_gap, cur_itv);

    fill_join_both(value_type(end_gap, x_val));
}


//-----------------------------------------------------------------------------
// erase(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::erase_(const value_type& x)
{
    const interval_type& x_itv = x.KEY_VALUE;
    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==codomain_combine::neutron()) 
        return;

    iterator fst_it = this->_map.lower_bound(x_itv);
    if(fst_it==this->_map.end()) return;
    iterator end_it = this->_map.upper_bound(x_itv);
    if(fst_it==end_it) return;

    interval_type fst_itv = (*fst_it).KEY_VALUE ;
    // must be copies because fst_it will be erased
    CodomainT fst_val = (*fst_it).CONT_VALUE ;

    // only for the first there can be a leftResid: a part of *it left of x
    interval_type leftResid;  
    fst_itv.right_subtract(leftResid, x_itv);

    // handle special case for first

    interval_type interSec = fst_itv & x_itv;

    iterator snd_it = fst_it; snd_it++;
    if(snd_it == end_it) 
    {
        // only for the last there can be a rightResid: a part of *it right of x
        interval_type rightResid;  (*fst_it).KEY_VALUE.left_subtract(rightResid, x_itv);

        if(!interSec.empty() && fst_val == x_val)
        {
            this->_map.erase(fst_it);
            insert_(value_type(leftResid,  fst_val));
            insert_(value_type(rightResid, fst_val));
        }
    }
    else
    {
        // first AND NOT last
        if(!interSec.empty() && fst_val == x_val)
        {
            this->_map.erase(fst_it);
            insert_(value_type(leftResid, fst_val));
        }

        erase_rest(x_itv, x_val, snd_it, end_it);
    }
}


template <typename DomainT, typename CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
void interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
    ::erase_rest(const interval_type& x_itv, const CodomainT& x_val, 
                 iterator& it, iterator& end_it)
{
    iterator nxt_it=it; nxt_it++;

    // For all intervals within loop: it->KEY_VALUE are contained_in x_itv
    while(nxt_it!=end_it)
    {
        if((*it).CONT_VALUE == x_val)
            this->_map.erase(it++); 
        else it++;

        nxt_it=it; nxt_it++;
    }

    // it refers the last overlaying intervals of x_itv
    interval_type cur_itv = (*it).KEY_VALUE ;
    // Has to be a copy, cause 'it' will be erased
    CodomainT cur_val = (*it).CONT_VALUE;

    interval_type rightResid; 
    cur_itv.left_subtract(rightResid, x_itv);

    if(rightResid.empty())
    {
        if(cur_val == x_val)
            this->_map.erase(it);
    }
    else
    {
        interval_type interSec = cur_itv & x_itv; 
        if(!interSec.empty() && cur_val == x_val)
        {
            this->_map.erase(it);
            insert_(value_type(rightResid, cur_val));
        }
    }
}


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_set<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_set<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    static const bool value = true; 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_map<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_map<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    static const bool value = true; 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct has_inverse<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef has_inverse<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    static const bool value = has_inverse<CodomainT>::value; 
};


template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_interval_container<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef is_interval_container<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    static const bool value = true; 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct absorbs_neutrons<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef absorbs_neutrons<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    static const bool value = Traits::absorbs_neutrons; 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct is_total<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef is_total<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    static const bool value = Traits::is_total; 
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, template<class,ITL_COMPARE>class Interval, ITL_ALLOC Alloc>
struct type_to_string<itl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    static std::string apply()
    { 
        return "itv_map<"+ type_to_string<DomainT>::apply()   + ","
                         + type_to_string<CodomainT>::apply() + ","
                         + type_to_string<Traits>::apply()    + ">"; 
    }
};

}} // namespace itl boost

#endif


