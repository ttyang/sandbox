/**
 * Copyright (C) 2009
 * Michael Lopez
 *
 * Issued under Boost Software License - Version 1.0
 * http://www.boost.org/LICENSE_1_0.txt
 *
 */

/** @todo Remember that all iterators contain references to the graphs from
 *  whence they come from. This means begin and end never need to be stored.
 */

#ifndef FUNCTION_GRAPH_HPP_
#define FUNCTION_GRAPH_HPP_

#include <boost/graph/graph_traits.hpp>
#include <boost/function.hpp>
#include <boost/function_types/function_arity.hpp>
#include <utility>
#include <boost/optional/optional_fwd.hpp>
#include <boost/range/iterator.hpp>
#include <iterator>

/** Error checking */
#include <iostream>

namespace boost {

template<typename Graph> struct function_graph_in_edge_iterator;
template<typename Graph> struct function_graph_out_edge_iterator;

/** @name Domain Tags
 * @description Traits that identify the function_graph as either having a
 * finite domain, a range, or having an infinite domain, no range.
 */

struct finite_domain_tag { };
struct infinite_domain_tag { };



/** @name Edge Descriptor */

namespace detail {

template <typename Result, typename Vertex>
struct func_graph_edge {
    typedef Result result_type;
    typedef Vertex vertex_descriptor;

    func_graph_edge(result_type result,
                    vertex_descriptor source,
                    vertex_descriptor target)
        : result_(result), source_(source), target_(target)
    { }

    result_type result_;
    vertex_descriptor source_;
    vertex_descriptor target_;
};



/** @name bind_edge
 * edge(u, v, g) is part of the adjacency matrix concept called Direct Edge
 * Access. The function must account for edges that already return. There is
 * specialization to account for functions that use bool and optional<T>.
 */

//@{
template <typename Result, typename Vertex>
std::pair<detail::func_graph_edge<Result, Vertex>, bool>
bind_edge(Result const& r, Vertex u, Vertex v)
{
    return std::make_pair(detail::func_graph_edge<Result, Vertex>(r, u, v),
                          true);
}

template <typename Vertex>
std::pair<detail::func_graph_edge<bool, Vertex>, bool>
bind_edge(bool r, Vertex u, Vertex v)
{
    return std::make_pair(typename detail::func_graph_edge<
                              bool, Vertex
                          >(r, u, v),
                          r);
}

// This overload is specific to optional<T>
template <typename OptType, typename Vertex>
std::pair<detail::func_graph_edge<optional<OptType>, Vertex>, bool>
bind_edge(optional<OptType> const& r, Vertex u, Vertex v)
{
    return std::make_pair(detail::func_graph_edge<
                              optional<OptType>, Vertex
                          >(r, u, v),
                          (bool)r);
}

}   // detail namespace



/** @name Function Graph Base
 * @description function_graph_base handles the edge function. A user can
 * define the function as a boost::function, but the user may only have access
 * to this function through the function graph via edge().
 */

//@{
template <typename Func>
struct function_graph_base {
    typedef Func function_type;
    typedef typename function_type::first_argument_type vertex_type;
    typedef typename function_type::result_type result_type;
    typedef typename detail::func_graph_edge<
                         result_type,
                         vertex_type
                     > edge_type;

    /** Constructors to allow for initialization of edge */
    function_graph_base(function_type const& f)
        : edge_(f)
    { }

    // Allow access to the function edge_ holds, not edge_ itself.
    result_type edge (vertex_type v1, vertex_type v2) const
    { return edge_(v1, v2); }

    function_type edge_;
};

template <typename Func, typename Rng>
struct function_graph_base_range {

    typedef Func function_type;
    typedef typename function_type::first_argument_type vertex_type;
    typedef typename function_type::result_type result_type;
    typedef typename detail::func_graph_edge<result_type,
                                             vertex_type> edge_type;
    typedef Rng vertex_iterator_range;

    /** Constructors to allow for initialization of edge */
    function_graph_base_range(function_type const& f,
                              vertex_iterator_range const& r)
        : edge_(f), range_(r)
    { }

    // Allow access to the function edge_ holds, not edge_ itself.
    result_type edge (vertex_type v1, vertex_type v2) const
    { return edge_(v1, v2); }

