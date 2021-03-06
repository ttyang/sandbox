// -*- mode:c++ -*-
//
// Header file visitor.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this material for any purpose is hereby
// granted without fee, provided the above notices are retained on all
// copies.  Permission to modify the material and to distribute modified
// versions is granted, provided the above notices are retained, and a
// notice that the material was modified is included with the above
// copyright notice.
//
// History
// =======
// 2003/ 9/11	rmg	File creation from container_suite.hpp
//
// $Id$
//

#ifndef visitor_rmg_20030823_included
#define visitor_rmg_20030823_included

#include "slice_handler.hpp"

#include <boost/python/def_visitor.hpp>
#include <boost/python/iterator.hpp>
#include <boost/bind.hpp>
#include <functional>

namespace indexing {
  namespace detail {
    template<typename PrecallPolicy>
    struct precall_only : public boost::python::default_call_policies
    {
      // This policies struct uses default policies for everything
      // except precall, which must be provided by the template
      // argument.

      precall_only () : mPrecall () { }
      explicit precall_only (PrecallPolicy const &copy) : mPrecall (copy) { }

      bool precall (PyObject *args) { return mPrecall.precall (args); }
      bool precall (PyObject *args) const { return mPrecall.precall (args); }

    private:
      PrecallPolicy mPrecall;
    };
  }

  //////////////////////////////////////////////////////////////////////////
  // __len__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_len {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __len__ real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_len<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__len__", &Algorithms::size, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<IndexStyle>
  struct maybe_add_getitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_getitem<index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __getitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_getitem<index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__getitem__", &Algorithms::get, policy);
      pyClass.def ("__getitem__"
		   , slice_handler<Algorithms, Policy>::make_getitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<IndexStyle>
  struct maybe_add_setitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_setitem<index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __setitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_setitem<index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__setitem__", &Algorithms::assign, policy);
      pyClass.def ("__setitem__"
		   , slice_handler<Algorithms, Policy>::make_setitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, IndexStyle syle>
  struct maybe_add_delitem {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ no-slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_delitem<true, index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__delitem__", &Algorithms::erase_one, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __delitem__ with slice
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_delitem<true, index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("__delitem__", &Algorithms::erase_one, policy);
      pyClass.def ("__delitem__"
		   , slice_handler<Algorithms, Policy>::make_delitem (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // __iter__ dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_iter {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // __iter__ real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_iter<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      // *FIXME* seperate precall and postcall portions of the
      // policy (precall when generating the range object, postcall
      // when returing from range.next())
      pyClass.def ("__iter__"
		   , boost::python::range<Policy> (Algorithms::begin
						   , Algorithms::end));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // append dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_append {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // append real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_append<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("append", &Algorithms::push_back, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // extend dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_extend {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // extend real
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_extend<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("extend"
		   , slice_handler<Algorithms, Policy>::make_extend (policy));
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // index dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit>
  struct maybe_add_index {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // index real
  //////////////////////////////////////////////////////////////////////////

  namespace detail {
    template<typename Algorithms>
    typename Algorithms::index_type
    get_index (typename Algorithms::container &c
	       , typename Algorithms::key_param key)
    {
      typename Algorithms::iterator temp (Algorithms::find (c, key));

      if (temp == Algorithms::end(c))
	{
	  PyErr_SetString (PyExc_ValueError
			   , "get_index: element not found");

	  boost::python::throw_error_already_set ();
	}

      return std::distance (Algorithms::begin (c), temp);
    }
  }

  template<>
  struct maybe_add_index<true> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("index", detail::get_index<Algorithms>, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // count dummy
  //////////////////////////////////////////////////////////////////////////

  template<bool doit, IndexStyle>
  struct maybe_add_count {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &, Algorithms const &, Policy const &) { }
  };

  //////////////////////////////////////////////////////////////////////////
  // count real (sequences without indexing)
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_count<true, index_style_none> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      pyClass.def ("count", Algorithms::count, policy);
    }
  };


  //////////////////////////////////////////////////////////////////////////
  // count real (sequences with indexing)
  //////////////////////////////////////////////////////////////////////////

  template<>
  struct maybe_add_count<true, index_style_linear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      // This is identical to the index_style_none version. Doing it
      // this way avoids using a partial specialization for
      // <true, *>
      pyClass.def ("count", Algorithms::count, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // count real (associative containers). add has_key
  //////////////////////////////////////////////////////////////////////////

  namespace detail {
    template<typename Algorithms>
    bool has_key (typename Algorithms::container &c
		  , typename Algorithms::key_param key)
    {
      return Algorithms::find (c, key) != Algorithms::end (c);
    }
  }

  template<>
  struct maybe_add_count<true, index_style_nonlinear> {
    template<class PythonClass, class Algorithms, class Policy>
    static void apply (PythonClass &pyClass
		       , Algorithms const &
		       , Policy const &policy)
    {
      // Nearest equivalent is has_key, since Python dictionaries
      // have at most one value for a key.
      pyClass.def ("has_key", detail::has_key<Algorithms>, policy);

      // Maybe this makes sense for multimap or multiset. Then again,
      // maybe they should always return a list of elements for a key?
      pyClass.def ("count", Algorithms::count, policy);
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // Do-all visitor
  //////////////////////////////////////////////////////////////////////////

  template<class Algorithms, class Policy>
  class visitor
    : public boost::python::def_visitor< visitor< Algorithms, Policy > >
  {
    Policy mPolicy;

  public:
    typedef Algorithms algorithms;
    typedef typename algorithms::container_traits traits;

    explicit visitor (Policy const &policy = Policy()) : mPolicy (policy) { }

    template <class PythonClass>
    void visit (PythonClass &pyClass) const
    {
      detail::precall_only<Policy> precallPolicy (mPolicy);

      // Note - this will add __len__ for anything that can determine
      // its size, even if that might be inefficient (e.g. have linear
      // time complexity). It might be better to add a new feature
      // selection flag to the container_traits to make this
      // configurable.
      maybe_add_len<traits::has_copyable_iter>
	::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_getitem<traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_setitem<traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_delitem<traits::has_erase, traits::index_style>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_iter<((traits::index_style != index_style_linear)
		      && traits::has_copyable_iter)>
	::apply (pyClass, algorithms(), mPolicy);

      maybe_add_append<traits::has_push_back>
	::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_extend<(traits::has_insert
			&& traits::index_style == index_style_linear)>
	::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_index<(traits::has_find
		       && (traits::index_style == index_style_linear))>
	::apply (pyClass, algorithms(), precallPolicy);

      maybe_add_count<traits::has_find, traits::index_style>
	::apply (pyClass, algorithms(), precallPolicy);

      Algorithms::visitor_helper (pyClass, mPolicy);
    }
  };
}

#endif // visitor_rmg_20030823_included
