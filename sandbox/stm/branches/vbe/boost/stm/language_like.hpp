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

#ifndef BOOST_STM_LANGUAGE_LIKE__HPP
#define BOOST_STM_LANGUAGE_LIKE__HPP

//-----------------------------------------------------------------------------
#include <boost/stm/detail/config.hpp>
//-----------------------------------------------------------------------------
#include <boost/stm/transaction.hpp>
#include <cstring>
#include <iostream>

//---------------------------------------------------------------------------
// helper function to implement macros
namespace boost { namespace stm { namespace detail {

enum control_flow {
    none,
    break_,
    continue_
};

struct commit_on_destruction {
    transaction* tx_;
    bool &stop_;
    bool &exception_catched_;
    bool commited_;
    commit_on_destruction(transaction& tx, bool &stop, bool& exception_catched)
    : tx_(&tx), stop_(stop), exception_catched_(exception_catched), commited_(false) {}

    ~commit_on_destruction() {
        if (tx_!=0) {
            if(!commited_) {
                try {
                    tx_->commit();
                } catch (...) {
                    exception_catched_=true;
                }
            }
            stop_ = tx_->committed();
        };
    }

    void commit() {
        if (tx_!=0&&!commited_) {
            tx_->commit();
            commited_=true;
        }
    }
    void release() {
        tx_=0;
    }
};

bool no_opt_false() {return false;}

template <typename TX, typename T> T commit_and_return(TX &t, T const& var) {
    T tmp(var); 
    t.commit(); 
    return tmp;
}

template <typename TX> 
bool commit_expr(TX &t) {
    t.commit(); return true;
}

int get_int(const char* s) {
    return 1+strlen(s);
}

void commit(std::nothrow_t, transaction&t)
{
    try { t.commit(); }
    catch (...) {}
}

struct dummy_exception{};
}}}


//---------------------------------------------------------------------------
// Transaction control constructs
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// do not remove if (). It is necessary a necessary fix for compilers
// that do not destroy index variables of for loops. In addition, the
// rand()+1 check is necessarily complex so smart compilers can't
// optimize the if away
//---------------------------------------------------------------------------

#ifdef BOOST_STM_COMPILER_DONT_DESTROY_FOR_VARIABLES
#define BOOST_STM_COMPILER_DONT_DESTROY_FOR_VARIABLES_WORKAROUND if (0==rnd()+1) {} else
#else
#define BOOST_STM_COMPILER_DONT_DESTROY_FOR_VARIABLES_WORKAROUND
#endif

//---------------------------------------------------------------------------

#define BOOST_STM_LABEL_CONTINUE(TX) BOOST_JOIN(__boost_stm_continue_, TX)
#define BOOST_STM_LABEL_BREAK(TX) BOOST_JOIN(__boost_stm_break_, TX)
#define BOOST_STM_LABEL_TRICK(TX) BOOST_JOIN(__boost_stm_trick_, TX)
#define BOOST_STM_VAR_DESTR(TX) BOOST_JOIN(__boost_stm_destr_, TX)
#define BOOST_STM_VAR_STOP __boost_stm_stop_

