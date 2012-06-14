/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "data/qsql/QSqlSelector.h"

namespace data
{

template<class Accessor>
struct IsQuerySelector
{
    typedef IsQuerySelector<Accessor> type;
    static const bool value = false;
};

template<>
struct IsQuerySelector<QSqlSelector>
{
    typedef IsQuerySelector<QSqlSelector> type;
    static const bool value = true;
};

template<class KeyIterator>
struct IsQuerySelector<KeyBinding_QSqlSelector<KeyIterator> >
{
    typedef IsQuerySelector<QSqlSelector> type;
    static const bool value = true;
};

} // namespace data



