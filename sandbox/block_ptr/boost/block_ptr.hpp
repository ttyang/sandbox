/**
	@file
	Boost block_ptr.hpp header file.

	@author
	Copyright (c) 2008 Phil Bouchard <phil@fornux.com>.

	@note
	Distributed under the Boost Software License, Version 1.0.

	See accompanying file LICENSE_1_0.txt or copy at
	http://www.boost.org/LICENSE_1_0.txt

	See http://www.boost.org/libs/smart_ptr/doc/index.html for documentation.


	Thanks to: Steven Watanabe <watanabesj@gmail.com>
*/


#ifndef BOOST_DETAIL_BLOCK_PTR_INCLUDED
#define BOOST_DETAIL_BLOCK_PTR_INCLUDED


#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4355 )

#include <new.h>
#endif

#include <iostream>
#include <boost/pool/pool_alloc.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>
#include <boost/thread/thread.hpp>

#include <boost/detail/intrusive_list.hpp>
#include <boost/detail/intrusive_stack.hpp>
#include <boost/detail/roofof.hpp>
#include <boost/detail/block_ptr_base.hpp>


namespace boost
{

namespace detail
{

namespace sh
{


class block_base;


/**
	Set header.
	
	Proxy object used to count the number of pointers from the stack are referencing pointee objects belonging to the same @c block_header .
*/

class block_header
{
    typedef detail::atomic_count count_type;

    count_type count_;								/**< Count of the number of pointers from the stack referencing the same @c block_header .*/
    mutable block_header * redir_;					/**< Redirection in the case of an union multiple sets.*/

    intrusive_list includes_;						/**< List of all sets of an union. */
    intrusive_list elements_;						/**< List of all pointee objects belonging to a @c block_header . */

    static fast_pool_allocator<block_header> pool_;/**< Pool where all sets are allocated. */

public:
#ifndef BOOST_DISABLE_THREADS
	mutex mutex_;
#endif
	bool destroy_;									/**< Destruction sequence initiated. */
    intrusive_list::node tag_;						/**< Tag used to enlist to @c block_header::includes_ . */


	/**
		Initialization of a single @c block_header .
	*/
	
    block_header() : count_(1), redir_(this), destroy_(false)
    {
        includes_.push_back(& tag_);
    }
	
	
	/**
		Release of a @c block_header with possible destruction of all its elements and other sets unified to it.
		
		@return		True if the @c block_header was released.
	*/
	
    bool release()
    {
        block_header * p = redir();

        if (-- p->count_ == 0)
        {
#ifndef BOOST_DISABLE_THREADS
        	mutex::scoped_lock scoped_lock(mutex_);
#endif
			p->destroy_ = true;
            for (intrusive_list::iterator<block_base, & block_base::block_tag_> i; i = p->elements_.begin(), i != p->elements_.end(); )
                delete &* i;
			p->destroy_ = false;
            
            for (intrusive_list::iterator<block_header, & block_header::tag_> i = p->includes_.begin(), j; j = i, i != p->includes_.end(); i = j)
			{ 
				++ j;
                if (&* i != this && &* i != p)
                    delete &* i;
			}
                    
            if (p != this)
                delete p;

            return true;
        }

        return false;
    }

	
	/**
		Recursive search for the @c block_header header of an union.
		
		@return		@c block_header responsible for managing the counter of an union.
	*/
	
    block_header * redir() const
    {
        while (redir_ != redir_->redir_)
        	redir_ = redir_->redir_;
        
        return redir_;
    }
	
	
	/**
		Unification with a new @c block_header .
		
		@param	p	New @c block_header to unify with.
	*/

    void redir(block_header * p)
    {
        if (redir_ != p->redir())
        {
#ifndef BOOST_DISABLE_THREADS
        	mutex::scoped_lock scoped_lock(mutex_);
#endif
            redir_ = p->redir();
            redir_->includes_.merge(includes_);
            redir_->elements_.merge(elements_);
            new (& redir_->count_) count_type(redir_->count_ + count_); /**< Hack */
        }
    }

	
	/**
		Finds the elements constituting one or many sets unified.
		
		@return		List of all elements.
	*/
	
    intrusive_list * elements() const
    {
        return & redir()->elements_;
    }
    
	
	/**
		Allocates a new @c block_header using the fast pool allocator.
		
		@param	s	Size of the @c block_header .
		@return		Pointer of the new memory block.
	*/
	
    void * operator new (size_t s)
    {
        return pool_.allocate(s);
    }
    
	
	/**
		Placement new.
		
		@param	s	Size of the @c block_header .
		@param	p	Address to construct the @c block_header on.
		@return		Address to construct the @c block_header on.
	*/
	
    void * operator new (size_t s, block_header * p)
    {
        return p;
    }

	
	/**
		Deallocates a @c block_header from the fast pool allocator.
		
		@param	p	Address of the @c block_header to deallocate.
	*/
	
