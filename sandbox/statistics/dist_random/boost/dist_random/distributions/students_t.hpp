//////////////////////////////////////////////////////////////////////////////
// dist_random::distributions::students_t.hpp                               //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_DIST_RANDOM_DISTRIBUTIONS_STUDENTS_T_HPP_ER_2009
#define BOOST_DIST_RANDOM_DISTRIBUTIONS_STUDENTS_T_HPP_ER_2009
#include <boost/standard_distribution/distributions/students_t.hpp>
#include <boost/random/students_t.hpp>
#include <boost/dist_random/meta/dist_random.hpp>

namespace boost{

    template<typename T,typename P>
    struct dist_random< 
        boost::math::students_t_distribution<T,P> 
    >{
        typedef boost::math::students_t_distribution<T,P> dist_;
        typedef boost::random::students_t_distribution<T> type;
        
        static type make(const dist_& d){ 
            return type(d.degrees_of_freedom()); 
        }
    };
    
}// boost

#endif
