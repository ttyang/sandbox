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

class NameGenerator
{
public:
    NameGenerator(int min, int max)
        : m_aPrefix(), m_aDist(min, max){}

    tString operator()()const;

    static int syllablesBeginCount();
    static int syllablesMidCount();
    static int syllablesEndCount();

private:
    int      m_iMinSyllables;
    int      m_iMaxSyllables;
    tString  m_aPrefix;

    static boost::random::mt19937 s_aGen;

    tUniform m_aDist;

    static const char* s_SyllablesBegin[];
    static const char* s_SyllablesMid[];
    static const char* s_SyllablesEnd[];

    static tUniform s_BeginDist;
    static tUniform s_MidDist;
    static tUniform s_EndDist;
};


} // namespace data