#define BOOST_STM_MANAGE_BREAK_CONTINUE(TX)                                 \
    if (bool BOOST_STM_VAR_STOP = boost::stm::detail::no_opt_false()) {     \
        BOOST_STM_LABEL_CONTINUE(TX):                                       \
            continue;                                                       \
        BOOST_STM_LABEL_BREAK(TX):                                          \
            break;                                                          \
        BOOST_STM_LABEL_TRICK(TX):                                          \
            if(boost::stm::detail::get_int(#TX)%3==0) goto BOOST_STM_LABEL_CONTINUE(TX);                  \
            if(boost::stm::detail::get_int(#TX)%3==1) goto BOOST_STM_LABEL_BREAK(TX);                     \
            if(boost::stm::detail::get_int(#TX)%3==2) goto BOOST_STM_LABEL_TRICK(TX);                     \
    } else

//---------------------------------------------------------------------------
// Usage
// BOOST_STM_OUTER_TRANSACTION(_) {
// ...
//   BOOST_STM_INNER_TRANSACTION(_) {
//      transactional block
//   }
// ...
// } BOOST_STM_RETRY    // or BOOST_STM_CACHE_BEFORE_RETRY(E)
//                      // or BOOST_STM_BEFORE_RETRY
//---------------------------------------------------------------------------

#define BOOST_STM_INNER_TRANSACTION(TX)                                \
    if (bool BOOST_STM_VAR_STOP = boost::stm::detail::no_opt_false()) {} else   \
    for (boost::stm::transaction TX;                            \
            !   BOOST_STM_VAR_STOP;                                  \
        BOOST_STM_VAR_STOP=true, TX.end())

#define BOOST_STM_INNER_TRANSACTION_IN_LOOP(TX)                        \
    BOOST_STM_MANAGE_BREAK_CONTINUE(TX)                         \
    for (boost::stm::transaction TX;                            \
            !   BOOST_STM_VAR_STOP;                                  \
        BOOST_STM_VAR_STOP=true, TX.end())


#define BOOST_STM_USE_ATOMIC(TX) BOOST_STM_INNER_TRANSACTION(TX)
#define BOOST_STM_USE_ATOMIC_IN_LOOP(TX) BOOST_STM_INNER_TRANSACTION_IN_LOOP(TX)

//---------------------------------------------------------------------------
// Usage
// BOOST_STM_OUTER_TRANSACTION(_) {
//   transactional block
// } BOOST_STM_RETRY    // or BOOST_STM_CACHE_BEFORE_RETRY(E)
//                      // or BOOST_STM_BEFORE_RETRY
//---------------------------------------------------------------------------

#define BOOST_STM_OUTER_TRANSACTION(TX)                                \
    BOOST_STM_COMPILER_DONT_DESTROY_FOR_VARIABLES_WORKAROUND    \
    for (boost::stm::transaction TX;                            \
            !   TX.committed()                                  \
            &&  TX.restart();                                   \
        TX.no_throw_end()) try

#define BOOST_STM_OUTER_TRANSACTION_IN_LOOP(TX)                                \
    BOOST_STM_MANAGE_BREAK_CONTINUE(TX)                         \
    for (boost::stm::transaction TX;                            \
            !   TX.committed()                                  \
            &&  TX.restart();                                   \
        BOOST_STM_VAR_STOP=true, TX.no_throw_end()) try

#define BOOST_STM_TRY_ATOMIC(TX) BOOST_STM_TRY_TRANSACTION(TX)
#define BOOST_STM_TRY_ATOMIC_IN_LOOP(TX) BOOST_STM_TRY_TRANSACTION_IN_LOOP(TX)

//---------------------------------------------------------------------------
// Usage
// BOOST_STM_TRANSACTION(_) {
//   transactional block
// } BOOST_STM_RETRY    // or BOOST_STM_CACHE_BEFORE_RETRY(E)
//                      // or BOOST_STM_BEFORE_RETRY
//---------------------------------------------------------------------------

#define BOOST_STM_TRANSACTION(TX)                                    \
    BOOST_STM_COMPILER_DONT_DESTROY_FOR_VARIABLES_WORKAROUND    \
    for (boost::stm::transaction TX;                            \
            !   TX.committed()                                  \
            &&  TX.check_throw_before_restart()                 \
            &&  TX.restart_if_not_inflight();                   \
        TX.no_throw_end()) try

#define BOOST_STM_TRANSACTION_IN_LOOP(TX)                            \
    BOOST_STM_MANAGE_BREAK_CONTINUE(TX)                         \
    for (boost::stm::transaction TX;                            \
            !   TX.committed()                                  \
            &&  TX.check_throw_before_restart()                 \
            &&  TX.restart_if_not_inflight();                   \
        BOOST_STM_VAR_STOP=true, TX.no_throw_end()) try


#define BOOST_STM_ATOMIC(TX) BOOST_STM_TRANSACTION(TX)
#define BOOST_STM_ATOMIC_IN_LOOP(TX) BOOST_STM_TRANSACTION_IN_LOOP(TX)

//---------------------------------------------------------------------------
// Usage
// BOOST_STM_B_TRANSACTION(_) {
//   transactional block
// } BOOST_STM_RETRY_END    // or BOOST_STM_CACHE_BEFORE_RETRY(E)
//                      // or BOOST_STM_BEFORE_RETRY
//---------------------------------------------------------------------------

#define BOOST_STM_B_TRANSACTION(TX)                                             \
if (bool BOOST_STM_VAR_STOP = boost::stm::detail::no_opt_false()) {} else       \
{                                                                               \
    boost::stm::detail::control_flow ctrl;                                      \
    do {                                                                        \
        boost::stm::transaction TX;                                                 \
        try{                                                                    \
            bool exception_catched=false;\
            {\
                boost::stm::detail::commit_on_destruction BOOST_STM_VAR_DESTR(TX)(TX, BOOST_STM_VAR_STOP, exception_catched); \
                try{                                                                \
                    {                                                               \
                        try {

//~ ctrl: states if a specific control flow must be done
//~ TX: the transaction     
//~ exception_catched: variable
// abort on destruction if active
// allow the user to compose exception handlers after his/her code
// avoid the commit on destruction when an exception is thrown

#define BOOST_STM_B_TRANSACTION_IN_LOOP(TX)                                     \
if (bool BOOST_STM_VAR_STOP = boost::stm::detail::no_opt_false()) {} else       \
{                                                                               \
    boost::stm::detail::control_flow ctrl;                                      \
    do {                                                                        \
        boost::stm::transaction TX;                                             \
        try {                                                                   \
            bool exception_catched=false;                                       \
            {                                                                   \
                boost::stm::detail::commit_on_destruction BOOST_STM_VAR_DESTR(TX)(TX, BOOST_STM_VAR_STOP, exception_catched); \
                try {                                                           \
                    for (ctrl=boost::stm::detail::break_;                       \
                        ctrl==boost::stm::detail::break_;                       \
                        ctrl=boost::stm::detail::continue_)                     \
                    {                                                           \
                        try {

                        // user code here

#define BOOST_STM_E_RETRY(TX)                                                       \
                        } catch(boost::stm::detail::dummy_exception &ex) { throw; } \
                        ctrl=boost::stm::detail::none;                              \
                    }                                                               \
                    BOOST_STM_VAR_DESTR(TX).commit();                               \
                } catch(...) {                                                      \
                    BOOST_STM_VAR_DESTR(TX).release();                              \
                    throw;                                                          \
                }                                                                   \
            }                                                                       \
            if (exception_catched) {                                                \
                throw boost::stm::aborted_tx("commit throw");                       \
            }                                                                       \
            break;                                                                  \
        } catch (boost::stm::aborted_tx &) {                                        \
            if (TX.is_nested()) throw;                                              \
            TX.restart();            


#define BOOST_STM_E_BEFORE_RETRY(TX)                                                \
                        } catch(boost::stm::detail::dummy_exception &ex) { throw; } \
                        ctrl=boost::stm::detail::none;                              \
                    }                                                               \
                    BOOST_STM_VAR_DESTR(TX).commit();                               \
                } catch(...) {                                                      \
                    BOOST_STM_VAR_DESTR(TX).release();                              \
                    throw;                                                          \
                }                                                                   \
            }                                                                       \
            if (exception_catched) {                                                \
                throw boost::stm::aborted_tx("commit throw");                       \
            }                                                                       \
            break;                                                                  \
        } catch (boost::stm::aborted_tx &) {                                        \
            if (TX.is_nested()) throw;                                              \
            TX.restart();                                                                          


#define BOOST_STM_E_END(TX)                                                     \
        }                                                                       \
    } while(!BOOST_STM_VAR_STOP);                                               \
}

#define BOOST_STM_RETRY_END(TX)                                                 \
 BOOST_STM_E_RETRY(TX) {}                                                       \
 BOOST_STM_E_END(TX)


#define BOOST_STM_E_END_IN_LOOP(TX)                                             \
        }                                                                       \
    } while(!BOOST_STM_VAR_STOP);                                               \
    if (ctrl==boost::stm::detail::continue_) continue;                          \
    else if (ctrl==boost::stm::detail::break_) break;                           \
    else ;                                                                      \
}

#define BOOST_STM_RETRY_END_IN_LOOP(TX)                                         \
 BOOST_STM_E_RETRY(TX) {}                                                       \
 BOOST_STM_E_END_IN_LOOP(TX)


#define BOOST_STM_E_RETURN(TX, EXPRESSION) \
    return boost::stm::detail::commit_and_return(BOOST_STM_VAR_DESTR(TX), EXPRESSION)

#define BOOST_STM_E_RETURN_NOTHING(TX) \
    if (!boost::stm::detail::commit_expr(BOOST_STM_VAR_DESTR(TX)));else return

//---------------------------------------------------------------------------
// Catch a named abort exception leting the user to do somethink before retry
//---------------------------------------------------------------------------
#define BOOST_STM_CACHE_BEFORE_RETRY(E) catch (boost::stm::aborted_tx &E)

//---------------------------------------------------------------------------
// Catch a unnamed abort exception leting the user to do somethink before retry
//---------------------------------------------------------------------------
#define BOOST_STM_BEFORE_RETRY catch (boost::stm::aborted_tx &)

//---------------------------------------------------------------------------
// Catch a unnamed abort exception and retry
//---------------------------------------------------------------------------
#define BOOST_STM_RETRY catch (boost::stm::aborted_tx &) {}
#define BOOST_STM_END_ATOMIC BOOST_STM_RETRY

//---------------------------------------------------------------------------
// Catch a named exception and re-throw it after commiting
//---------------------------------------------------------------------------
#define BOOST_STM_RETHROW(TX, E) catch (E&) {boost::stm::detail::commit_expr(TX); throw;}

//---------------------------------------------------------------------------
// Catch any exception and re-throw it after commiting
//---------------------------------------------------------------------------
#define BOOST_STM_RETHROW_ANY(TX) catch (...) {boost::stm::detail::commit_expr(TX); throw;}

//---------------------------------------------------------------------------
// Catch a named exception and abort the transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_TX_ABORT_ON_EXCEPTION(TX, E) \
    catch (E&) {(TX).force_to_abort();}
//---------------------------------------------------------------------------
// Catch any exception and abort the transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_TX_ABORT_ON_ANY_EXCEPTION(TX) \
    catch (...) {(TX).force_to_abort();}

//---------------------------------------------------------------------------
// return the expression EXPRESSION from inside a transaction TX
//---------------------------------------------------------------------------
#define BOOST_STM_TX_RETURN(TX, EXPRESSION) \
    return boost::stm::detail::commit_and_return(TX, EXPRESSION)

#define BOOST_STM_TX_RETURN_NOTHING(TX) \
    if (!boost::stm::detail::commit_expr(TX));else return

//---------------------------------------------------------------------------
// return the expression EXPRESSION from inside a transaction TX
//---------------------------------------------------------------------------
#define BOOST_STM_RETURN(EXPRESSION) \
    if (boost::stm::current_transaction()==0) return EXPRESSION;  \
    else BOOST_STM_TX_RETURN(*boost::stm::current_transaction(), EXPRESSION)

//---------------------------------------------------------------------------
// break: exit from the transaction block associate to TX successfully
//---------------------------------------------------------------------------

#define BOOST_STM_BREAK(TX)    \
    if (!boost::stm::detail::commit_expr(TX));else goto BOOST_STM_LABEL_BREAK(TX)


//---------------------------------------------------------------------------
// continue: exit from the transaction block associate to TX successfully
//---------------------------------------------------------------------------
#define BOOST_STM_CONTINUE(TX)    \
    if (!boost::stm::detail::commit_expr(TX));else goto BOOST_STM_LABEL_CONTINUE(TX)

//---------------------------------------------------------------------------
// goto : exit from the transaction block associate to T successfully jumping to the named label LABEL
// Note that label must be outside the transaction block.
//---------------------------------------------------------------------------
#define BOOST_STM_TX_GOTO(TX, LABEL) \
    if (!boost::stm::detail::commit_expr(TX));else goto LABEL

#define BOOST_STM_GOTO(LABEL) \
    if (boost::stm::current_transaction()==0) goto LABEL;  \
    else BOOST_STM_TX_GOTO(*boost::stm::current_transaction(), LABEL)

//---------------------------------------------------------------------------
// aborts the transaction TX
//---------------------------------------------------------------------------
#define BOOST_STM_TX_ABORT(TX) (TX).force_to_abort()

//---------------------------------------------------------------------------
// aborts the current transaction
//---------------------------------------------------------------------------
#define BOOST_STM_ABORT     \
    if (boost::stm::current_transaction()==0) ;  \
    else BOOST_STM_TX_ABORT(*boost::stm::current_transaction())

//---------------------------------------------------------------------------
// aborts the transaction TX
//---------------------------------------------------------------------------
#define BOOST_STM_TX_ABORT_OUTER(TX) (TX).force_to_abort()

//---------------------------------------------------------------------------
// aborts the current transaction
//---------------------------------------------------------------------------
#define BOOST_STM_ABORT_OUTER     \
    if (boost::stm::current_transaction()==0) ;  \
    else BOOST_STM_TX_ABORT_OUTER(*boost::stm::current_transaction())


//---------------------------------------------------------------------------
// throw an exception
//---------------------------------------------------------------------------
#define BOOST_STM_TX_THROW(TX, EXCEPTION) throw (EXCEPTION)

#define BOOST_STM_THROW(EXCEPTION) throw (EXCEPTION)

//---------------------------------------------------------------------------
// aborts the transaction TX and throw exception
//---------------------------------------------------------------------------
#define BOOST_STM_TX_ABORT_AND_THROW(TX, EXCEPTION) if ((TX).force_to_abort()) throw (EXCEPTION)

//---------------------------------------------------------------------------
// aborts the current transaction
//---------------------------------------------------------------------------
#define BOOST_STM_ABORT_AND_THROW(EXCEPTION)     \
    if (boost::stm::current_transaction()==0) ;  \
    else BOOST_STM_TX_ABORT_AND_THROW(*boost::stm::current_transaction(), EXCEPTION)

//---------------------------------------------------------------------------
// aborts the transaction TX and throw exception
//---------------------------------------------------------------------------
#define BOOST_STM_TX_ABORT_OUTER_AND_THROW(TX, EXCEPTION) if ((TX).force_to_abort()) throw (EXCEPTION)

//---------------------------------------------------------------------------
// aborts the current transaction
//---------------------------------------------------------------------------
#define BOOST_STM_ABORT_OUTER_AND_THROW(EXCEPTION)     \
    if (boost::stm::current_transaction()==0) ;  \
    else BOOST_STM_TX_ABORT_OUTER_AND_THROW(*boost::stm::current_transaction(), EXCEPTION)

//---------------------------------------------------------------------------
// Memory management
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// creates a new allocated object on transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_TX_NEW_PTR(TX, T_PARAMS) \
    ((TX).throw_if_forced_to_abort_on_new(), \
    (TX).as_new(new T_PARAMS))

//---------------------------------------------------------------------------
// creates a new array of object of type T on transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_TX_NEW_ARRAY(TX, SIZE, T) \
    ((TX).throw_if_forced_to_abort_on_new(), \
    (TX).as_new_array(new T[SIZE], SIZE))


//---------------------------------------------------------------------------
// creates a new allocated object on the current transaction
//---------------------------------------------------------------------------
#define BOOST_STM_NEW_PTR(T_PARAMS) \
    ((boost::stm::current_transaction()!=0)  \
    ? BOOST_STM_TX_NEW_PTR(*boost::stm::current_transaction() \
        , T_PARAMS) \
    : new T_PARAMS)

//---------------------------------------------------------------------------
// creates a new array of objects of type T on the current transaction
//---------------------------------------------------------------------------
#define BOOST_STM_NEW_ARRAY(SIZE, T) \
    ((boost::stm::current_transaction()!=0)  \
    ? BOOST_STM_TX_NEW_ARRAY(*boost::stm::current_transaction() \
        , SIZE, T) \
    : new T[SIZE])

//---------------------------------------------------------------------------
// deletes the allocated object on transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_TX_DELETE_PTR(TX, PTR) \
    boost::stm::delete_ptr(TX, PTR)

//---------------------------------------------------------------------------
// deletes the allocated object on transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_TX_DELETE_ARRAY(TX, PTR) \
    (TX).delete_array(PTR)

//---------------------------------------------------------------------------
// deletes the allocated object on transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_DELETE_PTR(PTR) \
    if (boost::stm::current_transaction()!=0)  \
        BOOST_STM_TX_DELETE_PTR(*boost::stm::current_transaction(), \
            PTR) \
    else delete PTR

//---------------------------------------------------------------------------
// deletes the allocated object on transaction TX
//---------------------------------------------------------------------------

#define BOOST_STM_DELETE_ARRAY(PTR) \
    if (boost::stm::current_transaction()!=0)  \
        BOOST_STM_TX_DELETE_ARRAY(*boost::stm::current_transaction(), \
            PTR) \
    else delete [] PTR

///////////////////////////////////////////////////////////////////////////////
#endif // BOOST_STM_LANGUAGE_LIKE__HPP


