// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_GENERATOR_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_GENERATOR_HPP_INCLUDED

#include <algorithm>
#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/range.hpp>
#include <boost/automata/tags/base.hpp>
#include <boost/automata/concept_check.hpp>

//[example__neural_network_generator__preamble
namespace example {

    struct neural_network_generator
    {
        template <typename Function>
        struct apply
        {
            //]
            //[example__neural_network_generator__concept_check
            BOOST_CONCEPT_ASSERT((
                boost::RandomAccessContainer<typename Function::input>
            ));
            BOOST_CONCEPT_ASSERT((
                boost::Sequence<typename Function::input>
            ));
            BOOST_CONCEPT_ASSERT((
                boost::automata::ConstrainedInputTransitionFunction<
                    Function
                  , typename Function::input
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::automata::StateRegisterTransitionFunction<Function>
            ));
            //]

            //[example__neural_network_generator__typedefs
            class type
            {
             protected:
                typedef boost::automata::automaton_base_tag tag;

                struct traits
                {
                    typedef typename Function::output output;
                };
                //]

                //[example__neural_network_generator__private
             private:
                BOOST_STATIC_ASSERT((
                    boost::is_same<
                        typename Function::input
                      , typename traits::output
                    >::value
                ));
                BOOST_STATIC_ASSERT((
                    boost::is_same<
                        typename traits::output::value_type
                      , double
                    >::value
                ));

                typename traits::output _current_output;
                //]

                //[example__neural_network_generator__ctors
             protected:
                type() : _current_output(Function::state_count)
                {
                }
                //]

                //[example__neural_network_generator__input_start
                bool
                    process_input_impl(
                        Function const& function
                      , typename Function::state& current_state
                      , typename Function::input const& in
                    )
                {
                    function.feed_forward(in, _current_output);
                    //]
                    //[example__neural_network_generator__input_max
                    current_state = std::distance(
                        boost::begin(_current_output)
                      , std::max_element(
                            boost::begin(_current_output)
                          , boost::end(_current_output)
                        )
                    );
                    //]
                    //[example__neural_network_generator__input_return
                    return true;
                }
                //]

                //[example__neural_network_generator__accessors
             public:
                inline typename traits::output const&
                    get_current_output() const
                {
                    return _current_output;
                }
            };
        };
    };
}  // namespace example
//]

#endif  // LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_GENERATOR_HPP_INCLUDED

