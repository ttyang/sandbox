#pragma once

#include <ostream>
#include <vector>
#include "Object.h"

typedef int tUuid;
typedef int tTime;

template<class Uuid>
class Playable
{
public:
  Playable(Uuid uuid)
    : m_uuid(uuid)
  {  }

  Uuid uuid()const { return m_uuid; }

private:
  Uuid m_uuid;
};

template<class CharType, class CharTraits, class Uuid>
std::basic_ostream<CharType, CharTraits>&
operator << (std::basic_ostream<CharType, CharTraits> &stream, Playable<Uuid> const& object)
{
  return stream << "Play(" << object.uuid() << ")";
}

typedef std::vector<Playable<tUuid> > tPlaylist;

struct PlayableTag{};

template<class Type>
struct Vec
{
  typedef std::vector<object>     tVector;
  typedef tVector::iterator       iterator;
  typedef tVector::const_iterator const_iterator;
  typedef tVector::value_type     value_type;

  const_iterator begin()const { return m_vector.begin(); }
  const_iterator end()const   { return m_vector.end(); }

  void push_back(const Type& val){ m_vector.push_back(val); }

  tVector m_vector;  
};



template<class Content>
class Node
{
public:
  typedef Vec<Content> ContentVec;
  typedef Vec<Node>    NodeVec;


  Node(const ContentVec& content = ContentVec(), const NodeVec& children = NodeVec())
    : m_content(content), m_children(children)
  {  }

  ContentVec content()const  { return m_content;  }
  NodeVec    children()const { return m_children; }  

private:
  ContentVec m_content;
  NodeVec    m_children;
};

template<class Type>
void draw(const Node<Type>& obj, std::ostream& out, size_t pos)
{
  out << std::string(pos,' ') << "<Node>\n";

  draw(obj.content(), out, pos+2);
  draw(obj.children(), out, pos+2); 

  out << std::string(pos,' ') << "</Node>\n";
}

