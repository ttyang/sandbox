
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION_HPP_

#include <boost/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>

// PRIVATE //

// Adapted from BOOST_TTI_DETAIL_TRAIT_HAS_COMP_MEMBER_FUNCTION (see Boost.TTI).
#define BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION_(id, trait, name) \
    template< class BOOST_CONTRACT_AUX_SYMBOL( (IntroHasMemberFuncT)(id) ) > \
    struct trait { \
        template< class BOOST_CONTRACT_AUX_SYMBOL( \
                (IntroHasMemberFuncF)(id) ) > \
        struct class_type { \
            typedef \
                typename boost::remove_const< \
                    typename boost::mpl::at< \
                          typename boost::function_types::parameter_types< \
                              BOOST_CONTRACT_AUX_SYMBOL( \
                                    (IntroHasMemberFuncF)(id) ) \
                            , boost::mpl::quote1< boost::mpl::identity > \
                          >::type \
                        , boost::mpl::int_<0> \
                    >::type \
                >::type \
                type \
            ; \
        }; \
        template< BOOST_CONTRACT_AUX_SYMBOL( (IntroHasMemberFuncT)(id) ) > \
        struct helper; \
        template< class BOOST_CONTRACT_AUX_SYMBOL( \
                (IntroHasMemberFuncU)(id) ) > \
        static ::boost::type_traits::yes_type check( \
            helper<& BOOST_CONTRACT_AUX_SYMBOL( \
                    (IntroHasMemberFuncU)(id) ) ::name>* \
        ); \
        template< class BOOST_CONTRACT_AUX_SYMBOL( \
                (IntroHasMemberFuncU)(id) ) > \
        static ::boost::type_traits::no_type check(...); \
        BOOST_STATIC_CONSTANT( \
            bool, value = \
                   sizeof(check<typename class_type< \
                        BOOST_CONTRACT_AUX_SYMBOL( (IntroHasMemberFuncT)(id) ) \
                   >::type>(0)) \
                == sizeof(::boost::type_traits::yes_type) \
        ); \
        typedef boost::mpl::bool_<value> type; \
    }; \

// PUBLIC //

#define BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION(trait, name) \
    BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, trait, name)

#endif // #include guard

