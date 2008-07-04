/**
 * \file examples/registering/namespaces.cpp
 * Example of namespace registering and reflection with
 * the mirror library
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

// narrow/wide char stream
#include <boost/char_type_switch/iostream.hpp>
// namespace registering 
#include <boost/mirror/meta_namespace.hpp>
// utility that allows to put the name of the namespace to a given stream
#include <boost/mirror/utils/name_to_stream/namespace.hpp>
//
// mpl size meta function
#include <boost/mpl/size.hpp>


namespace test {
namespace feature {
namespace detail {

} // namespace detail
} // namespace feature

namespace stuff {
namespace detail {

} // namespace detail
} // namespace stuff
} // namespace test


namespace boost { 
namespace mirror {

// register the namespaces
//
BOOST_MIRROR_REG_NAMESPACE((test))
BOOST_MIRROR_REG_NAMESPACE((test)(feature))
BOOST_MIRROR_REG_NAMESPACE((test)(feature)(detail))
// 
BOOST_MIRROR_REG_NAMESPACE((test)(stuff))
BOOST_MIRROR_REG_NAMESPACE((test)(stuff)(detail))

} // namespace mirror
} // namespace boost

int main(void)
{
	using namespace ::std;
	using namespace ::boost;
	using namespace ::boost::mirror;
	//
	// NOTE bcout ~ cout when using narrow chars
	//            ~ wcout when using wide chars
	// it's typedef'd in the boost namespace
	//
	// the BOOST_MIRRORED_NAMESPACE(FULL_NAMESPACE_NAME) returns the 
	// meta_namespace<> specialization for the given namespace 
	//
	// define an alternative name for the global scope meta-namespace
	// BOOST_MIRRORED_NAMESPACE(::__) is equivalent to this
	typedef BOOST_MIRRORED_GLOBAL_SCOPE() meta_ns_global_scope;

	// define an alternative name for the ::test namespace meta-data
	typedef BOOST_MIRRORED_NAMESPACE(::test) meta_ns_test;
	typedef BOOST_MIRRORED_NAMESPACE(::test::stuff::detail) meta_ns_test_stuff_detail;
	//
	//
	// the base name function allows to get the base name
	// of the namespace
	//
	// print the base name of the namespace
	bcout << "|01| " <<meta_ns_test_stuff_detail::base_name() << endl;
	//
	// the 'parent' type is the meta_namespace<> for the parent
	// namespace of the given namespace
	//
	// print the base name of the parent namespace 
	bcout << "|02| " <<meta_ns_test_stuff_detail::scope::base_name() << endl;
	bcout << "|03| " <<meta_ns_test_stuff_detail::scope::scope::base_name() << endl;
	//
	// the 'scope' member is a mpl::vector containing the whole 
	// list of ancestor namespaces 
	//
	// find out and print the 'depth' of the namespace
	bcout << "|04| " <<mpl::size<meta_ns_global_scope::ancestors>::value << endl;
	bcout << "|05| " <<mpl::size<meta_ns_test::ancestors>::value << endl;
	bcout << "|06| " <<mpl::size<meta_ns_test_stuff_detail::ancestors>::value << endl;
	//
	// the name_to_stream<meta_object> class allows to put the full name
	// (including the scope) into a stream
	bcout << "|07| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::__) >() << endl;
	bcout << "|08| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::test) >() << endl;
	bcout << "|09| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::test::stuff) >() << endl;
	bcout << "|10| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::test::stuff::detail) >() << endl;
	// in this case the :: is prepended to the full name
	// thus test::stuff -> ::test::stuff
	bcout << "|11| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::__) >(true) << endl;
	bcout << "|12| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::test) >(true) << endl;
	bcout << "|13| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::test::stuff) >(true) << endl;
	bcout << "|14| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::test::stuff::detail) >(true) << endl;
	//
	// there are few namespace registered by default
	// including (::std, ::boost, ::boost::mirror)
	bcout << "|15| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::std) >(true) << endl;
	bcout << "|16| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::boost) >(true) << endl;
	bcout << "|17| " <<name_to_stream< BOOST_MIRRORED_NAMESPACE(::boost::mirror) >(true) << endl;
	//
	// printing out the full namespace names directly without the name_to_stream
	// printer template
	bcout << "|18| " << BOOST_MIRRORED_NAMESPACE(::__) ::full_name() << endl;
	bcout << "|19| " << BOOST_MIRRORED_NAMESPACE(::std) ::full_name() << endl;
	bcout << "|20| " << BOOST_MIRRORED_NAMESPACE(::boost) ::full_name() << endl;
	bcout << "|21| " << BOOST_MIRRORED_NAMESPACE(::boost::mirror) ::full_name() << endl;
	bcout << "|22| " << BOOST_MIRRORED_NAMESPACE(::test) ::full_name() << endl;
	bcout << "|23| " << BOOST_MIRRORED_NAMESPACE(::test::stuff) ::full_name() << endl;
	bcout << "|24| " << BOOST_MIRRORED_NAMESPACE(::test::stuff::detail) ::full_name() << endl;
	return 0;
}

