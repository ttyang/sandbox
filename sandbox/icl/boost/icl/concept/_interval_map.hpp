/*-----------------------------------------------------------------------------+    
Copyright (c) 2012-2012: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT__INTERVAL_MAP_HPP_JOFA_120724
#define BOOST_ICL_CONCEPT__INTERVAL_MAP_HPP_JOFA_120724

#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <map>
#include <boost/icl/functors.hpp>
#include <boost/icl/_interval_map_traits.hpp>

namespace boost{ namespace icl
{


template<class Type> //JODO different interval_map-Types
bool domain_less_( typename interval_map_traits<Type>::interpair_const_iterator left
                 , typename interval_map_traits<Type>::interpair_const_iterator right )
{
    typedef typename interval_map_traits<Type>::type Concept;
    return Concept::domain_compare()((*left).first, (*right).first);
}

template<class Type> //JODO different interval_map-Types
typename interval_map_traits<Type>::codomain_type
co_combine( typename interval_map_traits<Type>::interpair_const_iterator left
          , typename interval_map_traits<Type>::interpair_const_iterator right )
{
    typedef typename interval_map_traits<Type>::type Concept;
    typename Concept::codomain_type co_val = (*left).second;
    Concept::codomain_combine()(co_val, (*right).second);
    return co_val;
}

template<class Type> 
typename interval_map_traits<Type>::codomain_type
co_value( typename interval_map_traits<Type>::interpair_iterator iter )
{
    return (*iter).second;
}

template<class Type> 
typename interval_map_traits<Type>::interpair_const_iterator
interpairs_cbegin( const Type& object )
{
    return interval_map_traits<Type>::interpairs_cbegin(object);
}

template<class Type> 
typename interval_map_traits<Type>::interpair_const_iterator
interpairs_cend( const Type& object )
{
    return interval_map_traits<Type>::interpairs_cend(object);
}

template<class Type> 
typename interval_map_traits<Type>::interpair_iterator
interpairs_begin( Type& object )
{
    return interval_map_traits<Type>::interpairs_begin(object);
}

template<class Type> 
typename interval_map_traits<Type>::interpair_iterator
interpairs_end( Type& object )
{
    return interval_map_traits<Type>::interpairs_end(object);
}

template<class Type>
inline typename 
    enable_if< interval_map_traits<Type>
             , typename interval_map_traits<Type>::interpair_iterator>::type
insert( Type& object
      , typename interval_map_traits<Type>::interpair_iterator position
      , const typename interval_map_traits<Type>::interpair_type& value )
{
    return interval_map_traits<Type>::insert(object, position, value);
}




template<class Type>
typename enable_if<interval_map_traits<Type>, Type>::type
joining_add(const Type& map1, const Type& map2, bool join=true)
{
    typedef typename interval_map_traits<Type>::type  Concept;
    typedef typename Concept::codomain_type            codomain_type;
    typedef typename Concept::domain_compare           domain_compare;
    typedef typename Concept::interpair_iterator       interpair_iterator;
    typedef typename Concept::interpair_const_iterator interpair_const_iterator;
    typedef typename std::insert_iterator<Type>        insert_iterator;

    // A constructor that reserves space for vector result arguments
    //JODO Type sum = construct<Type>(map1,map2,init_for_addition);
    Type sum;

    //Algorithm depends on result type : joining here

    //interval_maps are never empty and begin with the identical minimum point
    interpair_const_iterator  it1_ = interpairs_cbegin(map1),
                              it2_ = interpairs_cbegin(map2),
                              pred1_, pred2_;
    interpair_iterator        last_in_ = interpairs_begin(sum);

    codomain_type co_val = co_combine<Type>(it1_, it2_);
    last_in_ = insert(sum, interpairs_end(sum), make_pair((*it1_).first, co_val)); 
    //JODO *sum_ = construct<interpair>(it1_, co_val);
    pred1_ = it1_++;
    pred2_ = it2_++;

    while(it1_ != interpairs_cend(map1) && it2_ != interpairs_cend(map2))
    {
        if( domain_less_<Type>(it1_,it2_) )
        {
            codomain_type co_val = co_combine<Type>(it1_, pred2_);
            if(!join || (*last_in_).second != co_val)
                last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val));

            pred1_ = it1_++;
        }
        else if ( domain_less_<Type>(it2_,it1_) )
        {
            codomain_type co_val = co_combine<Type>(it2_, pred1_);
            if(!join || (*last_in_).second != co_val)
                last_in_ = sum.insert(interpairs_end(sum), make_pair((*it2_).first, co_val));

            pred2_ = it2_++;
        }
        else //( domain_equal(it1_,it2_) )
        {
            codomain_type co_val = co_combine<Type>(it1_, it2_);
            if(!join || (*last_in_).second != co_val)
                last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val));

            pred1_ = it1_++;
            pred2_ = it2_++;
        }
    }

    while(it1_ != interpairs_cend(map1))
    {
        codomain_type co_val = co_combine<Type>(it1_, pred2_);
        if(!join || (*last_in_).second != co_val)
            last_in_ = sum.insert(interpairs_end(sum), make_pair((*it1_).first, co_val));

        pred1_ = it1_++;
    }
    while(it2_ != interpairs_cend(map2))
    {
        codomain_type co_val = co_combine<Type>(it2_, pred1_);
        if(!join || (*last_in_).second != co_val)
            last_in_ = sum.insert(interpairs_end(sum), make_pair((*it2_).first, co_val));

        pred2_ = it2_++;
    }

    return sum;
}

/*CONTINUE
template<class Type>
typename enable_if<interval_map_traits<Type>, Type>::type
add_interval( const Type& map1
            , const typename Type::segment_type& segment
            , bool join=true)
{
    Type sum;
    sum.insert(sum.end(), make_pair(0, 0));
    sum.insert(sum.end(), make_pair(inter_val.lower(), 0));
}
*/

template<class Type>
void new_show(const Type& object)
{
    typedef typename interval_map_traits<Type>::type   Concept;
    typedef typename Concept::domain_type              domain_type;
    typedef typename Concept::codomain_type            codomain_type;
    typedef typename Concept::interpair_iterator       interpair_iterator;
    typedef typename Concept::interpair_const_iterator interpair_const_iterator;

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
    typedef typename interval_map_traits<Type>::type   Concept;
    typedef typename Concept::domain_type              domain_type;
    typedef typename Concept::codomain_type            codomain_type;
    typedef typename Concept::interpair_iterator       interpair_iterator;
    typedef typename Concept::interpair_const_iterator interpair_const_iterator;

    interpair_const_iterator it_ = interpairs_cbegin(object);

    while(it_ != interpairs_cend(object))
    {
        std::cout << (*it_).first << "->" << (*it_).second << " "; 
        ++it_;
    }
    std::cout << "\n"; 
}


}} // namespace boost icl

#endif //BOOST_ICL_CONCEPT__INTERVAL_MAP_HPP_JOFA_120724


