//////////////////////////////////////////////////////////////////////////////
// cross_validation::estimator::meta::estimator.hpp                         //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef  BOOST_STATISTICS_DETAIL_CROSS_VALIDATION_ESTIMATOR_META_ESTIMATOR_HPP_ER_2009
#define  BOOST_STATISTICS_DETAIL_CROSS_VALIDATION_ESTIMATOR_META_ESTIMATOR_HPP_ER_2009
#include <boost/mpl/empty_base.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace cross_validation{
namespace estimator{
namespace meta{

    template<typename I,typename B = boost::mpl::empty_base>
    struct estimator : B{
        typedef I estimator_type;
    };

}// meta
}// estimator
}// cross_validation
}// detail
}// statistics
}// boost

#endif
