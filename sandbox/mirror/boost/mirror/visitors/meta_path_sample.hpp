/**
 * \file boost/mirror/visitors/meta_path_sample.hpp
 * Sample implementation of a meta-object visitor
 * showing how traversal contexts and meta-paths work
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MIRROR_VISITORS_META_PATH_SAMPLE
#define BOOST_MIRROR_VISITORS_META_PATH_SAMPLE

// meta namespaces (includes boost/char_type_switch/string.hpp)
#include <boost/mirror/meta_namespace.hpp>
// meta types 
#include <boost/mirror/meta_class.hpp>
// traits
#include <boost/mirror/traits/reflects_virtual_inheritance.hpp>
#include <boost/mirror/traits/reflects_global_scope.hpp>
// container size and emptiness
#include <boost/mirror/intrinsic/size.hpp>
#include <boost/mirror/intrinsic/empty.hpp>
//
// meta-path related stuff
#include <boost/mirror/meta_path/export_paths_and_nodes.hpp>
#include <boost/mirror/meta_path/for_each.hpp>
#include <boost/mirror/meta_path/self.hpp>
#include <boost/mirror/meta_path/parent.hpp>
#include <boost/mirror/meta_path/ancestors.hpp>
#include <boost/mirror/meta_path/ancestors_and_self.hpp>
#include <boost/mirror/meta_path/siblings.hpp>
#include <boost/mirror/meta_path/siblings_and_self.hpp>
#include <boost/mirror/meta_path/prior.hpp>
#include <boost/mirror/meta_path/next.hpp>
#include <boost/mirror/meta_path/size.hpp>

//
#include <boost/type_traits/is_fundamental.hpp>

namespace boost {
namespace mirror {

namespace detail {

	struct node_printer
	{
		bool simple;

		node_printer(void):simple(true){ }
		node_printer(const node_printer&):simple(false){ }

		void print_indent(void) const
		{
			if(!simple) cts::bcout() << ::std::endl << "\t\t";
		}

		template <
			class ReflectedType, 
			class VariantTag,
			class MetaAttributes,
			class AttribPos
		>
		void operator()(meta_class_attribute<
			ReflectedType,
			VariantTag,
			MetaAttributes,
			AttribPos
		> mca) const
		{
			cts::bcout() << "|attribute '" << mca.base_name() << "'|";
			print_indent();
		}
	
		template <
			class ReflectedType, 
			class VariantTag
		>
		void operator()(meta_class_attributes<
			ReflectedType,
			VariantTag
		> mca) const
		{
			cts::bcout() << "|attributes|";
			print_indent();
		}
	
		template <
			class ReflectedType, 
			class VariantTag
		>
		void operator()(meta_class_all_attributes<
			ReflectedType,
			VariantTag
		> mca) const
		{
			cts::bcout() << "|all_attributes|";
			print_indent();
		}
	
		template <
			class ReflectedType, 
			class VariantTag
		>
		void operator()(meta_base_classes<
			ReflectedType,
			VariantTag
		> mca) const
		{
			cts::bcout() << "|base_classes|";
			print_indent();
		}
	
		template < class InheritanceInfo >
		void operator()(meta_inheritance< InheritanceInfo > mi) const
		{
			typedef typename meta_inheritance<
				InheritanceInfo
			>::base_class mbc;
			cts::bcout() << "|base_class '" << mbc::base_name() << "'|";
			print_indent();
		}
	
		template <class Class>
		void operator()(meta_class<Class> mc) const
		{
			cts::bcout() << "|type '" << mc.base_name() << "'|";
			print_indent();
		}
	
		template <class Placeholder>
		void operator()(meta_namespace<Placeholder> mn) const
		{
			cts::bcout() << "|namespace '" << mn.base_name() << "'|";
			print_indent();
		}

		template <class Unknown>
		void operator()(Unknown) const
		{
			cts::bcout() << "|unknown |";
			print_indent();
		}
	};
	
} // namespace detail 

class meta_path_sample_visitor 
{
public:
	typedef mpl::bool_<false> works_on_instances;

        // enter a namespace
        template <class MetaNamespace, class Context>
        void enter_namespace(MetaNamespace, Context)
        {
		print_node(MetaNamespace(), Context());
        }

        // leave the namespace
        template <class MetaNamespace, class Context>
        void leave_namespace(MetaNamespace, Context) { }

        template <class MetaObjectSequence, class Context>
        void enter_namespace_members(MetaObjectSequence, Context) { }

        template <class MetaObjectSequence, class Context>
        void leave_namespace_members(MetaObjectSequence, Context) { }



	// enter a class/type
	template <class MetaClass, class Context>
	void enter_type(MetaClass, Context)
	{
		print_node(MetaClass(), Context());
	}

	template <class MetaClass, class BaseClasses, class Context>
	inline void enter_base_classes(MetaClass, BaseClasses, Context)
	{
		if(!empty<BaseClasses>::value)
			print_node(BaseClasses(), Context());
	}
	
	// enter a base class
	template <class MetaInheritance, class Context>
	void enter_base_class(MetaInheritance, Context)
	{
		print_node(MetaInheritance(), Context());
	}

	template <class MetaClass, class MetaAttributes, class Context>
	void enter_attributes(MetaClass, MetaAttributes, Context)
	{
		if(!empty<MetaAttributes>::value)
			print_node(MetaAttributes(), Context());
	}

	template <class MetaAttribute, class Context>
	inline void enter_attribute(MetaAttribute, Context)
	{
		print_node(MetaAttribute(), Context());
	}

private:

	template <template <class> class Axis, class MetaObject, class Context>
	void print_node_set(const char* name, MetaObject mo, Context ctx)
	{
		using ::std::endl;
		//
		cts::bcout() << "\t" << name << ": "; 
		meta_path::for_each<
			Axis<Context>, 
			mpl::lambda<mpl::second<mpl::_1> > 
		>(detail::node_printer());
		cts::bcout() << endl;
	}

	template <class MetaObject, class Context>
	void print_node(MetaObject mo, Context ctx)
	{
		using ::std::endl;
		//
		detail::node_printer p;
		cts::bcout() << "node "; 
		p(mo);
		cts::bcout() << ":" << endl;
		//
		print_node_set<meta_path::self>("self", mo, ctx);
		print_node_set<meta_path::parent>("parent", mo, ctx);
		print_node_set<meta_path::ancestors>("ancestors", mo, ctx);
		print_node_set<meta_path::ancestors_and_self>("ancestors_and_self", mo, ctx);
		print_node_set<meta_path::siblings>("siblings", mo, ctx);
		print_node_set<meta_path::siblings_and_self>("siblings_and_self", mo, ctx);
		print_node_set<meta_path::prior>("prior", mo, ctx);
		print_node_set<meta_path::next>("next", mo, ctx);
	}

};


} // namespace mirror
} // namespace boost

#endif //include guard
