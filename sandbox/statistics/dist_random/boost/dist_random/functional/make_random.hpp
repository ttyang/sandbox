//////////////////////////////////////////////////////////////////////////////
// dist_random::functional::make_random.hpp                                 //
//                                                                          //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_DIST_RANDOM_FUNCTIONAL_MAKE_RANDOM_HPP_ER_2009
#define BOOST_DIST_RANDOM_FUNCTIONAL_MAKE_RANDOM_HPP_ER_2009
#include <boost/dist_random/meta/dist_random.hpp>

namespace boost{

    template<typename D>
    typename dist_random<D>::type
    make_random(const D& d){
        typedef dist_random<D> meta_;
        return meta_::make(d);
    }

}

#endif