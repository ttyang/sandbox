/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+-----------------------------------------------------------------------------+
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
+----------------------------------------------------------------------------*/

/* ------------------------------------------------------------------
class split_interval_map
--------------------------------------------------------------------*/
#ifndef __split_interval_map_h_JOFA_000706__
#define __split_interval_map_h_JOFA_000706__

#include <boost/itl/interval_set.hpp>
#include <boost/itl/interval_map.hpp>
#include <boost/itl/interval_base_map.hpp>
#include <boost/itl/interval_maps.hpp>
#include <boost/itl/split_interval_set.hpp>

namespace boost{namespace itl
{

    /// implements a map as a map of intervals - on insertion overlapping intervals are split and associated values are combined.
    /** 
        Template-class <b>split_interval_map</b>
        implements a map as a map of intervals - On insertion overlapping intervals are
        <b>split</b> and associated values are combined.
       
        Template parameter <b>DomainT</b>: Domain type of the map. Also type of the
        map's keys.

          Suitable as domain types are all datatypes that posess a partial order.
        In particular all discrete atomic datatypes like <tt>int, short, long</tt> and
        atomic pseudo-continuous datatypes <tt>float, double</tt> may be instantiated.

        Datatypes for the codomain parameter have to <b>implement</b> operations
        <tt>+=</tt>, <tt>-=</tt>, <tt>==</tt> (equality) and <tt>CodomainT()</tt> (default constructor).

        The default constructor <tt>CodomainT()</tt> has to contruct a neutral element
        such that the following holds:

          If <tt>x = y; y += CodomainT();</tt> then <tt>x==y;</tt> and
          If <tt>x = y; y -= CodomainT();</tt> then <tt>x==y;</tt>

          Template parameter <b>Interval=itl::interval</b>: Template type of interval used
        to implement the map. The default <b>itl::interval</b> uses the
        interval class template that comes with this library. Own implementation of interval
        classes are possible (but not trivial).

        <b>split_interval_map</b> implements a map <tt>map<DomainT, CodomainT></tt> as a map
        of intervals <tt>map<interval<DomainT>, CodomainT, ExclusiveLessT<Interval> ></tt>

        Interval maps <tt>split_interval_map<DomainT,CodomainT></tt> can be used similar (and in many
        aspects exactly like) common stl-maps. Unlike to stl-maps where you store
        a value for every key an interval map stores a contents value for an interval of
        keys. In it's degenerated form the key intervals contain a single element
        only. Then the interval map works like a normal stl-map. But if you work in problem
        domains where you associate values to large contiguous intervals, interval maps
        are very useful and efficient.


        Class <tt>interval_base_map</tt>  yields the following benefits:
      
        <ul>
            <li> A set of intervals is conceived as the domain set of the map. 
                The complexity involved with
                operations on intervals maps is encapsulated. The user of the class who
                wants to perform operations on interval maps is no more concerned
                with questions of overlapping, joining and bordering intervals.
            <li>
                <b>split_interval_map</b> gives an efficient implementation of maps consisting
                of larger contiguous chunks. Very large, even uncountably infinite maps
                can be represented in a compact way and handled efficiently.
            <li>
                <b>split_interval_map</b> serves as a overlay- or collision-computer.
        </ul>

        <b>split_interval_map as overlay computer</b>

        An object <tt>split_interval_map<int,int> overlays;</tt> computes the overlays or 
        collisions of intervalls which have been inserted into it, if they are
        associated with the <tt>int</tt>-value <tt>1</tt> as the codommain value.

        If a newly inserted interval overlaps with intervals which are already in the
        map, the interval is split up at the borders of the collisions. The assiciated
        values of the overlapping intervals are incremented by 1, thus counting
        the numbers of overlaps.

        If sets are used as codomain types, interval_maps will compute unions of
        associated maps in case of interval collisions.

          <b>Restrictions: </b>
        
        A small number of functions can only be used for <b>discrete</b> domain datatypes 
        (<tt>short, int, Date</tt> etc.) that implement operators <tt>++</tt> and <tt>--</tt>.

        These functions are tagged in the documentation. Using such functions
        for continuous domain datatypes yields compiletime errors. C.f. getting
        the <tt>first()</tt> element of a left open interval makes sense for intervals of
        int but not for intervals of double.

        @author  Joachim Faulhaber
    */
    template
    <
        typename DomainT,
        typename CodomainT,
        class Traits = itl::neutron_absorber,
        template<class>class Interval = itl::interval,
        template<class>class Compare  = std::less,
        template<class>class Alloc    = std::allocator
    >
    class split_interval_map:
        public interval_base_map<split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>, 
                                 DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    {
    public:
        typedef Traits traits;
        typedef split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc> type;
        typedef       interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc> joint_type;
        typedef interval_base_map <split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>, 
                                   DomainT,CodomainT,Traits,Interval,Compare,Alloc> base_type;

        typedef split_interval_map<DomainT,CodomainT,itl::neutron_absorber,Interval,Compare,Alloc>
            neutron_absorber_type;

        typedef Interval<DomainT> interval_type;
        typedef typename base_type::iterator iterator;
        typedef typename base_type::value_type value_type;
        typedef typename base_type::base_value_type base_value_type;
        typedef typename base_type::base_pair_type  base_pair_type;
        typedef typename base_type::ImplMapT ImplMapT;

        typedef interval_set<DomainT,Interval,Compare,Alloc> interval_set_type;
        typedef interval_set_type set_type;

        /// Default constructor for the empty map 
        split_interval_map(): base_type() {}
        /// Copy constructor
        split_interval_map(const split_interval_map& src): base_type(src) {}

        explicit split_interval_map(base_pair_type& base_pair): base_type()
        { add(base_pair); }

        explicit split_interval_map(const value_type& value_pair): base_type()
        { add(value_pair); }

        /// Assignment operator
        template<class SubType>
        split_interval_map& operator =
            (const interval_base_map<SubType,DomainT,CodomainT,
                                     Traits,Interval,Compare,Alloc>& src)
        { assign(src); return *this; }

        /// Assignment from a base interval_map.
        template<class SubType>
        void assign(const interval_base_map<SubType,DomainT,CodomainT,
                                            Traits,Interval,Compare,Alloc>& src)
        {
            typedef interval_base_map<SubType,DomainT,CodomainT,
                                      Traits,Interval,Compare,Alloc> base_map_type;
            this->clear();
            // Can be implemented via _map.insert: Interval joining not necessary.
            const_FORALL(typename base_map_type, it, src) 
                this->_map.insert(*it); 
        }

        bool contains_(const value_type& x)const;


        template<template<class>class Combinator>
        void add_(const value_type&, const Combinator<CodomainT>&);

        void add_(const value_type& value)
        { add_(value, inplace_plus<CodomainT>()); }

        template<template<class>class Combinator>
        void subtract_(const value_type&, const Combinator<CodomainT>&);

        void subtract_(const value_type& value)
        {
            if(Traits::emits_neutrons)
                add_(value, inplace_minus<CodomainT>()); 
            else
                subtract_(value, inplace_minus<CodomainT>()); 
        }

        void insert_(const value_type& value);
        void erase_(const value_type& value);

        void handle_neighbours(const iterator& it){}
        
        //TESTCODE
        void getResiduals(const interval_type& x_itv, interval_type& leftResid, interval_type& rightResid);

    private:

        void fill(const value_type&);

        template<template<class>class Combinator>
        void fill_gap(const value_type&, const Combinator<CodomainT>& combine);

        template<template<class>class Combinator>
        void add_rest(const interval_type& x_itv, const CodomainT& x_val, 
                      iterator& it, iterator& end_it,
					  const Combinator<CodomainT>& combine);

        template<template<class>class Combinator>
        void add_rear(const interval_type& x_itv, const CodomainT& x_val, 
			          iterator& it, const Combinator<CodomainT>& combine);

        template<template<class>class Combinator>
        void subtract_rest(const interval_type& x_itv, const CodomainT& x_val, 
			               iterator& it, iterator& end_it, 
						   const Combinator<CodomainT>& combine);

        void insert_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it);
        void insert_rear(const interval_type& x_itv, const CodomainT& x_val, iterator& it);

