#include "Dag/DbType.h"

using namespace dag::db;



class TypeTraits
{
public:
    static const int ciMaxBitCount = 64;
    typedef std::bitset<ciMaxBitCount> tTraitSet;
private:
    tTraitSet m_aTraitSet;
};


bool dag::db::isBuiltIn(const TypeTraits& aTraits);
bool dag::db::isAtom(const TypeTraits& aTraits);
bool isComposite(const TypeTraits& aTraits);




/*
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



//! dag::db::Object is a fairly general and thus boring object.
//! It has a db::Type which determines the flat type of data record m_aValue.
template<class Type>
class Object
{
public:
    Object(): m_aType(){};
    explicit Object(Type aType): m_aType(aType){};
private:
    Type        m_aType;
    tVariVector m_aValue;
};

typedef boost::scoped_ptr<Object> tObjectUniPtr;
typedef                   Object* tObjectRawPtr;
typedef             const Object* tObjectConstRawPtr;

*/

}} //namespace dag { namespace db



