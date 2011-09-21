// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_BUILDER_FROM_GRAPH_HPP_INCLUDED
#define BOOST_AUTOMATA_BUILDER_FROM_GRAPH_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 4)
#error Set BOOST_PARAMETER_MAX_ARITY to 4 or more.
#endif

#include <vector>
#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/config.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/functional/value_factory.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/map/convert.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/range.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/detail/metafunction/property_map_key.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/automata/keyword/name.hpp>

//[reference__builder_from_graph
namespace boost {
 namespace automata {

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Function
    >
    void
        build_from_graph(
            Graph const& graph
          , VertexStateMap const& vertex_state_map
          , EdgeInputMap const& edge_input_map
          , Function& function
          , dpda_transition_function_tag
        )
    {
        BOOST_CONCEPT_ASSERT((DPDATransitionFunction<Function>));

        function.reset(::boost::num_vertices(graph));

        typename ::boost::graph_traits<Graph>::edge_iterator ei, eend;

        for (
            ::std::tr1::tie(ei, eend) = ::boost::edges(graph);
            ei != eend;
            ++ei
        )
        {
            typename property_traits<EdgeInputMap>::value_type const&
                i = get(edge_input_map, *ei);
            typename Function::result_map
                r_map(
                    ::boost::fusion::make_pair<next_state_key>(
                        get(vertex_state_map, target(*ei, graph))
                    )
                  , ::boost::fusion::make_pair<push_to_stack_key>(
                        ::boost::fusion::at_key<push_to_stack_key>(i)
                    )
                );

            if (
                typename Function::optional_stack_element const&
                    o_e = ::boost::fusion::at_key<pop_from_stack_key>(i)
            )
            {
                function.set_transition(
                    get(vertex_state_map, source(*ei, graph))
                  , ::boost::fusion::at_key<input_symbol_key>(i)
                  , *o_e
                  , r_map
                );
            }
            else
            {
                function.set_transition(
                    get(vertex_state_map, source(*ei, graph))
                  , ::boost::fusion::at_key<input_symbol_key>(i)
                  , r_map
                );
            }
        }
    }

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Function
    >
    void
        build_from_graph(
            Graph const& graph
          , VertexStateMap const& vertex_state_map
          , EdgeInputMap const& edge_input_map
          , Function& function
          , tabular_transition_function_tag
        )
    {
        BOOST_CONCEPT_ASSERT((TabularTransitionFunction<Function>));

        typename Function::second_argument_type
            input = typename Function::second_argument_type();
        typename ::boost::graph_traits<Graph>::edge_iterator ei, eend;

        for (
            ::std::tr1::tie(ei, eend) = ::boost::edges(graph);
            ei != eend;
            ++ei
        )
        {
            if (input < get(edge_input_map, *ei))
            {
                input = get(edge_input_map, *ei);
            }
        }

        if (input)
        {
            function.reset(::boost::num_vertices(graph), ++input);

            for (
                ::std::tr1::tie(ei, eend) = ::boost::edges(graph);
                ei != eend;
                ++ei
            )
            {
                function.set_transition(
                    get(vertex_state_map, source(*ei, graph))
                  , get(edge_input_map, *ei)
                  , get(vertex_state_map, target(*ei, graph))
                );
            }
        }
    }

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Function
    >
    void
        build_from_graph(
            Graph const& graph
          , VertexStateMap const& vertex_state_map
          , EdgeInputMap const& edge_input_map
          , Function& function
          , mapped_input_tabular_transition_function_tag
        )
    {
        BOOST_CONCEPT_ASSERT((MappedInputTabularTransitionFunction<Function>));

        std::vector<typename Function::second_argument_type> inputs;
        typename ::boost::graph_traits<Graph>::edge_iterator ei, eend;

        for (
            ::std::tr1::tie(ei, eend) = ::boost::edges(graph);
            ei != eend;
            ++ei
        )
        {
            inputs.push_back(get(edge_input_map, *ei));
        }

        function.reset(::boost::num_vertices(graph), inputs);

        for (
            ::std::tr1::tie(ei, eend) = ::boost::edges(graph);
            ei != eend;
            ++ei
        )
        {
            function.set_transition(
                get(vertex_state_map, source(*ei, graph))
              , get(edge_input_map, *ei)
              , get(vertex_state_map, target(*ei, graph))
            );
        }
    }

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Function
    >
    void
        build_from_graph(
            Graph const& graph
          , VertexStateMap const& vertex_state_map
          , EdgeInputMap const& edge_input_map
          , Function& function
          , mapped_input_transition_function_tag
        )
    {
        BOOST_CONCEPT_ASSERT((MappedInputTransitionFunction<Function>));

        function.reset(num_vertices(graph));

        typename ::boost::graph_traits<Graph>::edge_iterator ei, eend;

        for (
            ::std::tr1::tie(ei, eend) = ::boost::edges(graph);
            ei != eend;
            ++ei
        )
        {
            function.set_transition(
                get(vertex_state_map, source(*ei, graph))
              , get(edge_input_map, *ei)
              , get(vertex_state_map, target(*ei, graph))
            );
        }
    }

