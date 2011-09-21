// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/automata/function_automaton.hpp>

//[example__ublas_product__function
using namespace boost;
using namespace numeric;
using namespace ublas;

vector<double> ublas_product(vector<double> const& v, matrix<double> const& m)
{
    return prod(v, m);
}
//]

//[example__markov_chain__setup
int main()
{
    matrix<double> m(2, 2);

    std::cout << "Chance that a sunny day will remain sunny tomorrow: ";
    std::cout << (m(0, 0) = 0.9) << std::endl;
    std::cout << "Chance that a sunny day will become rainy tomorrow: ";
    std::cout << (m(0, 1) = 0.1) << std::endl;
    std::cout << "Chance that a rainy day will become sunny tomorrow: ";
    std::cout << (m(1, 0) = 0.5) << std::endl;
    std::cout << "Chance that a rainy day will remain rainy tomorrow: ";
    std::cout << (m(1, 1) = 0.5) << std::endl;

    vector<double> v(2);

    v(0) = 1.0;
    v(1) = 0.0;
    //]

    //[example__markov_chain__automaton
    typedef automata::function_automaton<BOOST_TYPEOF(ublas_product)>
            MarkovChain;

#ifdef __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
    MarkovChain markov_chain(ublas_product, v);
#else  // !defined(__BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__)
    MarkovChain markov_chain(v, ublas_product);
#endif  // __BOOST_AUTOMATA_NO_FUNC_PARAM_WKND__
    //]

    //[example__markov_chain__usage
    int input;

    for (;;)
    {
        std::cout << "Today\'s chances of sunshine: ";
        std::cout << markov_chain.get_current_state()(0) << std::endl;
        std::cout << "Today\'s chances of rain: ";
        std::cout << markov_chain.get_current_state()(1) << std::endl;
        std::cout << "Enter the number of days to look ahead: ";

        if ((std::cin >> input) && (0 < input))
        {
            while (input--)
            {
                markov_chain(m);
            }
        }
        else
        {
            std::cout << "Go bye-bye." << std::endl;
            break;
        }
    }

    return 0;
}
//]

