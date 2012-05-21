/****************************************************************************
**
**
****************************************************************************/

#include "NameGenerator.h"

using namespace gen;

boost::random::mt19937 NameGenerator::s_aGen;

const char* NameGenerator::s_SyllablesBegin[] =
{
      "Ana"
    , "Pa"
    , "Re"
};

const char* NameGenerator::s_SyllablesMid[] =
{
      "be"
    , "dre"
    , "dri"
    , "ja"
    , "na"
    , "ma"
    , "no"
    , "ra"
};

const char* NameGenerator::s_SyllablesEnd[] =
{
      "ja"
    , "ka"
    , "le"
    , "ma"
    , "na"
};


int NameGenerator::syllablesBeginCount()
{
    return sizeof(s_SyllablesBegin)/sizeof(s_SyllablesBegin[0]);
}

int NameGenerator::syllablesMidCount()
{
    return sizeof(s_SyllablesMid)/sizeof(s_SyllablesMid[0]);
}

int NameGenerator::syllablesEndCount()
{
    return sizeof(s_SyllablesEnd)/sizeof(s_SyllablesEnd[0]);
}

tUniform NameGenerator::s_BeginDist(0, NameGenerator::syllablesBeginCount()-1);
tUniform NameGenerator::s_MidDist  (0, NameGenerator::syllablesMidCount()-1);
tUniform NameGenerator::s_EndDist  (0, NameGenerator::syllablesEndCount()-1);

tString NameGenerator::operator()()const
{
    tString someName = m_aPrefix;
    someName += s_SyllablesBegin[s_BeginDist(s_aGen)];

    int count = m_aDist(s_aGen) - 2;
    count = count < 0 ? 0 : count;

    for(int idx = 0; idx < count; idx++)
        someName += s_SyllablesMid[s_MidDist(s_aGen)];


    someName += s_SyllablesEnd[s_EndDist(s_aGen)];

    return someName;
}
