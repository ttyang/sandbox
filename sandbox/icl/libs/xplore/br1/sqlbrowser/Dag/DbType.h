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

    tKey sourceKey()const { return m_iRefSourceType; }
    tKey targetKey()const { return m_iRefTargetType; }

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
//! Parameter 'ModelType' is either ObjectType or EdgeType
//! Object<ObjectType> is associated to Vertixes of the graph
//! Object<EdgeType> is associated to Edges of the graph
template<class ModelType>
class Object
{
public:
    typedef dag::db::ObjectType tModelType;
    Object(): m_Type(){};
    explicit Object(tModelType aType): m_Type(aType){};

    bool isConsistent()const; //!< Checks for consistency between types and data

    tKey key()const { m_Key; }
    void setName(const QString& aName) { m_Name = aName; }
    QString name()const { return m_Name; }

private:
    tKey        m_Key;
    tModelType  m_Type;
    tVariVector m_Value;
    QString     m_Name; //JODO for ease of testing only. Remove soon.
};

typedef Object<ObjectType>         tObject;
typedef boost::shared_ptr<tObject> tObjectSharedPtr;
typedef                   tObject* tObjectRawPtr;
typedef             const tObject* tObjectConstRawPtr;


class Edge
{
public:
    Edge(): m_SourceKey(), m_TargetKey(){};

    explicit Edge(tKey sourceKey, tKey targetKey)
        : m_SourceKey(sourceKey), m_TargetKey(targetKey){};

    tKey key()const { m_Key; }
    tKey sourceKey()const { return m_SourceKey; }
    tKey targetKey()const { return m_TargetKey; }

private:
    tKey m_Key;
    tKey m_SourceKey;
    tKey m_TargetKey;

    Object<EdgeType> m_Object;
};


}} //namespace dag { namespace db


