// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_CONTAINER_ITERATOR_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_CONTAINER_ITERATOR_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct container_iterator
    {
     private:
        typedef typename ::std::tr1::remove_const<T>::type
                C;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_const<T>
                  , typename C::const_iterator
                  , typename C::iterator
                >::type
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,container_iterator,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_CONTAINER_ITERATOR_HPP_INCLUDED

