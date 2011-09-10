// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// std::cout and std::endl
#include <iostream>
// std::tr1::mt19937
#include <boost/tr1/random.hpp>
// vec_adjacency_list_example
#include "loop_erased_random_weighted_tree.hpp"

int usage()
{
    std::cout << "Options:" << std::endl;
    std::cout << "-s#, where # is an integer between 0 and 23, inclusive";
    std::cout << " (default is 0)" << std::endl;
    std::cout << "-e#, where # is an integer between 0 and 23, inclusive";
    std::cout << " (default is 22)" << std::endl;
    std::cout << "-n#, where # is a nonnegative integer";
    std::cout << " (default is 16)" << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    unsigned int start_index = 0;
    unsigned int end_index = 22;
    unsigned int num_runs = 16;
    char* arg;

    while (--argc > 0)
    {
        arg = argv[argc];

        if ((std::strlen(arg) > 2) && (arg[0] == '-'))
        {
            switch (arg[1])
            {
                case 's':
                    start_index = std::atoi(&arg[2]);

                    if (start_index > 23)
                    {
                        return usage();
                    }

                    break;

                case 'e':
                    end_index = std::atoi(&arg[2]);

                    if (end_index > 23)
                    {
                        return usage();
                    }

                    break;

                case 'n':
                    num_runs = std::atoi(&arg[2]);
                    break;

                default:
                    return usage();
            }
        }
        else
        {
            return usage();
        }
    }

    vec_adjacency_list_example<boost::listS,std::tr1::mt19937>(
        start_index
      , end_index
      , num_runs
    );

    return 0;
}

