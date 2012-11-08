//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_HPP_INCLUDED

#include <utility>
#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container/detail/workaround.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/container/detail/preprocessor.hpp>
#endif

namespace boost { namespace detail {

    template <typename F, typename C>
    class emplace_assoc_function_proxy
    {
        F const _function;
        C& _container;

     public:
        explicit emplace_assoc_function_proxy(C& c);

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename ...Args>
        inline emplace_assoc_function_proxy&
            operator()(typename C::key_type const& key, Args&& ...args)
        {
            this->_function(
                this->_container
              , key
              , ::boost::forward<Args>(args)...
            );
            return *this;
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        inline emplace_assoc_function_proxy&                                 \
            operator()(                                                      \
                typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            )                                                                \
        {                                                                    \
            this->_function(                                                 \
                this->_container                                             \
              , key                                                          \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , poop                                                     \
                )                                                            \
            );                                                               \
            return *this;                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename F, typename C>
    emplace_assoc_function_proxy<F,C>::emplace_assoc_function_proxy(C& c)
      : _function(), _container(c)
    {
    }

    struct uac_emplace_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<uac_emplace_associative_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(
                C& _container
              , typename C::key_type const& key
              , Args&& ...args
            ) const
        {
            return _container.emplace(
                key
              , ::boost::move(
                    typename C::mapped_type(::boost::forward<Args>(args)...)
                )
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return _container.emplace(                                       \
                key                                                          \
              , ::boost::move(                                               \
                    typename C::mapped_type(                                 \
                        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                     \
                            n                                                \
                          , BOOST_CONTAINER_PP_PARAM_FORWARD                 \
                          , poop                                             \
                        )                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_PP_DEC(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_assoc_function_proxy<uac_emplace_associative_function,C>
        uac_emplace_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            uac_emplace_associative_function
          , C
        >(_container);
    }

    struct uac_emplace_emu_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<uac_emplace_emu_associative_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(
                C& _container
              , typename C::key_type const& key
              , Args&& ...args
            ) const
        {
            return _container.insert(
                typename C::value_type(
                    key
                  , typename C::mapped_type(::boost::forward<Args>(args)...)
                )
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return _container.insert(                                        \
                typename C::value_type(                                      \
                    key                                                      \
                  , typename C::mapped_type(                                 \
                        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                     \
                            n                                                \
                          , BOOST_CONTAINER_PP_PARAM_FORWARD                 \
                          , poop                                             \
                        )                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_assoc_function_proxy<uac_emplace_emu_associative_function,C>
        uac_emplace_emu_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            uac_emplace_emu_associative_function
          , C
        >(_container);
    }

    struct mac_emplace_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<mac_emplace_associative_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(
                C& _container
              , typename C::key_type const& key
              , Args&& ...args
            ) const
        {
            return ::std::make_pair(
                _container.emplace(
                    key
                  , ::boost::move(
                        typename C::mapped_type(
                            ::boost::forward<Args>(args)...
                        )
                    )
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return ::std::make_pair(                                         \
                _container.emplace(                                          \
                    key                                                      \
                  , ::boost::move(                                           \
                        typename C::mapped_type(                             \
                            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                 \
                                n                                            \
                              , BOOST_CONTAINER_PP_PARAM_FORWARD             \
                              , poop                                         \
                            )                                                \
                        )                                                    \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_PP_DEC(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_assoc_function_proxy<mac_emplace_associative_function,C>
        mac_emplace_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            mac_emplace_associative_function
          , C
        >(_container);
    }

    struct mac_emplace_emu_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<mac_emplace_emu_associative_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(
                C& _container
              , typename C::key_type const& key
              , Args&& ...args
            ) const
        {
            return ::std::make_pair(
                _container.insert(
                    typename C::value_type(
                        key
                      , typename C::mapped_type(
                            ::boost::forward<Args>(args)...
                        )
                    )
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return ::std::make_pair(                                         \
                _container.insert(                                           \
                    typename C::value_type(                                  \
                        key                                                  \
                      , typename C::mapped_type(                             \
                            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                 \
                                n                                            \
                              , BOOST_CONTAINER_PP_PARAM_FORWARD             \
                              , poop                                         \
                            )                                                \
                        )                                                    \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_assoc_function_proxy<mac_emplace_emu_associative_function,C>
        mac_emplace_emu_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            mac_emplace_emu_associative_function
          , C
        >(_container);
    }

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING

    struct huac_emplace_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<huac_emplace_associative_function,C>
            operator[](C& _container) const;

#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return _container.emplace(                                       \
                ::boost::unordered::piecewise_construct                      \
              , ::boost::make_tuple(key)                                     \
              , ::boost::make_tuple(                                         \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , poop                                                 \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
    };

    template <typename C>
    emplace_assoc_function_proxy<huac_emplace_associative_function,C>
        huac_emplace_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            huac_emplace_associative_function
          , C
        >(_container);
    }

    struct hmac_emplace_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<hmac_emplace_associative_function,C>
            operator[](C& _container) const;

#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return ::std::make_pair(                                         \
                _container.emplace(                                          \
                    ::boost::unordered::piecewise_construct                  \
                  , ::boost::make_tuple(key)                                 \
                  , ::boost::make_tuple(                                     \
                        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                     \
                            n                                                \
                          , BOOST_CONTAINER_PP_PARAM_FORWARD                 \
                          , poop                                             \
                        )                                                    \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
    };

    template <typename C>
    emplace_assoc_function_proxy<hmac_emplace_associative_function,C>
        hmac_emplace_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            hmac_emplace_associative_function
          , C
        >(_container);
    }

#if defined BOOST_HAS_TR1_UNORDERED_MAP

// Handle different native TR1 emplacement implementations.
#if defined BOOST_MSVC

    struct tr1_huac_emplace_associative_function
    {
        template <typename C>
        emplace_assoc_function_proxy<tr1_huac_emplace_associative_function,C>
            operator[](C& _container) const;

#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return _container.emplace(                                       \
                ::boost::move(                                               \
                    typename C::value_type(                                  \
                        key                                                  \
                      , typename C::mapped_type(                             \
                            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                 \
                                n                                            \
                              , BOOST_CONTAINER_PP_PARAM_FORWARD             \
                              , poop                                         \
                            )                                                \
                        )                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
    };

    template <typename C>
    emplace_assoc_function_proxy<tr1_huac_emplace_associative_function,C>
        tr1_huac_emplace_associative_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<
            tr1_huac_emplace_associative_function
          , C
        >(_container);
    }

    typedef tr1_huac_emplace_associative_function
            tr1_hmac_emplace_associative_function;
#else  // TR1 == Boost wrt unordered_[multi]map::emplace
#define BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif

#else  // !defined BOOST_HAS_TR1_UNORDERED_MAP
#define BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif  // BOOST_HAS_TR1_UNORDERED_MAP

#if defined BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_USE_NO_NATIVE_TR1
    typedef huac_emplace_associative_function
            tr1_huac_emplace_associative_function;
    typedef hmac_emplace_associative_function
            tr1_hmac_emplace_associative_function;
#undef BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif  // BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    struct ua_ptr_emplace_assoc_function
    {
        template <typename C>
        emplace_assoc_function_proxy<ua_ptr_emplace_assoc_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(
                C& _container
              , typename C::key_type const& key
              , Args&& ...args
            ) const
        {
            typedef typename ::std::tr1::remove_pointer<
                        typename C::mapped_type
                    >::type
                    _data_type;

            typename C::key_type k(key);
            return _container.insert(
                k
              , new _data_type(::boost::forward<Args>(args)...)
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            typedef typename ::std::tr1::remove_pointer<                     \
                        typename C::mapped_type                              \
                    >::type                                                  \
                    _data_type;                                              \
            typename C::key_type k(key);                                     \
            return _container.insert(                                        \
                k                                                            \
              , new _data_type(                                              \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , poop                                                 \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_assoc_function_proxy<ua_ptr_emplace_assoc_function,C>
        ua_ptr_emplace_assoc_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<ua_ptr_emplace_assoc_function,C>(
            _container
        );
    }

    struct ma_ptr_emplace_assoc_function
    {
        template <typename C>
        emplace_assoc_function_proxy<ma_ptr_emplace_assoc_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(
                C& _container
              , typename C::key_type const& key
              , Args&& ...args
            ) const
        {
            typedef typename ::std::tr1::remove_pointer<
                        typename C::mapped_type
                    >::type
                    _data_type;

            typename C::key_type k(key);
            return ::std::make_pair(
                _container.insert(
                    k
                  , new _data_type(::boost::forward<Args>(args)...)
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO(z, n, poop)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
              , typename C::key_type const& key                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            typedef typename ::std::tr1::remove_pointer<                     \
                        typename C::mapped_type                              \
                    >::type                                                  \
                    _data_type;                                              \
            typename C::key_type k(key);                                     \
            return ::std::make_pair(                                         \
                _container.insert(                                           \
                    k                                                        \
                  , new _data_type(                                          \
                        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                     \
                            n                                                \
                          , BOOST_CONTAINER_PP_PARAM_FORWARD                 \
                          , poop                                             \
                        )                                                    \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPL_ASSOC_FUNC_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_assoc_function_proxy<ma_ptr_emplace_assoc_function,C>
        ma_ptr_emplace_assoc_function::operator[](C& _container) const
    {
        return emplace_assoc_function_proxy<ma_ptr_emplace_assoc_function,C>(
            _container
        );
    }
}}  // namespace boost::detail

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/container_gen/has_emplace_mfunc_selector.hpp>
#include <boost/container_gen/is_associative_selector.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include <boost/container_gen/is_multiple_assoc_selector.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/container_gen/is_hashed_assoc_selector.hpp>
#include <boost/container_gen/is_tr1_selector.hpp>
#endif

//[reference__emplace_associative_function_gen
namespace boost {

    template <typename Selector>
    struct emplace_associative_function_gen
        //<-
      : ::boost::mpl::eval_if<
            is_ptr_selector<Selector>
          , ::boost::mpl::if_<
                is_multiple_associative_selector<Selector>
              , detail::ma_ptr_emplace_assoc_function
              , detail::ua_ptr_emplace_assoc_function
            >
          , ::boost::mpl::eval_if<
                has_emplace_member_function_selector<Selector>
#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
              , ::boost::mpl::eval_if<
                    is_hashed_associative_selector<Selector>
                  , ::boost::mpl::eval_if<
                        is_tr1_selector<Selector>
                      , ::boost::mpl::if_<
                            is_unique_associative_selector<Selector>
                          , detail::tr1_huac_emplace_associative_function
                          , detail::tr1_hmac_emplace_associative_function
                        >
                      , ::boost::mpl::if_<
                            is_unique_associative_selector<Selector>
                          , detail::huac_emplace_associative_function
                          , detail::hmac_emplace_associative_function
                        >
                    >
#endif
                  , ::boost::mpl::if_<
                        is_multiple_associative_selector<Selector>
                      , detail::mac_emplace_associative_function
                      , detail::uac_emplace_associative_function
                    >
#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
                >
#endif
              , ::boost::mpl::if_<
                    is_multiple_associative_selector<Selector>
                  , detail::mac_emplace_emu_associative_function
                  , detail::uac_emplace_emu_associative_function
                >
            >
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , emplace_associative_function_gen
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_CONTAINER_GEN_EMPLACE_ASSOC_FUNCTION_GEN_HPP_INCLUDED