    void operator delete (void * p)
    {
        pool_.deallocate(static_cast<block_header *>(p), sizeof(block_header));
    }
};


fast_pool_allocator<block_header> block_header::pool_;


/**
	Deterministic memory manager of constant complexity.
	
	Complete memory management utility on top of standard reference counting.
*/

template <typename T>
    class block_ptr : public block_ptr_base<T>
    {
        template <typename> friend class block_ptr;

        typedef block_ptr_base<T> base;
        
        using base::share;
		using base::po_;

        union
        {
            block_header * ps_;						/**< Pointer to the @c block_header node @c block_ptr<> belongs to. */
            intrusive_stack::node pn_;				/**< Tag used for enlisting a pointer on the heap to later share the @c block_header it belongs to. */
        };

    public:
        typedef T                       value_type;
        typedef block<value_type>     element_type;


		/**
			Initialization of a pointer living on the stack or proper enlistment if living on the heap.
		*/
		
        block_ptr() : ps_(0)
        {
            if (! block_base::pool_.is_from(this))
                ps_ = new block_header();
            else
                block_base::pool_.top(this)->ptrs_.push(& pn_);
        }

		
		/**
			Initialization of a pointer living on the stack or proper enlistment if living on the heap.
			
			@param	p	New pointee object to manage.
		*/
		
        template <typename V>
            block_ptr(block<V> * p) : base(p)
            {
                if (! block_base::pool_.is_from(this))
                {
                    ps_ = new block_header();

                    init(p);
                }
                else
                {
                    block_base::pool_.top(this)->ptrs_.push(& pn_);
                    block_base::pool_.top(this)->inits_.merge(p->inits_);
                }
            }

		
		/**
			Initialization of a pointer living on the stack or proper enlistment if living on the heap.
			
			@param	p	New pointer to manage.
		*/

        template <typename V>
            block_ptr(block_ptr<V> const & p) : base(p)
            {
                if (! block_base::pool_.is_from(this))
                    ps_ = new block_header();
                else
                    block_base::pool_.top(this)->ptrs_.push(& pn_);

                ps_->redir(p.ps_);
            }

		
		/**
			Initialization of a pointer living on the stack or proper enlistment if living on the heap.
			
			@param	p	New pointer to manage.
		*/

			block_ptr(block_ptr<T> const & p) : base(p)
            {
                if (! block_base::pool_.is_from(this))
                    ps_ = new block_header();
                else
                    block_base::pool_.top(this)->ptrs_.push(& pn_);
				
                ps_->redir(p.ps_);
            }


		/**
			Assignment & union of 2 sets if the pointee resides a different @c block_header.
			
			@param	p	New pointee object to manage.
		*/
		
        template <typename V>
            block_ptr & operator = (block<V> * p)
            {
                release(false);

                init(p);

                base::operator = (p);

                return * this;
            }


		/**
			Assignment & union of 2 sets if the pointee resides a different @c block_header.
			
			@param	p	New pointer to manage.
		*/
			
        template <typename V>
            block_ptr & operator = (block_ptr<V> const & p)
            {
                if (ps_->redir() != p.ps_->redir())
                {
                    release(false);
					
                    ps_->redir(p.ps_);
                }
                base::operator = (p);

                return * this;
            }


		/**
			Assignment & union of 2 sets if the pointee resides a different @c block_header.
			
			@param	p	New pointer to manage.
		*/

            block_ptr & operator = (block_ptr<T> const & p)
            {
                return operator = <T>(p);
            }

        void reset()
        {
            release(false);
        }

        ~block_ptr()
        {
			if (ps_->destroy_)
				base::po_ = 0;
			else
				release(true);
        }

    private:
		/**
			Release of the pointee object with or without destroying the entire @c block_header it belongs to.
			
			@param	d	Destroy (true) or reuse (false) the @c block_header it is releasing.
		*/
		
        void release(bool d)
        {
            base::reset();
            
            if (! block_base::pool_.is_from(this))
                if (ps_->release())
                    if (! d)
                        new (ps_) block_header();
                    else
                        delete ps_;
                else 
					if (! d)
                    	ps_ = new block_header();
        }

		
		/**
			Enlist & initialize pointee objects belonging to the same @c block_header .  This initialization occurs when a pointee object is affected to the first pointer living on the stack it encounters.
			
			@param	p	Pointee object to initialize.
		*/
		
        void init(block_base * p)
        {
            if (p->init_)
                return;

			// iterate memory blocks
            for (intrusive_list::iterator<block_base, & block_base::init_tag_> i = p->inits_.begin(); i != p->inits_.end(); ++ i)
            {
                i->init_ = true;
                ps_->elements()->push_back(& i->block_tag_);

				// iterate block_ptr elements
                for (intrusive_stack::iterator<block_ptr, & block_ptr::pn_> j = i->ptrs_.begin(), k; k = j, j != i->ptrs_.end(); j = k)
				{
					++ k;
                    j->ps_ = ps_;
				}
            }
        }
    };


} // namespace sh

} // namespace detail

using detail::sh::block_ptr;
using detail::sh::block;

} // namespace boost


#if defined(_MSC_VER)
#pragma warning( pop )
#endif


#endif // #ifndef BOOST_DETAIL_SH_RTCMM_H_INCLUDED