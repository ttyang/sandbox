/*=================================---------------------------------------------
    Copyright 2007,2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#if !BOOST_PP_IS_ITERATING

    #ifndef BOOST__DATAFLOW__GENERIC__FRAMEWORK_ENTITY__TRAITS_SEQUENCE_INTRUSIVE_REGISTRATION_HPP
    #define BOOST__DATAFLOW__GENERIC__FRAMEWORK_ENTITY__TRAITS_SEQUENCE_INTRUSIVE_REGISTRATION_HPP

    #include <boost/preprocessor/iteration/iterate.hpp>

    #include <boost/mpl/at.hpp>
    #include <boost/mpl/int.hpp>
    #include <boost/mpl/less.hpp>
    #include <boost/mpl/size.hpp>


namespace boost { namespace dataflow {

namespace detail {

    template<typename Framework, typename T, int N>
    struct lazy_is_same_traits_tag
    {
        typedef typename is_same<Framework, typename mpl::at_c<typename T::dataflow_traits, N>::type::tag>::type type;
    };
    
    template<int Iteration, typename Sequence>
    struct lazy_is_less_than_size
    {
        typedef typename mpl::less<mpl::int_<Iteration>, typename mpl::size<Sequence>::type>::type type;
    };
    
}

} }

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, 2, <boost/dataflow/generic/framework_entity/traits_sequence_intrusive_registration.hpp>))
    #include BOOST_PP_ITERATE()

    #endif // BOOST__DATAFLOW__GENERIC__FRAMEWORK_ENTITY__TRAITS_SEQUENCE_INTRUSIVE_REGISTRATION_HPP

#else

namespace boost { namespace dataflow {


template<typename T, typename Framework>
struct traits_of<
    T,
    Framework,
    typename enable_if<
        mpl::and_<
            mpl::is_sequence<typename T::dataflow_traits>,
            detail::lazy_is_less_than_size<BOOST_PP_ITERATION(), typename T::dataflow_traits>,
            detail::lazy_is_same_traits_tag<Framework, T, BOOST_PP_ITERATION()>
        >
    >::type
>
{
    typedef typename mpl::at_c<typename T::dataflow_traits, BOOST_PP_ITERATION()>::type type;
    BOOST_MPL_ASSERT(( is_traits<type> ));
};

}}

#endif