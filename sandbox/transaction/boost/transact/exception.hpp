//          Copyright Stefan Strasser 2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_TRANSACT_EXCEPTION_HEADER_HPP
#define BOOST_TRANSACT_EXCEPTION_HEADER_HPP

#include <exception>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/assert.hpp>


namespace boost{
namespace transact{

///\brief Exception base class.
struct exception : std::exception{};

///\brief Indicates that a persistent resource recovery failed.
struct recovery_failure : transact::exception{};

///\brief Indicates that an internal operation reading from/writing to files failed.
struct io_failure : transact::exception{};

///\brief Indicates that this operation required a transaction but there was no transaction bound to this thread, or that the operation
///required an active transaction but the transaction bound to this thread was inactive.
struct no_transaction : transact::exception{};

///\brief Indicates an error with regard to connecting a resource to a transaction manager
struct resource_error : transact::exception{};

///\brief Indicates that no transaction manager was constructed.
struct no_transaction_manager : transact::exception{};

///\brief Indicates that this operation is not supported by this implementation
struct unsupported_operation : transact::exception{};

struct isolation_exception;
template<class ResMgr>
struct resource_isolation_exception;

namespace detail{

//this used so that resource managers can throw isolation exceptions
//without knowing the type of the transaction manager. as a result,
//the type of the transaction manager is only known to isolation_exception::unwind(),
//which makes it a function template, i.e. not a virtual function. to still be able to call
//the correct unwind() function of the derived class the resource managers are iterated.

template<class TxMgr,class Iterator>
struct isolation_unwind_visitor{
    void operator()(isolation_exception const &iso){
        typedef typename mpl::deref<Iterator>::type resource_type;
        if(resource_isolation_exception<resource_type> const *viso=dynamic_cast<resource_isolation_exception<resource_type> const *>(&iso)){
            viso->template unwind<TxMgr>();
        }else{
            isolation_unwind_visitor<TxMgr,typename mpl::next<Iterator>::type> visit;
            visit(iso);
        }
    }
};

template<class TxMgr>
struct isolation_unwind_visitor<TxMgr,typename mpl::end<typename TxMgr::resource_types>::type>{
    void operator()(isolation_exception const &){
        BOOST_ASSERT(false);
    }
};

}

///\brief Indicates that the operation conflicted with another transaction.
///
///\c isolation_exception is an abstract base class. The derived class
///\c resource_isolation_exception can be used to throw this exception.
struct isolation_exception : transact::exception{
    ///Rethrows the exception if the current transaction is a nested transaction but the isolation exception was caused by a parent transaction of it,
    ///or if the isolation_exception was caused independently of a transaction.
    ///\pre TxMgr::current_transaction() must be a rolled back transaction
    template<class TxMgr>
    void unwind() const{ //pseudo-virtual
        detail::isolation_unwind_visitor<TxMgr,typename mpl::begin<typename TxMgr::resource_types>::type> visit;
        visit(*this);
    }
protected:
    isolation_exception(){}
};


///\brief Indicates that the operation conflicted with another transaction.
///
///The base class \c isolation_exception should be used to catch this exception,
///in order to catch isolation exceptions of all resource managers.
template<class ResMgr>
struct resource_isolation_exception : isolation_exception{
    ///\brief Constructs a resource_isolation_exception
    resource_isolation_exception() : retry(0){}

    ///\brief Constructs a resource_isolation_exception
    ///\param retry The transaction that caused the isolation_exception and ought to be repeated.
    ///Must be a transaction on the nested transaction stack.
    explicit resource_isolation_exception(typename ResMgr::transaction &retry)
        : retry(&retry){}

    ///Throws: thread_resource_error. no_transaction if \c retry was not on the nested transaction stack or it was removed before unwind() was called.
    ///\brief Equivalent to <tt>isolation_exception::unwind<TxMgr>()</tt>
    ///\pre TxMgr::current_transaction() must be a rolled back transaction
    template<class TxMgr>
    void unwind() const{ //pseudo-virtual
        if(this->retry){
            typename ResMgr::transaction &currenttx=TxMgr::resource_transaction(TxMgr::current_transaction(),typename ResMgr::tag());
            if(this->retry != &currenttx) throw;
        }else throw;
    }
private:
    typename ResMgr::transaction *retry;
};

}
}



#endif
