//  Copyright (c) 2006, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file cursor_helpers.hpp
 * Cursor facade and adaptor implementations
 */

// TODO: Use TR1 type_traits (integral_constant)
// can we abstract the cursor stuff any further, 
// eventually producing cursor_adaptor?

#ifndef BOOST_TREE_CURSOR_HELPERS_HPP
#define BOOST_TREE_CURSOR_HELPERS_HPP

//#include <boost/tree/detail/node/nary.hpp>

#include <boost/type_traits/integral_constant.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <iterator>
#include <utility>

namespace boost {
namespace tree {

using boost::iterator_core_access;

class cursor_core_access {
 public:
  	template <class Facade>
	static bool empty_(Facade const& f)
	{
		return f.empty_();
	}
	
 	template <class Facade>
	static typename Facade::size_type size_(Facade const& f)
	{
		return f.size_();
	}
	
	template <class Facade>
	static typename Facade::size_type max_size_(Facade const& f)
	{
		return f.max_size_();
	}

	template <class Facade>
	static typename Facade::size_type par(Facade const& f)
	{
		return f.par();
	}
		
	template <class Facade>
	static Facade left(Facade const& f)
	{
		return f.left();
	}
	
	template <class Facade>
	static Facade right(Facade const& f)
	{
		return f.right();
	}
	
	//only if ascending
	template <class Facade>
	static Facade up(Facade const& f)
	{
		return f.up();
	}
	
};

template <
    class Derived             // The derived cursor type being constructed
  , class Value
  , class HorizontalCategoryOrTraversal
  , class VerticalCategoryOrTraversal
  , class Reference   = Value&
  , class Difference  = std::ptrdiff_t
  , class Size		  = std::size_t
>
class cursor_facade 
 : public iterator_facade<Derived, Value, HorizontalCategoryOrTraversal> {
 private:
 	//typedef Derive<Value> Derived;
	//
	// Curiously Recurring Template interface.
	//
	Derived& derived()
	{
	    return *static_cast<Derived*>(this);
	}
	
	Derived const& derived() const
	{
	    return *static_cast<Derived const*>(this);
	}

//	typedef iterator_facade<Derived, Value, HorizontalCategoryOrTraversal, 
//							Reference, Difference> iterator_facade_;
	typedef typename cursor_facade::iterator_facade_ iterator_facade_;
 protected:
 	// For use by derived classes
	typedef cursor_facade<Derived, Value, HorizontalCategoryOrTraversal,
						  VerticalCategoryOrTraversal, Reference, Difference> 
			cursor_facade_;
 public:

	typedef typename iterator_facade_::value_type value_type;
	typedef Reference reference;
	typedef Difference difference_type;
	typedef typename iterator_facade_::pointer pointer;
	typedef typename iterator_facade_::iterator_category iterator_category;

	typedef Size size_type;

	typedef bidirectional_traversal_tag cursor_category;

	bool const empty() const
	{
		return cursor_core_access::empty_(this->derived());
	}
	
	size_type const size() const
	{
		return cursor_core_access::size_(this->derived());
	}
	
	size_type const max_size() const
	{
		return cursor_core_access::max_size_(this->derived());
	}

	size_type const parity() const
	{
		return cursor_core_access::par(this->derived());
	}
			 
 	Derived begin()
 	{
		return cursor_core_access::left(this->derived()); 		
 	}

 	Derived end()
 	{
		return cursor_core_access::right(this->derived()); 		
 	}
 	
 	Derived parent()
 	{
		return cursor_core_access::up(this->derived()); 		
 	}
};

template <
    class Derived
  , class Base
  , class Value               = use_default
  , class HorizontalTraversal = use_default
  , class VerticalTraversal	  = use_default
  , class Reference           = use_default
  , class Difference          = use_default
  , class Size                = use_default
>
class cursor_adaptor 
  : public iterator_adaptor<Derived, Base, Value, HorizontalTraversal, Reference,
  							Difference>
{
	friend class iterator_core_access;
	friend class cursor_core_access;
	typedef iterator_adaptor<Derived, Base, Value, HorizontalTraversal, Reference,
  							Difference> iterator_adaptor_;
 public:
    cursor_adaptor() : iterator_adaptor_()
    { }
    
    explicit cursor_adaptor(Base const& iter) : iterator_adaptor_(iter)
    { }
    
    typedef HorizontalTraversal horizontal_traversal;
    typedef VerticalTraversal cursor_category;
    
    typedef Size size_type;
    typedef Base base_type;
    
    
 protected:
    typedef cursor_adaptor cursor_adaptor_;

 public:
 	bool const empty_() const
	{
		return iterator_adaptor_::base().empty();
	}
	
	size_type const size_() const
	{
		return iterator_adaptor_::base().size();
	}
	
	size_type const max_size_() const
	{
		return iterator_adaptor_::base().max_size();
	}

	size_type const par() const
	{
		return iterator_adaptor_::base().parity();
	}
		
	Derived begin()
	{
		return Derived(this->base_reference().begin());
	}
	
	Derived end()
	{
		return Derived(this->base_reference().end());
	}
	
	Derived parent()
	{
		return Derived(this->base_reference().parent());
	}
};

//TODO: Put somewhere else?
template <class Value>
struct metadata {
	struct type {};
};

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_CURSOR_HELPERS_HPP