// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_GENERIC_OBJECT_HPP
#define BOOST_OBJECT_MODEL_GENERIC_OBJECT_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/forward_declarations.hpp>
#include <boost/object_model/handle.hpp>
#include <boost/object_model/type/traits.hpp>
#include <boost/object_model/generic/base.hpp>

BOOST_OM_BEGIN

namespace generic
{
	struct object_base
	{
	protected:
		registry *reg;
		klass const *type;
		handle number;

		object_base();
		object_base(const object_base&);
		object_base(const const_storage&);

		template <class T, class Al> friend struct object_model::klass;

		void construct(registry &, klass const &, handle);

	public:
		klass const &get_class() const;
		type::number get_type_number() const;
		registry &get_registry() const;
		handle get_handle() const;

		const storage &get_storage() const;
		bool exists() const;

		template <class T>
		bool is_type() const
		{
			return get_type_number() == type::traits<T>::type_number;
		}
	};

	struct const_object : object_base
	{

	protected:

	public:
//		const_object();
		//const_object(const const_storage &);
		//const_object(const const_object &);
		//const_object(const object &);
		//const_object &operator=(const const_object &);

	};

	// can be const or mutable
	struct object : const_object
	{
	private:
		bool konst;

	public:
		object();
		object(const const_object&);
		object(const mutable_object&);
//		object(const object&);
		object(const storage &);
		object(const const_storage &);

		object &operator=(const const_object&);
		object &operator=(const mutable_object&);
//		object &operator=(const object&);

		bool is_const() const { return konst; }
		storage &get_storage();
	};

	struct mutable_object : const_object
	{
		mutable_object();
		mutable_object(storage &);
		mutable_object(const object &obj) : const_object(obj) { }

		storage &get_storage();
	};

}

extern const generic::object null_object;

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_GENERIC_OBJECT_HPP

//EOF
