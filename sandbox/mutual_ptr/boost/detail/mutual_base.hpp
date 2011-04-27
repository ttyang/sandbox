/**
	@file
	Boost detail/sh_mutual_base_nt.hpp header file.

	@note
	Copyright (c) 2008 Phil Bouchard <phil@fornux.com>.

	Distributed under the Boost Software License, Version 1.0.

	See accompanying file LICENSE_1_0.txt or copy at
	http://www.boost.org/LICENSE_1_0.txt

	See http://www.boost.org/libs/smart_ptr/doc/index.html for documentation.
*/


#ifndef BOOST_DETAIL_MUTUAL_BASE_HPP_INCLUDED
#define BOOST_DETAIL_MUTUAL_BASE_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <stack>
#include <limits>

#include <boost/thread.hpp>
#include <boost/thread/tss.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/numeric/interval.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/detail/intrusive_list.hpp>
#include <boost/detail/intrusive_stack.hpp>
#include <boost/detail/roofof.hpp>


namespace boost
{

namespace detail
{

namespace sh
{


class mutual_header;
class mutual_base;


/**
    Allocator wrapper tracking allocations.
	
	Pool where all pointee objects are allocated and tracks memory blocks for later enlisting & marking the @c mutual_header the pointee object belongs to.
*/

struct pool : boost::pool<>
{
	typedef std::list< numeric::interval<long>, fast_pool_allocator< numeric::interval<long> > > pool_lii;	/**< Syntax helper. */

#ifndef BOOST_DISABLE_THREADS
    thread_specific_ptr<pool_lii> plii_;			/**< Thread specific list of memory boundaries. */
#else
    std::auto_ptr<pool_lii> plii_;					/**< List of memory boundaries. */
#endif


	/**
		Initialization of a pool instance.
	*/
	
    pool() : boost::pool<>(1)
    {
        plii_.reset(new pool_lii());
    }
	
	
	/**
		Tracks the memory boundaries where a pointer belongs to.  Also gets rid of the boundaries that were allocated before the pointer was allocated.
		
		@param	p	Pointer that is being tracked.
		@return		Pointer to the pointee object where @c p belongs to.
	*/
	
    mutual_base * top(void * p)
    {
        pool_lii::reverse_iterator i;
        
        for (i = plii_->rbegin(); i != plii_->rend(); i ++)
            if (in((long)(p), * i))
                break;

        plii_->erase(i.base(), plii_->end());
        
        return (mutual_base *)(plii_->rbegin()->lower());
    }
    
	
	/**
		Pointee object allocator and stacking of the newly allocated memory boundary.
		
		@param	s	Size of the memory block to allocate.
		@return		Address of the newly allocated block.
	*/
	
    void * allocate(std::size_t s)
    {
        void * p = ordered_malloc(s);
        
        plii_->push_back(numeric::interval<long>((long) p, long((char *)(p) + s)));
        
        return p;
    }

	
	/**
		Pointee object deallocator and removal of the boundaries that were allocated before the pointer was allocated.
		
		@param	p	Address of the memory block to deallocate.
		@param	s	Size of the memory block.
	*/
	
    void deallocate(void * p, std::size_t s)
    {
        pool_lii::reverse_iterator i;
        
        for (i = plii_->rbegin(); i != plii_->rend(); i ++)
            if (in((long)(p), * i))
                break;

        plii_->erase(i.base(), plii_->end());
        ordered_free(p, s);
    }
};


/**
	Root class of all pointee objects.
*/

class mutual_base : public sp_counted_base
{
public:
    bool init_;										/**< Flag marking initialization of the pointee object to its @c mutual_header . */

	intrusive_stack ptrs_;							/**< Stack of all @c mutual_ptr s on the heap that will later need to be initlialized to a specific @c mutual_header . */
	intrusive_list inits_;							/**< List of all pointee objects that will later need to be initlialized to a specific @c mutual_header .*/

    intrusive_list::node mutual_tag_;					/**< Tag used to enlist to @c mutual_header::elements_ . */
    intrusive_list::node init_tag_;					/**< Tag used to enlist to @c mutual_base::inits_ . */


