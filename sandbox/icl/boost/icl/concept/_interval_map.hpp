/*-----------------------------------------------------------------------------+    
Copyright (c) 2012-2012: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT__INTERVAL_ASSOCIATOR_HPP_JOFA_120724
#define BOOST_ICL_CONCEPT__INTERVAL_ASSOCIATOR_HPP_JOFA_120724

#include <iterator>
#include <map>
#include <boost/icl/functors.hpp>

namespace boost{ namespace icl
{

template<class Model>
struct interval_map_concept
{
    typedef interval_map_concept                         type;
    typedef Model                                        model_type;
    typedef typename model_type::key_type                domain_type;
    typedef typename model_type::value_type::second_type codomain_type;
    typedef typename model_type::key_compare             domain_compare; 
    typedef typename model_type::iterator                interpair_iterator; 
    typedef typename model_type::const_iterator          interpair_const_iterator; 

    static       interpair_iterator interpairs_begin (model_type&);
    static       interpair_iterator interpairs_end   (model_type&);
    static interpair_const_iterator interpairs_cbegin(const model_type&);
    static interpair_const_iterator interpairs_cend  (const model_type&);
};

template<class DomainT, class CodomainT>
struct interval_map_concept/*modeled by*/< std::map<DomainT, CodomainT> >
{
    typedef interval_map_concept                         type;
    typedef typename std::map<DomainT, CodomainT>        model_type;

    typedef typename model_type::key_type                domain_type;
    typedef typename model_type::value_type::second_type codomain_type;
    typedef typename model_type::key_compare             domain_compare; 
    typedef typename inplace_plus<codomain_type>         codomain_combine;
    typedef typename model_type::iterator                interpair_iterator; 
    typedef typename model_type::const_iterator          interpair_const_iterator; 

    static       interpair_iterator interpairs_begin (model_type& model)      { return model.begin(); };
    static       interpair_iterator interpairs_end   (model_type& model)      { return model.end();   };
    static interpair_const_iterator interpairs_cbegin(const model_type& model){ return model.begin(); };
    static interpair_const_iterator interpairs_cend  (const model_type& model){ return model.end();   };
};

template<class DomainT, class CodomainT>
struct interval_map_concept/*modeled by*/< std::vector<std::pair<DomainT, CodomainT> > >
{
    typedef interval_map_concept                                 type;
    typedef typename std::vector<std::pair<DomainT, CodomainT> > model_type;

    typedef typename model_type::value_type::first_type  domain_type;
    typedef typename model_type::value_type::second_type codomain_type;
    typedef typename std::less<domain_type>              domain_compare; 
    typedef typename inplace_plus<codomain_type>         codomain_combine;
    typedef typename model_type::iterator                interpair_iterator; 
    typedef typename model_type::const_iterator          interpair_const_iterator; 

    static       interpair_iterator interpairs_begin (model_type& model)      { return model.begin(); };
    static       interpair_iterator interpairs_end   (model_type& model)      { return model.end();   };
    static interpair_const_iterator interpairs_cbegin(const model_type& model){ return model.begin(); };
    static interpair_const_iterator interpairs_cend  (const model_type& model){ return model.end();   };
};

template<class Type> //JODO different interval_map-Types
bool domain_less_( typename interval_map_concept<Type>::interpair_const_iterator left
                 , typename interval_map_concept<Type>::interpair_const_iterator right )
{
    typedef typename interval_map_concept<Type>::type concept;
    return concept::domain_compare()((*left).first, (*right).first);
}

template<class Type> //JODO different interval_map-Types
typename interval_map_concept<Type>::codomain_type
co_combine( typename interval_map_concept<Type>::interpair_const_iterator left
          , typename interval_map_concept<Type>::interpair_const_iterator right )
{
    typedef typename interval_map_concept<Type>::type concept;
    typename concept::codomain_type co_val = (*left).second;
    concept::codomain_combine()(co_val, (*right).second);
    return co_val;
}

template<class Type> 
typename interval_map_concept<Type>::codomain_type
co_value( typename interval_map_concept<Type>::interpair_iterator iter )
{
    return (*iter).second;
}

template<class Type> 
typename interval_map_concept<Type>::interpair_const_iterator
interpairs_cbegin( const Type& object )
{
    return interval_map_concept<Type>::interpairs_cbegin(object);
}

template<class Type> 
typename interval_map_concept<Type>::interpair_const_iterator
interpairs_cend( const Type& object )
{
    return interval_map_concept<Type>::interpairs_cend(object);
}

