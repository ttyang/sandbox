//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_PIPE_FORWARD_PARS_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_PIPE_FORWARD_PARS_ER_2010_HPP
#include <boost/mpl/apply.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/assign/v2/put/generic/result_of_modulo.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace put_pipe_aux{

	template<std::size_t N, typename Pars, typename T,
    	bool exit = (N == boost::mpl::size<Pars>::value)>
	struct result_of_forward_pars
    {
    	typedef typename boost::mpl::at_c<Pars, N>::type at_;
        typedef result_of_modulo::generic<T> meta_;
        typedef typename boost::mpl::apply1<meta_, at_>::type new_t_;

        typedef result_of_forward_pars<N+1, Pars, new_t_> next_;

        typedef typename next_::type type;

        template<typename H>
        static type call(H const& h, T const& t)
        {
        	typedef boost::mpl::int_<N> int_;
        	return next_::call(
            	h,
                t % h.static_lookup( int_() )
            );
        }

    };

	template<std::size_t N,typename Pars, typename T>
	struct result_of_forward_pars<N, Pars, T, true>
    {

		typedef T type;

        template<typename H>
        static type call(H const& h, T const& t)
        {
        	return t;
        }

    };

	template<typename Pars, typename T,typename C>
    typename result_of_forward_pars<0, Pars, T>::type
	forward_pars(
        T const& object,
        C const& c
	)
    {
    	typedef result_of_forward_pars<0, Pars, T> caller_;
        return caller_::call( c, object );
	}

}// put_pipe_aux
namespace result_of{

	template<typename T,typename Pars>
    struct forward_pars : put_pipe_aux::result_of_forward_pars<
		0,
        Pars,
        T
    >{};

}// result_of
}// v2
}// assign
}// boost

#endif