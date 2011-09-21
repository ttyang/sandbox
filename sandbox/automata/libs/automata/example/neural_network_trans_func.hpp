// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_TRANS_FUNC_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_TRANS_FUNC_HPP_INCLUDED

#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#include <boost/tr1/random.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/automata/tags/transition_function.hpp>

//[example__neural_network_trans_func__tag
namespace example {

    struct neural_network_transition_function_tag
      : boost::automata::constrained_input_transition_function_tag
      , boost::automata::state_register_transition_function_tag
    {
    };
    //]

    //[example__neural_network_trans_func__class
    class neural_network_transition_function
    {
        typedef boost::numeric::ublas::matrix<double>  Weights;

     public:
        typedef neural_network_transition_function_tag tag;
        typedef std::vector<double>                    input;
        typedef input                                  output;
        typedef std::size_t                            state;

        BOOST_STATIC_CONSTANT(unsigned long, input_count = 4);
        BOOST_STATIC_CONSTANT(unsigned long, hidden_neuron_count = 3);
        BOOST_STATIC_CONSTANT(unsigned long, state_count = 4);

     private:
        Weights _weights_input2hidden;
        Weights _weights_hidden2output;
        input   _bias_1;
        input   _bias_2;
        //]

        //[example__neural_network_trans_func__ctor
     public:
        neural_network_transition_function()
          : _weights_input2hidden(input_count, hidden_neuron_count)
          , _weights_hidden2output(hidden_neuron_count, state_count)
          , _bias_1(hidden_neuron_count)
          , _bias_2(state_count)
        {
        }
        //]

