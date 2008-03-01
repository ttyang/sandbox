// Copyright Stjepan Rajko 2007,2008. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_DATAFLOW_UTILITY_BIND_OBJECT_HPP)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/dataflow/utility/slot_type.hpp>

#include <boost/function_types/function_arity.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace boost { namespace dataflow { namespace utility {
        
namespace detail {
        
    template<typename Signature, typename T, int Arity>
    struct bind_object_impl;

#   define BOOST_PP_ITERATION_PARAMS_1 (3,(0,9,<boost/dataflow/utility/bind_object.hpp>))
#   include BOOST_PP_ITERATE()
    
} // namespace detail

template<typename Signature, typename T>
struct bind_object : public detail::bind_object_impl<Signature, T, boost::function_types::function_arity<Signature>::value>
{};

} } } // namespace boost::dataflow::utility

#define BOOST_DATAFLOW_UTILITY_BIND_OBJECT_HPP
#else // defined(BOOST_PP_IS_ITERATING)

template<typename Signature, typename T>
struct bind_object_impl<Signature, T, BOOST_PP_ITERATION()>
{
    boost::function<Signature> operator()(typename slot_type<Signature, T>::type mem_fn, T &object)
    {
        return boost::bind(mem_fn, boost::ref(object)
                        BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
                        BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(BOOST_PP_ITERATION()),_));
    }
    boost::function<Signature> operator()(typename slot_type<Signature, T>::type mem_fn, const T &object)
    {
        return boost::bind(mem_fn, boost::cref(object)
                           BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
                           BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(BOOST_PP_ITERATION()),_));
    }
};

#endif // defined(BOOST_PP_IS_ITERATING)
#endif // BOOST_DATAFLOW_UTILITY_BIND_OBJECT_HPP

    