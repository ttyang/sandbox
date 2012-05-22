/****************************************************************************
**
**
****************************************************************************/

#include "gen/NumberGenerator.h"
#include "gen/NameGenerator.h"

using namespace gen;

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

int NameGenerator::syllableIndexBegin()
{
    return s_BeginDist(g_aRandomGenerator);
}

int NameGenerator::syllableIndexMid()
{
    return s_MidDist(g_aRandomGenerator);
}

int NameGenerator::syllableIndexEnd()
{
    return s_EndDist(g_aRandomGenerator);
}



tUniform NameGenerator::s_BeginDist(0, NameGenerator::syllablesBeginCount()-1);
tUniform NameGenerator::s_MidDist  (0, NameGenerator::syllablesMidCount()-1);
tUniform NameGenerator::s_EndDist  (0, NameGenerator::syllablesEndCount()-1);

tString NameGenerator::operator()()const
{
    tString someName = m_aPrefix;
    someName += s_SyllablesBegin[syllableIndexBegin()];

    int count = m_aDist(g_aRandomGenerator) - 2;
    count = count < 0 ? 0 : count;

    for(int idx = 0; idx < count; idx++)
        someName += s_SyllablesMid[syllableIndexMid()];


    someName += s_SyllablesEnd[syllableIndexEnd()];

    return someName;
}