        //[example__neural_network_trans_func__recognize
        bool recognizes_input(input const& in) const
        {
            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] < 0.0)
                {
                    return false;
                }
            }

            return true;
        }

        inline bool recognizes_state(state const& s) const
        {
            return s < 4;
        }

        inline std::size_t get_state_count() const
        {
            return state_count;
        }
        //]

        //[example__neural_network_trans_func__feed_forward_helpers
     private:
        static double _calculate_sigmoid(double const value)
        {
            using namespace std;
            return 1.0 / (1.0 + exp(-value));
        }

        static double _calculate_sigmoid_derivative(double const value)
        {
            return value * (1.0 - value);
        }
        //]

        //[example__neural_network_trans_func__feed_forward
        template <typename Input, typename Bias, typename Output>
        static void
            _feed_forward(
                Input const& dendrites
              , Weights const& weights
              , Bias const& bias
              , Output& axons
            )
        {
            for (std::size_t j = 0; j < axons.size(); ++j)
            {
                axons[j] = bias[j];

                for (std::size_t i = 0; i < dendrites.size(); ++i)
                {
                    axons[j] += dendrites[i] * weights(i, j);
                }

                axons[j] = _calculate_sigmoid(axons[j]);
            }
        }

     public:
        void feed_forward(input const& in, output& out) const
        {
            input hidden_layer(hidden_neuron_count);

            _feed_forward(in, _weights_input2hidden, _bias_1, hidden_layer);
            _feed_forward(hidden_layer, _weights_hidden2output, _bias_2, out);
        }
        //]

        //[example__neural_network_trans_func__reset_helper
     private:
        template <typename Input, typename Output, typename Bias>
        static void
            _back_propagate(
                Input const& dendrons
              , Output const& error
              , double const learning_rate
              , Weights& weights
              , Bias& bias
            )
        {
            for (std::size_t j = 0; j < bias.size(); ++j)
            {
                for (std::size_t i = 0; i < dendrons.size(); ++i)
                {
                    weights(i, j) += learning_rate * error[j] * dendrons[i];
                }

                bias[j] += learning_rate * error[j];
            }
        }
        //]

        //[example__neural_network_trans_func__reset
     public:
        template <typename Inputs, typename Outputs>
        void
            reset(
                Inputs const& inputs
              , Outputs const& outputs
              , std::size_t sample_count
              , double const learning_rate
            )
        {
            //]
            //[example__neural_network_trans_func__reset__init_rand_weights
            typedef std::tr1::mt19937
                    RNGEngine;
            typedef std::tr1::uniform_real<double>
                    RandomDistribution;
            typedef std::tr1::variate_generator<RNGEngine,RandomDistribution>
                    RandomValue;

            RNGEngine
                rng_engine;
            RandomValue
                random_value(rng_engine, RandomDistribution(-0.5, 0.5));

            using std::time;
            rng_engine.seed(static_cast<unsigned int>(time(0)));

            typename boost::range_iterator<typename Weights::array_type>::type
                weight_itr = boost::begin(_weights_input2hidden.data());
            typename boost::range_iterator<typename Weights::array_type>::type
                weight_end = boost::end(_weights_input2hidden.data());

            while (weight_itr != weight_end)
            {
                *weight_itr = random_value();
                ++weight_itr;
            }

            typename input::iterator bias_itr = _bias_2.begin();
            typename input::iterator bias_end = _bias_2.end();

            while (bias_itr != bias_end)
            {
                *bias_itr = random_value();
                ++bias_itr;
            }

            // Initalize more weightes and biases...
            //]

            weight_end = boost::end(_weights_hidden2output.data());

            for (
                weight_itr = boost::begin(_weights_hidden2output.data());
                weight_itr != weight_end;
                ++weight_itr
            )
            {
                *weight_itr = random_value();
            }

            bias_end = _bias_1.end();

            for (bias_itr = _bias_1.begin(); bias_itr != bias_end; ++bias_itr)
            {
                *bias_itr = random_value();
            }

            //[example__neural_network_trans_func__reset__init_outputs_errors
            input  hidden_layer(hidden_neuron_count);
            output actual_output(state_count);
            output output_error(state_count);
            input  hidden_layer_error(hidden_neuron_count);

            typename boost::range_const_iterator<Inputs>::type const
                inputs_begin = boost::begin(inputs);
            typename boost::range_const_iterator<Inputs>::type const
                inputs_end = boost::end(inputs);
            typename boost::range_const_iterator<Outputs>::type const
                outputs_begin = boost::begin(outputs);
            typename boost::range_const_iterator<Inputs>::type
                inputs_itr = inputs_begin;
            typename boost::range_const_iterator<Outputs>::type
                outputs_itr = outputs_begin;
            //]

            //[example__neural_network_trans_func__reset__start_cycle
            while (sample_count)
            {
                input const& in = *inputs_itr;

                _feed_forward(
                    in
                  , _weights_input2hidden
                  , _bias_1
                  , hidden_layer
                );
                _feed_forward(
                    hidden_layer
                  , _weights_hidden2output
                  , _bias_2
                  , actual_output
                );
                //]

                //[example__neural_network_trans_func__reset__back_propagate
                output const& target_output = *outputs_itr;

                for (std::size_t i = 0; i < output_error.size(); ++i)
                {
                    output_error[i]
                        = (target_output[i] - actual_output[i])
                        * _calculate_sigmoid_derivative(actual_output[i]);
                }

                for (std::size_t i = 0; i < hidden_layer_error.size(); ++i)
                {
                    hidden_layer_error[i] = 0.0;

                    for (std::size_t j = 0; j < output_error.size(); ++j)
                    {
                        hidden_layer_error[i]
                            += output_error[j]
                            * _weights_hidden2output(i, j);
                    }

                    hidden_layer_error[i]
                        *= _calculate_sigmoid_derivative(hidden_layer[i]);
                }

                _back_propagate(
                    hidden_layer
                  , output_error
                  , learning_rate
                  , _weights_hidden2output
                  , _bias_2
                );
                _back_propagate(
                    in
                  , hidden_layer_error
                  , learning_rate
                  , _weights_input2hidden
                  , _bias_1
                );
                //]

                //[example__neural_network_trans_func__reset__end_cycle
                if (++inputs_itr == inputs_end)
                {
                    inputs_itr = inputs_begin;
                    outputs_itr = outputs_begin;
                }
                else
                {
                    ++outputs_itr;
                }

                --sample_count;
            }
        }
    };
}  // namespace example
//]

#endif  // LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_TRANS_FUNC_HPP_INCLUDED

