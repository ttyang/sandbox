/*-----------------------------------------------------------------------------+
Copyright (c) 2012-2012: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL__INTERVAL_MAP_HPP_JOFA_120728
#define BOOST_ICL__INTERVAL_MAP_HPP_JOFA_120728

#include <boost/icl/impl_config.hpp>

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   include <boost/container/set.hpp>
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   include <set>
#else // Default for implementing containers
#   include <set>
#endif


#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/_interval_map_traits.hpp>
#include <boost/icl/concept/_interval_map.hpp>

namespace boost{namespace icl
{

/** \brief implements a map as a map of intervals - on insertion 
    overlapping intervals are split and associated values are combined.*/
template
<
    typename DomainT,
    typename CodomainT,
    class Traits = icl::partial_absorber, //JODO ImplType could also be coded within Traits to enable a short notation for std cases.
    ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_COMBINE Combine = ICL_COMBINE_INSTANCE(icl::inplace_plus, CodomainT),
    ICL_SECTION Section = ICL_SECTION_INSTANCE(icl::inter_section, CodomainT), 
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_IMPL_TYPE ImplT = ICL_IMPL_SPACE::map< DomainT, CodomainT >
>
class _interval_map
{
public:
    typedef Traits traits;
    typedef _interval_map type;
    typedef ImplT impl_type;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;

    typedef typename impl_type::iterator          interpair_iterator;
    typedef typename impl_type::const_iterator    interpair_const_iterator;
    typedef typename impl_type::value_type        value_type;
    typedef typename DomainT                      element_type;
    typedef typename DomainT                      domain_type;
    typedef typename CodomainT                    codomain_type;
    //JODO typedef typename impl_type::domain_mapping_type domain_mapping_type;
    //JODO typedef typename impl_type::interval_mapping_type interval_mapping_type;

    //JODO typedef typename impl_type::size_type         size_type;
    typedef typename Compare<DomainT>                   domain_compare;
    typedef typename Combine<CodomainT>                 codomain_combine;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    typedef std::pair<interval_type, codomain_type>     segment_type;

    enum { fineness = 1 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================

    /// Default constructor for the empty object
    _interval_map(): m_data() {}

    /// Copy constructor
    _interval_map(const _interval_map& src): m_data(src.m_data) {}

    /// Copy constructor for impl_type
    /*JODO
    template<class SubType>
    explicit _interval_map
        (const interval_base_map<SubType,DomainT,CodomainT,
                                 Traits,Compare,Combine,Section,Interval,Alloc>& src)
    { this->assign(src); }

    explicit _interval_map(domain_mapping_type& base_pair): impl_type()
    { this->add(base_pair); }

    explicit _interval_map(const value_type& value_pair): impl_type()
    { this->add(value_pair); }
    */


    /// Assignment operator
    _interval_map& operator = (const _interval_map& src)
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
        : impl_type(boost::move(src))
    {}

    /// Move assignment operator
    _interval_map& operator = (_interval_map&& src)
    { 
        impl_type::operator=(boost::move(src));
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
    impl_type m_data;
} ;

//==============================================================================
//=T _interval_map -> concept _interval_map 
//==============================================================================
template
<
    typename DomainT,
    typename CodomainT,
    class Traits,
    ICL_COMPARE Compare,
    ICL_COMBINE Combine,
    ICL_SECTION Section, 
    ICL_INTERVAL(ICL_COMPARE) Interval,
    ICL_IMPL_TYPE ImplT 
>
struct interval_map_traits
       < 
            _interval_map< DomainT, CodomainT, Traits
                         , Compare, Combine, Section
                         , Interval, ImplT >
       >
{
    typedef interval_map_traits                           type;
    typedef typename
            _interval_map< DomainT, CodomainT, Traits
                         , Compare, Combine, Section
                         , Interval, ImplT >              model_type;

    BOOST_STATIC_CONSTANT(bool, value = true);
    ICL_INTERVAL_MAP_TRAIT_TYPES(model_type);
    ICL_INTERVAL_MAP_TRAIT_FUNCTIONS(model_type);
};


}} // namespace icl boost

#endif