        void erase_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it);
    } ;


    template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    bool split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
        ::contains_(const value_type& interv_value)const
    {
        interval_type interv = interv_value.KEY_VALUE;
        if(interv.empty()) 
            return true;

        type section;
        add_intersection(section, interv);
        return is_element_equal(section, type(interv_value));
    }




    template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>::getResiduals(const interval_type& x_itv, interval_type& leftResid, interval_type& rightResid)
    {
        iterator fst_it = this->_map.lower_bound(x_itv);
        iterator end_it = this->_map.upper_bound(x_itv);
        
        if(fst_it==end_it)
        {
            leftResid.clear();
            rightResid.clear();
            return;
        }

        (*fst_it).KEY_VALUE.left_surplus(leftResid, x_itv);
        iterator lst_it = fst_it; lst_it++;

        if(lst_it==end_it)
        {
            rightResid.clear();
            return;
        }

        lst_it=end_it; lst_it--;

        (*lst_it).KEY_VALUE.right_surplus(rightResid, x_itv);
    }


template <typename DomainT, typename CodomainT, class Traits,
          template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::fill(const value_type& value)
{
    //collision free insert is asserted
    if(value.KEY_VALUE.empty())
        return;
    if(Traits::absorbs_neutrons && value.CONT_VALUE == CodomainT())
        return;
    this->_map.insert(value);
}

