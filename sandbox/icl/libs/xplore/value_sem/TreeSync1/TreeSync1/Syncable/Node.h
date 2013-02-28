#pragma once

#include <iostream>
#include <string>
#include "Syncable_ModeledBy.h"


template<class ContentT, class UuidT = int, class TimeT = int>
class Node
{
public:
  typedef ContentT        Content;
  typedef UuidT           Uuid;
  typedef TimeT           Time;
  typedef Vector<Content> ContentVec;
  typedef Vector<Node>    NodeVec;

  typedef typename ContentVec::const_iterator element_const_iterator;
  typedef typename ContentVec::iterator element_iterator;

  typedef typename NodeVec::const_iterator node_const_iterator;
  typedef typename NodeVec::iterator       node_iterator;

  Node( Uuid const& uuid = 0, std::string const& name = std::string()
      , const ContentVec& content = ContentVec(), const NodeVec& children = NodeVec())
    : m_uuid(uuid), m_name(name)
    , m_content(content), m_children(children)
  {
    m_time = std::max(m_content.time(), m_children.time());
  }

  Node(Node const& val) : m_uuid(val.m_uuid), m_time(val.m_time), m_name(val.m_name)
      , m_content(val.m_content), m_children(val.m_children)
  {
      std::cout << "n.c() ";
  }

  Node(Node&& val) : m_uuid(std::move(val.m_uuid))
      , m_time(std::move(val.m_time)), m_name(std::move(val.m_name))
      , m_content(std::move(val.m_content)), m_children(std::move(val.m_children))
  {
      std::cout << "n.m() ";
  }

  Node& operator = (Node val)
  {
      m_uuid     = std::move(val.m_uuid);
      m_time     = std::move(val.m_time);
      m_name     = std::move(val.m_name);
      m_content  = std::move(val.m_content);
      m_children = std::move(val.m_children);
      std::cout << "n.m= ";
      return *this; 
  }


  element_const_iterator elements_begin()const { return m_content.begin(); }
  element_const_iterator elements_end()const   { return m_content.end();   }
  element_iterator elements_begin()            { return m_content.begin(); }
  element_iterator elements_end()              { return m_content.end();   }
  int element_count()const                     { return m_content.size();  }

  node_const_iterator nodes_begin()const       { return m_children.begin(); }
  node_const_iterator nodes_end()const         { return m_children.end();   }
  node_iterator nodes_begin()                  { return m_children.begin(); }
  node_iterator nodes_end()                    { return m_children.end();   }
  int node_count()const                        { return m_children.size();  }



  Uuid        uuid()const { return m_uuid; }
  Time        time()const { return m_time; }
  std::string name()const { return m_name; }

  Uuid        contentUuid()const { return m_content.uuid(); }
  Time        contentTime()const { return m_content.time(); }
  std::string contentName()const { return m_content.name(); }

  Uuid        childrenUuid()const { return m_children.uuid(); }
  Time        childrenTime()const { return m_children.time(); }
  std::string childrenName()const { return m_children.name(); }

  void        setUuid(Uuid const& uuid) { m_uuid=uuid; }
  void        setTime(Time const& time) { m_time=time; }
  void        setName(std::string& name){ m_name=name; }

  void        setContent(ContentVec content){ m_content = std::move(content); };
  void        setChildren(NodeVec nodes){ m_children = std::move(nodes); };

  ContentVec content()const  { return m_content;  }
  NodeVec    children()const { return m_children; }  
  ContentVec const& ref_content()const  { return m_content;  }
  NodeVec const&    ref_children()const { return m_children; }  

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

  draw(obj.ref_content(), out, pos+2);
  draw(obj.ref_children(), out, pos+2); 

  out << std::string(pos,' ') << "</Node>\n";
}


template<class ContentT,class UuidT, class TimeT> 
struct Syncable_ModeledBy<Node<ContentT,UuidT,TimeT> >
{
    static const bool value = true;
    typedef typename Node<ContentT,UuidT,TimeT> Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const& object){ return object.uuid(); }
    static Time time(Model const& object){ return object.time(); }
};

