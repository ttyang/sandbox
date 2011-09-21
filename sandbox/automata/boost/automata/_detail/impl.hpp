// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA__DETAIL_IMPL_HPP_INCLUDED
#define BOOST_AUTOMATA__DETAIL_IMPL_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/parameter.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
#include <boost/functional/value_factory.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/map/convert.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/detail/metafunction/is_adaptable_unary_function.hpp>
#include <boost/detail/metafunction/is_adaptable_binary_function.hpp>
#include <boost/detail/metafunction/is_n_ary_function.hpp>
#include <boost/detail/metafunction/unary_argument.hpp>
#include <boost/automata/_detail/memento.hpp>
#include <boost/automata/_detail/extensible_memento.hpp>
#include <boost/automata/tags/base.hpp>
#include <boost/automata/tags/builder.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/automata/keyword/name.hpp>

namespace boost { namespace automata { namespace _detail {

    template <typename Builder, typename State>
    struct builder_argument_tester
      : ::std::tr1::is_same<
            typename ::boost::detail::data_type<
                typename ::boost::detail::unary_argument<Builder>::type
            >::type
          , State
        >
    {
    };

    template <typename Builder, typename State>
    struct builder_dispatch_helper
    {
        typedef typename ::boost::mpl::if_<
                    typename ::boost::mpl::if_<
                        ::boost::mpl::or_<
                            ::boost::detail::is_n_ary_function<
                                Builder
                              , ::std::tr1::integral_constant<unsigned int,1>
                            >
                          , ::boost::detail::is_adaptable_unary_function<
                                Builder
                            >
                        >
                      , builder_argument_tester<Builder,State>
                      , ::std::tr1::false_type
                    >::type
                  , state_builder_tag
                  , function_builder_tag
                >::type
                type;
    };

    // This metafunction determines which of the base constructors
    // the impl::type argument pack constructor should delegate to.
    template <typename Builder, typename State>
    struct builder_dispatch
    {
        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_same<Builder,::boost::mpl::void_>
                  , ::boost::mpl::identity<function_setter_tag>
                  , ::boost::mpl::eval_if<
                        ::boost::mpl::or_<
                            ::boost::detail::is_n_ary_function<
                                Builder
                              , ::std::tr1::integral_constant<unsigned int,2>
                            >
                          , ::boost::detail::is_adaptable_binary_function<
                                Builder
                            >
                        >
                      , ::boost::mpl::identity<state_and_function_builder_tag>
                      , builder_dispatch_helper<Builder,State>
                    >
                >::type
                type;
    };

    // This function object class allows the automaton's default and copy
    // constructors to call the on_construction() member function of each
    // associated AutomatonObserver.
    struct observer_on_construction_dispatch
    {
        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_construction();
        }
    };

    // This function object class allows the automaton's argument-pack
    // constructors to call the on_construction() tag-dispatched member
    // function of each associated AutomatonObserver.
    template <typename Builder, typename Tag>
    class observer_on_arg_pack_construction_dispatch
    {
        Builder const& _builder;

     public:
        explicit observer_on_arg_pack_construction_dispatch(
            Builder const& builder
        ) : _builder(builder)
        {
        }

        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_construction(_builder, Tag());
        }
    };

    // This function object class allows the automaton's initialize() methods
    // to call the on_initialize() member function of each associated
    // AutomatonObserver.
    template <typename Builder, typename Tag>
    class observer_on_initialize_dispatch
    {
        Builder const& _builder;

