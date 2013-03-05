#pragma once

#include <vector>
#include "Syncable_ModeledBy.h"


template<class Type, class UuidT = int, class TimeT = int>
class Vector : private std::vector<Type>
{
public:
  typedef UuidT                              Uuid;
  typedef TimeT                              Time;
  typedef std::vector<Type>                  BaseT;

  typedef typename BaseT::size_type          size_type;
  typedef typename BaseT::value_type         value_type;
  typedef typename BaseT::const_reference    const_reference;

  typedef typename BaseT::iterator           iterator;
  typedef typename BaseT::const_iterator     const_iterator;

  Vector(): BaseT(), m_uuid(), m_time(), m_name("empty"){}

  Vector(Uuid const& uuid, Time const& time, std::string const& name)
    : BaseT(), m_uuid(uuid), m_time(time), m_name(name)
  {
  }

  Vector(Vector const& val) : BaseT(val)
    , m_uuid(val.m_uuid)
    , m_time(val.m_time)
    , m_name(val.m_name)
  {
    std::cout << "c(" << BaseT::size() << ") ";
  }

  Vector(Vector&& val): BaseT(std::move(val))
    , m_uuid(std::move(val.m_uuid))
    , m_time(std::move(val.m_time))
    , m_name(std::move(val.m_name))
  {
    std::cout << "m(" << BaseT::size() << ") ";
  };

  Vector& operator = (Vector val)
  { 
    BaseT::operator = (std::move(val));
    m_uuid   = std::move(val.m_uuid);
    m_time   = std::move(val.m_time);
    m_name   = std::move(val.m_name);
    std::cout << "m=" << BaseT::size() << " ";
    return *this; 
  }

  using BaseT::begin;
  using BaseT::end;
  using BaseT::reserve;
  using BaseT::size;

  void emplace_back(Type val)
  {
    m_time = std::move(std::max(m_time, val.time()));
    BaseT::emplace_back(std::move(val)); 
  }

  void push_back(const Type& val)
  {
    m_time = std::max(m_time, val.time());
    BaseT::push_back(val); 
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

