/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
#include <bitset>
//boost
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
//qt
#include <QtCore/QVariant>
#include <QtCore/QVector>


class VertexAttributes;

typedef VertexAttributes* VertexAttributesPtr;

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
        , eComposed        //Bit 1: 0:atomic    1:composite
        , eRelation        //Bit 2: 0:object    1:relation
        , eAddedType       //Bit 3: 0:built_in  1:added_type
        , eSize
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

class TypedField
{
public:
    TypedField(): m_uType(0), m_uField(0){}
    TypedField(tKey type, tKey field): m_uType(type), m_uField(field){}

    tKey type()const { return m_uType;  }
    tKey field()const{ return m_uField; }
private:
    tKey m_uType;
    tKey m_uField;
};

typedef QVector<TypedField> tFieldSignature;

//! FieldSignature: The sequence of typed fields of an Object.
class FieldSignature
{
public:
    //JODO Read the field signature from the data base.
private:
    tFieldSignature m_aFieldSequence;
};


//==============================================================================
//= TypeGraph Objects
//==============================================================================
class ObjectType
{
public:
private:
    tKey            m_uKey;
    tTypeTraits     m_aTraits;
    tString         m_aName;
    TypeSignature   m_aTypeSeq;
    FieldSignature  m_aFieldSeq;
};

typedef boost::shared_ptr<ObjectType> tObjectTypeSharedPtr;
typedef ObjectType*                   tObjectTypeRawPtr;
typedef const ObjectType*             tConstObjectTypeRawPtr;


class EdgeType
{
public:
private:
    tKey                 m_uKey;
    tString              m_aName;
    tObjectTypeSharedPtr m_pSourceType;
    tObjectTypeSharedPtr m_pRelationType;
    tObjectTypeSharedPtr m_pTargetType;
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

    bool isConsistent()const; //!< Checks for consistency between types and data

    void setName(const QString& aName) { m_aName = aName; }
    QString name()const { return m_aName; }

private:
    Type        m_aType;
    tVariVector m_aValue;
    QString     m_aName; //JODO for ease of testing only. Remove soon.
};

typedef Object<ObjectType>         tObject;
//typedef boost::scoped_ptr<tObject> tObjectUniPtr;
typedef boost::shared_ptr<tObject> tObjectSharedPtr;
typedef                   tObject* tObjectRawPtr;
typedef             const tObject* tObjectConstRawPtr;



}} //namespace dag { namespace db


