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

template<unsigned int ciMaxBitCount = 64>
class TypeTraits : public std::bitset<ciMaxBitCount>
{
public:
    enum
    {
          eDefined  = 0    //Bit 0: 0:undefined 1:defined
        , eComposed        //Bit 0: 0:atomic    1:composite
        , eRelation        //Bit 1: 0:object    1:relation
        , eAddedType       //Bit 2: 0:built_in  1:added_type
        , eTraits_count
    };

    typedef std::bitset<ciMaxBitCount> tTraitSet;

    TypeTraits(): tTraitSet(){};
    TypeTraits(unsigned long bits): tTraitSet(bits){};
};

typedef TypeTraits<> tTypeTraits;

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
    TypeTraits<>    m_aTraits;
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



//! dag::db::Object is a fairly general and thus boring object.
//! It has a db::Type which determines the flat type of data record m_aValue.
template<class Type>
class Object
{
public:
    typedef Type tType;
    Object(): m_aType(){};
    explicit Object(Type aType): m_aType(aType){};
private:
    Type        m_aType;
    tVariVector m_aValue;
};

typedef Object<ObjectType>         tObject;
typedef boost::scoped_ptr<tObject> tObjectUniPtr;
typedef                   tObject* tObjectRawPtr;
typedef             const tObject* tObjectConstRawPtr;



}} //namespace dag { namespace db



