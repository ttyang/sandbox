/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
#include <bitset>
//boost
#include <boost/scoped_ptr.hpp>
//qt
#include <QtCore/QVariant>
#include <QtCore/QVector>

namespace dag { namespace db
{

typedef unsigned int      tKey;
typedef QVector<tKey>     tKeySequence;
typedef QVector<QVariant> tVariVector;
typedef QString           tString;



//==============================================================================
//= dag::db::Types
//==============================================================================


class TypeTraits
{
public:
    static const int ciMaxBitCount = 64;
    typedef std::bitset<ciMaxBitCount> tTraitSet;
private:
    tTraitSet m_aTraitSet;
};

bool isBuiltIn(const TypeTraits& aTraits);
bool isAtom(const TypeTraits& aTraits);
bool isComposite(const TypeTraits& aTraits);



//! TypeSignature: The sequence of Types of an Objects
//! Fields. The fields that contain all 1:1 Relationships
//! that an object has in a given model.
class TypeSignature
{
public:
private:
    tKeySequence m_aTypeSequence;
};

//! FieldSignature: The sequence of Fields of an Object.
class FieldSignature
{
public:
private:
    tKeySequence m_aFieldSequence;
};


//Don't optimize premature: Clearness first!!
//I have to prepare and build the TypeGraph first.
//

class ObjectType
{
public:
private:
    tKey            m_uKey;
    TypeTraits      m_aTraits;
    tString         m_aName;
    TypeSignature   m_aTypeSeq;
    FieldSignature  m_aFieldSeq;
};

typedef boost::scoped_ptr<ObjectType> tObjectTypeUniPtr;
typedef ObjectType*                   tObjectTypeRawPtr;
typedef const ObjectType*             tConstObjectTypeRawPtr;


class EdgeType
{
public:
private:
    tKey              m_uKey;
    tString           m_aName;
    tObjectTypeUniPtr m_pSourceType;
    tObjectTypeUniPtr m_pRelationType;
    tObjectTypeUniPtr m_pTargetType;
};


//==============================================================================
//= dag::db::Objects
//==============================================================================

//!
template<class Type>
class Object
{
public:
    Object(Type aType): m_aType(aType){};
private:
    Type        m_aType;
    tVariVector m_aValue;
};

}} //namespace dag { namespace db



