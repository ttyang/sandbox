// TreeSync1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Object.h"
#include "Tree.h"
#include "TreeMaker.h"

typedef std::vector<object> collection;
typedef collection::iterator       coll_iter;
typedef collection::const_iterator coll_citer;


template<class Type>
std::string type_name(Type const& value)
{
  return typeid(value).name();
}

void draw(const int& val, std::ostream& out, size_t pos)
{ 
  out << std::string(pos, ' ') << "int: " << val << std::endl; 
}

void draw(const double& val, std::ostream& out, size_t pos)
{ 
  out << std::string(pos, ' ') << "dbl: " << val << std::endl; 
}

void draw(const collection& col, std::ostream& out, size_t pos)
{
  out << std::string(pos,' ') << "<collection>\n";
  for(coll_citer it = col.begin(); it != col.end(); ++it)
    draw(*it, out, pos+2);

  out << std::string(pos,' ') << "</collection>\n";
}

template<class Type>
void draw(const Vec<Type>& obj, std::ostream& out, size_t pos)
{
  typedef typename Vec<Type>::const_iterator citer;
  out << std::string(pos,' ') 
    //<< type_name(obj) << "{\n";
    << "<Vec>[" << obj.name() << "](" << obj.uuid() << ","  << obj.time() << ")\n";
  for(citer it = obj.begin(); it != obj.end(); ++it)
    draw(*it, out, pos+2);

  out << std::string(pos,' ') 
    //<< "}\n";
    << "</Vec>\n";
}



int _tmain(int argc, _TCHAR* argv[])
{
  std::cout << "Hello concept\n";

  collection coll;

  coll.push_back(42);


  Playlists content1   = content_1(4, " pls_1 ");


  /*
  //--- Nodes -----------------------
  Playlists content1   = content_1(4, " pls_1 ");
  NodeList  children1  = children_0(5, 6, "children_1", content1);

  Playlists content2   = content_2(9, " pls_2 ");
  NodeList  children2  = children_0(10, 6, "children_2", content1);

  Node<Playlist> node1 = Node<Playlist>(8, " node_1 ", content1, children1);

  Node<Playlist> node2 = Node<Playlist>(11, " node_2 ", content2, children2);


  draw(node1, std::cout, 0);

  sort(node1);
  sort(node2);
  std::cout << "node1 ========================================\n";
  draw(node1, std::cout, 0);
  std::cout << "node2 ========================================\n";
  draw(node2, std::cout, 0);

  
  Node<Playlist> merged = merge(node1, node2);
  std::cout << "merged ========================================\n";
  draw(merged, std::cout, 0);
  */

  return 0;
}