    function_type edge_;
    vertex_iterator_range range_;
};
//@}




/** @name Function Graph
 * @description function_graph is a data structure that implements implicit
 * graphs and more.
 * @note This is a trap for poor template parameters
 */

template <typename Function, typename Range = infinite_domain_tag>
struct function_graph;



/**
 * function_graph is a data structure that implements implicit graphs and more.
 * Better documentation and explanation of the data structure to come.
 *
 * @internal The typical user of function graph may not need to change edge
 * function during execution. However, since the code needed is trivial,
 * set_edge is part of the interface. Paired with it is the default constructor.
 */

template <typename Result, typename Vertex, typename Range>
struct function_graph<function<Result(Vertex, Vertex)>, Range>
    : private function_graph_base_range<function<Result(Vertex, Vertex)>, Range>
{
private:
    typedef function_graph_base_range<
                function<Result(Vertex, Vertex)>,
                Range
            > Base;
    typedef function_graph<function<Result(Vertex, Vertex)>, Range > This;

public:
    typedef typename Base::function_type function_type;
    typedef typename Base::vertex_type vertex_descriptor;
    typedef typename Base::edge_type edge_descriptor;
    typedef typename Base::result_type result_type;
    typedef std::size_t degree_size_type;
    typedef std::size_t vertices_size_type;
    typedef directed_tag directed_category;
    typedef disallow_parallel_edge_tag edge_parallel_category;
    typedef adjacency_matrix_tag traversal_category;
    typedef Range vertex_iterator_range;
    typedef typename range_iterator<vertex_iterator_range>::type
                         vertex_iterator;
    typedef function_graph_in_edge_iterator<This> in_edge_iterator;
    typedef function_graph_out_edge_iterator<This> out_edge_iterator;
    typedef finite_domain_tag domain_category;

    /** Constructor: takes a functor and range */
    function_graph(function_type const& f, vertex_iterator_range const& r)
        : Base(f, r)
    { }

    // @todo This must include the edge and the range
    bool operator==(This const& rhs)
    { return range_ == rhs.range_; }

    bool operator!=(This const& rhs)
    { return !(*this == rhs); }

    using Base::edge;
    using Base::range_;
};

/** @internal Allow a template function parameter without wrapping it with
 * boost::function.
 */
/*template <typename Result, typename Vertex, typename Range>
struct function_graph<Result(Vertex, Vertex), Range>
    : public function_graph<function<Result(Vertex, Vertex)>, Range>
{ };*/

// Specialization of function_graph without range
template <typename Result, typename Vertex>
struct function_graph<function<Result(Vertex, Vertex)>, infinite_domain_tag>
    : public function_graph_base<function<Result(Vertex, Vertex)> >
{
private:
    typedef function_graph_base<function<Result(Vertex, Vertex)> > Base;
    typedef function_graph<function<Result(Vertex, Vertex)> > This;

public:
    typedef typename Base::function_type function_type;
    typedef typename Base::vertex_type vertex_descriptor;
    typedef typename Base::edge_type edge_descriptor;
    typedef typename Base::result_type result_type;
    typedef std::size_t degree_size_type;
    typedef std::size_t vertices_size_type;
    typedef directed_tag directed_category;
    typedef disallow_parallel_edge_tag edge_parallel_category;
    typedef adjacency_matrix_tag traversal_category;
    typedef infinite_domain_tag domain_category;

    /** Constructor: takes a boost::function or functor */
    function_graph(function_type const& f)
        : Base(f)
    { }

    using Base::edge;
};

/*template <typename Result, typename Vertex>
struct function_graph<Result(Vertex, Vertex), infinite_domain_tag>
    : public function_graph<function<Result(Vertex, Vertex)> >
{ };*/



/** source(e, g) and target(e, g) are part of the incedence graph concept. */

template <typename Result, typename Vertex, typename Range>
Vertex source(detail::func_graph_edge<Result, Vertex> const& e,
              function_graph<function<Result(Vertex, Vertex)>, Range > const& g)
{ return e.source_; }

template <typename Result, typename Vertex, typename Range>
Vertex target(detail::func_graph_edge<Result, Vertex> const& e,
              function_graph<function<Result(Vertex, Vertex)>, Range > const& g)
{ return e.target_; }



#define FUNC_GRAPH \
    function_graph<function<Result(Vertex, Vertex)>, Range>

/** Degree functions */

template<typename Result, typename Vertex, typename Range>
typename FUNC_GRAPH::degree_size_type
out_degree(typename FUNC_GRAPH::vertex_descriptor const& u, FUNC_GRAPH const& g)
{
    typedef FUNC_GRAPH Graph;
    typedef typename Graph::vertex_iterator vertex_iterator;
    typedef typename FUNC_GRAPH::degree_size_type degree_size_type;

    degree_size_type out_edges();
    vertex_iterator vertex_at(begin(g.range_));
    vertex_iterator vertex_end(end(g.range_));
    for(;vertex_at != vertex_end; ++vertex_at)
    {
        if(g.edge_(u, *vertex_at)) ++out_edges;
    }

    return out_edges;
}

template<typename Result, typename Vertex, typename Range>
typename FUNC_GRAPH::degree_size_type
in_degree(typename FUNC_GRAPH::vertex_descriptor const& v, FUNC_GRAPH const& g)
{
    typedef FUNC_GRAPH Graph;
    typedef typename Graph::vertex_iterator vertex_iterator;
    typedef typename FUNC_GRAPH::degree_size_type degree_size_type;

    degree_size_type in_edges();
    vertex_iterator vertex_at(begin(g.range_));
    vertex_iterator vertex_end(end(g.range_));
    for(;vertex_at != vertex_end; ++vertex_at)
    {
        if(g.edge_(*vertex_at, v)) ++in_edges;
    }

    return in_edges;
}

template<typename Result, typename Vertex, typename Range>
typename FUNC_GRAPH::degree_size_type
degree(typename FUNC_GRAPH::vertex_descriptor const& v, FUNC_GRAPH const& g)
{ return in_degree(v, g) + out_degree(v, g); }



/** vertices(g) is part of the vertex list concept. */

template <typename Result, typename Vertex, typename Range>
std::pair<
    typename FUNC_GRAPH::vertex_iterator,
    typename FUNC_GRAPH::vertex_iterator
>
vertices(function_graph<function<Result(Vertex, Vertex)>, Range> const& g)
{ return std::make_pair(begin(g.range_), end(g.range_)); }



/** num_vertices(g) is part of the vertex list concept.
 * @note Uses boost::size() from the iterator_range concept.
 */
template<typename Result, typename Vertex, typename Range>
typename FUNC_GRAPH::vertices_size_type
num_vertices(FUNC_GRAPH const& g)
{ return size(g.range_); }



template <typename Result, typename Vertex, typename Range>
std::pair<typename FUNC_GRAPH::edge_descriptor, bool>
edge(typename FUNC_GRAPH::vertex_descriptor u,
     typename FUNC_GRAPH::vertex_descriptor v,
     FUNC_GRAPH const& g)
{
    typedef FUNC_GRAPH graph_type;
    typedef typename FUNC_GRAPH::result_type result_type;
    result_type result = g.edge(u, v);
    return detail::bind_edge(result, u, v);
}

//@}

/** in_edges(v, g) and out_edges(u, g)
 * @note This is a rough draft for testing purposes and readability. There will
 * be improvements later.
 */

template <typename Result, typename Vertex, typename Range>
std::pair<
    typename FUNC_GRAPH::in_edge_iterator,
    typename FUNC_GRAPH::in_edge_iterator
>
in_edges(typename FUNC_GRAPH::vertex_descriptor const& v, FUNC_GRAPH const& g)
{
    typedef function_graph<function<Result(Vertex, Vertex)>, Range> Graph;
    typedef typename Graph::in_edge_iterator in_edge_iterator;
    typedef typename Graph::vertex_iterator vertex_iterator;
    typedef std::pair<in_edge_iterator, in_edge_iterator> iter_range;

    vertex_iterator vertex_begin = begin(g.range_);
    vertex_iterator vertex_end = end(g.range_);
    in_edge_iterator in_edge_begin(g, v, vertex_begin, vertex_end);
    in_edge_iterator in_edge_end(g, v, vertex_end, vertex_end);

    return std::make_pair(in_edge_begin, in_edge_end);
}

template <typename Result, typename Vertex, typename Range>
std::pair<
    typename FUNC_GRAPH::out_edge_iterator,
    typename FUNC_GRAPH::out_edge_iterator
>
out_edges(typename FUNC_GRAPH::vertex_descriptor const& u, FUNC_GRAPH const& g)
{
    typedef function_graph<function<Result(Vertex, Vertex)>, Range> Graph;
    typedef typename Graph::out_edge_iterator out_edge_iterator;
    typedef typename Graph::vertex_iterator vertex_iterator;
    typedef std::pair<out_edge_iterator, out_edge_iterator> iter_range;

    vertex_iterator vertex_begin = begin(g.range_);
    vertex_iterator vertex_end = end(g.range_);
    out_edge_iterator out_edge_begin(g, u, vertex_begin, vertex_end);
    out_edge_iterator out_edge_end(g, u, vertex_end, vertex_end);

    return std::make_pair(out_edge_begin, out_edge_end);
}

/** @name In-Edge Iterator
 * @description Iterates through the in edges of a vertex.
 */

template<typename Graph>
struct function_graph_in_edge_iterator {
private:
    typedef function_graph_in_edge_iterator<Graph> This;

public:
    typedef Graph graph_type;
    typedef typename graph_type::vertex_iterator vertex_iterator;
    typedef typename graph_type::edge_descriptor edge_descriptor;
    typedef typename graph_type::vertex_descriptor vertex_descriptor;
    typedef typename graph_type::function_type function_type;

