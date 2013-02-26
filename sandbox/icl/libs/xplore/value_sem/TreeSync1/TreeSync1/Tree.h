#pragma once

#include <ostream>
#include <iterator>
#include <vector>
#include <boost/utility/enable_if.hpp>
#include "std_algorithm.h"
#include "Object.h"

typedef int tUuid;
typedef int tTime;

template<class ContentT, class UuidT = int, class TimeT = int>
class Node;

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


template<class Uuid, class Time>
bool operator < (Playable<Uuid,Time> const& lhs, Playable<Uuid,Time> const& rhs)
{
  return lhs.time() < rhs.time();
}

template<class Comparable>
struct Minimum
{
  Comparable operator()(Comparable const& lhs, Comparable const& rhs)
  { return rhs < lhs ? rhs : lhs; }
};

template<class Comparable>
struct Maximum
{
  Comparable operator()(Comparable const& lhs, Comparable const& rhs)
  { return lhs < rhs ? rhs : lhs; }
};

template<class Mergable>
struct Merger
{
  Mergable operator()(Mergable const& lhs, Mergable const& rhs)
  { return merge(lhs, rhs); }
};


template<class CharType, class CharTraits, class Uuid>
std::basic_ostream<CharType, CharTraits>&
operator << (std::basic_ostream<CharType, CharTraits> &stream, Playable<Uuid> const& object)
{
  return stream << "Play(" << object.uuid() << ")";
}


template<class Type, class UuidT = int, class TimeT = int>
struct Vec
{
  typedef std::vector<Type>                    tVector;
  typedef UuidT                                Uuid;
  typedef TimeT                                Time;

  typedef typename tVector::size_type          size_type;
  typedef typename tVector::value_type         value_type;
  typedef Type                                 ValueType;
  typedef typename tVector::const_reference    const_reference;

  typedef typename tVector::iterator           iterator;
  typedef typename tVector::const_iterator     const_iterator;

  Vec(): m_uuid(), m_time(), m_name(), m_vector() {}
  Vec(Uuid const& uuid, Time const& time, std::string const& name)
    : m_uuid(uuid), m_time(time), m_name(name), m_vector() {}

  Vec(Vec const& val) : m_vector(val.m_vector)
    , m_uuid(val.m_uuid)
    , m_time(val.m_time)
    , m_name(val.m_name)
  {
    //std::cout << "c() ";
  }

  Vec(Vec&& val): m_vector(std::move(val.m_vector))
    , m_uuid(std::move(val.m_uuid))
    , m_time(std::move(val.m_time))
    , m_name(std::move(val.m_name))
  {
    //std::cout << "m() ";
  };

  Vec& operator = (Vec val)
  { 
    m_uuid   = std::move(val.m_uuid);
    m_time   = std::move(val.m_time);
    m_name   = std::move(val.m_name);
    m_vector = std::move(val.m_vector); 
    //std::cout << "m= ";
    return *this; 
  }
  
  const_iterator begin()const { return m_vector.begin(); }
  const_iterator end()const   { return m_vector.end(); }

  iterator begin() { return m_vector.begin(); }
  iterator end()   { return m_vector.end(); }

  void reserve(size_type size){ m_vector.reserve(size); }
  size_type size()const { return m_vector.size(); }

  //void push_back(const value_type& val)
  void push_back(const Type& val)
  {
    //JODO 
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

template<class Type, class Uuid, class Time>
bool operator < (Vec<Type,Uuid,Time> const& lhs, Vec<Type,Uuid,Time> const& rhs)
{
  return lhs.time() < rhs.time();
}

//-----------------------------------------------------------------
// Concept Dateable something that is universally identifiable
// and has a timestamp, so it can be synchronized
template<class ModelT> struct Syncable_ModeledBy
{
    static const bool value = false;
    typedef typename ModelT Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const&);
    static Time time(Model const&);
};

template<class UuidT, class TimeT> 
struct Syncable_ModeledBy<Playable<UuidT,TimeT> >
{
    static const bool value = true;
    typedef typename Playable<UuidT> Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const& object){ return object.uuid() };
    static Time time(Model const& object){ return object.time() };
};

template<class ElementT, class UuidT, class TimeT> 
struct Syncable_ModeledBy<Vec<ElementT,UuidT,TimeT> >
{
    static const bool value = true;
    typedef typename Vec<ElementT,UuidT,TimeT> Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const& object){ return object.uuid(); }
    static Time time(Model const& object){ return object.time(); }
};

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

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
typename Syncable_ModeledBy<Model>::Uuid>::type uuid(Model const& object)
{
    return Syncable_ModeledBy<Model>::uuid(object);
}

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
typename Syncable_ModeledBy<Model>::Time>::type time(Model const& object)
{
    return Syncable_ModeledBy<Model>::time(object);
}

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
bool>::type less_for_time(Model const& lhs, Model const& rhs)
{
    return time(lhs) < time(rhs);
}

template<class Model>
typename boost::enable_if<Syncable_ModeledBy<Model>,
bool>::type less_for_uuid(Model const& lhs, Model const& rhs)
{
    return uuid(lhs) < uuid(rhs);
}

template<class Syncable>
struct LessForUuid : std::binary_function<Syncable const&, Syncable const&, bool>
{
    bool operator()(Syncable const& lhs, Syncable const& rhs)
    { return less_for_uuid(lhs, rhs); }
};


//-----------------------------------------------------------------

template<class ContentT, class UuidT = int, class TimeT = int>
class Node
{
public:
  typedef ContentT     Content;
  typedef UuidT        Uuid;
  typedef TimeT        Time;
  typedef Vec<Content> ContentVec;
  typedef Vec<Node>    NodeVec;

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

  void        setUuid(Uuid const& uuid) { m_uuid=uuid; }
  void        setTime(Time const& time) { m_time=time; }
  void        setName(std::string& name){ m_name=name; }
  void        setContent(ContentVec content){ m_content = std::move(content); };
  void        setChildren(NodeVec nodes){ m_children = std::move(nodes); };

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


template<class Type, class Selector> struct Ordering
{
  Ordering(const Selector& select): m_select(select){}
  bool operator()(Type const& lhs, Type const& rhs){ m_select(lhs) < m_select(rhs); }
  Selector m_select;
};

template<class Type>
Node<Type> merge(const Node<Type>& lhs, const Node<Type>& rhs)
{
  typedef typename Node<Type>::ContentVec ContentVec;
  Node<Type> merged;
  merged.setUuid(lhs.uuid());
  merged.setTime(std::max(lhs.time(), rhs.time()));

  merged.setContent(mergeElements(lhs, rhs));
  merged.setChildren(mergeNodes(lhs, rhs));

  return std::move(merged);
}


template<class Type>
typename Node<Type>::ContentVec mergeElements(Node<Type>const& lhs, Node<Type>const& rhs)
{
  typedef Node<Type>::ContentVec  Elements;
  typedef Elements::ValueType     ElementType;

  Elements merged;
  merged.reserve(lhs.element_count() + rhs.element_count());

  std::general_union( lhs.elements_begin(), lhs.elements_end()
                    , rhs.elements_begin(), rhs.elements_end()
                    , Maximum<ElementType>()
                    , std::back_inserter(merged) );

  return std::move(merged);
}


template<class Type>
typename Node<Type>::NodeVec mergeNodes(Node<Type>const& lhs, Node<Type>const& rhs)
{
  typedef Node<Type>::NodeVec Nodes;
  typedef typename Nodes::ValueType NodeType;

  Nodes merged;
  merged.reserve(lhs.node_count() + rhs.node_count());
  
  std::general_union( lhs.nodes_begin(), lhs.nodes_end()
                    , rhs.nodes_begin(), rhs.nodes_end()
                    , Merger<NodeType>()
                    , std::back_inserter(merged) );
                    
  return std::move(merged);
}


template<class Type>
void sort(Node<Type>& val)
{
  typedef typename Node<Type>::ContentVec ContentVec;
  Node<Type> sorted;

  sortElements(val);
  sortNodes(val);
}

template<class Type> struct Sorter
{
  void operator()(Type& value){ sort(value); }
};

template<class Type>
void sortElements(Node<Type>& val)
{
  std::sort( val.elements_begin(), val.elements_end(), LessForUuid<Type>());
}

template<class Type>
void sortNodes(Node<Type>& val)
{
  std::sort( val.nodes_begin(), val.nodes_end(), LessForUuid<Node<Type> >());
  std::for_each(val.nodes_begin(), val.nodes_end(), Sorter<Node<Type> >());
}


