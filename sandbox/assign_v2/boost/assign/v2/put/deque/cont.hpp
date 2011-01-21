//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_DEQUE_CONT_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_DEQUE_CONT_ER_2010_HPP
#include <deque>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size.hpp>
#include <boost/range/size_type.hpp>
#include <boost/assign/v2/put/generic/result_of_modulo.hpp>
#include <boost/assign/v2/put/generic/crtp.hpp>
#include <boost/assign/v2/put/deque/fwd.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace result_of_modulo{

    template<typename T,typename F,typename Tag>
    struct new_fun<put_deque_aux::cont<T,F,Tag> >
    {

    	template<typename F1>
        struct apply{ typedef put_deque_aux::cont<T, F1, Tag> type; };

    };

    template<typename T,typename F,typename Tag>
    struct new_modifier<put_deque_aux::cont<T,F,Tag> >
    {

    	template<typename NewTag>
        struct apply{ typedef put_deque_aux::cont<T, F, NewTag> type; };

    };

}//result_of_modulo
namespace put_deque_aux{

    template<typename T>
    struct impl{ typedef std::deque<T> type; };

    template<typename T, typename F, typename Tag>
    class cont :
        public put_aux::crtp<
        	typename put_deque_aux::impl<T>::type, F, Tag,
            cont<T, F, Tag>
        >
    {
        typedef typename put_deque_aux::impl<T>::type impl_;
        typedef impl_ const cimpl_;
        typedef put_aux::crtp<impl_, F, Tag, cont> put_crtp_;

        typedef put_aux::modifier<Tag> modifier_;

    	public:

    	typedef T value_type;
        typedef typename boost::range_size<impl_>::type size_type;
        typedef typename boost::range_iterator<impl_>::type iterator;
        typedef typename boost::range_iterator<cimpl_>::type const_iterator;

        // Construct
        cont(){}
        explicit cont(const F& f) : put_crtp_( f ){}
        explicit cont(impl_ const& v, F const& f): put_crtp_( f ), impl( v )
        {
        	// Required by crtp when Tag or F is modified.
        }

        explicit cont( impl_ const& v, F const& f, modifier_ const& m )
            : put_crtp_( f, m ), impl( v )
        {
        	// Required by crtp when Tag or F is modified.
        }

        // Deque interface
        iterator begin(){
            return boost::begin( this->impl );
        }
        iterator end(){
            return boost::end( this->impl );
        }
        const_iterator begin()const{
            return boost::begin( this->impl );
        }
        const_iterator end()const{
        	return boost::end( this->impl );
        }

        typedef typename impl_::reference reference;
        typedef typename impl_::const_reference const_reference;
        typedef typename impl_::difference_type difference_type;

        size_type size()const{
            return this->get().size();
        }
        size_type max_size()const{
            return this->get().max_size();
        }
        bool empty()const{
            return this->get().empty();
        }
        reference operator[](size_type n){
            return this->get()[n];
        }
        const_reference operator[](size_type n)const{
            return this->get()[n];
        }
        reference front(){
            return this->get().front();
        }
        const_reference front()const{
            return this->get().front();
        }
		reference back(){
        	return this->get().back();
        }
        const_reference back()const{
            return this->get().back();
        }
        void pop_front(){
            this->get().pop_front();
        }
        void pop_back(){
            this->get().pop_back();
        }
        void swap(cont& that){
            this->get().swap( that.get() );
        }

        // Note : the modifiers such as push_back() are ommitted as they
        // accessible through the put interface.

       impl_& get()const{ return this->impl; }
        protected:
        mutable impl_ impl;

    };

}// put_deque_aux
}// v2
}// assign
}// boost

#endif