    /** Iterator traits */
    typedef std::input_iterator_tag iterator_category;
    typedef edge_descriptor value_type;
    typedef std::size_t different_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    /** @name Constructors */
    //@{
    
    function_graph_in_edge_iterator(graph_type const& g,
                                    vertex_descriptor const& v,
                                    vertex_iterator const& i_begin,
                                    vertex_iterator const& i_end)
        : g_(g),
          vertex_(v),
          i_begin_(i_begin),
          i_end_(i_end)
    {
        while((i_begin_ != i_end_) && !edge(*i_begin_, vertex_, g_).second)
        { ++i_begin_; }
    };

    function_graph_in_edge_iterator(This const& cp)
        : g_(cp.g_),
          vertex_(cp.vertex_),
          i_begin_(cp.i_begin_),
          i_end_(cp.i_end_)
    { };
    //@}

    /** Input Iterator operator overloads */
    This& operator++()
    {
        // Cycle through the range until an edge is found,
        // or the end of the list is found
        do {
            ++i_begin_;
        } while((i_begin_ != i_end_) &&
              !edge(*i_begin_, vertex_, g_).second);

        return *this;
    }

    edge_descriptor operator*()
    { return edge_descriptor(edge(*i_begin_, vertex_, g_).first); }

    graph_type const& g_;
    vertex_descriptor vertex_;
    vertex_iterator i_begin_;
    vertex_iterator i_end_;
};

template<typename Graph>
bool operator==(function_graph_in_edge_iterator<Graph> const& lhs,
                function_graph_in_edge_iterator<Graph> const& rhs)
{
    return lhs.vertex_ == rhs.vertex_ &&
           lhs.i_begin_ == rhs.i_begin_ &&
           lhs.i_end_ == rhs.i_end_;
}

template<typename Graph>
bool operator!=(function_graph_in_edge_iterator<Graph> const& lhs,
                function_graph_in_edge_iterator<Graph> const& rhs)
{
    return !(lhs.vertex_ == rhs.vertex_ &&
             lhs.i_begin_ == rhs.i_begin_ &&
             lhs.i_end_ == rhs.i_end_);
}



/** @name Out-Edge Iterator
 * @description Iterates through the in edges of a vertex.
 */

template<typename Graph>
struct function_graph_out_edge_iterator {
private:
    typedef function_graph_out_edge_iterator<Graph> This;

public:
    typedef Graph graph_type;
    typedef typename graph_type::vertex_iterator vertex_iterator;
    typedef typename graph_type::edge_descriptor edge_descriptor;
    typedef typename graph_type::vertex_descriptor vertex_descriptor;

