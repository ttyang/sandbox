// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_BUILDER_FUNCTION_HPP_INCLUDED
#define BOOST_AUTOMATA_BUILDER_FUNCTION_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 4)
#error Set BOOST_PARAMETER_MAX_ARITY to 4 or more.
#endif

#include <boost/config.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/functional/value_factory.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/map/convert.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/detail/metafunction/is_predicate.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/automata/keyword/name.hpp>

//[reference__builder_function
namespace boost { namespace automata {
  namespace _detail {

    template <typename Recognizer, typename Argument>
    struct can_recognize_argument_helper
      : ::std::tr1::is_convertible<
            typename ::boost::detail::data_type<
                typename ::boost::function_traits<
                    Recognizer
                >::arg1_type
            >::type
          , Argument
        >
    {
    };

    template <typename Recognizer, typename Argument>
    struct can_recognize_argument
      : ::boost::mpl::eval_if<
            ::boost::detail::is_predicate<Recognizer>
          , can_recognize_argument_helper<Recognizer,Argument>
          , ::std::tr1::false_type
        >::type
    {
    };

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    class function_builder_impl
    {
        Function const& _function;
        StateRecognizer const& _state_recognizer;
        InputRecognizer const& _input_recognizer;

        class observer_builder_maker
        {
            function_builder_impl const& _builder;

         public:
            observer_builder_maker(function_builder_impl const& builder)
              : _builder(builder)
            {
            }

            template <typename T>
            struct result;

            template <typename BuilderMaker, typename T>
            struct result<BuilderMaker(T)>
            {
             private:
                typedef typename ::boost::detail::data_type<T>::type
                        T_data;

             public:
                typedef ::boost::fusion::pair<
                            typename T_data::key_type
                          , typename ::boost::mpl::apply_wrap1<
                                T_data
                              , Function
                            >::type
                        >
                        type;
            };

            template <typename T>
            inline ::boost::fusion::pair<
                typename T::key_type
              , typename ::boost::mpl::apply_wrap1<T,Function>::type
            >
                operator()(T const& t) const
            {
                return ::boost::fusion::pair<
                    typename T::key_type
                  , typename ::boost::mpl::apply_wrap1<T,Function>::type
                >(
                    typename ::boost::mpl::apply_wrap1<T,Function>::type(
                        t
                      , _builder._function
                    )
                );
            }
        };

     public:
        typedef typename ::boost::fusion::result_of::as_map<
                    typename ::boost::fusion::result_of::transform<
                        Policies
                      , observer_builder_maker
                    >::type
                >::type
                observer_builder_map;

     private:
        observer_builder_map _observer_builder_map;

     public:
        function_builder_impl(
            Function const& function
          , StateRecognizer const& state_recognizer
          , InputRecognizer const& input_recognizer
        );

        template <typename ArgumentPack>
        function_builder_impl(ArgumentPack const& args);

        function_builder_impl(function_builder_impl const& copy);

     private:
        template <typename TFunction>
        void
            _build_input_recognizer(
                TFunction& function
              , ::std::tr1::true_type
            ) const;

        template <typename TFunction>
        void
            _build_input_recognizer(
                TFunction& function
              , ::std::tr1::false_type
            ) const;

        template <typename TFunction>
        void
            _build_state_recognizer(
                TFunction& function
              , ::std::tr1::true_type
            ) const;

        template <typename TFunction>
        void
            _build_state_recognizer(
                TFunction& function
              , ::std::tr1::false_type
            ) const;

     public:
        template <typename TFunction>
        void operator()(TFunction& function) const;

        observer_builder_map const& get_observer_builder_map() const;
    };

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    function_builder_impl<
        Function
      , StateRecognizer
      , InputRecognizer
      , Policies
    >::function_builder_impl(
        Function const& function
      , StateRecognizer const& state_recognizer
      , InputRecognizer const& input_recognizer
    ) : _function(function)
      , _state_recognizer(state_recognizer)
      , _input_recognizer(input_recognizer)
    {
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    template <typename ArgumentPack>
    function_builder_impl<
        Function
      , StateRecognizer
      , InputRecognizer
      , Policies
    >::function_builder_impl(ArgumentPack const& args)
      : _function(args[::boost::automata::keyword::_function])
      , _state_recognizer(
            args[
                ::boost::automata::keyword::_state_recognizer
             || value_factory<StateRecognizer>()
            ]
        )
      , _input_recognizer(
            args[
                ::boost::automata::keyword::_input_recognizer
             || value_factory<InputRecognizer>()
            ]
        )
      , _observer_builder_map(
            ::boost::fusion::as_map(
                ::boost::fusion::transform(
                    args[
                        ::boost::automata::keyword::_policies
                     || value_factory<Policies>()
                    ]
                  , observer_builder_maker(*this)
                )
            )
        )
    {
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    function_builder_impl<
        Function
      , StateRecognizer
      , InputRecognizer
      , Policies
    >::function_builder_impl(function_builder_impl const& copy)
      : _function(copy._function)
      , _state_recognizer(copy._state_recognizer)
      , _input_recognizer(copy._input_recognizer)
    {
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    template <typename TFunction>
    inline void
        function_builder_impl<
            Function
          , StateRecognizer
          , InputRecognizer
          , Policies
        >::_build_input_recognizer(
            TFunction& function
          , ::std::tr1::true_type
        ) const
    {
        function.set_input_recognizer(_input_recognizer);
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    template <typename TFunction>
    inline void
        function_builder_impl<
            Function
          , StateRecognizer
          , InputRecognizer
          , Policies
        >::_build_input_recognizer(
            TFunction& function
          , ::std::tr1::false_type
        ) const
    {
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    template <typename TFunction>
    inline void
        function_builder_impl<
            Function
          , StateRecognizer
          , InputRecognizer
          , Policies
        >::_build_state_recognizer(
            TFunction& function
          , ::std::tr1::true_type
        ) const
    {
        function.set_state_recognizer(_state_recognizer);
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    template <typename TFunction>
    inline void
        function_builder_impl<
            Function
          , StateRecognizer
          , InputRecognizer
          , Policies
        >::_build_state_recognizer(
            TFunction& function
          , ::std::tr1::false_type
        ) const
    {
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    template <typename TFunction>
    inline void
        function_builder_impl<
            Function
          , StateRecognizer
          , InputRecognizer
          , Policies
        >::operator()(TFunction& function) const
    {
        function = _function;
        _build_state_recognizer(
            function
          , typename can_recognize_argument<
                StateRecognizer
              , typename TFunction::first_argument_type
            >::type()
        );
        _build_input_recognizer(
            function
          , typename can_recognize_argument<
                InputRecognizer
              , typename TFunction::second_argument_type
            >::type()
        );
    }

    template <
        typename Function
      , typename StateRecognizer
      , typename InputRecognizer
      , typename Policies
    >
    inline typename function_builder_impl<
        Function
      , StateRecognizer
      , InputRecognizer
      , Policies
    >::observer_builder_map const&
        function_builder_impl<
            Function
          , StateRecognizer
          , InputRecognizer
          , Policies
        >::get_observer_builder_map() const
    {
        return _observer_builder_map;
    }
  }  // namespace _detail

#define BOOST_AUTOMATA_BUILDER_ARG_TYPE \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_Function> \
      , ::boost::parameter::optional<keyword::tag::_StateRecognizer> \
      , ::boost::parameter::optional<keyword::tag::_InputRecognizer> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1>::type \
//

#define BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(_args, _keyword) \
    typename ::boost::detail::data_type< \
        typename ::boost::parameter::binding< \
            _args \
          , keyword::tag::_keyword \
        >::type \
    >::type \
//

#define BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(_args, _keyword, _default) \
    typename ::boost::detail::data_type< \
        typename ::boost::parameter::binding< \
            _args \
          , keyword::tag::_keyword \
          , _default \
        >::type \
    >::type \
//

    template <
        typename T0
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    class function_builder
      : public _detail::function_builder_impl<
            BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(
                BOOST_AUTOMATA_BUILDER_ARG_TYPE
              , _Function
            )
          , BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                BOOST_AUTOMATA_BUILDER_ARG_TYPE
              , _StateRecognizer
              , ::boost::parameter::void_
            )
          , BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                BOOST_AUTOMATA_BUILDER_ARG_TYPE
              , _InputRecognizer
              , ::boost::parameter::void_
            )
          , BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                BOOST_AUTOMATA_BUILDER_ARG_TYPE
              , _Policies
              , ::boost::fusion::nil
            )
        >
    {
        typedef BOOST_AUTOMATA_BUILDER_ARG_TYPE
                Args;
        typedef BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(Args, _Function)
                Function;
        typedef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    Args
                  , _StateRecognizer
                  , ::boost::parameter::void_
                )
                StateRecognizer;
        typedef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    Args
                  , _InputRecognizer
                  , ::boost::parameter::void_
                )
                InputRecognizer;
        typedef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    Args
                  , _Policies
                  , ::boost::fusion::nil
                )
                Policies;
        typedef _detail::function_builder_impl<
                    Function
                  , StateRecognizer
                  , InputRecognizer
                  , Policies
                >
                Base;

     public:
        typedef typename Base::observer_builder_map
                observer_builder_map;

        function_builder(Function const& function)
          : Base(static_cast<Function const&>(function))
        {
        }

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
     private:
        typedef ::std::tr1::is_convertible<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , Function
                >
                FunctionPredicate;
        typedef ::std::tr1::is_convertible<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , StateRecognizer
                >
                StateRecognizerPredicate;
        typedef ::std::tr1::is_convertible<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , InputRecognizer
                >
                InputRecognizerPredicate;
        typedef ::std::tr1::is_same<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , Policies
                >
                PoliciesPredicate;

     public:
        BOOST_PARAMETER_CONSTRUCTOR(
            function_builder, (Base), keyword::tag,
            (deduced
                (required
                    (function, *(FunctionPredicate))
                )
                (optional
                    (state_recognizer, *(StateRecognizerPredicate))
                    (input_recognizer, *(InputRecognizerPredicate))
                    (policies, *(PoliciesPredicate))
                )
            )
        )
#else  // !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
        BOOST_PARAMETER_CONSTRUCTOR(
            function_builder, (Base), keyword::tag,
            (deduced
                (required
                    (function
                      , *(
                            ::std::tr1::is_convertible<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Function
                            >
                        )
                    )
                )
                (optional
                    (state_recognizer
                      , *(
                            ::std::tr1::is_convertible<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , StateRecognizer
                            >
                        )
                    )
                    (input_recognizer
                      , *(
                            ::std::tr1::is_convertible<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , InputRecognizer
                            >
                        )
                    )
                    (policies
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Policies
                            >
                        )
                    )
                )
            )
        )
#endif  // ctor

        function_builder(function_builder const& copy)
          : Base(static_cast<Base const&>(copy))
        {
        }
    };

#undef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE
#undef BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE
#undef BOOST_AUTOMATA_BUILDER_ARG_TYPE

}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_BUILDER_FUNCTION_HPP_INCLUDED

