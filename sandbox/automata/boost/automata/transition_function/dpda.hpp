// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_DPDA_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_DPDA_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 4)
#error Set BOOST_PARAMETER_MAX_ARITY to 4 or more.
#endif

#include <map>
#include <boost/type_traits/is_same.hpp>
#include <boost/optional/optional.hpp>
//#include <boost/fusion/sequence/comparison/less.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keys/common.hpp>
#include <boost/automata/keys/dpda.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/assert.hpp>

//[reference__dpda_transition_function
namespace boost { namespace automata {
  //<-
  namespace _detail {

    template <typename InputMap>
    struct deterministic_pushdown_less
    {
        typedef bool                result_type;
        typedef InputMap const&     first_argument_type;
        typedef first_argument_type second_argument_type;

        result_type
            operator()(
                first_argument_type arg1
              , second_argument_type arg2
            ) const;
    };

    template <typename InputMap>
    inline typename deterministic_pushdown_less<InputMap>::result_type
        deterministic_pushdown_less<InputMap>::operator()(
            first_argument_type arg1
          , second_argument_type arg2
        ) const
    {
        return (
            (
                ::boost::fusion::at_key<input_symbol_key>(arg1)
              < ::boost::fusion::at_key<input_symbol_key>(arg2)
            )
         || (
                (
                    ::boost::fusion::at_key<input_symbol_key>(arg1)
                 == ::boost::fusion::at_key<input_symbol_key>(arg2)
                )
             && (
                    ::boost::fusion::at_key<pop_from_stack_key>(arg1)
                  < ::boost::fusion::at_key<pop_from_stack_key>(arg2)
                )
            )
        );
    }
  }  // namespace _detail
  //->

    template <
        typename T0
      , typename T1
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    class dpda_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_Input>
                  , ::boost::parameter::required<keyword::tag::_StackElement>
                  , ::boost::parameter::optional<
                        keyword::tag::_AssociativeContainerSelector
                    >
                  , ::boost::parameter::optional<
                        keyword::tag::_RandomAccessContainerSelector
                    >
                >::BOOST_NESTED_TEMPLATE bind<
                    T0
                  , T1
                  , T2
                  , T3
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , boost::parameter::void_
#endif
                >::type
                Args;
        //->

     public:
        typedef dpda_transition_function_tag
                tag;
        typedef ::std::size_t
                state;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_Input
                >::type
                //->
                input;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_StackElement
                >::type
                //->
                stack_element;

        //<-
     private:
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AssociativeContainerSelector
                  , ::boost::mapS
                >::type
                AssociativeContainerSelector;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_RandomAccessContainerSelector
                  , ::boost::vecS
                >::type
                RandomAccessContainerSelector;
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , input
                >::type
                InputSet;
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , stack_element
                >::type
                StackElements;

     public:
        //->
        typedef ::boost::optional<stack_element>
                optional_stack_element;

     private:
        typedef ::boost::fusion::pair<next_state_key,state>
                NextState;
        typedef ::boost::fusion::pair<push_to_stack_key,optional_stack_element>
                StackPush;

     public:
        typedef ::boost::fusion::map<NextState,StackPush>
                result_map;

     private:
        // typedef implementation_defined Result;
        //<-
        typedef ::boost::optional<result_map>
                Result;
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , input
                  , Result
                >::type
                TransitionMap1;
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , TransitionMap1
                >::type
                Transitions1;
        typedef ::boost::fusion::map<
                    ::boost::fusion::pair<input_symbol_key,input>
                  , ::boost::fusion::pair<pop_from_stack_key,stack_element>
                >
                InputMap;
        typedef ::std::map<
                    InputMap
                  , Result
                  , _detail::deterministic_pushdown_less<InputMap>
                >
                TransitionMap2;
        typedef typename container_gen<
                    RandomAccessContainerSelector
                  , TransitionMap2
                >::type
                Transitions2;
        //->
        // typedef implementation_defined Setter1;
        // typedef implementation_defined Setter2;

     public:
        typedef Result const& result_type;

        //<-
     private:
        class Setter1
        {
            dpda_transition_function& _function;
            state const& _current_state;
            input const& _i;

         public:
            Setter1(
                dpda_transition_function& f
              , state const& current_state
              , input const& i
            );

            void operator=(result_map const& result);
        };

