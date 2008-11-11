/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
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
class itl::map
    a general map class that extends stl-maps
    for concepts InplaceAddable and InplaceSubtractable
--------------------------------------------------------------------*/
#ifndef __itl_map_h_JOFA_070519__
#define __itl_map_h_JOFA_070519__

#include <string>
#include <boost/itl/notate.hpp>
#include <boost/itl/type_traits/to_string.hpp>
#include <boost/itl/functors.hpp>
#include <boost/itl/predicates.hpp>
#include <boost/itl/set.hpp>
#include <boost/itl/map_algo.hpp>
#include <map>


namespace boost{namespace itl
{

    struct neutron_absorber
    {
        enum { absorbs_neutrons = true };
        enum { emits_neutrons = false };
    };

    template<> 
    inline std::string type_to_string<neutron_absorber>::apply() { return "@0"; }


    struct neutron_enricher
    {
        enum { absorbs_neutrons = false };
        enum { emits_neutrons = false };

    };

    template<> 
    inline std::string type_to_string<neutron_enricher>::apply() { return "e0"; }

    struct neutron_emitter
    {
        enum { absorbs_neutrons = true };
        enum { emits_neutrons = true };
    };

    template<> 
    inline std::string type_to_string<neutron_emitter>::apply() { return "^0"; }

    struct neutron_emitter_and_enricher
    {
        enum { absorbs_neutrons = false };
        enum { emits_neutrons = true };
    };

    template<> 
    inline std::string type_to_string<neutron_emitter_and_enricher>::apply() { return "e^0"; }


    /*JODO move this comment to concept InplaceAddable, InplaceSubtractable, InplaceCombinable

        Many features of the itl are based on the concept, that instances of
        template parameter are InplaceAddable(InplaceSubtractible). That is, 
        operators += and -= are implemented.
    */

