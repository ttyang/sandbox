//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_OPTION_MODIFIER_REPEAT_ER_2010_HPP
#define BOOST_ASSIGN_V2_OPTION_MODIFIER_REPEAT_ER_2010_HPP
#include <cstddef>
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#include <boost/assign/v2/detail/traits/container.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_reference.hpp>
#endif
#include <boost/assign/v2/interpreter/fwd.hpp>
#include <boost/assign/v2/option/modifier/framework.hpp>

namespace boost{
namespace assign{
namespace v2{
//[syntax_option_repeat
namespace modifier_tag{ 

    template<typename Tag> struct repeat/*<-*/{}/*->*/; 

}// modifier_tag
namespace interpreter_aux{

    template<typename Arg>
    class interpreter_modifier<modifier_tag::repeat<Arg> >/*<-*/
    {
        typedef interpreter_modifier<Arg> inner_type;

        public:

        typedef std::size_t size_type;

        interpreter_modifier() : n_( 0 ){}
        explicit interpreter_modifier( inner_type inner, size_type n )
            : inner_( inner ), n_( n )
        {}

#if BOOST_ASSIGN_V2_ENABLE_CPP0X
        template<typename C, typename T, typename DataTag>
        void impl(C& cont, T&& t, DataTag tag )const
        {
            size_type m = this->size();\
            while(m--) this->inner_.impl( cont, std::forward<T>( t ), tag );
        }

#else

        template<typename C, typename T, typename DataTag>
        void impl(C& cont, T& t, DataTag tag )const
        {
            size_type m = this->size();
            while(m--) this->inner_.impl( cont, t, tag );
        }

#endif

        size_type const& size()const{ return this->n_; }

        protected:
        inner_type inner_;
        size_type n_;
    }/*->*/;

}// interpreter_aux
BOOST_ASSIGN_V2_OPTION_MODIFIER_KEYWORD(repeat)
BOOST_ASSIGN_V2_OPTION_MODIFIER_META_MODIFIER_TAG(repeat, modifier_tag::repeat<typename D::modifier_tag>)
//]
}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_OPTION_MODIFIER_REPEAT_ER_2010_HPP
