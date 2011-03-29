/* Copyright Joaqu�n M L�pez Mu�oz 2003-2004. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#ifndef BOOST_INDEXED_SET_MODIFY_KEY_ADAPTOR_HPP
#define BOOST_INDEXED_SET_MODIFY_KEY_ADAPTOR_HPP

namespace boost{

namespace indexed_sets{

namespace detail{

/* Functional adaptor to resolve modify_key as a call to modify.
 * Preferred over compose_f_gx and stuff cause it eliminates problems
 * with references to references, dealing with function pointers, etc.
 */

template<typename Modifier,typename Value,typename KeyFromValue>
struct modify_key_adaptor
{

  modify_key_adaptor(Modifier mod_,KeyFromValue kfv_):mod(mod_),kfv(kfv_){}

  void operator()(Value& x)
  {
    mod(kfv(x));
  }

private:
  Modifier     mod;
  KeyFromValue kfv;
};

} /* namespace indexed_sets::detail */

} /* namespace indexed_sets */

} /* namespace boost */

#endif