    /// an stl based map implementing inplace addition and subtraction operators += and -=
    //JODO 1_0_1 documentation
    /** 

        @author Joachim Faulhaber
    */
    template 
    <
        typename KeyT, 
        typename DataT, 
        class Traits = itl::neutron_absorber,
        class Compare = std::less<KeyT>,
        template<class>class Alloc   = std::allocator 
    >
    class map: private std::map<KeyT, DataT, Compare, 
                                Alloc<std::pair<const KeyT, DataT> > >
    {
    public:
        typedef Alloc<typename std::pair<const KeyT, DataT> >  allocator_type;

        typedef typename itl::map<KeyT, DataT, Traits, Compare, Alloc> type;
        typedef typename std::map<KeyT, DataT, Compare, 
                                  allocator_type>            base_type;
        typedef typename itl::set<KeyT,Compare,Alloc>        set_type;

        typedef itl::map<KeyT, DataT, itl::neutron_absorber, Compare, Alloc> 
                                                               neutron_absorber_type;

        typedef Traits traits;

    public:
        typedef KeyT                                       key_type;
        typedef KeyT                                       domain_type;
        typedef DataT                                      mapped_type;
        typedef DataT                                      data_type;
        typedef DataT                                      codomain_type;
        typedef std::pair<const KeyT, DataT>               value_type;
        typedef Compare                              key_compare;
        typedef typename base_type::value_compare          value_compare;

    public:
        typedef typename base_type::pointer                pointer;
        typedef typename base_type::const_pointer          const_pointer;
        typedef typename base_type::reference              reference;
        typedef typename base_type::const_reference        const_reference;
        typedef typename base_type::iterator               iterator;
        typedef typename base_type::const_iterator         const_iterator;
        typedef typename base_type::size_type              size_type;
        typedef typename base_type::difference_type        difference_type;
        typedef typename base_type::reverse_iterator       reverse_iterator;
        typedef typename base_type::const_reverse_iterator const_reverse_iterator;
        
    public:
        map(){}
        map(const key_compare& comp): base_type(comp){}

        template <class InputIterator>
        map(InputIterator f, InputIterator l): base_type(f,l) {}

        template <class InputIterator>
        map(InputIterator f, InputIterator l, const key_compare& comp): base_type(f,l,comp) {}

        map(const map& src): base_type::map(src){}

        map& operator=(const map& src) { base_type::operator=(src); return *this; } 
        void swap(map& src) { base_type::swap(src); }

        using base_type::begin;
        using base_type::end;
        using base_type::rbegin;
        using base_type::rend;

        using base_type::size;
        using base_type::max_size;
        using base_type::empty;

        using base_type::key_comp;
        using base_type::value_comp;

        using base_type::insert;
        using base_type::erase;
        using base_type::clear;
        using base_type::find;
        using base_type::count;

        using base_type::lower_bound;
        using base_type::upper_bound;
        using base_type::equal_range;

        using base_type::operator[];

    public:
        inline static bool has_symmetric_difference() 
        { return itl::is_set<codomain_type>::value || !traits::absorbs_neutrons || traits::emits_neutrons; }

    public:
        // --------------------------------------------------------------------
        // itl specific extensions

        //JODO concept set
        /** Checks if a key element is in the map */
        bool contains(const KeyT& x)const { return !(find(x) == end()); }

        /** Is <tt>*this</tt> contained in <tt>super</tt>? */
        bool contained_in(const map& super)const 
        { return Map::contained_in(*this, super); }

        /** Does <tt>*this</tt> contain <tt>sub</tt>? */
        bool contains(const map& sub)const 
        { return Map::contained_in(sub, *this); }

        std::pair<iterator,bool> insert(const value_type& value_pair)
        {
            if(Traits::absorbs_neutrons && value_pair.CONT_VALUE == DataT()) 
                return std::pair<iterator,bool>(end(),true);
            else
                return base_type::insert(value_pair);
        }

        /** \c add inserts \c value_pair into the map if it's key does 
            not exist in the map.    
            If \c value_pairs's key value exists in the map, it's data
            value is added to the data value already found in the map. */
        iterator add(const value_type& value_pair) { return add<inplace_plus>(value_pair); }

        template<template<class>class Combinator>
        iterator add(const value_type& value_pair);

        iterator operator += (const value_type& value_pair) { return add(value_pair); }

        /** If the \c value_pair's key value is in the map, it's data value is
            subtraced from the data value stored in the map. */
        iterator subtract(const value_type& value_pair);

        /** Add a map \c x2 to this map. If an element of \c x2 already exists
            in \c *this, add up the contents using <tt>operator +=</tt>. */
        map& operator += (const map& x2) { Set::add(*this, x2); return *this; }

        /** Subtract a map \c x2 from this map. If an element of \c x2 already exists
            in \c *this, subtract the contents using <tt>operator -=</tt>. */
        map& operator -= (const map& x2) 
        { 
            if(Traits::emits_neutrons)
                const_FORALL(typename map, it_, x2)
                    this->add<inplace_minus>(*it_);
            else Set::subtract(*this, x2); 
            return *this; 
        }

        /** Subtract a set \c x2 from this map. Every element of \c this map that
            has a key that is element of \c x2 is deleted from the map. */
        map& operator -= (const set_type& x2) { Set::erase(*this, x2); return *this; }

        //JODO 
        /** erase the value pair \c pair(key,val) from the map.
            Erase only if, the exact value content \c val is stored at key \key. */
        size_type erase(const value_type& value);

        //JODO
        /** Intersect map \c x2 and \c *this.
            So \c *this becomes the intersection of \c *this and \c x2 */
        map& operator *= (const map& x2) 
        { Map::intersect(*this, x2); return *this; }

        /** Intersect set \c x2 and \c *this.
            So \c *this becomes the intersection of \c *this and \c x2 */
        map& operator *= (const set_type& x2) 
        { Map::intersect(*this, x2); return *this; }

        /** \c key_value allows for a uniform access to \c key_values which is
            is used for common algorithms on sets and maps. */
        template<typename IteratorT>
        static const key_type& key_value(IteratorT& value_)
        { return (*value_).first; }

        /** \c data_value allows for a uniform access to \c data_values which is
            is used for common algorithms on sets and maps. */
        template<typename IteratorT>
        static const data_type& data_value(IteratorT& value_){ return (*value_).second; }

        /** \c key_less allows for a uniform notation of key comparison which
            is used for common algorithms on sets and maps. */
        template<typename LeftIterT, typename RightIterT>
        static bool key_less(LeftIterT& lhs_, RightIterT& rhs_) 
        { return key_compare()((*lhs_).first,(*rhs_).first); }

        /** \c iterative_size() yields the number of elements that is visited
            throu complete iteration. For interval sets \c iterative_size() is
            different from \c size(). */
        static value_type make_element(const key_type& key_val, const data_type& data_val)
        { return value_type(key_val, data_val); }

        /** \c iterative_size() yields the number of elements that is visited
            throu complete iteration. For interval sets \c iterative_size() is
            different from \c size(). */
        size_t iterative_size()const { return size(); }

        void absorb_neutrons()
        {
            //content_is_neutron<key_type, data_type> neutron_dropper;
            if(!Traits::absorbs_neutrons)
                erase_if(content_is_neutron<value_type>());
        }

        /** Erase the elements in *this map to which property \c hasProperty applies. 
        Keep all the rest. */
        template<class Predicate>
        map& erase_if(const Predicate&);

        /** Copy the elements in map \c src to which property \c hasProperty applies 
        into \c *this map. */
        template<class Predicate>
        map& assign_if(const map& src, const Predicate&);

        /** Represent this map as string */
        std::string as_string()const;
    };


