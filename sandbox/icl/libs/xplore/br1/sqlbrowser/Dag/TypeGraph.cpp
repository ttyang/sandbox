#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>

#include <boost/property_map/property_map.hpp>

#include "StringVisitor2.h"

#include "Dag/TypeGraph.h"

//using namespace dag::db;
struct VertexProps { //CL...
  boost::default_color_type color;
  std::size_t discover_time;
};


typedef boost::property_map<dag::db::TypeGraph::tGraph, boost::vertex_index_t>::type IndexMap;

template <class Iterator, class IDMap>
class iterator_map
{
public:
  typedef typename boost::property_traits<IDMap>::key_type key_type;
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef boost::lvalue_property_map_tag category;

  iterator_map(Iterator i = Iterator(),
              const IDMap& id = IDMap())
    : m_iter(i), m_id(id) { }
  Iterator m_iter;
  IDMap m_id;
};

template <class Iter, class ID>
typename std::iterator_traits<Iter>::value_type
get(const iterator_map<Iter,ID>& i,
    typename boost::property_traits<ID>::key_type key)
{
  return i.m_iter[i.m_id[key]];
}
template <class Iter, class ID>
void
put(const iterator_map<Iter,ID>& i,
    typename boost::property_traits<ID>::key_type key,
    const typename std::iterator_traits<Iter>::value_type& value)
{
  i.m_iter[i.m_id[key]] = value;
}
template <class Iter, class ID>
typename std::iterator_traits<Iter>::reference
at(const iterator_map<Iter,ID>& i,
    typename boost::property_traits<ID>::key_type key)
{
  return i.m_iter[i.m_id[key]];
}


dag::db::tString dag::db::TypeGraph::depthFirstString()
{
    typedef dag::db::TypeGraph::vertex_descriptor vertex_descriptor;
    typedef dag::db::TypeGraph::tVertex2Depth     tVertex2Depth;

    tVertex2Depth vertexDepth;
    QString tygraAsString;

    boost::depth_first_search(
        m_aGraph
      , boost::visitor(make_dfs_visitor(boost::make_list(
                                              StringVisitor2::OnDiscoverVertex(&tygraAsString, vertexDepth)
                                            , StringVisitor2::OnExamineEdge   (&tygraAsString, vertexDepth)
                                            , StringVisitor2::OnFinishVertex  (&tygraAsString, vertexDepth)
                                            )
                      ))
    );

    return tygraAsString;

}