    /** Iterator traits */
    typedef std::input_iterator_tag iterator_category;
    typedef edge_descriptor value_type;
    typedef std::size_t different_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    /** @name Constructors */
    //@{
    
    function_graph_out_edge_iterator(graph_type const& g,
                                    vertex_descriptor const& v,
                                    vertex_iterator const& i_begin,
                                    vertex_iterator const& i_end)
        : g_(g),
          vertex_(v),
          i_begin_(i_begin),
          i_end_(i_end)
    {
        while((i_begin_ != i_end_) && !edge(vertex_, *i_begin_, g_).second)
        { ++i_begin_; }
    }

    function_graph_out_edge_iterator(This const& cp)
        : g_(cp.g_),
          vertex_(cp.vertex_),
          i_begin_(cp.i_begin_),
          i_end_(cp.i_end_)
    { }
    //@}

    /** Input Iterator operator overloads */
    This& operator++()
    {
        // Cycle through the range until an edge is found,
        // or the end of the list is found
        do {
            ++i_begin_;
        } while((i_begin_ != i_end_) &&
              !edge(vertex_, *i_begin_, g_).second);

        return *this;
    }

    edge_descriptor operator*()
    { return edge_descriptor(edge(vertex_, *i_begin_, g_).first); }

    graph_type const& g_;
    vertex_descriptor vertex_;
    vertex_iterator i_begin_;
    vertex_iterator i_end_;
};

template<typename Graph>
bool operator==(function_graph_out_edge_iterator<Graph> const& lhs,
                function_graph_out_edge_iterator<Graph> const& rhs)
{
    return lhs.vertex_ == rhs.vertex_ &&
           lhs.i_begin_ == rhs.i_begin_ &&
           lhs.i_end_ == rhs.i_end_;
}

template<typename Graph>
bool operator!=(function_graph_out_edge_iterator<Graph> const& lhs,
                function_graph_out_edge_iterator<Graph> const& rhs)
{
    return !(lhs.vertex_ == rhs.vertex_ &&
             lhs.i_begin_ == rhs.i_begin_ &&
             lhs.i_end_ == rhs.i_end_);
}

/** Adjacency Iterator - iterates through all of the edges adjacent to a vector
 *  v.
 *  @todo
 */
template<typename Graph>
struct function_graph_adjacency_iterator {
private:
    typedef function_graph_adjacency_iterator<Graph> This;

public:
    typedef Graph graph_type;
    typedef typename graph_type::vertex_iterator vertex_iterator;
    typedef typename graph_type::edge_descriptor edge_descriptor;
    typedef typename graph_type::vertex_descriptor vertex_descriptor;

