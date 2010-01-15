#include <iostream>

#include <libs/statistics/detail/non_parametric/example/frequency_int.h>
#include <libs/statistics/detail/non_parametric/example/kolmogorov_smirnov.h>

int main()
{
	example_frequency_int(std::cout);
	example_kolmogorov_smirnov(std::cout);

    return 0;
}