template <typename DomainT, typename CodomainT, class Traits,
          template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    template<template<class>class Combinator>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::fill_gap(const value_type& value, const Combinator<CodomainT>& combine)
{
    //CL static Combinator<CodomainT> combine;
    //collision free insert is asserted
    if(value.KEY_VALUE.empty())
        return;
    if(Traits::absorbs_neutrons && value.CONT_VALUE == CodomainT())
        return;

    if(Traits::emits_neutrons)
    {
        CodomainT added_val = CodomainT();
        combine(added_val, value.CONT_VALUE);
        this->_map.insert(value_type(value.KEY_VALUE, added_val));
    }
    else
        this->_map.insert(value);
}

//-----------------------------------------------------------------------------
// add<Combinator>(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    template<template<class>class Combinator>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::add_(const value_type& x, const Combinator<CodomainT>& combine)
{
    //CL static Combinator<CodomainT> combine;
    const interval_type& x_itv = x.KEY_VALUE;

    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==CodomainT()) 
        return;

    std::pair<iterator,bool> insertion;
    if(Traits::emits_neutrons)
    {
        CodomainT added_val = CodomainT();
        combine(added_val, x_val);
        insertion = this->_map.insert(value_type(x_itv, added_val));
    }
    else
        insertion = this->_map.insert(x);

    if(!insertion.WAS_SUCCESSFUL)
    {
        // Detect the first and the end iterator of the collision sequence
        iterator fst_it = this->_map.lower_bound(x_itv);
        iterator end_it = insertion.ITERATOR;
        if(end_it != this->_map.end())
            end_it++; 
        //assert(end_it == this->_map.upper_bound(x_itv));

        interval_type fst_itv = (*fst_it).KEY_VALUE ;
        CodomainT cur_val     = (*fst_it).CONT_VALUE ;


        interval_type leadGap; x_itv.left_surplus(leadGap, fst_itv);
        // this is a new Interval that is a gap in the current map
        fill_gap(value_type(leadGap, x_val), combine);

        // only for the first there can be a leftResid: a part of *it left of x
        interval_type leftResid;  fst_itv.left_surplus(leftResid, x_itv);

        // handle special case for first

        interval_type interSec;
        fst_itv.intersect(interSec, x_itv);

        CodomainT cmb_val = cur_val;
        combine(cmb_val, x_val);

        iterator snd_it = fst_it; snd_it++;
        if(snd_it == end_it) 
        {
            // first == last

            interval_type endGap; x_itv.right_surplus(endGap, fst_itv);
            // this is a new Interval that is a gap in the current map
            fill_gap(value_type(endGap, x_val), combine);

            // only for the last there can be a rightResid: a part of *it right of x
            interval_type rightResid;  (*fst_it).KEY_VALUE.right_surplus(rightResid, x_itv);

            this->_map.erase(fst_it);
            fill(value_type(leftResid,  cur_val));
            fill(value_type(interSec,   cmb_val));
            fill(value_type(rightResid, cur_val));
        }
        else
        {
            this->_map.erase(fst_it);
            fill(value_type(leftResid, cur_val));
            fill(value_type(interSec,  cmb_val));

            // shrink interval
            interval_type x_rest(x_itv);
            x_rest.left_subtract(fst_itv);

            add_rest(x_rest, x_val, snd_it, end_it, combine);
        }
    }
}

