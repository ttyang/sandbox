// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_AUTOMATON_HPP_INCLUDED
#define BOOST_AUTOMATA_AUTOMATON_HPP_INCLUDED

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
#include <boost/automata/policy/default_input_validation.hpp>
#include <boost/automata/_detail/impl.hpp>

//[reference__automaton
namespace boost { namespace automata {

//<-
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#define BOOST_AUTOMATA_AUTOMATON_ARGS \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_BaseGenerator> \
      , ::boost::parameter::required<keyword::tag::_Function> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
      , ::boost::parameter::optional<keyword::tag::_InputValidationPolicy> \
      , ::boost::parameter::optional<keyword::tag::_IsUndoable> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1,T2,T3,T4,parameter::void_>::type \
//
#else
#define BOOST_AUTOMATA_AUTOMATON_ARGS \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_BaseGenerator> \
      , ::boost::parameter::required<keyword::tag::_Function> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
      , ::boost::parameter::optional<keyword::tag::_InputValidationPolicy> \
      , ::boost::parameter::optional<keyword::tag::_IsUndoable> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1,T2,T3,T4>::type \
//
#endif

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
        typename T0
      , typename T1
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
    >
    class automaton
      : public  // Base
        //<-
        _detail::impl<
            BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(
                BOOST_AUTOMATA_AUTOMATON_ARGS
              , _BaseGenerator
            )
          , BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(
                BOOST_AUTOMATA_AUTOMATON_ARGS
              , _Function
            )
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
        typedef BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(
                    Args
                  , _BaseGenerator
                )
                BaseGenerator;
        typedef BOOST_AUTOMATA_AUTOMATON_REQUIRED_TPL_PARAM(
                    Args
                  , _Function
                )
                Function;
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
                    BaseGenerator
                  , Function
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

        automaton() : Base()
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

     public:
        BOOST_PARAMETER_CONSTRUCTOR(
            automaton, (Base), keyword::tag,
            (deduced
                (required
                    (builder, *)
                )
                (optional
                    (policies, *(PoliciesPredicate))
                    (input_validation_policy, *(InputValidationPredicate))
                    (source_state, *(StatePredicate))
                    (undo_limit, *(UndoLimitPredicate))
                )
            )
        )
#else  // !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
        //->
        BOOST_PARAMETER_CONSTRUCTOR(
            automaton, (Base), keyword::tag,
            (required
                (builder
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
#endif  // BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
        //->

        automaton(automaton const& copy)
          : Base(static_cast<Base const&>(copy))
        {
        }

        //<-
        inline
        //->
        automaton& operator=(automaton const& copy)
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
        automaton& operator=(state const& source_state)
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
        automaton& operator=(TFunction f)
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

#endif  // BOOST_AUTOMATA_AUTOMATON_HPP_INCLUDED

