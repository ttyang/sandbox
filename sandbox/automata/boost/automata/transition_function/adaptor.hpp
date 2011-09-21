// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_ADAPTOR_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_ADAPTOR_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/assert.hpp>

//[reference__adaptor_transition_function
namespace boost { namespace automata {

    template <typename Function>
    class adaptor_transition_function;

    template <typename F, typename Arg>
    class adaptor_transition_function<F(Arg)>
    {
     public:
        typedef combinatorial_transition_function_tag
                tag;
        typedef typename ::std::tr1::function<F(Arg)>::result_type
                result_type;
        typedef result_type
                state;

        //<-
     private:
        ::std::tr1::function<F(Arg)> _function;
        ::std::tr1::function<bool(Arg const&)> _input_recognizer;

     public:
        //->
        adaptor_transition_function()
        //<-
          : _function(), _input_recognizer()
        {
        }
        //->
        ;

        template <typename Function>
        adaptor_transition_function(Function function)
        //<-
          : _function(function), _input_recognizer()
        {
        }
        //->
        ;

        adaptor_transition_function(adaptor_transition_function const& copy)
        //<-
          : _function(copy._function)
          , _input_recognizer(copy._input_recognizer)
        {
        }
        //->
        ;

        //<-
        inline
        //->
        adaptor_transition_function&
            operator=(adaptor_transition_function const& copy)
        //<-
        {
            if (this != &copy)
            {
                _function = copy._function;
                _input_recognizer = copy._input_recognizer;
            }

            return *this;
        }
        //->
        ;

        template <typename Input>
        //<-
        inline
        //->
        bool recognizes_input(Input const& i) const
        //<-
        {
            return _input_recognizer ? _input_recognizer(i) : true;
        }
        //->
        ;

        template <typename Input>
        //<-
        inline
        //->
        result_type operator()(Input const& i) const
        //<-
        {
            return _function(i);
        }
        //->
        ;

        template <typename InputRecognizer>
        //<-
        inline
        //->
        void set_input_recognizer(InputRecognizer input_recognizer)
        //<-
        {
            _input_recognizer = input_recognizer;
        }
        //->
        ;

        template <typename F1, typename A1, typename F2, typename A2>
        //<-
        inline
        //->
        friend bool
            operator==(
                adaptor_transition_function<F1(A1)> const& lhs
              , adaptor_transition_function<F2(A2)> const& rhs
            )
        //<-
        {
            return lhs._function == rhs._function;
        }
        //->
        ;

        template <typename F1, typename A1, typename F2, typename A2>
        //<-
        inline
        //->
        friend bool
            operator!=(
                adaptor_transition_function<F1(A1)> const& lhs
              , adaptor_transition_function<F2(A2)> const& rhs
            )
        //<-
        {
            return lhs._function != rhs._function;
        }
        //->
        ;
    };

    template <typename F, typename Arg1, typename Arg2>
    class adaptor_transition_function<F(Arg1,Arg2)>
    {
        struct error__state_must_be_convertible_to_either_argument;

     public:
        typedef transition_function_tag
                tag;
        typedef typename ::std::tr1::function<F(Arg1,Arg2)>::result_type
                result_type;
        typedef result_type
                state;

     private:
        // typedef implementation_defined Arg1_Data;
        // typedef implementation_defined Arg2_Data;
        // typedef implementation_defined Is_State_Convertible_To_Arg1;
        //<-
        typedef typename ::boost::detail::data_type<Arg1>::type
                Arg1_Data;
        typedef typename ::boost::detail::data_type<Arg2>::type
                Arg2_Data;
        typedef typename ::std::tr1::is_convertible<state,Arg1_Data>::type
                Is_State_Convertible_To_Arg1;
        //->

     public:
        typedef state
                first_argument_type;
        typedef typename ::boost::mpl::eval_if<
                    Is_State_Convertible_To_Arg1
                  , ::boost::mpl::identity<Arg2_Data>
                  , ::boost::mpl::eval_if<
                        ::std::tr1::is_convertible<state,Arg2_Data>
                      , ::boost::mpl::identity<Arg1_Data>
                      , error__state_must_be_convertible_to_either_argument
                    >
                >::type
                second_argument_type;