    template <
        typename Graph
      , typename VertexStateMap
      , typename Function
    >
    void
        build_from_graph(
            Graph const& graph
          , VertexStateMap const& vertex_state_map
          , Function& function
          , next_state_transition_function_tag
        )
    {
        BOOST_CONCEPT_ASSERT((NextStateTransitionFunction<Function>));

        function.reset(::boost::num_vertices(graph));

        typename ::boost::graph_traits<Graph>::vertex_iterator    vi, vend;
        typename ::boost::graph_traits<Graph>::adjacency_iterator ai, aend;
        typename Function::state                                  state;

        for (
            ::std::tr1::tie(vi, vend) = ::boost::vertices(graph);
            vi != vend;
            ++vi
        )
        {
            state = get(vertex_state_map, *vi);

            for (
                ::std::tr1::tie(ai, aend) = ::boost::adjacent_vertices(
                    *vi
                  , graph
                );
                ai != aend;
                ++ai
            )
            {
                function.add_transition(state, get(vertex_state_map, *ai));
            }
        }
    }
 }  // namespace automata

    enum edge_input_t
    {
        edge_input
    };

    template <>
    struct property_kind<edge_input_t>
    {
        typedef edge_property_tag type;
    };

 namespace automata {
  namespace _detail {

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Policies
    >
    class builder_from_graph_w_eim
    {
        BOOST_CONCEPT_ASSERT((
            ::boost::concepts::VertexAndEdgeListGraph<Graph>
        ));
        typedef typename ::boost::graph_traits<Graph>::vertex_descriptor
                Vertex;
        BOOST_CONCEPT_ASSERT((
            ReadablePropertyMapConcept<VertexStateMap,Vertex>
        ));
        BOOST_CONCEPT_ASSERT((
            ReadablePropertyMapConcept<
                EdgeInputMap
              , typename ::boost::graph_traits<Graph>::edge_descriptor
            >
        ));

        Graph const&          _g;
        VertexStateMap const& _vertex_state_map;
        EdgeInputMap const&   _edge_input_map;

        class observer_builder_maker
        {
            builder_from_graph_w_eim const& _builder;

         public:
            observer_builder_maker(builder_from_graph_w_eim const& builder)
              : _builder(builder)
            {
            }

            template <typename T>
            struct result;

            template <typename BuilderMaker, typename T>
            struct result<BuilderMaker(T)>
            {
             private:
                typedef typename ::boost::detail::data_type<T>::type
                        T_data;

             public:
                typedef ::boost::fusion::pair<
                            typename T_data::key_type
                          , typename ::boost::mpl::apply_wrap3<
                                T_data
                              , Graph
                              , VertexStateMap
                              , EdgeInputMap
                            >::type
                        >
                        type;
            };

