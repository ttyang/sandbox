//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_OPTION_REPEAT_ER_2010_HPP
#define BOOST_ASSIGN_V2_OPTION_REPEAT_ER_2010_HPP
#include <cstddef>
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_reference.hpp>
#endif
#include <boost/assign/v2/interpreter/fwd.hpp>
#include <boost/assign/v2/option/modifier.hpp>

namespace boost{
namespace assign{
namespace v2{
//[syntax_option_repeat
namespace modifier_tag{ 

    template<typename Tag> struct repeat/*<-*/{}/*->*/; 

}// modifier_tag
namespace aux{

    template<typename Arg>
    class adapter_modifier<modifier_tag::repeat<Arg> >/*<-*/
    {
        typedef adapter_modifier<Arg> inner_type;

        public:

        typedef std::size_t size_type;

        adapter_modifier() : n_( 0 ){}
        explicit adapter_modifier( inner_type inner, size_type n )
            : inner_( inner ), n_( n )
        {}

#if BOOST_ASSIGN_V2_ENABLE_CPP0X
        template<typename C, typename T>
            typename boost::disable_if<
            boost::is_reference<T>,
            void
        >::type
        impl(C& cont, T&& t )const
        {
            size_type m = this->size();\
            while(m--) this->inner_.impl( cont, std::forward<T>( t ) );
        }

#endif

        template<typename C, typename T>
        void impl(C& cont, T& t )const
        {
            size_type m = this->size();
            while(m--) this->inner_.impl( cont, t );
        }

        template<typename C, typename T>
        void impl(C& cont, T* t)const
        {
            size_type m = this->size();
            while(m--) this->inner_.impl( cont, t );
        }

        size_type const& size()const{ return this->n_; }

        protected:
        inner_type inner_;
        size_type n_;
    }/*->*/;

}// aux
BOOST_ASSIGN_V2_OPTION_MODIFIER_KEYWORD(repeat)
BOOST_ASSIGN_V2_OPTION_MODIFIER_META_MODIFIER_TAG(repeat, modifier_tag::repeat<typename D::modifier_tag>)
//]
}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_OPTION_REPEAT_ER_2010_HPP