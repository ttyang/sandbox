//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_HPP_INCLUDED

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
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/container/detail/preprocessor.hpp>

#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQUENCE_MACRO(z, n, itr)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return ::std::make_pair(                                         \
                _container.emplace(                                          \
                    itr                                                      \
                    BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!

#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQ_EMU_MACRO(z, n, itr)    \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return ::std::make_pair(                                         \
                _container.insert(                                           \
                    itr                                                      \
                  , typename C::value_type(                                  \
                        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                     \
                            n                                                \
                          , BOOST_CONTAINER_PP_PARAM_FORWARD                 \
                          , _                                                \
                        )                                                    \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

namespace boost { namespace detail {

    template <typename F, typename C>
    class emplace_function_proxy
    {
        F const _function;
        C& _container;

     public:
        explicit emplace_function_proxy(C& c);

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename ...Args>
        inline emplace_function_proxy& operator()(Args&& ...args)
        {
            this->_function(this->_container, ::boost::forward<Args>(args)...);
            return *this;
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        inline emplace_function_proxy&                                       \
            operator()(                                                      \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            )                                                                \
        {                                                                    \
            this->_function(                                                 \
                this->_container                                             \
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
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename F, typename C>
    emplace_function_proxy<F,C>::emplace_function_proxy(C& c)
      : _function(), _container(c)
    {
    }

    struct fis_emplace_function
    {
        template <typename C>
        emplace_function_proxy<fis_emplace_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return ::std::make_pair(
                _container.emplace(
                    _container.begin()
                  , ::boost::forward<Args>(args)...
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQUENCE_MACRO
          , _container.begin()
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<fis_emplace_function,C>
        fis_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<fis_emplace_function,C>(_container);
    }

    struct bis_emplace_function
    {
        template <typename C>
        emplace_function_proxy<bis_emplace_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return ::std::make_pair(
                _container.emplace(
                    _container.end()
                  , ::boost::forward<Args>(args)...
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQUENCE_MACRO
          , _container.end()
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<bis_emplace_function,C>
        bis_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<bis_emplace_function,C>(_container);
    }

    struct fis_emplace_emu_function
    {
        template <typename C>
        emplace_function_proxy<fis_emplace_emu_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return ::std::make_pair(
                _container.insert(
                    _container.begin()
                  , typename C::value_type(
                        ::boost::forward<Args>(args)...
                    )
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQ_EMU_MACRO
          , _container.begin()
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<fis_emplace_emu_function,C>
        fis_emplace_emu_function::operator[](C& _container) const
    {
        return emplace_function_proxy<fis_emplace_emu_function,C>(_container);
    }

    struct bis_emplace_emu_function
    {
        template <typename C>
        emplace_function_proxy<bis_emplace_emu_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return ::std::make_pair(
                _container.insert(
                    _container.end()
                  , typename C::value_type(
                        ::boost::forward<Args>(args)...
                    )
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQ_EMU_MACRO
          , _container.end()
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<bis_emplace_emu_function,C>
        bis_emplace_emu_function::operator[](C& _container) const
    {
        return emplace_function_proxy<bis_emplace_emu_function,C>(_container);
    }

    struct uac_emplace_function
    {
        template <typename C>
        emplace_function_proxy<uac_emplace_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return _container.emplace(::boost::forward<Args>(args)...);
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return _container.emplace(                                       \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , poop                                                     \
                )                                                            \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<uac_emplace_function,C>
        uac_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<uac_emplace_function,C>(_container);
    }

    struct uac_emplace_emu_function
    {
        template <typename C>
        emplace_function_proxy<uac_emplace_emu_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return _container.insert(
                typename C::value_type(::boost::forward<Args>(args)...)
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return _container.insert(                                        \
                typename C::value_type(                                      \
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
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<uac_emplace_emu_function,C>
        uac_emplace_emu_function::operator[](C& _container) const
    {
        return emplace_function_proxy<uac_emplace_emu_function,C>(_container);
    }

    struct mac_emplace_function
    {
        template <typename C>
        emplace_function_proxy<mac_emplace_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return ::std::make_pair(
                _container.emplace(::boost::forward<Args>(args)...)
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            return ::std::make_pair(                                         \
                _container.emplace(                                          \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , poop                                                 \
                    )                                                        \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<mac_emplace_function,C>
        mac_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<mac_emplace_function,C>(_container);
    }

    struct mac_emplace_emu_function
    {
        template <typename C>
        emplace_function_proxy<mac_emplace_emu_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            return ::std::make_pair(
                _container.insert(
                    typename C::value_type(::boost::forward<Args>(args)...)
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
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
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<mac_emplace_emu_function,C>
        mac_emplace_emu_function::operator[](C& _container) const
    {
        return emplace_function_proxy<mac_emplace_emu_function,C>(_container);
    }

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#if defined BOOST_HAS_TR1_UNORDERED_SET

// Handle different native TR1 emplacement implementations.
#if defined BOOST_MSVC

    struct tr1_huac_emplace_function
    {
        template <typename C>
        emplace_function_proxy<tr1_huac_emplace_function,C>
            operator[](C& _container) const;

#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
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
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
    };

    template <typename C>
    emplace_function_proxy<tr1_huac_emplace_function,C>
        tr1_huac_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<tr1_huac_emplace_function,C>(_container);
    }

    typedef tr1_huac_emplace_function tr1_hmac_emplace_function;
#else  // TR1 == Boost wrt unordered_[multi]set::emplace
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif

#else  // !defined BOOST_HAS_TR1_UNORDERED_SET
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif  // BOOST_HAS_TR1_UNORDERED_SET

#if defined BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_USE_NO_NATIVE_TR1
    typedef uac_emplace_function tr1_huac_emplace_function;
    typedef mac_emplace_function tr1_hmac_emplace_function;
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif  // BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_USE_NO_NATIVE_TR1
#endif  // !defined BOOST_CONTAINER_PERFECT_FORWARDING

    struct ptr_sequence_emplace_function
    {
        template <typename C>
        emplace_function_proxy<ptr_sequence_emplace_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            typedef typename ::std::tr1::remove_pointer<
                        typename C::value_type
                    >::type
                    _data_type;

            return ::std::make_pair(
                _container.insert(
                    _container.end()
                  , new _data_type(::boost::forward<Args>(args)...)
                )
              , true
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            typedef typename ::std::tr1::remove_pointer<                     \
                        typename C::value_type                               \
                    >::type                                                  \
                    _data_type;                                              \
            return ::std::make_pair(                                         \
                _container.insert(                                           \
                    _container.end()                                         \
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
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<ptr_sequence_emplace_function,C>
        ptr_sequence_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<ptr_sequence_emplace_function,C>(
            _container
        );
    }

    struct ua_ptr_container_emplace_function
    {
        template <typename C>
        emplace_function_proxy<ua_ptr_container_emplace_function,C>
            operator[](C& _container) const;

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename C, typename ...Args>
        inline ::std::pair<typename C::iterator,bool>
            operator()(C& _container, Args&& ...args) const
        {
            typedef typename ::std::tr1::remove_pointer<
                        typename C::value_type
                    >::type
                    _data_type;

            return _container.insert(
                new _data_type(::boost::forward<Args>(args)...)
            );
        }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO(z, n, poop)   \
        template <                                                           \
            typename C                                                       \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, typename P)                \
        >                                                                    \
        inline ::std::pair<typename C::iterator,bool>                        \
            operator()(                                                      \
                C& _container                                                \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , poop                                                     \
                )                                                            \
            ) const                                                          \
        {                                                                    \
            typedef typename ::std::tr1::remove_pointer<                     \
                        typename C::value_type                               \
                    >::type                                                  \
                    _data_type;                                              \
            return _container.insert(                                        \
                new _data_type(                                              \
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
          , BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
          , _
        )
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_CALL_OP_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

    template <typename C>
    emplace_function_proxy<ua_ptr_container_emplace_function,C>
        ua_ptr_container_emplace_function::operator[](C& _container) const
    {
        return emplace_function_proxy<ua_ptr_container_emplace_function,C>(
            _container
        );
    }
}}  // namespace boost::detail

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQ_EMU_MACRO
#undef BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_SEQUENCE_MACRO
#endif

#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/container_gen/has_emplace_mfunc_selector.hpp>
#include <boost/container_gen/is_associative_selector.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include <boost/container_gen/is_multiple_assoc_selector.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/container_gen/is_tr1_selector.hpp>
#endif

//[reference__emplace_function_gen
namespace boost {

    template <typename Selector>
    struct emplace_function_gen
        //<-
      : ::boost::mpl::eval_if<
            is_ptr_selector<Selector>
          , ::boost::mpl::if_<
                is_unique_associative_selector<Selector>
              , detail::ua_ptr_container_emplace_function
              , detail::ptr_sequence_emplace_function
            >
          , ::boost::mpl::eval_if<
                has_emplace_member_function_selector<Selector>
              , ::boost::mpl::eval_if<
                    is_associative_selector<Selector>
#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
                  , ::boost::mpl::eval_if<
                        is_tr1_selector<Selector>
                      , ::boost::mpl::if_<
                            is_multiple_associative_selector<Selector>
                          , detail::tr1_hmac_emplace_function
                          , detail::tr1_huac_emplace_function
                        >
#endif
                      , ::boost::mpl::if_<
                            is_multiple_associative_selector<Selector>
                          , detail::mac_emplace_function
                          , detail::uac_emplace_function
                        >
#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
                    >
#endif
                  , ::boost::mpl::identity<detail::bis_emplace_function>
                >
              , ::boost::mpl::eval_if<
                    is_associative_selector<Selector>
                  , ::boost::mpl::if_<
                        is_unique_associative_selector<Selector>
                      , detail::uac_emplace_emu_function
                      , detail::mac_emplace_emu_function
                    >
                  , ::boost::mpl::identity<detail::bis_emplace_emu_function>
                >
            >
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, emplace_function_gen, (Selector))
        //->
    };
}  // namespace boost
//]

#include <boost/container_gen/selectors.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename AllocatorSelector>
    struct emplace_function_gen<slist_selector<AllocatorSelector> >
    {
        typedef detail::fis_emplace_function type;
    };
}  // namespace boost

#elif !defined BOOST_NO_SLIST

namespace boost {

    template <>
    struct emplace_function_gen<slist_selector_base>
    {
        typedef detail::fis_emplace_emu_function type;
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION, BOOST_NO_SLIST

#endif  // BOOST_CONTAINER_GEN_EMPLACE_FUNCTION_GEN_HPP_INCLUDED

