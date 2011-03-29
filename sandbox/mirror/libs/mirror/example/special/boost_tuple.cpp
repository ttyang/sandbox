/**
 * \file examples/special/boost_tuple.cpp
 * 
 * Example showing reflection of boost::tuples 
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#include <boost/char_type_switch/string.hpp>
#include <boost/char_type_switch/iostream.hpp>

#include <boost/mirror/meta_namespace.hpp>
#include <boost/mirror/meta_type.hpp>
#include <boost/mirror/meta_class.hpp>

#include <boost/mirror/algorithms.hpp>
#include <boost/mirror/functions.hpp>

#include <boost/mirror/meta_types/boost/tuples/tuple.hpp>
#include <boost/mirror/meta_types/std/pair.hpp>
#include <boost/mirror/meta_types/std/vector.hpp>
#include <boost/mirror/meta_types/std/list.hpp>
#include <boost/mirror/meta_types/std/map.hpp>
#include <boost/mirror/meta_types/std/set.hpp>
#include <boost/mirror/meta_types/boost/any.hpp>
#include <boost/mirror/meta_types/boost/variant.hpp>
#include <boost/mirror/meta_types/boost/optional.hpp>

#include <boost/mirror/meta_classes/boost/tuples/tuple.hpp>
#include <boost/mirror/meta_classes/boost/fusion/vector.hpp>

template <class Class>
class attrib_value_printer
{
public:
                attrib_value_printer(Class& _inst)
                : inst(_inst){ }
	
                template <typename MetaAttribute>
                void operator()(MetaAttribute ma) const
                {
                        using namespace ::std;
                        using namespace ::boost;
                        using namespace ::boost::mirror;
						cts::bcout() <<
                                " " <<
                                ma.base_name() <<
				" [offset: " <<
				ma.offset_of() <<
                                "] = " <<
                                ma.get(inst) <<
                                endl;
                }
private:
	Class& inst;
};

struct str_printer
{
	void operator()(const ::boost::cts::bstring& str) const
	{
		::boost::cts::bcout() << str << ", ";
	}
	~str_printer(void)
	{
		::boost::cts::bcout() << ::std::endl;
	}
};

int main(void)
{
	using namespace ::std;
	using namespace ::boost;
	using namespace ::boost::mirror;
	//
	cts::bostream& bcout = cts::bcout();
	//
	typedef int (*A)(double);
	typedef A (*B)(string);
	typedef B (C)(char, wchar_t);
	typedef A D[2][3];
        typedef ::boost::optional< ::boost::any> Z;
        typedef ::boost::variant< A, B, C&, D> V;
	typedef ::boost::tuple<int, double, const string *> T1;
	typedef ::boost::tuple<const A, volatile B, C&, D, V, Z> T2;
	typedef pair<T1, T2> T3;
	typedef ::boost::tuple<void*, const wstring& , const string&> T4;
	typedef ::boost::tuple<char, wchar_t, short int const> T5;
	typedef pair<T4, T5> T6;
	typedef vector< ::boost::tuple<T1, T2, T3, T4, T5, T6> > T7;
	typedef set<map<list<T1>, T7> > T;
	//
	typedef BOOST_MIRRORED_CLASS(T) meta_T;
	//
	//
	//
	bcout << "---------------------------------------------------" << endl;
	bcout << "The type name is: "<< meta_T::base_name() << endl;
	bcout << "---------------------------------------------------" << endl;
	bcout << "The full type name is: "<< meta_T::full_name() << endl;
	bcout << "---------------------------------------------------" << endl;
	//
	T1 t1(12, 34.56, 0);
	typedef BOOST_MIRRORED_CLASS(T1) meta_T1;
	bcout << "---------------------------------------------------" << endl;
	bcout << "The full type name is: "<< meta_T1::full_name() << endl;
	bcout << "---------------------------------------------------" << endl;
	bcout << "The class has "<< size<meta_T1::all_attributes>::value << " members" << endl;
	bcout << "---------------------------------------------------" << endl;
	bcout << meta_T1::all_attributes::get_name(mpl::int_<0>(), mpl::false_(), cts::bchar_traits()) << " = ";
	bcout << meta_T1::all_attributes::get(t1, mpl::int_<0>()) << endl;
	bcout << meta_T1::all_attributes::get_name(mpl::int_<1>(), mpl::false_(), cts::bchar_traits()) << " = ";
	bcout << meta_T1::all_attributes::get(t1, mpl::int_<1>()) << endl;
	bcout << meta_T1::all_attributes::get_name(mpl::int_<2>(), mpl::false_(), cts::bchar_traits()) << " = ";
	bcout << meta_T1::all_attributes::get(t1, mpl::int_<2>()) << endl;
	bcout << "---------------------------------------------------" << endl;
	//
	meta_T1::all_attributes::set(t1, mpl::int_<0>(), 23);
	meta_T1::all_attributes::set(t1, mpl::int_<1>(), 45.67);
	//
	assert(meta_T1::all_attributes::get(t1, mpl::int_<0>()) == tuples::get<0>(t1));
	assert(meta_T1::all_attributes::get(t1, mpl::int_<1>()) == tuples::get<1>(t1));
	//
	//
	fusion::vector<int, int, int, int, int, int, int, int, int, int> x(0,1,2,3,4,5,6,7,8,9);
	typedef BOOST_MIRRORED_CLASS(BOOST_TYPEOF(x)) meta_X;
	attrib_value_printer<meta_X::reflected_type> p(x);
	//
	bcout << "The type name is: "<< meta_X::base_name() << endl;
	bcout << "The class has "<< size<meta_X::all_attributes>::value << " members" << endl;
	bcout << "---------------------------------------------------" << endl;
	for_each<meta_X::attributes>(p);
	bcout << "---------------------------------------------------" << endl;
	reverse_for_each<meta_X::attributes>(p);
	bcout << "---------------------------------------------------" << endl;
	for_each<meta_X::attributes>(
		::boost::cref(select_base_name()), 
		::boost::cref(str_printer())
	);
	bcout << "---------------------------------------------------" << endl;
	for_each<
		begin<meta_X::attributes>::type,
		end<meta_X::attributes>::type
	>(::boost::cref(select_full_name()), ::boost::cref(str_printer()));
	bcout << "---------------------------------------------------" << endl;
	reverse_for_each<
		begin<meta_X::attributes>::type,
		end<meta_X::attributes>::type
	>(::boost::cref(select_base_name()), ::boost::cref(str_printer()));
	bcout << "---------------------------------------------------" << endl;
	bcout << "Finished" << endl;

	return 0;
}