            template <typename T>
            inline ::boost::fusion::pair<
                typename T::key_type
              , typename ::boost::mpl::apply_wrap3<
                    T
                  , Graph
                  , VertexStateMap
                  , EdgeInputMap
                >::type
            >
                operator()(T const& t) const
            {
                return ::boost::fusion::pair<
                    typename T::key_type
                  , typename ::boost::mpl::apply_wrap3<
                        T
                      , Graph
                      , VertexStateMap
                      , EdgeInputMap
                    >::type
                >(
                    typename ::boost::mpl::apply_wrap3<
                        T
                      , Graph
                      , VertexStateMap
                      , EdgeInputMap
                    >::type(
                        t
                      , _builder._g
                      , _builder._vertex_state_map
                      , _builder._edge_input_map
                    )
                );
            }
        };

     public:
        typedef typename ::boost::fusion::result_of::as_map<
                    typename ::boost::fusion::result_of::transform<
                        Policies
                      , observer_builder_maker
                    >::type
                >::type
                observer_builder_map;

     private:
        observer_builder_map _observer_builder_map;

     public:
        template <typename ArgumentPack>
        builder_from_graph_w_eim(ArgumentPack const& args);

        template <typename Function>
        void operator()(Function& function) const;

        observer_builder_map const& get_observer_builder_map() const;
    };

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Policies
    >
    template <typename ArgumentPack>
    builder_from_graph_w_eim<
        Graph
      , VertexStateMap
      , EdgeInputMap
      , Policies
    >::builder_from_graph_w_eim(ArgumentPack const& args)
      : _g(args[::boost::automata::keyword::_graph])
      , _vertex_state_map(args[::boost::automata::keyword::_vertex_state_map])
      , _edge_input_map(
            args[
                ::boost::automata::keyword::_edge_input_map
             || value_factory< ::boost::mpl::void_>()
            ]
        )
      , _observer_builder_map(
            ::boost::fusion::as_map(
                ::boost::fusion::transform(
                    args[
                        ::boost::automata::keyword::_policies
                     || value_factory<Policies>()
                    ]
                  , observer_builder_maker(*this)
                )
            )
        )
    {
    }

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Policies
    >
    template <typename Function>
    inline void
        builder_from_graph_w_eim<
            Graph
          , VertexStateMap
          , EdgeInputMap
          , Policies
        >::operator()(Function& function) const
    {
        build_from_graph(
            _g
          , _vertex_state_map
          , _edge_input_map
          , function
          , typename Function::tag()
        );
    }

    template <
        typename Graph
      , typename VertexStateMap
      , typename EdgeInputMap
      , typename Policies
    >
    inline typename builder_from_graph_w_eim<
        Graph
      , VertexStateMap
      , EdgeInputMap
      , Policies
    >::observer_builder_map const&
        builder_from_graph_w_eim<
            Graph
          , VertexStateMap
          , EdgeInputMap
          , Policies
        >::get_observer_builder_map() const
    {
        return _observer_builder_map;
    }

    template <typename Graph, typename VertexStateMap, typename Policies>
    class builder_from_graph_wo_eim
    {
        BOOST_CONCEPT_ASSERT((
            ::boost::concepts::VertexListGraph<Graph>
        ));
        BOOST_CONCEPT_ASSERT((
            ::boost::concepts::AdjacencyGraph<Graph>
        ));
        typedef typename ::boost::graph_traits<Graph>::vertex_descriptor
                Vertex;
        BOOST_CONCEPT_ASSERT((
            ReadablePropertyMapConcept<VertexStateMap,Vertex>
        ));

        Graph const&          _g;
        VertexStateMap const& _vertex_state_map;

        class observer_builder_maker
        {
            builder_from_graph_wo_eim const& _builder;

         public:
            observer_builder_maker(builder_from_graph_wo_eim const& builder)
              : _builder(builder)
            {
            }

            template <typename T>
            struct result;

            template <typename BuilderMaker, typename T>
            struct result<BuilderMaker(T)>
            {
             private:
                typedef typename ::boost::detail::data_type<T>::type
                        T_data;

             public:
                typedef ::boost::fusion::pair<
                            typename T_data::key_type
                          , typename ::boost::mpl::apply_wrap2<
                                T_data
                              , Graph
                              , VertexStateMap
                            >::type
                        >
                        type;
            };

