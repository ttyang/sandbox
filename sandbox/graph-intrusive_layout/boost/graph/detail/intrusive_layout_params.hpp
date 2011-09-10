// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_INTRUSIVE_LAYOUT_PARAMS_HPP
#define BOOST_GRAPH_DETAIL_INTRUSIVE_LAYOUT_PARAMS_HPP

#include <boost/graph/named_function_params.hpp>
#include <boost/graph/keywords/dimension_count.hpp>
#include <boost/graph/keywords/dimensions.hpp>
#include <boost/graph/keywords/has_square_origin.hpp>
#include <boost/graph/keywords/inscribed_radius.hpp>
#include <boost/graph/keywords/is_zeta.hpp>
#include <boost/graph/keywords/origin.hpp>
#include <boost/graph/keywords/point_factory.hpp>
#include <boost/graph/keywords/position_index_map.hpp>
#include <boost/graph/keywords/position_map.hpp>
#include <boost/graph/keywords/scale.hpp>
#include <boost/graph/keywords/vertex_centroid_distance.hpp>
#include <boost/graph/keywords/wraparound_policy.hpp>

#define BOOST_BGL_INTRUSIVE_LAYOUT_DECLARE_PARAMS \
BOOST_BGL_ONE_PARAM_CREF(dimension_count, dimension_count) \
BOOST_BGL_ONE_PARAM_CREF(dimensions, dimensions) \
BOOST_BGL_ONE_PARAM_CREF(has_square_origin, has_square_origin) \
BOOST_BGL_ONE_PARAM_CREF(inscribed_radius, inscribed_radius) \
BOOST_BGL_ONE_PARAM_CREF(is_zeta, is_zeta) \
BOOST_BGL_ONE_PARAM_CREF(origin, origin) \
BOOST_BGL_ONE_PARAM_CREF(point_factory, point_factory) \
BOOST_BGL_ONE_PARAM_CREF(position_index_map, position_index_map) \
BOOST_BGL_ONE_PARAM_CREF(position_map, position_map) \
BOOST_BGL_ONE_PARAM_CREF(scale, scale) \
BOOST_BGL_ONE_PARAM_CREF(vertex_centroid_distance, vertex_centroid_distance) \
BOOST_BGL_ONE_PARAM_CREF(wraparound_policy, wraparound_policy) \
//

namespace boost {
  namespace detail {

    template <typename T, typename Tag, typename Base = no_property>
    struct intrusive_layout_params : Base
    {
        typedef intrusive_layout_params self;
        typedef Base                    next_type;
        typedef Tag                     tag_type;
        typedef T                       value_type;

        T m_value;

        intrusive_layout_params(T v = T()) : Base(), m_value(v)
        {
        }

        intrusive_layout_params(T v, Base const& b)
          : Base(b), m_value(v)
        {
        }

#define BOOST_BGL_ONE_PARAM_REF(name, key) \
        template <typename PType> \
        inline intrusive_layout_params< \
            ::boost::reference_wrapper<PType> \
          , BOOST_PP_CAT(key, _t) \
          , self \
        > \
            name(PType& p) const \
        { \
            typedef intrusive_layout_params< \
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
        inline intrusive_layout_params< \
            PType \
          , BOOST_PP_CAT(key, _t) \
          , self \
        > \
            name(PType const& p) const \
        { \
            typedef intrusive_layout_params< \
                        PType \
                      , BOOST_PP_CAT(key, _t) \
                      , self \
                    > \
                    Params; \
            return Params(p, *this); \
        } \
//

        BOOST_BGL_INTRUSIVE_LAYOUT_DECLARE_PARAMS

#undef BOOST_BGL_ONE_PARAM_CREF
#undef BOOST_BGL_ONE_PARAM_REF
    };

    typedef intrusive_layout_params<char,unused_tag_type>
            no_intrusive_layout_params;

    template <>
    struct convert_bgl_params_to_boost_parameter<no_intrusive_layout_params>
    {
        typedef ::boost::parameter::aux::empty_arg_list type;

        static type conv(no_property const&)
        {
            return type();
        }
    };
  }  // namespace detail

    inline detail::no_intrusive_layout_params
        make_intrusive_layout_params()
    {
        return detail::no_intrusive_layout_params();
    }

#define BOOST_BGL_ONE_PARAM_REF(name, key) \
    template <typename PType> \
    inline detail::intrusive_layout_params< \
        ::boost::reference_wrapper<PType> \
      , BOOST_PP_CAT(key, _t) \
    > \
        name(PType& p) \
    { \
        typedef detail::intrusive_layout_params< \
                    ::boost::reference_wrapper<PType> \
                  , BOOST_PP_CAT(key, _t) \
                > \
                Params; \
        return Params(::boost::ref(p)); \
    } \
//

#define BOOST_BGL_ONE_PARAM_CREF(name, key) \
    template <typename PType> \
    inline detail::intrusive_layout_params< \
        PType \
      , BOOST_PP_CAT(key, _t) \
    > \
        name(PType const& p) \
    { \
        typedef detail::intrusive_layout_params< \
                    PType \
                  , BOOST_PP_CAT(key, _t) \
                > \
                Params; \
        return Params(p); \
    } \
//

    BOOST_BGL_INTRUSIVE_LAYOUT_DECLARE_PARAMS

#undef BOOST_BGL_ONE_PARAM_CREF
#undef BOOST_BGL_ONE_PARAM_REF
}  // namespace boost

#undef BOOST_BGL_INTRUSIVE_LAYOUT_DECLARE_PARAMS

#endif  // BOOST_GRAPH_DETAIL_INTRUSIVE_LAYOUT_PARAMS_HPP

