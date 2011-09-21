// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_KEYWORD_TEMPLATE_HPP_INCLUDED
#define BOOST_AUTOMATA_KEYWORD_TEMPLATE_HPP_INCLUDED

#include <boost/parameter/aux_/template_keyword.hpp>

namespace boost { namespace automata { namespace keyword {
  namespace tag {

    struct _Function;
    struct _State;
    struct _Input;
    struct _StackElement;
    struct _AttributeKey;
    struct _AttributeValue;
    struct _RealNumber;
    struct _AssociativeContainerSelector;
    struct _RandomAccessContainerSelector;
  }  // namespace tag

    template <typename T>
    struct _Function
      : boost::parameter::template_keyword<tag::_Function,T>
    {
    };

    template <typename T>
    struct _State
      : boost::parameter::template_keyword<tag::_State,T>
    {
    };

    template <typename T>
    struct _Input
      : boost::parameter::template_keyword<tag::_Input,T>
    {
    };

    template <typename T>
    struct _StackElement
      : boost::parameter::template_keyword<tag::_StackElement,T>
    {
    };

    template <typename T>
    struct _AttributeKey
      : boost::parameter::template_keyword<tag::_AttributeKey,T>
    {
    };

    template <typename T>
    struct _AttributeValue
      : boost::parameter::template_keyword<tag::_AttributeValue,T>
    {
    };

    template <typename T>
    struct _RealNumber
      : boost::parameter::template_keyword<tag::_RealNumber,T>
    {
    };

    template <typename T>
    struct _AssociativeContainerSelector
      : boost::parameter::template_keyword<
            tag::_AssociativeContainerSelector
          , T
        >
    {
    };

    template <typename T>
    struct _RandomAccessContainerSelector
      : boost::parameter::template_keyword<
            tag::_RandomAccessContainerSelector
          , T
        >
    {
    };

  namespace tag {

    struct _StateRecognizer;
    struct _InputRecognizer;
  }  // namespace tag

    template <typename T>
    struct _StateRecognizer
      : boost::parameter::template_keyword<tag::_StateRecognizer,T>
    {
    };

    template <typename T>
    struct _InputRecognizer
      : boost::parameter::template_keyword<tag::_InputRecognizer,T>
    {
    };

  namespace tag {

    struct _Graph;
    struct _VertexStateMap;
    struct _EdgeInputMap;
    struct _Policies;
  }  // namespace tag

    template <typename T>
    struct _Graph
      : boost::parameter::template_keyword<tag::_Graph,T>
    {
    };

    template <typename T>
    struct _VertexStateMap
      : boost::parameter::template_keyword<tag::_VertexStateMap,T>
    {
    };

    template <typename T>
    struct _EdgeInputMap
      : boost::parameter::template_keyword<tag::_EdgeInputMap,T>
    {
    };

    template <typename T>
    struct _Policies
      : boost::parameter::template_keyword<tag::_Policies,T>
    {
    };

  namespace tag {

    struct _BaseGenerator;
    struct _InputValidationPolicy;
    struct _IsUndoable;
  }  // namespace tag

    template <typename T>
    struct _BaseGenerator
      : boost::parameter::template_keyword<tag::_BaseGenerator,T>
    {
    };

    template <typename T>
    struct _InputValidationPolicy
      : boost::parameter::template_keyword<tag::_InputValidationPolicy,T>
    {
    };

    template <typename T>
    struct _IsUndoable
      : boost::parameter::template_keyword<tag::_IsUndoable,T>
    {
    };
}}}  // namespace boost::automata:keyword

#endif  // BOOST_AUTOMATA_KEYWORD_TEMPLATE_HPP_INCLUDED

