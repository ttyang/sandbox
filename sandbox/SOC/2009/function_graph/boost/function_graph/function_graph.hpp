/**
 * Copyright (C) 2009
 * Michael Lopez
 * 
 * Issued under Boost Software License - Version 1.0
 * http://www.boost.org/LICENSE_1_0.txt
 * 
 */



#ifndef FUNCTION_GRAPH_HPP_
#define FUNCTION_GRAPH_HPP_

#include <boost/function.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace graph {

/**
 * function_graph_base handles the edge function. A user can define the function
 * through a boost::function or a functor, but the user must only have access to
 * this function through function graph via the function edge.
 */

template <typename F>
struct function_graph_base {
    // If the type F has an arity of 2, then it is the boost function syntax.
    // Otherwise, this function is either a functor or a boost function that is
    // already defined.
    typedef typename mpl::if_c<function_types::function_arity<F>::value == 2,
                               function<F>,
                               F>::type func_type;
    /** Types are deduced from F */
    
    /** Edge function that defines the implicit graph */
    func_type edge;
};


/**
 * function_graph is a data structure that creates an implicit graph based on a
 * function or functor that is either user defined or from the stl or boost.
 * 
 * For a more enlightening explanation, please refer to the documentation. 
 * 
 * @todo
 * Supply polished documentation
 * Implement domain and range
 * Implement an edge iterator
 */
 
template<typename F>
class function_graph : private function_graph_base<F>
{
    typedef function_graph_base<F> Base;
public:

    /** The edge function. */
    using Base::edge;
    
};

}   // graph namespace
}   // boost namespace

#endif /*FUNCTION_GRAPH_HPP_*/

