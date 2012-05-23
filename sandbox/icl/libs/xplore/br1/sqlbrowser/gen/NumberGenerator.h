/****************************************************************************
**
**
****************************************************************************/

#pragma once


#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include <boost/icl/interval.hpp>

#include <QString.h>

namespace gen
{

typedef QString tString;
typedef boost::random::uniform_int_distribution<>  tUniformInt;
typedef boost::random::uniform_real_distribution<> tUniformReal;
typedef boost::random::mt19937                     tRandomGenerator;


extern tRandomGenerator g_aRandomGenerator;

class IntGenerator
{
public:
    //typedef boost::icl::interval_type_default<int>::type tInterval;
    typedef boost::icl::interval_type_default<int>::type tInterval;

    IntGenerator(int min, int max): m_aDist(min, max){}
    explicit IntGenerator(const tInterval& range):
        m_aDist(first(range), last(range)){}

    int operator()()const { return m_aDist(g_aRandomGenerator); }

private:
    gen::tUniformInt m_aDist;
};

class DoubleGenerator
{
public:
    DoubleGenerator(double min, double max): m_aDist(min, max){}

    double operator()()const { return m_aDist(g_aRandomGenerator); }

private:
    gen::tUniformReal m_aDist;
};


} // namespace data
