//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_REF_LIST_TUPLE_EXTRACTION_ER_2010_HPP
#define BOOST_ASSIGN_V2_REF_LIST_TUPLE_EXTRACTION_ER_2010_HPP
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace ref{
namespace list_tuple_aux{

    template<std::size_t N, typename L, typename T, typename D>
    class extraction
    {
        typedef D const& result_of_derived_;
        result_of_derived_ derived()const
        {
            return static_cast<
                result_of_derived_
            >( *this );
        }

        public:

        template<int I>
        struct is_head : boost::mpl::bool_< I + 1 == N >{};

        template<int I>
        struct link_get_result : L::template get_result<I>{};

		template<int I>
		struct get_result : boost::mpl::eval_if<
        	is_head<I>,
            boost::mpl::identity<
            	T const&
            >,
            link_get_result<I>
        >{};

        template<int I>
        typename boost::lazy_enable_if<
        	is_head<I>,
        	get_result<I>
        >::type
        get(boost::mpl::int_<I> index)const
        {
        	return this->derived().get_tuple();
        }

        template<int I>
        typename boost::lazy_disable_if<
        	is_head<I>,
        	get_result<I>
        >::type
        get( boost::mpl::int_<I> index )const
        {
            return this->derived().get_link().unlink.get( index );
        }

    };

}// list_tuple_aux
}// ref
}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_REF_LIST_TUPLE_EXTRACTION_ER_2010_HPP