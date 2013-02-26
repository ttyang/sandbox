// TreeSync1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Object.h"
#include "Tree.h"

typedef std::vector<object> collection;
typedef collection::iterator       coll_iter;
typedef collection::const_iterator coll_citer;

typedef Vec<Playable<int> >   Playlist;
typedef Vec<Playlist>         Playlists;
typedef Vec<Node<Playlist> >  NodeList;


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

  //--- Playlist --------------------
  Playlist pl1(1, 2, " pl_1 ");
    pl1.push_back(Playable<int>(11));
    pl1.push_back(Playable<int>(12));

  Playlist pl2(2, 5, " pl_2 ");
    pl2.push_back(Playable<int>(21));
    pl2.push_back(Playable<int>(22));

  Playlist pl3(3, 3, " pl_3 ");
    pl2.push_back(Playable<int>(31));


  //--- Playlists -------------------
  Playlists pls1(4, 0, " pls_1 ");
    pls1.push_back(pl1);
    pls1.push_back(pl3);

  Playlists pls2(5, 0, " pls_1 ");
    pls2.push_back(pl2);
    pls2.push_back(pl3);

  //--- Nodes -----------------------
  Node<Playlist> node1(6, " node_1 ", pls1);
    NodeList nodes1(7, 2, " nodes_1 ");
      nodes1.push_back(node1);

  Node<Playlist> node2(8, " node_2 ", pls2, nodes1);

  //=================================
  draw(node2, std::cout, 0);

  std::cout << "========================================\n";
  //Node<Playlist> merged = merge(node1, node2);
  //draw(merged, std::cout, 0);

  sort(node2);
  draw(node2, std::cout, 0);

  return 0;
}