    /** Standard equality, which is lexicographical equality of the sets
        as sequences, that are given by their Compare order. */
    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    inline bool operator == (const itl::map<KeyT,DataT,Traits,Compare,Alloc>& lhs,
                             const itl::map<KeyT,DataT,Traits,Compare,Alloc>& rhs)
    {
        typedef std::map<KeyT,DataT,Compare,Alloc<KeyT> > base_type;
        return operator==((const base_type&)lhs, (const base_type&)rhs);
    }

    //JODO comment... 
    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    inline bool is_element_equal(const itl::map<KeyT,DataT,Traits,Compare,Alloc>& lhs,
                                 const itl::map<KeyT,DataT,Traits,Compare,Alloc>& rhs)
    {
        typedef std::map<KeyT,DataT,Compare,Alloc<KeyT> > base_type;
        return operator==((const base_type&)lhs, (const base_type&)rhs);
    }

    /** Protonic equality is equality on all elements that do not carry a neutron as content. */
    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    inline bool is_protonic_equal (const itl::map<KeyT,DataT,Traits,Compare,Alloc>& lhs,
                                   const itl::map<KeyT,DataT,Traits,Compare,Alloc>& rhs)
    {
        //JODO: Efficient implementation.
        typedef std::map<KeyT,DataT,Compare,Alloc<KeyT> > base_type;

        itl::map<KeyT,DataT,Traits,Compare,Alloc> lhs0 = lhs;
        itl::map<KeyT,DataT,Traits,Compare,Alloc> rhs0 = rhs;
        lhs0.absorb_neutrons();
        rhs0.absorb_neutrons();
        return operator==((const base_type&)lhs0, (const base_type&)rhs0);
    }

    /** Strict weak less ordering which is given by the Compare order */
    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    inline bool operator < (const itl::map<KeyT,DataT,Traits,Compare,Alloc>& lhs,
        const itl::map<KeyT,DataT,Traits,Compare,Alloc>& rhs)
    {
        typedef std::map<KeyT,DataT,Compare,Alloc<KeyT> > base_type;
        return operator<((const base_type&)lhs, (const base_type&)rhs);
    }

    /** Partial ordering which is induced by Compare */
    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    inline bool operator <= (const itl::map<KeyT,DataT,Traits,Compare,Alloc>& lhs,
        const itl::map<KeyT,DataT,Traits,Compare,Alloc>& rhs)
    {
        typedef std::map<KeyT,DataT,Compare,Alloc<KeyT> > base_type;
        return operator<=((const base_type&)lhs, (const base_type&)rhs);
    }

    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
        template <template<class>class Combinator>
    typename map<KeyT,DataT,Traits,Compare,Alloc>::iterator
        map<KeyT,DataT,Traits,Compare,Alloc>::add(const value_type& val)
    {
        if(Traits::absorbs_neutrons && val.CONT_VALUE == DataT())
            return end();

        std::pair<iterator, bool> insertion;
        if(Traits::emits_neutrons)
        {
            DataT added_val = DataT();
            Combinator<DataT>()(added_val, val.CONT_VALUE);
            insertion = insert(value_type(val.KEY_VALUE, added_val));
        }
        else // Existential case
            insertion = insert(val);

        if( insertion.WAS_SUCCESSFUL )
            return insertion.ITERATOR ;
        else
        {
            iterator it = insertion.ITERATOR;
            Combinator<DataT>()((*it).CONT_VALUE, val.CONT_VALUE);

            if(Traits::absorbs_neutrons && (*it).CONT_VALUE == DataT())
            {
                erase(it);
                return end();
            }
            else
                return it ;
        }
    }

    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    typename map<KeyT,DataT,Traits,Compare,Alloc>::size_type 
        map<KeyT,DataT,Traits,Compare,Alloc>
        ::erase(const value_type& value_pair)
    {
        if(Traits::absorbs_neutrons && value_pair.CONT_VALUE == DataT())
            return 0; // neutrons are never contained 'substantially' 
                      // only 'virually'.

        iterator it_ = find(value_pair.KEY_VALUE);
        if(it_ != end() && value_pair.CONT_VALUE == it_->CONT_VALUE)
        {
            erase(it_);
            return 1;
        }

        return 0;
    }


    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    typename map<KeyT,DataT,Traits,Compare,Alloc>::iterator
        map<KeyT,DataT,Traits,Compare,Alloc>::subtract(const value_type& val)
    {
        if(Traits::emits_neutrons)
            return add<inplace_minus>(val);
        else
        {
            iterator it_ = find(val.KEY_VALUE);
            if(it_ != end())
            {
                (*it_).CONT_VALUE -= val.CONT_VALUE;

                if(Traits::absorbs_neutrons && (*it_).CONT_VALUE == DataT())
                {
                    erase(it_);
                    return end();
                }
                else
                    return it_;
            }
            return it_;
        }
    }


    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
    std::string map<KeyT,DataT,Traits,Compare,Alloc>::as_string()const
    { 
        std::string repr;
        const_FORALL_THIS(it) {
            std::string elem("(");
            elem += to_string<KeyT>::apply((*it).KEY_VALUE);
            elem += "->";
            elem += to_string<DataT>::apply((*it).CONT_VALUE);
            elem += ")";

            repr += elem;
        }
        return repr;
    }

    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
        template<class Predicate>
    map<KeyT,DataT,Traits,Compare,Alloc>& map<KeyT,DataT,Traits,Compare,Alloc>
        ::erase_if(const Predicate& pred)
    {
        iterator it = begin();
        while(it != end())
            if(pred(*it))
                erase(it++); 
            else ++it;
        return *this;
    }


