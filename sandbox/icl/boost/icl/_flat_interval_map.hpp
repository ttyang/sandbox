/*-----------------------------------------------------------------------------+
Copyright (c) 2012-2012: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL__FLAT_INTERVAL_MAP_HPP_JOFA_120729
#define BOOST_ICL__FLAT_INTERVAL_MAP_HPP_JOFA_120729

#include <boost/icl/impl_config.hpp>

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   include <boost/container/vector.hpp>
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   include <vector>
#else // Default for implementing containers
#   include <vector>
#endif


#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/_interval_map_traits.hpp>
#include <boost/icl/concept/_interval_map.hpp>

namespace boost{namespace icl
{

/**JODO \brief implements a map as a map of intervals - on insertion 
    overlapping intervals are split and associated values are combined.*/
template
<
    typename DomainT,
    typename CodomainT,
    class Traits = icl::partial_absorber, //JODO ImplType could also be coded within Traits to enable a short notation for std cases.
    ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_COMBINE Combine = ICL_COMBINE_INSTANCE(icl::inplace_plus, CodomainT),
    ICL_SECTION Section = ICL_SECTION_INSTANCE(icl::inter_section, CodomainT), 
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare)
>
class flat_interval_map //JODO private inheritace and using?
{
public:
    typedef ICL_IMPL_SPACE::vector< std::pair<DomainT, CodomainT> > impl_type;
    typedef _interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,impl_type> base_type;
    typedef flat_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval> type;

    typedef typename base_type::interpair_iterator       interpair_iterator;
    typedef typename base_type::interpair_const_iterator interpair_const_iterator;
    typedef typename base_type::value_type               value_type;
    typedef typename DomainT                             element_type;
    //JODO typedef typename base_type::segment_type      segment_type;
    typedef typename DomainT                             domain_type;
    typedef typename base_type::value_type::second_type  codomain_type;
    //JODO typedef typename base_type::domain_mapping_type domain_mapping_type;
    //JODO typedef typename base_type::interval_mapping_type interval_mapping_type;

    //JODO typedef typename base_type::size_type         size_type;
    typedef typename Compare<DomainT>             domain_compare;
    typedef typename Combine<CodomainT>           codomain_combine;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    typedef std::pair<interval_type, interval_type>     segment_type;

    enum { fineness = 1 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================

    /// Default constructor for the empty object
    flat_interval_map(): m_data() {}

    /// Copy constructor
    flat_interval_map(const flat_interval_map& src): m_data(src.m_data) {}

    /// Copy constructor for base_type
    /*JODO
    template<class SubType>
    explicit _interval_map
        (const interval_base_map<SubType,DomainT,CodomainT,
                                 Traits,Compare,Combine,Section,Interval,Alloc>& src)
    { this->assign(src); }

    explicit _interval_map(domain_mapping_type& base_pair): base_type()
    { this->add(base_pair); }

    explicit _interval_map(const value_type& value_pair): base_type()
    { this->add(value_pair); }
    */


    /// Assignment operator
    flat_interval_map& operator = (const flat_interval_map& src)
    { 
        m_data = src.m_data; 
        return *this; 
    }

    /*JODO
    /// Assignment from a base _interval_map.
    template<class SubType>
    void assign(const interval_base_map<SubType,DomainT,CodomainT,
                                        Traits,Compare,Combine,Section,Interval,Alloc>& src)
    {
        typedef interval_base_map<SubType,DomainT,CodomainT,
                                  Traits,Compare,Combine,Section,Interval,Alloc> base_map_type;
        this->clear();
        iterator prior_ = this->_map.end();
        ICL_const_FORALL(typename base_map_type, it_, src) 
            prior_ = this->add(prior_, *it_); 
    }

#   ifndef BOOST_NO_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    /// Move constructor
    _interval_map(_interval_map&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    _interval_map& operator = (_interval_map&& src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }

    //==========================================================================
#   endif // BOOST_NO_RVALUE_REFERENCES
    */

    interpair_iterator begin(){ return m_data.begin(); }
    interpair_iterator end()  { return m_data.end(); }
    interpair_const_iterator begin()const{ return m_data.begin(); }
    interpair_const_iterator end()const  { return m_data.end(); }

    //JODO insert -> into the traits. what about reserving memory for vectors?
    interpair_iterator insert(interpair_const_iterator pos, const value_type& value)
    { return m_data.insert(pos, value); }

    //JODO This is temporary for testing.
    std::pair<interpair_iterator,bool> insert(const value_type& value)
    { return m_data.insert(value); }

private:
    base_type m_data;
} ;

//==============================================================================
//=T flat_interval_map -> concept _interval_map 
//==============================================================================
template
<
    typename DomainT,
    typename CodomainT,
    class Traits,
    ICL_COMPARE Compare,
    ICL_COMBINE Combine,
    ICL_SECTION Section, 
    ICL_INTERVAL(ICL_COMPARE) Interval
>
struct interval_map_traits
       < 
            flat_interval_map< DomainT, CodomainT, Traits
                             , Compare, Combine, Section
                             , Interval >
       >
{
    typedef interval_map_traits                           type;
    typedef typename
        flat_interval_map< DomainT, CodomainT, Traits
                         , Compare, Combine, Section
                         , Interval >                     model_type;

    typedef ICL_IMPL_SPACE::vector< std::pair<DomainT, CodomainT> > impl_type;
    typedef typename
            _interval_map< DomainT, CodomainT, Traits
                         , Compare, Combine, Section
                         , Interval, impl_type >         base_type;

    BOOST_STATIC_CONSTANT(bool, value = true);
    ICL_INTERVAL_MAP_TRAIT_TYPES(base_type);
    ICL_INTERVAL_MAP_TRAIT_FUNCTIONS(model_type);
};


}} // namespace icl boost

#endif


