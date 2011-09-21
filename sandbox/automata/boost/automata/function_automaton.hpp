// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_FUNCTION_AUTOMATON_HPP_INCLUDED
#define BOOST_AUTOMATA_FUNCTION_AUTOMATON_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 5)
#error Set BOOST_PARAMETER_MAX_ARITY to 5 or more.
#endif

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/automata/keyword/name.hpp>
#include <boost/automata/generator/deterministic.hpp>
#include <boost/automata/transition_function/adaptor.hpp>
#include <boost/automata/policy/default_input_validation.hpp>
#include <boost/automata/_detail/impl.hpp>

//#define __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__

//[reference__function_automaton
namespace boost { namespace automata {

//<-
#ifdef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#define BOOST_AUTOMATA_AUTOMATON_ARGS \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::optional<keyword::tag::_Policies> \
      , ::boost::parameter::optional<keyword::tag::_InputValidationPolicy> \
      , ::boost::parameter::optional<keyword::tag::_IsUndoable> \
    >::BOOST_NESTED_TEMPLATE bind<T1,T2,T3,parameter::void_>::type \
//
#else  // !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
#define BOOST_AUTOMATA_AUTOMATON_ARGS \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::optional<keyword::tag::_Policies> \
      , ::boost::parameter::optional<keyword::tag::_InputValidationPolicy> \
      , ::boost::parameter::optional<keyword::tag::_IsUndoable> \
    >::BOOST_NESTED_TEMPLATE bind<T1,T2,T3>::type \
//
#endif  // BOOST_AUTOMATA_AUTOMATON_ARGS
#else  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#define BOOST_AUTOMATA_AUTOMATON_ARGS \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_Function> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
      , ::boost::parameter::optional<keyword::tag::_InputValidationPolicy> \
      , ::boost::parameter::optional<keyword::tag::_IsUndoable> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1,T2,T3,parameter::void_>::type \
//
#else  // !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
#define BOOST_AUTOMATA_AUTOMATON_ARGS \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_Function> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
      , ::boost::parameter::optional<keyword::tag::_InputValidationPolicy> \
      , ::boost::parameter::optional<keyword::tag::_IsUndoable> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1,T2,T3>::type \
//
#endif  // BOOST_AUTOMATA_AUTOMATON_ARGS
#endif  // __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__

#define BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(_args, _keyword) \
    typename ::boost::parameter::value_type< \
        _args \
      , keyword::tag::_keyword \
    >::type \
//

#define BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(_args, _keyword, _default) \
    typename ::boost::parameter::value_type< \
        _args \
      , keyword::tag::_keyword \
      , _default \
    >::type \
//
//->

