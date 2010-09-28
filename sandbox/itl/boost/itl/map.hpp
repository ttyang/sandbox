/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_MAP_HPP_JOFA_070519
#define BOOST_ITL_MAP_HPP_JOFA_070519

#include <boost/itl/impl_config.hpp>

#if defined(ITL_USE_BOOST_INTERPROCESS_IMPLEMENTATION)
#include <boost/interprocess/containers/map.hpp>
#elif defined(ITL_USE_BOOST_MOVE_IMPLEMENTATION)
#include <boost/container/map.hpp>
#else 
#include <map>
#endif

#include <string>
#include <boost/type_traits/ice.hpp>
#include <boost/call_traits.hpp> 
#include <boost/itl/detail/notate.hpp>
#include <boost/itl/detail/design_config.hpp>
#include <boost/itl/detail/concept_check.hpp>
#include <boost/itl/detail/on_absorbtion.hpp>
#include <boost/itl/type_traits/is_map.hpp>
#include <boost/itl/type_traits/absorbs_neutrons.hpp>
#include <boost/itl/type_traits/is_total.hpp>
#include <boost/itl/type_traits/is_element_container.hpp>
#include <boost/itl/type_traits/has_inverse.hpp>
#include <boost/itl/type_traits/to_string.hpp>
#include <boost/itl/functors.hpp>
#include <boost/itl/predicates.hpp>
#include <boost/itl/set.hpp>

#include <boost/itl/detail/map_algo.hpp>
#include <boost/itl/concept/container.hpp>
#include <boost/itl/concept/element_map.hpp>
#include <boost/itl/concept/element_associator.hpp>

