// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_CONTAINER_REVERSE_ITERATOR_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_CONTAINER_REVERSE_ITERATOR_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_reverse_iterator.hpp>
#include <boost/detail/metafunction/is_bidirectional_iterator.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename C>
    struct container_reverse_iterator_check_1
      : ::boost::mpl::if_<
            ::std::tr1::is_void<typename C::reverse_iterator>
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type
    {
    };

    template <typename C>
    struct container_reverse_iterator_check_2
      : is_bidirectional_iterator<typename C::reverse_iterator>
    {
    };

    template <typename C, typename IsConst>
    struct container_reverse_iterator_impl
      : ::boost::mpl::if_<
            IsConst
          , typename C::const_reverse_iterator
          , typename C::reverse_iterator
        >
    {
    };

    template <typename T>
    struct container_reverse_iterator
    {
     private:
        typedef typename ::std::tr1::remove_const<T>::type
                C;

     public:
        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::mpl::eval_if<
                        typename has_reverse_iterator<C>::type
                      , ::boost::mpl::eval_if<
                            container_reverse_iterator_check_1<C>
                          , container_reverse_iterator_check_2<C>
                          , ::boost::mpl::false_
                        >
                      , ::boost::mpl::false_
                    >::type
                  , container_reverse_iterator_impl<C,::std::tr1::is_const<T> >
                  , ::boost::mpl::identity<void>
                >::type
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,container_reverse_iterator,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_CONTAINER_REVERSE_ITERATOR_HPP_INCLUDED