     public:
        explicit observer_on_initialize_dispatch(Builder const& builder)
          : _builder(builder)
        {
        }

        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_initialize(_builder, Tag());
        }
    };

    // This function object class allows the automaton's reset() method to call
    // the on_reset() member function of each associated AutomatonObserver.
    struct observer_on_reset_dispatch
    {
        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_reset();
        }
    };

    // This function object class template allows the automaton's function
    // call operator to call the on_accept_input() member function of each
    // associated AutomatonObserver.
    template <typename Input>
    class observer_on_accept_input_dispatch
    {
        Input const& _input;

     public:
        observer_on_accept_input_dispatch(Input const& i) : _input(i)
        {
        }

        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_accept_input(_input);
        }
    };

    // This function object class template allows the automaton's function
    // call operator to call the on_reject_input() member function of each
    // associated AutomatonObserver.
    template <typename Input>
    class observer_on_reject_input_dispatch
    {
        Input const& _input;

     public:
        observer_on_reject_input_dispatch(Input const& i) : _input(i)
        {
        }

        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_reject_input(_input);
        }
    };

    // This function object class template allows the automaton's function
    // call operator to call the on_invalid_input() member function of each
    // associated AutomatonObserver.
    template <typename Input>
    class observer_on_invalid_input_dispatch
    {
        Input const& _input;

     public:
        observer_on_invalid_input_dispatch(Input const& i) : _input(i)
        {
        }

        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_invalid_input(_input);
        }
    };

    // This function object class allows the automaton's undo() method to call
    // the on_accept_undo() member function of each associated
    // AutomatonObserver.
    struct observer_on_accept_undo_dispatch
    {
        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_accept_undo();
        }
    };

    // This function object class allows the automaton's undo() method to call
    // the on_reject_undo() member function of each associated
    // AutomatonObserver.
    struct observer_on_reject_undo_dispatch
    {
        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            pair.second.on_reject_undo();
        }
    };

    // The function object class templates responsible for creating the actual
    // policy maps must inherit from this base class template in order to
    // possess the nested result struct template, and also because the result
    // sequences need to be assignable to the _observers member variable.
    template <typename SubjectAutomaton>
    struct observer_maker
    {
        template <typename T>
        struct result;

        template <typename ObserverMaker, typename Key>
        struct result<ObserverMaker(Key)>
        {
            typedef ::boost::fusion::pair<
                        typename ::boost::detail::data_type<Key>::type
                      , typename ::boost::mpl::apply_wrap1<
                            typename ::boost::detail::data_type<Key>::type
                          , SubjectAutomaton
                        >::type
                    >
                    type;
        };

        // Fortunately, this base class template doesn't need to define a
        // virtual templated function call operator, which is illegal anyway.
    };

    // This function object class template is used by the default constructor
    // and the argument pack constructors to create the policy map.
    template <typename SubjectAutomaton>
    class observer_default_maker : public observer_maker<SubjectAutomaton>
    {
        SubjectAutomaton const& _subject_automaton;

     public:
        explicit observer_default_maker(SubjectAutomaton const& automaton)
          : _subject_automaton(automaton)
        {
        }

        template <typename Key>
        inline ::boost::fusion::pair<
            Key
          , typename ::boost::mpl::apply_wrap1<Key,SubjectAutomaton>::type
        >
            operator()(Key const& key) const
        {
            return ::boost::fusion::pair<
                Key
              , typename ::boost::mpl::apply_wrap1<Key,SubjectAutomaton>::type
            >(
                typename ::boost::mpl::apply_wrap1<Key,SubjectAutomaton>::type(
                    key
                  , _subject_automaton
                )
            );
        }
    };

    // This function object class template is used by the copy constructor
    // to create the policy map.
    template <typename SubjectAutomaton>
    class observer_copy_maker : public observer_maker<SubjectAutomaton>
    {
        SubjectAutomaton const& _copy;
        SubjectAutomaton const& _subject_automaton;

     public:
        observer_copy_maker(
            SubjectAutomaton const& copy
          , SubjectAutomaton const& automaton
        ) : _copy(copy), _subject_automaton(automaton)
        {
        }

        template <typename Key>
        inline ::boost::fusion::pair<
            Key
          , typename ::boost::mpl::apply_wrap1<Key,SubjectAutomaton>::type
        >
            operator()(Key const& key) const
        {
            return ::boost::fusion::pair<
                Key
              , typename ::boost::mpl::apply_wrap1<Key,SubjectAutomaton>::type
            >(
                typename ::boost::mpl::apply_wrap1<Key,SubjectAutomaton>::type(
                    ::boost::fusion::at_key<Key>(_copy.get_observer_map())
                  , _subject_automaton
                )
            );
        }
    };

    // This function object class template is used to invoke
    // the assignment operator of each observer in the policy map.
    template <typename ObserverMap>
    class observer_map_assign
    {
        ObserverMap& _observer_map;

     public:
        explicit observer_map_assign(ObserverMap& map) : _observer_map(map)
        {
        }

        template <typename FusionPair>
        inline void operator()(FusionPair& pair) const
        {
            ::boost::fusion::at_key<typename FusionPair::first_type>(
                _observer_map
            ) = pair.second;
        }
    };

    template <
        typename BaseGenerator
      , typename Function
      , typename Policies
      , typename InputValidationPolicy
      , typename IsUndoable
    >
    struct impl
    {
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
     private:
#endif  // MSVC 7.1 and earlier
        BOOST_CONCEPT_ASSERT((TransitionFunction<Function>));

        typedef typename ::boost::mpl::apply_wrap1<
                    BaseGenerator
                  , Function
                >::type
                Ancestor;

// Macros are evil, but the alternative here is massive code duplication.
#define BOOST_AUTOMATA_IMPL_ARG_DATA_TYPE(Tag) \
        typename ::boost::parameter::value_type< \
            ArgumentPack \
          , keyword::tag::Tag \
        >::type \
//

#define BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder) \
        typename builder_dispatch_helper< \
            typename ::boost::detail::data_type< \
                Builder \
            >::type \
          , typename Function::state  \
        >::type \
//

        class Base : public Ancestor
        {
            Function                                           _function;
            typename Function::state                           _current_state;
            ::boost::function1<void,typename Function::state&> _state_builder;

         protected:
            typedef typename Ancestor::tag    tag;
            typedef typename Ancestor::traits traits;

            inline Base()
              : Ancestor()
              , _function()
              , _current_state()
              , _state_builder(
                    ::boost::lambda::_1 = typename Function::state()
                )
            {
            }

            template <typename TFunction>
            inline Base(
                TFunction function
              , typename Function::state const& source_state
              , function_setter_tag
            ) : Ancestor()
              , _function(function)
              , _current_state(source_state)
              , _state_builder(::boost::lambda::_1 = source_state)
            {
            }

            template <typename FunctionBuilder>
            inline Base(
                FunctionBuilder builder
              , typename Function::state const& source_state
              , function_builder_tag
            ) : Ancestor()
              , _function()
              , _current_state(source_state)
              , _state_builder(::boost::lambda::_1 = source_state)
            {
                ::boost::function1<void,Function&> build_function = builder;
                build_function(_function);
            }

            template <typename StateBuilder>
            inline Base(
                StateBuilder builder
              , typename Function::state const& source_state
              , state_builder_tag
            ) : Ancestor()
              , _function()
              , _current_state(source_state)
              , _state_builder(builder)
            {
                _state_builder(_current_state);
            }

            template <typename Builder>
            inline Base(
                Builder builder
              , typename Function::state const& source_state
              , state_and_function_builder_tag
            ) : Ancestor()
              , _function()
              , _current_state(source_state)
              , _state_builder(::boost::bind(builder, _1, _function))
            {
                _state_builder(_current_state);
            }

         public:
            Base(Base const& copy)
              : Ancestor(static_cast<Ancestor const&>(copy))
              , _function(copy._function)
              , _current_state(copy._current_state)
              , _state_builder(copy._state_builder)
            {
            }

            inline Base& operator=(Base const& copy)
            {
                Ancestor::operator=(static_cast<Ancestor const&>(copy));
                _function      = copy._function;
                _current_state = copy._current_state;
                _state_builder = copy._state_builder;
                return *this;
            }

         protected:
            inline void reset_impl()
            {
                _state_builder(_current_state);
                Ancestor::reset_impl();
            }

            template <typename Input>
            inline bool process_input_impl(Input const& i)
            {
                return Ancestor::process_input_impl(
                    get_transition_function()
                  , _current_state
                  , i
                );
            }

            template <typename Builder>
            inline void initialize_impl(Builder builder)
            {
                this->_initialize_impl(
                    builder
                  , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder)()
                );
            }

            template <typename Builder>
            inline void
                initialize_impl(
                    Builder builder
                  , typename Function::state const& source_state
                )
            {
                this->set_source_state(source_state);
                this->_initialize_impl(
                    builder
                  , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder)()
                );
            }

            inline void
                set_source_state(typename Function::state const& source_state)
            {
                _state_builder = (boost::lambda::_1 = source_state);
            }

         private:
            template <typename TFunction>
            inline void
                _initialize_impl(TFunction function, function_setter_tag)
            {
                _function = function;
            }

            template <typename Builder>
            inline void
                _initialize_impl(
                    Builder builder
                  , function_builder_tag
                )
            {
                ::boost::function1<void,Function&> build_function = builder;
                build_function(_function);
            }

            template <typename Builder>
            inline void
                _initialize_impl(Builder builder, state_builder_tag)
            {
                _state_builder = builder;
            }

            template <typename Builder>
            inline void
                _initialize_impl(
                    Builder builder
                  , state_and_function_builder_tag
                )
            {
                _state_builder = ::boost::bind(builder, _1, _function);
            }

         public:
            inline Function const& get_transition_function() const
            {
                return _function;
            }

            inline typename Function::state const& get_current_state() const
            {
                return _current_state;
            }

            template <typename Input>
            inline bool is_nontrivial_input(Input const& i) const
            {
                return Ancestor::is_nontrivial_input_impl(
                    get_transition_function()
                  , get_current_state()
                  , i
                );
            }

            template <typename Iterator>
            inline void
                make_nontrivial_inputs(Iterator itr) const
            {
                Ancestor::make_nontrivial_inputs_impl(
                    get_transition_function()
                  , _current_state
                  , itr
                );
            }
        };

