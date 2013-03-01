#pragma once

#include <vector>
#include "Syncable_ModeledBy.h"


template<class Type, class UuidT = int, class TimeT = int>
class Vector
{
public:
  typedef UuidT                                Uuid;
  typedef TimeT                                Time;
  typedef std::vector<Type>                    tVector;

  typedef typename tVector::size_type          size_type;
  typedef typename tVector::value_type         value_type;
  typedef typename tVector::const_reference    const_reference;

  typedef typename tVector::iterator           iterator;
  typedef typename tVector::const_iterator     const_iterator;

  Vector(): m_uuid(), m_time(), m_name("empty"), m_vector() {}

  Vector(Uuid const& uuid, Time const& time, std::string const& name)
    : m_uuid(uuid), m_time(time), m_name(name), m_vector() 
  {
  }

  Vector(Vector const& val) : m_vector(val.m_vector)
    , m_uuid(val.m_uuid)
    , m_time(val.m_time)
    , m_name(val.m_name)
  {
    std::cout << "c(" << m_vector.size() << ") ";
  }

  Vector(Vector&& val): m_vector(std::move(val.m_vector))
    , m_uuid(std::move(val.m_uuid))
    , m_time(std::move(val.m_time))
    , m_name(std::move(val.m_name))
  {
    std::cout << "m(" << m_vector.size() << ") ";
  };

  Vector& operator = (Vector val)
  { 
    m_uuid   = std::move(val.m_uuid);
    m_time   = std::move(val.m_time);
    m_name   = std::move(val.m_name);
    m_vector = std::move(val.m_vector); 
    std::cout << "m=" << m_vector.size() << " ";
    return *this; 
  }
  
  const_iterator begin()const { return m_vector.begin(); }
  const_iterator end()const   { return m_vector.end(); }

  iterator begin() { return m_vector.begin(); }
  iterator end()   { return m_vector.end(); }

  void reserve(size_type size){ m_vector.reserve(size); }
  size_type size()const { return m_vector.size(); }

  void emplace_back(Type val)
  {
    m_time = std::move(std::max(m_time, val.time()));
    m_vector.emplace_back(val); 
  }

  void push_back(const Type& val)
  {
    m_time = std::max(m_time, val.time());
    m_vector.push_back(val); 
  }

  Uuid uuid()const { return m_uuid; }
  Time time()const { return m_time; }
  std::string name()const { return m_name; }

  void setUuid(Uuid const& uuid){ m_uuid = uuid; }
  void setTime(Time const& time){ m_time = time; }
  void setName(std::string const& name){ m_name = name; }
  void name(std::string const& name)const { m_name = name; }

private:
  Uuid m_uuid;
  Time m_time;
  std::string m_name;
  tVector m_vector;  
};


template<class ElementT, class UuidT, class TimeT> 
struct Syncable_ModeledBy<Vector<ElementT,UuidT,TimeT> >
{
    static const bool value = true;
    typedef Vector<ElementT,UuidT,TimeT> Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const& object){ return object.uuid(); }
    static Time time(Model const& object){ return object.time(); }
};

