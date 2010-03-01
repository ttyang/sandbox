//////////////////////////////////////////////////////////////////////////////
// assign::detail::array::policy.hpp                                        //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_AUTO_SIZE_DETAIL_ARRAY_POLICY_ER_2010_HPP
#define BOOST_ASSIGN_AUTO_SIZE_DETAIL_ARRAY_POLICY_ER_2010_HPP
#include <boost/shared_ptr.hpp>
#include <boost/assign/auto_size/array/interface.hpp>
#include <boost/assign/auto_size/array/wrapper.hpp>

namespace boost{
namespace assign{
namespace detail{
namespace auto_size{
 
    template<
    	typename E,typename T,int N,template<typename> class Ref,typename P
    >
    class expr;         

    template<typename T,int N,template<typename> class Ref>
    struct ref_array;
                         
    template<typename A,typename E,typename T,int N,
    	template<typename> class Ref,typename P>
    void write_to_array(A& a,const expr<E,T,N,Ref,P>& e);
                  

   // Policy for auto_size::expr that exposes an array interface
   template<typename T,int N,template<typename> class Ref,typename D>
   	class array_policy 
    	: public array_interface<T,N,Ref,array_policy<T,N,Ref,D> >
    {

        typedef typename ref_array<T,N,Ref>::type ref_array_;
                
        void alloc_if()const{
            if(!this->ptr){
               return this->alloc();
            }
        }

        void alloc()const{ 
            this->ptr = smart_ptr_(new ref_array_);
            write_to_array(*this->ptr,static_cast<const D&>(*this));		
        }
		
        public:

        ref_array_& ref_array_impl(){ 
            this->alloc_if();
            return (*this->ptr);
        }

        const ref_array_& ref_array_impl()const{ 
            this->alloc_if();
            return (*this->ptr);
        }
        
        private:
        typedef boost::shared_ptr<ref_array_> smart_ptr_;
        // Only the last of N expressions needs to instantiate an array, 
        // hence a pointer.
        mutable smart_ptr_ ptr;

    };

}// auto_size  
}// detail      
}// assign
}// boost

#endif