    /** Iterator traits */
    typedef std::input_iterator_tag iterator_category;
    typedef edge_descriptor value_type;
    typedef std::size_t different_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    /** @name Constructor */
    //@{
    function_graph_adjacency_iterator(graph_type const& g,
                                      vertex_descriptor const& vertex)
        : g_(g),
          vertex_(vertex),
          i_at_(begin(g_.range_)),
          in_edge_check_(true)
    {
        const vertex_iterator i_end = end(g_.range_);
        const vertex_iterator i_begin = begin(g_.range_);

        while(i_at_ != i_end && !edge(*i_begin, vertex_, g_).second)
        { ++i_at_; }
        if(i_at_ == i_end)
        {
            in_edge_check_ = false;
            i_at_ = i_begin;
            while(i_begin != i_end && !edge(vertex_, *i_begin, g_).second)
            {  ++i_at_; }
        }
    }

    function_graph_adjacency_iterator(This const& cp)
        : g_(cp.g_),
          vertex_(cp.vertex_),
          i_at_(cp.i_at_),
          in_edge_check_(cp.in_edge_check_)
    { }
    //@}

    This& operator++()
    {
        const vertex_iterator i_end = end(g_.range_);
        const vertex_iterator i_begin = begin(g_.range_);

        if(in_edge_check_)
        {
            do {
                ++i_at_;
            } while(i_at_ != i_end && !edge(*i_begin, vertex_, g_).second);
            if(i_at_ == i_end) in_edge_check_ = false;
        }
        if(!in_edge_check_)
        {
            do {
                ++i_at_;
            } while(i_at_ != i_end && !edge(vertex_, *i_begin, g_).second);
        }

        return *this;
    }

    vertex_descriptor operator*()
    {
        return *i_at_;
    }

    graph_type const& g_;
    vertex_descriptor vertex_;
    vertex_iterator i_at_;
    bool in_edge_check_;
};

#undef FUNC_GRAPH

}   // boost namespace

#endif /*FUNCTION_GRAPH_HPP_*/

