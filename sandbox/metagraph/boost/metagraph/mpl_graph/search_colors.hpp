#ifndef BOOST_METAGRAPH_MPL_GRAPH_SEARCH_COLORS_HPP_INCLUDED
#define BOOST_METAGRAPH_MPL_GRAPH_SEARCH_COLORS_HPP_INCLUDED

namespace boost {
namespace metagraph {
namespace mpl_graph {

struct search_colors {
    struct White {};
    struct Gray {};
    struct Black {};
};

struct create_search_color_map : mpl::map<> {};

struct search_color_map_operations {
    template<typename Node, typename Color, typename State>
    struct set_color :
        mpl::insert<State, mpl::pair<Node, Color> >
    {};
    template<typename Node, typename State>
    struct get_color :
        mpl::if_<mpl::has_key<State, Node>,
                 mpl::at<State, Node>,
                 search_colors::White>
    {};
};


} // namespace mpl_graph
} // namespace metagraph
} // namespace boost


#endif // BOOST_METAGRAPH_MPL_GRAPH_SEARCH_COLORS_HPP_INCLUDED
