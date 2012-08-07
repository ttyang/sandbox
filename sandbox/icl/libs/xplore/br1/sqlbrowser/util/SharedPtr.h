/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <boost/shared_ptr.hpp>


typedef QVector<QVariant> tVariVector;
typedef boost::shared_ptr<tVariVector> tSharedData;

template<class Type, class Arg1>
boost::shared_ptr<Type> makeShared(const Arg1& arg1)
{
    return boost::shared_ptr<Type>(new Type(arg1));
}