template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    template<template<class>class Combinator>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::add_rest(const interval_type& x_itv, const CodomainT& x_val, 
               iterator& it, iterator& end_it,
               const Combinator<CodomainT>& combine)
{
    //CL static Combinator<CodomainT> combine;
    iterator nxt_it = it; nxt_it++;
    interval_type x_rest = x_itv, gap, common, cur_itv;

    while(nxt_it!=end_it)
    {
        cur_itv = (*it).KEY_VALUE ;            
        x_rest.left_surplus(gap, cur_itv);

        combine(it->CONT_VALUE, x_val);
        fill_gap(value_type(gap, x_val), combine);

        if(Traits::absorbs_neutrons && it->CONT_VALUE == CodomainT())
            this->_map.erase(it++);
        else it++;

        // shrink interval
        x_rest.left_subtract(cur_itv);
        nxt_it++;
    }

    add_rear(x_rest, x_val, it, combine);
}

template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    template<template<class>class Combinator>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::add_rear(const interval_type& x_rest, const CodomainT& x_val, iterator& it,
	           const Combinator<CodomainT>& combine)
{
    //CL static Combinator<CodomainT> combine;
    interval_type cur_itv = (*it).KEY_VALUE ;
    CodomainT     cur_val = (*it).CONT_VALUE ;

    interval_type left_gap;
    x_rest.left_surplus(left_gap, cur_itv);
    fill_gap(value_type(left_gap, x_val), combine);

    interval_type common;
    cur_itv.intersect(common, x_rest);

    CodomainT cmb_val = cur_val;
    combine(cmb_val, x_val);

    interval_type end_gap; 
    x_rest.right_surplus(end_gap, cur_itv);
    fill_gap(value_type(end_gap, x_val), combine);

    // only for the last there can be a rightResid: a part of *it right of x
    interval_type right_resid;  
    cur_itv.right_surplus(right_resid, x_rest);

    this->_map.erase(it);
    fill(value_type(common,   cmb_val));
    fill(value_type(right_resid, cur_val));
}


//-----------------------------------------------------------------------------
// subtract<Combinator>(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    template<template<class>class Combinator>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::subtract_(const value_type& x, const Combinator<CodomainT>& combine)
{
    //CL static Combinator<CodomainT> combine;
    const interval_type& x_itv = x.KEY_VALUE;

    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==CodomainT()) 
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
    fst_itv.left_surplus(leftResid, x_itv);

    // handle special case for first

    interval_type interSec;
    fst_itv.intersect(interSec, x_itv);

    CodomainT cmb_val = fst_val;
    combine(cmb_val, x_val);

    iterator snd_it = fst_it; snd_it++;
    if(snd_it == end_it) 
    {
        // only for the last there can be a rightResid: a part of *it right of x
        interval_type rightResid;  (*fst_it).KEY_VALUE.right_surplus(rightResid, x_itv);

        this->_map.erase(fst_it);
        fill(value_type(leftResid,  fst_val));
        fill(value_type(interSec,   cmb_val));
        fill(value_type(rightResid, fst_val));
    }
    else
    {
        // first AND NOT last
        this->_map.erase(fst_it);
        fill(value_type(leftResid, fst_val));
        fill(value_type(interSec,  cmb_val));

        subtract_rest(x_itv, x_val, snd_it, end_it, combine);
    }
}