            template <typename T>
            inline ::boost::fusion::pair<
                typename T::key_type
              , typename ::boost::mpl::apply_wrap2<
                    T
                  , Graph
                  , VertexStateMap
                >::type
            >
                operator()(T const& t) const
            {
                return ::boost::fusion::pair<
                    typename T::key_type
                  , typename ::boost::mpl::apply_wrap2<
                        T
                      , Graph
                      , VertexStateMap
                    >::type
                >(
                    typename ::boost::mpl::apply_wrap2<
                        T
                      , Graph
                      , VertexStateMap
                    >::type(
                        t
                      , _builder._g
                      , _builder._vertex_state_map
                    )
                );
            }
        };

     public:
        typedef typename ::boost::fusion::result_of::as_map<
                    typename ::boost::fusion::result_of::transform<
                        Policies
                      , observer_builder_maker
                    >::type
                >::type
                observer_builder_map;

     private:
        observer_builder_map _observer_builder_map;

     public:
        template <typename ArgumentPack>
        builder_from_graph_wo_eim(ArgumentPack const& args);

        template <typename Function>
        void operator()(Function& function) const;

        observer_builder_map const& get_observer_builder_map() const;
    };

    template <typename Graph, typename VertexStateMap, typename Policies>
    template <typename ArgumentPack>
    builder_from_graph_wo_eim<
        Graph
      , VertexStateMap
      , Policies
    >::builder_from_graph_wo_eim(ArgumentPack const& args)
      : _g(args[::boost::automata::keyword::_graph])
      , _vertex_state_map(args[::boost::automata::keyword::_vertex_state_map])
      , _observer_builder_map(
            ::boost::fusion::as_map(
                ::boost::fusion::transform(
                    args[
                        ::boost::automata::keyword::_policies
                     || value_factory<Policies>()
                    ]
                  , observer_builder_maker(*this)
                )
            )
        )
    {
    }

    template <typename Graph, typename VertexStateMap, typename Policies>
    template <typename Function>
    inline void
        builder_from_graph_wo_eim<Graph,VertexStateMap,Policies>::operator()(
            Function& function
        ) const
    {
        build_from_graph(
            _g
          , _vertex_state_map
          , function
          , typename Function::tag()
        );
    }

    template <typename Graph, typename VertexStateMap, typename Policies>
    inline typename builder_from_graph_wo_eim<
        Graph
      , VertexStateMap
      , Policies
    >::observer_builder_map const&
        builder_from_graph_wo_eim<
            Graph
          , VertexStateMap
          , Policies
        >::get_observer_builder_map() const
    {
        return _observer_builder_map;
    }
  }  // namespace _detail

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#define BOOST_AUTOMATA_BUILDER_ARG_TYPE \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_Graph> \
      , ::boost::parameter::required<keyword::tag::_VertexStateMap> \
      , ::boost::parameter::optional<keyword::tag::_EdgeInputMap> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1,T2,T3,boost::parameter::void_>::type \
//
#else
#define BOOST_AUTOMATA_BUILDER_ARG_TYPE \
    typename ::boost::parameter::parameters< \
        ::boost::parameter::required<keyword::tag::_Graph> \
      , ::boost::parameter::required<keyword::tag::_VertexStateMap> \
      , ::boost::parameter::optional<keyword::tag::_EdgeInputMap> \
      , ::boost::parameter::optional<keyword::tag::_Policies> \
    >::BOOST_NESTED_TEMPLATE bind<T0,T1,T2,T3>::type \
//
#endif
#define BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(_args, _keyword) \
    typename ::boost::detail::data_type< \
        typename ::boost::parameter::binding< \
            _args \
          , keyword::tag::_keyword \
        >::type \
    >::type \
//
#define BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(_args, _keyword, _default) \
    typename ::boost::detail::data_type< \
        typename ::boost::parameter::binding< \
            _args \
          , keyword::tag::_keyword \
          , _default \
        >::type \
    >::type \
//