    template <typename KeyT, typename DataT, class Traits, class Compare, template<class>class Alloc>
        template<class Predicate>
    map<KeyT,DataT,Traits,Compare,Alloc>& map<KeyT,DataT,Traits,Compare,Alloc>
        ::assign_if(const map<KeyT,DataT,Traits,Compare,Alloc>& src, const Predicate& pred)
    {
        clear();
        const_iterator it = src.begin();
        while(it != src.end()) {
            if(pred(*it)) 
                add(*it++); 
        }
        return *this;
    }
    //-------------------------------------------------------------------------
    template <typename KeyT, typename DataT, class Traits, 
              class Compare, template<class>class Alloc>
    map<KeyT,DataT,Traits,Compare,Alloc>& 
        insert(map<KeyT,DataT,Traits,Compare,Alloc>& object, 
               const map<KeyT,DataT,Traits,Compare,Alloc>& insertee) 
    {
        typedef map<KeyT,DataT,Traits,Compare,Alloc> map_type;

        const_FORALL(typename map_type, elem_, insertee) 
            object.insert(*elem_); 

        return object; 
    }

    template <typename KeyT, typename DataT, class Traits, 
              class Compare, template<class>class Alloc>
    map<KeyT,DataT,Traits,Compare,Alloc>& 
        erase(map<KeyT,DataT,Traits,Compare,Alloc>& object, 
              const map<KeyT,DataT,Traits,Compare,Alloc>& erasee) 
    {
        typedef map<KeyT,DataT,Traits,Compare,Alloc> map_type;

        const_FORALL(typename map_type, elem_, erasee) 
            object.erase(*elem_); 

        return object; 
    }

    //-------------------------------------------------------------------------
    template <class KeyT, class DataT, class Traits>
    struct is_interval_container<itl::map<KeyT,DataT,Traits> >
    { enum{value = true}; };

    template <class KeyT, class DataT, class Traits>
    struct is_interval_splitter<itl::map<KeyT,DataT,Traits> >
    { enum{value = false}; };

    template <class KeyT, class DataT, class Traits>
    struct is_neutron_absorber<itl::map<KeyT,DataT,Traits> >
    { enum{value = Traits::absorbs_neutrons}; };

    template <class KeyT, class DataT, class Traits>
    struct is_neutron_emitter<itl::map<KeyT,DataT,Traits> >
    { enum{value = Traits::emits_neutrons}; };

    template <class KeyT, class DataT, class Traits>
    struct type_to_string<itl::map<KeyT,DataT,Traits> >
    {
        static std::string apply()
        {
            return "map<"+ type_to_string<KeyT>::apply()  + ","
                         + type_to_string<DataT>::apply() + ","
                         + type_to_string<Traits>::apply() +">"; 
        }
    };


}} // namespace itl boost

#endif // __itl_map_h_JOFA_070519__

