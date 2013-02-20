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
void draw(const Vec<Type>& col, std::ostream& out, size_t pos)
{
  out << std::string(pos,' ') << "<Vec>\n";
  for(coll_citer it = col.begin(); it != col.end(); ++it)
    draw(*it, out, pos+2);

  out << std::string(pos,' ') << "</Vec>\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
  std::cout << "Hello concept\n";

  collection coll;

  Playlist pl1;
  pl1.push_back(Playable<int>(43));
  pl1.push_back(Playable<int>(44));

  Playlist pl2;
  pl2.push_back(Playable<int>(53));
  pl2.push_back(Playable<int>(54));
  //draw(pl, std::cout, 0);

  Playlists pls1;
  pls1.push_back(pl1);
  Playlists pls2;
  pls2.push_back(pl2);

  Node<Playlist> node1(pls1);
  NodeList nodes1;
  nodes1.push_back(node1);
  Node<Playlist> node2(pls2, nodes1);
  
  coll.push_back(node1);
  coll.push_back(node2);
  draw(coll, std::cout, 0);

	return 0;
}