namespace boost{namespace itl
{

struct partial_absorber
{
    enum { absorbs_neutrons = true };
    enum { is_total = false };
};

template<> 
inline std::string type_to_string<partial_absorber>::apply() { return "@0"; }


struct partial_enricher
{
    enum { absorbs_neutrons = false };
    enum { is_total = false };

};

template<> 
inline std::string type_to_string<partial_enricher>::apply() { return "e0"; }

struct total_absorber
{
    enum { absorbs_neutrons = true };
    enum { is_total = true };
};

template<> 
inline std::string type_to_string<total_absorber>::apply() { return "^0"; }

struct total_enricher
{
    enum { absorbs_neutrons = false };
    enum { is_total = true };
};

template<> 
inline std::string type_to_string<total_enricher>::apply() { return "e^0"; }



/** \brief Addable, subractable and intersectable maps */
template 
<
    typename DomainT, 
    typename CodomainT, 
    class Traits = itl::partial_absorber,
    ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, DomainT),
    ITL_COMBINE Combine = ITL_COMBINE_INSTANCE(itl::inplace_plus, CodomainT),
    ITL_SECTION Section = ITL_SECTION_INSTANCE(itl::inter_section, CodomainT), 
    ITL_ALLOC   Alloc   = std::allocator 
>
class map: private ITL_IMPL_SPACE::map<DomainT, CodomainT, ITL_COMPARE_DOMAIN(Compare,DomainT), 
                                       Alloc<std::pair<const DomainT, CodomainT> > >
{
public:
    typedef Alloc<typename std::pair<const DomainT, CodomainT> >  allocator_type;

    typedef typename itl::map<DomainT,CodomainT,Traits, Compare,Combine,Section,Alloc> type;
    typedef typename ITL_IMPL_SPACE::map<DomainT, CodomainT, ITL_COMPARE_DOMAIN(Compare,DomainT),
                                         allocator_type>   base_type;
    typedef typename itl::set<DomainT, Compare, Alloc >    set_type;
    typedef set_type                                       key_object_type;

    typedef Traits traits;

public:
    typedef DomainT                                     domain_type;
    typedef typename boost::call_traits<DomainT>::param_type domain_param;
    typedef DomainT                                     key_type;
    typedef CodomainT                                   codomain_type;
    typedef CodomainT                                   mapped_type;
    typedef CodomainT                                   data_type;
    typedef std::pair<const DomainT, CodomainT>         element_type;
    typedef std::pair<const DomainT, CodomainT>         value_type;
    typedef ITL_COMPARE_DOMAIN(Compare,DomainT)         domain_compare;
    typedef ITL_COMBINE_CODOMAIN(Combine,CodomainT)     codomain_combine;
    typedef domain_compare                              key_compare;
    typedef ITL_COMPARE_DOMAIN(Compare,element_type)    element_compare;
    typedef typename inverse<codomain_combine >::type   inverse_codomain_combine;
    typedef typename mpl::if_
        <has_set_semantics<codomain_type>
        , ITL_SECTION_CODOMAIN(Section,CodomainT)     
        , codomain_combine
        >::type                                         codomain_intersect;
    typedef typename inverse<codomain_intersect>::type  inverse_codomain_intersect;
    typedef typename base_type::value_compare           value_compare;

    BOOST_STATIC_CONSTANT(bool, _total   = (Traits::is_total));
    BOOST_STATIC_CONSTANT(bool, _absorbs = (Traits::absorbs_neutrons));
    BOOST_STATIC_CONSTANT(bool, 
        total_invertible = (mpl::and_<is_total<type>, has_inverse<codomain_type> >::value));

    typedef on_absorbtion<type,codomain_combine,Traits::absorbs_neutrons> 
                                                        on_neutron_absorbtion;

public:
    typedef typename base_type::pointer                 pointer;
    typedef typename base_type::const_pointer           const_pointer;
    typedef typename base_type::reference               reference;
    typedef typename base_type::const_reference         const_reference;
    typedef typename base_type::iterator                iterator;
    typedef typename base_type::const_iterator          const_iterator;
    typedef typename base_type::size_type               size_type;
    typedef typename base_type::difference_type         difference_type;
    typedef typename base_type::reverse_iterator        reverse_iterator;
    typedef typename base_type::const_reverse_iterator  const_reverse_iterator;

public:
    BOOST_STATIC_CONSTANT(bool, 
        is_total_invertible = (   Traits::is_total 
                               && has_inverse<codomain_type>::value));

    BOOST_STATIC_CONSTANT(int, fineness = 4); 

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    map()
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    map(const key_compare& comp): base_type(comp){}

    template <class InputIterator>
    map(InputIterator first, InputIterator past)
        : base_type(first,past){} 

    template <class InputIterator>
    map(InputIterator first, InputIterator past, const key_compare& comp)
        : base_type(first,past,comp) 
    {}

    map(const map& src): base_type::map(src)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    explicit map(const element_type& key_value_pair): base_type::map()
    { 
        insert(key_value_pair); 
    }

    map& operator=(const map& src) { base_type::operator=(src); return *this; } 
    void swap(map& src) { base_type::swap(src); }

    //==========================================================================
    using base_type::empty;
    using base_type::clear;

    using base_type::begin;
    using base_type::end;
    using base_type::rbegin;
    using base_type::rend;

    using base_type::size;
    using base_type::max_size;

    using base_type::key_comp;
    using base_type::value_comp;

    using base_type::insert;
    using base_type::erase;
    using base_type::find;
    using base_type::count;

    using base_type::lower_bound;
    using base_type::upper_bound;
    using base_type::equal_range;

    using base_type::operator[];

public:
    //==========================================================================
    //= Containedness
    //==========================================================================

    template<class SubObject>
    bool contains(const SubObject& sub)const 
    { return itl::contains(*this, sub); }

    bool within(const map& super)const 
    { return itl::contains(super, *this); }

    //==========================================================================
    //= Size
    //==========================================================================
    /** \c iterative_size() yields the number of elements that is visited
        throu complete iteration. For interval sets \c iterative_size() is
        different from \c size(). */
    std::size_t iterative_size()const { return base_type::size(); }

    //==========================================================================
    //= Selection
    //==========================================================================

    /** Total select function. */
    codomain_type operator()(const domain_type& key)const
    {
        const_iterator it = find(key); 
        return it==end() ? neutron<codomain_type>::value()
                         : it->second;
    }

    //==========================================================================
    //= Addition
    //==========================================================================
    /** \c add inserts \c value_pair into the map if it's key does 
        not exist in the map.    
        If \c value_pairs's key value exists in the map, it's data
        value is added to the data value already found in the map. */
    map& add(const value_type& value_pair) 
    { 
        return _add<codomain_combine>(value_pair); 
    }

    /** \c add add \c value_pair into the map using \c prior as a hint to
        insert \c value_pair after the position \c prior is pointing to. */
    iterator add(iterator prior, const value_type& value_pair) 
    { 
        return _add<codomain_combine>(prior, value_pair); 
    }

    //==========================================================================
    //= Subtraction
    //==========================================================================
    /** If the \c value_pair's key value is in the map, it's data value is
        subtraced from the data value stored in the map. */
    map& subtract(const element_type& value_pair)
    {
        on_invertible<type, is_total_invertible>
            ::subtract(*this, value_pair);
        return *this;
    }

    map& subtract(const domain_type& key)
    {
        itl::erase(*this, key);
        return *this;
    }

    //==========================================================================
    //= Insertion, erasure
    //==========================================================================
    std::pair<iterator,bool> insert(const value_type& value_pair)
    {
        if(on_neutron_absorbtion::is_absorbable(value_pair.second)) 
            return std::pair<iterator,bool>(end(),true);
        else
            return base_type::insert(value_pair);
    }
    
    iterator insert(iterator prior, const value_type& value_pair)
    {
        if(on_neutron_absorbtion::is_absorbable(value_pair.second)) 
            return end();
        else
            return base_type::insert(prior, value_pair);
    }

    /** With <tt>key_value_pair = (k,v)</tt> set value \c v for key \c k */
    map& set(const element_type& key_value_pair)
    { 
        return itl::set_at(*this, key_value_pair);
    }

    /** erase \c key_value_pair from the map.
        Erase only if, the exact value content \c val is stored for the given key. */
    size_type erase(const element_type& key_value_pair)
    {
        return itl::erase(*this, key_value_pair); 
    }

    //==========================================================================
    //= Intersection
    //==========================================================================
    /** The intersection of \c key_value_pair and \c *this map is added to \c section. */
    void add_intersection(map& section, const element_type& key_value_pair)const
    {
        on_definedness<type, Traits::is_total>
            ::add_intersection(section, *this, key_value_pair);
    }

    /** Returns true, if there is an intersection of \c operand and \c *this map. */
    //CL template<class OperandT>
    //bool intersects(const OperandT& operand)const
    //{
    //    return itl::intersects(*this, operand);
    //}

    //==========================================================================
    //= Symmetric difference
    //==========================================================================

    map& flip(const element_type& operand)
    {
        on_total_absorbable<type,_total,_absorbs>::flip(*this, operand);
        return *this;
    }

private:
    template<class Combiner>
    map& _add(const element_type& value_pair);

    template<class Combiner>
    iterator _add(iterator prior, const element_type& value_pair);

    template<class Combiner>
    map& _subtract(const element_type& value_pair);

    template<class FragmentT>
    void total_add_intersection(type& section, const FragmentT& fragment)const
    {
        section += *this;
        section.add(fragment);
    }

    void partial_add_intersection(type& section, const element_type& operand)const
    {
        const_iterator it_ = find(operand.first);
        if(it_ != end())
        {
            section.template _add<codomain_combine  >(*it_);
            section.template _add<codomain_intersect>(operand); 
        }
    }


private:
    //--------------------------------------------------------------------------
    template<class Type, bool is_total_invertible>
    struct on_invertible;

    template<class Type>
    struct on_invertible<Type, true>
    {
        typedef typename Type::element_type element_type;
        typedef typename Type::inverse_codomain_combine inverse_codomain_combine;

        static void subtract(Type& object, const element_type& operand)
        { object.template _add<inverse_codomain_combine>(operand); }
    };

    template<class Type>
    struct on_invertible<Type, false>
    {
        typedef typename Type::element_type element_type;
        typedef typename Type::inverse_codomain_combine inverse_codomain_combine;

        static void subtract(Type& object, const element_type& operand)
        { object.template _subtract<inverse_codomain_combine>(operand); }
    };

    friend struct on_invertible<type, true>;
    friend struct on_invertible<type, false>;
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    template<class Type, bool is_total>
    struct on_definedness;

    template<class Type>
    struct on_definedness<Type, true>
    {
        static void add_intersection(Type& section, const Type& object, 
                                     const element_type& operand)
        { object.total_add_intersection(section, operand); }
    };

    template<class Type>
    struct on_definedness<Type, false>
    {
        static void add_intersection(Type& section, const Type& object, 
                                     const element_type& operand)
        { object.partial_add_intersection(section, operand); }
    };

    friend struct on_definedness<type, true>;
    friend struct on_definedness<type, false>;
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    template<class Type, bool has_set_semantics, bool absorbs_neutrons>
    struct on_codomain_model;

    template<class Type>
    struct on_codomain_model<Type, false, false>
    {                // !codomain_is_set, !absorbs_neutrons
        static void subtract(Type& object, typename Type::iterator       it_, 
                                     const typename Type::codomain_type&     )
        { it_->second = neutron<typename Type::codomain_type>::value(); }
    };

    template<class Type>
    struct on_codomain_model<Type, false, true>
    {                // !codomain_is_set, absorbs_neutrons
        static void subtract(Type& object, typename Type::iterator       it_, 
                                     const typename Type::codomain_type&     )
        { object.erase(it_); }
    };

    template<class Type>
    struct on_codomain_model<Type, true, false>
    {                // !codomain_is_set, !absorbs_neutrons
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;
        static void subtract(Type& object, typename Type::iterator       it_, 
                                     const typename Type::codomain_type& co_value)
        { 
            inverse_codomain_intersect()(it_->second, co_value); 
        }
    };

    template<class Type>
    struct on_codomain_model<Type, true, true>
    {                // !codomain_is_set, absorbs_neutrons
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;
        static void subtract(Type& object, typename Type::iterator       it_, 
                                     const typename Type::codomain_type& co_value)
        { 
            inverse_codomain_intersect()(it_->second, co_value); 
            if(it_->second == neutron<codomain_type>::value())
                object.erase(it_);
        }
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    template<class Type, bool is_total, bool absorbs_neutrons>
    struct on_total_absorbable;

    template<class Type>
    struct on_total_absorbable<Type, true, true>
    {
        typedef typename Type::element_type  element_type;
        static void flip(Type& object, const typename Type::element_type&)
        { itl::clear(object); }
    };

    template<class Type>
    struct on_total_absorbable<Type, true, false>
    {
        typedef typename Type::element_type  element_type;
        typedef typename Type::codomain_type codomain_type;

        static void flip(Type& object, const element_type& operand)
        { 
            object.add(operand);
            ITL_FORALL(typename Type, it_, object)
                it_->second = neutron<codomain_type>::value();
        }
    };

    template<class Type>
    struct on_total_absorbable<Type, false, true>
    {                         // !is_total, absorbs_neutrons
        typedef typename Type::element_type   element_type;
        typedef typename Type::codomain_type  codomain_type;
        typedef typename Type::iterator       iterator;
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;

        static void flip(Type& object, const element_type& operand)
        {
            std::pair<iterator,bool> insertion = object.insert(operand);
            if(!insertion.second)
                on_codomain_model<Type, has_set_semantics<codomain_type>::value, true>
                ::subtract(object, insertion.first, operand.second);
        }
    };

    template<class Type>
    struct on_total_absorbable<Type, false, false>
    {                         // !is_total  !absorbs_neutrons
        typedef typename Type::element_type   element_type;
        typedef typename Type::codomain_type  codomain_type;
        typedef typename Type::iterator       iterator;
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;

        static void flip(Type& object, const element_type& operand)
        {
            std::pair<iterator,bool> insertion = object.insert(operand);
            if(!insertion.second)
                on_codomain_model<Type, has_set_semantics<codomain_type>::value, false>
                ::subtract(object, insertion.first, operand.second);
        }
    };

    friend struct on_total_absorbable<type, true,  true >;
    friend struct on_total_absorbable<type, false, true >;
    friend struct on_total_absorbable<type, true,  false>;
    friend struct on_total_absorbable<type, false, false>;
    //--------------------------------------------------------------------------
};



//==============================================================================
//= Addition<ElementMap>
//==============================================================================
template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
    template <class Combiner>
map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>&
    map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>
    ::_add(const element_type& addend)
{
    typedef typename on_absorbtion
        <type,Combiner,absorbs_neutrons<type>::value>::type on_absorbtion_;

    const codomain_type& co_val    = addend.second;
    if(on_absorbtion_::is_absorbable(co_val))
        return *this;

    std::pair<iterator,bool> insertion 
        = base_type::insert(value_type(addend.first, version<Combiner>()(co_val)));

    if(!insertion.second)
    {
        iterator it = insertion.first;
        Combiner()((*it).second, co_val);

        if(on_absorbtion_::is_absorbable((*it).second))
            erase(it);
    }
    return *this;
}


template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
    template <class Combiner>
typename map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>::iterator
    map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>
    ::_add(iterator prior_, const value_type& addend)
{
    typedef typename on_absorbtion
        <type,Combiner,absorbs_neutrons<type>::value>::type on_absorbtion_;

    const codomain_type& co_val    = addend.second;
    if(on_absorbtion_::is_absorbable(co_val))
        return end();

    iterator inserted_ 
        = base_type::insert(prior_, 
                            value_type(addend.first, Combiner::neutron()));
    Combiner()(inserted_->second, addend.second);

    if(on_absorbtion_::is_absorbable(inserted_->second))
    {
        erase(inserted_);
        return end();
    }
    else
        return inserted_;
}


//==============================================================================
//= Subtraction<ElementMap>
//==============================================================================
template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
    template <class Combiner>
map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>&
    map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>::_subtract(const value_type& minuend)
{
    typedef typename on_absorbtion
        <type,Combiner,absorbs_neutrons<type>::value>::type on_absorbtion_;

    iterator it_ = find(minuend.first);
    if(it_ != end())
    {
        Combiner()(it_->second, minuend.second);
        if(on_absorbtion_::is_absorbable(it_->second))
            erase(it_);
    }
    return *this;
}


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
struct is_map<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{ 
    typedef is_map<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
struct has_inverse<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{ 
    typedef has_inverse<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (has_inverse<CodomainT>::value)); 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
struct absorbs_neutrons<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{ 
    typedef absorbs_neutrons type;
    BOOST_STATIC_CONSTANT(int, value = Traits::absorbs_neutrons); 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
struct is_total<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{ 
    typedef is_total type;
    BOOST_STATIC_CONSTANT(int, value = Traits::is_total); 
};

template <class DomainT, class CodomainT, class Traits, ITL_COMPARE Compare, ITL_COMBINE Combine, ITL_SECTION Section, ITL_ALLOC Alloc>
struct type_to_string<itl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{
    static std::string apply()
    {
        return "map<"+ type_to_string<DomainT>::apply()  + ","
                     + type_to_string<CodomainT>::apply() + ","
                     + type_to_string<Traits>::apply() +">"; 
    }
};



}} // namespace itl boost

#endif // BOOST_ITL_MAP_HPP_JOFA_070519

