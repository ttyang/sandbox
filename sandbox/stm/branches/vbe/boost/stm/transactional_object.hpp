//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_STM_TRANSACTIONAL_OBJECT__HPP
#define BOOST_STM_TRANSACTIONAL_OBJECT__HPP

#include <boost/stm/base_transaction.hpp>

//-----------------------------------------------------------------------------
namespace boost { namespace stm {

//-----------------------------------------------------------------------------
// transactional object wrapper
// A transactional_object<T> is a base_transaction_object wrapping an instance of type T
// Provides the definition of the virtual functions
//      forward constructors to the wrapped type
//      copy_state: relaying on the cache_copy<T> generic function
//      move_state and
//      cache_deallocate: relaying on the cache_copy<T> generic function
// Defines in addition the functions new and delete when USE_STM_MEMORY_MANAGER is defined
//
// If a class D inherits from B we have that transactional_object<D> dont inherits from transactional_object<B>, but
// we can static/dynamic cast them robustly.
// Evidently the std::static_cast/std::dynamic_cast do not works. We need to define the specific cast
//
// transactional_object<D>* d=...;
// transactional_object<B>* b=tx_static_cast<B>(d);
//
// transactional_object<B>* b=...;
// transactional_object<D>* d=tx_dynamic_cast<B>(b);
//
//-----------------------------------------------------------------------------

template <typename T>
class transactional_object : public base_transaction_object {
public:
    T value;

    transactional_object() {}
    transactional_object(const T*ptr)
        : base_transaction_object()
        , value(*ptr) {}

    transactional_object(transactional_object<T> const & r)
        : base_transaction_object(r)
        , value(r.value) {}

    template <typename T1>
    transactional_object(T1 const &p1)
        : base_transaction_object()
        , value(p1) {}

    template <typename T1, typename T2>
    transactional_object(T1 const &p1, T2 const &p2)
        : base_transaction_object()
        , value(p1,p2) {}

    transactional_object & operator=(transactional_object const & r)  // =default never throws
    {
        value = r.value;
        return *this;
    }

    virtual base_transaction_object* clone() const {
        return cache_clone(*this);
    }

    virtual void copy_state(base_transaction_object const * const rhs) {
        cache_copy(static_cast<transactional_object<T> const * const>(rhs),
                      //static_cast<transactional_object<T> *>(this));
                      this);
    }

#ifdef BOOST_STM_USE_MEMCOPY
    virtual void cache_deallocate() {
        boost::stm::cache_deallocate(this);
    }
#endif

#if USE_STM_MEMORY_MANAGER
   void* operator new(size_t size) throw ()
   {
      return retrieve_mem(size);
   }

   void operator delete(void* mem)
   {
      return_mem(mem, sizeof(transactional_object<T>));
   }
#endif

};

//-----------------------------------------------------------------------------
// gets the transactional_object<T> pointer wrapping the T pointer
//-----------------------------------------------------------------------------
template <typename T>
static transactional_object<T>* tx_up_cast(T* ptr) {
    return reinterpret_cast<transactional_object<T>*>(reinterpret_cast<char*>(ptr)-offsetof(transactional_object<T>, value));
}

//-----------------------------------------------------------------------------
// static_cast two transactional_object's
//-----------------------------------------------------------------------------
template <typename T, typename U>
static transactional_object<T>* tx_static_cast(transactional_object<U>* ptr) {
    return tx_up_cast(static_cast<T*>(&ptr->value));
}

//-----------------------------------------------------------------------------
// dynamic_cast two transactional_object's
//-----------------------------------------------------------------------------
template <typename T, typename U>
static transactional_object<T>* tx_dynamic_cast(transactional_object<U>* ptr) {
    T* p = dynamic_cast<T*>(&ptr->value);
    if (p==0) return 0;
    return tx_up_cast(p);
}



#ifdef BOOST_STM_USE_MEMCOPY
#ifdef BOOST_STM_NO_PARTIAL_SPECIALIZATION
namespace partial_specialization_workaround {

template <class T, class A>
struct cache_clone<transactional_object<std::vector<T,A> > > {
    static inline transactional_object<std::vector<T,A> >* apply(const transactional_object<std::vector<T,A> >& val) {
        return new transactional_object<std::vector<T,A> >(val);
    }
};
} // partial_specialization_workaround

#else //BOOST_STM_NO_PARTIAL_SPECIALIZATION

template <class T>
inline transactional_object<std::vector<T> >* cache_clone(const transactional_object<std::vector<T> >& val) {
    return new transactional_object<std::vector<T> >(val);
}

#endif // BOOST_STM_NO_PARTIAL_SPECIALIZATION
#endif



#ifdef BOOST_STM_USE_MEMCOPY
#ifdef BOOST_STM_NO_PARTIAL_SPECIALIZATION
namespace partial_specialization_workaround {

template <class T>
struct cache_copy<transactional_object<std::vector<T> > > {
    static inline void apply(const transactional_object<std::vector<T> >* const ori, transactional_object<std::vector<T> >* target) {
        *target=*ori;
    }
};

} // partial_specialization_workaround
#else
template <class T> void cache_copy(const transactional_object<std::vector<T> >* const ori, transactional_object<std::vector<T> >* target) {
    *target=*ori;
}
#endif
#endif


#ifdef BOOST_STM_USE_MEMCOPY
#ifdef BOOST_STM_NO_PARTIAL_SPECIALIZATION
namespace partial_specialization_workaround {

template <class T>
struct cache_deallocate<transactional_object<std::vector<T> > > {
    static void apply(transactional_object<std::vector<T> >* ptr) {
        delete ptr;
    }
};

}

#else //!BOOST_STM_NO_PARTIAL_SPECIALIZATION

template <class T>
inline void cache_deallocate(transactional_object<std::vector<T> >* ptr) {
    delete ptr;
}

#endif //BOOST_STM_NO_PARTIAL_SPECIALIZATION
#endif // BOOST_STM_USE_MEMCOPY


} // namespace core
}
#endif // BASE_TRANSACTION_H


