#pragma once

#include "Syncable/Vector.h"
#include "Syncable/Node.h"
#include "Playable.h"

typedef Vector<Playable<int> >   Playlist;
typedef Vector<Playlist>         Playlists;
typedef Vector<Node<Playlist> >  NodeList;


Playlists content_1(int uuid, std::string const& name)
{
      Playlist pl1(3, 2, " pl_1 ");
        pl1.reserve(2);
        pl1.emplace_back(Playable<int>(11));

      Playlist pl2(2, 5, " pl_2 ");
        pl2.reserve(2);
        pl2.emplace_back(Playable<int>(22));
        pl2.emplace_back(Playable<int>(21));

  Playlists pls1(uuid, 0, name);
    pls1.reserve(2);
    pls1.emplace_back(std::move(pl1));
    pls1.emplace_back(std::move(pl2));

  return std::move(pls1);
}

Playlists content_2(int uuid, std::string const& name)
{

      Playlist pl1(3, 6, " pl_3 ");
        pl1.reserve(3);
        pl1.emplace_back(Playable<int>(11));
        pl1.emplace_back(Playable<int>(12));
        pl1.emplace_back(Playable<int>(11));

      Playlist pl2(7, 5, " pl_4 ");
        pl2.emplace_back(Playable<int>(22));
        pl2.emplace_back(Playable<int>(21));

  Playlists pls1(uuid, 0, name);
    pls1.emplace_back(std::move(pl1));
    pls1.emplace_back(std::move(pl2));

  return std::move(pls1);
}

NodeList children_0(int uuid, int time, std::string const& name, Playlists pls)
{
      //CL Node<Playlist> node(6, "node_1", pls);
  NodeList nodes1(uuid, time, " nodes_1 ");
      nodes1.emplace_back(Node<Playlist>(6, "node_1", std::move(pls)));
  return std::move(nodes1);
}