    mutual_base() : init_(false)
    {
        inits_.push_back(& init_tag_); 
    }

    static pool pool_;								/**< Pool where all pointee objects are allocated from. */

protected:
    virtual void dispose() 				                    {} 				/**< dumutualy */
    virtual void * get_deleter( std::type_info const & ti ) { return 0; } 	/**< dumutualy */
};


pool mutual_base::pool_;


#define TEMPLATE_DECL(z, n, text) BOOST_PP_COMMA_IF(n) typename T ## n
#define ARGUMENT_DECL(z, n, text) BOOST_PP_COMMA_IF(n) T ## n const & t ## n
#define PARAMETER_DECL(z, n, text) BOOST_PP_COMMA_IF(n) t ## n

#define CONSTRUCT_OWNED(z, n, text)																			    \
	template <BOOST_PP_REPEAT(n, TEMPLATE_DECL, 0)>										                        \
		text(BOOST_PP_REPEAT(n, ARGUMENT_DECL, 0)) : elem_(BOOST_PP_REPEAT(n, PARAMETER_DECL, 0)) {}																										

/**
	Object wrapper.
*/

template <typename T>
    class mutual : public mutual_base
    {
        typedef T data_type;

        T elem_; 									/**< Pointee object.  @note Needs alignas<long>. */
        
    public:
        class roofof;
        friend class roofof;

		mutual() : elem_() 
        {
        }

        BOOST_PP_REPEAT_FROM_TO(1, 10, CONSTRUCT_OWNED, mutual)


		/**
			@return		Pointee object address.
		*/
		
        data_type * element() 				{ return & elem_; }
        operator data_type & ()             { return * element(); }
        operator data_type const & () const { return * element(); }

        virtual ~mutual()					
        { 
            dispose(); 
        }

    public:
		/**
			Cast operator used by @c mutual_ptr_comutualon::header() .
		*/
		
        class roofof
        {
            mutual * p_;							/**< Address of the @c mutual the element belong to. */

        public:
			/**
				Casts from a @c data_type to its parent @c mutual object.
				
				@param	p	Address of a @c data_type member object to cast from.
			*/
			
            roofof(data_type * p) : p_(sh::roofof((data_type mutual::*)(& mutual::elem_), p)) {}
            
			
			/**
				@return		Address of the parent @c mutual object.
			*/
			
            operator mutual * () const { return p_; }
        };

        
		/**
			Allocates a new @c mutual using the pool.
			
			@param	s	Size of the @c mutual .
			@return		Pointer of the new memory block.
		*/
		
        void * operator new (size_t s)
        {
            return pool_.allocate(s);
        }
        

		/**
			Deallocates a @c mutual from the pool.
			
			@param	p	Address of the @c mutual to deallocate.
		*/
		
        void operator delete (void * p)
        {
            pool_.deallocate(p, sizeof(mutual));
        }
    };


template <>
    class mutual<void> : public mutual_base
    {
        typedef void data_type;

        long elem_; 									/**< Pointee placeholder.  @note Aligned. */

        mutual();

    public:
        class roofof;
        friend class roofof;

        data_type * element() 				{ return & elem_; }

        virtual ~mutual()					{}
        virtual void dispose() 				{}

        virtual void * get_deleter( std::type_info const & ti ) {}

    public:
		/**
			Cast operator used by @c mutual_ptr_comutualon::header() .
		*/
		
        class roofof
        {
            mutual * p_;							/**< Address of the @c mutual the element belong to. */

        public:
			/**
				Casts from a @c data_type to its parent @c mutual object.
				
				@param	p	Address of a @c data_type member object to cast from.
			*/
			
            roofof(data_type * p) : p_(sh::roofof((long mutual::*)(& mutual::elem_), static_cast<long *>(p))) {}
            
			
			/**
				@return		Address of the parent @c mutual object.
			*/
			
            operator mutual * () const { return p_; }
        };
    };


} // namespace sh

} // namespace detail

} // namespace boost


#endif  // #ifndef BOOST_DETAIL_SH_OWNED_BASE_NT_HPP_INCLUDED