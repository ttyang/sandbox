#ifndef BOOST_METAGRAPH_MPL_GRAPH_DETAIL_INCIDENCE_LIST_GRAPH_IPP_INCLUDED
#define BOOST_METAGRAPH_MPL_GRAPH_DETAIL_INCIDENCE_LIST_GRAPH_IPP_INCLUDED

// these metafunctions provide the metadata structures needed by the public interface 
// in mpl_graph.hpp

#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/type_traits.hpp>

namespace boost {
namespace metagraph {
namespace mpl_graph {
namespace detail {

// tag to identify this graph implementation (not defined)
struct incidence_list_tag;
    
// clarifiers
template<typename EST> struct fetch_edge : 
    mpl::front<EST> {};
template<typename EST> struct fetch_source : 
    mpl::deref<typename mpl::next<typename mpl::begin<EST>::type>::type> {};
template<typename EST> struct fetch_target : 
    mpl::back<EST> {};

//#define MPL_GRAPH_PRODUCE_OUTMAP_AS_MAP
#ifdef MPL_GRAPH_PRODUCE_OUTMAP_AS_MAP
    // this implementation didn't work on msvc - anyway not sure if it's more efficient
    // to build all maps at once at the expense of lots of map updates, or to use
    // the many pass, easier-to-read filter-and-build algs below.
// Source->Edge->Target map for out_*, adjacent_vertices
template<typename ESTSequence>
struct produce_il_outs_map :
    mpl::fold<ESTSequence,
              mpl::map<>,
              mpl::insert<mpl::_1,
                          mpl::pair<fetch_source<mpl::_2>,
                                    mpl::insert<mpl::if_<mpl::has_key<mpl::_1,fetch_source<mpl::_2> >,
                                                         mpl::at<mpl::_1,fetch_source<mpl::_2> >,
                                                         mpl::map<> >,
                                                mpl::pair<fetch_edge<mpl::_2>, fetch_target<mpl::_2> > > > > >
{};
template<typename Source, typename ESTSequence>
struct produce_out_map<incidence_list_tag, Source, ESTSequence> :
    mpl::at<typename produce_il_outs_map<ESTSequence>::type, Source>
{};
#else // produce out map by filtering est list  
// Edge->Target map for an Source for out_*, adjacent_vertices
template<typename Source, typename ESTSequence>
struct produce_out_map<incidence_list_tag, Source, ESTSequence> :
    mpl::fold<typename mpl::filter_view<ESTSequence, boost::is_same<fetch_source<mpl::_1>,Source> >::type,
         mpl::map<>,
         mpl::insert<mpl::_1,mpl::pair<fetch_edge<mpl::_2>,fetch_target<mpl::_2> > > >
{};
#endif

// Edge->Source map for a Target for in_*, degree
template<typename Target, typename ESTSequence>
struct produce_in_map<incidence_list_tag, Target, ESTSequence> :
    mpl::fold<typename mpl::filter_view<ESTSequence, 
                                        boost::is_same<fetch_target<mpl::_1>,Target> >::type,
         mpl::map<>,
         mpl::insert<mpl::_1,mpl::pair<fetch_edge<mpl::_2>,fetch_source<mpl::_2> > > >

{};
// Edge->pair<Source,Target> map for source, target
template<typename ESTSequence>
struct produce_edge_st_map<incidence_list_tag, ESTSequence> :
    mpl::fold<ESTSequence,
         mpl::map<>,
         mpl::insert<mpl::_1,mpl::pair<fetch_edge<mpl::_2>,
                        mpl::pair<fetch_source<mpl::_2>, 
                             fetch_target<mpl::_2> > > > >
{};
// Vertex set for VertexListGraph
template<typename ESTSequence>
struct produce_vertex_set<incidence_list_tag, ESTSequence> :
    mpl::fold<ESTSequence,
         typename mpl::fold<ESTSequence,
                       mpl::set<>,
                       mpl::insert<mpl::_1,fetch_target<mpl::_2> >
                       >::type,
         mpl::insert<mpl::_1, fetch_source<mpl::_2> > >
{};
// Edge set for EdgeListGraph
template<typename ESTSequence>
struct produce_edge_set<incidence_list_tag, ESTSequence> :
    mpl::fold<ESTSequence,
        mpl::set<>,
        mpl::insert<mpl::_1,fetch_edge<mpl::_2> > >
{};
}
}
}
}

#endif // BOOST_METAGRAPH_MPL_GRAPH_DETAIL_INCIDENCE_LIST_GRAPH_IPP_INCLUDED
