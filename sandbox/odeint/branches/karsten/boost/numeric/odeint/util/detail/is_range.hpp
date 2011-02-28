// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP
#define BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <boost/range/config.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>

namespace boost {
namespace numeric {
namespace odeint {



    namespace range_detail
    {
    	BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
		BOOST_MPL_HAS_XXX_TRAIT_DEF(const_iterator)
    }

namespace detail
{

    template< typename Range >
    struct is_range : boost::mpl::and_<range_detail::has_iterator<Range>, range_detail::has_const_iterator<Range> >
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////////

    template< typename iteratorT >
    struct is_range< std::pair<iteratorT,iteratorT> > : boost::mpl::true_
    {
    };

    template< typename iteratorT >
    struct is_range< const std::pair<iteratorT,iteratorT> > : boost::mpl::true_
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////////

    template< typename elementT, std::size_t sz >
    struct is_range< elementT[sz] > : boost::mpl::true_
    {
    };

    template< typename elementT, std::size_t sz >
    struct is_range< const elementT[sz] > : boost::mpl::true_
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // string
    //////////////////////////////////////////////////////////////////////////

    template<>
    struct is_range< char* > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< wchar_t* > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< const char* > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< const wchar_t* > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< char* const > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< wchar_t* const > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< const char* const > : boost::mpl::true_
    {
    };

    template<>
    struct is_range< const wchar_t* const > : boost::mpl::true_
    {
    };

} // namespace detail

} // namespaec odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP
