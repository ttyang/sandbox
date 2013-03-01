#pragma once

#include <ostream>
#include <iterator>
#include "std_algorithm.h"

#include "Syncable/Syncable_Concept.h"
#include "Syncable/Vector.h"
#include "Syncable/Node.h"
#include "Playable.h"

template<class Mergable>
struct Merger
{
  Mergable operator()(Mergable const& lhs, Mergable const& rhs)
  { 
      return std::move(merge(lhs, rhs)); 
  }
};

template<class Type, class UuidT, class TimeT>
Node<Type,UuidT,TimeT>
merge(Node<Type,UuidT,TimeT>const& lhs, Node<Type,UuidT,TimeT>const& rhs)
{
  typedef Node<Type,UuidT,TimeT> NodeT;
  typedef typename NodeT::ContentVec ContentVec;
  NodeT merged;
  merged.setUuid(lhs.uuid());
  merged.setTime(std::max(lhs.time(), rhs.time()));
  merged.setName(lhs.name());

  merged.setContent(mergeElements(lhs, rhs));
  merged.setChildren(mergeNodes(lhs, rhs));

  return std::move(merged);
}


template<class Type, class UuidT, class TimeT>
typename Node<Type,UuidT,TimeT>::ContentVec
mergeElements(Node<Type,UuidT,TimeT>const& lhs, Node<Type,UuidT,TimeT>const& rhs)
{
  typedef Node<Type,UuidT,TimeT>          NodeT;
  typedef typename NodeT::ContentVec      Elements;
  typedef typename Elements::value_type   Element;

  Elements merged;
  merged.reserve(lhs.element_count() + rhs.element_count());
  merged.setUuid(lhs.contentUuid());
  merged.setName(lhs.contentName());
  merged.setTime(std::max(lhs.contentTime(), rhs.contentTime()));

  std::general_union( lhs.elements_begin(), lhs.elements_end()
                    , rhs.elements_begin(), rhs.elements_end()
                    , std::back_inserter(merged)
                    , LessForUuid<Element>()
                    , std::Maximum<LessForTime<Element> >() 
                    );

  return std::move(merged);
}


template<class Type, class UuidT, class TimeT>
typename Node<Type,UuidT,TimeT>::NodeVec
mergeNodes(Node<Type,UuidT,TimeT>const& lhs, Node<Type,UuidT,TimeT>const& rhs)
{
  typedef typename Node<Type>::NodeVec Nodes;
  typedef typename Nodes::value_type NodeType;

  Nodes merged;
  merged.reserve(lhs.node_count() + rhs.node_count());
  merged.setUuid(lhs.childrenUuid());
  merged.setName(lhs.childrenName());
  merged.setTime(std::max(lhs.childrenTime(), rhs.childrenTime()));
  
  std::general_union( lhs.nodes_begin(), lhs.nodes_end()
                    , rhs.nodes_begin(), rhs.nodes_end()
                    , std::back_inserter(merged)
                    , LessForUuid<NodeType>()
                    , Merger<NodeType>()
                    );
                    
  return std::move(merged);
}


template<class Type, class UuidT, class TimeT>
void sort(Node<Type,UuidT,TimeT>& value)
{
  typedef Node<Type,UuidT,TimeT> NodeT;
  typedef typename NodeT::ContentVec ContentVec;

  sortElements(value);
  sortNodes(value);
}

template<class Type> struct Sorter
{
  void operator()(Type& value){ sort(value); }
};

template<class Type, class UuidT, class TimeT>
void sortElements(Node<Type,UuidT,TimeT>& value)
{
  std::sort( value.elements_begin(), value.elements_end(), LessForUuid<Type>() );
}

template<class Type, class UuidT, class TimeT>
void sortNodes(Node<Type,UuidT,TimeT>& value)
{
  std::for_each( value.nodes_begin(), value.nodes_end(), Sorter<Node<Type> >() );
  std::sort( value.nodes_begin(), value.nodes_end(), LessForUuid<Node<Type> >() );
}

