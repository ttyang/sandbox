/*-----------------------------------------------------------------------------+    
Copyright (c) 2012-2012: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT__INTERVAL_MAP_TRAITS_HPP_JOFA_120728
#define BOOST_ICL_CONCEPT__INTERVAL_MAP_TRAITS_HPP_JOFA_120728

#include <iterator>
#include <map>
#include <boost/icl/functors.hpp>
#include <boost/icl/_interval_map_traits.hpp>

namespace boost{ namespace icl
{

template<class Model>
struct interval_map_traits
{
    typedef interval_map_traits                          type;
    typedef interval_map_traits                          concept_mapping;
    typedef Model                                        model_type;
    typedef typename model_type::key_type                domain_type;
    typedef typename model_type::value_type::second_type codomain_type;
    typedef typename model_type::key_compare             domain_compare; 
    typedef typename model_type::codomain_combine        codomain_combine; 
    typedef typename model_type::interpair_type          interpair_type;
    typedef typename model_type::iterator                interpair_iterator; 
    typedef typename model_type::const_iterator          interpair_const_iterator; 

    BOOST_STATIC_CONSTANT(bool, value = false);

//conceptual private:
    static       interpair_iterator interpairs_begin (model_type&);
    static       interpair_iterator interpairs_end   (model_type&);
    static interpair_const_iterator interpairs_cbegin(const model_type&);
    static interpair_const_iterator interpairs_cend  (const model_type&);

    static       interpair_iterator insert(model_type&, interpair_iterator, const interpair_type&);
};

}} // namespace boost icl

//#define ICL_REFINED_TYPE(base, type_name) typedef typename base::type_name type_name ; 

#define ICL_INTERVAL_MAP_TRAIT_TYPES(base_type)\
    typedef typename base_type::domain_type              domain_type;\
    typedef typename base_type::codomain_type            codomain_type;\
    typedef typename base_type::domain_compare           domain_compare;\
    typedef typename base_type::codomain_combine         codomain_combine;\
    typedef typename base_type::value_type               interpair_type;\
    typedef typename base_type::interpair_iterator       interpair_iterator;\
    typedef typename base_type::interpair_const_iterator interpair_const_iterator;

#define ICL_INTERVAL_MAP_TRAIT_FUNCTIONS(model_type)\
    static       interpair_iterator interpairs_begin (model_type& model)      { return model.begin(); };\
    static       interpair_iterator interpairs_end   (model_type& model)      { return model.end();   };\
    static interpair_const_iterator interpairs_cbegin(const model_type& model){ return model.begin(); };\
    static interpair_const_iterator interpairs_cend  (const model_type& model){ return model.end();   };\
    static interpair_iterator insert(model_type& model, interpair_iterator position, const interpair_type& value)\
    { return model.insert(position, value); }

#endif //BOOST_ICL_CONCEPT__INTERVAL_MAP_TRAITS_HPP_JOFA_120728


