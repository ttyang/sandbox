// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_INPUT_RULE_WOLFRAM_CODE_HPP_INCLUDED
#define BOOST_AUTOMATA_INPUT_RULE_WOLFRAM_CODE_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/utility/associative_container_gen.hpp>

//[reference__wolfram_code_input_rule
namespace boost { namespace automata {

    template <
        typename StateElement
      , typename AssociativeContainerSelector = ::boost::mapS
    >
    class wolfram_code_input_rule
    {
        // typedef implementation_defined Setter;
        //<-
        typedef ::boost::tuple<StateElement,StateElement,StateElement>
                Neighborhood;
        typedef typename ::boost::mpl::apply_wrap2<
                    ::boost::associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , Neighborhood
                  , StateElement
                >::type
                Code;

        class Setter
        {
            wolfram_code_input_rule& _rule;
            Neighborhood _key;

         public:
            Setter(
                wolfram_code_input_rule& rule
              , StateElement const& prior_old_value
              , StateElement const& old_value
              , StateElement const& next_old_value
            );

            void operator=(StateElement const& new_value);
        };

        Code         _code;
        StateElement _blank;
        //->

     public:
        wolfram_code_input_rule();

        explicit wolfram_code_input_rule(StateElement const& blank);

        void reset();

        void reset(StateElement const& blank);

        void
            add_association(
                StateElement const& prior_old_value
              , StateElement const& old_value
              , StateElement const& next_old_value
              , StateElement const& new_value
            );

        Setter
            operator()(
                StateElement const& prior_old_value
              , StateElement const& old_value
              , StateElement const& next_old_value
            );

        template <typename StateSequence>
        StateSequence operator()(StateSequence const& current_state) const;

        //<-
     private:
        StateElement const&
            _find_element(
                StateElement const& e1
              , StateElement const& e2
              , StateElement const& e3
            ) const;

        template <typename StateSequence>
        void _normalize(StateSequence& next_state) const;
        //->
    };

    //<-
    template <typename StateElement, typename AssociativeContainerSelector>
    wolfram_code_input_rule<
        StateElement
      , AssociativeContainerSelector
    >::Setter::Setter(
        wolfram_code_input_rule& rule
      , StateElement const& prior_old_value
      , StateElement const& old_value
      , StateElement const& next_old_value
    ) : _rule(rule), _key(prior_old_value, old_value, next_old_value)
    {
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    inline void
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::Setter::operator=(StateElement const& new_value)
    {
        _rule._code.insert(typename Code::value_type(_key, new_value));
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    wolfram_code_input_rule<
        StateElement
      , AssociativeContainerSelector
    >::wolfram_code_input_rule() : _code(), _blank()
    {
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    wolfram_code_input_rule<
        StateElement
      , AssociativeContainerSelector
    >::wolfram_code_input_rule(StateElement const& blank)
      : _code(), _blank(blank)
    {
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    inline void
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::reset()
    {
        _code.clear();
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    inline void
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::reset(StateElement const& blank)
    {
        _code.clear();
        _blank = blank;
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    inline void
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::add_association(
            StateElement const& prior_old_value
          , StateElement const& old_value
          , StateElement const& next_old_value
          , StateElement const& new_value
        )
    {
        _code.insert(
            typename Code::value_type(
                Neighborhood(prior_old_value, old_value, next_old_value)
              , new_value
            )
        );
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    inline typename wolfram_code_input_rule<
        StateElement
      , AssociativeContainerSelector
    >::Setter
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::operator()(
            StateElement const& prior_old_value
          , StateElement const& old_value
          , StateElement const& next_old_value
        )
    {
        return Setter(*this, prior_old_value, old_value, next_old_value);
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    inline StateElement const&
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::_find_element(
            StateElement const& e1
          , StateElement const& e2
          , StateElement const& e3
        ) const
    {
        typename Code::const_iterator itr = _code.find(
            Neighborhood(e1, e2, e3)
        );

        return (itr == _code.end()) ? _blank : itr->second;
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    template <typename StateSequence>
    void
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::_normalize(StateSequence& next_state) const
    {
        while (!next_state.empty() && (next_state.back() == _blank))
        {
            next_state.pop_back();
        }

        while (!next_state.empty() && (next_state.front() == _blank))
        {
            next_state.pop_front();
        }
    }

    template <typename StateElement, typename AssociativeContainerSelector>
    template <typename StateSequence>
    StateSequence
        wolfram_code_input_rule<
            StateElement
          , AssociativeContainerSelector
        >::operator()(StateSequence const& current_state) const
    {
        BOOST_CONCEPT_ASSERT((::boost::FrontInsertionSequence<StateSequence>));
        BOOST_CONCEPT_ASSERT((::boost::BackInsertionSequence<StateSequence>));
        BOOST_MPL_ASSERT((
            ::std::tr1::is_same<
                typename StateSequence::value_type
              , StateElement
            >
        ));

        typename StateSequence::const_iterator itr_0 = current_state.begin();
        typename StateSequence::const_iterator itr_begin = itr_0;
        typename StateSequence::const_iterator itr_end = current_state.end();
        StateSequence next_state(current_state);

        if (itr_0 == itr_end)
        {
            next_state.push_back(_find_element(_blank, _blank, _blank));
            _normalize(next_state);
            return next_state;
        }

        typename StateSequence::const_iterator itr_1 = itr_0;

        if (++itr_1 == itr_end)
        {
            next_state.push_front(_find_element(_blank, _blank, *itr_0));
            next_state.back() = _find_element(_blank, *itr_0, _blank);
            next_state.push_back(_find_element(*itr_0, _blank, _blank));
            _normalize(next_state);
            return next_state;
        }

        typename StateSequence::const_iterator itr_2 = itr_1;

        next_state.front() = _find_element(_blank, *itr_0, *itr_1);
        next_state.push_front(_find_element(_blank, _blank, *itr_0));

        if (++itr_2 == itr_end)
        {
            next_state.back() = _find_element(*itr_0, *itr_1, _blank);
            next_state.push_back(_find_element(*itr_1, _blank, _blank));
            _normalize(next_state);
            return next_state;
        }

        typename StateSequence::iterator n_itr = next_state.begin();

        ++n_itr;

        do
        {
            *(++n_itr) = _find_element(*itr_0, *itr_1, *itr_2);
            ++itr_0;
            ++itr_1;
        }
        while (++itr_2 != itr_end);

        *(++n_itr) = _find_element(*itr_0, *itr_1, _blank);
        next_state.push_back(_find_element(*itr_1, _blank, _blank));
        _normalize(next_state);
        return next_state;
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_INPUT_RULE_WOLFRAM_CODE_HPP_INCLUDED

