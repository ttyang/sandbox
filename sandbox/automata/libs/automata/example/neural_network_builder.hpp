// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_BUILDER_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_BUILDER_HPP_INCLUDED

#include <vector>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

//[example__neural_network_builder__fwd_decl
namespace example {

    struct neural_network_transition_function_tag;
    //]

    //[example__neural_network_builder
    template <typename Inputs, typename Outputs>
    class neural_network_builder
    {
        Inputs const&     _inputs;
        Outputs const&    _outputs;
        double const      _learning_rate;
        std::size_t const _sample_count;

     public:
        neural_network_builder(
            Inputs const& inputs
          , Outputs const& outputs
          , std::size_t const sample_count
          , double const learning_rate
        ) : _inputs(inputs)
          , _outputs(outputs)
          , _learning_rate(learning_rate)
          , _sample_count(sample_count)
        {
        }

        template <typename Function>
        void operator()(Function& function) const
        {
            BOOST_STATIC_ASSERT((
                boost::is_same<
                    typename Function::tag
                  , neural_network_transition_function_tag
                >::value
            ));
            function.reset(_inputs, _outputs, _sample_count, _learning_rate);
        }
    };
}  // namespace example
//]

#endif  // LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_BUILDER_HPP_INCLUDED