// The transition function should be stored in a wrapper derived from the Base
// class instead of within the Base class itself, where it may be all too easy
// for the process_input_impl method, which is non-const (as well as the
// reset_impl method) to modify the transition function by mistake.
#define BOOST_AUTOMATA_IMPL_ANY_TYPE_PREAMBLE(Type) \
            typedef Function \
                    transition_function; \
            typedef typename Function::state \
                    state; \
            typedef typename Base::traits \
                    traits; \
         private: \
            typedef typename ::boost::mpl::apply_wrap1< \
                        InputValidationPolicy \
                      , Type \
                    >::type \
                    InputChecker; \
            InputChecker _input_validator; \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_PREAMBLE(Type) \
         public: \
            typedef ::boost::fusion::nil \
                    observer_map; \
            BOOST_AUTOMATA_IMPL_ANY_TYPE_PREAMBLE(Type) \
//

// The _policies member variable is used only by the constructors.  Its
// presence is mandatory for the copy constructor to work correctly,
// even though the _observers member variable holds all the necessary
// information.
//
// No other member functions should access the elements of the _policies
// member variable, since it may become a dangling reference once the regular
// constructor has finished execution.  The copy constructor needs only the
// corresponding type of each element.
#define BOOST_AUTOMATA_IMPL_EXT_TYPE_PREAMBLE(Type) \
         public: \
            BOOST_AUTOMATA_IMPL_ANY_TYPE_PREAMBLE(Type) \
         public: \
            typedef typename ::boost::fusion::result_of::as_map< \
                        typename ::boost::fusion::result_of::transform< \
                            Policies \
                          , observer_maker<Type> \
                        >::type \
                    >::type \
                    observer_map; \
         private: \
            observer_map    _observers; \
            Policies const& _policies; \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_DEFAULT_CTOR_HEAD(Type) \
            Type() \
              : Base() \
              , _input_validator(InputValidationPolicy(), *this) \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_DEFAULT_CTOR_HEAD(Type) \
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_DEFAULT_CTOR_HEAD(Type) \
              , _observers( \
                    ::boost::fusion::as_map( \
                        ::boost::fusion::transform( \
                            _policies \
                          , observer_default_maker<Type>(*this) \
                        ) \
                    ) \
                ) \
              , _policies(Policies()) \