template<class Type> 
typename interval_map_concept<Type>::interpair_const_iterator
interpairs_end( Type& object )
{
    return interval_map_concept<Type>::interpairs_end(object);
}

template<class Type>
//typename enable_if<is_interval_map<Type>, Type>::type
Type
new_add(const Type& map1, const Type& map2)
{
    typedef typename interval_map_concept<Type>::type  concept;
    typedef typename concept::codomain_type            codomain_type;
    typedef typename concept::domain_compare           domain_compare;
    typedef typename concept::interpair_iterator       interpair_iterator;
    typedef typename concept::interpair_const_iterator interpair_const_iterator;
    typedef typename std::insert_iterator<Type>        insert_iterator;

    // A constructor that reserves space for vector result arguments
    //JODO Type sum = construct<Type>(map1,map2,init_for_addition);
    Type sum;

    //Algorithm depends on result type : joining here

    //interval_maps are never empty and begin with the identical minimum point
    interpair_const_iterator  it1_ = interpairs_cbegin(map1),
                              it2_ = interpairs_cbegin(map2),
                              pred1_, pred2_;
    interpair_iterator        last_in_ = sum.begin();

    codomain_type co_val = co_combine<Type>(it1_, it2_);
    last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val)); 
    //JODO *sum_ = construct<interpair>(it1_, co_val);
    pred1_ = it1_++;
    pred2_ = it2_++;

    while(it1_ != interpairs_cend(map1) && it2_ != interpairs_cend(map2))
    {
        if( domain_less_<Type>(it1_,it2_) )
        {
            codomain_type co_val = co_combine<Type>(it1_, pred2_);
            if((*last_in_).second != co_val)
                last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val));

            pred1_ = it1_++;
        }
        else if ( domain_less_<Type>(it2_,it1_) )
        {
            codomain_type co_val = co_combine<Type>(it2_, pred1_);
            if((*last_in_).second != co_val)
                last_in_ = sum.insert(interpairs_end(sum), make_pair((*it2_).first, co_val));

            pred2_ = it2_++;
        }
        else //( domain_equal(it1_,it2_) )
        {
            codomain_type co_val = co_combine<Type>(it1_, it2_);
            if((*last_in_).second != co_val)
                last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val));

            pred1_ = it1_++;
            pred2_ = it2_++;
        }
    }

    while(it1_ != interpairs_cend(map1))
    {
        codomain_type co_val = co_combine<Type>(it1_, pred2_);
        if((*last_in_).second != co_val)
            last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val));

        pred1_ = it1_++;
    }
    while(it2_ != interpairs_cend(map2))
    {
        codomain_type co_val = co_combine<Type>(it2_, pred1_);
        if((*last_in_).second != co_val)
            last_in_ = sum.insert(interpairs_end(sum), make_pair((*it2_).first, co_val));

        pred2_ = it2_++;
    }

    return sum;
}

template<class Type>
void new_show(const Type& object)
{
    typedef typename interval_map_concept<Type>::type  concept;
    typedef typename concept::domain_type              domain_type;
    typedef typename concept::codomain_type            codomain_type;
    typedef typename concept::interpair_iterator       interpair_iterator;
    typedef typename concept::interpair_const_iterator interpair_const_iterator;

    interpair_const_iterator it_ = interpairs_cbegin(object), pred_;

    pred_ = it_++;
    while(it_ != interpairs_cend(object))
    {
        right_open_interval<domain_type> interv((*pred_).first, (*it_).first);
        std::cout << interv << "->" << (*pred_).second << " "; 
        pred_ = it_++;
    }
    std::cout << "[" << (*pred_).first << ",oo)" << "->" << (*pred_).second << "\n"; 
}

template<class Type>
void raw_show(const Type& object)
{
    typedef typename interval_map_concept<Type>::type  concept;
    typedef typename concept::domain_type              domain_type;
    typedef typename concept::codomain_type            codomain_type;
    typedef typename concept::interpair_iterator       interpair_iterator;
    typedef typename concept::interpair_const_iterator interpair_const_iterator;

    interpair_const_iterator it_ = interpairs_cbegin(object);

    while(it_ != interpairs_cend(object))
    {
        std::cout << (*it_).first << "->" << (*it_).second << " "; 
        ++it_;
    }
    std::cout << "\n"; 
}


}} // namespace boost icl

#endif //BOOST_ICL_CONCEPT__INTERVAL_ASSOCIATOR_HPP_JOFA_120724


