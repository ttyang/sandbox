/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "data/qsql/QSqlSelector.h"

namespace data
{

template<class Accessor> struct isQuerySelector;

template<class Accessor>
struct isQuerySelector
{
    static const bool value = false;
};

template<>
struct isQuerySelector<QSqlSelector>
{
    static const bool value = true;
};

} // namespace data



