
// benchmark based on: http://cpp-next.com/archive/2010/10/howards-stl-move-semantics-benchmark/

#include "boost/container/static_vector.hpp"
#include "boost/container/vector.hpp"
#include "boost/container/set.hpp"
#include <vector>
#include <iostream>
#include <boost/timer/timer.hpp>
#include <set>
#include <algorithm>
#include <exception>

using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::nanosecond_type;

static const std::size_t N = 720;

extern bool some_test;

template<typename T>
T get_set(std::size_t)
{
    T s;
    for (std::size_t i = 0; i < N; ++i)
        s.push_back(std::rand());
        
    if (some_test)
        return s;
    return T();
}

template<typename T>
T generate()
{
    T v;
    for (std::size_t i = 0; i < N; ++i)
        v.push_back(get_set<typename T::value_type>(i));
    if (some_test)
        return v;
    return T();
}

template<typename T>
cpu_times time_it()
{
    cpu_timer totalTime, stepTime;
    {
        T v = generate<T>();
        totalTime.stop(); stepTime.stop();
        std::cout << "  construction took " << boost::timer::format(stepTime.elapsed());
        
        totalTime.resume(); stepTime.start();
        std::sort(v.begin(), v.end());
        totalTime.stop(); stepTime.stop();
        std::cout << "  sort took         " << boost::timer::format(stepTime.elapsed());
        
        totalTime.resume(); stepTime.start();
        std::rotate(v.begin(), v.begin() + v.size()/2, v.end());
        totalTime.stop(); stepTime.stop();
        std::cout << "  rotate took       " << boost::timer::format(stepTime.elapsed());
        
        totalTime.resume(); stepTime.start();
    }
    
    totalTime.stop(); stepTime.stop();
    std::cout << "  destruction took  " << boost::timer::format(stepTime.elapsed());
    std::cout << "  done\n" << std::endl;
    
    std::cout << "  Total time =      " << boost::timer::format(totalTime.elapsed()) << "\n\n\n";
    return totalTime.elapsed();
}

int main()
{
    try {
        std::cout << "N = " << N << "\n\n";
        
        std::cout << "static_vector benchmark:\n";
        cpu_times tsv = time_it<boost::container::static_vector<boost::container::static_vector<std::size_t,N>,N > >();
        
        std::cout << "vector benchmark\n";
        cpu_times tv = time_it<boost::container::vector<boost::container::vector<std::size_t> > >();
        
        std::cout << "static_vector/vector total time comparison:"
        << "\n  wall          = " << ((double)tsv.wall/(double)tv.wall)
        << "\n  user          = " << ((double)tsv.user/(double)tv.user)
        << "\n  system        = " << ((double)tsv.system/(double)tv.system)
        << "\n  (user+system) = " << ((double)(tsv.system+tsv.user)/(double)(tv.system+tv.user)) << '\n';
    }catch(std::exception e){
        std::cout << e.what();
    }
}

bool some_test = true;
