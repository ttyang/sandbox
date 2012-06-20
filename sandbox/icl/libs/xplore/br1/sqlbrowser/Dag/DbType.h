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

//JODO typedef unsigned int      tKey;
typedef int               tKey;
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
    TypedField(): m_iType(0), m_iField(0){}
    TypedField(tKey type, tKey field): m_iType(type), m_iField(field){}

    tKey type()const { return m_iType;  }
    tKey field()const{ return m_iField; }
private:
    tKey m_iType;
    tKey m_iField;
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
    ObjectType(){}

    ObjectType(tKey key, tTypeTraits traits, const tString& name)
        : m_iKey(key)
        , m_aTraits(traits)
        , m_aName(name)
        , m_depth(0)
    {
        int dbg_key = m_iKey;
    }

    QString toString()const
    { return QString("ObjectType(%1, %2)").arg(m_iKey).arg(m_aName); }

    tKey key()const { return m_iKey; }
    tString name()const { return m_aName; }

    int depth()const { return m_depth; }
    void setDepth(int depth) { m_depth = depth; }

private:
    tKey            m_iKey;
    tTypeTraits     m_aTraits;
    tString         m_aName;
    int             m_depth; //JODO TMP
    //TypeSignature   m_aTypeSeq;
    //FieldSignature  m_aFieldSeq;
};

typedef boost::shared_ptr<ObjectType> tObjectTypeSharedPtr;
typedef ObjectType*                   tObjectTypeRawPtr;
typedef const ObjectType*             tConstObjectTypeRawPtr;


class EdgeType
{
public:
    EdgeType(){}

    EdgeType(tKey iKey, tKey iSrc, tKey iRel, tKey iTrg, const tString& aName)
        : m_iKey(iKey)
        , m_iRefSourceType(iSrc)
        , m_iRefRelationType(iRel)
        , m_iRefTargetType(iTrg)
        , m_aName(aName)
    {}

    QString toString()const
    { return QString("EdgeType(%1,..)").arg(m_iKey); }
    //{ return QString("EdgeType(%1, %2)").arg(m_iKey).arg(m_aName); }

    tKey sourceType()const { return m_iRefSourceType; }
    tKey targetType()const { return m_iRefTargetType; }

private:
    tKey                 m_iKey;
    tKey                 m_iRefSourceType;
    tKey                 m_iRefRelationType;
    tKey                 m_iRefTargetType;
    tString              m_aName;
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