        class Setter2
        {
            dpda_transition_function& _function;
            state const& _current_state;
            input const& _i;
            stack_element const& _e;

         public:
            Setter2(
                dpda_transition_function& f
              , state const& current_state
              , input const& i
              , stack_element const& e
            );

            void operator=(result_map const& result);
        };

        static Result const _null_state;

        InputSet      _inputs;
        StackElements _stack_elements;
        Transitions1  _transitions_1;
        Transitions2  _transitions_2;

     public:
        //->
        dpda_transition_function();

        dpda_transition_function(dpda_transition_function const& copy);

        dpda_transition_function&
            operator=(dpda_transition_function const& copy);

        ::std::size_t get_state_count() const;

        bool recognizes_input(input const& i) const;

        bool recognizes_state(state const& s) const;

        bool recognizes_stack_element(stack_element const& e) const;

        result_type
            operator()(state const& current_state, input const& i) const;

        result_type
            operator()(
                state const& current_state
              , input const& i
              , stack_element const& e
            ) const;

        template <typename Iterator>
        void
            make_nontrivial_inputs(
                state const& current_state
              , Iterator itr
            ) const;

        template <typename Iterator>
        void
            make_nontrivial_inputs(
                state const& current_state
              , stack_element const& e
              , Iterator itr
            ) const;

        void
            set_transition(
                state const& current_state
              , input const& i
              , result_map const& result
            );

        Setter1 operator()(state const& current_state, input const& i);

        void
            set_transition(
                state const& current_state
              , input const& i
              , stack_element const& e
              , result_map const& result
            );

        Setter2
            operator()(
                state const& current_state
              , input const& i
              , stack_element const& e
            );

        void reset(::std::size_t state_count);

        //<-
        template <
            typename T0_
          , typename T1_
          , typename T2_
          , typename T3_
          , typename T4_
          , typename T5_
          , typename T6_
          , typename T7_
        >
        friend bool
            operator==(
                dpda_transition_function<T0_,T1_,T2_,T3_> const& lhs
              , dpda_transition_function<T4_,T5_,T6_,T7_> const& rhs
            );
        //->
    };

    //<-
    template <typename T0, typename T1, typename T2, typename T3>
    typename dpda_transition_function<T0,T1,T2,T3>::Result const
        dpda_transition_function<T0,T1,T2,T3>::_null_state = Result();

