#pragma once

#include <ostream>
#include <vector>
#include "Object.h"

typedef int tUuid;
typedef int tTime;


template<class Uuid, class Time = int>
class Playable
{
public:
  Playable(Uuid uuid)
    : m_uuid(uuid)
  {  }

  Uuid uuid()const { return m_uuid; }
  Time time()const { return Time(); } //JODO

private:
  Uuid m_uuid;
};

template<class CharType, class CharTraits, class Uuid>
std::basic_ostream<CharType, CharTraits>&
operator << (std::basic_ostream<CharType, CharTraits> &stream, Playable<Uuid> const& object)
{
  return stream << "Play(" << object.uuid() << ")";
}


template<class Type, class Uuid = int, class Time = int>
struct Vec
{
  typedef std::vector<object>     tVector;
  typedef tVector::iterator       iterator;
  typedef tVector::const_iterator const_iterator;
  typedef tVector::value_type     value_type;

  Vec(): m_uuid(), m_time(), m_name(), m_vector() {}
  Vec(Uuid const& uuid, Time const& time, std::string const& name)
    : m_uuid(uuid), m_time(time), m_name(name), m_vector() {}

  const_iterator begin()const { return m_vector.begin(); }
  const_iterator end()const   { return m_vector.end(); }

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
  void name(std::string const& name)const { m_name = name; }

  Uuid m_uuid;
  Time m_time;
  std::string m_name;
  tVector m_vector;  
};


template<class Content, class Uuid = int, class Time = int>
class Node
{
public:
  typedef Vec<Content> ContentVec;
  typedef Vec<Node>    NodeVec;


  Node( Uuid const& uuid = 0, std::string const& name = std::string()
      , const ContentVec& content = ContentVec(), const NodeVec& children = NodeVec())
    : m_uuid(uuid), m_name(name)
    , m_content(content), m_children(children)
  {
    m_time = std::max(m_content.time(), m_children.time());
  }

  Uuid        uuid()const { return m_uuid; }
  Time        time()const { return m_time; }
  std::string name()const { return m_name; }

  ContentVec content()const  { return m_content;  }
  NodeVec    children()const { return m_children; }  

private:
  Uuid        m_uuid;
  Time        m_time;
  std::string m_name;
  ContentVec  m_content;
  NodeVec     m_children;
};

template<class Type>
void draw(const Node<Type>& obj, std::ostream& out, size_t pos)
{
  out << std::string(pos,' ') << "<Node>[" << obj.name() << "](" << obj.uuid() << "," << obj.time() <<")\n";

  draw(obj.content(), out, pos+2);
  draw(obj.children(), out, pos+2); 

  out << std::string(pos,' ') << "</Node>\n";
}

/*
template<class Type>
Node<Type> merge(const Node<Type>& lhs, const Node<Type>& rhs)
{ 
  Node<Type> merged;
  m_uuid = lhs.uuid();
  m_time = std::max(lhs.time(), rhs.time());
  
  for( ContentVec::const_iterator cont_it = m_content.begin()
     ; cont_it != m_content.end(); ++ cont_it)
  {
     merged.push_back(merge(*cont_it), );
  }
  merged.setContent(merge_content(lhs, rhs));
  merged.setChildren(merge_children(lhs, rhs));
}
*/

