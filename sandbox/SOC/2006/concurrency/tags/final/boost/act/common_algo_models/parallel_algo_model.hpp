//  Copyright (c) 2006, Matthew Calabrese
//
//  This code may be used under either of the following two licences:
//
//    Permission is hereby granted, free of charge, to any person
//    obtaining a copy of this software and associated documentation
//    files (the "Software"), to deal in the Software without
//    restriction, including without limitation the rights to use,
//    copy, modify, merge, publish, distribute, sublicense, and/or
//    sell copies of the Software, and to permit persons to whom the
//    Software is furnished to do so, subject to the following
//    conditions:
//
//    The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//    OTHER DEALINGS IN THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACT_COMMON_ALGO_MODELS_PARALLEL_ALGO_MODEL_HPP
#define BOOST_ACT_COMMON_ALGO_MODELS_PARALLEL_ALGO_MODEL_HPP

#include "../algo_model.hpp"

#include "parallel_algo_model/detail/parallel_basic_for.hpp"
#include "parallel_algo_model/detail/parallel_count_if.hpp"
#include "serial_algo_model/detail/serial_basic_for.hpp"

#include "../algorithm/basic_for/basic_for_base.hpp"

#include <boost/utility/enable_if.hpp>

namespace boost
{
namespace act
{
namespace detail
{
struct parallel_algo_model_tag;
}

struct parallel_algo_model
  : algo_model< detail::parallel_algo_model_tag >
{
};

template< typename AlgoModel >
struct basic_for_impl;

template<>
struct basic_for_impl< parallel_algo_model >
  : basic_for_base
{
  using basic_for_base::execute;

  template< typename ExtendedParams
          , typename AssignType
          , typename ConditionType
          , typename StepType
          , typename FunctionType
          >
  static typename
  ::boost::enable_if
  <
    is_parallel_safe< FunctionType >
  , FunctionType
  >
  ::type
  execute( ExtendedParams const& extended_params
         , AssignType assign
         , ConditionType condition
         , StepType step
         , FunctionType& body
         )
  {
    return detail::parallel_basic_for
             ( extended_params, assign, condition, step, body );
  }

  template< typename ExtendedParams
          , typename AssignType
          , typename ConditionType
          , typename StepType
          , typename FunctionType
          >
  static typename
  ::boost::disable_if
  <
    is_parallel_safe< FunctionType >
  , FunctionType
  >
  ::type
  execute( ExtendedParams const& extended_params
         , AssignType assign
         , ConditionType condition
         , StepType step
         , FunctionType& body
         , void** dummy = 0 // Workaround for GCC
         )
  {
    return detail::serial_basic_for
             ( extended_params, assign, condition, step, body );
  }
};

}
}

#endif
