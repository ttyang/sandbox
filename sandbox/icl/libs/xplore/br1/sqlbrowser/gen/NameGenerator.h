/****************************************************************************
**
**
****************************************************************************/

#pragma once


#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <QString.h>

namespace gen
{

typedef QString tString;
typedef boost::random::uniform_int_distribution<> tUniform;
typedef boost::random::mt19937                    tRandomGenerator;


class NameGenerator
{
public:
    NameGenerator(int min, int max)
        : m_aPrefix(), m_aDist(min, max){}

    tString operator()()const;
    tString operator()(const tString& prefix)const;


    static int syllablesBeginCount();
    static int syllablesMidCount();
    static int syllablesEndCount();

    static int syllableIndexBegin();
    static int syllableIndexMid();
    static int syllableIndexEnd();

private:
    int      m_iMinSyllables;
    int      m_iMaxSyllables;
    tString  m_aPrefix;

    tUniform m_aDist;

    static const char* s_SyllablesBegin[];
    static const char* s_SyllablesMid[];
    static const char* s_SyllablesEnd[];

    static tUniform s_BeginDist;
    static tUniform s_MidDist;
    static tUniform s_EndDist;
};


} // namespace data
