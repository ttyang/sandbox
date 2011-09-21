// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_TOTALISTIC_DT_CELL_HPP_INC
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_TOTALISTIC_DT_CELL_HPP_INC

#include <utility>
#include <boost/config.hpp>
#include <boost/parameter.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/range.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/automata/transition_function/decision_tree.hpp>

//[reference__totalistic_dfa_cell_transition_function
namespace boost { namespace automata {

    template <
        typename T0
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    class totalistic_dt_cell_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_State>
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
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , ::boost::parameter::void_
#endif
                >::type
                Args;
        //->

     public:
        typedef transition_function_tag
                tag;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_State
                >::type
                //->
                state;
        typedef bool
                result_type;

        //<-
     private:
        BOOST_STATIC_ASSERT((::std::tr1::is_integral<state>::value));
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
        typedef decision_tree_explicit_transition_function<
                    state
                  , state
                  , state
                  , AssociativeContainerSelector
                  , RandomAccessContainerSelector
                >
                Function;

     public:
        //->
        typedef typename Function::builder
                builder;

        //<-
     private:
        Function _function;
        state    _state_key;

     public:
        //->
        totalistic_dt_cell_transition_function();

        totalistic_dt_cell_transition_function(
            totalistic_dt_cell_transition_function const& copy
        );

        totalistic_dt_cell_transition_function&
            operator=(totalistic_dt_cell_transition_function const& copy);

        template <typename Input>
        result_type operator()(state& current_state, Input const& i) const;

        void reset();

        builder add_transitions(state const& state_key);

     private:
        template <typename Iterator>
        result_type
            _process_input(
                state& current_state
              , Iterator itr
              , Iterator itr_end
            ) const;
    };

    //<-
    template <typename T0, typename T1, typename T2>
    totalistic_dt_cell_transition_function<
        T0
      , T1
      , T2
    >::totalistic_dt_cell_transition_function() : _function(), _state_key()
    {
    }

    template <typename T0, typename T1, typename T2>
    totalistic_dt_cell_transition_function<
        T0
      , T1
      , T2
    >::totalistic_dt_cell_transition_function(
        totalistic_dt_cell_transition_function const& copy
    ) : _function(copy._function), _state_key(copy._state_key)
    {
    }

    template <typename T0, typename T1, typename T2>
    inline totalistic_dt_cell_transition_function<T0,T1,T2>&
        totalistic_dt_cell_transition_function<T0,T1,T2>::operator=(
            totalistic_dt_cell_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _function  = copy._function;
            _state_key = copy._state_key;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2>
    template <typename Input>
    inline typename totalistic_dt_cell_transition_function<
        T0
      , T1
      , T2
    >::result_type
        totalistic_dt_cell_transition_function<T0,T1,T2>::operator()(
            state& current_state
          , Input const& i
        ) const
    {
        return _process_input(
            current_state
          , ::boost::begin(i)
          , ::boost::end(i)
        );
    }

    template <typename T0, typename T1, typename T2>
    template <typename Iterator>
    typename totalistic_dt_cell_transition_function<T0,T1,T2>::result_type
        totalistic_dt_cell_transition_function<T0,T1,T2>::_process_input(
            state& current_state
          , Iterator itr
          , Iterator itr_end
        ) const
    {
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , state
                  , state
                >::type
                InputMap;

        InputMap input_map;
        typename InputMap::iterator in_itr;

        for (
            input_map.insert(
                typename InputMap::value_type(_state_key, current_state)
            );
            itr != itr_end;
            ++itr
        )
        {
            in_itr = input_map.find(*itr);

            if (in_itr == input_map.end())
            {
                input_map.insert(typename InputMap::value_type(*itr, 1));
            }
            else
            {
                ++in_itr->second;
            }
        }

        return _function(current_state, input_map);
    }

    template <typename T0, typename T1, typename T2>
    inline void totalistic_dt_cell_transition_function<T0,T1,T2>::reset()
    {
        _function.reset();
    }

    template <typename T0, typename T1, typename T2>
    inline typename totalistic_dt_cell_transition_function<T0,T1,T2>::builder
        totalistic_dt_cell_transition_function<T0,T1,T2>::add_transitions(
            state const& state_key
        )
    {
        return _function.add_transitions(_state_key = state_key);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_TOTALISTIC_DT_CELL_HPP_INC