//

#define BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_FUNC_CTOR_HEAD(Type) \
            template <typename ArgumentPack> \
            Type(ArgumentPack const& args, ::std::tr1::true_type) \
              : Base( \
                    args[::boost::automata::keyword::_function] \
                  , args[ \
                        ::boost::automata::keyword::_source_state \
                     || value_factory<state>() \
                    ] \
                  , function_setter_tag() \
                ) \
//

#define BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_BUILDER_CTOR_HEAD(Type) \
            template <typename ArgumentPack> \
            Type(ArgumentPack const& args, ::std::tr1::false_type) \
              : Base( \
                    args[::boost::automata::keyword::_builder] \
                  , args[ \
                        ::boost::automata::keyword::_source_state \
                     || value_factory<state>() \
                    ] \
                  , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE( \
                        BOOST_AUTOMATA_IMPL_ARG_DATA_TYPE(builder) \
                    )() \
                ) \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX \
              , _input_validator( \
                    args[ \
                        ::boost::automata::keyword::_input_validation_policy \
                     || value_factory<InputValidationPolicy>() \
                    ] \
                  , *this \
                ) \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX(Type) \
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX \
              , _observers( \
                    ::boost::fusion::as_map( \
                        ::boost::fusion::transform( \
                            args[ \
                                ::boost::automata::keyword::_policies \
                             || value_factory<Policies>() \
                            ] \
                          , observer_default_maker<Type>(*this) \
                        ) \
                    ) \
                ) \
              , _policies( \
                    args[ \
                        ::boost::automata::keyword::_policies \
                     || value_factory<Policies>() \
                    ] \
                ) \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_COPY_CTOR_HEAD(Type) \
            Type(Type const& copy) \
              : Base(static_cast<Base const&>(copy)) \
              , _input_validator(copy._input_validator, *this) \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_COPY_CTOR_HEAD(Type) \
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_COPY_CTOR_HEAD(Type) \
              , _observers( \
                    ::boost::fusion::as_map( \
                        ::boost::fusion::transform( \
                            copy._policies \
                          , observer_copy_maker<Type>(copy, *this) \
                        ) \
                    ) \
                ) \
              , _policies(copy._policies) \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_CTOR \
                _input_validator.on_construction(); \
                ::boost::fusion::for_each( \
                    _observers \
                  , observer_on_construction_dispatch() \
                ); \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR(Tag) \
                typedef BOOST_AUTOMATA_IMPL_ARG_DATA_TYPE(Tag) Builder; \
                _input_validator.on_construction( \
                    args[::boost::automata::keyword::BOOST_PP_CAT(_, Tag)] \
                  , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder)() \
                ); \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_ARG_CTOR(Tag) \
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR(Tag) \
                ::boost::fusion::for_each( \
                    _observers \
                  , observer_on_arg_pack_construction_dispatch< \
                        Builder \
                      , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder) \
                    >(args[::boost::automata::keyword::BOOST_PP_CAT(_, Tag)]) \
                ); \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ASSIGNABLE \
                Base::operator=(static_cast<Base const&>(copy)); \
                _input_validator = copy._input_validator; \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_ASSIGNABLE \
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ASSIGNABLE \
                ::boost::fusion::for_each( \
                    copy.get_observer_map() \
                  , observer_map_assign<observer_map>(_observers) \
                ); \