        //<-
     private:
        ::std::tr1::function<F(Arg1,Arg2)>
            _function;
        ::std::tr1::function<bool(first_argument_type const&)>
            _state_recognizer;
        ::std::tr1::function<bool(second_argument_type const&)>
            _input_recognizer;

     public:
        //->
        adaptor_transition_function()
        //<-
          : _function(), _state_recognizer(), _input_recognizer()
        {
        }
        //->
        ;

        template <typename Function>
        adaptor_transition_function(Function function)
        //<-
          : _function(function), _state_recognizer(), _input_recognizer()
        {
        }
        //->
        ;

        adaptor_transition_function(adaptor_transition_function const& copy)
        //<-
          : _function(copy._function)
          , _state_recognizer(copy._state_recognizer)
          , _input_recognizer(copy._input_recognizer)
        {
        }
        //->
        ;

        //<-
        inline
        //->
        adaptor_transition_function&
            operator=(adaptor_transition_function const& copy)
        //<-
        {
            if (this != &copy)
            {
                _function = copy._function;
                _state_recognizer = copy._state_recognizer;
                _input_recognizer = copy._input_recognizer;
            }

            return *this;
        }
        //->
        ;

        //<-
        inline
        //->
        bool recognizes_input(second_argument_type const& i) const
        //<-
        {
            return _input_recognizer ? _input_recognizer(i) : true;
        }
        //->
        ;

        //<-
        inline
        //->
        bool recognizes_state(first_argument_type const& s) const
        //<-
        {
            return _state_recognizer ? _state_recognizer(s) : true;
        }
        //->
        ;

        //<-
        inline
        //->
        result_type
            operator()(
                first_argument_type const& current_state
              , second_argument_type const& i
            ) const
        //<-
        {
            BOOST_ASSERT(recognizes_state(current_state));
            BOOST_ASSERT(recognizes_input(i));

            return _evaluate(current_state, i, Is_State_Convertible_To_Arg1());
        }
        //->
        ;

        template <typename InputRecognizer>
        //<-
        inline
        //->
        void set_input_recognizer(InputRecognizer input_recognizer)
        //<-
        {
            _input_recognizer = input_recognizer;
        }
        //->
        ;

        template <typename StateRecognizer>
        //<-
        inline
        //->
        void set_state_recognizer(StateRecognizer state_recognizer)
        //<-
        {
            _state_recognizer = state_recognizer;
        }
        //->
        ;

        //<-
     private:
        inline state
            _evaluate(
                first_argument_type const& current_state
              , second_argument_type const& i
              , ::std::tr1::true_type
            ) const
        {
            return _function(current_state, i);
        }

        inline state
            _evaluate(
                first_argument_type const& current_state
              , second_argument_type const& i
              , ::std::tr1::false_type
            ) const
        {
            return _function(i, current_state);
        }
        //->

        template <
            typename F1
          , typename A1_1
          , typename A1_2
          , typename F2
          , typename A2_1
          , typename A2_2
        >
        //<-
        inline
        //->
        friend bool
            operator==(
                adaptor_transition_function<F1(A1_1,A1_2)> const& lhs
              , adaptor_transition_function<F2(A2_1,A2_2)> const& rhs
            )
        //<-
        {
            return lhs._function == rhs._function;
        }
        //->
        ;

        template <
            typename F1
          , typename A1_1
          , typename A1_2
          , typename F2
          , typename A2_1
          , typename A2_2
        >
        //<-
        inline
        //->
        friend bool
            operator!=(
                adaptor_transition_function<F1(A1_1,A1_2)> const& lhs
              , adaptor_transition_function<F2(A2_1,A2_2)> const& rhs
            )
        //<-
        {
            return lhs._function != rhs._function;
        }
        //->
        ;
    };
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_ADAPTOR_HPP_INCLUDED

