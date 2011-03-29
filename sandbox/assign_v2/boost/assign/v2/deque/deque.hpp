//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_DEQUE_DEQUE_ER_2010_HPP
#define BOOST_ASSIGN_V2_DEQUE_DEQUE_ER_2010_HPP
#include <deque>
#include <boost/assign/v2/interpreter/crtp.hpp>
#include <boost/assign/v2/interpreter/data_generator.hpp>
#include <boost/assign/v2/interpreter/modifier.hpp>
#include <boost/assign/v2/interpreter/replace.hpp>
#include <boost/assign/v2/deque/fwd.hpp>
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#include <boost/assign/v2/detail/keyword/nil.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size.hpp>
#include <boost/range/size_type.hpp>
#include <boost/type_traits/remove_cv.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X

namespace boost{
namespace assign{
namespace v2{
//[syntax_deque_deque
namespace interpreter_aux{

    template<typename T>
    struct deque_impl{ 
    	typedef /*<-*/std::deque<T> 
        	BOOST_ASSIGN_V2_IGNORE(/*->*/unspecified /*<-*/)/*->*/
            type; 
    };

    template<typename T, typename F, typename ModifierTag>
    class deque_interpreter 
        : public interpreter_crtp<
            typename deque_impl<T>::type, F, ModifierTag, data_tag::value,
            deque_interpreter<T, F, ModifierTag>
        >
    {
//<-
        typedef typename deque_impl<T>::type impl_;
        typedef impl_ const cimpl_;
        typedef interpreter_crtp<
        	impl_, F, ModifierTag, data_tag::value, deque_interpreter
        > put_crtp_;

        typedef interpreter_aux::interpreter_modifier<ModifierTag> modifier_;
//->
        public:

        typedef T value_type;
        typedef /*<-*/typename boost::range_size<impl_>::type BOOST_ASSIGN_V2_IGNORE(/*->*/unspecified /*<-*/)/*->*/size_type;
        typedef /*<-*/typename boost::range_iterator<impl_>::type BOOST_ASSIGN_V2_IGNORE(/*->*/unspecified /*<-*/)/*->*/iterator;
        typedef /*<-*/typename boost::range_iterator<cimpl_>::type BOOST_ASSIGN_V2_IGNORE(/*->*/unspecified /*<-*/)/*->*/const_iterator;

        // Construct
        deque_interpreter()/*<-*/
            {}BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        explicit deque_interpreter( impl_ const& cont, F const& f, modifier_ const& m )/*<-*/
            : put_crtp_( f, m ), impl( cont )
        {}BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

        // Deque interface
        iterator begin()/*<-*/{
            return boost::begin( this->impl );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        iterator end()/*<-*/{
            return boost::end( this->impl );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        const_iterator begin()const/*<-*/{
            return boost::begin( this->impl );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        const_iterator end()const/*<-*/{
            return boost::end( this->impl );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

        typedef /*<-*/typename impl_::reference BOOST_ASSIGN_V2_IGNORE(/*->*/ unspecified /*<-*/)reference;
        typedef /*<-*/typename impl_::const_reference BOOST_ASSIGN_V2_IGNORE(/*->*/ unspecified /*<-*/)const_reference;
        typedef /*<-*/typename impl_::difference_type BOOST_ASSIGN_V2_IGNORE(/*->*/ unspecified /*<-*/)difference_type;

        size_type size()const/*<-*/{
            return this->container().size();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        size_type max_size()const/*<-*/{
            return this->container().max_size();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        bool empty()const/*<-*/{
            return this->container().empty();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)
        reference operator[](size_type n)/*<-*/{
            return this->container()[n];
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        const_reference operator[](size_type n)const/*<-*/{
            return this->container()[n];
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        reference front()/*<-*/{
            return this->container().front();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        const_reference front()const/*<-*/{
            return this->container().front();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        reference back()/*<-*/{
            return this->container().back();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        const_reference back()const/*<-*/{
            return this->container().back();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        void pop_front()/*<-*/{
            this->container().pop_front();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        void pop_back()/*<-*/{
            this->container().pop_back();
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        void swap(deque_interpreter& that)/*<-*/{
            this->container().swap( that.container() );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

        impl_& container()const/*<-*/{ 
            return this->impl; 
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
//<-
        protected:
        mutable impl_ impl;
//->
    };

    template<typename T, typename F, typename ModifierTag>
    struct replace_data_generator< deque_interpreter<T, F, ModifierTag> >
    {
        template<typename F1>
        struct apply{ typedef /*<-*/BOOST_ASSIGN_V2_IGNORE(/*->*/unspecified/*<-*/)deque_interpreter<T, F1, ModifierTag>/*->*/ type; };
    };

    template<typename T, typename F, typename ModifierTag>
    struct replace_modifier_tag< deque_interpreter<T, F, ModifierTag> >/*<-*/
    {
        template<typename ModifierTag1>
        struct apply{ /*<-*/BOOST_ASSIGN_V2_IGNORE(/*->*/unspecified/*<-*/)typedef deque_interpreter<T, F, ModifierTag1>/*->*/ type; };
    }/*->*/;

//<-
namespace result_of{

    template<typename T>
    struct deque
    {
        typedef typename boost::remove_cv<T>::type t_;
        typedef typename deque_impl<t_>::type impl_;
        typedef typename deduce_data_generator<impl_>::type f_;
        typedef typename deduce_modifier_tag<impl_>::type modifier_tag_;
        typedef deque_interpreter<t_, f_, modifier_tag_> type;
    };

}// result_of
//<-
}// interpreter_aux
//->
namespace interpreter_aux{
//<-

    template<typename T>
    typename result_of::deque<T>::type
    deque( keyword_aux::nil )/*<-*/
    {
        return typename result_of::deque<T>::type();
    }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
    
//<-
}// interpreter_aux
//->
namespace result_of{

    template<typename T>
    struct deque/*<-*/ 
        : interpreter_aux::result_of::deque<T>
    {}/*->*/;

}// result_of
//<-
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
namespace interpreter_aux{
//->

    template<typename T, typename...Args>
    typename result_of::deque<T>::type
    deque(Args&&...args)/*<-*/
    {
        return deque<T>( v2::_nil )( std::forward<Args>(args)... );
    }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

//]
}// interpreter_aux
using interpreter_aux::deque;

#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X
}// v2
}// assign
}// boost

#if !BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <boost/assign/v2/deque/cpp03/deque.hpp>
#endif

#endif // BOOST_ASSIGN_V2_DEQUE_DEQUE_ER_2010_HPP