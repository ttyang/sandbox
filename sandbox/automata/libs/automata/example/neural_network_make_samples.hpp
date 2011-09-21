// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_BUILD_SAMPLES_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_BUILD_SAMPLES_HPP_INCLUDED

#include "neural_network_trans_func.hpp"

//[example__neural_network_make_samples
namespace example {

    template <typename Inputs, typename Outputs>
    void make_samples(Inputs& inputs, Outputs& outputs)
    {
        neural_network_transition_function::input
            in(neural_network_transition_function::input_count);
        neural_network_transition_function::output
            out(neural_network_transition_function::state_count);

        in[0]  = 2.0; in[1]  = 0.0; in[2]  = 0.0; in[3]  = 0.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 1.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 2.0; in[1]  = 0.0; in[2]  = 0.0; in[3]  = 1.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 1.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);

        // More samples pushed back ...
        //<-
        in[0]  = 2.0; in[1]  = 0.0; in[2]  = 1.0; in[3]  = 1.0;
        out[0] = 1.0; out[1] = 0.0; out[2] = 0.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 2.0; in[1]  = 0.0; in[2]  = 1.0; in[3]  = 2.0;
        out[0] = 1.0; out[1] = 0.0; out[2] = 0.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 2.0; in[1]  = 1.0; in[2]  = 0.0; in[3]  = 2.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 2.0; in[1]  = 1.0; in[2]  = 0.0; in[3]  = 1.0;
        out[0] = 1.0; out[1] = 0.0; out[2] = 0.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 1.0; in[1]  = 0.0; in[2]  = 0.0; in[3]  = 0.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 1.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 1.0; in[1]  = 0.0; in[2]  = 0.0; in[3]  = 1.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 1.0; in[1]  = 0.0; in[2]  = 1.0; in[3]  = 1.0;
        out[0] = 1.0; out[1] = 0.0; out[2] = 0.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 1.0; in[1]  = 0.0; in[2]  = 1.0; in[3]  = 2.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 1.0; in[1]  = 1.0; in[2]  = 0.0; in[3]  = 2.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 1.0; in[1]  = 1.0; in[2]  = 0.0; in[3]  = 1.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 0.0; in[1]  = 0.0; in[2]  = 0.0; in[3]  = 0.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 1.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 0.0; in[1]  = 0.0; in[2]  = 0.0; in[3]  = 1.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 0.0; in[1]  = 0.0; in[2]  = 1.0; in[3]  = 1.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 0.0; in[1]  = 0.0; in[2]  = 1.0; in[3]  = 2.0;
        out[0] = 0.0; out[1] = 1.0; out[2] = 0.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 0.0; in[1]  = 1.0; in[2]  = 0.0; in[3]  = 2.0;
        out[0] = 0.0; out[1] = 1.0; out[2] = 0.0; out[3] = 0.0;
        inputs.push_back(in);
        outputs.push_back(out);
        in[0]  = 0.0; in[1]  = 1.0; in[2]  = 0.0; in[3]  = 1.0;
        out[0] = 0.0; out[1] = 0.0; out[2] = 0.0; out[3] = 1.0;
        inputs.push_back(in);
        outputs.push_back(out);
        //->
    }
}  // namespace example
//]

#endif  // build_samples