template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    template<template<class>class Combinator>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::subtract_rest(const interval_type& x_itv, const CodomainT& x_val, 
                    iterator& it, iterator& end_it, 
					const Combinator<CodomainT>& combine)
{
    //CL static Combinator<CodomainT> combine;
    iterator nxt_it=it; nxt_it++;

    while(nxt_it!=end_it)
    {
        CodomainT& cur_val = (*it).CONT_VALUE ;
        combine(cur_val, x_val);

        if(Traits::absorbs_neutrons && cur_val==CodomainT())
            this->_map.erase(it++); 
        else it++;

        nxt_it=it; nxt_it++;
    }

    // it refers the last overlaying intervals of x_itv
    const interval_type& cur_itv = (*it).KEY_VALUE ;

    interval_type rightResid; 
    cur_itv.right_surplus(rightResid, x_itv);

    if(rightResid.empty())
    {
        CodomainT& cur_val = (*it).CONT_VALUE ;
        combine(cur_val, x_val);
        if(Traits::absorbs_neutrons && cur_val==CodomainT())
            this->_map.erase(it);
    }
    else
    {
        CodomainT cur_val = (*it).CONT_VALUE ;
        CodomainT cmb_val = cur_val ;
        combine(cmb_val, x_val);
        interval_type interSec; 
        cur_itv.intersect(interSec, x_itv);

        this->_map.erase(it);
        fill(value_type(interSec, cmb_val));
        fill(value_type(rightResid, cur_val));
    }
}



//-----------------------------------------------------------------------------
// insert(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, 
          template<class>class Compare, template<class>class Alloc>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::insert_(const value_type& x)
{
    const interval_type& x_itv = x.KEY_VALUE;
    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==CodomainT()) 
        return;

    std::pair<typename ImplMapT::iterator,bool> 
        insertion = this->_map.insert(x);

    if(!insertion.WAS_SUCCESSFUL)
    {
        // Detect the first and the end iterator of the collision sequence
        iterator fst_it = this->_map.lower_bound(x_itv);
        iterator end_it = insertion.ITERATOR;
        if(end_it != this->_map.end())
            end_it++; 
        //assert(end_it == this->_map.upper_bound(x_itv));
        interval_type fst_itv = (*fst_it).KEY_VALUE ;

        interval_type leadGap; x_itv.left_surplus(leadGap, fst_itv);
        // this is a new Interval that is a gap in the current map
        fill_gap(value_type(leadGap, x_val), inplace_plus<CodomainT>());

        // only for the first there can be a leftResid: a part of *it left of x
        interval_type leftResid;  fst_itv.left_surplus(leftResid, x_itv);

        // handle special case for first

        interval_type interSec;
        fst_itv.intersect(interSec, x_itv);

        iterator snd_it = fst_it; snd_it++;
        if(snd_it == end_it) 
        {
            interval_type endGap; x_itv.right_surplus(endGap, fst_itv);
            // this is a new Interval that is a gap in the current map
            fill_gap(value_type(endGap, x_val), inplace_plus<CodomainT>());
        }
        else
        {
            // shrink interval
            interval_type x_rest(x_itv);
            x_rest.left_subtract(fst_itv);

            insert_rest(x_rest, x_val, snd_it, end_it);
        }
    }
}


template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, 
          template<class>class Compare, template<class>class Alloc>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::insert_rest(const interval_type& x_itv, const CodomainT& x_val, 
                  iterator& it, iterator& end_it)
{
    iterator nxt_it = it; nxt_it++;
    interval_type x_rest = x_itv, gap, common, cur_itv;

    for(; nxt_it!=end_it; ++it, ++nxt_it)
    {
        cur_itv = (*it).KEY_VALUE ;            
        x_rest.left_surplus(gap, cur_itv);
        fill_gap(value_type(gap, x_val), inplace_plus<CodomainT>());
        // shrink interval
        x_rest.left_subtract(cur_itv);
    }

    insert_rear(x_rest, x_val, it);
}

