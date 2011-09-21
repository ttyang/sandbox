// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TRANSITION_FUNCTION_DECISION_TREE_HPP_INCLUDED
#define BOOST_AUTOMATA_TRANSITION_FUNCTION_DECISION_TREE_HPP_INCLUDED

#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

#if BOOST_PP_LESS(BOOST_PARAMETER_MAX_ARITY, 5)
#error Set BOOST_PARAMETER_MAX_ARITY to 5 or more.
#endif

#include <cmath>
#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/random.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/none.hpp>
#include <boost/optional/optional.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/range/distance.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/tree_node/raw_associative_node.hpp>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keys/common.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/assert.hpp>

//[reference__decision_tree_transition_function
namespace boost { namespace automata {
  //<-
  namespace _detail {

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    class decision_tree_transition_function_helper
    {
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , State
                >::type
                StateArray;
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , State
                >::type
                StateSet;
        typedef typename ::boost::mpl::apply_wrap1<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , AttributeKey
                >::type
                AttributeKeySet;
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , AttributeKey
                  , AttributeValue
                >::type
                InputMap;
        typedef ::boost::fusion::pair<input_symbol_key,InputMap>
                InputEntry;
        typedef ::boost::fusion::pair<next_state_key,State>
                NextStateEntry;
        typedef ::boost::fusion::map<InputEntry,NextStateEntry>
                Example;
        typedef typename ::boost::container_gen<
                    RandomAccessContainerSelector
                  , Example
                >::type
                ExampleArray;
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , AttributeValue
                  , ExampleArray
                >::type
                LightweightTree;

        class ExampleMaker
        {
            decision_tree_transition_function_helper& _helper;
            StateSet&                                 _states;
            Example                                   _example;

         public:
            ExampleMaker(
                decision_tree_transition_function_helper& helper
              , StateSet& states
            );

            inline Example const& get() const
            {
                return _example;
            }

            void
                input(
                    AttributeKey const& key
                  , AttributeValue const& value
                  , ::std::tr1::true_type
                );

            void
                input(
                    AttributeKey const& key
                  , AttributeValue const& value
                  , ::std::tr1::false_type
                );

            void set_next_state(State const& next_state);
        };

     public:
        class builder
        {
            class Helper
            {
                builder&     _builder;
                ExampleMaker _maker;

             public:
                explicit Helper(builder& builder);

                inline Helper&
                    operator()(
                        AttributeKey const& key
                      , AttributeValue const& value
                    )
                {
                    _maker.input(
                        key
                      , value
                      , ::std::tr1::is_convertible<AttributeValue,State>()
                    );
                    return *this;
                }

                inline builder& operator[](State const& next_state)
                {
                    _maker.set_next_state(next_state);
                    _builder._examples.push_back(_maker.get());
                    return _builder;
                }
            };

            decision_tree_transition_function_helper& _helper;
            StateSet                                  _states;
            ExampleArray                              _examples;
            bool                                      _check_for_homogeneity;

         public:
            builder(
                decision_tree_transition_function_helper& helper
              , bool check_for_homogeneity
            );

            builder(
                decision_tree_transition_function_helper& helper
              , AttributeKey const& state_key
              , bool check_for_homogeneity
            );

            ~builder();

            inline Helper
                operator()(
                    AttributeKey const& key
                  , AttributeValue const& value
                )
            {
                Helper helper(*this);

                helper(key, value);
                return helper;
            }
        };

        class incremental_builder
        {
            decision_tree_transition_function_helper& _helper;
            StateSet                                  _states;
            ExampleMaker                              _maker;

         public:
            explicit incremental_builder(
                decision_tree_transition_function_helper& helper
            );

            inline incremental_builder&
                operator()(
                    AttributeKey const& key
                  , AttributeValue const& value
                )
            {
                _maker.input(
                    key
                  , value
                  , ::std::tr1::is_same<AttributeValue,State>()
                );
                return *this;
            }

            void operator[](State const& next_state);
        };

     private:
        class NodeData
        {
            bool         _has_homogeneous_examples;
            ExampleArray _input_examples;
            AttributeKey _split_attribute_key;

         public:
            NodeData();

            inline bool has_homogeneous_examples() const
            {
                return _has_homogeneous_examples;
            }

            inline ExampleArray const& get_input_examples() const
            {
                return _input_examples;
            }

            inline AttributeKey const& get_split_attribute_key() const
            {
                return _split_attribute_key;
            }

            void set_input_examples(ExampleArray const& examples);

            void add_input_example(Example const& example);

            void set_split_attribute_key(AttributeKey const& key);

            void clear();
        };

        typedef ::boost::tree_node::raw_associative_node<
                    AttributeValue
                  , NodeData
                  , AssociativeContainerSelector
                >
                Node;

        Node                   _root;
        StateArray             _states;
        AttributeKeySet        _attribute_keys;
        optional<AttributeKey> _state_key;

     public:
        bool is_ready_to_process_input() const;

        template <typename Input>
        bool
            process_input(
                State& current_state
              , Input const& i
              , ::std::tr1::true_type
            ) const;

        template <typename Input>
        bool
            process_input(
                State& current_state
              , Input const& i
              , ::std::tr1::false_type
            ) const;

        template <typename Input, typename RNGEngine>
        void
            process_input(
                State& current_state
              , Input const& i
              , RNGEngine& engine
              , ::std::tr1::true_type
            ) const;

        template <typename Input, typename RNGEngine>
        void
            process_input(
                State& current_state
              , Input const& i
              , RNGEngine& engine
              , ::std::tr1::false_type
            ) const;

        template <typename Examples>
        void learn_examples(Examples const& examples);

        template <typename NewExample>
        void learn_example(NewExample const& example);

        void reset();

     private:
        static double _compute_entropy(ExampleArray const& examples);

        static double _compute_average_entropy(LightweightTree const& l_tree);

        static void
            _id3(
                AttributeKeySet const& available_keys
              , NodeData& data
              , LightweightTree& output_tree
              , bool check_for_homogeneity
            );

        static void
            _create_descendants(
                typename Node::pointer node
              , AttributeKeySet const& attribute_keys
              , LightweightTree& l_tree
              , bool check_for_homogeneity
            );

        void _id4(Example const& example, bool check_for_homogeneity);
    };

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::ExampleMaker::ExampleMaker(
        decision_tree_transition_function_helper& helper
      , StateSet& states
    ) : _helper(helper), _states(states), _example()
    {
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::ExampleMaker::input(
            AttributeKey const& key
          , AttributeValue const& value
          , ::std::tr1::true_type
        )
    {
        if (_helper._attribute_keys.find(key) == _helper._attribute_keys.end())
        {
            _helper._attribute_keys.insert(key);
        }

        if (
            (_helper._state_key)
         && (key == *_helper._state_key)
         && (_states.find(value) == _states.end())
        )
        {
            _states.insert(value);
        }

        ::boost::fusion::at_key<input_symbol_key>(_example).insert(
            typename InputMap::value_type(key, value)
        );
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::ExampleMaker::input(
            AttributeKey const& key
          , AttributeValue const& value
          , ::std::tr1::false_type
        )
    {
        if (_helper._attribute_keys.find(key) == _helper._attribute_keys.end())
        {
            _helper._attribute_keys.insert(key);
        }

        ::boost::fusion::at_key<input_symbol_key>(_example).insert(
            typename InputMap::value_type(key, value)
        );
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::ExampleMaker::set_next_state(State const& next_state)
    {
        if (_states.find(next_state) == _states.end())
        {
            _states.insert(next_state);
        }

        ::boost::fusion::at_key<next_state_key>(_example) = next_state;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::builder::Helper::Helper(builder& builder)
      : _builder(builder), _maker(builder._helper, builder._states)
    {
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::builder::builder(
        decision_tree_transition_function_helper& helper
      , bool check_for_homogeneity
    ) : _helper(helper)
      , _states()
      , _examples()
      , _check_for_homogeneity(check_for_homogeneity)
    {
        _helper._state_key = boost::none;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::builder::builder(
        decision_tree_transition_function_helper& helper
      , AttributeKey const& state_key
      , bool check_for_homogeneity
    ) : _helper(helper)
      , _states()
      , _examples()
      , _check_for_homogeneity(check_for_homogeneity)
    {
        _helper._state_key = state_key;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::builder::~builder()
    {
        LightweightTree l_tree;

        _helper._states.resize(_states.size());
        ::boost::range::copy(_states, _helper._states.begin());
        _helper._root.remove_all_children();
        _helper._root.get_data().set_input_examples(_examples);
        decision_tree_transition_function_helper::_create_descendants(
            &_helper._root
          , _helper._attribute_keys
          , l_tree
          , _check_for_homogeneity
        );
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::incremental_builder::incremental_builder(
        decision_tree_transition_function_helper& helper
    ) : _helper(helper)
      , _states(_helper._states.begin(), _helper._states.end())
      , _maker(helper, _states)
    {
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::incremental_builder::operator[](State const& next_state)
    {
        _maker.set_next_state(next_state);
        _helper._states.resize(_states.size());
        ::boost::range::copy(_states, _helper._states.begin());
        _helper._id4(_maker.get(), true);
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    decision_tree_transition_function_helper<
        State
      , AttributeKey
      , AttributeValue
      , RandomAccessContainerSelector
      , AssociativeContainerSelector
    >::NodeData::NodeData()
      : _has_homogeneous_examples(false)
      , _input_examples()
      , _split_attribute_key()
    {
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::NodeData::set_input_examples(ExampleArray const& examples)
    {
        _input_examples = examples;

        if (!examples.empty())
        {
            typename ExampleArray::const_iterator itr = examples.begin();
            State const& state = ::boost::fusion::at_key<next_state_key>(*itr);

            _has_homogeneous_examples = true;

            while (++itr != examples.end())
            {
                if (::boost::fusion::at_key<next_state_key>(*itr) != state)
                {
                    _has_homogeneous_examples = false;
                    break;
                }
            }
        }
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::NodeData::add_input_example(Example const& example)
    {
        if (_input_examples.empty())
        {
            _has_homogeneous_examples = true;
        }
        else if (_has_homogeneous_examples)
        {
            _has_homogeneous_examples = (
                ::boost::fusion::at_key<next_state_key>(example)
             == ::boost::fusion::at_key<next_state_key>(_input_examples[0])
            );
        }

        _input_examples.push_back(example);
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::NodeData::set_split_attribute_key(AttributeKey const& key)
    {
        _split_attribute_key = key;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::NodeData::clear()
    {
        _has_homogeneous_examples = false;
        _input_examples.clear();
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    inline bool
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::is_ready_to_process_input() const
    {
        return !_root.get_data().get_input_examples().empty();
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    template <typename Input>
    bool
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::process_input(
            State& current_state
          , Input const& i
          , ::std::tr1::true_type
        ) const
    {
        typename Node::const_pointer node = &_root;
        typename Node::const_child_iterator c_itr;
        typename Node::const_child_iterator c_end;
        typename Input::const_iterator in_itr;
        typename Input::const_iterator in_end = i.end();

        for (;;)
        {
            c_itr = node->get_child_begin();
            c_end = node->get_child_end();

            if (c_itr == c_end)
            {
                break;
            }

            NodeData const& data = node->get_data();
            AttributeKey const& key = data.get_split_attribute_key();

            if ((_state_key) && (key == *_state_key))
            {
                c_itr = node->find_child(current_state);

                if (c_itr == c_end)
                {
                    return false;
                }

                node = c_itr->second;
                continue;
            }

            in_itr = i.find(key);

            if (in_itr == in_end)
            {
                return false;
            }

            c_itr = node->find_child(in_itr->second);

            if (c_itr == c_end)
            {
                return false;
            }

            node = c_itr->second;
        }

        ExampleArray const& examples = node->get_data().get_input_examples();

        BOOST_ASSERT(!examples.empty() && "Descendant creation bug.");
        current_state = ::boost::fusion::at_key<next_state_key>(examples[0]);
        return true;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    template <typename Input>
    bool
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::process_input(
            State& current_state
          , Input const& i
          , ::std::tr1::false_type
        ) const
    {
        typename Node::const_pointer node = &_root;
        typename Node::const_child_iterator c_itr;
        typename Node::const_child_iterator c_end;
        typename Input::const_iterator in_itr;
        typename Input::const_iterator in_end = i.end();

        for (;;)
        {
            c_itr = node->get_child_begin();
            c_end = node->get_child_end();

            if (c_itr == c_end)
            {
                break;
            }

            NodeData const& data = node->get_data();

            in_itr = i.find(data.get_split_attribute_key());

            if (in_itr == in_end)
            {
                return false;
            }

            c_itr = node->find_child(in_itr->second);

            if (c_itr == c_end)
            {
                return false;
            }

            node = c_itr->second;
        }

        ExampleArray const& examples = node->get_data().get_input_examples();

        BOOST_ASSERT(!examples.empty() && "Descendant creation bug.");
        current_state = ::boost::fusion::at_key<next_state_key>(examples[0]);
        return true;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    template <typename Input, typename RNGEngine>
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::process_input(
            State& current_state
          , Input const& i
          , RNGEngine& engine
          , ::std::tr1::true_type
        ) const
    {
        typename Node::const_pointer node = &_root;
        typename Node::const_child_iterator c_itr;
        typename Node::const_child_iterator c_end;
        typename Input::const_iterator in_itr;
        typename Input::const_iterator in_end = i.end();

        for (;;)
        {
            c_itr = node->get_child_begin();
            c_end = node->get_child_end();

            if (c_itr == c_end)
            {
                break;
            }

            NodeData const& data = node->get_data();
            AttributeKey const& key = data.get_split_attribute_key();

            if ((_state_key) && (key == *_state_key))
            {
                c_itr = node->find_child(current_state);

                if (c_itr == c_end)
                {
                    typedef ::std::tr1::uniform_int< ::std::size_t>
                            Distribution;

                    current_state = _states[
                        ::std::tr1::variate_generator<RNGEngine&,Distribution>(
                            engine
                          , Distribution(0, _states.size() - 1)
                        )()
                    ];
                    return;
                }

                node = c_itr->second;
                continue;
            }

            in_itr = i.find(key);

            if (in_itr == in_end)
            {
                typedef ::std::tr1::uniform_int< ::std::size_t> Distribution;

                ExampleArray const& examples = data.get_input_examples();

                current_state = ::boost::fusion::at_key<next_state_key>(
                    examples[
                        ::std::tr1::variate_generator<RNGEngine&,Distribution>(
                            engine
                          , Distribution(0, examples.size() - 1)
                        )()
                    ]
                );
                return;
            }

            c_itr = node->find_child(in_itr->second);

            if (c_itr == c_end)
            {
                typedef ::std::tr1::uniform_int<std::size_t> Distribution;

                current_state = _states[
                    ::std::tr1::variate_generator<RNGEngine&,Distribution>(
                        engine
                      , Distribution(0, _states.size() - 1)
                    )()
                ];
                return;
            }

            node = c_itr->second;
        }

        ExampleArray const& examples = node->get_data().get_input_examples();

        BOOST_ASSERT(!examples.empty() && "Descendant creation bug.");
        current_state = ::boost::fusion::at_key<next_state_key>(examples[0]);
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    template <typename Input, typename RNGEngine>
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::process_input(
            State& current_state
          , Input const& i
          , RNGEngine& engine
          , ::std::tr1::false_type
        ) const
    {
        typename Node::const_pointer node = &_root;
        typename Node::const_child_iterator c_itr;
        typename Node::const_child_iterator c_end;
        typename Input::const_iterator in_itr;
        typename Input::const_iterator in_end = i.end();

        for (;;)
        {
            c_itr = node->get_child_begin();
            c_end = node->get_child_end();

            if (c_itr == c_end)
            {
                break;
            }

            NodeData const& data = node->get_data();

            in_itr = i.find(data.get_split_attribute_key());

            if (in_itr == in_end)
            {
                typedef ::std::tr1::uniform_int< ::std::size_t> Distribution;

                ExampleArray const& examples = data.get_input_examples();

                current_state = ::boost::fusion::at_key<next_state_key>(
                    examples[
                        ::std::tr1::variate_generator<RNGEngine&,Distribution>(
                            engine
                          , Distribution(0, examples.size() - 1)
                        )()
                    ]
                );
                return;
            }

            c_itr = node->find_child(in_itr->second);

            if (c_itr == c_end)
            {
                typedef ::std::tr1::uniform_int< ::std::size_t> Distribution;

                current_state = _states[
                    ::std::tr1::variate_generator<RNGEngine&,Distribution>(
                        engine
                      , Distribution(0, _states.size() - 1)
                    )()
                ];
                return;
            }

            node = c_itr->second;
        }

        ExampleArray const& examples = node->get_data().get_input_examples();

        BOOST_ASSERT(!examples.empty() && "Descendant creation bug.");
        current_state = ::boost::fusion::at_key<next_state_key>(examples[0]);
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    template <typename Examples>
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::learn_examples(Examples const& examples)
    {
        // TODO:
        // 1. Copy examples into root node data.
        //    Add each attribute key found in each example input map
        //    if it is not already added.
        //    Add each state found in each example
        //    if it is not already added.
        // 2. Create the tree.
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    template <typename NewExample>
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::learn_example(NewExample const& example)
    {
        // TODO: Add the example into the tree where appropriate using ID4.
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::reset()
    {
        _root->remove_all_children();
        _root->get_data().reset();
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    double
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::_compute_entropy(ExampleArray const& examples)
    {
        using namespace std;

        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , State
                  , size_t
                >::type
                NextStateTallies;

        NextStateTallies tallies;
        typename ExampleArray::const_iterator e_itr_end = examples.end();

        for (
            typename ExampleArray::const_iterator itr = examples.begin();
            itr != e_itr_end;
            ++itr
        )
        {
            ++tallies[::boost::fusion::at_key<next_state_key>(*itr)];
        }

        double result = 0.0;
        double examples_size = static_cast<double>(examples.size());
        typename NextStateTallies::const_iterator nst_end = tallies.end();

        for (
            typename NextStateTallies::const_iterator itr = tallies.begin();
            itr != nst_end;
            ++itr
        )
        {
            double const proportion = itr->second / examples_size;

            result -= proportion * log(proportion);
        }

        return result;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    double
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::_compute_average_entropy(LightweightTree const& l_tree)
    {
        double example_count = 0.0;
        typename LightweightTree::const_iterator itr_end = l_tree.end();

        for (
            typename LightweightTree::const_iterator itr = l_tree.begin();
            itr != itr_end;
            ++itr
        )
        {
            example_count += itr->second.size();
        }

        double result = 0.0;

        for (
            typename LightweightTree::const_iterator itr = l_tree.begin();
            itr != itr_end;
            ++itr
        )
        {
            ExampleArray const& examples = itr->second;
            double const proportion = examples.size() / example_count;

            result += proportion * _compute_entropy(examples);
        }

        return result;
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::_id3(
            AttributeKeySet const& keys
          , NodeData& data
          , LightweightTree& output_tree
          , bool check_for_homogeneity
        )
    {
        LightweightTree current_tree;
        ExampleArray const& examples = data.get_input_examples();
        double init_entropy = _compute_entropy(examples);
        double best_information_gain = 0.0;
        typename AttributeKeySet::const_iterator k_itr_end = keys.end();
        typename ExampleArray::const_iterator e_itr;
        typename ExampleArray::const_iterator e_itr_end = examples.end();
        typename InputMap::const_iterator in_itr;
        bool can_use_as_split_attribute;

        for (
            typename AttributeKeySet::const_iterator k_itr = keys.begin();
            k_itr != k_itr_end;
            ++k_itr
        )
        {
            can_use_as_split_attribute = true;
            current_tree.clear();

            for (e_itr = examples.begin(); e_itr != e_itr_end; ++e_itr)
            {
                InputMap const& in_map = ::boost::fusion::at_key<
                    input_symbol_key
                >(*e_itr);

                in_itr = in_map.find(*k_itr);

                if (in_itr == in_map.end())
                {
                    can_use_as_split_attribute = false;
                    break;
                }

                current_tree[in_itr->second].push_back(*e_itr);
            }

            if (can_use_as_split_attribute)
            {
                double const information_gain = (
                    init_entropy - _compute_average_entropy(current_tree)
                );

                if (
                    !check_for_homogeneity && output_tree.empty()
                 || (best_information_gain < information_gain)
                )
                {
                    data.set_split_attribute_key(*k_itr);
                    output_tree = current_tree;
                    best_information_gain = information_gain;
                }
            }
        }
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::_create_descendants(
            typename Node::pointer node
          , AttributeKeySet const& attribute_keys
          , LightweightTree& l_tree
          , bool check_for_homogeneity
        )
    {
        typename LightweightTree::const_iterator lt_itr;
        typename LightweightTree::const_iterator lt_itr_end;

        for (
            ::boost::tree_node::breadth_first_iterator<
                typename Node::pointer
              , ::std::tr1::false_type
            > node_itr(node);
            node_itr;
            ++node_itr
        )
        {
            NodeData& data = (node = *node_itr)->get_data();

            if (check_for_homogeneity)
            {
                if (data.has_homogeneous_examples())
                {
                    continue;
                }
            }
            else if (data.get_input_examples().size() < 2)
            {
                continue;
            }

            if (l_tree.empty())
            {
                AttributeKeySet available_keys(attribute_keys);
                typename Node::const_pointer p(node);

                while (p = p->get_parent())
                {
                    available_keys.erase(
                        p->get_data().get_split_attribute_key()
                    );

                    if (available_keys.empty())
                    {
                        return;
                    }
                }

                _id3(available_keys, data, l_tree, check_for_homogeneity);
            }

            if (!l_tree.empty())
            {
                lt_itr_end = l_tree.end();

                for (lt_itr = l_tree.begin(); lt_itr != lt_itr_end; ++lt_itr)
                {
                    node->add_child(
                        lt_itr->first
                    )->get_data().set_input_examples(lt_itr->second);
                }
            }

            l_tree.clear();
        }
    }

    template <
        typename State
      , typename AttributeKey
      , typename AttributeValue
      , typename RandomAccessContainerSelector
      , typename AssociativeContainerSelector
    >
    void
        decision_tree_transition_function_helper<
            State
          , AttributeKey
          , AttributeValue
          , RandomAccessContainerSelector
          , AssociativeContainerSelector
        >::_id4(Example const& example, bool check_for_homogeneity)
    {
        AttributeKey previous_key;
        AttributeKey new_key;
        LightweightTree l_tree;
        typename InputMap::const_iterator in_itr;
        typename Node::pointer node = &_root;
        typename Node::child_iterator c_itr;
        typename Node::child_iterator c_end;

        for (;;)
        {
            NodeData& data = node->get_data();

            data.add_input_example(example);
            c_itr = node->get_child_begin();
            c_end = node->get_child_end();

            if (c_itr == c_end)
            {
                break;
            }

            InputMap const& in_map = ::boost::fusion::at_key<
                input_symbol_key
            >(example);

            l_tree.clear();
            in_itr = in_map.find(
                previous_key = data.get_split_attribute_key()
            );

            if (in_itr == in_map.end())
            {
                _create_descendants(
                    node
                  , _attribute_keys
                  , l_tree
                  , check_for_homogeneity
                );
                return;
            }

            _id3(_attribute_keys, data, l_tree, check_for_homogeneity);

            if (l_tree.empty())
            {
                node->remove_all_children();
                return;
            }

            new_key = data.get_split_attribute_key();

            if (previous_key != new_key)
            {
                _create_descendants(
                    node
                  , _attribute_keys
                  , l_tree
                  , check_for_homogeneity
                );
                return;
            }

            c_itr = node->find_child(in_itr->second);

            if (c_itr == c_end)
            {
                node->add_child(
                    in_itr->second
                )->get_data().add_input_example(example);
                return;
            }

            node = c_itr->second;
        }

        if (!node->get_data().has_homogeneous_examples())
        {
            l_tree.clear();
            _create_descendants(
                node
              , _attribute_keys
              , l_tree
              , check_for_homogeneity
            );
        }
    }
  }  // namespace _detail
  //->

    template <
        typename T0
      , typename T1
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
    >
    class decision_tree_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_State>
                  , ::boost::parameter::required<keyword::tag::_AttributeKey>
                  , ::boost::parameter::optional<keyword::tag::_AttributeValue>
                  , ::boost::parameter::optional<
                        keyword::tag::_AssociativeContainerSelector
                    >
                  , ::boost::parameter::optional<
                        keyword::tag::_RandomAccessContainerSelector
                    >
                >::BOOST_NESTED_TEMPLATE bind<
                    T0
                  , T1
                  , T2
                  , T3
                  , T4
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , ::boost::parameter::void_
#endif
                >::type
                Args;
        //->

     public:
        typedef transition_function_tag
                tag;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_State
                >::type
                //->
                state;
        typedef bool
                result_type;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AttributeKey
                >::type
                //->
                attribute_key;

        //<-
     private:
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AttributeValue
                  , state
                >::type
                AttributeValue;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AssociativeContainerSelector
                  , ::boost::mapS
                >::type
                AssociativeContainerSelector;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_RandomAccessContainerSelector
                  , ::boost::vecS
                >::type
                RandomAccessContainerSelector;
        typedef _detail::decision_tree_transition_function_helper<
                    state
                  , attribute_key
                  , AttributeValue
                  , RandomAccessContainerSelector
                  , AssociativeContainerSelector
                >
                Helper;

     public:
        //->
        typedef typename Helper::builder
                builder;
        typedef typename Helper::incremental_builder
                incremental_builder;

        //<-
     private:
        Helper _helper;

     public:
        //->
        decision_tree_transition_function();

        decision_tree_transition_function(
            decision_tree_transition_function const& copy
        );

        decision_tree_transition_function&
            operator=(decision_tree_transition_function const& copy);

        template <typename Input, typename RNGEngine>
        result_type
            operator()(
                state& current_state
              , Input const& i
              , RNGEngine& rng_engine
            ) const;

        void reset();

        builder set_examples();

        builder set_examples(attribute_key const& state_key);

        incremental_builder add_example();
    };

    //<-
    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    decision_tree_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::decision_tree_transition_function() : _helper()
    {
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    decision_tree_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::decision_tree_transition_function(
        decision_tree_transition_function const& copy
    ) : _helper(copy._helper)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    decision_tree_transition_function<T0,T1,T2,T3,T4>&
        decision_tree_transition_function<T0,T1,T2,T3,T4>::operator=(
            decision_tree_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _helper = copy._helper;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    template <typename Input, typename RNGEngine>
    inline typename decision_tree_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::result_type
        decision_tree_transition_function<T0,T1,T2,T3,T4>::operator()(
            state& current_state
          , Input const& input
          , RNGEngine& rng_engine
        ) const
    {
        if (_helper.is_ready_to_process_input())
        {
            _helper.process_input(
                current_state
              , input
              , rng_engine
              , ::std::tr1::is_same<attribute_key,state>()
            );
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void decision_tree_transition_function<T0,T1,T2,T3,T4>::reset()
    {
        _helper.reset();
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline typename decision_tree_transition_function<T0,T1,T2,T3,T4>::builder
        decision_tree_transition_function<T0,T1,T2,T3,T4>::set_examples()
    {
        return builder(_helper, true);
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline typename decision_tree_transition_function<T0,T1,T2,T3,T4>::builder
        decision_tree_transition_function<T0,T1,T2,T3,T4>::set_examples(
            attribute_key const& state_key
        )
    {
        return builder(_helper, state_key, true);
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline typename decision_tree_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::incremental_builder
        decision_tree_transition_function<T0,T1,T2,T3,T4>::add_example()
    {
        return incremental_builder(_helper);
    }
    //->
}}  // namespace boost::automata
//]

//[reference__decision_tree_explicit_transition_function
namespace boost { namespace automata {

    template <
        typename T0
      , typename T1
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
    >
    class decision_tree_explicit_transition_function
    {
        //<-
        typedef typename ::boost::parameter::parameters<
                    ::boost::parameter::required<keyword::tag::_State>
                  , ::boost::parameter::required<keyword::tag::_AttributeKey>
                  , ::boost::parameter::optional<keyword::tag::_AttributeValue>
                  , ::boost::parameter::optional<
                        keyword::tag::_AssociativeContainerSelector
                    >
                  , ::boost::parameter::optional<
                        keyword::tag::_RandomAccessContainerSelector
                    >
                >::BOOST_NESTED_TEMPLATE bind<
                    T0
                  , T1
                  , T2
                  , T3
                  , T4
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                  , ::boost::parameter::void_
#endif
                >::type
                Args;
        //->

     public:
        typedef transition_function_tag
                tag;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_State
                >::type
                //->
                state;
        typedef bool
                result_type;
        typedef // implementation_defined
                //<-
                typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AttributeKey
                >::type
                //->
                attribute_key;

        //<-
     private:
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AttributeValue
                  , state
                >::type
                AttributeValue;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_AssociativeContainerSelector
                  , mapS
                >::type
                AssociativeContainerSelector;
        typedef typename ::boost::parameter::value_type<
                    Args
                  , keyword::tag::_RandomAccessContainerSelector
                  , vecS
                >::type
                RandomAccessContainerSelector;
        typedef _detail::decision_tree_transition_function_helper<
                    state
                  , attribute_key
                  , AttributeValue
                  , RandomAccessContainerSelector
                  , AssociativeContainerSelector
                >
                Helper;

     public:
        //->
        typedef typename Helper::builder
                builder;

        //<-
     private:
        Helper _helper;

     public:
        //->
        decision_tree_explicit_transition_function();

        decision_tree_explicit_transition_function(
            decision_tree_explicit_transition_function const& copy
        );

        decision_tree_explicit_transition_function&
            operator=(decision_tree_explicit_transition_function const& copy);

        template <typename Input>
        result_type operator()(state& current_state, Input const& i) const;

        void reset();

        builder add_transitions();

        builder add_transitions(attribute_key const& state_key);
    };

    //<-
    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    decision_tree_explicit_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::decision_tree_explicit_transition_function() : _helper()
    {
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    decision_tree_explicit_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::decision_tree_explicit_transition_function(
        decision_tree_explicit_transition_function const& copy
    ) : _helper(copy._helper)
    {
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    decision_tree_explicit_transition_function<T0,T1,T2,T3,T4>&
        decision_tree_explicit_transition_function<T0,T1,T2,T3,T4>::operator=(
            decision_tree_explicit_transition_function const& copy
        )
    {
        if (this != &copy)
        {
            _helper = copy._helper;
        }

        return *this;
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    template <typename Input>
    inline typename decision_tree_explicit_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::result_type
        decision_tree_explicit_transition_function<T0,T1,T2,T3,T4>::operator()(
            state& current_state
          , Input const& input
        ) const
    {
        if (_helper.is_ready_to_process_input())
        {
            return _helper.process_input(
                current_state
              , input
              , ::std::tr1::is_same<attribute_key,state>()
            );
        }
        else
        {
            return false;
        }
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void
        decision_tree_explicit_transition_function<T0,T1,T2,T3,T4>::reset()
    {
        _helper.reset();
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline typename decision_tree_explicit_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::builder
        decision_tree_explicit_transition_function<
            T0
          , T1
          , T2
          , T3
          , T4
        >::add_transitions()
    {
        return builder(_helper, false);
    }

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    inline typename decision_tree_explicit_transition_function<
        T0
      , T1
      , T2
      , T3
      , T4
    >::builder
        decision_tree_explicit_transition_function<
            T0
          , T1
          , T2
          , T3
          , T4
        >::add_transitions(attribute_key const& state_key)
    {
        return builder(_helper, state_key, false);
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_TRANSITION_FUNCTION_DECISION_TREE_HPP_INCLUDED

