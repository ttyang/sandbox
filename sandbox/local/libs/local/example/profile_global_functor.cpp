
#include <boost/chrono.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include "profile_helpers.hpp"

struct global_add {
    global_add(double& _sum, const int& _factor):
                sum(_sum), factor(_factor) {}
    inline void operator()(const double& num) {
        sum += factor * num;
    }
private:
    double& sum;
    const int& factor;
};

int main(int argc, char* argv[]) {
    unsigned long size = 0, trials =0;
    begin(argc, argv, size, trials);

    double sum = 0.0;
    int factor = 1;

    boost::chrono::system_clock::time_point start =
            boost::chrono::system_clock::now();
    global_add add(sum, factor);
    boost::chrono::duration<double> decl_sec =
            boost::chrono::system_clock::now() - start;

    std::vector<double> v(size);
    std::fill(v.begin(), v.end(), 1.0);

    boost::chrono::duration<double> trials_sec;
    for (unsigned long i = 0; i < trials; ++i) {
        boost::chrono::system_clock::time_point start =
                boost::chrono::system_clock::now();
        std::for_each(v.begin(), v.end(), add);
        trials_sec += boost::chrono::system_clock::now() - start;
    }

    end(size, trials, sum, trials_sec.count(), decl_sec.count());
    return 0;
}
