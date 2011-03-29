/* Boost.IndexedSet test suite.
 *
 * Copyright Joaqu�n M L�pez Mu�oz 2003-2004. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#include <boost/test/included/test_exec_monitor.hpp>
#include "test_basic.hpp"
#include "test_capacity.hpp"
#include "test_comparison.hpp"
#include "test_conv_iterators.hpp"
#include "test_copy_assignment.hpp"
#include "test_iterators.hpp"
#include "test_key_extractors.hpp"
#include "test_list_ops.hpp"
#include "test_modifiers.hpp"
#include "test_mpl_ops.hpp"
#include "test_projection.hpp"
#include "test_range.hpp"
#include "test_safe_mode.hpp"
#include "test_set_ops.hpp"
#include "test_special_set_ops.hpp"
#include "test_update.hpp"

int test_main(int,char *[])
{
  test_basic();
  test_capacity();
  test_comparison();
  test_conv_iterators();
  test_copy_assignment();
  test_iterators();
  test_key_extractors();
  test_list_ops();
  test_modifiers();
  test_mpl_ops();
  test_projection();
  test_range();
  test_safe_mode();
  test_set_ops();
  test_special_set_ops();
  test_update();

  return 0;
}