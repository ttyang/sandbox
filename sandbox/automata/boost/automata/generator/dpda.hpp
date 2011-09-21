// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_GENERATOR_DPDA_HPP_INCLUDED
#define BOOST_AUTOMATA_GENERATOR_DPDA_HPP_INCLUDED

#include <deque>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/automata/tags/base.hpp>
#include <boost/automata/keys/dpda.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/assert.hpp>

//[reference__dpda_generator
namespace boost { namespace automata {

    struct dpda_generator
    {
        template <typename Function>
        struct apply
        {
            BOOST_CONCEPT_ASSERT((DPDATransitionFunction<Function>));

            class type
            {
                //typedef implementation_defined stack_sequence;
                //<-
                typedef ::std::deque<typename Function::stack_element>
                        stack_sequence;
                //->

             protected:
                typedef input_enumerable_automaton_base_tag tag;

                struct traits
                {
                    typedef typename Function::stack_element
                            stack_element;
                    typedef typename stack_sequence::const_iterator
                            stack_iterator;
                };

                //<-
             private:
                stack_sequence _sequence;

             protected:
                //->
                type();

             public:
                type(type const& copy);

                type& operator=(type const& copy);

                bool has_empty_stack() const;

                //<-
                inline
                //->
                typename traits::stack_element const& get_stack_top() const
                //<-
                {
                    BOOST_ASSERT(!has_empty_stack());
                    return _sequence.back();
                }
                //->
                ;

                //<-
                inline
                //->
                typename traits::stack_iterator get_stack_begin() const
                //<-
                {
                    return _sequence.begin();
                }
                //->
                ;

                //<-
                inline
                //->
                typename traits::stack_iterator get_stack_end() const
                //<-
                {
                    return _sequence.end();
                }
                //->
                ;

             protected:
                void reset_impl();

                template <typename Input>
                bool
                    is_nontrivial_input_impl(
                        Function const& function
                      , typename Function::state const& current_state
                      , Input const& i
                    ) const;

                template <typename Iterator>
                void
                    make_nontrivial_inputs_impl(
                        Function const& function
                      , typename Function::state const& current_state
                      , Iterator itr
                    ) const;

                template <typename Input>
                bool
                    process_input_impl(
                        Function const& function
                      , typename Function::state& current_state
                      , Input const& i
                    );

                //<-
             private:
                bool
                    _process_input(
                        typename Function::state& current_state
                      , typename Function::result_map const& m
                    );

#if 0
                // Not used yet.
                static bool
                    _has_equal_states(type const& lhs, type const& rhs);
#endif  // 0
                //->
            };
        };
    };

    //<-
    template <typename Function>
    dpda_generator::apply<Function>::type::type() : _sequence()
    {
    }

    template <typename Function>
    dpda_generator::apply<Function>::type::type(type const& copy)
      : _sequence(copy._sequence)
    {
    }

    template <typename Function>
    inline typename dpda_generator::BOOST_NESTED_TEMPLATE apply<
        Function
    >::type&
        dpda_generator::apply<Function>::type::operator=(type const& copy)
    {
        _sequence = copy._sequence;
        return *this;
    }

    template <typename Function>
    inline bool dpda_generator::apply<Function>::type::has_empty_stack() const
    {
        return _sequence.empty();
    }

    template <typename Function>
    inline void dpda_generator::apply<Function>::type::reset_impl()
    {
        _sequence.clear();
    }

    template <typename Function>
    template <typename Input>
    inline bool
        dpda_generator::apply<Function>::type::is_nontrivial_input_impl(
            Function const& function
          , typename Function::state const& current_state
          , Input const& i
        ) const
    {
        if (!has_empty_stack())
        {
            if (function(current_state, i, get_stack_top()))
            {
                return true;
            }
        }

        if (function(current_state, i))
        {
            return true;
        }

        return false;
    }

    template <typename Function>
    template <typename Iterator>
    inline void
        dpda_generator::apply<Function>::type::make_nontrivial_inputs_impl(
            Function const& function
          , typename Function::state const& current_state
          , Iterator itr
        ) const
    {
        if (!has_empty_stack())
        {
            function.make_nontrivial_inputs(
                current_state
              , get_stack_top()
              , itr
            );
        }

        function.make_nontrivial_inputs(current_state, itr);
    }

    template <typename Function>
    template <typename Input>
    bool
        dpda_generator::apply<Function>::type::process_input_impl(
            Function const& function
          , typename Function::state& current_state
          , Input const& i
        )
    {
        if (!has_empty_stack())
        {
            if (
                typename Function::result_type r = function(
                    current_state
                  , i
                  , get_stack_top()
                )
            )
            {
                _sequence.pop_back();
                return _process_input(current_state, *r);
            }
        }

        if (typename Function::result_type r = function(current_state, i))
        {
            return _process_input(current_state, *r);
        }

        return false;
    }

    template <typename Function>
    bool
        dpda_generator::apply<Function>::type::_process_input(
            typename Function::state& current_state
          , typename Function::result_map const& m
        )
    {
        current_state = ::boost::fusion::at_key<next_state_key>(m);

        if (
            typename Function::optional_stack_element const&
                o_e = ::boost::fusion::at_key<push_to_stack_key>(m)
        )
        {
            _sequence.push_back(*o_e);
        }

        return true;
    }

#if 0
    // Not used yet.
    template <typename Function>
    bool
        dpda_generator::apply<Function>::type::_has_equal_states(
            type const& lhs
          , type const& rhs
        )
    {
        typename traits::stack_iterator l_end = lhs.get_stack_end();
        typename traits::stack_iterator r_itr = rhs.get_stack_begin();
        typename traits::stack_iterator r_end = rhs.get_stack_end();

        for (
            typename traits::stack_iterator l_itr = lhs.get_stack_begin();
            l_itr != l_end;
            ++l_itr
        )
        {
            if ((r_itr == r_end) || !(*l_itr == *r_itr))
            {
                return false;
            }

            ++r_itr;
        }

        return r_itr == r_end;
    }
#endif  // 0
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_GENERATOR_DPDA_HPP_INCLUDED

