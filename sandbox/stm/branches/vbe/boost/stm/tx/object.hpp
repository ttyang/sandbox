//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/stm for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_STM_TX_OBJECT__HPP
#define BOOST_STM_TX_OBJECT__HPP

//-----------------------------------------------------------------------------
#include <boost/stm/transaction.hpp>
#include <boost/stm/transaction_object.hpp>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace boost { namespace stm { namespace tx {

//-----------------------------------------------------------------------------
// mixing transactional object class that wraps a object type providing
// a transparent transactional view on a transactional context
// a non-transactional view on a non-transactional context
// Note: the sizeof(object<T>)>>>>=sizeof(T)
//-----------------------------------------------------------------------------
template <typename Final, typename T>
class object : public transaction_object< Final >
{
protected:
    T val_;
public:
    typedef Final final_type;
    typedef T value_type;
    //-----------------------------------------------------------------------------
    object() : val_() {}

    //
    template<typename F, typename U>
    object(object<F,U> const& r) : val_(r.value()) {}

    // contructor from a convertible to T
    template <typename U>
    object(U v) : val_(v) {}
    //object(T v) : val_(v) {}

    #if 0
    template<typename F, typename U>
    object& operator=(object<F, U> const& r) {
        val_=r.value();
    }
    #endif

    operator T() const { return value(); }
    operator T&() { return ref(); }

    T& ref() {
        transaction* tx=current_transaction();
        if (tx!=0) {
            if (tx->forced_to_abort()) {
                tx->lock_and_abort();
                throw aborted_transaction_exception("aborting transaction");
            }

            return tx->write(*this).val_;
        }
        return val_;
    }

    T value() const {
        transaction* tx=current_transaction();
        if (tx!=0) {
            if (tx->forced_to_abort()) {
                tx->lock_and_abort();
                throw aborted_transaction_exception("aborting transaction");
            }
            return tx->read(*this).val_;
        }
        return val_;
    }

};

}}}
#endif