    template <typename T0, typename T1, typename T2, typename T3>
    dpda_transition_function<T0,T1,T2,T3>::dpda_transition_function()
      : _inputs(), _stack_elements(), _transitions_1(), _transitions_2()
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    dpda_transition_function<T0,T1,T2,T3>::dpda_transition_function(
        dpda_transition_function const& copy
    ) : _inputs(copy._inputs)
      , _stack_elements(copy._stack_elements)
      , _transitions_1(copy._transitions_1)
      , _transitions_2(copy._transitions_2)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    dpda_transition_function<T0,T1,T2,T3>&
        dpda_transition_function<T0,T1,T2,T3>::operator=(
            dpda_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _inputs         = copy._inputs;
            _stack_elements = copy._stack_elements;
            _transitions_1  = copy._transitions_1;
            _transitions_2  = copy._transitions_2;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline ::std::size_t
        dpda_transition_function<T0,T1,T2,T3>::get_state_count() const
    {
        return _transitions_1.size();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        dpda_transition_function<T0,T1,T2,T3>::recognizes_input(
            input const& i
        ) const
    {
        return _inputs.find(i) != _inputs.end();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        dpda_transition_function<T0,T1,T2,T3>::recognizes_state(
            state const& s
        ) const
    {
        return s < _transitions_1.size();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline bool
        dpda_transition_function<T0,T1,T2,T3>::recognizes_stack_element(
            stack_element const& e
        ) const
    {
        return _stack_elements.find(e) != _stack_elements.end();
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline typename dpda_transition_function<T0,T1,T2,T3>::result_type
        dpda_transition_function<T0,T1,T2,T3>::operator()(
            state const& current_state
          , input const& i
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));

        TransitionMap1 const& t_map = _transitions_1[current_state];
        typename TransitionMap1::const_iterator map_itr = t_map.find(i);
        return (map_itr == t_map.end()) ? _null_state : map_itr->second;
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline typename dpda_transition_function<T0,T1,T2,T3>::result_type
        dpda_transition_function<T0,T1,T2,T3>::operator()(
            state const& current_state
          , input const& i
          , stack_element const& e
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_input(i));
        BOOST_ASSERT(recognizes_stack_element(e));

        TransitionMap2 const&
            t_map = _transitions_2[current_state];
        typename TransitionMap2::const_iterator
            map_itr = t_map.find(InputMap(i, e));
        return (map_itr == t_map.end()) ? _null_state : map_itr->second;
    }

    template <typename T0, typename T1, typename T2, typename T3>
    template <typename Iterator>
    void
        dpda_transition_function<T0,T1,T2,T3>::make_nontrivial_inputs(
            state const& current_state
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));

        TransitionMap1 const& t_map = _transitions_1[current_state];
        typename TransitionMap1::const_iterator map_end = t_map.end();

        for (
            typename TransitionMap1::const_iterator map_itr = t_map.begin();
            map_itr != map_end;
            ++map_itr
        )
        {
            *itr = map_itr->first;
            ++itr;
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    template <typename Iterator>
    void
        dpda_transition_function<T0,T1,T2,T3>::make_nontrivial_inputs(
            state const& current_state
          , stack_element const& e
          , Iterator itr
        ) const
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(recognizes_stack_element(e));

        TransitionMap2 const& t_map = _transitions_2[current_state];
        typename TransitionMap2::const_iterator map_end = t_map.end();

        for (
            typename TransitionMap2::const_iterator map_itr = t_map.begin();
            map_itr != map_end;
            ++map_itr
        )
        {
            if (
                ::boost::fusion::at_key<pop_from_stack_key>(map_itr->first)
             == e
            )
            {
                *itr = boost::fusion::at_key<input_symbol_key>(map_itr->first);
                ++itr;
            }
        }
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline void
        dpda_transition_function<T0,T1,T2,T3>::set_transition(
            state const& current_state
          , input const& i
          , result_map const& result
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(
            recognizes_state(::boost::fusion::at_key<next_state_key>(result))
        );

        _inputs.insert(i);

        if (
            optional_stack_element const& o_e = ::boost::fusion::at_key<
                push_to_stack_key
            >(result)
        )
        {
            _stack_elements.insert(*o_e);
        }

        _transitions_1[current_state][i] = Result(result);
    }

    template <typename T0, typename T1, typename T2, typename T3>
    dpda_transition_function<T0,T1,T2,T3>::Setter1::Setter1(
        dpda_transition_function& f
      , state const& current_state
      , input const& i
    ) : _function(f), _current_state(current_state), _i(i)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    void
        dpda_transition_function<T0,T1,T2,T3>::Setter1::operator=(
            result_map const& result
        )
    {
        _function.set_transition(_current_state, _i, result);
    }

    template <typename T0, typename T1, typename T2, typename T3>
    typename dpda_transition_function<T0,T1,T2,T3>::Setter1
        dpda_transition_function<T0,T1,T2,T3>::operator()(
            state const& current_state
          , input const& i
        )
    {
        return Setter1(*this, current_state, i);
    }

    template <typename T0, typename T1, typename T2, typename T3>
    inline void
        dpda_transition_function<T0,T1,T2,T3>::set_transition(
            state const& current_state
          , input const& i
          , stack_element const& e
          , result_map const& result
        )
    {
        BOOST_ASSERT(recognizes_state(current_state));
        BOOST_ASSERT(
            recognizes_state(::boost::fusion::at_key<next_state_key>(result))
        );

        _inputs.insert(i);
        _stack_elements.insert(e);

        if (
            optional_stack_element const& o_e = ::boost::fusion::at_key<
                push_to_stack_key
            >(result)
        )
        {
            _stack_elements.insert(*o_e);
        }

        _transitions_2[current_state][InputMap(i, e)] = Result(result);
    }

    template <typename T0, typename T1, typename T2, typename T3>
    dpda_transition_function<T0,T1,T2,T3>::Setter2::Setter2(
        dpda_transition_function& f
      , state const& current_state
      , input const& i
      , stack_element const& e
    ) : _function(f), _current_state(current_state), _i(i), _e(e)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3>
    void
        dpda_transition_function<T0,T1,T2,T3>::Setter2::operator=(
            result_map const& result
        )
    {
        _function.set_transition(_current_state, _i, _e, result);
    }

    template <typename T0, typename T1, typename T2, typename T3>
    typename dpda_transition_function<T0,T1,T2,T3>::Setter2
        dpda_transition_function<T0,T1,T2,T3>::operator()(
            state const& current_state
          , input const& i
          , stack_element const& e
        )
    {
        return Setter2(*this, current_state, i, e);
    }

    template <typename T0, typename T1, typename T2, typename T3>
    void
        dpda_transition_function<T0,T1,T2,T3>::reset(::std::size_t state_count)
    {
        _inputs.clear();
        _stack_elements.clear();
        _transitions_1.resize(state_count);
        _transitions_2.resize(state_count);

        while (state_count)
        {
            _transitions_1[--state_count].clear();
            _transitions_2[state_count].clear();
        }
    }
    //->

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename T6
      , typename T7
    >
    bool
        operator==(
            dpda_transition_function<T0,T1,T2,T3> const& lhs
          , dpda_transition_function<T4,T5,T6,T7> const& rhs
        );

    //<-
    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename T6
      , typename T7
    >
    bool
        operator==(
            dpda_transition_function<T0,T1,T2,T3> const& lhs
          , dpda_transition_function<T4,T5,T6,T7> const& rhs
        )
    {
        if (
            !(lhs._inputs.size() == rhs._inputs.size())
         && !(lhs._stack_elements.size() == rhs._stack_elements.size())
         && !(lhs._transitions_1.size() == rhs._transitions_1.size())
        )
        {
            return false;
        }

        typedef typename dpda_transition_function<T0,T1,T2,T3>::InputSet
                LHS_InputSet;
        typedef typename LHS_InputSet::const_iterator
                LHS_InputSetIterator;
        typedef typename dpda_transition_function<T4,T5,T6,T7>::InputSet
                RHS_InputSet;
        typedef typename RHS_InputSet::const_iterator
                RHS_InputSetIterator;

        RHS_InputSetIterator rhs_in_end = rhs._inputs.end();
        LHS_InputSetIterator lhs_in_end = lhs._inputs.end();
        LHS_InputSetIterator lhs_in_itr = lhs._inputs.begin();

        while (lhs_in_itr != lhs_in_end)
        {
            if (rhs._inputs.find(*lhs_in_itr) == rhs_in_end)
            {
                return false;
            }

            ++lhs_in_itr;
        }

        typedef typename dpda_transition_function<T0,T1,T2,T3>::StackElements
                LHS_StackElements;
        typedef typename LHS_StackElements::const_iterator
                LHS_StackElementsIterator;
        typedef typename dpda_transition_function<T4,T5,T6,T7>::StackElements
                RHS_StackElements;
        typedef typename RHS_StackElements::const_iterator
                RHS_StackElementsIterator;

        RHS_StackElementsIterator rhs_se_end = rhs._stack_elements.end();
        LHS_StackElementsIterator lhs_se_end = lhs._stack_elements.end();
        LHS_StackElementsIterator lhs_se_itr = lhs._stack_elements.begin();

        while (lhs_se_itr != lhs_se_end)
        {
            if (rhs._stack_elements.find(*lhs_se_itr) == rhs_se_end)
            {
                return false;
            }

            ++lhs_se_itr;
        }

        typedef typename dpda_transition_function<T0,T1,T2,T3>::TransitionMap1
                LHS_TransitionMap1;
        typedef typename dpda_transition_function<T0,T1,T2,T3>::TransitionMap2
                LHS_TransitionMap2;
        typedef typename LHS_TransitionMap1::const_iterator
                LHS_TransitionMapIterator1;
        typedef typename LHS_TransitionMap2::const_iterator
                LHS_TransitionMapIterator2;
        typedef typename dpda_transition_function<T0,T1,T2,T3>::result_map
                LHS_ResultMap;
        typedef typename dpda_transition_function<
                    T0
                  , T1
                  , T2
                  , T3
                >::optional_stack_element
                LHS_OptionalStackElement;
        typedef typename dpda_transition_function<T4,T5,T6,T7>::TransitionMap1
                RHS_TransitionMap1;
        typedef typename dpda_transition_function<T4,T5,T6,T7>::TransitionMap2
                RHS_TransitionMap2;
        typedef typename RHS_TransitionMap1::const_iterator
                RHS_TransitionMapIterator1;
        typedef typename RHS_TransitionMap2::const_iterator
                RHS_TransitionMapIterator2;
        typedef typename dpda_transition_function<T4,T5,T6,T7>::result_map
                RHS_ResultMap;
        typedef typename dpda_transition_function<
                    T4
                  , T5
                  , T6
                  , T7
                >::optional_stack_element
                RHS_OptionalStackElement;

        LHS_TransitionMapIterator1 lhs_tm1_itr, lhs_tm1_end;
        LHS_TransitionMapIterator2 lhs_tm2_itr, lhs_tm2_end;
        RHS_TransitionMapIterator1 rhs_tm1_itr, rhs_tm1_end;
        RHS_TransitionMapIterator2 rhs_tm2_itr, rhs_tm2_end;
        std::size_t s = lhs._transitions_1.size();

        while (s)
        {
            LHS_TransitionMap1 const& lhs_tm1 = lhs._transitions_1[--s];
            RHS_TransitionMap1 const& rhs_tm1 = rhs._transitions_1[s];
            LHS_TransitionMap2 const& lhs_tm2 = lhs._transitions_2[s];
            RHS_TransitionMap2 const& rhs_tm2 = rhs._transitions_2[s];

            if (
                !(lhs_tm1.size() == rhs_tm1.size())
             || !(lhs_tm2.size() == rhs_tm2.size())
            )
            {
                return false;
            }

            lhs_tm1_end = lhs_tm1.end();
            rhs_tm1_end = rhs_tm1.end();

            for (
                lhs_tm1_itr = lhs_tm1.begin();
                lhs_tm1_itr != lhs_tm1_end;
                ++lhs_tm1_itr
            )
            {
                rhs_tm1_itr = rhs_tm1.find(lhs_tm1_itr->first);

                if (rhs_tm1_itr == rhs_tm1_end)
                {
                    return false;
                }

                LHS_ResultMap const& lhs_r_map = *(lhs_tm1_itr->second);
                RHS_ResultMap const& rhs_r_map = *(rhs_tm1_itr->second);

                if (
                    LHS_OptionalStackElement const&
                        lhs_o_e
                          = ::boost::fusion::at_key<push_to_stack_key>(
                              lhs_r_map
                          )
                )
                {
                    if (
                        RHS_OptionalStackElement const&
                            rhs_o_e
                              = ::boost::fusion::at_key<push_to_stack_key>(
                                    rhs_r_map
                                )
                    )
                    {
                        if (*lhs_o_e != *rhs_o_e)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (::boost::fusion::at_key<push_to_stack_key>(rhs_r_map))
                {
                    return false;
                }
            }

            lhs_tm2_end = lhs_tm2.end();
            rhs_tm2_end = rhs_tm2.end();

            for (
                lhs_tm2_itr = lhs_tm2.begin();
                lhs_tm2_itr != lhs_tm2_end;
                ++lhs_tm2_itr
            )
            {
                rhs_tm2_itr = rhs_tm2.find(lhs_tm2_itr->first);

                if (rhs_tm2_itr == rhs_tm2_end)
                {
                    return false;
                }

                LHS_ResultMap const& lhs_r_map = *(lhs_tm1_itr->second);
                RHS_ResultMap const& rhs_r_map = *(rhs_tm1_itr->second);

                if (
                    LHS_OptionalStackElement const&
                        lhs_o_e
                          = ::boost::fusion::at_key<push_to_stack_key>(
                              lhs_r_map
                          )
                )
                {
                    if (
                        RHS_OptionalStackElement const&
                            rhs_o_e
                              = ::boost::fusion::at_key<push_to_stack_key>(
                                    rhs_r_map
                                )
                    )
                    {
                        if (*lhs_o_e != *rhs_o_e)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (::boost::fusion::at_key<push_to_stack_key>(rhs_r_map))
                {
                    return false;
                }
            }
        }

        return true;
    }
    //->

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename T6
      , typename T7
    >
    bool
        operator!=(
            dpda_transition_function<T0,T1,T2,T3> const& lhs
          , dpda_transition_function<T4,T5,T6,T7> const& rhs
        );

    //<-
    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename T6
      , typename T7
    >
    inline bool
        operator!=(
            dpda_transition_function<T0,T1,T2,T3> const& lhs
          , dpda_transition_function<T4,T5,T6,T7> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_DPDA_HPP_INCLUDED