    template <
//<-
#ifdef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
//->
        typename Function
//<-
#else  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
        typename T0
#endif  // __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
//->
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    class function_automaton
      : public  // Base
        //<-
        _detail::impl<
            deterministic_generator
#ifdef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
          , adaptor_transition_function<Function>
#else  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
          , adaptor_transition_function<
                BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(
                    BOOST_AUTOMATA_AUTOMATON_ARGS
                  , _Function
                )
            >
#endif  // __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
          , BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(
                BOOST_AUTOMATA_AUTOMATON_ARGS
              , _Policies
              , ::boost::fusion::nil
            )
          , BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(
                BOOST_AUTOMATA_AUTOMATON_ARGS
              , _InputValidationPolicy
              , default_input_validation_policy
            )
          , BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(
                BOOST_AUTOMATA_AUTOMATON_ARGS
              , _IsUndoable
              , ::boost::mpl::false_
            )
        >::type
        //->
    {
        //<-
        typedef BOOST_AUTOMATA_AUTOMATON_ARGS
                Args;
#ifndef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
        typedef BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(
                    Args
                  , _Function
                )
                Function;
#endif  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
        typedef BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(
                    Args
                  , _Policies
                  , ::boost::fusion::nil
                )
                Policies;
        typedef BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(
                    Args
                  , _InputValidationPolicy
                  , default_input_validation_policy
                )
                InputValidationPolicy;
        typedef BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM(
                    Args
                  , _IsUndoable
                  , ::boost::mpl::false_
                )
                IsUndoable;
        typedef typename _detail::impl<
                    deterministic_generator
                  , adaptor_transition_function<Function>
                  , Policies
                  , InputValidationPolicy
                  , IsUndoable
                >::type
                Base;
        //->

     public:
        typedef typename Base::transition_function
                transition_function;
        typedef typename Base::state
                state;
        typedef typename Base::observer_map
                observer_map;
        typedef typename Base::traits
                traits;

        function_automaton() : Base()
        {
        }

        //<-
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
     private:
        typedef ::std::tr1::is_same<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , Policies
                >
                PoliciesPredicate;
        typedef ::std::tr1::is_same<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , InputValidationPolicy
                >
                InputValidationPredicate;
        typedef ::std::tr1::is_convertible< ::boost::mpl::_,state>
                StatePredicate;
        typedef ::std::tr1::is_integral<
                    ::boost::detail::data_type< ::boost::mpl::_>
                >
                UndoLimitPredicate;

#ifdef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
     public:
        BOOST_PARAMETER_CONSTRUCTOR(
            function_automaton, (Base), keyword::tag,
            (required
                (function, *)
            )
            (deduced
                (optional
                    (policies, *(PoliciesPredicate))
                    (input_validation_policy, *(InputValidationPredicate))
                    (source_state, *(StatePredicate))
                    (undo_limit, *(UndoLimitPredicate))
                )
            )
        )
#else  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
        typedef ::std::tr1::is_same<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , Function
                >
                FunctionPredicate;

     public:
        BOOST_PARAMETER_CONSTRUCTOR(
            function_automaton, (Base), keyword::tag,
            (deduced
                (required
                    (function, *(FunctionPredicate))
                )
                (optional
                    (policies, *(PoliciesPredicate))
                    (input_validation_policy, *(InputValidationPredicate))
                    (source_state, *(StatePredicate))
                    (undo_limit, *(UndoLimitPredicate))
                )
            )
        )
#endif  // __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
#else  // !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
#ifdef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
        //->
        BOOST_PARAMETER_CONSTRUCTOR(
            function_automaton, (Base), keyword::tag,
            (required
                (function
                  , *
                )
            )
            (deduced
                (optional
                    (policies
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Policies
                            >
                        )
                    )
                    (input_validation_policy
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , InputValidationPolicy
                            >
                        )
                    )
                    (source_state
                      , *(::std::tr1::is_convertible< ::boost::mpl::_,state>)
                    )
                    (undo_limit
                      , *(
                            ::std::tr1::is_integral<
                                ::boost::detail::data_type< ::boost::mpl::_>
                            >
                        )
                    )
                )
            )
        )
        //<-
#else  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
        BOOST_PARAMETER_CONSTRUCTOR(
            function_automaton, (Base), keyword::tag,
            (deduced
                (required
                    (function
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Function
                            >
                        )
                    )
                )
                (optional
                    (policies
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Policies
                            >
                        )
                    )
                    (input_validation_policy
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , InputValidationPolicy
                            >
                        )
                    )
                    (source_state
                      , *(::std::tr1::is_convertible< ::boost::mpl::_,state>)
                    )
                    (undo_limit
                      , *(
                            ::std::tr1::is_integral<
                                ::boost::detail::data_type< ::boost::mpl::_>
                            >
                        )
                    )
                )
            )
        )
#endif  // __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
#endif  // BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
        //->

        function_automaton(function_automaton const& copy)
          : Base(static_cast<Base const&>(copy))
        {
        }

        //<-
        inline
        //->
        function_automaton& operator=(function_automaton const& copy)
        //<-
        {
            if (this != &copy)
            {
                Base::operator=(static_cast<Base const&>(copy));
            }

            return *this;
        }
        //->
        ;

        //<-
        inline
        //->
        function_automaton& operator=(state const& source_state)
        //<-
        {
            Base::operator=(source_state);
            return *this;
        }
        //->
        ;

        template <typename TFunction>
        //<-
        inline
        //->
        function_automaton& operator=(TFunction f)
        //<-
        {
            Base::operator=(f);
            return *this;
        }
        //->
        ;
    };

//<-
#undef BOOST_AUTOMATA_AUTOMATON_OPTIONAL_TPL_PARAM
#undef BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM
#undef BOOST_AUTOMATA_AUTOMATON_ARGS
//->

}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_FUNCTION_AUTOMATON_HPP_INCLUDED

