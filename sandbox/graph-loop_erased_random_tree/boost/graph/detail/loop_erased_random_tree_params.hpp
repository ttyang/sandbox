// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_PARAMS_HPP
#define BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_PARAMS_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/keywords/rng_engine.hpp>
#include <boost/graph/keywords/source_vertex.hpp>
#include <boost/graph/keywords/terminate_predicate.hpp>

#define BOOST_BGL_DECLARE_NAMED_PARAMS \
        BOOST_BGL_ONE_PARAM_CREF(weight_map, edge_weight) \
        BOOST_BGL_ONE_PARAM_CREF(predecessor_map, vertex_predecessor) \
        BOOST_BGL_ONE_PARAM_CREF(root_vertex, root_vertex) \
        BOOST_BGL_ONE_PARAM_CREF(color_map, vertex_color) \
        BOOST_BGL_ONE_PARAM_CREF(visitor, graph_visitor) \
        BOOST_BGL_ONE_PARAM_CREF(distance_compare, distance_compare) \
        BOOST_BGL_ONE_PARAM_CREF(distance_combine, distance_combine) \
//

#define BOOST_BGL_LOOP_ERASED_RANDOM_TREE_DECLARE_PARAMS \
        BOOST_BGL_ONE_PARAM_REF(rng_engine, rng_engine) \
        BOOST_BGL_ONE_PARAM_CREF(source_vertex, source_vertex) \
        BOOST_BGL_ONE_PARAM_CREF(terminate_predicate, terminate_predicate) \
//

namespace boost {
  namespace detail {

    template <typename T, typename Tag, typename Base = no_property>
    struct loop_erased_random_tree_params : Base
    {
        typedef loop_erased_random_tree_params self;
        typedef Base                           next_type;
        typedef Tag                            tag_type;
        typedef T                              value_type;

        T m_value;

        loop_erased_random_tree_params(T v = T()) : Base(), m_value(v)
        {
        }

        loop_erased_random_tree_params(T v, Base const& b)
          : Base(b), m_value(v)
        {
        }

#define BOOST_BGL_ONE_PARAM_REF(name, key) \
        template <typename PType> \
        inline loop_erased_random_tree_params< \
            ::boost::reference_wrapper<PType> \
          , BOOST_PP_CAT(key, _t) \
          , self \
        > \
            name(PType& p) const \
        { \
            typedef loop_erased_random_tree_params< \
                        ::boost::reference_wrapper<PType> \
                      , BOOST_PP_CAT(key, _t) \
                      , self \
                    > \
                    Params; \
            return Params(::boost::ref(p), *this); \
        } \
//

#define BOOST_BGL_ONE_PARAM_CREF(name, key) \
        template <typename PType> \
        inline loop_erased_random_tree_params< \
            PType \
          , BOOST_PP_CAT(key, _t) \
          , self \
        > \
            name(PType const& p) const \
        { \
            typedef loop_erased_random_tree_params< \
                        PType \
                      , BOOST_PP_CAT(key, _t) \
                      , self \
                    > \
                    Params; \
            return Params(p, *this); \
        } \
//

        BOOST_BGL_LOOP_ERASED_RANDOM_TREE_DECLARE_PARAMS

#undef BOOST_BGL_ONE_PARAM_CREF
#undef BOOST_BGL_ONE_PARAM_REF

#define BOOST_BGL_ONE_PARAM_REF(name, key) \
        template <typename PType> \
        inline bgl_named_params< \
            ::boost::reference_wrapper<PType> \
          , BOOST_PP_CAT(key, _t) \
          , self \
        > \
            name(PType& p) const \
        { \
            typedef bgl_named_params< \
                        ::boost::reference_wrapper<PType> \
                      , BOOST_PP_CAT(key, _t) \
                      , self \
                    > \
                    Params; \
            return Params(::boost::ref(p), *this); \
        } \
//

#define BOOST_BGL_ONE_PARAM_CREF(name, key) \
        template <typename PType> \
        inline bgl_named_params<PType,BOOST_PP_CAT(key, _t),self> \
            name(PType const& p) const \
        { \
            typedef bgl_named_params<PType,BOOST_PP_CAT(key, _t),self> \
                    Params; \
            return Params(p, *this); \
        } \
//

        BOOST_BGL_DECLARE_NAMED_PARAMS

#undef BOOST_BGL_ONE_PARAM_CREF
#undef BOOST_BGL_ONE_PARAM_REF

        template <typename PType>
        inline bgl_named_params<PType,vertex_color_t,self>
            vertex_color_map(PType const& p) const
        {
            return this->color_map(p);
        }
    };

    typedef loop_erased_random_tree_params<char,unused_tag_type>
            no_loop_erased_random_tree_params;

    template <>
    struct convert_bgl_params_to_boost_parameter<
        no_loop_erased_random_tree_params
    >
    {
        typedef ::boost::parameter::aux::empty_arg_list type;

        static type conv(no_property const&)
        {
            return type();
        }
    };
  }  // namespace detail

    inline detail::no_loop_erased_random_tree_params
        make_loop_erased_random_tree_params()
    {
        return detail::no_loop_erased_random_tree_params();
    }

#if 0
#define BOOST_BGL_ONE_PARAM_REF(name, key) \
    template <typename PType> \
    inline detail::loop_erased_random_tree_params< \
        ::boost::reference_wrapper<PType> \
      , BOOST_PP_CAT(key, _t) \
    > \
        name(PType& p) const \
    { \
        typedef detail::loop_erased_random_tree_params< \
                    ::boost::reference_wrapper<PType> \
                  , BOOST_PP_CAT(key, _t) \
                > \
                Params; \
        return Params(::boost::ref(p)); \
    } \
//

#define BOOST_BGL_ONE_PARAM_CREF(name, key) \
    template <typename PType> \
    inline detail::loop_erased_random_tree_params< \
        PType \
      , BOOST_PP_CAT(key, _t) \
    > \
        name(PType const& p) const \
    { \
        typedef detail::loop_erased_random_tree_params< \
                    PType \
                  , BOOST_PP_CAT(key, _t) \
                > \
                Params; \
        return Params(p); \
    } \
//

	BOOST_BGL_LOOP_ERASED_RANDOM_TREE_DECLARE_PARAMS

#undef BOOST_BGL_ONE_PARAM_CREF
#undef BOOST_BGL_ONE_PARAM_REF
#endif
}  // namespace boost

#undef BOOST_BGL_LOOP_ERASED_RANDOM_TREE_DECLARE_PARAMS
#undef BOOST_BGL_DECLARE_NAMED_PARAMS

#endif  // BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_PARAMS_HPP