template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, 
          template<class>class Compare, template<class>class Alloc>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::insert_rear(const interval_type& x_rest, const CodomainT& x_val, 
                  iterator& it)
{
    interval_type cur_itv = (*it).KEY_VALUE ;

    interval_type left_gap;
    x_rest.left_surplus(left_gap, cur_itv);
    fill_gap(value_type(left_gap, x_val), inplace_plus<CodomainT>());

    interval_type common;
    cur_itv.intersect(common, x_rest);

    interval_type end_gap; 
    x_rest.right_surplus(end_gap, cur_itv);
    fill_gap(value_type(end_gap, x_val), inplace_plus<CodomainT>());
}


//-----------------------------------------------------------------------------
// erase(pair(interval,value)):
//-----------------------------------------------------------------------------
template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
    ::erase_(const value_type& x)
{
    const interval_type& x_itv = x.KEY_VALUE;
    if(x_itv.empty()) 
        return;

    const CodomainT& x_val = x.CONT_VALUE;
    if(Traits::absorbs_neutrons && x_val==CodomainT()) 
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
    fst_itv.left_surplus(leftResid, x_itv);

    // handle special case for first

    interval_type interSec;
    fst_itv.intersect(interSec, x_itv);

    iterator snd_it = fst_it; snd_it++;
    if(snd_it == end_it) 
    {
        // only for the last there can be a rightResid: a part of *it right of x
        interval_type rightResid;  (*fst_it).KEY_VALUE.right_surplus(rightResid, x_itv);

        if(!interSec.empty() && fst_val == x_val)
        {
            this->_map.erase(fst_it);
            fill(value_type(leftResid,  fst_val));
            // erased: fill(value_type(interSec,  cmb_val));
            fill(value_type(rightResid, fst_val));
        }
    }
    else
    {
        // first AND NOT last
        if(!interSec.empty() && fst_val == x_val)
        {
            this->_map.erase(fst_it);
            fill(value_type(leftResid, fst_val));
            // erased: fill(value_type(interSec,  cmb_val));
        }

        erase_rest(x_itv, x_val, snd_it, end_it);
    }
}


template <typename DomainT, typename CodomainT, class Traits, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void split_interval_map<DomainT,CodomainT,Traits,Interval,Compare,Alloc>
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
    cur_itv.right_surplus(rightResid, x_itv);

    if(rightResid.empty())
    {
        if(cur_val == x_val)
            this->_map.erase(it);
    }
    else
    {
        interval_type interSec; 
        cur_itv.intersect(interSec, x_itv);

        if(!interSec.empty() && cur_val == x_val)
        {
            this->_map.erase(it);
            //erased: fill(value_type(interSec, cmb_val));
            fill(value_type(rightResid, cur_val));
        }
    }
}


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------

template <class KeyT, class DataT, class Traits>
struct is_set<itl::split_interval_map<KeyT,DataT,Traits> >
{ enum{value = true}; };

template <class KeyT, class DataT, class Traits>
struct is_interval_container<itl::split_interval_map<KeyT,DataT,Traits> >
{ enum{value = true}; };

template <class KeyT, class DataT, class Traits>
struct is_interval_splitter<itl::split_interval_map<KeyT,DataT,Traits> >
{ enum{value = true}; };

template <class KeyT, class DataT, class Traits>
struct is_neutron_absorber<itl::split_interval_map<KeyT,DataT,Traits> >
{ enum{value = Traits::absorbs_neutrons}; };

template <class KeyT, class DataT, class Traits>
struct is_neutron_emitter<itl::split_interval_map<KeyT,DataT,Traits> >
{ enum{value = Traits::emits_neutrons}; };

template <class KeyT, class DataT, class Traits>
struct type_to_string<itl::split_interval_map<KeyT,DataT,Traits> >
{
    static std::string apply()
    { 
        return "sp_itv_map<"+ type_to_string<KeyT>::apply()  + ","
                            + type_to_string<DataT>::apply() + ","
                            + type_to_string<Traits>::apply() +">"; 
    }
};


}} // namespace itl boost

#endif