    template <
        typename T0
      , typename T1
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    class builder_from_graph
      : public ::boost::mpl::if_<
            ::std::tr1::is_same<
                BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _EdgeInputMap
                  , ::boost::mpl::void_
                )
              , ::boost::mpl::void_
            >
          , _detail::builder_from_graph_wo_eim<
                BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _Graph
                )
              , BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _VertexStateMap
                )
              , BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _Policies
                  , ::boost::fusion::nil
                )
            >
          , _detail::builder_from_graph_w_eim<
                BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _Graph
                )
              , BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _VertexStateMap
                )
              , BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _EdgeInputMap
                  , ::boost::mpl::void_
                )
              , BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    BOOST_AUTOMATA_BUILDER_ARG_TYPE
                  , _Policies
                  , ::boost::fusion::nil
                )
            >
        >::type
    {
        typedef BOOST_AUTOMATA_BUILDER_ARG_TYPE
                Args;
        typedef BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(Args, _Graph)
                Graph;
        typedef BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE(Args, _VertexStateMap)
                VertexStateMap;
        typedef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    Args
                  , _EdgeInputMap
                  , ::boost::mpl::void_
                )
                EdgeInputMap;
        typedef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE(
                    Args
                  , _Policies
                  , ::boost::fusion::nil
                )
                Policies;
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_same<EdgeInputMap,::boost::mpl::void_>
                  , _detail::builder_from_graph_wo_eim<
                        Graph
                      , VertexStateMap
                      , Policies
                    >
                  , _detail::builder_from_graph_w_eim<
                        Graph
                      , VertexStateMap
                      , EdgeInputMap
                      , Policies
                    >
                >::type
                Base;

     public:
        typedef typename Base::observer_builder_map
                observer_builder_map;

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
     private:
        typedef ::std::tr1::is_same<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , Graph
                >
                GraphPredicate;
        typedef ::std::tr1::is_same<
                    ::boost::detail::property_map_key< ::boost::mpl::_>
                  , typename graph_traits<Graph>::vertex_descriptor
                >
                VertexStateMapPredicate;
        typedef ::std::tr1::is_same<
                    ::boost::detail::property_map_key< ::boost::mpl::_>
                  , typename graph_traits<Graph>::edge_descriptor
                >
                EdgeInputMapPredicate;
        typedef ::std::tr1::is_same<
                    ::boost::detail::data_type< ::boost::mpl::_>
                  , Policies
                >
                PoliciesPredicate;

     public:
        BOOST_PARAMETER_CONSTRUCTOR(
            builder_from_graph, (Base), keyword::tag,
            (deduced
                (required
                    (graph
                      , *(GraphPredicate)
                    )
                    (vertex_state_map
                      , *(VertexStateMapPredicate)
                    )
                )
                (optional
                    (edge_input_map
                      , *(EdgeInputMapPredicate)
//                      , ::boost::mpl::void_()
                    )
                    (policies
                      , *(PoliciesPredicate)
//                      , Policies()
                    )
                )
            )
        )
#else
        BOOST_PARAMETER_CONSTRUCTOR(
            builder_from_graph, (Base), keyword::tag,
            (deduced
                (required
                    (graph
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Graph
                            >
                        )
                    )
                    (vertex_state_map
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::property_map_key<
                                    ::boost::mpl::_
                                >
                              , typename ::boost::graph_traits<
                                    Graph
                                >::vertex_descriptor
                            >
                        )
                    )
                )
                (optional
                    (edge_input_map
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::property_map_key<
                                    ::boost::mpl::_
                                >
                              , typename ::boost::graph_traits<
                                    Graph
                                >::edge_descriptor
                            >
                        )
//                      , ::boost::mpl::void_()
                    )
                    (policies
                      , *(
                            ::std::tr1::is_same<
                                ::boost::detail::data_type< ::boost::mpl::_>
                              , Policies
                            >
                        )
//                      , Policies()
                    )
                )
            )
        )
#endif  // BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
    };

#undef BOOST_AUTOMATA_BUILDER_OPTIONAL_TYPE
#undef BOOST_AUTOMATA_BUILDER_REQUIRED_TYPE
#undef BOOST_AUTOMATA_BUILDER_ARG_TYPE

}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_BUILDER_FROM_GRAPH_HPP_INCLUDED