//

#define BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT \
                _input_validator.on_initialize( \
                    builder \
                  , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder)() \
                ); \
//

#define BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT \
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT \
                ::boost::fusion::for_each( \
                    _observers \
                  , observer_on_initialize_dispatch< \
                        Builder \
                      , BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE(Builder) \
                    >(builder) \
                ); \
//

#define BOOST_AUTOMATA_IMPL_ANY_TYPE_ASSIGN_OPS(Type) \
            inline Type& operator=(state const& source_state) \
            { \
                this->set_source_state(source_state); \
                reset(); \
                return *this; \
            } \
//

#define BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_PROCESS_INPUT \
            template <typename Input> \
            inline bool operator()(Input const& i) \
            { \
                return \
                    _process_input( \
                        i \
                      , typename ::std::tr1::is_base_of< \
                            discrete_automaton_base_tag \
                          , typename Base::tag \
                        >::type() \
                    ); \
            } \
//

#define BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_ACCESS \
            inline typename memento<Base>::size_type get_undo_limit() const \
            { \
                return _memento.get_save_limit(); \
            } \
            inline bool can_undo() const \
            { \
                return _memento.can_restore(); \
            } \
//

        class ext_type : public Base
        {
            BOOST_AUTOMATA_IMPL_EXT_TYPE_PREAMBLE(ext_type)

         protected:
            BOOST_AUTOMATA_IMPL_EXT_TYPE_DEFAULT_CTOR_HEAD(ext_type)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_CTOR
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_FUNC_CTOR_HEAD(ext_type)
            BOOST_AUTOMATA_IMPL_EXT_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX(ext_type)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_ARG_CTOR(function)
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_BUILDER_CTOR_HEAD(ext_type)
            BOOST_AUTOMATA_IMPL_EXT_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX(ext_type)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_ARG_CTOR(builder)
            }

            BOOST_AUTOMATA_IMPL_EXT_TYPE_COPY_CTOR_HEAD(ext_type)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_CTOR
            }

            ext_type& operator=(ext_type const& copy)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_ASSIGNABLE
                return *this;
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ASSIGN_OPS(ext_type)

         public:
            template <typename Builder>
            inline void initialize(Builder builder)
            {
                initialize_impl(builder);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(Builder builder, state const& source_state)
            {
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(state const& source_state, Builder builder)
            {
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
            }

            inline observer_map const& get_observer_map() const
            {
                return _observers;
            }

            inline void reset()
            {
                this->reset_impl();
                ::boost::fusion::for_each(
                    _observers
                  , observer_on_reset_dispatch()
                );
            }

            template <typename Input>
            inline bool operator()(Input const& i)
            {
                if (_input_validator(i))
                {
                    if (this->process_input_impl(i))
                    {
                        ::boost::fusion::for_each(
                            _observers
                          , observer_on_accept_input_dispatch<Input>(i)
                        );
                        return true;
                    }
                    else
                    {
                        ::boost::fusion::for_each(
                            _observers
                          , observer_on_reject_input_dispatch<Input>(i)
                        );
                        return false;
                    }
                }
                else
                {
                    ::boost::fusion::for_each(
                        _observers
                      , observer_on_invalid_input_dispatch<Input>(i)
                    );
                    return false;
                }
            }
        };

        class undo_ext_type : public Base
        {
            BOOST_AUTOMATA_IMPL_EXT_TYPE_PREAMBLE(undo_ext_type)
            extensible_memento<Base,observer_map> _memento;

         protected:
            BOOST_AUTOMATA_IMPL_EXT_TYPE_DEFAULT_CTOR_HEAD(undo_ext_type)
              , _memento()
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_CTOR
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_FUNC_CTOR_HEAD(
                undo_ext_type
            )
            BOOST_AUTOMATA_IMPL_EXT_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX(
                undo_ext_type
            )
              , _memento(
                    args[
                        ::boost::automata::keyword::_undo_limit
                      | ::std::size_t()
                    ]
                )
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_ARG_CTOR(function)
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_BUILDER_CTOR_HEAD(
                undo_ext_type
            )
            BOOST_AUTOMATA_IMPL_EXT_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX(
                undo_ext_type
            )
              , _memento(
                    args[
                        ::boost::automata::keyword::_undo_limit
                      | ::std::size_t()
                    ]
                )
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_ARG_CTOR(builder)
            }

            BOOST_AUTOMATA_IMPL_EXT_TYPE_COPY_CTOR_HEAD(undo_ext_type)
              , _memento(copy._memento)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_CTOR
            }

            undo_ext_type& operator=(undo_ext_type const& copy)
            {
                BOOST_AUTOMATA_IMPL_EXT_TYPE_ASSIGNABLE
                _memento = copy._memento;
                return *this;
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ASSIGN_OPS(undo_ext_type)

         public:
            template <typename Builder>
            inline void initialize(Builder builder)
            {
                _memento.clear();
                initialize_impl(builder);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(Builder builder, state const& source_state)
            {
                _memento.clear();
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(state const& source_state, Builder builder)
            {
                _memento.clear();
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
            }

            inline observer_map const& get_observer_map() const
            {
                return _observers;
            }

            inline void reset()
            {
                _memento.clear();
                this->reset_impl();
                ::boost::fusion::for_each(
                    _observers
                  , observer_on_reset_dispatch()
                );
            }

         private:
            template <typename Input>
            inline bool _process_input(Input const& i, ::std::tr1::true_type)
            {
                if (_input_validator(i))
                {
                    if (is_nontrivial_input(i))
                    {
                        _memento.save(*this, get_observer_map());
                        Base::process_input_impl(i);
                        ::boost::fusion::for_each(
                            _observers
                          , observer_on_accept_input_dispatch<Input>(i)
                        );
                        return true;
                    }
                    else
                    {
                        ::boost::fusion::for_each(
                            _observers
                          , observer_on_reject_input_dispatch<Input>(i)
                        );
                        return false;
                    }
                }
                else
                {
                    ::boost::fusion::for_each(
                        _observers
                      , observer_on_invalid_input_dispatch<Input>(i)
                    );
                    return false;
                }
            }

            template <typename Input>
            inline bool _process_input(Input const& i, ::std::tr1::false_type)
            {
                if (_input_validator(i))
                {
                    _memento.save(*this, get_observer_map());

                    if (Base::process_input_impl(i))
                    {
                        ::boost::fusion::for_each(
                            _observers
                          , observer_on_accept_input_dispatch<Input>(i)
                        );
                        return true;
                    }
                    else
                    {
                        ::boost::fusion::for_each(
                            _observers
                          , observer_on_reject_input_dispatch<Input>(i)
                        );
                        return false;
                    }
                }
                else
                {
                    ::boost::fusion::for_each(
                        _observers
                      , observer_on_invalid_input_dispatch<Input>(i)
                    );
                    return false;
                }
            }

         public:
            BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_PROCESS_INPUT

            BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_ACCESS

            inline void undo()
            {
                if (can_undo())
                {
                    _memento.restore(*this, _observers);
                    ::boost::fusion::for_each(
                        _observers
                      , observer_on_accept_undo_dispatch()
                    );
                }
                else
                {
                    ::boost::fusion::for_each(
                        _observers
                      , observer_on_reject_undo_dispatch()
                    );
                }
            }
        };

        class plain_type : public Base
        {
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_PREAMBLE(plain_type)

         protected:
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_DEFAULT_CTOR_HEAD(plain_type)
            {
                _input_validator.on_construction();
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_FUNC_CTOR_HEAD(
                plain_type
            )
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX
            {
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR(function)
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_BUILDER_CTOR_HEAD(
                plain_type
            )
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX
            {
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR(builder)
            }

            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_COPY_CTOR_HEAD(plain_type)
            {
                _input_validator.on_construction();
            }

            inline plain_type& operator=(plain_type const& copy)
            {
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ASSIGNABLE
                return *this;
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ASSIGN_OPS(plain_type)

         public:
            template <typename Builder>
            inline void initialize(Builder builder)
            {
                initialize_impl(builder);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(Builder builder, state const& source_state)
            {
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(state const& source_state, Builder builder)
            {
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
            }

            inline void reset()
            {
                this->reset_impl();
            }

            template <typename Input>
            inline bool operator()(Input const& i)
            {
                return (
                    _input_validator(i)
                 && this->process_input_impl(i)
                );
            }
        };

        class undo_plain_type : public Base
        {
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_PREAMBLE(undo_plain_type)
            memento<Base> _memento;

         protected:
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_DEFAULT_CTOR_HEAD(undo_plain_type)
              , _memento()
            {
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_FUNC_CTOR_HEAD(
                undo_plain_type
            )
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX
              , _memento(
                    args[
                        ::boost::automata::keyword::_undo_limit
                      | ::std::size_t()
                    ]
                )
            {
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR(function)
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_BUILDER_CTOR_HEAD(
                undo_plain_type
            )
            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX
              , _memento(
                    args[
                        ::boost::automata::keyword::_undo_limit
                      | ::std::size_t()
                    ]
                )
            {
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR(builder)
            }

            BOOST_AUTOMATA_IMPL_PLAIN_TYPE_COPY_CTOR_HEAD(undo_plain_type)
              , _memento(copy._memento)
            {
            }

            inline undo_plain_type& operator=(undo_plain_type const& copy)
            {
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ASSIGNABLE
                _memento = copy._memento;
                return *this;
            }

            BOOST_AUTOMATA_IMPL_ANY_TYPE_ASSIGN_OPS(undo_plain_type)

         public:
            template <typename Builder>
            inline void initialize(Builder builder)
            {
                _memento.clear();
                initialize_impl(builder);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(Builder builder, state const& source_state)
            {
                _memento.clear();
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
            }

            template <typename Builder>
            inline void
                initialize(state const& source_state, Builder builder)
            {
                _memento.clear();
                initialize_impl(builder, source_state);
                this->reset_impl();
                BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
            }

            inline void reset()
            {
                _memento.clear();
                this->reset_impl();
            }

         private:
            template <typename Input>
            inline bool _process_input(Input const& i, ::std::tr1::true_type)
            {
                if (_input_validator(i) && is_nontrivial_input(i))
                {
                    _memento.save(*this);
                    this->process_input_impl(i);
                    return true;
                }
                else
                {
                    return false;
                }
            }

            template <typename Input>
            inline bool _process_input(Input const& i, ::std::tr1::false_type)
            {
                if (_input_validator(i))
                {
                    _memento.save(*this);
                    return this->process_input_impl(i);
                }
                else
                {
                    return false;
                }
            }

         public:
            BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_PROCESS_INPUT

            BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_ACCESS

            inline void undo()
            {
                if (can_undo())
                {
                    _memento.restore(*this);
                }
            }
        };

        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::result_of::empty<Policies>::type
                  , ::boost::mpl::if_<
                        IsUndoable
                      , undo_plain_type
                      , plain_type
                    >
                  , ::boost::mpl::if_<
                        IsUndoable
                      , undo_ext_type
                      , ext_type
                    >
                >::type
                Base0;

     public:
        struct type : public Base0
        {
            typedef typename Base0::transition_function
                    transition_function;
            typedef typename Base0::state
                    state;
            typedef typename Base0::traits
                    traits;
            typedef typename Base0::observer_map
                    observer_map;

         protected:
            type() : Base0()
            {
            }

         public:
            template <typename ArgumentPack>
            type(ArgumentPack const& args)
              : Base0(
                    args
                  , ::std::tr1::is_same<
                        typename ::boost::parameter::value_type<
                            ArgumentPack
                          , ::boost::automata::keyword::tag::builder
                          , ::boost::mpl::void_
                        >::type
                      , boost::mpl::void_
                    >()
                )
            {
            }

         protected:
            type(type const& copy) : Base0(static_cast<Base0 const&>(copy))
            {
            }

            inline type& operator=(type const& copy)
            {
                Base0::operator=(static_cast<Base0 const&>(copy));
                return *this;
            }

            inline type& operator=(state const& src_state)
            {
                Base0::operator=(src_state);
                return *this;
            }

            template <typename TFunction>
            inline type& operator=(TFunction f)
            {
                Base0::initialize(f);
                return *this;
            }
        };

#undef BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_ACCESS
#undef BOOST_AUTOMATA_IMPL_UNDOABLE_TYPE_PROCESS_INPUT
#undef BOOST_AUTOMATA_IMPL_ANY_TYPE_ASSIGN_OPS
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_INIT
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_INIT
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_ASSIGNABLE
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ASSIGNABLE
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_ARG_CTOR
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_OBSERVERS_ON_ARG_CTOR
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_OBSERVERS_ON_CTOR
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_COPY_CTOR_HEAD
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_COPY_CTOR_HEAD
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_ARG_PACK_CTOR_HEAD_SUFFIX
#undef BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_BUILDER_CTOR_HEAD
#undef BOOST_AUTOMATA_IMPL_ANY_TYPE_ARG_PACK_W_FUNC_CTOR_HEAD
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_DEFAULT_CTOR_HEAD
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_DEFAULT_CTOR_HEAD
#undef BOOST_AUTOMATA_IMPL_EXT_TYPE_PREAMBLE
#undef BOOST_AUTOMATA_IMPL_PLAIN_TYPE_PREAMBLE
#undef BOOST_AUTOMATA_IMPL_ANY_TYPE_PREAMBLE
#undef BOOST_AUTOMATA_IMPL_BUILDER_TAG_TYPE
#undef BOOST_AUTOMATA_IMPL_ARG_DATA_TYPE
    };
}}}  // namespace boost::automata::_detail

#endif  // BOOST_AUTOMATA__DETAIL_IMPL_HPP_INCLUDED

