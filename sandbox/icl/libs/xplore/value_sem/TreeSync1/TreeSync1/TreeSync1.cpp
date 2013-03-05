#include <iostream>

#include "TreeMerge.h"
#include "TreeMaker.h"


template<class T>
void draw(const T& x, std::ostream& out, size_t pos)
{ out << std::string(pos, ' ') << x << std::endl; }


template<class Type>
void draw(const Vector<Type>& obj, std::ostream& out, size_t pos)
{
  typedef typename Vector<Type>::const_iterator citer;
  out << std::string(pos,' ') 
    << "<Vector>[" << obj.name() << "](" << obj.uuid() << ","  << obj.time() << ")\n";
  for(citer it = obj.begin(); it != obj.end(); ++it)
    draw(*it, out, pos+2);

  out << std::string(pos,' ') 
    << "</Vector>\n";
}



int main()
{
  std::cout << "Hello concept\n";

  //--- Nodes -----------------------
  Playlists content1   = content_1(4, " pls_1 ");
  NodeList  children1  = children_0(5, 6, "children_1", content1);

  Playlists content2   = content_2(9, " pls_2 ");
  NodeList  children2  = children_0(10, 6, "children_2", content1);

  Node<Playlist> node1 = Node<Playlist>(8, " node_1 ", content1, children1);

  Node<Playlist> node2 = Node<Playlist>(11, " node_2 ", content2, children2);


  draw(node1, std::cout, 0);

  std::cout << ">>sort(node1) ========================================\n";
  sort(node1);
  std::cout << "\n<<sort(node1) ========================================\n";
  sort(node2);
  std::cout << "node1 ========================================\n";
  draw(node1, std::cout, 0);
  std::cout << "node2 ========================================\n";
  draw(node2, std::cout, 0);

  
  std::cout << "\n>>merge ========================================\n";
  Node<Playlist> merged = merge(node1, node2);
  std::cout << "\n<<merge ========================================\n";
  std::cout << "merged ========================================\n";
  draw(merged, std::cout, 0);

  return 0;
}

