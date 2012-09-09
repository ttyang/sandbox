// Copyright (C) 2004-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_PRM_HPP
#define BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_PRM_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/keywords/rng_engine.hpp>
#include <boost/graph/keywords/source_vertex.hpp>
#include <boost/graph/keywords/terminate_predicate.hpp>

#define BOOST_BGL_DECLARE_NAMED_PARAMS \
        BOOST_BGL_ONE_PARAM_CREF(weight_map, edge_weight) \
        BOOST_BGL_ONE_PARAM_REF(predecessor_map, vertex_predecessor) \
        BOOST_BGL_ONE_PARAM_CREF(root_vertex, root_vertex) \
        BOOST_BGL_ONE_PARAM_REF(color_map, vertex_color) \
        BOOST_BGL_ONE_PARAM_CREF(visitor, graph_visitor) \
        BOOST_BGL_ONE_PARAM_CREF(distance_compare, distance_compare) \
        BOOST_BGL_ONE_PARAM_CREF(distance_combine, distance_combine) \
//

#define BOOST_BGL_LOOP_ERASED_RANDOM_TREE_DECLARE_PARAMS \
        BOOST_BGL_ONE_PARAM_REF(rng_engine, rng_engine) \
        BOOST_BGL_ONE_PARAM_CREF(source_vertex, source_vertex) \
        BOOST_BGL_ONE_PARAM_CREF(terminate_predicate, terminate_predicate) \
//

namespace boost { namespace detail {

    template <typename T, typename Tag, typename Base = no_property>
    struct loop_erased_random_tree_params
    {
        typedef loop_erased_random_tree_params self;
        typedef Base                           next_type;
        typedef Tag                            tag_type;
        typedef T                              value_type;

        T m_value;
        Base m_base;

        loop_erased_random_tree_params(T v = T())
          : m_value(v), m_base()
        {
        }

        loop_erased_random_tree_params(T v, Base const& b)
          : m_value(v), m_base(b)
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

        static type conv(no_loop_erased_random_tree_params const&)
        {
            return type();
        }
    };

    template <typename P, typename R>
    struct convert_bgl_params_to_boost_parameter<
        loop_erased_random_tree_params<P,int,R>
    >
    {
        typedef convert_bgl_params_to_boost_parameter<R> rest_conv;
        typedef typename rest_conv::type type;

        static type conv(loop_erased_random_tree_params<P,int,R> const& x)
        {
            return rest_conv::conv(x.m_base);
        }
    };
}}  // namespace boost::detail

namespace boost {

    inline detail::no_loop_erased_random_tree_params
        make_loop_erased_random_tree_params()
    {
        return detail::no_loop_erased_random_tree_params();
    }

    template <typename T, typename Tag, typename Base>
    struct lookup_named_param<
        Tag
      , detail::loop_erased_random_tree_params<T,Tag,Base>
    >
    {
        typedef T type;

        static type const&
            get(detail::loop_erased_random_tree_params<T,Tag,Base> const& p)
        {
            return p.m_value;
        }
    };

    template <typename Tag1, typename T, typename Tag, typename Base>
    struct lookup_named_param<
        Tag1
      , detail::loop_erased_random_tree_params<T,Tag,Base>
    >
    {
        typedef typename lookup_named_param<Tag1,Base>::type type;

        static type const&
            get(detail::loop_erased_random_tree_params<T,Tag,Base> const& p)
        {
            return lookup_named_param<Tag1,Base>::get(p.m_base);
        }
    };

    template <typename T, typename Tag, typename Base, typename Def>
    struct lookup_named_param_def<
        Tag
      , detail::loop_erased_random_tree_params<T,Tag,Base>
      , Def
    >
    {
        typedef T type;

        static const type&
            get(
                detail::loop_erased_random_tree_params<T,Tag,Base> const& p
              , Def const& def
            )
        {
            return p.m_value;
        }
    };

    template <
        typename Tag1
      , typename T
      , typename Tag
      , typename Base
      , typename Def
    >
    struct lookup_named_param_def<
        Tag1
      , detail::loop_erased_random_tree_params<T,Tag,Base>
      , Def
    >
    {
        typedef typename lookup_named_param_def<Tag1,Base,Def>::type type;

        static const type&
            get(
                detail::loop_erased_random_tree_params<T,Tag,Base> const& p
              , Def const& def
            )
        {
            return lookup_named_param_def<Tag1,Base,Def>::get(p.m_base, def);
        }
    };

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

#endif  // BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_PRM_HPP

