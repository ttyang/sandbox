/////////////////////////////////////////////////////////////////////////////////
// distribution::toolkit::distributions::wrapper::log_unnormalized_pdf.hpp      //
//                                                                             //
//  (C) Copyright 2009 Erwann Rogard                                           //
//  Use, modification and distribution are subject to the                      //
//  Boost Software License, Version 1.0. (See accompanying file                //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)           //
/////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_TOOLKIT_WRAPPER_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_TOOLKIT_WRAPPER_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#include <boost/concept/assert.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/wrapper/wrapper.hpp>

namespace boost{
namespace statistics{
namespace detail{

    template<typename D,typename T>
    T
    log_unnormalized_pdf(
        const distribution::toolkit::wrapper<D>& w,
        const T& x
    ){
        return statistics::detail::log_unnormalized_pdf(w.const_reference(),x);
    }

}// detail
}// statistics
}// boost

#endif