// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_DATA_TYPE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_DATA_TYPE_HPP_INCLUDED

#include <boost/ref.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_volatile.hpp>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct data_type
    {
     private:
        typedef typename ::boost::remove_const<
                    typename ::boost::remove_reference<
                        typename ::boost::remove_pointer<
                            typename ::boost::remove_volatile<
                                typename ::boost::remove_all_extents<
                                    typename ::boost::unwrap_reference<T>::type
                                >::type
                            >::type
                        >::type
                    >::type
                >::type
                lower_type;

     public:
        typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<T,lower_type>
                  , ::boost::mpl::identity<T>
                  , data_type<lower_type>
                >::type
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,data_type,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_DATA_TYPE_HPP_INCLUDED

