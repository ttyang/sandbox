/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "data/qsql/QSqlSelector.h"

namespace data
{

template<class Object, class Accessor>
struct GetCreator;

template<class Object>
struct GetCreator<QSqlSelector>
{
    typedef QSqlCreator<Object, QSqlSelector> type;
};


} // namespace data



